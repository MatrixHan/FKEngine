/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SpriteSet
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	���鼯��
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//���鼯��
	// һ�����鼯����������ʹ��ͬһ����������о���
	class FK_DLL SpriteSet
	{
	public:
		Texture*			mpTexture;		//���鼯����
		TextureFilterType	mFilterType;	//�����������

		SpriteList			mSpriteList;	//���ڸþ��鼯�ľ����б�

	public:
		SpriteSet( UINT nWidth, UINT nHeight, PixelFormat ePixelFormat,
			UINT InitSpriteNum, UINT AddSpriteNum, TextureFilterType eFilter = TFT_LINEAR );
		SpriteSet( FileObject* pFile, const char* szName, PixelFormat ePixelFormat,
			UINT InitSpriteNum, UINT AddSpriteNum, TextureFilterType eFilter = TFT_LINEAR );
		~SpriteSet();

		//����һ�����ڸþ��鼯�ľ�̬����
		Sprite* CreateSprite( float fLeft, float fTop, float fWidth, float fHeight,
			ZOrderType eZType, OverlaySurface* pZRefOverlay, UV4* pUV, DWORD color = 0xFFFFFFFF );

		//����һ�����ڸþ��鼯�Ķ�������
		Sprite* CreateUVASprite( float fLeft, float fTop, float fWidth, float fHeight,
			ZOrderType eZType, OverlaySurface* pZRefOverlay, UVAnimation* pUVAnimation, DWORD color = 0xFFFFFFFF );

		//ɾ��ָ������
		void DeleteSprite( Sprite* pSprite );

		//ɾ�����о���
		void DeleteAllSprites();

		//�������о�����ʾ״̬
		void SetAllVisable( bool bVisable );
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< SpriteSet*>	SpriteSetList;
	//--------------------------------------------------------------------------------------------------------------
};

//==================================================================================================================
