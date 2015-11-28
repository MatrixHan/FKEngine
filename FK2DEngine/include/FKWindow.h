/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	FKWindow
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "InsidePreInclude.h"
#include "Platform.h"
#include "Input.h"
#include "../../depend/boost/scoped_ptr.hpp"
#include "../../depend/boost/shared_ptr.hpp"
#include "../../depend/boost/function.hpp"
#include <string>
//--------------------------------------------------------------------
#ifdef FK_WINDOWS
	#ifndef NOMINMAX
		#define NOMINMAX
	#endif
#include <windows.h>
#endif
//--------------------------------------------------------------------
namespace FK2DEngine
{
	class CFKWindow
	{
		struct			SImpl;
	private:
		boost::scoped_ptr< SImpl >		m_pImpl;
	public:
		CFKWindow( unsigned int p_unWidth, unsigned int p_unHeight, bool p_bFullScreen, double p_dUpdateInterval = 16.666666 );
		virtual ~CFKWindow();
		//--------------------------------------------------------------------
		// �����߼�����
		//--------------------------------------------------------------------
	public:
		double UpdateInterval() const;

		void Show();
		bool Close();
		//--------------------------------------------------------------------
		// �����Ժ���
		//--------------------------------------------------------------------
	public:
		std::wstring Caption() const;
		void SetCaption( const std::wstring& p_szCaption );
		// ���þ�̬���
		void SetNewCursor( const std::wstring& p_lpCursorName );
		// ��������
		void PrintScreen( const std::wstring& p_lpDestName );
		// ��ȡʱ��
		unsigned int GetTime() const;
		// ��ȡ��Ⱦ���ڿ��
		unsigned int GetScreenWidth() const;
		// ��ȡ��Ⱦ���ڸ߶�
		unsigned int GetScreenHeight() const;
		// ���ñ�����ɫ
		void SetBackgroudColor( CColor p_Color );
		//--------------------------------------------------------------------
		// �����Ժ���
		//--------------------------------------------------------------------
	public:
		virtual void Update( float p_fDelta )
		{

		}
		virtual void FKDraw()
		{
			
		}
		virtual bool NeedsReDraw() const 
		{
			return true;
		}
		virtual bool NeedsCursor() const
		{
			return true;
		}
		virtual void LoseFocus() const
		{

		}
		virtual void ReleaseMemory() const
		{

		}
		virtual void KeyDown( FK2DEngine::CKey )
		{

		}
		virtual void KeyUp( FK2DEngine::CKey )
		{

		}
		//! �ر�����
		//@return ����false�����٣�����true���������
		virtual bool OnClose()
		{
			return true;
		}
#ifndef SWIG

		const CGraphics&	Graphics() const;
		CGraphics&			Graphics();
		const CInput&		Input() const;
		CInput&				Input();
		const CAudio&		Audio() const;
		CAudio&				Audio();

		#ifdef FK_WINDOWS
			HWND Handle() const;
			virtual LRESULT HandleMessage( UINT p_unMessage, WPARAM p_wParam, LPARAM p_lParam );
		#endif

		#ifdef FK_UNIX
			typedef boost::shared_ptr< boost::function< void() > >	SharedContext;
			SharedContext CreateSharedContext();
		#endif

#ifdef FK_IPHONE
	virtual void TouchBegin( STouch p_Touch )
	{

	}
	virtual void TouchMoved( STouch p_Touch )
	{

	}
	virtual void TouchEnded( STouch p_Touch )
	{

	}
#endif
#endif

	};
}