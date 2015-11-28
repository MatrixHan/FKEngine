/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiSpriteUVA
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/UISystem/UISystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	GuiSpriteUVA::GuiSpriteUVA( ZOrderType eZType, OverlaySurface* pZRefOverlay, GuiDialog* pDialog,
		GuiLoca* pLoca, GuiClient* pClient, SpriteSet* pSpriteSet, UVAnimation* pUVA )
		: GuiBase		( pLoca, pClient )
		, mpSpriteSet	(NULL)
		, mpSprite		(NULL)
	{
		//������ťͼ����
		mpSprite = pSpriteSet->CreateUVASprite( pLoca->X, pLoca->Y, pLoca->Width, pLoca->Height,
			eZType, pZRefOverlay, pUVA );
		mpSpriteSet = pSpriteSet;
	}
	//--------------------------------------------------------------------------------------------------------------
	GuiSpriteUVA::~GuiSpriteUVA()
	{
		//ɾ����ťͼ����
		if( mpSpriteSet != NULL && mpSprite != NULL )
			mpSpriteSet->DeleteSprite( mpSprite );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʾ/���ؿؼ�
	void FKFastcall GuiSpriteUVA::Show( bool bShow )
	{
		mpSprite->SetVisable( bShow );

		mbVisable = bShow;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����λ��
	void FKFastcall GuiSpriteUVA::SetPos( long nX, long nY )
	{
		mLoca.X = nX;
		mLoca.Y = nY;

		mpSprite->SetLocation( nX, nY );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� Z ˳��
	void FKFastcall GuiSpriteUVA::SetZOrder( ZOrderType eZType, OverlaySurface* pZRefOverlay )
	{
		mpSprite->SetZOrder( eZType, pZRefOverlay );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ Z ˳��
	OverlaySurface* FKFastcall GuiSpriteUVA::GetZOrder( ZOrderType eZType )
	{
		return (OverlaySurface*)mpSprite;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ָ�� UV ������
	void FKFastcall GuiSpriteUVA::PlaySegment( int nPlaySegment, int nNextSegment, bool bReverse )
	{
		mpSprite->mpUVASprite->PlaySegment( nPlaySegment, nNextSegment, bReverse );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���û������������Ϣ
	LONG_PTR GuiSpriteUVA::SendMsg( LONG_PTR nGM, LONG_PTR nGMA, LONG_PTR nGMB )
	{
		switch (nGM)
		{
			case GM_Show:
				Show( ( nGMA == 1 ) ? true : false );
				return TRUE;
			case GM_SetPos:
				SetPos( nGMA, nGMB );
				return TRUE;
			case GM_MovePos:
				SetPos( mLoca.X + nGMA, mLoca.Y + nGMB );
				return TRUE;
			case GM_SetZOrder:
				SetZOrder( (ZOrderType)nGMA, (OverlaySurface*)nGMB );
				return TRUE;
			case GM_GetZOrder:
				return (LONG_PTR)GetZOrder( (ZOrderType)nGMA );
		}

		return FALSE;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

