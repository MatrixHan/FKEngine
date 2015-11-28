/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Texture
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
	Texture::Texture( UINT nWidth, UINT nHeight, PixelFormat ePixelFormat, UINT nNumLevel, TextureUsage Type )
		: BaseTexture		( ePixelFormat, nNumLevel, Type )
		, mWidth			(nWidth)
		, mHeight			(nHeight)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	Texture::~Texture()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ����ʵ�ʳߴ�
	FKInline void Texture::GetTextureSize( UINT& nWidth, UINT& nHeight )
	{
		nWidth = mWidth;
		nHeight = mHeight;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ָ����������Ϊĳ��ɫ
	void Texture::FillColor( DWORD color, RECT* pFillRect, UINT nLevel )
	{
		BYTE* pDstBuf = NULL;
		UINT pitch = 0;

		//���������
		UINT width = ( pFillRect != NULL ) ? pFillRect->right - pFillRect->left : mWidth;
		UINT height = ( pFillRect != NULL ) ? pFillRect->bottom - pFillRect->top : mHeight;

		//��������
		LockRect( (void**)&pDstBuf, &pitch, pFillRect, nLevel );

		switch (mPixelFormat)
		{
		case PF_X8R8G8B8:
		case PF_A8R8G8B8:
			{
				//��ѭ��
				for( UINT row=0; row<height; ++row )
				{
					DWORD* pDst = (DWORD*)pDstBuf;

					//��ѭ��
					for( UINT col=0; col<width; ++col )
						*pDst++ = color;

					pDstBuf += pitch;
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
				for( UINT row=0; row<height; ++row )
				{
					WORD* pDst = (WORD*)pDstBuf;

					//��ѭ��
					for( UINT col=0; col<width; ++col )
						*pDst++ = newColor;

					pDstBuf += pitch;
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
				for( UINT row=0; row<height; ++row )
				{
					WORD* pDst = (WORD*)pDstBuf;

					//��ѭ��
					for( UINT col=0; col<width; ++col )
						*pDst++ = newColor;

					pDstBuf += pitch;
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
				for( UINT row=0; row<height; ++row )
				{
					WORD* pDst = (WORD*)pDstBuf;

					//��ѭ��
					for( UINT col=0; col<width; ++col )
						*pDst++ = newColor;

					pDstBuf += pitch;
				}
				break;
			}
		default:
			Except( Exception::ERR_INTERNAL_ERROR, "������������ظ�ʽ��" );
		}

		//��������
		UnlockRect();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
