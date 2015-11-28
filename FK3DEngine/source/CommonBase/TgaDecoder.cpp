/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	TgaDecoder
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
	//���� TGA ͼ��ͷ
	void TgaParseHeader( ImageDecoder* pThis )
	{
		//ע�⣺ ���� TGA �ļ�û�����е��ļ����ͱ�־�ֶΣ������޷��ж��Ƿ�Ϊ TGA �ļ���

		//���� TGA ���������Ϣ�����ڴ�
		TgaExtData* pExtData = (TgaExtData*)malloc( sizeof(TgaExtData) );
		if( pExtData == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "���� TGA ���������Ϣ�����ڴ�ʧ�ܡ�" );

		pThis->mpExtData = pExtData;

		//��ȡ TGA �ļ�ͷ����
		TgaFileHeader* pHeaderData = &pExtData->sTgaFileHeader;

		//����ѽ��ļ�Ԥ�ȶ����ڴ�
		if( pThis->mbPreLoadInMem )
			pThis->mpImageData->Read( pHeaderData, sizeof(TgaFileHeader) );
		//���δ���ļ�Ԥ�ȶ����ڴ������ͷ��Ϣ����
		else
			pThis->mpImageFile->Read( pHeaderData, sizeof(TgaFileHeader) );

		//�洢ͼ���ȡ��߶ȡ�ÿ����λ����
		pThis->mWidth = (UINT)pHeaderData->wPicWidth;
		pThis->mHeight = (UINT)pHeaderData->wPicHeight;

		BYTE bColorDepth = pHeaderData->bPixelBits;

		//�ж� TGA �ļ�ѹ������
		switch ( pHeaderData->bCompFlag )
		{
		case 1:
			{
				//���ʹ�õ��ǵ�ɫ���򰴵�ɫ���е���ɫλ��Ϊͼ����ɫλ��
				bColorDepth = pHeaderData->bPalUnitBits;
				pExtData->bUsePal = true;

				//�Ƿ�ʹ���г�ѹ��
				pExtData->bUseRLE = false;
				break;
			}
		case 2:
			{
				pExtData->bUsePal = false;
				pExtData->bUseRLE = false;
				break;
			}
		case 9:
			{
				bColorDepth = pHeaderData->bPalUnitBits;
				pExtData->bUsePal = true;

				pExtData->bUseRLE = true;
				break;
			}
		case 10:
			{
				pExtData->bUsePal = false;
				pExtData->bUseRLE = true;
				break;
			}
		default:
			{
				Except( Exception::ERR_CANNOT_READ_FILE, "��֧�ֵ� TGA ѹ����ʽ��" );
			}
		}

		//ʶ�����ظ�ʽ
		switch (bColorDepth)
		{
		case 16:	pThis->mPixelFormat = PF_R5G6B5;	break;
		case 24:	pThis->mPixelFormat = PF_R8G8B8;	break;
		case 32:	pThis->mPixelFormat = PF_A8R8G8B8;	break;
		default:
			Except(Exception::ERR_INTERNAL_ERROR, "��֧�ֵ� TGA ������ɫλ����" );
		}

		//�ж�ͼ�����ݴ洢˳��
		BYTE bSaveOrder = pHeaderData->bPicInfoBits & 0x30;	//ȡ�� 5��6 λ
		switch (bSaveOrder)
		{
		case 0x00:
			{
				pExtData->bYReversed = true;
				break;
			}
		case 0x20:
			{
				pExtData->bYReversed = false;
				break;
			}
		default:
			{
				Except( Exception::ERR_CANNOT_READ_FILE, "��֧�ֵ�ͼ�����ݴ洢˳��" );
			}
		}

		//����ͼ������ƫ��λ��
		long nIDLen = (long)pHeaderData->bIDLen;
		pExtData->nPicDataOffset = 18 + nIDLen;

		//���ʹ�õ�ɫ������������
		if( pExtData->bUsePal )
		{
			BYTE* pSrcPalData;

			//������ת����ɫ�����ݴ洢�ڴ棨����Ϊÿ���� 32 λ��
			pExtData->pPalData = (BYTE*)malloc( (size_t)( pHeaderData->wPalSize * 4 ) );
			if( pExtData->pPalData == NULL )
				Except( Exception::ERR_NOT_ENOUGH_MEM, "���� TGA �����ɫ�������ڴ�ʧ�ܡ�" );

			//��ȡ��ɫ������
			long nSrcPalSize = (long)( pHeaderData->wPalSize * ( pHeaderData->bPalUnitBits >> 3 ) );
			pExtData->nPicDataOffset += nSrcPalSize;

			if( pThis->mbPreLoadInMem )
			{
				//��ȡ��ɫ����ʼλ���ڴ�ָ��
				pThis->mpImageData->SetPosition( nIDLen, BP_Curpos );
				pSrcPalData = pThis->mpImageData->GetPointer();
				pThis->mpImageData->SetPosition( nSrcPalSize );
			}
			else
			{
				//����δת����ɫ�����ݴ洢�ڴ�
				pSrcPalData = (BYTE*)malloc( nSrcPalSize );
				if( pSrcPalData == NULL )
					Except( Exception::ERR_NOT_ENOUGH_MEM, "���� TGA ����ԭʼ��ɫ�������ڴ�ʧ�ܡ�" );

				//����ȡָ���ƶ�����ɫ����ʼλ��
				pThis->mpImageFile->SetPosition( nIDLen, BP_Curpos );

				//��ȡ����
				pThis->mpImageFile->Read( pSrcPalData, nSrcPalSize );
			}

			//ת����ɫ������Ϊ 32 λɫ
			BYTE* pSrcPtr = pSrcPalData;
			BYTE* pPalPtr = pExtData->pPalData;

			/*---------------------------------------------------------

			2 �ֽڱ����У������ֽڷֽ��������ʽ��
			arrrrrgg gggbbbbb

			���ǣ����ڵ�λ��ǰ����λ�ں�Ĵ洢˳�򣬴��ļ��ж�������
			ʱ�����ȶ��� gggbbbbb ������� arrrrrgg ��a ��ʾ����λ��

			3 �ֽڱ����и��ֽ����ζ�Ӧ BLUE��GREEN��RED��

			4 �ֽڱ����У��ֽ� 1 ��ʾ BLUE���ֽ� 2 ��ʾ GREEN��
			�ֽ� 3 ��ʾ RED���ֽ� 4 ��ʾ���ԡ�

			
			---------------------------------------------------------*/
			UINT nPalIndexNum = (UINT)pHeaderData->wPalSize;
			switch ( pHeaderData->bPalUnitBits )
			{
			case 16:
				{
					for( UINT i=0; i<nPalIndexNum; i++ )
					{
						*pPalPtr++ = *pSrcPtr & 0x1F;									//B
						*pPalPtr++ = ( *pSrcPtr>>5 ) | ( ( *(pSrcPtr+1) & 0x3 )<<3 );	//G
						*pPalPtr++ = ( *(pSrcPtr+1) & 0x7C)>>2;							//R
						*pPalPtr++ = 255;												//A
						pSrcPtr += 2;
					}
					break;
				}
			case 24:
				{
					for( UINT i=0; i<nPalIndexNum; i++ )
					{
						*pPalPtr++ = *pSrcPtr++;	//B
						*pPalPtr++ = *pSrcPtr++;	//G
						*pPalPtr++ = *pSrcPtr++;	//R
						*pPalPtr++ = 255;			//A
					}
					break;
				}
			case 32:
				{
					for( UINT i=0; i<nPalIndexNum; i++ )
					{
						*pPalPtr++ = *pSrcPtr++;	//B
						*pPalPtr++ = *pSrcPtr++;	//G
						*pPalPtr++ = *pSrcPtr++;	//R
						*pPalPtr++ = *pSrcPtr++;	//A
					}
					break;
				}
			default:
				if( !pThis->mbPreLoadInMem )
					FKFree( pSrcPalData );
				Except( Exception::ERR_CANNOT_READ_FILE, "��֧�ֵ� TGA ͼ���ɫ��λ����" );
			}

			if( !pThis->mbPreLoadInMem )
				FKFree( pSrcPalData );
		}
		else
		{
			pExtData->pPalData = NULL;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��� TGA ͼ�����
	void TgaEndDecode( ImageDecoder* pThis )
	{
		TgaExtData* pExtData = (TgaExtData*)pThis->mpExtData;

		//�ͷŵ�ɫ���ڴ�ռ�
		if( pExtData != NULL )
		{
			if( pExtData->bUsePal )
				SafeFree( pExtData->pPalData );

			free( pExtData );
			pExtData = NULL;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� TGA ͼ������
	void TgaDecode( ImageDecoder* pThis, BYTE* pDstBuf, RECT* srcRect, RECT* dstRect,
		int pitch, PixelFormat ePixelFormat )
	{
		//������Ϣ��¼�ṹָ��
		TgaExtData* pExtData = (TgaExtData*)pThis->mpExtData;

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

		//�����ȡ��Դ��Ŀ����ν����е�������������Ҫ����Ϣ

		UINT nByte = (UINT)pExtData->sTgaFileHeader.bPixelBits >> 3;	//ÿ�����ص��ֽ���
		UINT nBltPixel = srcWidth * srcHeight;							//��Ҫ��ȡ�����ظ���

		//���������Ƿ�ת������ʼ��дλ�úͿ��

		UINT nReadOffset = 0;	//��ʼ����ͼ�����ݶ�ȡ��ƫ���ֽ���
		UINT nProcOffset = 0;	//��ʼ����ͼ������ƫ���ֽ���
		int nPitch = 0;			//������֮�����תֵ

		if( pExtData->bYReversed )
		{
			//���һ�е�һ��Ԫ��
			nReadOffset = ( pThis->mWidth * ( pThis->mHeight-srcY-srcHeight ) + srcX ) * nByte;
			nProcOffset = ( pThis->mWidth * ( srcHeight - 1 ) ) * nByte;
			nPitch = -(int)( (pThis->mWidth+srcWidth) * nByte );	//��ת����һ�����Ŀ��
			
		}
		else
		{
			nReadOffset = ( pThis->mWidth * srcY + srcX ) * nByte;	//��һ�е�һ��Ԫ��
			nProcOffset = 0;
			nPitch = (pThis->mWidth-srcWidth) * nByte;				//��ת����һ�����Ŀ��
		}

		//������Ҫ��ȡ��ͼ������������ֽ���
		UINT nPicDataLen = pThis->mWidth * srcHeight * nByte;

		//��ȡͼ������
		BYTE* pSrcPicData = NULL;

		//���ͼ��δʹ���г�ѹ��
		if( !pExtData->bUseRLE )
		{
			if( pThis->mbPreLoadInMem )
			{
				//�洢Դ���ݶ�ȡλ��ָ��
				pThis->mpImageData->SetPosition( pExtData->nPicDataOffset + nReadOffset, BP_Begin );
				pSrcPicData = pThis->mpImageData->GetPointer();
			}
			else
			{
				//����Դͼ�����ݴ洢�ڴ��
				pSrcPicData = (BYTE*)malloc( nPicDataLen );
				if( pSrcPicData == NULL )
				{
					Except( Exception::ERR_NOT_ENOUGH_MEM, "����Դͼ�����ݴ洢�ڴ��ʧ�ܡ�" );
				}

				//���ļ��ж�ȡԴͼ������
				pThis->mpImageFile->SetPosition( pExtData->nPicDataOffset + nReadOffset, BP_Begin );
				pThis->mpImageFile->Read( pSrcPicData, nPicDataLen );
			}
		}
		//���ͼ��ʹ���г�ѹ�������Ҫ�������ļ�Ԥ�ȶ����ڴ�
		else
		{
			if( !pThis->mbPreLoadInMem )
			{
				Except( Exception::ERR_INTERNAL_ERROR,
					"�ڽ���ʹ���г�ѹ���� TGA ͼ��ʱ����Ԥ�Ƚ������ļ����ݶ����ڴ档" );
			}

			pThis->mpImageData->SetPosition( pExtData->nPicDataOffset, BP_Begin );
			pSrcPicData = pThis->mpImageData->GetPointer();
		}


		BYTE* pSrcPtr = pSrcPicData;

		//������Ҫ���͵� 32 λ��ʱͼ�����ݿ��ڴ�
		BYTE* pBitPic = (BYTE*)malloc( nBltPixel*4 );
		if( pBitPic == NULL )
		{
			Except( Exception::ERR_NOT_ENOUGH_MEM, "���� TGA ͼ��ʱ���� 32 λ��ʱͼ�����ݿ��ڴ�ʧ�ܡ�" );
		}
		memset( pBitPic, 0, nBltPixel*4 );

		//����Ŀ���ڴ��д��ָ��
		BYTE* pBuf = pBitPic;


		//������ݲ�ͬ�ĸ�ʽ����ͼ�����
		switch ( pExtData->sTgaFileHeader.bCompFlag )
		{
			//δѹ���ģ���ɫ��ͼ��
		case 1:
			{
				//��ȡ������ÿ���ص���ɫ����ֵ������ӳ��Ϊ��Ӧ����ɫ
				BYTE* pPal = pExtData->pPalData;

				//�ƶ���ȡ��������ʼλ��
				pSrcPtr += nProcOffset;

				//���ݵ�ɫ������ֵλ�����ò�ͬ��ȡ����
				switch (nByte)
				{
				case 1:
					{
						for( UINT row=0; row<srcHeight; row++ )
						{
							for( UINT col=0; col<srcWidth; col++ )
							{
								UINT nPalItem = (*pSrcPtr++) * 4;

								*pBuf++ = pPal[nPalItem];	//B
								*pBuf++ = pPal[++nPalItem];	//G
								*pBuf++ = pPal[++nPalItem];	//R
								*pBuf++ = pPal[++nPalItem];	//A
							}

							//����Ѿ���ɵ�ǰ�ж�ȡ����ת����һ�л���һ��
							pSrcPtr += nPitch;
						}
						break;
					}
				case 2:
					{
						for( UINT row=0; row<srcHeight; row++ )
						{
							for( UINT col=0; col<srcWidth; col++ )
							{
								UINT nPalItem = (*(WORD*)pSrcPtr) * 4;
								pSrcPtr += 2;

								*pBuf++ = pPal[nPalItem];	//B
								*pBuf++ = pPal[++nPalItem];	//G
								*pBuf++ = pPal[++nPalItem];	//R
								*pBuf++ = pPal[++nPalItem];	//A
							}

							//����Ѿ���ɵ�ǰ�ж�ȡ����ת����һ�л���һ��
							pSrcPtr += nPitch;
						}
						break;
					}
				case 4:
					{
						for( UINT row=0; row<srcHeight; row++ )
						{
							for( UINT col=0; col<srcWidth; col++ )
							{
								UINT nPalItem = (*(DWORD*)pSrcPtr) * 4;
								pSrcPtr += 4;

								*pBuf++ = pPal[nPalItem];	//B
								*pBuf++ = pPal[++nPalItem];	//G
								*pBuf++ = pPal[++nPalItem];	//R
								*pBuf++ = pPal[++nPalItem];	//A
							}

							//����Ѿ���ɵ�ǰ�ж�ȡ����ת����һ�л���һ��
							pSrcPtr += nPitch;
						}
						break;
					}
				default:
					Except( Exception::ERR_CANNOT_READ_FILE, "����� TGA ͼ���ɫ��������λ����" );
				}

				break;
			}
			//δѹ���ģ�λͼͼ��
		case 2:
			{
				//�ƶ���ȡ��������ʼλ��
				pSrcPtr += nProcOffset;

				//����ÿ����λ����ɫ�ѡ��ͬ��ֵ��ʽ��ͳһת��Ϊ BGRA��
				switch (nByte)
				{
					//16 λ
				case 2:
					{
						for( UINT row=0; row<srcHeight; row++ )
						{
							for( UINT col=0; col<srcWidth; col++ )
							{
								*pBuf++ = ( *pSrcPtr & 0x1F ) * 8;									//B
								*pBuf++ = ( ( *pSrcPtr>>5 ) | ( ( *(pSrcPtr+1) & 0x3 )<<3 ) ) * 8;	//G
								*pBuf++ = ( *(pSrcPtr+1) & 0x7C) * 2;								//R
								*pBuf++ = 255;														//A

								pSrcPtr += 2;
							}

							//����Ѿ���ɵ�ǰ�ж�ȡ����ת����һ�л���һ��
							pSrcPtr += nPitch;
						}
						break;
					}
					//24 λ
				case 3:
					{
						for( UINT row=0; row<srcHeight; row++ )
						{
							for( UINT col=0; col<srcWidth; col++ )
							{
								*pBuf++ = *pSrcPtr++;	//B
								*pBuf++ = *pSrcPtr++;	//G
								*pBuf++ = *pSrcPtr++;	//R
								*pBuf++ = 255;			//A
							}

							//����Ѿ���ɵ�ǰ�ж�ȡ����ת����һ�л���һ��
							pSrcPtr += nPitch;
						}
						break;
					}
					//32 λ
				case 4:
					{
						for( UINT row=0; row<srcHeight; row++ )
						{
							for( UINT col=0; col<srcWidth; col++ )
							{
								*pBuf++ = *pSrcPtr++;	//B
								*pBuf++ = *pSrcPtr++;	//G
								*pBuf++ = *pSrcPtr++;	//R
								*pBuf++ = *pSrcPtr++;	//A
							}

							//����Ѿ���ɵ�ǰ�ж�ȡ����ת����һ�л���һ��
							pSrcPtr += nPitch;
						}
						break;
					}
				default:
					Except( Exception::ERR_CANNOT_READ_FILE, "����� TGA ͼ��ɫ�" );
				}

				break;
			}

			//--------------------------------------------------------------------------------------------
			//ѹ����ͼ�����ݣ�Ϊ���ܿ��Ǳ����ȶ�ȡ���е����ص�һ���м仺�棬Ȼ���ٴ�����ʱ���н����Ĳ��֡�
			//--------------------------------------------------------------------------------------------

			//�г̱���ĵ�ɫ��ͼ��
		case 9:
			{
				//��ȡ��������
				UINT nNumPixel = pThis->mWidth * pThis->mHeight;

				//����ͼ�������ڴ��
				UINT nTmpBitLen = nNumPixel * nByte;
				BYTE* pTmpBitPic = (BYTE*)malloc( nTmpBitLen );
				if( pTmpBitPic == NULL )
				{
					Except( Exception::ERR_NOT_ENOUGH_MEM, "���� TGA ͼ������г�ѹ����ѹ��ʱ����ʧ�ܡ�" );
				}
				memset( pTmpBitPic, 0, nTmpBitLen );

				//��ʱ�ڴ��д��ָ��
				BYTE* pTmpBuf = pTmpBitPic;
				BYTE* pPal = pExtData->pPalData;

				//���ݸ��ݵ�ɫ��λ��ѡ��ͬ���뷽ʽ
				switch (nByte)
				{
				case 1:
					{
						//ѭ����ȡֱ������������������ȡ���
						for( UINT i=0; i<nNumPixel;)
						{
							//ʶ�����ݰ�ͷ��Ϣ����

							//�г����ݰ���ͷ��Ϣ����λ��¼���������ɫֵ�ظ��Ĵ�����
							if( ( *pSrcPtr & 0x80 ) == 128 )
							{
								//�����ظ��������ۼ����ؼ���
								UINT repeat = ( *pSrcPtr++ & 0x7F ) + 1;
								i += repeat;

								//��¼�ظ���������ɫ����ֵ
								BYTE Index = *pSrcPtr++;

								//����ظ�������
								for( UINT c=0; c<repeat; c++ )
								{
									*pTmpBuf++ = Index;
								}
							}
							//���г����ݰ���ͷ��Ϣ����λ��¼�������������ɫֵ������
							else
							{
								//����������������������ۼ����ؼ���
								UINT nPixel = ( *pSrcPtr++ & 0x7F ) + 1;
								i += nPixel;

								//���ð�����������
								for( UINT c=0; c<nPixel; c++ )
								{
									*pTmpBuf++ = *pSrcPtr++;
								}
							}
						}

						//��������ϵ�������������Ҫ�Ľ������ִ��͵� pBitPic �ڴ���У���ɫֵӳ�䣩

						//������ʼ��ȡλ��
						pTmpBuf = pTmpBitPic + nReadOffset + nProcOffset;

						for( UINT row=0; row<srcHeight; row++ )
						{
							for( UINT col=0; col<srcWidth; col++ )
							{
								UINT nPalItem = (*pTmpBuf++) * 4;

								*pBuf++ = pPal[nPalItem];	//B
								*pBuf++ = pPal[++nPalItem];	//G
								*pBuf++ = pPal[++nPalItem];	//R
								*pBuf++ = pPal[++nPalItem];	//A
							}

							//����Ѿ���ɵ�ǰ�ж�ȡ����ת����һ�л���һ��
							pTmpBuf += nPitch;
						}

						break;
					}
				case 2:
					{
						//ѭ����ȡֱ���������ض���ȡ���
						for( UINT i=0; i<nNumPixel;)
						{
							//ʶ�����ݰ�ͷ��Ϣ����

							//�г����ݰ���ͷ��Ϣ����λ��¼���������ɫֵ�ظ��Ĵ�����
							if( ( *pSrcPtr & 0x80 ) == 128 )
							{
								//�����ظ��������ۼ����ؼ���
								UINT repeat = ( *pSrcPtr++ & 0x7F ) + 1;
								i += repeat;

								//��¼�ظ���������ɫ����ֵ
								BYTE HiBits = *pSrcPtr++;
								BYTE LoBits = *pSrcPtr++;

								//����ظ�������
								for( UINT c=0; c<repeat; c++ )
								{
									*pTmpBuf++ = HiBits;
									*pTmpBuf++ = LoBits;
								}
							}
							//���г����ݰ���ͷ��Ϣ����λ��¼�������������ɫֵ������
							else
							{
								//����������������������ۼ����ؼ���
								UINT nPixel = ( *pSrcPtr++ & 0x7F ) + 1;
								i += nPixel;

								//���ð�����������
								for( UINT c=0; c<nPixel; c++ )
								{
									*pTmpBuf++ = *pSrcPtr++;	//B
									*pTmpBuf++ = *pSrcPtr++;	//G
								}
							}
						}

						//��������ϵ�������������Ҫ�Ľ������ִ��͵� pBitPic �ڴ���У���ɫֵӳ�䣩

						//������ʼ��ȡλ��
						pTmpBuf = pTmpBitPic + nReadOffset + nProcOffset;

						for( UINT row=0; row<srcHeight; row++ )
						{
							for( UINT col=0; col<srcWidth; col++ )
							{
								UINT nPalItem = (*(WORD*)pTmpBuf) * 4;
								pTmpBuf += 2;

								*pBuf++ = pPal[nPalItem];	//B
								*pBuf++ = pPal[++nPalItem];	//G
								*pBuf++ = pPal[++nPalItem];	//R
								*pBuf++ = pPal[++nPalItem];	//A
							}

							//����Ѿ���ɵ�ǰ�ж�ȡ����ת����һ�л���һ��
							pTmpBuf += nPitch;
						}

						break;
					}
					//32 λ
				case 4:
					{
						//ѭ����ȡֱ���������ض���ȡ���
						for( UINT i=0; i<nNumPixel;)
						{
							//�г����ݰ���ͷ��Ϣ����λ��¼���������ɫֵ�ظ��Ĵ�����
							if( ( *pSrcPtr & 0x80 ) == 128 )
							{
								//�����ظ��������ۼ����ؼ���
								UINT repeat = ( *pSrcPtr++ & 0x7F ) + 1;
								i += repeat;

								//��¼�ظ���������ɫ����ֵ
								BYTE Index1 = *pSrcPtr++;
								BYTE Index2 = *pSrcPtr++;
								BYTE Index3 = *pSrcPtr++;
								BYTE Index4 = *pSrcPtr++;

								//����ظ�������
								for( UINT c=0; c<repeat; c++ )
								{
									*pTmpBuf++ = Index1;
									*pTmpBuf++ = Index2;
									*pTmpBuf++ = Index3;
									*pTmpBuf++ = Index4;
								}
							}
							//���г����ݰ���ͷ��Ϣ����λ��¼�������������ɫֵ������
							else
							{
								//����������������������ۼ����ؼ���
								UINT nPixel = ( *pSrcPtr++ & 0x7F ) + 1;
								i += nPixel;

								//���ð�����������
								for( UINT c=0; c<nPixel; c++ )
								{
									*pTmpBuf++ = *pSrcPtr++;	//B
									*pTmpBuf++ = *pSrcPtr++;	//G
									*pTmpBuf++ = *pSrcPtr++;	//R
									*pTmpBuf++ = *pSrcPtr++;	//A
								}
							}
						}

						//��������ϵ�������������Ҫ�Ľ������ִ��͵� pBitPic �ڴ���У���ɫֵӳ�䣩

						//������ʼ��ȡλ��
						pTmpBuf = pTmpBitPic + nReadOffset + nProcOffset;

						for( UINT row=0; row<srcHeight; row++ )
						{
							for( UINT col=0; col<srcWidth; col++ )
							{
								UINT nPalItem = (*(DWORD*)pTmpBuf) * 4;
								pTmpBuf += 4;

								*pBuf++ = pPal[nPalItem];	//B
								*pBuf++ = pPal[++nPalItem];	//G
								*pBuf++ = pPal[++nPalItem];	//R
								*pBuf++ = pPal[++nPalItem];	//A
							}

							//����Ѿ���ɵ�ǰ�ж�ȡ����ת����һ�л���һ��
							pTmpBuf += nPitch;
						}

						break;
					}
				default:
					Except( Exception::ERR_CANNOT_READ_FILE, "����� TGA ͼ���ɫ��������λ����" );
				}

				FKFree( pTmpBitPic );
				break;
			}
			//�г̱����λͼͼ��
		case 10:
			{
				//��ȡ��������
				UINT nNumPixel = pThis->mWidth * pThis->mHeight;

				//����ͼ�������ڴ��
				UINT nTmpBitLen = nNumPixel * nByte;
				BYTE* pTmpBitPic = (BYTE*)malloc( nTmpBitLen );
				if( pTmpBitPic == NULL )
				{
					Except( Exception::ERR_NOT_ENOUGH_MEM, "���� TGA ͼ������г�ѹ����ѹ��ʱ����ʧ�ܡ�" );
				}
				memset( pTmpBitPic, 0, nTmpBitLen );

				//��ʱ�ڴ��д��ָ��
				BYTE* pTmpBuf = pTmpBitPic;

				//����ÿ����λ����ɫ�ѡ��ͬ��ֵ��ʽ
				switch (nByte)
				{
					//16 λ
				case 2:
					{
						//ѭ����ȡֱ���������ض���ȡ���
						for( UINT i=0; i<nNumPixel;)
						{
							//ʶ�����ݰ�ͷ��Ϣ����

							//�г����ݰ���ͷ��Ϣ����λ��¼���������ɫֵ�ظ��Ĵ�����
							if( ( *pSrcPtr & 0x80 ) == 128 )
							{
								//�����ظ��������ۼ����ؼ���
								UINT repeat = ( *pSrcPtr++ & 0x7F ) + 1;
								i += repeat;

								//��¼�ظ���������ɫֵ
								BYTE HiBits = *pSrcPtr++;
								BYTE LoBits = *pSrcPtr++;

								//����ظ�������
								for( UINT c=0; c<repeat; c++ )
								{
									*pTmpBuf++ = HiBits;
									*pTmpBuf++ = LoBits;
								}
							}
							//���г����ݰ���ͷ��Ϣ����λ��¼�������������ɫֵ������
							else
							{
								//����������������������ۼ����ؼ���
								UINT nPixel = ( *pSrcPtr++ & 0x7F ) + 1;
								i += nPixel;

								//���ð�����������
								for( UINT c=0; c<nPixel; c++ )
								{
									*pTmpBuf++ = *pSrcPtr++;
									*pTmpBuf++ = *pSrcPtr++;
								}
							}
						}

						//��������ϵ�λͼ��������Ҫ�Ľ������ִ��͵� pBitPic �ڴ���У���ͬʱ���� 32 λת����

						//������ʼ��ȡλ��
						pTmpBuf = pTmpBitPic + nReadOffset + nProcOffset;

						for( UINT row=0; row<srcHeight; row++ )
						{
							for( UINT col=0; col<srcWidth; col++ )
							{
								*pBuf++ = ( *pTmpBuf & 0x1F ) * 8;									//B
								*pBuf++ = ( ( *pTmpBuf>>5 ) | ( ( *(pTmpBuf+1) & 0x3 )<<3 ) ) * 8;	//G
								*pBuf++ = ( ( *(pTmpBuf+1) & 0x7C)>>2 ) * 8;						//R
								*pBuf++ = 255;														//A
								pTmpBuf += 2;
							}

							//����Ѿ���ɵ�ǰ�ж�ȡ����ת����һ�л���һ��
							pTmpBuf += nPitch;
						}

						break;
					}
					//24 λ
				case 3:
					{
						//ѭ����ȡֱ���������ض���ȡ���
						for( UINT i=0; i<nNumPixel;)
						{
							//ʶ�����ݰ�ͷ��Ϣ����

							//�г����ݰ���ͷ��Ϣ����λ��¼���������ɫֵ�ظ��Ĵ�����
							if( ( *pSrcPtr & 0x80 ) == 128 )
							{
								//�����ظ��������ۼ����ؼ���
								UINT repeat = ( *pSrcPtr++ & 0x7F ) + 1;
								i += repeat;

								//��¼�ظ���������ɫֵ
								BYTE b = *pSrcPtr++;		//B
								BYTE g = *pSrcPtr++;		//G
								BYTE r = *pSrcPtr++;		//R

								//����ظ�������
								for( UINT c=0; c<repeat; c++ )
								{
									*pTmpBuf++ = b;
									*pTmpBuf++ = g;
									*pTmpBuf++ = r;
								}
							}
							//���г����ݰ���ͷ��Ϣ����λ��¼�������������ɫֵ������
							else
							{
								//����������������������ۼ����ؼ���
								UINT nPixel = ( *pSrcPtr++ & 0x7F ) + 1;
								i += nPixel;

								//���ð�����������
								for( UINT c=0; c<nPixel; c++ )
								{
									*pTmpBuf++ = *pSrcPtr++;	//B
									*pTmpBuf++ = *pSrcPtr++;	//G
									*pTmpBuf++ = *pSrcPtr++;	//R
								}
							}
						}

						//��������ϵ�λͼ��������Ҫ�Ľ������ִ��͵� pBitPic �ڴ���У���ͬʱ���� 32 λת����

						//������ʼ��ȡλ��
						pTmpBuf = pTmpBitPic + nReadOffset + nProcOffset;

						for( UINT row=0; row<srcHeight; row++ )
						{
							for( UINT col=0; col<srcWidth; col++ )
							{
								*pBuf++ = *pTmpBuf++;	//B
								*pBuf++ = *pTmpBuf++;	//G
								*pBuf++ = *pTmpBuf++;	//R
								*pBuf++ = 255;			//A
							}

							//����Ѿ���ɵ�ǰ�ж�ȡ����ת����һ�л���һ��
							pTmpBuf += nPitch;
						}

						break;
					}
					//32 λ
				case 4:
					{
						//ѭ����ȡֱ���������ض���ȡ���
						for( UINT i=0; i<nNumPixel;)
						{
							//�г����ݰ���ͷ��Ϣ����λ��¼���������ɫֵ�ظ��Ĵ�����
							if( ( *pSrcPtr & 0x80 ) == 128 )
							{
								//�����ظ��������ۼ����ؼ���
								UINT repeat = ( *pSrcPtr++ & 0x7F ) + 1;
								i += repeat;

								//��¼�ظ���������ɫֵ
								BYTE b = *pSrcPtr++;		//B
								BYTE g = *pSrcPtr++;		//G
								BYTE r = *pSrcPtr++;		//R
								BYTE a = *pSrcPtr++;		//A

								//����ظ�������
								for( UINT c=0; c<repeat; c++ )
								{
									*pTmpBuf++ = b;
									*pTmpBuf++ = g;
									*pTmpBuf++ = r;
									*pTmpBuf++ = a;
								}
							}
							//���г����ݰ���ͷ��Ϣ����λ��¼�������������ɫֵ������
							else
							{
								//����������������������ۼ����ؼ���
								UINT nPixel = ( *pSrcPtr++ & 0x7F ) + 1;
								i += nPixel;

								//���ð�����������
								for( UINT c=0; c<nPixel; c++ )
								{
									*pTmpBuf++ = *pSrcPtr++;	//B
									*pTmpBuf++ = *pSrcPtr++;	//G
									*pTmpBuf++ = *pSrcPtr++;	//R
									*pTmpBuf++ = *pSrcPtr++;	//A
								}
							}
						}

						//��������ϵ�λͼ��������Ҫ�Ľ������ִ��͵� pBitPic �ڴ���У���ͬʱ���� 32 λת����

						//������ʼ��ȡλ��
						pTmpBuf = pTmpBitPic + nReadOffset + nProcOffset;

						for( UINT row=0; row<srcHeight; row++ )
						{
							for( UINT col=0; col<srcWidth; col++ )
							{
								*pBuf++ = *pTmpBuf++;	//B
								*pBuf++ = *pTmpBuf++;	//G
								*pBuf++ = *pTmpBuf++;	//R
								*pBuf++ = *pTmpBuf++;	//A
							}

							//����Ѿ���ɵ�ǰ�ж�ȡ����ת����һ�л���һ��
							pTmpBuf += nPitch;
						}

						break;
					}
				default:
					Except( Exception::ERR_CANNOT_READ_FILE, "����� TGA ͼ��ɫ�" );
				}

				FKFree( pTmpBitPic );
				break;
			}

			//������֧�ֵ�����
		default:
			Except( Exception::ERR_CANNOT_READ_FILE, "��֧�ֵ� TGA ѹ����ʽ��" );
		}

		//������ɣ����Ѿ���Ϊ 32 λλͼģʽ��ͼ���͵�Ŀ�껺��

		//��������Ҫ��ͼ�����ݶ�ȡ��Ϻ������Ӧ�ĺ���������ɫģʽ��ת���ʹ���

		pBuf = pBitPic;				//��ȡָ��
		BYTE*	pDst = pDstBuf;		//���ָ��
		UINT	nBegOffset = pitch/4 * dstY + dstX;	//�����ʼƫ��������

		switch (ePixelFormat)
		{
		case PF_A8R8G8B8:
		case PF_X8R8G8B8:
			{
				pDst += nBegOffset * 4;
				BYTE* pColBeg = pDst;

				//ѭ�������������
				for( UINT row=0; row<srcHeight; row++ )
				{
					for( UINT col=0; col<srcWidth; col++ )
					{
						*pDst++ = *pBuf++;	//��ȡ B
						*pDst++ = *pBuf++;	//��ȡ G
						*pDst++ = *pBuf++;	//��ȡ R
						*pDst++ = *pBuf++;	//��ȡ A
					}

					//����Ѿ���ɵ�ǰ�д�������ת��
					pColBeg += pitch;
					pDst = pColBeg;
				}
				break;
			}
		case PF_R5G6B5:
			{
				pDst += nBegOffset * 2;
				BYTE* pColBeg = pDst;

				//ѭ�������������
				for( UINT row=0; row<srcHeight; row++ )
				{
					for( UINT col=0; col<srcWidth; col++ )
					{
						BYTE b = (*pBuf++) >> 3;	//��ȡ B
						BYTE g = (*pBuf++) >> 2;	//��ȡ G
						BYTE r = (*pBuf++) >> 3;	//��ȡ R
						pBuf++;						//�Թ� A

						*(WORD*)pDst = b | (g<<5) | (r<<11);
						pDst += 2;
					}

					//����Ѿ���ɵ�ǰ�д�������ת��
					pColBeg += pitch;
					pDst = pColBeg;
				}
				break;
			}
		case PF_A1R5G5B5:
			{
				pDst += nBegOffset * 2;
				BYTE* pColBeg = pDst;

				//ѭ�������������
				for( UINT row=0; row<srcHeight; row++ )
				{
					for( UINT col=0; col<srcWidth; col++ )
					{
						BYTE b = (*pBuf++) >> 3;	//��ȡ B
						BYTE g = (*pBuf++) >> 3;	//��ȡ G
						BYTE r = (*pBuf++) >> 3;	//��ȡ R
						BYTE a = (*pBuf++) >> 7;	//��ȡ A

						*(WORD*)pDst = b | (g<<5) | (r<<10) | (a<<11);
						pDst += 2;
					}

					//����Ѿ���ɵ�ǰ�д�������ת��
					pColBeg += pitch;
					pDst = pColBeg;
				}
				break;
			}
		case PF_A4R4G4B4:
			{
				pDst += nBegOffset * 2;
				BYTE* pColBeg = pDst;

				//ѭ�������������
				for( UINT row=0; row<srcHeight; row++ )
				{
					for( UINT col=0; col<srcWidth; col++ )
					{
						BYTE b = (*pBuf++) >> 4;	//��ȡ B
						BYTE g = (*pBuf++) >> 4;	//��ȡ G
						BYTE r = (*pBuf++) >> 4;	//��ȡ R
						BYTE a = (*pBuf++) >> 4;	//��ȡ A

						*(WORD*)pDst = b | (g<<4) | (r<<8) | (a<<12);
						pDst += 2;
					}

					//����Ѿ���ɵ�ǰ�д�������ת��
					pColBeg += pitch;
					pDst = pColBeg;
				}
				break;
			}
		default:
			FKFree( pBitPic );
			Except( Exception::ERR_INVALIDPARAMS, "����� TGA ͼ�����������ظ�ʽ��" );
		}

		//�ͷŽ��������ؼ���ʱ�洢�ռ�
		FKFree( pBitPic );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
