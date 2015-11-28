/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	String
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/CommonBase/CommonBaseInsideHead.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	String::String()
		: mpCharString	(NULL)
		, mnCharLength	(0)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	String::String( const char* pCharString )
		: mpCharString	(NULL)
		, mnCharLength	(0)
	{
		*this = pCharString;
	}
	//--------------------------------------------------------------------------------------------------------------
	String::String( const char* pCharString, const unsigned int nLength )
		: mnCharLength	(nLength)
	{
		mpCharString = (char*)malloc( mnCharLength + 1 );
		if( mpCharString == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "��ʼ���ַ���ʱ�����ַ����ڴ�ʧ�ܡ�" );

		memcpy( mpCharString, pCharString, mnCharLength );

		mpCharString[mnCharLength] = '\0';
	}
	//--------------------------------------------------------------------------------------------------------------
	String::String( const String& refString )
		: mpCharString	(NULL)
		, mnCharLength	(0)
	{
		*this = refString;
	}
	//--------------------------------------------------------------------------------------------------------------
	String::String( float value )
		: mpCharString	(NULL)
		, mnCharLength	(0)
	{
		*this = value;
	}
	//--------------------------------------------------------------------------------------------------------------
	String::String( int value )
		: mpCharString	(NULL)
		, mnCharLength	(0)
	{
		*this = value;
	}
	//--------------------------------------------------------------------------------------------------------------
	String::~String()
	{
		SafeFree( mpCharString );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ����ำֵ
	String& String::operator = ( const String& refString )
	{
		SafeFree( mpCharString );

		mnCharLength = refString.mnCharLength;
		mpCharString = (char*)malloc( mnCharLength + 1 );
		if( mpCharString == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "��ʼ���ַ���ʱ�����ַ����ڴ�ʧ�ܡ�" );

		memcpy( mpCharString, refString.mpCharString, mnCharLength + 1 );

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ�����ֵ
	String& String::operator = ( const char* pCharString )
	{
		SafeFree( mpCharString );

		mnCharLength = (unsigned int)strlen( pCharString );

		mpCharString = (char*)malloc( mnCharLength + 1 );
		if( mpCharString == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "��ʼ���ַ���ʱ�����ַ����ڴ�ʧ�ܡ�" );

		memcpy( mpCharString, pCharString, mnCharLength );

		mpCharString[mnCharLength] = '\0';

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ֵ
	String& String::operator = ( float value )
	{
		SetString( value );
		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ֵ
	String& String::operator = ( int value )
	{
		SetString( value );
		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ�������ַ�������ȱȽ�
	bool String::operator == ( const String& refString ) const
	{
		if( mnCharLength == refString.mnCharLength )
		{
			if( 0 == memcmp( mpCharString, refString.mpCharString, mnCharLength ) )
				return true;
		}

		return false;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ�������ַ�����ȱȽ�
	bool String::operator == ( const char* pCharString ) const
	{
		unsigned int nLength = (unsigned int)strlen( pCharString );

		if( mnCharLength == nLength )
		{
			if( 0 == memcmp( mpCharString, pCharString, mnCharLength ) )
				return true;
		}

		return false;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ�������ַ����಻��ȱȽ�
	bool String::operator != ( const String& refString ) const
	{
		if( mnCharLength == refString.mnCharLength )
		{
			if( 0 == memcmp( mpCharString, refString.mpCharString, mnCharLength ) )
				return false;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ�������ַ�������ȱȽ�
	bool String::operator != ( const char* pCharString ) const
	{
		unsigned int nLength = (unsigned int)strlen( pCharString );

		if( mnCharLength == nLength )
		{
			if( 0 == memcmp( mpCharString, pCharString, mnCharLength ) )
				return false;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ�������ַ���������
	String String::operator + ( const String& refString ) const
	{
		String tmpStr;
		tmpStr.mnCharLength = mnCharLength + refString.mnCharLength;

		tmpStr.mpCharString = (char*)malloc( tmpStr.mnCharLength + 1 );
		if( mpCharString == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "�����ַ���ʱ�����ַ����ڴ�ʧ�ܡ�" );

		memcpy( tmpStr.mpCharString, this->mpCharString, this->mnCharLength );
		memcpy( tmpStr.mpCharString + mnCharLength, refString.mpCharString, refString.mnCharLength );
		tmpStr.mpCharString[ tmpStr.mnCharLength ] = '\0';

		return tmpStr;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ�������ַ�������
	String String::operator + ( const char* pCharString ) const
	{
		unsigned int nLength = (unsigned int)strlen( pCharString );

		String tmpStr;
		tmpStr.mnCharLength = mnCharLength + nLength;

		tmpStr.mpCharString = (char*)malloc( tmpStr.mnCharLength + 1 );
		if( mpCharString == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "�����ַ���ʱ�����ַ����ڴ�ʧ�ܡ�" );

		memcpy( tmpStr.mpCharString, this->mpCharString, this->mnCharLength );
		memcpy( tmpStr.mpCharString + mnCharLength, pCharString, nLength );
		tmpStr.mpCharString[ tmpStr.mnCharLength ] = '\0';

		return tmpStr;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ����͸�����ת�����ַ�������
	String String::operator + ( float value ) const
	{
		return *this + String( value );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ���������ת�����ַ�������
	String String::operator + ( int value )
	{
		return *this + String( value );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ�������ַ���������
	String& String::operator += ( const String& refString )
	{
		unsigned int newCharLength = mnCharLength + refString.mnCharLength;

		char* newCharString = (char*)malloc( newCharLength + 1 );
		if( newCharString == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "�����ַ���ʱ�����ַ����ڴ�ʧ�ܡ�" );

		memcpy( newCharString, this->mpCharString, this->mnCharLength );
		memcpy( newCharString + mnCharLength, refString.mpCharString, refString.mnCharLength );
		newCharString[ newCharLength ] = '\0';

		SafeFree( mpCharString );
		mpCharString = newCharString;
		mnCharLength = newCharLength;

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ�������ַ�������
	String& String::operator += ( const char* pCharString )
	{
		unsigned int nLength = (unsigned int)strlen( pCharString );

		unsigned int newCharLength = mnCharLength + nLength;

		char* newCharString = (char*)malloc( newCharLength + 1 );
		if( newCharString == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "�����ַ���ʱ�����ַ����ڴ�ʧ�ܡ�" );

		memcpy( newCharString, this->mpCharString, this->mnCharLength );
		memcpy( newCharString + mnCharLength, pCharString, nLength );
		newCharString[ newCharLength ] = '\0';

		SafeFree( mpCharString );
		mpCharString = newCharString;
		mnCharLength = newCharLength;

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ����͸�����ת�����ַ�������
	String& String::operator += ( float value )
	{
		*this += String( value );
		return *this; 
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ���������ת�����ַ�������
	String& String::operator += ( int value )
	{
		*this += String( value );
		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ַ��������ַ�����
	void String::SetString( const char* pCharString )
	{
		*this = pCharString;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ַ��������ַ����ࣨ�����ַ������ȣ�
	void String::SetString( const char* pCharString, unsigned int nLength )
	{
		SafeFree( mpCharString );

		mnCharLength = nLength;

		mpCharString = (char*)malloc( mnCharLength + 1 );
		if( mpCharString == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "��ʼ���ַ���ʱ�����ַ����ڴ�ʧ�ܡ�" );

		memcpy( mpCharString, pCharString, mnCharLength );

		mpCharString[mnCharLength] = '\0';
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������������ַ�����
	void String::SetString( int value )
	{
		char szBuf[ NumConvert::mMaxIntTextLen ] = { NULL };
		unsigned int nLen = NumConvert::IntToMultiByte( value, szBuf );
		SetString( szBuf, nLen );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ݸ����������ַ�����
	void String::SetString( float value, int nPrecision )
	{
		char szBuf[ NumConvert::mMaxFloatTextLen ] = { NULL };
		unsigned int nLen = NumConvert::FloatToMultiByte( value, szBuf, nPrecision );
		SetString( szBuf, nLen );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ַ���ָ��
	const char* String::GetCharPtr() const
	{
		return mpCharString;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ַ�������
	unsigned int String::GetLength() const
	{
		return mnCharLength;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ַ�������
	void String::Clear()
	{
		SafeFree( mpCharString );
		mnCharLength = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ص�һ��ָ���ַ����ַ����е�λ��
	int String::GetFirstCharIndex( char Symbol ) const
	{
		char* pStr = mpCharString;
		for( unsigned int i=0; i<mnCharLength; ++i )
		{
			if( *pStr++ == Symbol )
				return (int)i;
		}

		return -1;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������һ��ָ���ַ����ַ����е�λ��
	int String::GetLastCharIndex( char Symbol ) const
	{
		char* pStr = mpCharString + mnCharLength;
		for( unsigned int i=mnCharLength; i>0; --i )
		{
			if( *(--pStr) == Symbol )
				return (int)i;
		}

		return -1;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ָ���ַ��з��ַ���
	//bool String::Split( char, StringArray& ) const
	//{
	//}
	//--------------------------------------------------------------------------------------------------------------
	//��ָ��λ��֮����ַ���
	String String::SubString( unsigned int Start, unsigned int End ) const
	{
		return String( mpCharString + Start, End - Start );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ַ���β��ȥ��ָ�����ַ���
	String& String::CutString( const String& refString )
	{
		char* pChar = strstr( mpCharString, refString.mpCharString );
		if( pChar != NULL )
			*pChar = '\0';

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	String& String::CutString( const char* pCharString )
	{
		char* pChar = strstr( mpCharString, pCharString );
		if( pChar != NULL )
			*pChar = '\0';

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ַ���β�������ַ���
	String& String::AppendString( const String& refString )
	{
		unsigned int newLen = mnCharLength + refString.mnCharLength;
		char* newStr = (char*)malloc( newLen + 1 );

		memcpy( newStr, mpCharString, mnCharLength );
		memcpy( newStr + mnCharLength, refString.mpCharString, refString.mnCharLength + 1 );

		free( mpCharString );

		mpCharString = newStr;
		mnCharLength = newLen;

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	String& String::AppendString( const char* pCharString )
	{
		unsigned int AppendLen = (unsigned int)strlen( pCharString );

		unsigned int newLen = mnCharLength + AppendLen;
		char* newStr = (char*)malloc( newLen + 1 );

		memcpy( newStr, mpCharString, mnCharLength );
		memcpy( newStr + mnCharLength, pCharString, AppendLen + 1 );

		free( mpCharString );
		mpCharString = newStr;
		mnCharLength = newLen;

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ַ���ת��Ϊ��д
	String& String::ToUpperCase()
	{
		strupr( mpCharString );
		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ַ���ת��ΪСд
	String& String::ToLowerCase()
	{
		strlwr( mpCharString );
		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ܷ�ת��Ϊ����
	bool String::CanToInt() const
	{
		return NumConvert::CanMultiByteToInt( mpCharString );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ܷ�ת��Ϊ������
	bool String::CanToFloat() const
	{
		return NumConvert::CanMultiByteToFloat( mpCharString );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ת��Ϊ����
	int String::ToInt() const
	{
		return NumConvert::MultiByteToInt( mpCharString );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ת��Ϊ˫���ȸ�����
	float String::ToFloat() const
	{
		return NumConvert::MultiByteToFloat( mpCharString );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʽ���ַ���
	void String::Format( const char* szStr, ... )
	{
		//��ȡ�����б�
		va_list args;
		va_start( args, szStr );

		//��ȡ��ʽ��������ַ�������
		mnCharLength = _vscprintf( szStr, args );

		//�����ַ��������С
		SafeFree( mpCharString );

		mpCharString = (char*)malloc( mnCharLength + 1 );
		if( mpCharString == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "��ʽ���ַ���ʱ�����ַ����ڴ�ʧ�ܡ�" );

		//��ʽ���ַ���
		vsprintf( mpCharString, szStr, args );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
