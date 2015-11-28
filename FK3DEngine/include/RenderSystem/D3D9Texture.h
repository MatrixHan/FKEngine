/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9Texture
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
	// D3D9 ��ά������
	class FK_DLL D3D9Texture : public Texture
	{
	public:
		D3D9BaseTexture		mBaseTexture;

	public:
		D3D9Texture( UINT nWidth, UINT nHeight, PixelFormat ePixelFormat, UINT nNumLevel, TextureUsage Type );

		//��������
		void LockRect( void** ppBuf, UINT* pPitch, RECT* pLockRect, UINT nLevel, bool bDiscardLock );

		//��������
		void UnlockRect( UINT nLevel = 0 );

		//�Զ����ɶ༶����ӳ��
		void GenerateMipSubLevels( TextureFilterType eFilterType = TFT_LINEAR );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
