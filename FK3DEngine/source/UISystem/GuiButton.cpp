/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiButton
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
	GuiButton::GuiButton( ZOrderType eZType, OverlaySurface* pZRefOverlay, GuiDialog* pDialog, Param* pParam )
		: GuiSprite		( pDialog, &pParam->sLoca, &pParam->sClient, pParam->pSpriteSet )
		, mpUV			(pParam->pUV)
		, mFnEvent		(pParam->fnEvent)
		, mbPressed		(false)
	{
		//��������
		mpSprite = mpSpriteSet->CreateSprite( mLoca.X, mLoca.Y, mLoca.Width, mLoca.Height,
			eZType, pZRefOverlay, mpUV + mnNormalStatus );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���/ʧȥ����
	void FKFastcall GuiButton::Focus( bool bHasFocus )
	{
		mbFocus = bHasFocus;

		//�����ý���
		if( bHasFocus )
		{
			//�л�Ϊ������ʾ״̬
			mpSprite->SetSpriteUV( mpUV + mnFocusStatus );
		}
		//���ʧȥ����
		else
		{
			//�л�Ϊ��ͨ��ʾ״̬
			mpSprite->SetSpriteUV( mpUV + mnNormalStatus );

			//���ð�ť��δ�����¹�
			mbPressed = false;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������
	void FKFastcall GuiButton::LDown( InputSystem* pInputSystem )
	{
		//�л�Ϊ������ʾ״̬
		mpSprite->SetSpriteUV( mpUV + mnPressStatus );

		//���ð�ť�ѱ����¹�
		mbPressed = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ͷ�
	void FKFastcall GuiButton::LUp( InputSystem* pInputSystem )
	{
		//�л�Ϊ��ͨ��ʾ״̬
		mpSprite->SetSpriteUV( mpUV + mnFocusStatus );

		//�����ť�ѱ����¹�
		if( mbPressed )
		{
			//����ť�¼�����֡�¼��б�
			if( mFnEvent != NULL && Root::mpSingleton->mpFrameListener != NULL )
				Root::mpSingleton->mpFrameListener->AddFrameEvent( mFnEvent, (LONG_PTR)this );

			mbPressed = false;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ð�ť�¼�����
	void FKFastcall GuiButton::SetEvent( FnFrameEvent fnEvent )
	{
		mFnEvent = fnEvent;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���û������������Ϣ
	LONG_PTR GuiButton::SendMsg( LONG_PTR nGM, LONG_PTR nGMA, LONG_PTR nGMB )
	{
		switch (nGM)
		{
			case GM_Enable:
				Enable( ( nGMA == 1 ) ? true : false );
				return TRUE;
			case GM_Show:
				Show( ( nGMA == 1 ) ? true : false );
				return TRUE;
			case GM_Focus:
				Focus( ( nGMA == 1 ) ? true : false );
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
			case GM_LDown:
				LDown( (InputSystem*)nGMA );
				return TRUE;
			case GM_LUp:
				LUp( (InputSystem*)nGMA );
				return TRUE;
		}

		return FALSE;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

