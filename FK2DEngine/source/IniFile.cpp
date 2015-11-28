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

#include "../include/IniFile.h"
#include "../include/Exception.h"
#include "../include/FileDataStream.h"
#include <algorithm>
#include <functional>
#include <vector>

//--------------------------------------------------------------------
#pragma warning( disable : 4290 )
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	CIniFile::CIniFile()
		: m_nCurSection( -1 )
	{

	}
	//--------------------------------------------------------------------
	CIniFile::~CIniFile()
	{
		
	}
	//--------------------------------------------------------------------
	void CIniFile::Load( CFileDataStream* p_pFile )
	{
		FKAssert( p_pFile != NULL, "INI�ļ��������ȡ���ļ���" );

		std::wstring::size_type Pos, Pos2;
		SSectionInfo si;

		// ���ж�ȡ�ļ�������������
		std::wstring szLineBuffer;
		while( ! (szLineBuffer = p_pFile->GetLine()).empty() )
		{
			m_lData.push_back( szLineBuffer );
		}

		// ��ȡ�ļ���
		m_szFileName = p_pFile->GetName();

		// ɾ���ļ�
		if( p_pFile != NULL )
		{
			delete p_pFile;
			p_pFile = NULL;
		}

		// ��¼���ж�λ��
		for( ListIter it = m_lData.begin(); it != m_lData.end(); ++it )
		{
			// ȥ��ǰ���հ�
			Pos = ( *it ).find_first_not_of( ' ' );

			// �հ��У�ֱ������
			if( Pos == std::wstring::npos )
			{
				continue;
			}

			// ���Ҷ�
			if( (*it)[Pos] == '[' )
			{
				Pos2 = (*it).find( ']', Pos );

				// �ҵ���һ����
				if( Pos2 != std::wstring::npos )
				{
					si.m_szName	= (*it).substr( Pos + 1, Pos2 - Pos - 1 );
					si.m_ItePos = it;
					si.m_ItePos++;
					m_vecSection.push_back( si );
				}
			}
		}

		m_nCurSection = m_vecSection.size() > 0 ? 0 : -1;
	}
	//--------------------------------------------------------------------
	void CIniFile::Save( const std::wstring& p_szFileName )
	{
		FILE* fp = _wfopen( p_szFileName.c_str(), L"wt" );
		if( fp == NULL )
		{
			FK_EXCEPTION( CException::eEC_ErrorInternal, L"����INI�ļ�ʧ��", L"CIniFile::Save" );
		}
		for( ListIter it = m_lData.begin(); it != m_lData.end(); ++it )
		{
			const wchar_t*  str = (*it).c_str();
			fwprintf( fp, L"%s\n", str );
		}

		fclose( fp );
	}
	//--------------------------------------------------------------------
	void CIniFile::SetSection( const std::wstring& p_szSection )
	{
		// ���Ҷ�
		for( unsigned int i = 0; i < m_vecSection.size(); ++i )
		{
			if( m_vecSection[i].m_szName == p_szSection )
			{
				m_nCurSection = i;
				return;
			}
		}

		// ����ʧ�ܣ���β������һ���¶�
		std::wstring strSection = L"[";
		strSection += p_szSection;
		strSection += L"]";
		m_lData.push_back( strSection );

		// ���¶���Ϣ�������Ϣ������
		SSectionInfo si;
		si.m_szName	= p_szSection;
		si.m_ItePos	= m_lData.end();
		m_vecSection.push_back( si );

		m_nCurSection = static_cast< int >( m_vecSection.size() - 1 );
	}
	//--------------------------------------------------------------------
	std::wstring CIniFile::ReadString(const std::wstring& szSection,
		const std::wstring& szKey, const std::wstring& szDefault)
	{
		SetSection( szSection );
		return ReadString( szKey, szDefault );
	}	
	//--------------------------------------------------------------------
	bool IsNotSpace( char p_Char )
	{
		return ((p_Char != ' ') && (p_Char != '\t'));
	}
	//--------------------------------------------------------------------
	std::wstring CIniFile::ReadString(const std::wstring& szKey, const std::wstring& szDefault)
	{
		FKAssert( m_nCurSection >= 0, L"���ܶԿ��ļ���ȡ�ַ���" );

		std::wstring str;
		ListIter it = m_vecSection[m_nCurSection].m_ItePos;

		while( it != m_lData.end() )
		{
			std::wstring::size_type Pos;

			// ȥ��ǰ���հ�
			Pos = ( *it ).find_first_not_of( ' ' );

			// �հ��У�ֱ������
			if( Pos == std::wstring::npos )
			{
				++it;
				continue;
			}

			// ���Ҷ�
			if( (*it)[Pos] == '[' )
			{
				return szDefault;
			}

			// ���Ҽ���
			if( (*it).substr( Pos, szKey.length() ) == szKey )
			{
				Pos += szKey.length();

				// ȥ���Ⱥ�ǰ�հ�
				Pos = (*it).find_first_not_of( ' ', Pos );

				// �ȺŴ��ڣ����ҵ�ָ����
				if( (Pos != std::wstring::npos) && ((*it)[Pos] == '=') )
				{
					++Pos;

					if( (*it)[Pos] != '\0' )
					{
						// ȥ���Ⱥź�հ�
						Pos = (*it).find_first_not_of( ' ', Pos );

						if( Pos != std::wstring::npos )
						{
							str = (*it).substr( Pos );

							// ȥ���ַ���β���հ�
							str.erase( find_if( str.rbegin(), str.rend(),
								std::ptr_fun( IsNotSpace )).base(), str.end() );

							return str;
						}
					}

					str = szDefault;
					return str;
				}
			}

			++it;
		}

		str = szDefault;
		return str;
	}	
	//--------------------------------------------------------------------
	std::wstring CIniFile::SafeReadString(const std::wstring& szSection,
		const std::wstring& szKey) throw(CIniException)
	{
		SetSection( szSection );
		return SafeReadString( szKey );
	}	
	//--------------------------------------------------------------------
	std::wstring CIniFile::SafeReadString(const std::wstring& szKey) throw(CIniException)
	{
		std::wstring str = ReadString( szKey, L"\n\n" );
		if( str != L"\n\n" )
		{
			return str;
		}
		else
		{
			throw CIniException(m_szFileName, szKey);
		}
	}
	//--------------------------------------------------------------------
	int CIniFile::ReadInteger(const std::wstring& szSection, const std::wstring& szKey, int nDefault)
	{
		SetSection( szSection );
		return ReadInteger( szKey, nDefault );
	}
	//--------------------------------------------------------------------
	int CIniFile::ReadInteger(const std::wstring& szKey, int nDefault)
	{
		std::wstring str = ReadString( szKey, L"" );
		if( str == L"" )
		{
			return nDefault;
		}
		else
		{
			return atoi( WstringToUTF8( str ).c_str() );
		}
	}
	//--------------------------------------------------------------------
	int CIniFile::SafeReadInteger(const std::wstring& szSection,
		const std::wstring& szKey) throw( CIniException )
	{
		SetSection( szSection );
		return SafeReadInteger( szKey );
	}
	//--------------------------------------------------------------------
	int CIniFile::SafeReadInteger(const std::wstring& szKey) throw(CIniException)
	{
		std::wstring str = SafeReadString( szKey );
		if( str != L"" )
		{
			return atoi( WstringToUTF8( str ).c_str() );
		}
		else
		{
			throw CIniException(m_szFileName, szKey);
		}
	}
	//--------------------------------------------------------------------
	double CIniFile::ReadFloat(const std::wstring& szSection, const std::wstring& szKey, double lfDefault)
	{
		SetSection(szSection);
		return ReadFloat(szKey, lfDefault);
	}
	//--------------------------------------------------------------------
	double CIniFile::ReadFloat(const std::wstring& szKey, double lfDefault)
	{
		std::wstring str = ReadString(szKey, L"");
		if (str == L"")
		{
			return lfDefault;
		}
		else
		{
			return atof( WstringToUTF8( str ).c_str() );
		}
	}
	//--------------------------------------------------------------------
	double CIniFile::SafeReadFloat(const std::wstring& szSection,
		const std::wstring& szKey) throw(CIniException)
	{
		SetSection(szSection);
		return SafeReadFloat(szKey);
	}
	//--------------------------------------------------------------------
	double CIniFile::SafeReadFloat(const std::wstring& szKey) throw(CIniException)
	{
		std::wstring str = SafeReadString( szKey );
		if( str != L"" )
		{
			return atof( WstringToUTF8( str ).c_str() );
		}
		else
		{
			throw CIniException(m_szFileName, szKey);
		}
	}
	//--------------------------------------------------------------------
	bool CIniFile::ReadBoolean(const std::wstring& szSection, const std::wstring& szKey, bool bDefault)
	{
		SetSection(szSection);
		return ReadBoolean(szKey, bDefault);
	}
	//--------------------------------------------------------------------
	bool CIniFile::ReadBoolean(const std::wstring& szKey, bool bDefault)
	{
		std::wstring str = ReadString(szKey, L"");
		if (str[0] == '1')
		{
			return true;
		}
		else if (str[0] == '0')
		{
			return false;
		}
		else
		{
			return bDefault;
		}
	}
	//--------------------------------------------------------------------
	bool CIniFile::SafeReadBoolean(const std::wstring& szSection,
		const std::wstring& szKey) throw(CIniException)
	{
		SetSection(szSection);
		return SafeReadBoolean(szKey);
	}
	//--------------------------------------------------------------------
	bool CIniFile::SafeReadBoolean(const std::wstring& szKey) throw(CIniException)
	{
		std::wstring str = SafeReadString( szKey );
		if( str[0] == '1' )
		{
			return true;
		}
		else if( str[0] == '0' )
		{
			return false;
		}
		else
		{
			throw CIniException( m_szFileName, szKey );
		}
	}
	//--------------------------------------------------------------------
	void CIniFile::WriteString(const std::wstring& szSection,
		const std::wstring& szKey, const std::wstring& szValue)
	{
		SetSection(szSection);
		WriteString(szKey, szValue);
	}
	//--------------------------------------------------------------------
	void CIniFile::WriteString(const std::wstring& szKey, const std::wstring& szValue)
	{
		FKAssert( m_nCurSection >= 0 , L"WriteString������д����ַ���" );

		ListIter it = m_vecSection[ m_nCurSection ].m_ItePos;
		std::wstring strWrite = szKey;
		strWrite += L"=";
		strWrite += szValue;

		while( it != m_lData.end() )
		{
			std::wstring::size_type Pos;

			// ȥ��ǰ���հ�
			Pos = (*it).find_first_not_of( ' ' );

			// �հ��У�ֱ������
			if( Pos == std::wstring::npos )
			{
				++it;
				continue;
			}

			// �ѵ��¸��Σ�����ʧ��
			if( (*it)[Pos] == '[' )
			{
				// �½�һ���Σ�����
				m_lData.insert( m_vecSection[m_nCurSection].m_ItePos, strWrite );
				return;
			}

			// ���Ҽ���
			if( (*it).substr( Pos, szKey.length() ) == szKey )
			{
				Pos += szKey.length();

				// ȥ���Ⱥ�ǰ�հ�
				Pos = (*it).find_first_not_of( ' ', Pos );

				// �ȺŴ��ڣ��Ѿ��ҵ�ָ����
				if(( Pos != std::wstring::npos ) && ( (*it)[Pos] == '=' ))
				{
					(*it) = strWrite;
					return;
				}
			}

			++it;
		}

		// ����βҲû�ҵ����½�һ����
		m_lData.insert( m_vecSection[m_nCurSection].m_ItePos, strWrite );
	}
	//--------------------------------------------------------------------
	void CIniFile::WriteInteger(const std::wstring& szSection, const std::wstring& szKey, int nValue)
	{
		SetSection(szSection);
		WriteInteger(szKey, nValue);
	}
	//--------------------------------------------------------------------
	void CIniFile::WriteInteger(const std::wstring& szKey, int nValue)
	{
		wchar_t szBuffer[20];
		wsprintf( szBuffer, L"%d", nValue );
		WriteString( szKey, szBuffer );
	}
	//--------------------------------------------------------------------
	void CIniFile::WriteFloat(const std::wstring& szSection, const std::wstring& szKey, double lfValue)
	{
		SetSection( szSection );
		WriteFloat( szKey, lfValue );
	}
	//--------------------------------------------------------------------
	void CIniFile::WriteFloat(const std::wstring& szKey, double lfValue)
	{
		wchar_t szBuffer[20];
		wsprintf( szBuffer, L"%lf", lfValue );
		WriteString( szKey, szBuffer );
	}
	//--------------------------------------------------------------------
	void CIniFile::WriteBoolean(const std::wstring& szSection, const std::wstring& szKey, bool bValue)
	{
		SetSection( szSection );
		WriteFloat( szKey, bValue );
	}
	//--------------------------------------------------------------------
	void CIniFile::WriteBoolean(const std::wstring& szKey, bool bValue)
	{
		wchar_t szBuffer[2] = L"0";
		if( bValue )
		{
			wmemcpy( &szBuffer[0], L"1", 1 );
		}

		WriteString( szKey, szBuffer );
	}
	//--------------------------------------------------------------------
}