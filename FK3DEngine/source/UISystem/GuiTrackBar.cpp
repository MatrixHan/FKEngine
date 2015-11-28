/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiTrackBar
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
	GuiTrackBar::GuiTrackBar( ZOrderType eZType, OverlaySurface* pZRefOverlay, GuiDialog* pDialog, Param* pParam )
		: GuiBase		( NULL, NULL )
		, mpSpriteSet	(pParam->pSpriteSet)
		, mProgWidth	(pParam->nProgWidth)
		, mProgHeight	(pParam->nProgHeight)
		, mBkgY			(pParam->nBkgY)
		, mSliderY		(pParam->nSliderY)
		, mSliderMinX	(pParam->nSliderMinX)
		, mSliderMaxX	(pParam->nSliderMaxX)
		, mSliderWidth	(pParam->nSliderWidth)
		, mSliderHeight	(pParam->nSliderHeight)
		, mRange		(pParam->nRange)
		, mValue		(pParam->nValue)
		, mbDragSlider	(false)
		, mbSliderFocus	(false)
		, mFnEvent		(pParam->fnEvent)
	{
		//���㻬�����ͻ���
		mLoca.X = pParam->nX;
		mLoca.Y = pParam->nY;
		mLoca.Width = pParam->nBkgWidth;
		mLoca.Height = max( pParam->nBkgHeight + mBkgY, mSliderHeight + mSliderY );

		mClient.SetClient( 0, 0, mLoca.Width, mLoca.Height );

		//���㻬��ֵ�ٷֱ�
		mPercent = (float)mValue / (float)mRange;
		mDragWidth = mSliderMaxX - mSliderMinX;

		//����������ͻ����û���
		int nProgAbsTop = mBkgY + pParam->nProgTop;
		mSliderX = mSliderMinX + mDragWidth * mPercent;

		mProgressClient.SetClient( pParam->nProgLeft, nProgAbsTop, pParam->nProgLeft + mProgWidth,
			nProgAbsTop + mProgHeight );
		mSliderClient.SetClient( mSliderX, mSliderY, mSliderX + mSliderWidth, mSliderY + mSliderHeight );

		//���㻬���������� UV
		float fTexWidth = (float)mpSpriteSet->mpTexture->mWidth;
		float fTexHeight = (float)mpSpriteSet->mpTexture->mHeight;
		float fSliderWidth = (float)pParam->nBkgWidth;
		float fProgWidth = (float)FloorToInt( (float)mProgWidth * mPercent );

		UV4 sBkgUV;
		sBkgUV.u1 = 0.0f;
		sBkgUV.u2 = (float)pParam->nBkgWidth / fTexWidth;
		sBkgUV.v1 = 0.0f;
		sBkgUV.v2 = (float)pParam->nBkgHeight / fTexHeight;

		mProgressUV.u1 = 0.0f;
		mProgressUV.u2 = fProgWidth / fTexWidth;
		mProgressUV.v1 = sBkgUV.v2;
		mProgressUV.v2 = sBkgUV.v2 + (float)mProgHeight / fTexHeight;

		mNormalUV.u1 = 0.0f;
		mNormalUV.u2 = (float)mSliderWidth / fTexWidth;
		mNormalUV.v1 = mProgressUV.v2;
		mNormalUV.v2 = mProgressUV.v2 + (float)mSliderHeight / fTexHeight;

		mHighLightUV.u1 = mNormalUV.u2;
		mHighLightUV.u2 = mNormalUV.u2 + mNormalUV.u2;
		mHighLightUV.v1 = mNormalUV.v1;
		mHighLightUV.v2 = mNormalUV.v2;

		//���������־���
		mpBackground = mpSpriteSet->CreateSprite( mLoca.X, mLoca.Y + mBkgY, pParam->nBkgWidth, pParam->nBkgHeight,
			eZType, pZRefOverlay, &sBkgUV );

		mpProgress = mpSpriteSet->CreateSprite( mLoca.X + pParam->nProgLeft, mLoca.Y + nProgAbsTop,
			fProgWidth, mProgHeight, ZOT_Upon, mpBackground, &mProgressUV );

		mpSlider = mpSpriteSet->CreateSprite( mLoca.X + mSliderX, mLoca.Y + mSliderY,
			mSliderWidth, mSliderHeight, ZOT_Upon, mpProgress, &mNormalUV );
	}
	//--------------------------------------------------------------------------------------------------------------
	GuiTrackBar::~GuiTrackBar()
	{
		mpSpriteSet->DeleteSprite( mpBackground );
		mpSpriteSet->DeleteSprite( mpProgress );
		mpSpriteSet->DeleteSprite( mpSlider );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����/�رտؼ�
	void FKFastcall GuiTrackBar::Enable( bool bEnable )
	{
		mbEnable = bEnable;

		DWORD dwColor = bEnable ? 0xFFFFFFFF : 0x80FFFFFF;

		mpBackground->SetColor( dwColor );
		mpProgress->SetColor( dwColor );
		mpSlider->SetColor( dwColor );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʾ/���ؿؼ�
	void FKFastcall GuiTrackBar::Show( bool bShow )
	{
		mbVisable = bShow;

		mpBackground->SetVisable( bShow );
		mpProgress->SetVisable( bShow );
		mpSlider->SetVisable( bShow );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����λ��
	void FKFastcall GuiTrackBar::SetPos( long nX, long nY )
	{
		int nOffsetX = nX - mLoca.X;
		int nOffsetY = nY - mLoca.Y;

		mpBackground->MoveLocation( nOffsetX, nOffsetY );
		mpProgress->MoveLocation( nOffsetX, nOffsetY );
		mpSlider->MoveLocation( nOffsetX, nOffsetY );

		mLoca.X = nX;
		mLoca.Y = nY;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� Z ˳��
	void FKFastcall GuiTrackBar::SetZOrder( ZOrderType eZType, OverlaySurface* pZRefOverlay )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ Z ˳��
	OverlaySurface* FKFastcall GuiTrackBar::GetZOrder( ZOrderType eZType )
	{
		switch (eZType)
		{
		case ZOT_Top:		return mpSlider;
		case ZOT_Bottom:	return mpBackground;
		}

		return NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���/ʧȥ����
	void FKFastcall GuiTrackBar::Focus( bool bHasFocus )
	{
		mbFocus = bHasFocus;

		//���ʧȥ����
		if( !bHasFocus )
		{
			mpSlider->SetSpriteUV( &mNormalUV );
			mbSliderFocus = false;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƶ�
	void FKFastcall GuiTrackBar::MouseMove( InputSystem* pInputSystem )
	{
		//ת��Ϊ�ؼ�����ϵ
		int x = pInputSystem->mMouseX - mLoca.X;
		int y = pInputSystem->mMouseY - mLoca.Y;

		//������齹��䶯
		bool bSliderFocus = mSliderClient.IsOnClient( x, y );
		if( bSliderFocus != mbSliderFocus )
		{
			mpSlider->SetSpriteUV( bSliderFocus ? &mHighLightUV : &mNormalUV );
			mbSliderFocus = bSliderFocus;
		}

		//��������϶�����
		if( mbDragSlider )
		{
			//��������ƶ�����
			int nRelX = pInputSystem->mMouseRelX;
			int nFixRelX = 0;
			mSliderX += nRelX;

			if( mSliderX < mSliderMinX )
			{
				nFixRelX = mSliderMinX - mSliderX;
				mSliderX = mSliderMinX;
			}
			else if( mSliderX > mSliderMaxX )
			{
				nFixRelX = mSliderMaxX - mSliderX;
				mSliderX = mSliderMaxX;
			}

			pInputSystem->mMouseRelX += nFixRelX;
			pInputSystem->mMouseX += nFixRelX;
			pInputSystem->mMouseY -= pInputSystem->mMouseRelY;
			pInputSystem->mMouseRelY = 0;

			//���㻬��ֵ�仯
			int nOldValue = mValue;
			mPercent = (float)( mSliderX - mSliderMinX ) / mDragWidth;
			mValue = FloorToInt( mPercent * (float)mRange );

			//���㻬���û���
			mSliderClient.SetClient( mSliderX, mSliderY, mSliderX + mSliderWidth, mSliderY + mSliderHeight );

			//�ı们��λ��
			mpSlider->SetLocation( mLoca.X + mSliderX, mLoca.Y + mSliderY );

			//�ı��������ʾ����
			float fProgWidth = (float)FloorToInt( (float)mProgWidth * mPercent );
			mpProgress->SetSize( fProgWidth, mProgHeight );

			mProgressUV.u2 = fProgWidth / (float)mpSpriteSet->mpTexture->mWidth;
			mpProgress->SetSpriteUV( &mProgressUV );

			//�������ֵ�����仯����֡�¼�
			if( nOldValue != mValue )
				_ActiveEvent();
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������
	void FKFastcall GuiTrackBar::LDown( InputSystem* pInputSystem )
	{
		//ת��Ϊ�ؼ�����ϵ
		int x = pInputSystem->mMouseX - mLoca.X;
		int y = pInputSystem->mMouseY - mLoca.Y;

		//������ڻ����ϰ���
		if( mSliderClient.IsOnClient( x, y ) )
		{
			mbDragSlider = true;

			//��������
			GuiManager::mpSingleton->LockFocus( this );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ͷ�
	void FKFastcall GuiTrackBar::LUp( InputSystem* pInputSystem )
	{
		mbDragSlider = false;

		//��������
		GuiManager::mpSingleton->UnlockFocus();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���û������������Ϣ
	LONG_PTR GuiTrackBar::SendMsg( LONG_PTR nGM, LONG_PTR nGMA, LONG_PTR nGMB )
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
			case GM_MouseMove:
				MouseMove( (InputSystem*)nGMA );
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
	//���û������¼�����
	void FKFastcall GuiTrackBar::SetEvent( FnFrameEvent fnEvent )
	{
		mFnEvent = fnEvent;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���û���ֵ
	void FKFastcall GuiTrackBar::SetValue( int nValue )
	{
		//���㻬��ֵ�ٷֱ�
		int nOldValue = nValue;
		mValue = nValue;
		mPercent = (float)mValue / (float)mRange;

		//���㻬���û���
		mSliderX = mSliderMinX + mDragWidth * mPercent;
		mSliderClient.SetClient( mSliderX, mSliderY, mSliderX + mSliderWidth, mSliderY + mSliderHeight );

		//�ı们��λ��
		mpSlider->SetLocation( mLoca.X + mSliderX, mLoca.Y + mSliderY );

		//�ı��������ʾ����
		float fProgWidth = (float)FloorToInt( (float)mProgWidth * mPercent );
		mpProgress->SetSize( fProgWidth, mProgHeight );

		mProgressUV.u2 = fProgWidth / (float)mpSpriteSet->mpTexture->mWidth;
		mpProgress->SetSpriteUV( &mProgressUV );

		//�������ֵ�����仯����֡�¼�
		if( nOldValue != mValue )
			_ActiveEvent();
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������֡�¼�
	void FKFastcall GuiTrackBar::_ActiveEvent()
	{
		//���������¼�����֡�¼��б�
		if( mFnEvent != NULL && Root::mpSingleton->mpFrameListener != NULL )
			Root::mpSingleton->mpFrameListener->AddFrameEvent( mFnEvent, (LONG_PTR)this );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

