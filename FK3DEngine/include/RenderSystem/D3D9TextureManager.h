/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9TextureManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	D3D9 ���������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	// D3D9 ���������
	class FK_DLL D3D9TextureManager : public TextureManager
	{
	public:
		D3D9TextureManager();

		//������ά����
		Texture* CreateTexture( UINT nWidth, UINT nHeight, PixelFormat ePixelFormat,
			TextureUsage Type, int nNumLevels );

		//������������
		CubeTexture* CreateCubeTexture( UINT nEdgeLength, PixelFormat ePixelFormat,
			TextureUsage Type, int nNumLevels );

		//������ά����
		VolumeTexture* CreateVolumeTexture( UINT nWidth, UINT nHeight, UINT nDepth,
			PixelFormat ePixelFormat, TextureUsage Type, int nNumLevels );

		//��������ߴ������ֵ
		void SetMaxTextureSize( UINT nWidth, UINT nHeight );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
