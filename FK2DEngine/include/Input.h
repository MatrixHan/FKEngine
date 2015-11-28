/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Input
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
#include "../../depend/boost/function.hpp"
#include "../../depend/boost/scoped_ptr.hpp"
#include <vector>
//--------------------------------------------------------------------
#ifdef FK_WINDOWS
	#include "WinKey.h"
		#ifndef NOMINMAX
		#define NOMINMAX
		#endif
	#include <Windows.h>
#endif
//--------------------------------------------------------------------
#ifdef FK_MAC
	#include "MacKey.h"
#endif
//--------------------------------------------------------------------
#ifdef FK_X
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
	#include <X11/keysym.h>
	#include "XKey.h"
#endif
//--------------------------------------------------------------------

namespace FK2DEngine
{
	//--------------------------------------------------------------------
	class CKey
	{
	private:
		unsigned int		m_unID;
	public:
		explicit CKey( unsigned int p_unID )
			: m_unID( p_unID )
		{

		}

		unsigned int ID() const
		{
			return m_unID;
		}

		CKey()
			: m_unID( NoButton )
		{

		}

		CKey( ENUM_KeyName p_eName )
			: m_unID( p_eName )
		{

		}
	};

	inline bool operator == ( CKey p_Left, CKey p_Right )
	{
		return ( p_Left.ID() == p_Right.ID() );
	}
	inline bool operator != ( CKey p_Left, CKey p_Right )
	{
		return !( p_Left == p_Right );
	}
	inline bool operator < ( CKey p_Left, CKey p_Right )
	{
		return ( p_Left.ID() < p_Right.ID() );
	}

	//--------------------------------------------------------------------
	struct STouch
	{
		void*		m_pID;
		// ��������X,Y����
		float		m_fX;
		float		m_fY;
	};

	typedef std::vector< STouch >		VEC_Touches;
	//--------------------------------------------------------------------
	class CInput
	{
	private:
		struct SImpl;
		boost::scoped_ptr< SImpl >			m_pImpl;
	public:
		#ifdef FK_WINDOWS
			CInput( HWND p_hWnd );
		#endif

		#ifdef FK_MAC
			#ifdef FK_IPHONE
				CInput( void* p_pView, float p_fUpdateInterval );
				void FeedTouchEvent( int p_nType, void* p_pTouches );
			#else
				CInput( void* p_pWindow );
				bool FeedNSEvent( void* p_pEvent );
			#endif
		#endif

		#ifdef FK_X
			CInput( ::Display* p_pDisplay, ::Window p_Wnd );
			bool FeedXEvent( ::XEvent& p_Event );
		#endif
	public:
		~CInput();

		static wchar_t	IDToChar( CKey p_Key );
		static CKey		CharToID( wchar_t p_Char );
		static wchar_t	IDToChar( unsigned int p_unKey );

		//! �ж�һ�����Ƿ���( Ҫ��ÿ֡���м�� )
		bool Down( CKey p_Key ) const;

		//! ��������λ��
		double MouseX() const;
		double MouseY() const;

		//! �������λ�ã������������꣩
		void SetMousePosition( double p_dX, double p_dY );
		//! �������λ�ã��ٷֱȣ�
		void SetMouseFactors( double p_dFactorX, double p_dFactorY );

		//! ��ǰ������¼
		const VEC_Touches& CurrentTouches() const;

		//! �ƶ����ٶ�
		double AccelerometerX() const;
		double AccelerometerY() const;
		double AccelerometerZ() const;

		//! ÿ֡�ĸ���
		void Update( float p_fDelta );

		//! ���ص�ǰ������� TextInput ʵ������û�У��򷵻� NULL
		CTextInput* TextInput() const;
		//! ���õ�ǰ������� TextInput ʵ����������Ϊ NULL�����ʾ���
		void SetTextInput( CTextInput* p_pTextInput );
	
		//! ÿ֡�Ļص�,��Update�б�����
		boost::function< void( CKey ) >  OnButtonDown;
		boost::function< void( CKey ) >	 OnButtonUp;

		boost::function< void( STouch ) >	OnTouchBegin;
		boost::function< void( STouch ) >	OnTouchEnded;
		boost::function< void( STouch ) >	OnTouchMoved;
	};
}