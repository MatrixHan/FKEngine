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
	StringArray::StringArray()
	{
		mStringList.Initialize( 10, 10 );
	}
	//--------------------------------------------------------------------------------------------------------------
	StringArray::StringArray( const UINT nInitSize, const UINT nAddSize )
	{
		mStringList.Initialize( nInitSize, nAddSize );
	}
	//--------------------------------------------------------------------------------------------------------------
	StringArray::StringArray( const StringArray& refStringArray )
	{
		*this = refStringArray;
	}
	//--------------------------------------------------------------------------------------------------------------
	StringArray::~StringArray()
	{
		Clear();
		mStringList.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ��������ำֵ
	StringArray& StringArray::operator = ( const StringArray& refStringArray )
	{
		Clear();

		UINT nInitSize = refStringArray.mStringList.Size();
		mStringList.Resize( nInitSize );

		Iterator sit = refStringArray.Begin();
		Iterator send = refStringArray.End();
		Iterator dit = mStringList.Begin();
		for(; sit!=send; ++sit, ++dit )
		{
			dit->mpCharString = NULL;
			dit->mnCharLength = 0;
			*dit = *sit;
		}

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ�����������ַ�����������ȱȽ�
	bool StringArray::operator == ( const StringArray& refStringArray ) const
	{
		Iterator sit = refStringArray.Begin();
		Iterator send = refStringArray.End();
		Iterator dit = mStringList.Begin();
		for(; sit!=send; ++sit, ++dit )
		{
			if( *dit != *sit )
				return false;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ�����������ַ��������಻��ȱȽ�
	bool StringArray::operator != ( const StringArray& refStringArray ) const
	{
		Iterator sit = refStringArray.Begin();
		Iterator send = refStringArray.End();
		Iterator dit = mStringList.Begin();
		for(; sit!=send; ++sit, ++dit )
		{
			if( *dit != *sit )
				return true;
		}

		return false;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ�����������ַ�������������
	StringArray StringArray::operator + ( const StringArray& refStringArray ) const
	{
		UINT NumThis = mStringList.Size();
		UINT NumAdd = refStringArray.mStringList.Size();
		UINT NumDst = NumThis + NumAdd;

		//���Ʊ��ַ������鵽�����ַ���������
		StringArray DstStringArray( NumDst, 10 );
		DstStringArray = refStringArray;
		
		//����ӵ��ַ��������е��ַ�����ӵ������ַ���������
		Iterator it = refStringArray.Begin();
		Iterator end = refStringArray.End();
		for(; it!=end; ++it )
		{
			DstStringArray.Push( *it );
		}

		return DstStringArray;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ַ�����������ַ�������������
	StringArray& StringArray::operator += ( const StringArray& refStringArray )
	{
		//����ӵ��ַ��������е��ַ�����ӱ��ַ���������
		Iterator it = refStringArray.Begin();
		Iterator end = refStringArray.End();
		for(; it!=end; ++it )
			Push( *it );

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������ʲ�������[]��
	String& StringArray::operator [] ( int index )
	{
		return mStringList[index];
	}
	//--------------------------------------------------------------------------------------------------------------
	//��β�������ַ���
	void StringArray::Push( const char* pString )
	{
		String* pStr = mStringList.Push();

		pStr->mpCharString = NULL;
		pStr->mnCharLength = 0;
		*pStr = String( pString );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��β�������ַ���
	void StringArray::Push( const String& refString )
	{
		String* pStr = mStringList.Push();

		pStr->mpCharString = NULL;
		pStr->mnCharLength = 0;
		*pStr = refString;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��β�������ַ���
	void StringArray::Push( const char* pCharString, unsigned int nLength )
	{
		String* pStr = mStringList.Push();

		pStr->mpCharString = NULL;
		pStr->mnCharLength = 0;
		*pStr = String( pCharString, nLength );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��β�������ַ���
	void StringArray::Pop()
	{
		String* pStr = mStringList.Pop();
		pStr->~String();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ָ��λ�ò����ַ���
	void StringArray::Insert( const char* pString, String* ite )
	{
		String* pStr = mStringList.Insert( ite );

		pStr->mpCharString = NULL;
		pStr->mnCharLength = 0;
		*pStr = String( pString );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ָ��λ�ò����ַ���
	void StringArray::Insert( const String& refString, String* ite )
	{
		String* pStr = mStringList.Insert( ite );
		
		pStr->mpCharString = NULL;
		pStr->mnCharLength = 0;
		*pStr = refString;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ָ��λ�ò����ַ���
	void StringArray::Insert( const char* pCharString, unsigned int nLength, String* ite )
	{
		String* pStr = mStringList.Insert( ite );

		pStr->mpCharString = NULL;
		pStr->mnCharLength = 0;
		*pStr = String( pCharString, nLength );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ָ��λ�õ��ַ���
	void StringArray::Erase( String* ite )
	{
		ite->~String();

		mStringList.Erase( ite );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�������ַ���
	void StringArray::Clear()
	{
		Iterator it = mStringList.Begin();
		Iterator end = mStringList.End();
		for(; it!=end; ++it )
		{
			it->~String();
		}
		mStringList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ַ����ײ�Ԫ�ص�����
	StringArray::Iterator StringArray::Begin() const
	{
		return mStringList.Begin();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ַ�����βԪ�ص�����
	StringArray::Iterator StringArray::End() const
	{
		return mStringList.End();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ַ���β��Ԫ�ص�����
	StringArray::Iterator StringArray::Back() const
	{
		return mStringList.Back();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ַ�������
	UINT StringArray::Size() const
	{
		return mStringList.Size();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
