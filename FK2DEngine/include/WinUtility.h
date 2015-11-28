/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	WinUtility
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include <Windows.h>
#include "Platform.h"
#include "../../depend/boost/function.hpp"
#include "../../depend/boost/shared_ptr.hpp"
#include <string>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	namespace Win
	{
		//! �������Ӧ�ó���ʵ��
		HINSTANCE	Instance();

		void		HandleMessage();

		void		ProcessMessage();

		void		RegisterMessageHook( const boost::function< bool (MSG&) >& p_Hook );

		FK_DECL_NORETURN void ThrowLastError( const std::string& p_Action = "" );

		template< typename T >
		inline T Check( T p_ValueToCheck, const std::string& p_Action = "" )
		{
			if( !p_ValueToCheck )
			{
				ThrowLastError( p_Action );
			}
			return p_ValueToCheck;
		}

		template< typename T >
		void ReleaseComPtr( T* p_Ptr )
		{
			p_Ptr->Release();
		}

		//! 
		template< typename T >
		inline boost::shared_ptr< T > ShareComPtr( T* p_Ptr )
		{
			return boost::shared_ptr< T >( p_Ptr, ReleaseComPtr< T > );
		}

		//! ��ȡִ�г�����ļ���
		std::wstring AppFileName();

		//! ��ȡִ�г������ڵ�Ŀ¼
		std::wstring AppDirectory();
	}
}