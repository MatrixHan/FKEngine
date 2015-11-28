/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9CubeTexture
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	D3D9 ����������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	// D3D9 ����������
	class FK_DLL D3D9CubeTexture : public CubeTexture, public D3D9BaseTexture
	{
	public:
		D3D9BaseTexture		mBaseTexture;

	public:
		D3D9CubeTexture( UINT nEdgeLength, PixelFormat ePixelFormat, UINT nNumLevel, TextureUsage Type );

		//��������
		void LockRect( CubeFace eFace, void** ppBuf, UINT* pPitch, RECT* pLockRect, UINT nLevel, bool bDiscardLock );

		//��������
		void UnlockRect( CubeFace eFace, UINT nLevel = 0 );

		//�Զ����ɶ༶����ӳ��
		void GenerateMipSubLevels( TextureFilterType eFilterType = TFT_LINEAR );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
