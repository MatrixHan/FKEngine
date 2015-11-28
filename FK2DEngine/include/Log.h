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

#pragma once

//--------------------------------------------------------------------
#include <string>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//! ��־��Ҫ�ȼ�
	enum ENUM_LogLevel
	{
		eLL_Low			=	1,
		eLL_Normal		=	2,
		eLL_BoreMe		=	3,
	};

	//! ��־��Ϣ�ȼ�
	enum ENUM_LogMessageLevel
	{
		eLML_Trivial	=	1,		// ��΢��Ϣ
		eLML_Normal		=	2,		// ��ͨ�ȼ�
		eLML_Critical	=	3,		// ������Ϣ
	};

	//! ��� LogMessageLevel + LogLevel > LOG_THRESHOLD�����¼����־�ļ���
	#define LOG_THRESHOLD 4

	class CLog
	{
		friend class CLogManager;
	private:
		//! ��ʹ��CLogManager����
		//@param	[IN] p_bDebugOutput	�Ƿ�������
		//@param	[IN] p_bSuppressFile �Ƿ��ֹд�ļ�
		CLog( const std::wstring& p_szName, bool p_bDebugOutput = true, bool p_bSuppressFile = false );

		~CLog();
	public:
		//! д��־
		void LogMessage( const std::wstring& p_szMsg, ENUM_LogMessageLevel p_eLML = eLML_Normal, 
			bool p_bMaskDebug = false );

		//! ������־ϵͳ�ȼ�
		void SetLogDetail( ENUM_LogLevel p_eLL );
	protected:
		std::wofstream		m_fpLog;		// �ļ���
		ENUM_LogLevel		m_eLogLevel;	// ��־ϵͳ�ȼ�
		bool				m_bDebugOut;	// �Ƿ���־д������̨
		bool				m_bSuppressFile;// �Ƿ��ֹ����־д���ļ�
		std::wstring		m_szName;		// ��־�ļ���
	};
}