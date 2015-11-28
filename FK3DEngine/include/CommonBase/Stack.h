/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Stack
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ջģ����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "Macros.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//ָ���ջ�ࣨ����ɱ�֤�ڴ�����Է��䣬���ڴ��ַ�п��ܸı䡣��
	//
	//ע�⣺
	//		����Զ�ջ��Ԫ�ش�ȡ��������ͨ��ָ����ɵġ����磬Ҫ����һ��Ԫ����Ӧ��д�� *Stack.Push() = Value;
	template <typename T> class FK_DLL Stack
	{
	public:
		typedef T*		Iterator;		//T ����

	public:
		T*				m_pStackBegin;	//ջ��ָ��
		T*				m_pStackTop;	//ջ��ָ��
		T*				m_pStackEnd;	//ջβָ��
		unsigned int	m_nStackSize;	//��ջ��ǰ��С
		unsigned int	m_nAddSize;		//ÿ�����ӵ��ڴ�����
		unsigned int	m_nNumData;		//��ǰջ��Ԫ����

	public:
		Stack();
		~Stack();

		//��ʼ����ջ�ڴ棨InitNum Ϊ��ʼ�����Ԫ��������AddNum Ϊÿ�������Ԫ����������
		void Initialize( unsigned int InitNum, unsigned int AddNum );

		//�ͷŶ�ջ�ڴ�
		void Release();

		//���������ڴ�����ʱ�����С
		FKInline void ResetAddNum( unsigned int AddNum );

		//�������Ԫ��
		void Clear();

		//����ջ�Ƿ�Ϊ��
		FKInline bool IsEmpty() const;

		//���ص�ǰԪ����
		FKInline unsigned int Size() const;

		//�ı�Ԫ������������ڴ治�㽫�Զ����䣩
		void Resize( unsigned int size );

		//������Ԫ�ز�������ָ��
		T* Push();

		//����ָ����������Ԫ�ز����ص�һ��Ԫ�ص�ָ��
		T* Push( unsigned int num );

		//����ջ��Ԫ�ز�������ָ��
		T* Pop();

		//����ָ��������ջ��Ԫ�ز�������ָ��
		T* Pop( unsigned int num );

		//��ȡջ�׵ĵ�һ��Ԫ�ص�ָ��
		FKInline T* Begin() const;

		//��ȡջ�������һ��Ԫ��֮��ĳ�βָ��
		FKInline T* End() const;

		//��ȡջ�������һ��Ԫ�ص�ָ��
		FKInline T* Back() const;

		//��ָ��Ԫ��֮ǰ����һ��Ԫ�ز���֮���Ԫ�غ��ƣ�0 Ϊ��һ��Ԫ�أ�
		T* Insert( unsigned int index );

		//��ָ��Ԫ��֮ǰ����һ��Ԫ�ز���֮���Ԫ�غ��ƣ�ʹ�õ���������Ԫ�أ�
		T* Insert( T* ite );

		//ɾ��ָ��λ�õ�Ԫ�ز���֮���Ԫ��ǰ�ƣ�0 Ϊ��һ��Ԫ�أ�
		void Erase( unsigned int index, unsigned int num = 1 );
		
		//ɾ��ָ��λ�õ�Ԫ�ز���֮���Ԫ��ǰ�ƣ�ʹ�õ���������Ԫ�أ�
		void Erase( T* ite );

		//����ջ��Ԫ��
		void PopFront( unsigned int num = 1 );

		//�����������ʲ�������[]��ʹ��ʱע�ⲻҪԽ��
		FKInline T& operator [] ( int index );

		//���ظ��Ʋ����������������ݣ��ڴ����ݴ�С���䡣��
		void operator = ( const Stack<T>& refStack );

	protected:
		//�����ڴ�ռ�
		bool _Expand();
	};
	//--------------------------------------------------------------------------------------------------------------

	//������ջ��������
	typedef Stack< void* >				PTRStack;		//������ָ���ջ

	typedef Stack< bool >				BOOLStack;		//�����Ͷ�ջ
	typedef Stack< wchar_t >			WCHARStack;		//���ַ��Ͷ�ջ

	typedef Stack< char >				CHARStack;		//�з����ַ��Ͷ�ջ
	typedef Stack< short >				SHORTStack;		//�з��Ŷ����Ͷ�ջ
	typedef Stack< int >				INTStack;		//�з������Ͷ�ջ
	typedef Stack< long >				LONGStack;		//�з��ų����Ͷ�ջ

	typedef Stack< unsigned char >		BYTEStack;		//�޷����ַ��Ͷ�ջ
	typedef Stack< unsigned short >		WORDStack;		//�޷��Ŷ����Ͷ�ջ
	typedef Stack< unsigned int >		UINTStack;		//�޷������Ͷ�ջ
	typedef Stack< unsigned long >		ULONGStack;		//�޷��ų����Ͷ�ջ

	typedef Stack< float >				FLOATStack;		//�����ȸ����Ͷ�ջ
	typedef Stack< float >				DOUBLEStack;	//˫���ȸ����Ͷ�ջ

	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
