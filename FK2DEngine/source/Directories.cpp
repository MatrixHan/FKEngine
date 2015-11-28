/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Directories
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../include/Directories.h"
#include "../include/WinUtility.h"
#include <cwchar>
#include <stdexcept>
#include <ShlObj.h>

//--------------------------------------------------------------------
namespace
{
	std::wstring SpecialFolderPath( int p_nCsidl )
	{
		WCHAR szBuf[ MAX_PATH + 2 ];
		if( !SHGetSpecialFolderPath( 0, szBuf, p_nCsidl, TRUE ) )
		{
			throw std::runtime_error( "��ȡ�ļ���·��ʧ��" );
		}
		std::size_t unLen = std::wcslen( szBuf );
		if( szBuf[unLen - 1] != '\\' )
		{
			szBuf[unLen] = L'\\';
			szBuf[unLen + 1] = L'\0';
		}
		return szBuf;
	}
}
//--------------------------------------------------------------------
std::wstring FK2DEngine::ResourcePrefix()
{
	return Win::AppDirectory();
}
//--------------------------------------------------------------------
std::wstring FK2DEngine::ShareResourcePrefix()
{
	return Win::AppDirectory();
}
//--------------------------------------------------------------------
std::wstring FK2DEngine::UserSettingPrefix()
{
	return SpecialFolderPath( CSIDL_APPDATA );
}
//--------------------------------------------------------------------
std::wstring FK2DEngine::UserDocsPrefix()
{
	return SpecialFolderPath( CSIDL_PERSONAL );
}
//--------------------------------------------------------------------