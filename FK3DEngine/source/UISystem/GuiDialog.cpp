/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiDialog
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
	GuiDialog::GuiDialog( GuiLoca* pLoca, GuiClient* pClient )
		: GuiBase			( pLoca, pClient )
		, mpBottomDialog	(NULL)
	{
		mGuiList.Initialize( 10, 10 );
	}
	//--------------------------------------------------------------------------------------------------------------
	GuiDialog::~GuiDialog()
	{
		DeleteAllGui();

		mGuiList.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ť����
	GuiButton* GuiDialog::CreateButton( GuiButton::Param* pParam )
	{
		ZOrderType eZType;
		OverlaySurface* pZRefOverlay;
		GetTopZOrder( &eZType, &pZRefOverlay );

		GuiButton* pButton = new GuiButton( eZType, pZRefOverlay, this, pParam );
		*mGuiList.Push() = pButton;
		return pButton;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ѡ�����
	GuiCheckBox* GuiDialog::CreateCheckBox( GuiCheckBox::Param* pParam )
	{
		ZOrderType eZType;
		OverlaySurface* pZRefOverlay;
		GetTopZOrder( &eZType, &pZRefOverlay );

		GuiCheckBox* pCheckBox = new GuiCheckBox( eZType, pZRefOverlay, this, pParam );
		*mGuiList.Push() = pCheckBox;
		return pCheckBox;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ͽ����
	GuiComboBox* GuiDialog::CreateComboBox( GuiComboBox::Param* pParam )
	{
		ZOrderType eZType;
		OverlaySurface* pZRefOverlay;
		GetTopZOrder( &eZType, &pZRefOverlay );

		GuiComboBox* pComboBox = new GuiComboBox( eZType, pZRefOverlay, this, pParam );
		*mGuiList.Push() = pComboBox;
		return pComboBox;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������
	GuiTrackBar* GuiDialog::CreateTrackBar( GuiTrackBar::Param* pParam )
	{
		ZOrderType eZType;
		OverlaySurface* pZRefOverlay;
		GetTopZOrder( &eZType, &pZRefOverlay );

		GuiTrackBar* pTrackBar = new GuiTrackBar( eZType, pZRefOverlay, this, pParam );
		*mGuiList.Push() = pTrackBar;
		return pTrackBar;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ���û��������
	void GuiDialog::DeleteGui( GuiBase* pGui )
	{
		if( pGui == NULL )
			return;

		GuiList::Iterator it = mGuiList.Begin();
		GuiList::Iterator end = mGuiList.End();

		for(; it!=end; ++it )
		{
			if( *it == pGui )
			{
				mGuiList.Erase( it );
				delete pGui;
				return;
			}
		}

		Except( Exception::ERR_INVALIDPARAMS, "ָ��ɾ�����û�������󲻴��ڡ�" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�������û��������
	void GuiDialog::DeleteAllGui()
	{
		GuiList::Iterator it = mGuiList.Begin();
		GuiList::Iterator end = mGuiList.End();

		for(; it!=end; ++it )
		{
			if( *it != NULL )
				delete *it;
		}

		mGuiList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ڵ�ǰ���λ���ϵ��û��������ָ��
	GuiBase* FKFastcall GuiDialog::GetGuiOnMouse( int x, int y )
	{
		//���������û��������
		GuiList::Iterator it = mGuiList.Begin();
		GuiList::Iterator end = mGuiList.End();
		for(; it!=end; ++it )
		{
			GuiBase* pGui = *it;

			//�������ڸ��û��������ͻ���֮��
			if( pGui->IsOnClient( x, y ) )
				return pGui;
		}

		return NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�Ի��򶥲� Z ˳��
	void FKFastcall GuiDialog::GetTopZOrder( ZOrderType* pZType, OverlaySurface** ppZRefOverlay )
	{
		//����öԻ�����δ�����κ��û�����ؼ�
		if( mGuiList.Size() == 0 )
		{
			//����öԻ�������²�Ի���
			if( mpBottomDialog != NULL )
			{
				mpBottomDialog->GetTopZOrder( pZType, ppZRefOverlay );
			}
			else
			{
				GuiCursor* pCursor = GuiManager::mpSingleton->mpCursorGui;
				if( pCursor != NULL )
				{
					*pZType = ZOT_Below;
					*ppZRefOverlay = pCursor->mpSprite;
				}
				else
				{
					OverlaySurface* pTopmost = OverlayManager::mpSingleton->GetTopmostOverlay();
					*pZType = ( pTopmost == NULL ) ? ZOT_Top : ZOT_Upon;
					*ppZRefOverlay = pTopmost;
				}
			}
		}
		else
		{
			GuiBase* pGui = *mGuiList.Back();

			*pZType = ZOT_Upon;
			*ppZRefOverlay = (OverlaySurface*)pGui->SendMsg( GM_GetZOrder, (LONG_PTR)ZOT_Top );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���û������������Ϣ
	LONG_PTR GuiDialog::SendMsg( LONG_PTR nGM, LONG_PTR nGMA, LONG_PTR nGMB )
	{
		return 0;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

