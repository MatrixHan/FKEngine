/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiSprite
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
	GuiSprite::GuiSprite( GuiDialog* pDialog, GuiLoca* pLoca, GuiClient* pClient, SpriteSet* pSpriteSet )
		: GuiBase		( pLoca, pClient, pDialog )
		, mpSpriteSet	(pSpriteSet)
		, mpSprite		(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	GuiSprite::~GuiSprite()
	{
		//ɾ����ťͼ����
		if( mpSpriteSet != NULL && mpSprite != NULL )
			mpSpriteSet->DeleteSprite( mpSprite );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����/�رտؼ�
	void FKFastcall GuiSprite::Enable( bool bEnable )
	{
		mbEnable = bEnable;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʾ/���ؿؼ�
	void FKFastcall GuiSprite::Show( bool bShow )
	{
		mpSprite->SetVisable( bShow );

		mbVisable = bShow;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����λ��
	void FKFastcall GuiSprite::SetPos( long nX, long nY )
	{
		mLoca.X = nX;
		mLoca.Y = nY;

		mpSprite->SetLocation( nX, nY );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� Z ˳��
	void FKFastcall GuiSprite::SetZOrder( ZOrderType eZType, OverlaySurface* pZRefOverlay )
	{
		mpSprite->SetZOrder( eZType, pZRefOverlay );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ Z ˳��
	OverlaySurface* FKFastcall GuiSprite::GetZOrder( ZOrderType eZType )
	{
		return (OverlaySurface*)mpSprite;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���û������������Ϣ
	LONG_PTR GuiSprite::SendMsg( LONG_PTR nGM, LONG_PTR nGMA, LONG_PTR nGMB )
	{
		switch (nGM)
		{
			case GM_Enable:
				Enable( ( nGMA == 1 ) ? true : false );
				return TRUE;
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

