/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	StringArray
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�ַ���������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include <windows.h>
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//�ַ���������
	class FK_DLL StringArray
	{
	public:
		typedef String*		Iterator;

	protected:
		Stack< String >		mStringList;	//�ַ����б�

	public:
		StringArray();
		StringArray( const UINT nInitSize, const UINT nAddSize );
		StringArray( const StringArray& refStringArray );
		~StringArray();

		//�ַ��������ำֵ
		StringArray& operator = ( const StringArray& refStringArray );

		//�ַ�����������ַ�����������ȱȽ�
		bool operator == ( const StringArray& refStringArray ) const;

		//�ַ�����������ַ��������಻��ȱȽ�
		bool operator != ( const StringArray& refStringArray ) const;

		//�ַ�����������ַ�������������
		StringArray operator + ( const StringArray& refStringArray ) const;

		//�ַ�����������ַ�������������
		StringArray& operator += ( const StringArray& refStringArray );

		//�������ʲ�������[]��
		String& operator [] ( int index );

		//��β�������ַ���
		void Push( const char* pString );

		//��β�������ַ���
		void Push( const String& refString );

		//��β�������ַ���
		void Push( const char* pCharString, unsigned int nLength );

		//��β�������ַ���
		void Pop();

		//��ָ��λ�ò����ַ���
		void Insert( const char* pString, String* ite );

		//��ָ��λ�ò����ַ���
		void Insert( const String& refString, String* ite );

		//��ָ��λ�ò����ַ���
		void Insert( const char* pCharString, unsigned int nLength, String* ite );

		//ɾ��ָ��λ�õ��ַ���
		void Erase( String* ite );

		//ɾ�������ַ���
		void Clear();

		//��ȡ�ַ����ײ�Ԫ�ص�����
		Iterator Begin() const;

		//��ȡ�ַ�����βԪ�ص�����
		Iterator End() const;

		//��ȡ�ַ���β��Ԫ�ص�����
		Iterator Back() const;

		//�����ַ�������
		UINT Size() const;
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
