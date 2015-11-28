/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	UIControl
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include <Windows.h>
#include "WinKey.h"
#include "Font.h"
#include <list>
#include "UIInputManager.h"
//--------------------------------------------------------------------

namespace FK2DEngine
{
	//--------------------------------------------------------------------
	class IGUIControl;
	//--------------------------------------------------------------------
	// �¼�������
	typedef void ( IGUIControl::*NotifyFun)( void );
	struct SNotifyEvent
	{
		SNotifyEvent() : function(NULL), invoker(NULL) {}
		NotifyFun function;
		IGUIControl *invoker;
	};

	typedef void ( IGUIControl::*MouseMoveFun)( POINT pt );
	struct SMouseMoveEvent
	{
		SMouseMoveEvent() : function(NULL), invoker(NULL) {}
		MouseMoveFun function;
		IGUIControl *invoker;
	};

	typedef void ( IGUIControl::*MouseFun)( POINT pt, ENUM_MouseButton mb );
	struct SMouseEvent
	{
		SMouseEvent() : function(NULL), invoker(NULL) {}
		MouseFun function;
		IGUIControl *invoker;
	};

	typedef void ( IGUIControl::*KeyFun)( unsigned long p_ulKey, SShiftState p_State );
	struct SKeyEvent
	{
		SKeyEvent() : function(NULL), invoker(NULL) {}
		KeyFun function;
		IGUIControl *invoker;
	};

	typedef void ( IGUIControl::*KeyPressFun)( char p_cKey );
	struct SKeyPressEvent
	{
		SKeyPressEvent() : function(NULL), invoker(NULL) {}
		KeyPressFun function;
		IGUIControl *invoker;
	};
	//--------------------------------------------------------------------
	//! UI�ؼ�����
	//@remarks	��������ṩ������������¼�����������
	//			��һ�ǿؼ��������¼������󽫱� Gui ����ã�������̳�ʵ�ָ��Թ��ܡ�
	//			�ڶ����û���������ָ�뿪�Ÿ��û����û����б�д�¼���������ͬʱ��
	//				�û���������ַ���ؼ���
	//			�ؼ���ִ����������¼��󣬵����û��¼���
	class IGUIControl
	{
	public:
		IGUIControl();
		virtual ~IGUIControl();
	private:
		IGUIControl( const IGUIControl& );
		IGUIControl& operator= ( const IGUIControl& );
	public:
		virtual void FKDraw() const = 0;
		virtual void Update( float p_fDelta ){}
		//! �Ƿ���Ի�ȡ����
		//@ ���Ի�ý���Ŀؼ������Դ�������¼�
		virtual bool CanHaveFocus() const{ return true; }
	public:
		//! ������
		virtual void MouseEnter();
		//! ����뿪
		virtual void MouseLeave();
		//! ����ƶ�
		virtual void MouseMove( POINT p_Point );
		//! ��갴��
		virtual void MouseDown( POINT p_Point, ENUM_MouseButton p_eMB );
		//! ��굯��
		virtual void MouseUp( POINT p_Point, ENUM_MouseButton p_eMB );
		//! ���̰���
		virtual void KeyDown( unsigned long p_ulKey, SShiftState p_State );
		//! ���̵���
		virtual void KeyUp( unsigned long p_ulKey, SShiftState p_State );
		//! �ַ�������
		virtual void KeyPress( char p_cKey );
		//! ��ý���
		virtual void Enter();
		//! ʧȥ����
		virtual void Leave();
	public:
		//! �����ؼ����� Gui ���Ψһʵ����ע�᱾�ռ�
		void Create();
		//! ���ø��ؼ�
		void SetParent( IGUIControl* p_pParent );
		//! ����ӿؼ�
		void AddChild( IGUIControl* p_pChild );
		//! ɾ���ӿؼ�
		void DelChild( IGUIControl* p_pChild );
		//! ʹ�ؼ���Ч
		void Enable();
		//! ʹ�ؼ���Ч
		void Disable();
		//! ��ʾ�ؼ�
		void Show();
		//! ���ؿؼ�
		void Hide();
		//! �ؼ�����ת��Ļ�����򴰿����꣩
		void ClientToScreen( POINT &p_Point ) const;
		//! ��Ļ�����򴰿ڣ�����ת�ؼ�����
		void ScreenToClient( POINT &p_Point ) const;
		//! �ж�һ���Ƿ��ڿؼ���
		bool IsPointIn( POINT p_Point ) const;
		//! ʹ�ؼ���ȡ����
		void SetFocus();
		//! �жϿؼ��Ƿ���Ч
		bool IsEnabled() const;
		//! �жϿؼ��Ƿ�ɼ�
		bool IsVisiable() const;
		//! �жϿؼ��Ƿ��ý���
		bool IsFocesed() const;
		//! ���ÿؼ��͸��ؼ�������
		void SetLeft( int p_nLeft );
		//! ���ÿؼ��͸��ؼ����˾���
		void SetTop( int p_nTop );
		//! ȡ�ؼ��ุ�ؼ�������
		int GetLeft() const;
		//! ȡ�ؼ��ุ�ؼ����˾���
		int GetTop() const;
		//! ���ÿؼ����
		void SetWidth( int p_nWidth );
		//! ���ÿؼ��߶�
		void SetHeight( int p_nHeight );
		//! ȡ�ؼ����
		int GetWidth() const;
		//! ȡ�ؼ��߶�
		int GetHeight() const;
		//! ���ÿؼ�����
		void SetFont( CFont &p_Font );
		//! ��ȡ�ؼ�����
		CFont* GetFont() const;
		//! ���ÿؼ�������ɫ
		void SetFontColor( CColor &p_Color );
		//! ��ȡ�ؼ�������ɫ
		CColor* GetColor() const;
		//! ���ÿؼ�����
		void SetCaption( const std::wstring& p_szCaption );
		//! ��ȡ�ؼ�����
		std::wstring GetCaption() const;
		//! ���ÿؼ����
		void SetZPos( ZPos p_nZPos );
		//! ���ؿؼ����
		ZPos GetZPos() const;
	public:
		//! �û��Զ����¼�������ָ��
		//@note ���д�������ָ��λ��������ڸ��ؼ��ģ����������Ļ��
		SNotifyEvent OnMouseEnter;
		SNotifyEvent OnMouseLeave;
		SMouseMoveEvent OnMouseMove;
		SMouseEvent OnMouseDown;
		SMouseEvent OnMouseUp;
		SKeyEvent OnKeyDown;
		SKeyEvent OnKeyUp;
		SKeyPressEvent OnKeyPress;
		SNotifyEvent OnEnter;
		SNotifyEvent OnLeave;

	protected:
		IGUIControl*				m_pParent;			// ���ؼ�ָ��
		int							m_nLeft;			// �ุ�ؼ�������
		int							m_nTop;				// �ุ�ؼ����˾���
		int							m_nWidth;			// ���
		int							m_nHeight;			// �߶�
		bool						m_bEnabled;			// �Ƿ���Ч
		bool						m_bVisible;			// �Ƿ�ɼ�
		bool						m_bFocused;			// �Ƿ��ý���
		CFont*						m_pFont;			// ����
		std::wstring				m_szCaption;		// ����
		std::list< IGUIControl* >	m_listChild;		// �ӿؼ�����
		CColor*						m_pColor;			// ������ɫ
		ZPos						m_dZpos;			// UI���
	};
	//--------------------------------------------------------------------
}