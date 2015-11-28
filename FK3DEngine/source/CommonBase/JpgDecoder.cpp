/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	JpgDecoder
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/CommonBase/CommonBaseInsideHead.h"

//==================================================================================================================

#ifdef __cplusplus 
	extern "C" 
	{
#endif

#include "../../depend/interJpeg/jpeglib.h"

#ifdef __cplusplus 
	}
#endif 

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	// IJL ��������
	METHODDEF(void) IJL_ErrProc( j_common_ptr pInfo )
	{
		//��ȡ��������
		IJL_ErrData* pErrData = (IJL_ErrData*)pInfo->err;

		//��ʽ��������Ϣ
		( *pInfo->err->format_message )( pInfo, pErrData->szErrStrBuf );

		pErrData->bError = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� JPG ͼ��ͷ
	void JpgParseHeader( ImageDecoder* pThis )
	{
		//���� JPG ʱ����Ҫ�������ļ�Ԥ�ȶ����ڴ�
		if( !pThis->mbPreLoadInMem )
			Except( Exception::ERR_INVALIDPARAMS, "���� JPG ʱ����Ҫ�������ļ�Ԥ�ȶ����ڴ档" );


		//IJL ������Ϣ
		IJL_DecodeInfo IJLDecodeInfo;
		memset( &IJLDecodeInfo, 0, sizeof(IJL_DecodeInfo) );

		jpeg_decompress_struct* pDecompData = &IJLDecodeInfo.DecompData;
		IJL_ErrData* pErrData = &IJLDecodeInfo.ErrData;

		//��ʼ�� IJL ����������
		pDecompData->err = jpeg_std_error( &pErrData->IJL_ErrMgr );
		pErrData->IJL_ErrMgr.error_exit = IJL_ErrProc;

		//����������
		jpeg_create_decompress( pDecompData );
		if( pErrData->bError )
		{
			Except( Exception::ERR_INTERNAL_ERROR, (String)"���� JPG ����������\n"
				"IJL ������Ϣ��" + pErrData->szErrStrBuf );
		}

		static MemStream sMemStream;
		sMemStream.pData = (char*)pThis->mpImageData->GetPointer();
		sMemStream.nRemLen = pThis->mpImageData->GetProtectedLen();
		sMemStream.pPos = sMemStream.pData;

		//������������Դ
		jpeg_stdio_src( pDecompData, &sMemStream );
		if( pErrData->bError )
		{
			Except( Exception::ERR_INTERNAL_ERROR, (String)"���� JPG ͼ����������Դ����\n"
				"IJL ������Ϣ��" + pErrData->szErrStrBuf );
		}

		//��ȡ JPG ͼ��ͷ
		jpeg_read_header( pDecompData, TRUE );
		if( pErrData->bError )
		{
			Except( Exception::ERR_INTERNAL_ERROR, (String)"��ȡ JPG ͼ������ͷ����\n"
				"IJL ������Ϣ��" + pErrData->szErrStrBuf );
		}

		//��ʼ���н���
		jpeg_start_decompress( pDecompData );
		if( pErrData->bError )
		{
			Except( Exception::ERR_INTERNAL_ERROR, (String)"��ʼ���� JPG ͼ�����ݽ������\n"
				"IJL ������Ϣ��" + pErrData->szErrStrBuf );
		}

		if( pDecompData->output_components != 3 )
			Except( Exception::ERR_INTERNAL_ERROR, "����� JPG ͼ�����������ɫ��ʽ��" );

		pThis->mWidth		= pDecompData->output_width;
		pThis->mHeight		= pDecompData->output_height;
		pThis->mPixelFormat	= PF_R8G8B8;


		//Ԥ�Ƚ�����ͼ�����ݽ��뵽������
		BYTE* pImageBuf = (BYTE*)malloc( pThis->mWidth * pThis->mHeight * 3 );
		BYTE* pDecodePtr = pImageBuf;

		int nDecodeWidthLen = pDecompData->output_width * 3;

		for( UINT i=0; i<pThis->mHeight; ++i )
		{
			//����һ��
			if( 1 != jpeg_read_scanlines( pDecompData, (JSAMPARRAY)&pDecodePtr, 1 ) )
			{
				free( pImageBuf );
				Except( Exception::ERR_INTERNAL_ERROR, "���� JPG ͼ������ʧ�ܡ�" );
			}

			pDecodePtr += nDecodeWidthLen;
		}

		//��������
		jpeg_finish_decompress( &IJLDecodeInfo.DecompData );
		if( pErrData->bError )
		{
			Except( Exception::ERR_INTERNAL_ERROR, (String)"���� JPG ͼ�����ݽ������\n"
				"IJL ������Ϣ��" + pErrData->szErrStrBuf );
		}

		//�ݻٽ�����
		jpeg_destroy_decompress( &IJLDecodeInfo.DecompData );
		if( pErrData->bError )
		{
			Except( Exception::ERR_INTERNAL_ERROR, (String)"�ݻ� JPG ͼ�����������\n"
				"IJL ������Ϣ��" + pErrData->szErrStrBuf );
		}

		pThis->mpExtData = pImageBuf;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��� JPG ͼ�����
	void JpgEndDecode( ImageDecoder* pThis )
	{
		SafeFree( pThis->mpExtData );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� JPG ͼ������
	void JpgDecode( ImageDecoder* pThis, BYTE* pDstBuf, RECT* srcRect, RECT* dstRect,
		int pitch, PixelFormat ePixelFormat )
	{
		//�����Դ���κ������εĽ���
		UINT srcX = 0;
		UINT srcY = 0;
		UINT dstX = 0;
		UINT dstY = 0;
		UINT srcWidth = pThis->mWidth;
		UINT srcHeight = pThis->mHeight;
		UINT dstWidth = pThis->mWidth;
		UINT dstHeight = pThis->mHeight;

		if( dstRect != NULL )
		{
			dstX = dstRect->left;
			dstY = dstRect->top;
			dstWidth = dstRect->right - dstRect->left;
			dstHeight = dstRect->bottom - dstRect->top;
		}

		if( srcRect != NULL )
		{
			srcX = srcRect->left;
			srcY = srcRect->top;
			srcWidth = srcRect->right - srcRect->left;
			srcHeight = srcRect->bottom - srcRect->top;
		}

		srcWidth = ( srcWidth<dstWidth ) ? srcWidth : dstWidth;
		srcHeight = ( srcHeight<dstHeight ) ? srcHeight : dstHeight;

		//���Ʋ�ת��ָ������ͼ������

		//�����ָ���ƶ�����ʼд��λ��
		BYTE* pDst = pDstBuf + pitch * dstY + dstX;

		//����ͼ����ʼ�ж�ȡλ��
		UINT nImageWidthLen = 3 * pThis->mWidth;
		BYTE* pSrc = (BYTE*)pThis->mpExtData + nImageWidthLen * srcY + srcX * 3;

		switch(ePixelFormat)
		{
		case PF_A8R8G8B8:
		case PF_X8R8G8B8:
			{
				for( UINT col=0; col<srcHeight; ++col )
				{
					//����ʼ��ȡλ��
					BYTE* pSrcColBeg = pSrc;
					BYTE* pDstColBeg = pDst;
					for( UINT row=0; row<srcWidth; ++row )
					{
						*pDst++ = *(pSrc+2);//��ȡ B
						*pDst++ = *(pSrc+1);//��ȡ G
						*pDst++ = *pSrc;	//��ȡ R
						*pDst++ = 0xFF;		//�Թ� A

						pSrc += 3;
					}
					//������һ��д��λ��
					pSrc = pSrcColBeg + nImageWidthLen;
					pDst = pDstColBeg + pitch;
				}
			}
			break;
		case PF_R5G6B5:
			{
				for( UINT col=0; col<srcHeight; ++col )
				{
					//����ʼ��ȡλ��
					BYTE* pSrcColBeg = pSrc;
					BYTE* pDstColBeg = pDst;
					for( UINT row=0; row<srcWidth; ++row )
					{
						BYTE r = (*pSrc++) >> 3;	//��ȡ R
						BYTE g = (*pSrc++) >> 2;	//��ȡ G
						BYTE b = (*pSrc++) >> 3;	//��ȡ B

						*(WORD*)pDst = b | (g<<5) | (r<<11);
						pDst += 2;
					}
					//������һ��д��λ��
					pSrc = pSrcColBeg + nImageWidthLen;
					pDst = pDstColBeg + pitch;
				}
			}
			break;
		case PF_A1R5G5B5:
			{
				for( UINT col=0; col<srcHeight; ++col )
				{
					//����ʼ��ȡλ��
					BYTE* pSrcColBeg = pSrc;
					BYTE* pDstColBeg = pDst;
					for( UINT row=0; row<srcWidth; ++row )
					{
						BYTE r = (*pSrc++) >> 3;	//��ȡ R
						BYTE g = (*pSrc++) >> 3;	//��ȡ G
						BYTE b = (*pSrc++) >> 3;	//��ȡ B

						*(WORD*)pDst = b | (g<<5) | (r<<10) | (1<<11);
						pDst += 2;
					}
					//������һ��д��λ��
					pSrc = pSrcColBeg + nImageWidthLen;
					pDst = pDstColBeg + pitch;
				}
			}
			break;
		case PF_A4R4G4B4:
			{
				for( UINT col=0; col<srcHeight; ++col )
				{
					//����ʼ��ȡλ��
					BYTE* pSrcColBeg = pSrc;
					BYTE* pDstColBeg = pDst;
					for( UINT row=0; row<srcWidth; ++row )
					{
						BYTE r = (*pSrc++) >> 4;	//��ȡ R
						BYTE g = (*pSrc++) >> 4;	//��ȡ G
						BYTE b = (*pSrc++) >> 4;	//��ȡ B

						*(WORD*)pDst = b | (g<<4) | (r<<8) | (16<<12);
						pDst += 2;
					}
					//������һ��д��λ��
					pSrc = pSrcColBeg + nImageWidthLen;
					pDst = pDstColBeg + pitch;
				}
			}
			break;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "����� JPG ͼ�����������ظ�ʽ��" );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
