/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	VolumeTexture
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderSystem/RenderSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	VolumeTexture::VolumeTexture( UINT nWidth, UINT nHeight, UINT nDepth,
		PixelFormat ePixelFormat, UINT nNumLevel, TextureUsage Type )
		: BaseTexture		( ePixelFormat, nNumLevel, Type )
		, mWidth			(nWidth)
		, mHeight			(nHeight)
		, mDepth			(nDepth)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	VolumeTexture::~VolumeTexture()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ����ʵ�ʳߴ�
	FKInline void VolumeTexture::GetTextureSize( UINT& nWidth, UINT& nHeight, UINT& nDepth )
	{
		nWidth	= mWidth;
		nHeight	= mHeight;
		nDepth	= nDepth;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ָ����������Ϊĳ��ɫ
	void VolumeTexture::FillColor( DWORD color, Box3* pFillBox, UINT nLevel )
	{
		//�����������
		UINT width	= ( pFillBox != NULL ) ? pFillBox->nRight - pFillBox->nLeft : mWidth;
		UINT height	= ( pFillBox != NULL ) ? pFillBox->nFront - pFillBox->nBack : mHeight;
		UINT depth	= ( pFillBox != NULL ) ? pFillBox->nBottom - pFillBox->nTop : mDepth;

		//��������
		LockBox3 sLockBox;
		LockBox( &sLockBox, pFillBox, nLevel );

		BYTE* pDstBuf = (BYTE*)sLockBox.pBits;

		switch (mPixelFormat)
		{
		case PF_X8R8G8B8:
		case PF_A8R8G8B8:
			{
				//��ѭ��
				for( UINT i=0; i<depth; ++i )
				{
					//��ѭ��
					for( UINT j=0; j<height; ++j )
					{
						DWORD* pDst = (DWORD*)pDstBuf;

						//��ѭ��
						for( UINT k=0; k<width; ++k )
							*pDst++ = color;

						pDstBuf += sLockBox.nRowPitch;
					}

					pDstBuf += sLockBox.nSlicePitch;
				}
				break;
			}
		case PF_R5G6B5:
			{
				//������ɫ����
				BYTE* pByteColor = (BYTE*)&color;
				BYTE b = (*pByteColor++) >>	3;	//��ȡ B
				BYTE g = (*pByteColor++) >>	2;	//��ȡ G
				BYTE r = (*pByteColor++) >>	3;	//��ȡ R
				WORD newColor = b | (g<<5) | (r<<11);

				//��ѭ��
				for( UINT i=0; i<depth; ++i )
				{
					//��ѭ��
					for( UINT j=0; j<height; ++j )
					{
						WORD* pDst = (WORD*)pDstBuf;

						//��ѭ��
						for( UINT k=0; k<width; ++k )
							*pDst++ = newColor;

						pDstBuf += sLockBox.nRowPitch;
					}

					pDstBuf += sLockBox.nSlicePitch;
				}
				break;
			}
		case PF_A1R5G5B5:
			{
				//������ɫ����
				BYTE* pByteColor = (BYTE*)&color;
				BYTE b = (*pByteColor++) >>	3;	//��ȡ B
				BYTE g = (*pByteColor++) >>	2;	//��ȡ G
				BYTE r = (*pByteColor++) >>	3;	//��ȡ R
				BYTE a = (*pByteColor++) >>	7;	//��ȡ A

				WORD newColor = b | (g<<5) | (r<<10) | (a<<11);

				//��ѭ��
				for( UINT i=0; i<depth; ++i )
				{
					//��ѭ��
					for( UINT j=0; j<height; ++j )
					{
						WORD* pDst = (WORD*)pDstBuf;

						//��ѭ��
						for( UINT k=0; k<width; ++k )
							*pDst++ = color;

						pDstBuf += sLockBox.nRowPitch;
					}

					pDstBuf += sLockBox.nSlicePitch;
				}
				break;
			}
		case PF_A4R4G4B4:
			{
				//������ɫ����
				BYTE* pByteColor = (BYTE*)&color;
				BYTE b = (*pByteColor++) >>	4;	//��ȡ B
				BYTE g = (*pByteColor++) >>	4;	//��ȡ G
				BYTE r = (*pByteColor++) >>	4;	//��ȡ R
				BYTE a = (*pByteColor++) >>	4;	//��ȡ A

				WORD newColor = b | (g<<4) | (r<<8) | (a<<12);

				//��ѭ��
				for( UINT i=0; i<depth; ++i )
				{
					//��ѭ��
					for( UINT j=0; j<height; ++j )
					{
						WORD* pDst = (WORD*)pDstBuf;

						//��ѭ��
						for( UINT k=0; k<width; ++k )
							*pDst++ = color;

						pDstBuf += sLockBox.nRowPitch;
					}

					pDstBuf += sLockBox.nSlicePitch;
				}
				break;
			}
		default:
			Except( Exception::ERR_INTERNAL_ERROR, "������������ظ�ʽ��" );
		}

		//��������
		UnlockBox();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
