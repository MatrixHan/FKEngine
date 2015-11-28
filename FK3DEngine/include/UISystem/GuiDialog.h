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
*	�ļ�˵����	�û�����Ի��� 
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "GuiBase.h"
#include "GuiButton.h"
#include "GuiComboBox.h"
#include "GuiListBox.h"
#include "GuiTrackBar.h"
#include "GuiCheckBox.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//�û�����Ի���
	class FK_DLL GuiDialog : public GuiBase
	{
	public:
		GuiList			mGuiList;			//�û���������б�

		GuiDialog*		mpBottomDialog;		//�²�Ի���

	public:
		GuiDialog( GuiLoca* pLoca, GuiClient* pClient );
		virtual ~GuiDialog();

		//������ť����
		GuiButton* CreateButton( GuiButton::Param* pParam );

		//������ѡ�����
		GuiCheckBox* CreateCheckBox( GuiCheckBox::Param* pParam );

		//������Ͽ����
		GuiComboBox* CreateComboBox( GuiComboBox::Param* pParam );

		//����������
		GuiTrackBar* CreateTrackBar( GuiTrackBar::Param* pParam );

		//ɾ���û��������
		void DeleteGui( GuiBase* pGui );

		//ɾ�������û��������
		void DeleteAllGui();

		//��ȡ�ڵ�ǰ���λ���ϵ��û��������
		GuiBase* FKFastcall GetGuiOnMouse( int x, int y );

		//��ȡ�Ի��򶥲� Z ˳��
		void FKFastcall GetTopZOrder( ZOrderType* pZType, OverlaySurface** ppZRefOverlay );

	public:
		//���û������������Ϣ
		LONG_PTR SendMsg( LONG_PTR nGM, LONG_PTR nGMA = 0, LONG_PTR nGMB = 0 );
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< GuiDialog* >		GuiDlgList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

