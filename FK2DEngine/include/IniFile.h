/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	IniFile
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include <list>
#include <vector>
#include "Exception.h"
#include <Windows.h>

//--------------------------------------------------------------------
// ȥ���� Exception ǿ��Ҫ�� int���� �׳��ľ��档
#pragma warning( disable : 4290 )
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	class CFileDataStream;
	//--------------------------------------------------------------------
	class CIniException
	{
	public:
		CIniException(const std::wstring& szFileName, const std::wstring& szKey)
		{ wsprintf(m_szMessage, L"Ini�ļ� %s ��ֵ %s ��ȡʧ��", szFileName, szKey); }

		virtual wchar_t* GetErrorMessage(void) const
		{ return const_cast< wchar_t* >( &m_szMessage[0] ); }

	private:
		wchar_t m_szMessage[128];
	};
	//--------------------------------------------------------------------
	//! Ini�ඨ��
	class CIniFile
	{
	private:
		//! ����Ϣ�ṹ
		struct SSectionInfo
		{
			std::wstring							m_szName;			// ����
			std::list< std::wstring >::iterator		m_ItePos;			// ���������е�λ��
		};

		typedef std::list< std::wstring >			List;				// ���string������
		typedef std::list< std::wstring >::iterator ListIter;			// �α�
		typedef std::vector< SSectionInfo >			VecSecInfo;			// ����Ϣ����

	public:
		CIniFile();
		~CIniFile();
		
		//! ����Ini�ļ�
		void Load( CFileDataStream* p_pFile );
		//! ����Ini�ļ�
		void Save( const std::wstring& p_szFileName );
		//! ���õ�ǰ��
		void SetSection( const std::wstring& p_szSection );

	public:		// ����Ϣ����
		std::wstring ReadString(const std::wstring& szSection, const std::wstring& szKey, const std::wstring& szDefault);
		std::wstring ReadString(const std::wstring& szKey, const std::wstring& szDefault);
		std::wstring SafeReadString(const std::wstring& szSection, const std::wstring& szKey) throw(CIniException);
		std::wstring SafeReadString(const std::wstring& szKey) throw(CIniException);
		int ReadInteger(const std::wstring& szSection, const std::wstring& szKey, int nDefault);
		int ReadInteger(const std::wstring& szKey, int nDefault);
		int SafeReadInteger(const std::wstring& szSection, const std::wstring& szKey) throw( CIniException );
		int SafeReadInteger(const std::wstring& szKey) throw(CIniException);
		double ReadFloat(const std::wstring& szSection, const std::wstring& szKey, double lfDefault);
		double ReadFloat(const std::wstring& szKey, double lfDefault);
		double SafeReadFloat(const std::wstring& szSection, const std::wstring& szKey) throw(CIniException);
		double SafeReadFloat(const std::wstring& szKey) throw(CIniException);
		bool ReadBoolean(const std::wstring& szSection, const std::wstring& szKey, bool bDefault);
		bool ReadBoolean(const std::wstring& szKey, bool bDefault);
		bool SafeReadBoolean(const std::wstring& szSection, const std::wstring& szKey) throw(CIniException);
		bool SafeReadBoolean(const std::wstring& szKey) throw(CIniException);

		// д��Ϣ����
	public:
		void WriteString(const std::wstring& szSection, const std::wstring& szKey, const std::wstring& szValue);
		void WriteString(const std::wstring& szKey, const std::wstring& szValue);
		void WriteInteger(const std::wstring& szSection, const std::wstring& szKey, int nValue);
		void WriteInteger(const std::wstring& szKey, int nValue);
		void WriteFloat(const std::wstring& szSection, const std::wstring& szKey, double lfValue);
		void WriteFloat(const std::wstring& szKey, double lfValue);
		void WriteBoolean(const std::wstring& szSection, const std::wstring& szKey, bool bValue);
		void WriteBoolean(const std::wstring& szKey, bool bValue);

	private:
		List					m_lData;					// �ļ���������
		VecSecInfo				m_vecSection;				// ����Ϣ����
		int						m_nCurSection;				// ��ǰ��
		std::wstring			m_szFileName;				// �ļ���
	};
}