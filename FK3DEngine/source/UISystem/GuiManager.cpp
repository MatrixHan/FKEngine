/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiManager
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
	GuiManager::GuiManager()
		: mbEnable			(true)
		, mbVisalbe			(true)
		, mbCursorVisable	(true)
		, mpCursorGui		(NULL)
		, mbLockFocus		(false)
		, mpFocusedGui		(NULL)
	{
		mDialogList.Initialize( 6, 6 );
	}
	//--------------------------------------------------------------------------------------------------------------
	GuiManager::~GuiManager()
	{
		DeleteCursor();
		DeleteAllDialog();

		mDialogList.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����û�����ϵͳ����״̬
	void GuiManager::SetEnable( bool bEnable )
	{
		mbEnable = bEnable;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����û�������ʾ״̬
	void GuiManager::SetVisable( bool bVisable )
	{
		mbVisalbe = bVisable;

		//���������û����������ʾ״̬
		LONG_PTR nGMA = bVisable ? 1 : 0;

		GuiDlgList::Iterator it = mDialogList.Begin();
		GuiDlgList::Iterator end = mDialogList.End();

		for(; it!=end; ++it )
		{
			if( *it != NULL )
				(*it)->SendMsg( GM_Show, nGMA );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void GuiManager::LockFocus( GuiBase* pFocusGui )
	{
		mbLockFocus = true;
		mpFocusedGui = pFocusGui;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void GuiManager::UnlockFocus()
	{
		mbLockFocus = false;
		mpFocusedGui = NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ù����ʾ״̬
	void GuiManager::SetCursorVisable( bool bVisable )
	{
		mbCursorVisable = bVisable;

		if( mpCursorGui != NULL )
			mpCursorGui->Show( bVisable );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������
	void GuiManager::CreateCursor( UINT nWidth, UINT nHeight, int nTargetX, int nTargetY, SpriteSet* pSpriteSet, UVAnimation* pUVA )
	{
		GuiLoca sLoca;
		sLoca.X = 0;
		sLoca.Y = 0;
		sLoca.Width = nWidth;
		sLoca.Height = nHeight;

		mpCursorGui = new GuiCursor( &sLoca, nTargetX, nTargetY, pSpriteSet, pUVA );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��������
	void GuiManager::DeleteCursor()
	{
		SafeDelete( mpCursorGui );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʾ/�������ָ��
	void GuiManager::ShowCursor( bool bShow )
	{
		if( mpCursorGui != NULL )
			mpCursorGui->Show( bShow );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����Ի���
	GuiDialog* GuiManager::CreateDialog( ZOrderType eZType, GuiDialog* pZRefDialog, GuiLoca* pLoca, GuiClient* pClient )
	{
		//�����¶Ի���
		GuiDialog* pDialog = new GuiDialog( pLoca, pClient );

		GuiDialog* pBelowDialog = NULL;	//�½��Ի���֮�¶Ի���
		GuiDialog* pUponDialog = NULL;	//�½��Ի���֮�϶Ի���

		switch (eZType)
		{
			//���ϲ㣨�����Ⱦ��
		case ZOT_Top:
			{
				if( mDialogList.Size() > 0 )
					pUponDialog = *mDialogList.Back();

				*mDialogList.Push() = pDialog;
				goto FixList;
			}
			//���²㣨������Ⱦ��
		case ZOT_Bottom:
			{
				if( mDialogList.Size() > 0 )
					pBelowDialog = *mDialogList.Begin();

				*mDialogList.Insert( (unsigned int)0 ) = pDialog;
				goto FixList;
			}
			//ָ���Ի���֮�ϣ�����Ⱦ��
		case ZOT_Upon:
			{
				if( mDialogList.Size() == 0 )
					break;

				//���ָ����׼�Ի��������Ի���
				GuiDlgList::Iterator back = mDialogList.Back();
				if( pZRefDialog == *back )
				{
					pBelowDialog = pZRefDialog;
					*mDialogList.Push() = pDialog;
					goto FixList;
				}
				else
				{
					GuiDlgList::Iterator beg = mDialogList.Begin();
					GuiDlgList::Iterator it = --back;
					for(; it>=beg; --it )
					{
						if( *it == pZRefDialog )
						{
							pBelowDialog = *it;
							pUponDialog = *( ++it );
							*mDialogList.Insert( it ) = pDialog;
							goto FixList;
						}
					}
				}
				break;
			}
			//ָ���Ի���֮�£�����Ⱦ��
		case ZOT_Below:
			{
				if( mDialogList.Size() == 0 )
					break;

				//���ָ����׼�Ի�������ײ�Ի���
				GuiDlgList::Iterator begin = mDialogList.Begin();
				if( pZRefDialog == *begin )
				{
					pUponDialog = *begin;
					*mDialogList.Insert( (unsigned int)0 ) = pDialog;
					goto FixList;
				}
				else
				{
					GuiDlgList::Iterator it = ++begin;
					GuiDlgList::Iterator end = mDialogList.End();
					for(; it!=end; ++it )
					{
						if( *it == pZRefDialog )
						{
							pBelowDialog = *( it - 1 );
							pUponDialog = *it;
							*mDialogList.Insert( it ) = pDialog;
							goto FixList;
						}
					}
				}
				break;
			}
		}

		//Except( Exception::ERR_INVALIDPARAMS, "ָ���ĶԻ��� Z ˳������޷���������б�" );

FixList:
		//�������öԻ�������ָ��
		pDialog->mpBottomDialog = pBelowDialog;

		if( pUponDialog != NULL )
			pUponDialog->mpBottomDialog = pDialog;

		return pDialog;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ���Ի���
	void GuiManager::DeleteDialog( GuiDialog* pDialog )
	{
		if( pDialog == NULL )
			return;

		GuiDlgList::Iterator begin = mDialogList.Begin();
		GuiDlgList::Iterator back = mDialogList.Back();
		GuiDlgList::Iterator it = begin;
		for(; it>=back; ++it )
		{
			if( *it == pDialog )
			{
				//���ɾ���Ի�������ϲ�Ի���
				if( it != back )
				{
					GuiDialog* pUponDialog = *( it + 1 );
					pUponDialog->mpBottomDialog = ( it != begin ) ? *( it - 1 ) : NULL;
				}

				mDialogList.Erase( it );
				delete pDialog;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����жԻ���
	void GuiManager::DeleteAllDialog()
	{
		GuiDlgList::Iterator it = mDialogList.Begin();
		GuiDlgList::Iterator end = mDialogList.End();
		for(; it!=end; ++it )
		{
			if( *it != NULL )
				delete *it;
		}

		mDialogList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����û����������¼�
	void GuiManager::ProcGuiInput( InputSystem* pInputSystem, float fFrameTime )
	{
		//����û�����ϵͳ�ر���ֱ�ӷ���
		if( !mbEnable )
			return;

		//���û����������
		if( !mbLockFocus )
		{
			//��ȡ�ڵ�ǰ���λ���ϵ��û��������
			GuiBase* pTargetGui = GetGuiOnMouse( pInputSystem->mMouseX, pInputSystem->mMouseY );

			//������㷢���仯
			if( mpFocusedGui != pTargetGui )
			{
				//֪ͨ�ϴλ�ý���Ķ���ʧȥ����
				if( mpFocusedGui != NULL )
					mpFocusedGui->SendMsg( GM_Focus, 0 );

				//֪ͨ�»�ý���Ķ���
				if( pTargetGui != NULL )
					pTargetGui->SendMsg( GM_Focus, 1 );

				mpFocusedGui = pTargetGui;
			}
		}

		//���ȴ���˫���¼�����δ��������ż���
		if( mpFocusedGui != NULL )
		{
			if( pInputSystem->mbMouseDBClick[0] )
				mpFocusedGui->SendMsg( GM_LDBClick, (LONG_PTR)pInputSystem, NULL );
			else if( pInputSystem->mbMouseDown[0] )
				mpFocusedGui->SendMsg( GM_LDown, (LONG_PTR)pInputSystem, NULL );
			else if( pInputSystem->mbMouseUp[0] )
				mpFocusedGui->SendMsg( GM_LUp, (LONG_PTR)pInputSystem, NULL );
		}

		if( mpFocusedGui != NULL )
		{
			if( pInputSystem->mbMouseDBClick[1] )
				mpFocusedGui->SendMsg( GM_RDBClick, (LONG_PTR)pInputSystem, NULL );
			else if( pInputSystem->mbMouseDown[1] )
				mpFocusedGui->SendMsg( GM_RDown, (LONG_PTR)pInputSystem, NULL );
			else if( pInputSystem->mbMouseUp[1] )
				mpFocusedGui->SendMsg( GM_RUp, (LONG_PTR)pInputSystem, NULL );
		}

		//��������ƶ���Ϣ
		if( mpFocusedGui != NULL && ( pInputSystem->mMouseRelX != 0 || pInputSystem->mMouseRelY != 0 ) )
			mpFocusedGui->SendMsg( GM_MouseMove, (LONG_PTR)pInputSystem );

		//������ڹ���û��������
		if( mpCursorGui != NULL )
		{
			//���¹��λ��
			mpCursorGui->SetPos( (long)pInputSystem->mMouseX, (long)pInputSystem->mMouseY );

			//������λ���Ѹı�
			if( pInputSystem->mMouseRelX != 0 || pInputSystem->mMouseRelY != 0 )
			{
				//���¹�꼤��״̬
				mpCursorGui->UpdateActivate();
			}
			else
			{
				//���¹������ʱ��
				mpCursorGui->UpdateIdleTime( fFrameTime );
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ڵ�ǰ���λ���ϵ��û��������ָ��
	GuiBase* GuiManager::GetGuiOnMouse( int x, int y )
	{
		//�������жԻ���
		GuiDlgList::Iterator it = mDialogList.Begin();
		GuiDlgList::Iterator end = mDialogList.End();
		for(; it!=end; ++it )
		{
			GuiDialog* pDialog = *it;

			//�������ڸöԻ���ͻ���֮��
			if( pDialog->IsOnClient( x, y ) )
			{
				GuiBase* pGui = pDialog->GetGuiOnMouse( x, y );
				if( pGui != NULL )
					return pGui;
			}
		}

		return NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
