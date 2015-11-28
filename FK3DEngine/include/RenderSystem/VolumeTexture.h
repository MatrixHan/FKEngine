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

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��ά����
	class FK_DLL VolumeTexture : public BaseTexture
	{
	public:
		UINT		mWidth;			//������
		UINT		mHeight;		//����߶�
		UINT		mDepth;			//�������

	public:
		VolumeTexture();
		VolumeTexture( UINT nWidth, UINT nHeight, UINT nDepth,
			PixelFormat ePixelFormat, UINT nNumLevel, TextureUsage Type );
		virtual ~VolumeTexture() = 0;

		//��ȡ����ʵ�ʳߴ�
		FKInline void GetTextureSize( UINT& nWidth, UINT& nHeight, UINT& nDepth );

		//���ָ����������Ϊĳ��ɫ
		void FillColor( DWORD color = 0, Box3* pFillBox = NULL, UINT nLevel = 0 );

		//��������
		virtual void LockBox( LockBox3* pLocked, Box3* pLockBox = NULL, UINT nLevel = 0, bool bDiscardLock = false ) = 0;

		//��������
		virtual void UnlockBox( UINT nLevel = 0 ) = 0;
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< VolumeTexture* >		VolumeTextureList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
