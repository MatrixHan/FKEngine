/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	StringConversion
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include <string>
#include <vector>
#include "FKSharedPtr.h"
//--------------------------------------------------------------------

namespace FK2DEngine
{
	typedef std::vector< std::wstring >		StringVector;		// �ַ�����������
	typedef TSharedPtr< StringVector >		StringVectorPtr;	// �ַ�����������ָ������
	typedef std::wostringstream				StrStreamType;		// �ַ���

	//! ת�� std::string Ϊ std::wstring
	std::wstring UTF8ToWstring( const std::string& p_UTF8 );

	//! ת�� std::wstring Ϊ std::string
	std::string WstringToUTF8( const std::wstring& p_WString );

	//! ���ؽ��뷽ʽ ת�� std::string Ϊ std::wstring
	std::wstring Widen( const std::string& p_UTF8 );

	//! ���ؽ��뷽ʽ ת�� std::wstring Ϊ std::string
	std::string Narrow( const std::wstring& p_WString );

	//! ɾ���ַ���ͷβ�ո񣬻س���Tab
	//@param [IN] p_bLeft	�Ƿ�ɾ���ַ���ͷ�Ŀո񣬻س���Tab
	//@param [IN] p_bRight	�Ƿ�ɾ���ַ���β�Ŀո񣬻س���Tab
	void Trim( std::wstring& p_Str, bool p_bLeft = true, bool p_bRight = true );

	//! ��һ���ַ����ָ�Ϊ����ַ�����Ԫ���������ַ���������
	//@param [IN] p_Delims	���зָ���ַ���ɵ��ַ���,Ĭ��Ϊ("\t\n\r ")
	//@param [IN] p_unMaxSplits ���ָ����
	StringVector Split( const std::wstring& p_Str, std::wstring& p_Delims,
		unsigned int p_unMaxSplits = 0 );

	//! ���ַ��������д�д��ĸ��ΪСд��ĸ
	void ToLowerCase( std::wstring& p_Str );

	//! ���ַ���������Сд��ĸ��Ϊ��д��ĸ
	void ToUpperCase( std::wstring& p_Str );

	//! �ж��ַ����Ƿ���ָ���ַ���ģʽ��ͷ
	//@param [IN] p_Pattern	�ο���ָ���ַ���
	//@param [IN] p_bCaseSensitive �Ƿ��Сд����
	bool IsStartWith( const std::wstring& p_Str, const std::wstring& p_Pattern, bool p_bCaseSensitive = false );

	//! �ж��ַ����Ƿ���ָ���ַ���ģʽ��β
	bool IsEndWith( const std::wstring& p_Str, const std::wstring& p_Pattern, bool p_bCaseSensitive = false );

	//! ��׼��·��
	//@note ��·���е�'\\'ת��Ϊ'/'�����������'/'Ϊ��β
	//@par	���磺C:\\aaa\\bbb ת��Ϊ C:/aaa/bbb/
	std::wstring StandardisePath( const std::wstring& p_Init );

	//! �ָ��ļ�·�����ļ���
	void SplitFilename( const std::wstring& p_QualifiedName,
		std::wstring& p_szOutBasename, std::wstring& p_szOutPath );

	//! ���ԭ�ַ��Ƿ���ģʽ�ַ�ƥ��
	//@remarks	֧��'*'ͨ�����������������������ͨ�������������һ��ʱ����ÿ��ͨ�������һ���ַ���
	//			����ÿ��ͨ�������N���ַ�.
	//@Ppar		����: "FreeKnight" ��'F*t'ƥ�䣬ȴ����'F**t'ƥ�䡣
	bool Match( const std::wstring& p_Str, const std::wstring& p_Pattern, bool p_bCaseSensitive = true );

	//! ת��floatΪ std;:wstring
	//@param [IN] p_usPrecision ��ʾ��λ��
	std::wstring ToString( float p_fValue, unsigned short p_usPrecision = 6,
		unsigned short p_usWidth = 0, char p_Fill = ' ', 
		std::ios::fmtflags p_Flags = std::ios::fmtflags( 0 ) );
	std::wstring ToString( double p_dValue, unsigned short p_usPrecision = 6,
		unsigned short p_usWidth = 0, char p_Fill = ' ', 
		std::ios::fmtflags p_Flags = std::ios::fmtflags( 0 ) );

	//! ת��wchar_tΪstd::wstring
	std::wstring ToString( wchar_t p_Val );

	//! ת�� int Ϊ std::wstring
	std::wstring ToString( int p_nVal, unsigned short p_usWidth = 0, char p_Fill = ' ',
		std::ios::fmtflags p_Flags = std::ios::fmtflags( 0 ) );
	std::wstring ToString( size_t p_unVal, unsigned short p_usWidth = 0, char p_Fill = ' ',
		std::ios::fmtflags p_Flags = std::ios::fmtflags( 0 ) );
	std::wstring ToString( unsigned long p_ulVal, unsigned short p_usWidth = 0, char p_Fill = ' ',
		std::ios::fmtflags p_Flags = std::ios::fmtflags( 0 ) );
	std::wstring ToString( long p_lVal, unsigned short p_usWidth = 0, char p_Fill = ' ',
		std::ios::fmtflags p_Flags = std::ios::fmtflags( 0 ) );

	//! ת�� bool Ϊ std::wstring
	//@param [IN] bYesNo ���ò���Ϊtrue���򷵻��ַ���Ϊ"yes"��"no"�����򷵻�"true"��"false"
	std::wstring ToString( bool p_bValue, bool p_bYesNo = false );

	//! ת���ַ�������Ϊ std::wstring
	std::wstring ToString( const StringVector& p_Value );

	//! ת�� std::wstring Ϊ float
	float			ParseFloat( const std::wstring& p_Value );
	double			ParseDouble( const std::wstring& p_Value );
	int				ParseInt( const std::wstring& p_Value );
	unsigned int	ParseUnsignedInt( const std::wstring& p_Value );
	long			ParseLong( const std::wstring& p_Value );
	unsigned long	ParseUnsignedLong( const std::wstring& p_Value );
	bool			ParseBool( const std::wstring& p_Value );
	StringVector	ParseStringVector( const std::wstring& p_Value );

	//! �ж�һ�� std::wstring �Ƿ�������
	bool IsNumber( const std::wstring& p_Value );

	//! ���ֽ�ת˫�ֽ�
	void Ansi2Wide( wchar_t* p_pDest, const char* p_pSrc, size_t p_unLen );
	//! ˫�ֽ�ת���ֽ�
	void Wide2Ansi( char* p_pDest, const wchar_t* p_pSrc, size_t p_unLen );
	//! ���ֽ��ַ���תΪ���ַ�����
	void AnsiString2Array( char* p_pDest, const std::string& p_Str );
	//! ˫�ַ���תΪ˫�ַ�����
	void WideString2Array( wchar_t* p_pDest, const std::wstring& p_Str );
}