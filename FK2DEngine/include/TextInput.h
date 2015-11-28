/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	TextInput
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
#include "../../depend/boost/scoped_ptr.hpp"
#include <string>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	class CTextInput
	{
		struct		SImpl;
	private:
		boost::scoped_ptr< SImpl >		m_pImpl;
	public:
		CTextInput();
		virtual ~CTextInput();
	public:
		std::wstring Text() const;
		void SetText( const std::wstring& p_szText );

		unsigned int CarePos() const;
		void SetCarePos( unsigned int p_unPos );

		unsigned int SelectionStart() const;
		void SetSelectionStart( unsigned int p_unPos );

		#if defined( FK_MAC )
			bool FeedNSEvent( void* p_pEvent );
		#elif defined ( FK_WINDOWS )
			bool FeedMessage( unsigned long p_ulMessage, unsigned long p_wParam, unsigned long p_lParam );
		#elif defined ( FK_X )
			bool FeedXEvent( void* p_pDisplay, void* p_pEvent );
		#endif

		virtual std::wstring Filter( const std::wstring& p_TextIn ) const
		{
			return p_TextIn;
		}
	};
}