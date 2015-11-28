/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	DDSDecoder
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/CommonBase/CommonBaseInsideHead.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//���� DDS ͼ��ͷ
	void DDSParseHeader( ImageDecoder* pThis )
	{
		//��ȡ DDS �ļ�ͷ
		char szHeader[4];

		if( pThis->mbPreLoadInMem )
			pThis->mpImageData->Read( szHeader, 4 );
		else
			pThis->mpImageFile->Read( szHeader, 4 );

		if( 0 != memcmp( szHeader, "DDS ", 4 ) )
			Except( Exception::ERR_CANNOT_READ_FILE, "����� DDS �ļ���ʽ��" );

		//��ȡ����ͷ
		DDSURFACEDESC2 sSurfaceDesc;
		if( pThis->mbPreLoadInMem )
			pThis->mpImageData->Read( &sSurfaceDesc, sizeof(sSurfaceDesc) );
		else
			pThis->mpImageFile->Read( &sSurfaceDesc, sizeof(sSurfaceDesc) );
			
		if( sSurfaceDesc.dwSize != 124 )
			Except( Exception::ERR_INTERNAL_ERROR, "����� DDS �ļ����������ṹ��С��" );
		if( sSurfaceDesc.ddpfPixelFormat.dwSize != 32 )
			Except( Exception::ERR_INTERNAL_ERROR, "����� DDS �ļ����ظ�ʽ�ṹ��С��" );

		//ʶ��ͼ���ʽ
		if( sSurfaceDesc.ddpfPixelFormat.dwFlags & DDPF_RGB )
		{
			switch (sSurfaceDesc.ddpfPixelFormat.dwRGBBitCount)
			{
			case 16:	pThis->mPixelFormat = PF_R5G6B5;	break;
			case 24:	pThis->mPixelFormat = PF_R8G8B8;	break;
			case 32:	pThis->mPixelFormat = PF_A8R8G8B8;	break;
			default:
				Except( Exception::ERR_INTERNAL_ERROR, "����� DDS �ļ� RGB ���ظ�ʽλ����" );
			}
		}
		else if( sSurfaceDesc.ddpfPixelFormat.dwFlags & DDPF_FOURCC )
		{
			switch (sSurfaceDesc.ddpfPixelFormat.dwFourCC)
			{
			case TEXC_DXT1:		pThis->mPixelFormat = PF_DXT1;	break;
			case TEXC_DXT2:		pThis->mPixelFormat = PF_DXT2;	break;
			case TEXC_DXT3:		pThis->mPixelFormat = PF_DXT3;	break;
			case TEXC_DXT4:		pThis->mPixelFormat = PF_DXT4;	break;
			case TEXC_DXT5:		pThis->mPixelFormat = PF_DXT5;	break;
			default:
				Except( Exception::ERR_INTERNAL_ERROR, "��֧�ֵ� DDS �ļ�����ѹ����ʽ��" );
			}
		}
		else
			Except( Exception::ERR_INTERNAL_ERROR, "��֧�ֵ� DDS �ļ�ͼ���ʽ��" );

		//�洢ͼ��ߴ�
		pThis->mWidth = sSurfaceDesc.dwWidth;
		pThis->mHeight = sSurfaceDesc.dwHeight;

		//��ȡͼ����
		DWORD dwCaps1 = sSurfaceDesc.ddsCaps.dwCaps1;
		DWORD dwCaps2 = sSurfaceDesc.ddsCaps.dwCaps2;

		DWORD			dwLevelCount	= 1;
		DDSImageType	eDDSType		= DDS_Normal;

		//���Ϊ�༶����
		if( dwCaps1 & DDSCAPS_COMPLEX )
		{
			//���Ϊ��ͨ�༶ӳ������
			if( dwCaps1 & DDSCAPS_MIPMAP )
			{
				eDDSType = DDS_Normal;
				dwLevelCount = sSurfaceDesc.dwMipMapCount;
			}
			//���Ϊ��״����
			else if( dwCaps2 & DDSCAPS2_CUBEMAP )
			{
				eDDSType = DDS_Cube;

				if( dwCaps2 ^ DDSCAPS2_CUBEMAP_ALL )
					Except( Exception::ERR_INTERNAL_ERROR, "����������ȴ���� DDS �ļ���״����" );

				dwLevelCount = 6;
			}
			//���Ϊ��������
			else if( dwCaps2 & DDSCAPS2_VOLUME )
			{
				eDDSType = DDS_Volume;
			}
		}

		//���� DDS ������Ϣ����
		DDSDecodeInfo* pDDSInfo = (DDSDecodeInfo*)malloc( sizeof(DDSDecodeInfo) + sizeof(DDSImageLevel) * dwLevelCount );
		DDSImageLevel* pDDSLevel = (DDSImageLevel*)pDDSInfo + 1;

		pDDSInfo->dwLevelCount	= dwLevelCount;
		pDDSInfo->dwDecodeLevel = 0;
		pDDSInfo->eImageType	= eDDSType;
		pDDSInfo->pImageLevel	= pDDSLevel;

		pThis->mpDDSInfo = pDDSInfo;

		//���� DDS ͼ����Ϣ
		DWORD dwDataOffset = sizeof(DDSURFACEDESC2) + 4;
		DWORD dwWidth = sSurfaceDesc.dwWidth;
		DWORD dwHeight = sSurfaceDesc.dwHeight;

		//����δѹ�����ݳ���
		DWORD dwImageSize = 0;
		if( sSurfaceDesc.ddpfPixelFormat.dwFlags & DDPF_RGB )
			dwImageSize = sSurfaceDesc.dwPitchOrLinearSize * dwHeight;

		switch (eDDSType)
		{
		case DDS_Normal:
			{
				//��������ӳ�伶ͼ����Ϣ
				for( DWORD i=0; i<dwLevelCount; ++i, ++pDDSLevel )
				{
					pDDSLevel->dwWidth = dwWidth;
					pDDSLevel->dwHeight = dwHeight;

					//�������ݳ���

					//���Ϊѹ������
					if( dwImageSize == 0 )
					{
						DWORD dwSize = max( 1, dwWidth >> 2 ) * max( 1, dwHeight >> 2 );
						if( pThis->mPixelFormat == PF_DXT1 )
							dwSize <<= 3;
						else
							dwSize <<= 4;

						pDDSLevel->dwDataLen = dwSize;
					}
					//���Ϊδѹ������
					else
					{
						pDDSLevel->dwDataLen = dwImageSize;
						dwImageSize >>= 2;
					}

					pDDSLevel->dwDataOffset = dwDataOffset;
					dwDataOffset += pDDSLevel->dwDataLen;

					dwWidth >>= 1;
					dwHeight >>= 1;
				}
				break;
			}
		/*case DDS_Cube:
			{
				break;
			}
		case DDS_Volume:
			{
				break;
			}*/
		default:
			Except( Exception::ERR_INTERNAL_ERROR, "����� DDS �������͡�" );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��� DDS ͼ�����
	void DDSEndDecode( ImageDecoder* pThis )
	{
		//�ͷ� DDS ������Ϣ����
		SafeFree( pThis->mpDDSInfo );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� DDS ͼ������
	void DDSDecode( ImageDecoder* pThis, BYTE* pDstBuf, RECT* srcRect, RECT* dstRect,
		int pitch, PixelFormat ePixelFormat )
	{
		//��ȡ��ǰ����ͼ������
		DWORD dwDecodeLevel = pThis->mpDDSInfo->dwDecodeLevel;
		if( dwDecodeLevel >= pThis->mpDDSInfo->dwLevelCount )
			Except( Exception::ERR_INVALIDPARAMS, "ָ������� DDS ͼ�񼶱𲻴��ڡ�" );

		DDSImageLevel* pDDSLevel = pThis->mpDDSInfo->pImageLevel + dwDecodeLevel;

		//���Ϊѹ�������ʽ
		if( pThis->mPixelFormat & PF_COMPRESS_MASK )
		{
			if( srcRect != NULL || dstRect != NULL )
				Except( Exception::ERR_INVALIDPARAMS, "�޷�ָ������ѹ����ʽ DDS ͼ��Ľ�������" );

			if( ePixelFormat != pThis->mPixelFormat )
				Except( Exception::ERR_INVALIDPARAMS, "����ʹ�õ�ǰ DDS ͼ�������ѹ����ʽ���н��롣" );

			//�������ݻ���
			BYTE* pSrcBuf = (BYTE*)malloc( pDDSLevel->dwDataLen );
			if( pSrcBuf == NULL )
				Except( Exception::ERR_NOT_ENOUGH_MEM, "���� DDS ͼ����뻺��ʧ�ܡ�" );

			//��ѹ�����ݶ��뻺��
			if( pThis->mbPreLoadInMem )
			{
				pThis->mpImageData->SetPosition( pDDSLevel->dwDataOffset, BP_Begin );
				pThis->mpImageData->Read( pSrcBuf, pDDSLevel->dwDataLen );
			}
			else
			{
				pThis->mpImageFile->SetPosition( pDDSLevel->dwDataOffset, BP_Begin );
				pThis->mpImageFile->Read( pSrcBuf, pDDSLevel->dwDataLen );
			}

			//����ѹ������
			memcpy( pDstBuf, pSrcBuf, pDDSLevel->dwDataLen );

			free( pSrcBuf );
		}
		else
		{
			Except( Exception::ERR_INVALIDPARAMS, "�޷����������ѹ����ʽ�� DDS ͼ��" );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
