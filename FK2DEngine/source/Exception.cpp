/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Exception
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../include/Exception.h"
#include "../include/LogManager.h"
#include "../include/StringConversion.h"

//--------------------------------------------------------------------
namespace FK2DEngine
{
	CException*		CException::s_pLastException	= NULL;
	std::wstring	CException::s_FunctionStack[ FK_CALL_STACK_DEPTH ];
	unsigned short	CException::s_usStackDepth		= 0;
	//--------------------------------------------------------------------
	CException::CException(int p_nNumber, const std::wstring &p_szDesc, const std::wstring &p_szSrc)
		: m_nLine( 0 )
		, m_nNumber( p_nNumber )
		, m_szDescription( p_szDesc )
		, m_szSource( p_szSrc )
		, m_usStackDepth( s_usStackDepth )
	{
		SSLogManager::Instance()->LogMessage( this->GetFullDescription() );
		s_pLastException = this;
	}
	//--------------------------------------------------------------------
	CException::CException(int p_nNumber, const std::wstring &p_szDesc,
		const std::wstring &p_szSrc, const char *p_szFil, long p_lLine)
		: m_nLine( p_lLine )
		, m_nNumber( p_nNumber )
		, m_szDescription( p_szDesc )
		, m_szSource( p_szSrc )
		, m_usStackDepth( s_usStackDepth )
	{
		wchar_t buf[1024];
		FK2DEngine::Ansi2Wide( buf, p_szFil, strlen(p_szFil) );
		m_szFile = std::wstring( buf );

		SSLogManager::Instance()->LogMessage( this->GetFullDescription(), eLML_Critical, true );
		s_pLastException = this;
	}
	//--------------------------------------------------------------------
	CException::CException( const CException& p_Other )
		: m_nLine( p_Other.m_nLine )
		, m_nNumber( p_Other.m_nNumber )
		, m_szDescription( p_Other.m_szDescription )
		, m_szSource( p_Other.m_szSource )
		, m_szFile( p_Other.m_szFile )
	{

	}
	//--------------------------------------------------------------------
	void CException::operator =(const FK2DEngine::CException &p_Other)
	{
		m_szDescription		= p_Other.m_szDescription;
		m_nNumber			= p_Other.m_nNumber;
		m_szSource			= p_Other.m_szSource;
		m_szFile			= p_Other.m_szFile;
		m_nLine				= p_Other.m_nLine;
	}
	//--------------------------------------------------------------------
	std::wstring CException::GetFullDescription() const
	{
		FK2DEngine::StrStreamType desc;
		desc << L"---------------�쳣�׳�---------------\n"
			<< L"�������:"	<< m_nNumber
			<< L"\n����:"	<< m_szSource
			<< L"\n����:"	<< m_szDescription;
		if( m_nLine > 0 )
		{
			desc << L"\n�ļ�:"	<< m_szFile;
			desc << L"\n�к�:"	<< m_nLine;
		}

#ifdef FK_STACK_UNWINDING
		desc << L"\n��ջչ��: ";

		unsigned short usStackUnroll	= ( m_usStackDepth <= FK_CALL_STACK_DEPTH )
			? ( m_usStackDepth - 1 ) : ( FK_CALL_STACK_DEPTH - 1 );

		for( ; usStackUnroll < m_usStackDepth; --usStackUnroll )
		{
			desc << s_FunctionStack[ usStackUnroll ];
			desc << L"(...) <- ";
		}

		desc << L"��ջ�ס�\n";
#endif

		return desc.str();
	}
	//--------------------------------------------------------------------
	int CException::GetNumber() const throw()
	{
		return m_nNumber;
	}
	//--------------------------------------------------------------------
	CException* CException::GetLastException() throw()
	{
		return s_pLastException;
	}
	//--------------------------------------------------------------------
	void CException::PushFunction( const std::wstring& p_szFuncName ) throw()
	{
		if( s_usStackDepth < FK_CALL_STACK_DEPTH )
		{
			s_FunctionStack[ s_usStackDepth ] = p_szFuncName;
		}

		++s_usStackDepth;
	}
	//--------------------------------------------------------------------
	void CException::PopFunction() throw()
	{
		--s_usStackDepth;
	}
	//--------------------------------------------------------------------
}