/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	MsgListener
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include <windows.h>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//! Windows��Ϣ��������
	//@remarks ��Windows��Ϣ����Ȥ������ɼ��ɱ��࣬ʵ�־������
	class IWinMsgListener
	{
	public:
		virtual ~IWinMsgListener()
		{

		};
	public:
		//! �ַ�Windows��Ϣ
		virtual void Distribute( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) = 0;
	};
}