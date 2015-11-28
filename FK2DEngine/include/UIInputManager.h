/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	UIInputManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//-----------------------------------------------------------------------------
#include "Singleton.h"
#include <queue>
#include <Windows.h>
//-----------------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	#define BUF_SIZE 256
	//--------------------------------------------------------------------
	// ���ܼ�״̬�ṹ����
	struct SShiftState
	{
		bool m_bCtrlDown;
		bool m_bShiftDown;
		bool m_bAltDown;
	};

	// ��갴ťö�ٶ���
	enum ENUM_MouseButton
	{
		eMB_Left,
		eMB_Right,
		eMB_Middle
	};
	//-----------------------------------------------------------------------------
	//! ר�Ÿ���UI��Ϣ�Ĺ�����
	class CGUIInputManager
	{
	public:
		CGUIInputManager();
		~CGUIInputManager()
		{

		}
	public:
		//! ��ʼ������
		void Init( HWND p_hWnd );
		//! ��Ϣ������
		void MsgProc( UINT p_Msg, WPARAM p_wParam, LPARAM p_lParam );
		//! ���º���
		void Update( float p_fDelta );
	public:
		//! ��ȡ��һ֡�󱻰��µļ�
		std::queue< unsigned int >	GetKeyDown();
		//! ��ȡ��һ֡���ɿ��ļ�
		std::queue< unsigned int >	GetKeyUp();
		//! ��ȡ��һ֡��õ����ַ�
		std::queue< char >			GetKeyChar();
		//! ��ȡ���ܼ�״̬
		SShiftState					GetShiftState();
		//! ��ȡ��갴ť״̬
		bool						GetMouseState( ENUM_MouseButton p_eMB );
		//! ��ȡ���λ��
		POINT						GetMousePos();
		//! ָ�����Ƿ�ձ�����
		bool						IsKeyJustDown( unsigned int p_dwKey );
		//! ָ�����Ƿ�ձ��ɿ�
		bool						IsKeyJustUp( unsigned int p_dwKey );
		//! ����Ƿ�ձ�����
		bool						IsMouseJustDown( ENUM_MouseButton p_eMB );
		//! ����Ƿ�ձ��ɿ�
		bool						IsMouseJustUp( ENUM_MouseButton p_eMB );
		//! ����Ƿ��ƶ�
		bool						IsMouseMoved();
		//! ȡ���X����
		int							GetMousePosX();
		//! ȡ���Y����
		int							GetMousePosY();
	private:
		std::queue< unsigned int >			m_QueueKeyDown;					// ���ϴ�Update()�󱻰��µļ�
		std::queue< unsigned int >			m_QueueKeyUp;					// ���ϴ�Update()���ɿ��ļ�
		std::queue< char >					m_QueueChar;					// ���ϴ�Update()��õ����ַ�����	
		std::queue< unsigned int >			m_QueueKeyDownSave;				// ���ϴ�Update()�󱻰��µļ�
		std::queue< unsigned int >			m_QueueKeyUpSave;				// ���ϴ�Update()���ɿ��ļ�
		std::queue< char >					m_QueueCharSave;				// ���ϴ�Update()��õ����ַ�����	
		SShiftState							m_ShiftState;					// ���ܼ�״̬
		BYTE								m_vKeyState[BUF_SIZE];			// ���̻���
		BYTE								m_vKeyStateOld[BUF_SIZE];		// ǰ�μ��̻���
		POINT								m_MousePos;						// ���λ��
		POINT								m_MousePosOld;					// ǰ�����λ��
		HWND								m_hWnd;							// ���ھ��
	private:
		DECLARE_SINGLETON_CLASS( CGUIInputManager );
	};
}

typedef FK2DEngine::TSingleton< FK2DEngine::CGUIInputManager >	SSGUIInputManager;