/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiCheckBox
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
	GuiCheckBox::GuiCheckBox( ZOrderType eZType, OverlaySurface* pZRefOverlay, GuiDialog* pDialog, Param* pParam )
		: GuiSprite		( pDialog, &pParam->sLoca, &pParam->sClient, pParam->pSpriteSet )
		, mbChecked		(false)
		, mFnEvent		(pParam->fnEvent)
	{
		Texture* pSpriteTex = pParam->pSpriteSet->mpTexture;
		float fWidth = (float)mLoca.Width / (float)pSpriteTex->mWidth;
		float fHeight = (float)mLoca.Height / (float)pSpriteTex->mHeight;

		//���㸴ѡ�� UV
		mNormalUV.u1 = 0.0f;
		mNormalUV.u2 = fWidth;
		mNormalUV.v1 = 0.0f;
		mNormalUV.v2 = fHeight;

		mNormalLightUV.u1 = 0.0f;
		mNormalLightUV.u2 = fWidth;
		mNormalLightUV.v1 = fHeight;
		mNormalLightUV.v2 = fHeight + fHeight;

		mCheckedUV.u1 = fWidth;
		mCheckedUV.u2 = fWidth + fWidth;
		mCheckedUV.v1 = 0.0f;
		mCheckedUV.v2 = fHeight;

		mCheckedLightUV.u1 = fWidth;
		mCheckedLightUV.u2 = fWidth + fWidth;
		mCheckedLightUV.v1 = fHeight;
		mCheckedLightUV.v2 = fHeight + fHeight;

		//��������
		mpSprite = mpSpriteSet->CreateSprite( mLoca.X, mLoca.Y, mLoca.Width, mLoca.Height,
			eZType, pZRefOverlay, &mNormalUV );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���/ʧȥ����
	void FKFastcall GuiCheckBox::Focus( bool bHasFocus )
	{
		mbFocus = bHasFocus;

		//�����ý���
		if( bHasFocus )
		{
			//�л�Ϊ�߹���ʾ״̬
			mpSprite->SetSpriteUV( mbChecked ? &mCheckedLightUV : &mNormalLightUV );
		}
		//���ʧȥ����
		else
		{
			//�л�Ϊ��ͨ��ʾ״̬
			mpSprite->SetSpriteUV( mbChecked ? &mCheckedUV : &mNormalUV );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������
	void FKFastcall GuiCheckBox::LDown( InputSystem* pInputSystem )
	{
		//�л���ѡ״̬
		mbChecked = !mbChecked;

		//����趨��ѡ
		if( mbChecked )
		{
			//�л�Ϊ��ѡ��ʾ״̬
			mpSprite->SetSpriteUV( mbFocus ? &mCheckedLightUV : &mCheckedUV );
		}
		//���ȡ������ѡ
		else
		{
			//�л�Ϊ��ͨ��ʾ״̬
			mpSprite->SetSpriteUV( mbFocus ? &mNormalLightUV : &mNormalUV );
		}

		//����ѡ���¼�����֡�¼��б�
		if( mFnEvent != NULL && Root::mpSingleton->mpFrameListener != NULL )
			Root::mpSingleton->mpFrameListener->AddFrameEvent( mFnEvent, (LONG_PTR)this );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ø�ѡ���¼�����
	void FKFastcall GuiCheckBox::SetEvent( FnFrameEvent fnEvent )
	{
		mFnEvent = fnEvent;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���û������������Ϣ
	LONG_PTR GuiCheckBox::SendMsg( LONG_PTR nGM, LONG_PTR nGMA, LONG_PTR nGMB )
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
		}

		return FALSE;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

