/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9VolumeTexture
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	D3D9 ��ά������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	// D3D9 ������
	class FK_DLL D3D9VolumeTexture : public VolumeTexture, public D3D9BaseTexture
	{
	public:
		D3D9BaseTexture		mBaseTexture;

	public:
		D3D9VolumeTexture( UINT nWidth, UINT nHeight, UINT nDepth,
			PixelFormat ePixelFormat, UINT nNumLevel, TextureUsage Type );

		//��������
		void LockBox( LockBox3* pLocked, Box3* pLockBox, UINT nLevel, bool bDiscardLock );

		//��������
		void UnlockBox( UINT nLevel = 0 );

		//�Զ����ɶ༶����ӳ��
		void GenerateMipSubLevels( TextureFilterType eFilterType = TFT_LINEAR );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
