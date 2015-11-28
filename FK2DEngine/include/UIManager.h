/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	UIManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "UIControl.h"
#include "Graphics.h"
#include "Singleton.h"
#include "../../depend/boost/utility.hpp"
#include "Font.h"
#include <list>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	class CRadioButton;
	//--------------------------------------------------------------------
	class CGUIManager : boost::noncopyable
	{
	public:
		CGUIManager();
		~CGUIManager();
	public:
		//! ��ʼ�����趨����
		void Init( CGraphics& p_Canvas );
		//! ��ȡ����
		CGraphics& GetGraphics();

		//! ע��ؼ�
		void AddCtrl( IGUIControl* p_pCtrl );
		//! ע���ؼ�
		void DelCtrl( IGUIControl* p_pCtrl );

		//! ʹ�ؼ���ý���
		void SetFocus( IGUIControl* p_pCtrl );
		
		//! ����GUIϵͳ
		void Update( float p_fDelta );

		//! ����GUIϵͳ
		void FKDraw();

		//! ���ӵ�ѡ��ť
		void AddRadio( CRadioButton* p_pRadio );
		//! ɾ����ѡ��ť
		void DelRadio( CRadioButton* p_pRadio );
		//! ѡ�е�ѡ��ť
		void CheckRadio( CRadioButton* p_pRadio );

		//! ��ȡ���ؼ�
		IGUIControl* GetRootCtrl();

	private:
		//! ����ؼ�������¼�
		void ProcessMouseEvent( IGUIControl* p_pCtrl );
	private:
		std::list< IGUIControl* >		m_listControl;		// �ؼ��б�
		CGraphics*						m_pGraphics;		// ��Ⱦָ��
		IGUIControl*					m_pFocusedCtrl;		// ��ý���Ŀؼ�
		IGUIControl*					m_pLockedCtrl;		// �������Ŀؼ�
		IGUIControl*					m_pHoveredCtrl;		// ����µĿؼ�
		std::list< CRadioButton* >		m_ListRadioButton;	// ��ѡ��ť�б�
		CFont*							m_pDefaultFont;		// Ĭ������
		IGUIControl*					m_pRootCtrl;		// ���ؼ�
	private:
		DECLARE_SINGLETON_CLASS( CGUIManager );
	};
	//--------------------------------------------------------------------
}

typedef FK2DEngine::TSingleton< FK2DEngine::CGUIManager >	SSGUIManager;