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

#pragma once

//--------------------------------------------------------------------
#include <string>
//--------------------------------------------------------------------
//! �쳣�����
#define FK_EXCEPTION( num, desc, src ) throw( FK2DEngine::CException( num, desc, src, __FILE__, __LINE__ ) )
//--------------------------------------------------------------------
//! ��ջչ��ѡ��
//@remarks ���Ƽ�ʹ�� FKUnguard �� FKUnguardRet
#if FK_STACK_UNWINDING == 1
	#define FKGuard( a )	FK2DEngine::CAutomaticGuardUnguard _auto_guard_object( (a) )
	#define FKUnguard()
	#define FKUnguardRet( a )	return a
#else
	#define FKGuard( a )
	#define FKUnguard()
	#define FKUnguardRet( a )	return a
#endif
//--------------------------------------------------------------------
//! ���Դ���ģʽ
#if FK_ASSERT_MODE == 1
	#ifdef _DEBUG
		#define FKAssert( a, b )		assert( (a) && (b) )
	#else
		#define FKAssert( a, b )		if( !(a) ) FK_EXCEPTION( FK2DEngine::eEC_RuntimeAssertionFailed, (b), L"û�к�����Ϣ" )
	#endif
#elif FK_ASSERT_MODE == 2
	#define FKAssert( a, b )			if( !(a) ) FK_EXCEPTION( FK2DEngine::eEC_RuntimeAssertionFailed, (b), L"û�к�����Ϣ" )
#else 
	#define FKAssert( a, b )			assert( (a) && (b) )  
#endif
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//! ��ջ���
	const static unsigned int FK_CALL_STACK_DEPTH = 512;

	//! �쳣������
	//@remarks	Ӧ�ó�����뱣֤�����쳣������Ҳ����˵�����к��������뱻
	//			try{} catch( FK2DEngine::CException& e ){} ����
	class CException
	{
	public:
		//! ����������
		enum ENUM_ExceptionCode
		{
			eEC_None,

			eEC_InvalidParams,						// ��Ч����
			eEC_RuntimeAssertionFailed,				// ����δͨ��
			eEC_ErrorInternal,						// �ڲ�����������
			eEC_ItemCannotFind,						// Ԫ��û���ҵ�
			eEC_FileCannotFind,						// �ļ��޷��ҵ�
			eEC_HardwareCannotSupport,				// Ӳ���޷�֧��
			eEC_IniLoadError,						// INI�ļ���ȡʧ��
			//TODO�����std��Exception

			eEC_Max,
		};
	protected:
		long					m_nLine;
		int						m_nNumber;
		std::wstring			m_szDescription;
		std::wstring			m_szSource;
		std::wstring			m_szFile;
		unsigned short			m_usStackDepth;
	protected:
		static CException*		s_pLastException;
		static std::wstring		s_FunctionStack[FK_CALL_STACK_DEPTH];
		static unsigned short	s_usStackDepth;
	public:
		CException( int p_nNumber, const std::wstring& p_szDesc, const std::wstring& p_szSrc );
		CException( int p_nNumber, const std::wstring& p_szDesc, const std::wstring& p_szSrc,
			const char* p_szFil, long p_lLine );
		CException( const CException& p_Other );
		inline void operator = ( const CException& p_Other );
	public:
		//! �õ���ϸ�Ĵ�������
		std::wstring GetFullDescription() const;

		//! �õ�������
		int	GetNumber() const throw();

		//! �õ��쳣Դ
		const std::wstring& GetSource() const
		{
			return m_szSource;
		}

		//! �õ��ļ���
		const std::wstring& GetFile() const
		{
			return m_szFile;
		}

		//! �õ��к�
		long GetLine() const
		{
			return m_nLine;
		}

		//! �õ��򵥵�������Ϣ
		const std::wstring& GetDescription() const
		{
			return m_szDescription;
		}

		//! �õ�ָ�����һ���쳣�����ָ��
		static CException* GetLastException() throw();

		//! ������ջ
		static void PushFunction( const std::wstring& p_szFuncName ) throw();

		//! ������ջ
		static void PopFunction() throw();
	};

	class CAutomaticGuardUnguard
	{
	public:
		CAutomaticGuardUnguard( const std::wstring& p_FuncName ) throw()
		{
			CException::PushFunction( p_FuncName );
		}
		~CAutomaticGuardUnguard() throw()
		{
			CException::PopFunction();
		}
	};
}