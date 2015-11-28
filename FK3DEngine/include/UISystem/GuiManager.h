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
*	�ļ�˵����	�û����������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
class GuiBase;
#include "GuiCursor.h"
#include "GuiDialog.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	struct UVAnimation;
	//--------------------------------------------------------------------------------------------------------------
	//�û����������
	class FK_DLL GuiManager : public Singleton< GuiManager >
	{
	public:
		bool			mbEnable;			//�Ƿ����û�����
		bool			mbVisalbe;			//�Ƿ���ʾ�û�����
		bool			mbCursorVisable;	//�Ƿ���ʾ���

		GuiCursor*		mpCursorGui;		//����û��������

		bool			mbLockFocus;		//�Ƿ���������
		GuiBase*		mpFocusedGui;		//��ý�����û��������

	protected:
		GuiDlgList		mDialogList;		//�û�����Ի����б�

	public:
		GuiManager();
		~GuiManager();

		//�����û�����ϵͳ����״̬
		void SetEnable( bool bEnable );

		//�����û�������ʾ״̬
        void SetVisable( bool bVisable );

		//��������
		void LockFocus( GuiBase* pFocusGui );

		//��������
		void UnlockFocus();

		//���ù����ʾ״̬
		void SetCursorVisable( bool bVisable );

		//����������
		void CreateCursor( UINT nWidth, UINT nHeight, int nTargetX, int nTargetY, SpriteSet* pSpriteSet, UVAnimation* pUVA );

		//ɾ��������
		void DeleteCursor();

		//��ʾ/�������ָ��
		void ShowCursor( bool bShow = true );

		//�����Ի���
		GuiDialog* CreateDialog( ZOrderType eZType, GuiDialog* pZRefDialog, GuiLoca* pLoca, GuiClient* pClient );

		//ɾ���Ի���
		void DeleteDialog( GuiDialog* pDialog );

		//ɾ�����жԻ���
		void DeleteAllDialog();

		//�����û����������¼�
		void ProcGuiInput( InputSystem* pInputSystem, float fFrameTime );

		//��ȡ�ڵ�ǰ���λ���ϵ��û��������
		GuiBase* GetGuiOnMouse( int x, int y );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
