/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiComboBox
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
	GuiComboBox::GuiComboBox( ZOrderType eZType, OverlaySurface* pZRefOverlay, GuiDialog* pDialog, Param* pParam )
		: GuiBase		( NULL, NULL, pDialog )
		, mpSpriteSet	(pParam->pSpriteSet)
		, mpTextFont	(pParam->pFontFace)
		, mX			(pParam->nX)
		, mY			(pParam->nY)
		, mWidth		(pParam->nWidth)
		, mChoosenHeight(pParam->nChoosenHeight)
		, mItemHeight	(pParam->nItemHeight)
		, mBoarderHeight(pParam->nBoarderHeight)
		, mTextLeft		(pParam->nTextLeft)
		, mTextTop		(pParam->nTextTop)
		, mChoosenClient(pParam->sChoosenClient)
		, mListClient	(pParam->sChoosenClient)
		, mbChoosenFocus(false)
		, mbShowList	(false)
		, mnFocusItem	(0)
	{
		//������Ͽ��û���
		mLoca.X = pParam->nX;
		mLoca.Y = pParam->nY;
		mLoca.Width = pParam->nWidth;
		mLoca.Height = pParam->nChoosenHeight;

		mClient.SetClient( 0, 0, mLoca.Width, mLoca.Height );

		//������Ͽ�����־��� UV
		float fTexHeight = (float)mpSpriteSet->mpTexture->mHeight;
		float fComboWidth = (float)mWidth / (float)mpSpriteSet->mpTexture->mWidth;
		float fChoosenHeight = (float)mChoosenHeight / fTexHeight;
		float fItemHeight = (float)mItemHeight / fTexHeight;
		float fBoarderHeight = (float)mBoarderHeight / fTexHeight;

		mNormalUV.u1 = 0.0f;
		mNormalUV.u2 = fComboWidth;
		mNormalUV.v1 = 0.0f;
		mNormalUV.v2 = fChoosenHeight;

		mHighLightUV.u1 = 0.0f;
		mHighLightUV.u2 = fComboWidth;
		mHighLightUV.v1 = mNormalUV.v2;
		mHighLightUV.v2 = mNormalUV.v2 + fChoosenHeight;

		mItemUV.u1 = 0.0f;
		mItemUV.u2 = fComboWidth;
		mItemUV.v1 = mHighLightUV.v2;
		mItemUV.v2 = mHighLightUV.v2 + fItemHeight;

		UV4 sHighLightItemUV;
		sHighLightItemUV.u1 = 0.0f;
		sHighLightItemUV.u2 = fComboWidth;
		sHighLightItemUV.v1 = mItemUV.v2;
		sHighLightItemUV.v2 = mItemUV.v2 + fItemHeight;

		mTopBoarderUV.u1 = 0.0f;
		mTopBoarderUV.u2 = fComboWidth;
		mTopBoarderUV.v1 = sHighLightItemUV.v2 + fBoarderHeight;
		mTopBoarderUV.v2 = sHighLightItemUV.v2;

		mBottomBoarderUV.u1 = 0.0f;
		mBottomBoarderUV.u2 = fComboWidth;
		mBottomBoarderUV.v1 = mTopBoarderUV.v2;
		mBottomBoarderUV.v2 = mTopBoarderUV.v1;

		//����ѡ�������־���
		mpChoosenItem = mpSpriteSet->CreateSprite( mX, mY, mWidth, mChoosenHeight,
			eZType, pZRefOverlay, &mNormalUV );

		mpHighLightItem = mpSpriteSet->CreateSprite( mX, mY, mWidth, mItemHeight,
			ZOT_Upon, mpChoosenItem, &sHighLightItemUV );

		mpBoarder = mpSpriteSet->CreateSprite( mX, mY, mWidth, mBoarderHeight,
			ZOT_Upon, mpChoosenItem, &mBottomBoarderUV );

		mpHighLightItem->SetVisable( false );
		mpBoarder->SetVisable( false );

		//����ѡ��������
		mpChoosenText = TextManager::mpSingleton->CreateTextSurface( ZOT_Upon, mpChoosenItem, mpTextFont, L" ",
			mLoca.X + mChoosenClient.mRect.Left + mTextLeft, mLoca.Y + mChoosenClient.mRect.Top + mTextTop,
			0, 128 );

		//��ʼ���б���
		mItemList.Initialize( pParam->nItemNum, 10 );
	}
	//--------------------------------------------------------------------------------------------------------------
	GuiComboBox::~GuiComboBox()
	{
		//ɾ�������б���
		DelAllItem();

		mpSpriteSet->DeleteSprite( mpChoosenItem );
		mpSpriteSet->DeleteSprite( mpHighLightItem );
		mpSpriteSet->DeleteSprite( mpBoarder );

		TextManager::mpSingleton->DeleteTextSurface( mpChoosenText );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����/�رտؼ�
	void FKFastcall GuiComboBox::Enable( bool bEnable )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʾ/���ؿؼ�
	void FKFastcall GuiComboBox::Show( bool bShow )
	{
		mbVisable = bShow;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����λ��
	void FKFastcall GuiComboBox::SetPos( long nX, long nY )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� Z ˳��
	void FKFastcall GuiComboBox::SetZOrder( ZOrderType eZType, OverlaySurface* pZRefOverlay )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
//	��ȡ Z ˳��
	OverlaySurface* FKFastcall GuiComboBox::GetZOrder( ZOrderType eZType )
	{
		//switch (eZType)
		//{
		//case ZOT_Top:		return mpChoosenText;
		//case ZOT_Bottom:	return mpChoosenItem;
		//}

		return NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���/ʧȥ����
	void FKFastcall GuiComboBox::Focus( bool bHasFocus )
	{
		mbFocus = bHasFocus;

		//���ʧȥ����
		if( !bHasFocus )
		{
			mpChoosenItem->SetSpriteUV( &mNormalUV );
			mbChoosenFocus = false;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƶ�
	void FKFastcall GuiComboBox::MouseMove( InputSystem* pInputSystem )
	{
		//ת��Ϊ�ؼ�����ϵ
		int x = pInputSystem->mMouseX - mLoca.X;
		int y = pInputSystem->mMouseY - mLoca.Y;

		//���ѡ�����䶯
		bool bChoosenFocus = mChoosenClient.IsOnClient( x, y );
		if( bChoosenFocus != mbChoosenFocus )
		{
			mpChoosenItem->SetSpriteUV( bChoosenFocus ? &mHighLightUV : &mNormalUV );
			mbChoosenFocus = bChoosenFocus;
		}

		//���������ʾ�����б���������б�����
		if( mbShowList && mListClient.IsOnClient( x, y ) )
		{
			//�жϽ����б���
			int nItem = ( y - mListClient.mRect.Top ) / mItemHeight;

			//����б����ı�
			if( nItem != mnFocusItem )
			{
				//�ı��б���߹����־���λ��
				float fItemY = (float)( nItem * mItemHeight + mLoca.Y + mListClient.mRect.Top );
				mpHighLightItem->SetLocation( mX, fItemY );

				mnFocusItem = nItem;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������
	void FKFastcall GuiComboBox::LDown( InputSystem* pInputSystem )
	{
		//ת��Ϊ�ؼ�����ϵ
		int nX = pInputSystem->mMouseX - mLoca.X;
		int nY = pInputSystem->mMouseY - mLoca.Y;

		//��ѡ�����ϰ���
		if( mChoosenClient.IsOnClient( nX, nY ) )
		{
			//��ʾ�����������б�
			if( mbShowList )
				_HideList();
			else
				_ShowList();
		}
		//����������б��ϰ���
		else if( mbShowList && mListClient.IsOnClient( nX, nY ) )
		{
			//�жϽ����б���
			int nItem = ( nY - mListClient.mRect.Top ) / mItemHeight;
			Item* pItem = mItemList.Begin() + nItem;

			//�ı䵱ǰѡ������
			mpChoosenText->SetText( pItem->pItemText->mpText );

			//���������б�
			_HideList();
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����б���
	void FKFastcall GuiComboBox::AddItem( const wchar_t* szName, UINT nIndex, LONG_PTR pData )
	{
		//���ָ������λ���Ƿ���ȷ
		UINT nNumItems = mItemList.Size();
		if( nIndex > nNumItems )
			Except( Exception::ERR_INVALIDPARAMS, "����ȷ���б������λ�á�" );

		//�����б���
		Item* pItem = mItemList.Insert( nIndex );

		pItem->pData = pData;

		pItem->pItemSprite = mpSpriteSet->CreateSprite( mX, mY, mWidth, mItemHeight,
			ZOT_Below, mpHighLightItem, &mItemUV );

		pItem->pItemText = TextManager::mpSingleton->CreateTextSurface( ZOT_Upon, mpHighLightItem,
			mpTextFont, szName, mX, mY );

		pItem->pItemSprite->SetVisable( false );
		pItem->pItemText->SetVisable( false );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ���б���
	void FKFastcall GuiComboBox::DelItem( UINT nIndex )
	{
		//���Ҫ��ɾ�����б����Ƿ����
		UINT nNumItems = mItemList.Size();
		if( nIndex >= nNumItems )
			Except( Exception::ERR_INVALIDPARAMS, "����ȷ���б���ɾ��λ�á�" );

		Item* pItem = mItemList.Begin() + nIndex;

		mpSpriteSet->DeleteSprite( pItem->pItemSprite );
		TextManager::mpSingleton->DeleteTextSurface( pItem->pItemText );

		mItemList.Erase( pItem );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�������б���
	void FKFastcall GuiComboBox::DelAllItem()
	{
		ItemList::Iterator it = mItemList.Begin();
		ItemList::Iterator end = mItemList.End();
		for(; it!=end; ++it )
		{
			Item* pItem = it;

			TextManager::mpSingleton->DeleteTextSurface( pItem->pItemText );

			mpSpriteSet->DeleteSprite( pItem->pItemSprite );
		}

		mItemList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//ѡ���б���
	void FKFastcall GuiComboBox::SelItem( UINT nIndex )
	{
		//���Ҫ��ɾ�����б����Ƿ����
		UINT nNumItems = mItemList.Size();
		if( nIndex >= nNumItems )
			Except( Exception::ERR_INVALIDPARAMS, "����ȷ���б���ѡ��λ�á�" );

		Item* pItem = mItemList.Begin() + nIndex;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���û������������Ϣ
	LONG_PTR GuiComboBox::SendMsg( LONG_PTR nGM, LONG_PTR nGMA, LONG_PTR nGMB )
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
		}

		return FALSE;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʾ�����б�
	void FKFastcall GuiComboBox::_ShowList()
	{
		//���������б���ʾλ��
		UINT nNumItems = mItemList.Size();

		//��ʾ�б���Ҫ�߶�
		int nListHeight = mItemHeight * nNumItems + mBoarderHeight;

		//ѡ����¿��ø߶�
		int nChoosenBottom = mLoca.Y + mLoca.Height;
		int nRemainHeight =  OverlayManager::mpSingleton->mRenderHeight - nChoosenBottom;
		int nListTop;

		//���ѡ����¿ռ��㹻��ʾ
		if( nRemainHeight >= nListHeight )
		{
			nListTop = nChoosenBottom;

			//��ʾ�±߿�
			mpBoarder->SetSpriteUV( &mBottomBoarderUV );
			mpBoarder->SetLocation( (float)mX, (float)( nListTop + nListHeight - mBoarderHeight ) );
		}
		//�����б����ʾ������
		else
		{
			mLoca.Y = mLoca.Y - nListHeight;
			nListTop = mLoca.Y + mBoarderHeight;

			mChoosenClient.mRect.Top += nListHeight;
			mChoosenClient.mRect.Bottom += nListHeight;

			//��ʾ�ϱ߿�
			mpBoarder->SetSpriteUV( &mTopBoarderUV );
			mpBoarder->SetLocation( (float)mX, (float)mLoca.Y );
		}

		mpBoarder->SetVisable( true );

		//���¿ؼ��û���
		mLoca.Height += nListHeight;
		mClient.mRect.Bottom += nListHeight;

		mListClient.mRect.Top = nListTop - mLoca.Y;
		mListClient.mRect.Bottom = mListClient.mRect.Top + mItemHeight * nNumItems;

		int nTextLeft = mX + mChoosenClient.mRect.Left + mTextLeft;

		//��ʾѡ���б���ĸ߹����־���
		float fItemY = (float)( mnFocusItem * mItemHeight + mLoca.Y + mListClient.mRect.Top );

		//��֤����ʾ�ڶԻ������ϲ�
		ZOrderType eZType;
		OverlaySurface* pZRefOverlay;
		mpDialog->GetTopZOrder( &eZType, &pZRefOverlay );
		mpHighLightItem->SetZOrder( eZType, pZRefOverlay );

		mpHighLightItem->SetLocation( mX, fItemY );
		mpHighLightItem->SetVisable( true );

		//��ʾ�б���
		ItemList::Iterator it = mItemList.Begin();
		ItemList::Iterator end = mItemList.End();
		for(; it!=end; ++it )
		{
			Item* pItem = it;

			Sprite* pSprite = pItem->pItemSprite;
			TextSurface* pText = pItem->pItemText;

//			pSprite->SetZOrder( ZOT_Below, mpHighLightItem );
//			pText->SetZOrder( ZOT_Upon, mpHighLightItem );

			pSprite->SetLocation( mX, (float)nListTop );
			pText->SetTextPos( nTextLeft, nListTop + mTextTop );

			nListTop += mItemHeight;

			pSprite->SetVisable( true );
			pText->SetVisable( true );
		}

		mbShowList = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������б�
	void FKFastcall GuiComboBox::_HideList()
	{
		//���¿ؼ��û���
		mLoca.Y = mY;
		mLoca.Height = mChoosenHeight;
		mClient.mRect.Bottom = mChoosenHeight;

		mChoosenClient.mRect.Top = mTextTop;
		mChoosenClient.mRect.Bottom = mTextTop + mItemHeight;

		//���������б�
		mpBoarder->SetVisable( false );

		ItemList::Iterator it = mItemList.Begin();
		ItemList::Iterator end = mItemList.End();
		for(; it!=end; ++it )
		{
			Item* pItem = it;
			pItem->pItemSprite->SetVisable( false );
			pItem->pItemText->SetVisable( false );
		}

		//����ѡ���б���ĸ߹����־���
		mpHighLightItem->SetVisable( false );

		mbShowList = false;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

