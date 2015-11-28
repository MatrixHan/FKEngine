/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	MsgListenerManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "MsgListener.h"
#include "Singleton.h"
#include <list>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	class CWinMsgListenerManager 
	{ 
		typedef std::list< IWinMsgListener* >		MsgListenerList;
	public:
		CWinMsgListenerManager();
		~CWinMsgListenerManager();
	public:
		void Add( IWinMsgListener* p_pListener );
		void Remove( IWinMsgListener* p_pListener );
		void Distribute( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	private:
		MsgListenerList		m_listMsgListener;

		DECLARE_SINGLETON_CLASS( CWinMsgListenerManager );
	};
}

typedef FK2DEngine::TSingleton< FK2DEngine::CWinMsgListenerManager >		SSWinMsgListenerMgr;