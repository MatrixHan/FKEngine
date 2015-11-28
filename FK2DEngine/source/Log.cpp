/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Log
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../include/Log.h"
#include "../include/LogManager.h"
#include <iomanip>
#include <time.h>

//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	CLog::CLog( const std::wstring& p_szName, bool p_bDebugOutput /* = true */, bool p_bSuppressFile /* = false */ )
		: m_eLogLevel( eLL_Normal )
		, m_bDebugOut( p_bDebugOutput )
		, m_bSuppressFile( p_bSuppressFile )
		, m_szName( p_szName )
	{
		if( !m_bSuppressFile )
		{
			m_fpLog.open( m_szName.c_str() );
			// ��������֧��
			m_fpLog.imbue(std::locale("chs"));
		}
	}
	//--------------------------------------------------------------------
	CLog::~CLog()
	{
		if( !m_bSuppressFile )
		{
			m_fpLog.close();
		}
	}
	//--------------------------------------------------------------------
	void CLog::SetLogDetail( ENUM_LogLevel p_eLL )
	{
		m_eLogLevel = p_eLL;
	}
	//--------------------------------------------------------------------
	void CLog::LogMessage( const std::wstring& p_szMsg, 
		ENUM_LogMessageLevel p_eLML /* = eLML_Normal */, bool p_bMaskDebug /* = false */ )
	{
		if( m_eLogLevel + p_eLML >= LOG_THRESHOLD )
		{
			if( m_bDebugOut && !p_bMaskDebug )
			{
				std::wcerr << p_szMsg << std::endl;
			}

			if( !m_bSuppressFile )
			{
				struct tm* pTime;
				time_t ctTime;
				::time( &ctTime );
				pTime = localtime( &ctTime );

				m_fpLog << std::setw(2) << std::setfill( L'0') << pTime->tm_hour
					<< L":" << std::setw(2) << std::setfill(L'0') << pTime->tm_min
					<< L":" << std::setw(2) << std::setfill(L'0') << pTime->tm_sec
					<< L"  ----  " << p_szMsg << std::endl;

				m_fpLog.flush();
			}
		}
	}
	//--------------------------------------------------------------------
}