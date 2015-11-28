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
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderWrapper/RenderWrapperInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��������
	Sprite::Sprite( SpriteSet* pSpriteSet, float fLeft, float fTop, float fWidth, float fHeight,
		ZOrderType eZType, OverlaySurface* pZRefOverlay, TextureFilterType eFilterType,
		UV4* pUV, DWORD color )
		: OverlaySurface	( eZType, pZRefOverlay, eFilterType )
		, mpSpriteSet		(pSpriteSet)
		, mpUVASprite		(NULL)
		, mfWidth			(fWidth)
		, mfHeight			(fHeight)
	{
		//���ö�������
		OverlayVertex* pVer = mpVertexData;

		float Right = fLeft + mfWidth;
		float Bottom = fTop + mfHeight;

		//����
		pVer->x = fLeft;	pVer->y = Bottom;	pVer->z = 1.0f;
		pVer->u = pUV->u1;	pVer->v = pUV->v2;	pVer->color = color;	++pVer;

		//����
		pVer->x = fLeft;	pVer->y = fTop;		pVer->z = 1.0f;
		pVer->u = pUV->u1;	pVer->v = pUV->v1;	pVer->color = color;	++pVer;

		//����
		pVer->x = Right;	pVer->y = fTop;		pVer->z = 1.0f;
		pVer->u = pUV->u2;	pVer->v = pUV->v1;	pVer->color = color;	++pVer;

		//����
		pVer->x = Right;	pVer->y = Bottom;	pVer->z = 1.0f;
		pVer->u = pUV->u2;	pVer->v = pUV->v2;	pVer->color = color;

		mNumVertex = 4;
		mpVertexPtr = mpVertexData;

		//���Ӷ������
		OverlayManager::mpSingleton->mNumRenderVer += 4;
	}
	//--------------------------------------------------------------------------------------------------------------
	Sprite::Sprite( SpriteSet* pSpriteSet, float fLeft, float fTop, float fWidth, float fHeight,
		ZOrderType eZType, OverlaySurface* pZRefOverlay, TextureFilterType eFilterType,
		UVAnimation* pUVAnimation, DWORD color )
		: OverlaySurface	( eZType, pZRefOverlay, eFilterType )
		, mpSpriteSet		(pSpriteSet)
		, mfWidth			(fWidth)
		, mfHeight			(fHeight)
	{
		//���� UV ����������
		mpUVASprite = new UVASprite( this, pUVAnimation );
		OverlayManager::mpSingleton->_AddUVASpriteToList( mpUVASprite );

		const UV4* pUV = mpUVASprite->GetCurrentUV();

		//���ö�������
		OverlayVertex* pVer = mpVertexData;

		float Right = fLeft + mfWidth;
		float Bottom = fTop + mfHeight;

		//����
		pVer->x = fLeft;	pVer->y = Bottom;	pVer->z = 1.0f;
		pVer->u = pUV->u1;	pVer->v = pUV->v2;	pVer->color = color;	++pVer;

		//����
		pVer->x = fLeft;	pVer->y = fTop;		pVer->z = 1.0f;
		pVer->u = pUV->u1;	pVer->v = pUV->v1;	pVer->color = color;	++pVer;

		//����
		pVer->x = Right;	pVer->y = fTop;		pVer->z = 1.0f;
		pVer->u = pUV->u2;	pVer->v = pUV->v1;	pVer->color = color;	++pVer;

		//����
		pVer->x = Right;	pVer->y = Bottom;	pVer->z = 1.0f;
		pVer->u = pUV->u2;	pVer->v = pUV->v2;	pVer->color = color;

		mNumVertex = 4;
		mpVertexPtr = mpVertexData;

		//���Ӷ������
		OverlayManager::mpSingleton->mNumRenderVer += 4;
	}
	//--------------------------------------------------------------------------------------------------------------
	Sprite::~Sprite()
	{
		//ɾ�� UV ����������
		if( mpUVASprite != NULL )
		{
			OverlayManager::mpSingleton->_DelUVASpriteFromList( mpUVASprite );
			delete mpUVASprite;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���þ�������ľ��鼯��ɾ��
	void Sprite::DeleteFromSpriteSet()
	{
		mpSpriteSet->DeleteSprite( this );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���þ��� UV ����
	void FKFastcall FKFastcall Sprite::SetSpriteUV( const UV4* pUV )
	{
		//���ö��� UV ����
		OverlayVertex* pVer = mpVertexData;

		pVer->u = pUV->u1;	pVer->v = pUV->v2;	++pVer;	//����
		pVer->u = pUV->u1;	pVer->v = pUV->v1;	++pVer;	//����
		pVer->u = pUV->u2;	pVer->v = pUV->v1;	++pVer;	//����
		pVer->u = pUV->u2;	pVer->v = pUV->v2;			//����
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ͼ��λ��
	void FKFastcall Sprite::SetLocation( float fLeft, float fTop )
	{
		//���ö�������
		OverlayVertex* pVer = mpVertexData;

		float Right = fLeft + mfWidth;
		float Bottom = fTop + mfHeight;
		
		pVer->x = fLeft;	pVer->y = Bottom;	++pVer;	//����
		pVer->x = fLeft;	pVer->y = fTop;		++pVer;	//����
		pVer->x = Right;	pVer->y = fTop;		++pVer;	//����
		pVer->x = Right;	pVer->y = Bottom;			//����
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ƶ�����λ��
	void FKFastcall Sprite::MoveLocation( float fX, float fY )
	{
		//���ö�������
		OverlayVertex* pVer = mpVertexData;

		pVer->x += fX;	pVer->y += fY;	++pVer;	//����
		pVer->x += fX;	pVer->y += fY;	++pVer;	//����
		pVer->x += fX;	pVer->y += fY;	++pVer;	//����
		pVer->x += fX;	pVer->y += fY;			//����
	}
	//--------------------------------------------------------------------------------------------------------------
	//���þ���ߴ�
	void FKFastcall Sprite::SetSize( float fWidth, float fHeight )
	{
		//���ö�������
		OverlayVertex* pVer = mpVertexData;

		mfWidth = fWidth;
		mfHeight = fHeight;

		float fRight = pVer[0].x + fWidth;
		float fBottom = pVer[1].y + fHeight;

		pVer[2].x = fRight;
		pVer[3].x = fRight;
		pVer[0].y = fBottom;
		pVer[3].y = fBottom;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ͼ����ɫ
	void FKFastcall Sprite::SetColor( DWORD color )
	{
		//���ö�������
		OverlayVertex* pVer = mpVertexData;

		pVer->color = color;	++pVer;	//����
		pVer->color = color;	++pVer;	//����
		pVer->color = color;	++pVer;	//����
		pVer->color = color;			//����
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƽ��ͼ�񶥵�
	void FKFastcall Sprite::_ProcessVertex()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦƽ��ͼ��
	void FKFastcall Sprite::_RenderOverlay()
	{
		//���������������
		RenderSystem::mpSingleton->_SetTextureFilter( ST_MAGFILTER, mFilterType, 0 );
		RenderSystem::mpSingleton->_SetTextureFilter( ST_MINFILTER, mFilterType, 0 );

		//��������
		RenderSystem::mpSingleton->_SetTexture( mpSpriteSet->mpTexture, 0 );

		//����ͼԪ
		RenderSystem::mpSingleton->_RenderVertex( PT_TRIANGLE_FAN, mVertexOffset, 2 );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
