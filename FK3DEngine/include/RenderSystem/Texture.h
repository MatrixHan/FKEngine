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

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��ά������
	class FK_DLL Texture : public BaseTexture
	{
	public:
		UINT		mWidth;			//������
		UINT		mHeight;		//����߶�

	public:
		Texture( UINT nWidth, UINT nHeight, PixelFormat ePixelFormat, UINT nNumLevel, TextureUsage Type );
		virtual ~Texture() = 0;

		//��ȡ����ʵ�ʳߴ�
		FKInline void GetTextureSize( UINT& nWidth, UINT& nHeight );

		//���ָ����������Ϊĳ��ɫ
		void FillColor( DWORD color = 0, RECT* pFillRect = NULL, UINT nLevel = 0 );

		//��������
		virtual void LockRect( void** ppBuf, UINT* pPitch, RECT* pLockRect = NULL,
			UINT nLevel = 0, bool bDiscardLock = false ) = 0;

		//��������
		virtual void UnlockRect( UINT nLevel = 0 ) = 0;
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Texture* >	TextureList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
