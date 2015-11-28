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

#include "../Include/UIManager.h"
#include "../Include/Input.h"
#include "../Include/Exception.h"
#include "../Include/FKWindow.h"
#include "../Include/RadioButton.h"
#include "../Include/RootControl.h"
#include "../Include/Text.h"

//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	CGUIManager::CGUIManager()
		: m_pFocusedCtrl( NULL )
		, m_pLockedCtrl( NULL )
		, m_pHoveredCtrl( NULL )
		, m_pGraphics( NULL )
		, m_pDefaultFont( NULL )
		, m_pRootCtrl( NULL )
	{

	}
	//--------------------------------------------------------------------
	CGUIManager::~CGUIManager()
	{
		if( m_pDefaultFont != NULL )
		{
			delete m_pDefaultFont;
			m_pDefaultFont = NULL;
		}
		if( m_pRootCtrl != NULL )
		{
			delete m_pRootCtrl;
			m_pRootCtrl = NULL;
		}
	}
	//--------------------------------------------------------------------
	void CGUIManager::Init( CGraphics& p_Canvas )
	{
		m_pGraphics = &p_Canvas;
		m_pDefaultFont = new CFont( *m_pGraphics, DefaultFontName() , 20 );
		m_pRootCtrl = new CRootControl();
		m_pRootCtrl->SetFont( *m_pDefaultFont );
	}
	//--------------------------------------------------------------------
	CGraphics& CGUIManager::GetGraphics()
	{
		FKAssert( (m_pGraphics != NULL), L"��ȡGUI��Ⱦָ��ʧ��" );
		return *m_pGraphics;
	}
	//--------------------------------------------------------------------
	void CGUIManager::AddCtrl( IGUIControl* p_pCtrl )
	{
		std::list< IGUIControl* >::iterator Ite = m_listControl.begin();
		for( ; Ite != m_listControl.end(); ++Ite )
		{
			if( *Ite == p_pCtrl )
			{
				return;
			}
		}
		m_listControl.push_back( p_pCtrl );
	}
	//--------------------------------------------------------------------
	void CGUIManager::DelCtrl( IGUIControl* p_pCtrl )
	{
		std::list< IGUIControl* >::iterator Ite = m_listControl.begin();
		for( ; Ite != m_listControl.end(); ++Ite )
		{
			if( *Ite == p_pCtrl )
			{
				m_listControl.erase( Ite );

				if( m_pFocusedCtrl == p_pCtrl )
				{
					m_pFocusedCtrl = NULL;
				}
				if( m_pHoveredCtrl == p_pCtrl )
				{
					m_pHoveredCtrl = NULL;
				}
				if( m_pLockedCtrl == p_pCtrl )
				{
					m_pLockedCtrl = NULL;
				}
				return;
			}
		}
	}
	//--------------------------------------------------------------------
	void CGUIManager::SetFocus( IGUIControl* p_pCtrl )
	{
		if( p_pCtrl == m_pFocusedCtrl )
		{
			return;
		}

		if( m_pFocusedCtrl != NULL )
		{
			m_pFocusedCtrl->Leave();
		}

		m_pFocusedCtrl = p_pCtrl;

		if( p_pCtrl != NULL )
		{
			m_pFocusedCtrl->Enter();
		}
	}
	//--------------------------------------------------------------------
	void CGUIManager::Update( float p_fDelta )
	{
		IGUIControl* pCurControl = NULL;
		std::list< IGUIControl* >::iterator Ite = m_listControl.begin();
		// ֪ͨ�ӿؼ�����
		for( ; Ite != m_listControl.end(); ++Ite )
		{
			(*Ite)->Update( p_fDelta );
		}
		// ���½���ؼ�
		if( m_pFocusedCtrl != NULL )
		{
			std::queue< unsigned int > qKeyDown = SSGUIInputManager::Instance()->GetKeyDown();
			std::queue< unsigned int > qKeyUp = SSGUIInputManager::Instance()->GetKeyUp();
			std::queue< char > qKeyChar = SSGUIInputManager::Instance()->GetKeyChar();
			SShiftState tagShiftState = SSGUIInputManager::Instance()->GetShiftState();

			// �����Ϣ����
			while( !qKeyDown.empty() )
			{
				m_pFocusedCtrl->KeyDown( qKeyDown.front(), tagShiftState );
				qKeyDown.pop();
			}
			while( !qKeyUp.empty() )
			{
				m_pFocusedCtrl->KeyDown( qKeyUp.front(), tagShiftState );
				qKeyUp.pop();
			}
			while( !qKeyChar.empty() )
			{
				m_pFocusedCtrl->KeyDown( qKeyChar.front(), tagShiftState );
				qKeyChar.pop();
			}
		}

		// �����ڱ������ؼ�
		if( m_pLockedCtrl != NULL )
		{
			if( m_pHoveredCtrl == NULL )
			{
				SSLogManager::Instance()->LogMessage(L"BigEnter");
			}
			
			pCurControl = m_pLockedCtrl;

			if( !SSGUIInputManager::Instance()->GetMouseState( eMB_Left ) )
			{
				m_pLockedCtrl = NULL;
			}
			// ��ȡ����
			if(( m_pHoveredCtrl == pCurControl ) && ( !pCurControl->IsPointIn( SSGUIInputManager::Instance()->GetMousePos() ) ) )
			{
				pCurControl->MouseLeave();
				m_pHoveredCtrl = NULL;
			}
			else // ��ʧ����
			if( ( m_pHoveredCtrl == NULL ) && ( pCurControl->IsPointIn( SSGUIInputManager::Instance()->GetMousePos() ) ) )
			{
				pCurControl->MouseEnter();
				m_pHoveredCtrl = pCurControl;
			}

			ProcessMouseEvent( pCurControl );
		}
		else
		{
			// �����������ؼ�
			std::list< IGUIControl* >::reverse_iterator Ite = m_listControl.rbegin();
			for( ; Ite != m_listControl.rend(); ++Ite )
			{
				pCurControl = (*Ite);

				// ��������Ч�ģ��ɼ��ģ������λ�ڿؼ��ڵ� �ؼ�
				if( ( pCurControl != NULL ) && ( pCurControl->IsEnabled() ) && ( pCurControl->IsVisiable() )
					&& ( pCurControl->IsPointIn( SSGUIInputManager::Instance()->GetMousePos() ) ) )
				{
					if( m_pHoveredCtrl != pCurControl )
					{
						if( m_pHoveredCtrl != NULL )
						{
							m_pHoveredCtrl->MouseLeave();
						}

						m_pHoveredCtrl = pCurControl;
						m_pHoveredCtrl->MouseEnter();
					}

					ProcessMouseEvent( pCurControl );
					return;
				}
			}

			// ��겻���κ���Ч�ɼ��ؼ���
			if( m_pHoveredCtrl != NULL )
			{
				m_pHoveredCtrl->MouseLeave();
				m_pHoveredCtrl = NULL;
			}
		}

	}
	//--------------------------------------------------------------------
	void CGUIManager::FKDraw()
	{
		std::list< IGUIControl* >::iterator Ite = m_listControl.begin();
		for( ; Ite != m_listControl.end(); ++Ite )
		{
			if( ( *Ite != NULL ) && ( *Ite )->IsVisiable() )
			{
				(*Ite)->FKDraw();
			}
		}
	}
	//--------------------------------------------------------------------
	void CGUIManager::AddRadio( CRadioButton* p_pRadio )
	{
		std::list< CRadioButton* >::iterator Ite = m_ListRadioButton.begin();

		for( ; Ite != m_ListRadioButton.end(); ++Ite )
		{
			if(( *Ite ) == p_pRadio )
			{
				return;
			}
		}

		m_ListRadioButton.push_back( p_pRadio );
	}
	//--------------------------------------------------------------------
	void CGUIManager::DelRadio( CRadioButton* p_pRadio )
	{
		std::list< CRadioButton* >::iterator Ite = m_ListRadioButton.begin();

		for( ; Ite != m_ListRadioButton.end(); ++Ite )
		{
			if(( *Ite ) == p_pRadio )
			{
				m_ListRadioButton.erase( Ite );
				return;
			}
		}
	}
	//--------------------------------------------------------------------
	void CGUIManager::CheckRadio( CRadioButton* p_pRadio )
	{
		std::list< CRadioButton* >::iterator Ite = m_ListRadioButton.begin();

		for( ; Ite != m_ListRadioButton.end(); ++Ite )
		{
			if((( *Ite )->GetGroup() == p_pRadio->GetGroup()) && ((*Ite) != p_pRadio ))
			{
				(*Ite)->UnCheck();
			}
		}
	}
	//--------------------------------------------------------------------
	IGUIControl* CGUIManager::GetRootCtrl()
	{
		return static_cast< IGUIControl* >( m_pRootCtrl );
	}
	//--------------------------------------------------------------------
	void CGUIManager::ProcessMouseEvent( IGUIControl* p_pCtrl )
	{
		if( SSGUIInputManager::Instance()->IsMouseJustDown( eMB_Left ) )
		{
			m_pLockedCtrl = p_pCtrl;

			if( p_pCtrl->CanHaveFocus() )
			{
				SetFocus( p_pCtrl );
			}

			p_pCtrl->MouseDown( SSGUIInputManager::Instance()->GetMousePos(), eMB_Left );
		}

		if( SSGUIInputManager::Instance()->IsMouseJustDown( eMB_Right ) )
		{
			p_pCtrl->MouseDown( SSGUIInputManager::Instance()->GetMousePos(), eMB_Right );
		}

		if( SSGUIInputManager::Instance()->IsMouseJustDown( eMB_Middle ) )
		{
			p_pCtrl->MouseDown( SSGUIInputManager::Instance()->GetMousePos(), eMB_Middle );
		}

		if( SSGUIInputManager::Instance()->IsMouseJustUp( eMB_Middle ) )
		{
			p_pCtrl->MouseUp( SSGUIInputManager::Instance()->GetMousePos(), eMB_Middle );
		}

		if( SSGUIInputManager::Instance()->IsMouseJustUp( eMB_Right ) )
		{
			p_pCtrl->MouseUp( SSGUIInputManager::Instance()->GetMousePos(), eMB_Right );
		}

		if( SSGUIInputManager::Instance()->IsMouseJustUp( eMB_Left ) )
		{
			p_pCtrl->MouseUp( SSGUIInputManager::Instance()->GetMousePos(), eMB_Left );
		}

		if( SSGUIInputManager::Instance()->IsMouseMoved() )
		{
			p_pCtrl->MouseMove( SSGUIInputManager::Instance()->GetMousePos() );
		}
	}
	//--------------------------------------------------------------------
}