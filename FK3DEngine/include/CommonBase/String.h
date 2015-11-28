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
*	�ļ�˵����	�ַ�����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//�ַ�����
	class FK_DLL String
	{
	public:
		char*			mpCharString;		//�ַ���ָ��
		unsigned int	mnCharLength;		//�ַ�������

	public:
		String();
		String( const char* pCharString );
		String( const char* pCharString, const unsigned int nLength );
		String( const String& refString );
		String( float value );
		String( int value );
		~String();

		//�ַ����ำֵ
		String& operator = ( const String& refString );

		//�ַ�����ֵ
		String& operator = ( const char* pCharString );

		//��������ֵ
		String& operator = ( float value );

		//������ֵ
		String& operator = ( int value );

		//�ַ�������ַ�������ȱȽ�
		bool operator == ( const String& refString ) const;

		//�ַ�������ַ�����ȱȽ�
		bool operator == ( const char* pCharString ) const;

		//�ַ�������ַ����಻��ȱȽ�
		bool operator != ( const String& refString ) const;

		//�ַ�������ַ�������ȱȽ�
		bool operator != ( const char* pCharString ) const;

		//�ַ�������ַ���������
		String operator + ( const String& refString ) const;

		//�ַ�������ַ�������
		String operator + ( const char* pCharString ) const;

		//�ַ����͸�����ת�����ַ�������
		String operator + ( float value ) const;

		//�ַ���������ת�����ַ�������
		String operator + ( int value );

		//�ַ�������ַ���������
		String& operator += ( const String& refString );

		//�ַ�������ַ�������
		String& operator += ( const char* pCharString );

		//�ַ����͸�����ת�����ַ�������
		String& operator += ( float value );

		//�ַ���������ת�����ַ�������
		String& operator += ( int value );

		//�����ַ��������ַ�����
		void SetString( const char* pCharString );

		//�����ַ��������ַ����ࣨ�����ַ������ȣ�
		void SetString( const char* pCharString, unsigned int nLength );

		//�������������ַ�����
		void SetString( int value );

		//���ݸ����������ַ�����
		void SetString( float value, int nPrecision = 5 );

		//��ȡ�ַ���ָ��
		const char* GetCharPtr() const;

		//��ȡ�ַ�������
		unsigned int GetLength() const;

		//����ַ�������
		void Clear();

		//���ص�һ��ָ���ַ����ַ����е�λ�ã��Ҳ����򷵻� -1��
		int GetFirstCharIndex( char Symbol ) const;
		
		//�������һ��ָ���ַ����ַ����е�λ�ã��Ҳ����򷵻� -1��
		int GetLastCharIndex( char Symbol ) const;

		//����ָ���ַ��з��ַ���
		//bool Split( char, StringArray& ) const;

		//��ָ��λ��֮����ַ���
		String SubString( unsigned int Start, unsigned int End ) const;

		//���ַ���β��ȥ��ָ�����ַ���
		String& CutString( const String& refString );
		String& CutString( const char* pCharString );

		//���ַ���β�������ַ���
		String& AppendString( const String& refString );
		String& AppendString( const char* pCharString );

		//���ַ���ת��Ϊ��д
		String& ToUpperCase();

		//���ַ���ת��ΪСд
		String& ToLowerCase();

		//�ܷ�ת��Ϊ����
		bool CanToInt() const;

		//�ܷ�ת��Ϊ������
		bool CanToFloat() const;

		//ת��Ϊ����
		int ToInt() const;

		//ת��Ϊ������
		float ToFloat() const;

		//��ʽ���ַ���
		void Format( const char* szStr, ... );
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< String* >	StringList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
