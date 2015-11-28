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

#include "../include/WinUtility.h"
#include "../include/StringConversion.h"
#include <stdexcept>
#include <vector>

//--------------------------------------------------------------------
namespace
{
	typedef std::vector< boost::function< bool (MSG&) > >		VEC_HOOKS;
	VEC_HOOKS		g_Hooks;

	bool HandledByHook( MSG& p_Message )
	{
		for( VEC_HOOKS::iterator i = g_Hooks.begin(); i != g_Hooks.end(); ++i )
		{
			if( (*i)( p_Message ) )
			{
				return true;
			}
		}

		return false;
	}
}
//--------------------------------------------------------------------
HINSTANCE FK2DEngine::Win::Instance()
{
	return Check( ::GetModuleHandle(0), "��ȡӦ�ó���ʵ��" );
}
//--------------------------------------------------------------------
void FK2DEngine::Win::HandleMessage()
{
	MSG tagMessage;
	BOOL bRet = ::GetMessage( &tagMessage, 0, 0, 0 );

	switch( bRet )
	{
	case -1:
		{
			ThrowLastError( "��ȡ��һ����Ϣ" );
			break;
		}
	case 0:
		{
			break;
		}
	default:
		{
			// ���Ƚ�����ϢHook����֮���ٽ���Windowsϵͳ����
			if( !HandledByHook(tagMessage) )
			{
				::TranslateMessage( &tagMessage );
				::DispatchMessage( &tagMessage );
			}
		}
	}
}
//--------------------------------------------------------------------
void FK2DEngine::Win::ProcessMessage()
{
	MSG tagMessage;

	while( ::PeekMessage( &tagMessage, 0, 0, 0, PM_REMOVE ) )
	{
		if( !HandledByHook( tagMessage ) )
		{
			::TranslateMessage( &tagMessage );
			::DispatchMessage( &tagMessage );
		}
	}
}
//--------------------------------------------------------------------
void FK2DEngine::Win::RegisterMessageHook( const boost::function< bool (MSG&) >& p_Hook )
{
	g_Hooks.push_back( p_Hook );
}
//--------------------------------------------------------------------
FK_DECL_NORETURN void FK2DEngine::Win::ThrowLastError( const std::string& p_Action )
{
	char* pBuffer = NULL;
	if( ! ::FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		0, ::GetLastError(), MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), reinterpret_cast< LPSTR >(&pBuffer), 0, 0 ) 
		|| pBuffer == 0 )
	{
		throw std::runtime_error( "δ֪����" );
	}

	std::string szMessage;
	try
	{
		szMessage = pBuffer;
	}
	catch ( ... )
	{
		::LocalFree( pBuffer );
		throw;
	}
	::LocalFree( pBuffer );

	if( !p_Action.empty() )
	{
		szMessage = "���� " + p_Action + " ʱ���������д���" + szMessage;
	}

	throw std::runtime_error( szMessage );
}
//--------------------------------------------------------------------
std::wstring FK2DEngine::Win::AppFileName()
{
	static std::wstring szResult;

	if( ! szResult.empty() )
	{
		return szResult;
	}

	wchar_t szBuffer[ MAX_PATH * 2 ];
	Check( ::GetModuleFileName( 0, szBuffer, MAX_PATH * 2 ), "��ȡģ���ļ���" );
	
	szResult = std::wstring( szBuffer );
	return szResult;
}
//--------------------------------------------------------------------
std::wstring FK2DEngine::Win::AppDirectory()
{
	static std::wstring szResult;
	if( ! szResult.empty() )
	{
		return szResult;
	}

	szResult = AppFileName();

	std::wstring::size_type LastDelim = szResult.find_last_of( L"\\/" );
	if( LastDelim != std::wstring::npos )
	{
		szResult.resize( LastDelim + 1 );
	}
	else
	{
		szResult = L"";
	}
	return szResult;
}
//--------------------------------------------------------------------