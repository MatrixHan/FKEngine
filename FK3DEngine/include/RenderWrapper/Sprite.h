/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Sprite
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class SpriteSet;
	class UVASprite;
	struct UVAnimation;
	//--------------------------------------------------------------------------------------------------------------
	//������
	class FK_DLL Sprite : public OverlaySurface
	{
	public:
		float				mfWidth;		//��Ⱦ���
		float				mfHeight;		//��Ⱦ�߶�

		SpriteSet*			mpSpriteSet;	//�þ����������ľ��鼯ָ��
		OverlayVertex		mpVertexData[4];//ƽ��ͼ�񶥵����ݣ��������У�

		UVASprite*			mpUVASprite;	//���� UV ����������

	public:
		Sprite( SpriteSet* pSpriteSet, float fLeft, float fTop, float fWidth, float fHeight,
			ZOrderType eZType, OverlaySurface* pZRefOverlay, TextureFilterType eFilterType,
			UV4* pUV, DWORD color );
		Sprite( SpriteSet* pSpriteSet, float fLeft, float fTop, float fWidth, float fHeight,
			ZOrderType eZType, OverlaySurface* pZRefOverlay, TextureFilterType eFilterType,
			UVAnimation* pUVAnimation, DWORD color );
		~Sprite();

		//���þ�������ľ��鼯��ɾ��
		void DeleteFromSpriteSet();

		//���þ��� UV ����
		void FKFastcall SetSpriteUV( const UV4* pUV );

		//���þ���λ��
		void FKFastcall SetLocation( float fLeft, float fTop );

		//�ƶ�����λ��
		void FKFastcall MoveLocation( float fX, float fY );

		//���þ���ߴ�
		void FKFastcall SetSize( float fWidth, float fHeight );

		//���þ�����ɫ
		void FKFastcall SetColor( DWORD color );

	protected:
		//����ƽ��ͼ�񶥵�
		void FKFastcall _ProcessVertex();

		//��Ⱦƽ��ͼ��
		void FKFastcall _RenderOverlay();
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Sprite* >	SpriteList;
	//--------------------------------------------------------------------------------------------------------------
};

//==================================================================================================================
