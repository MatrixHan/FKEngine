/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	LogManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "Log.h"
#include "Singleton.h"
#include <map>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	class CLogManager
	{
		friend class CLog;

		typedef std::map< std::wstring, CLog*, std::less< std::wstring > >		LogList;
	private:
		LogList			m_Logs;
		CLog*			m_pDefaultLog;
	public:
		CLogManager();
		~CLogManager();
	public:
		//! ������־
		//@params [IN] p_bDefaultLog �Ƿ�����ΪĬ��Log�ļ���������Ĭ��Log�ļ�����������Ч
		//@params
		//@params [IN] p_bSuppressFile �Ƿ��ֹ�ļ������true �����Log�ļ�
		CLog* CreateLog( const std::wstring& p_szName, bool p_bDefaultLog = false,
			bool p_bDebugOutput = true, bool p_bSuppressFile = false );

		//! ͨ�����ƻ�ȡ���������־����ָ��
		CLog* GetLog( const std::wstring& p_szName );

		//! ��ȡĬ�ϵ���־����ָ��
		CLog* GetDefaultLog() const;

		//! ����Ĭ�ϵ���־����ָ��
		//@returns ����ԭ����Ĭ����־����ָ��
		CLog* SetDefaultLog( CLog* p_pNewLog );

		//! д��־
		void LogMessage( const std::wstring& p_szMsg, ENUM_LogMessageLevel p_eLML = eLML_Normal, 
			bool p_bMaskDebug = false );

		//! ������־ϵͳ�ȼ�
		void SetLogDetail( ENUM_LogLevel p_eLL );
	private:
		DECLARE_SINGLETON_CLASS( CLogManager );
	};
}

typedef FK2DEngine::TSingleton< FK2DEngine::CLogManager >	SSLogManager;