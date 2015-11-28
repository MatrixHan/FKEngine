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
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

#ifndef FK_NO_TEMPLATE_IMPLEMNTATION

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	template <typename T> Stack<T>::Stack()
		: m_pStackBegin	(NULL)
		, m_pStackTop	(NULL)
		, m_pStackEnd	(NULL)
		, m_nStackSize	(0)
		, m_nAddSize	(0)
		, m_nNumData	(0)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	template <typename T> Stack<T>::~Stack()
	{
		Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ����ջ�ڴ棨InitNum Ϊ��ʼ�����Ԫ��������AddNum Ϊÿ�������Ԫ����������
	template <typename T> void Stack<T>::Initialize( unsigned int InitNum, unsigned int AddNum )
	{
		if( m_pStackBegin != NULL )
		{
			Misc::ShowErrMsg( "�������ظ���ʼ����ջ��%s����", __FUNCSIG__ );
			return;
		}

		if( InitNum == 0 )
		{
			Misc::ShowErrMsg( "�޷���ʼ����ջ��%s��Ϊ��Ԫ�ء�", __FUNCSIG__ );
			return;
		}

		m_nNumData = 0;

		//�����ʼ�ڴ�
		m_nStackSize = InitNum * sizeof(T);
		m_pStackBegin = (T*)malloc( m_nStackSize );
		if( m_pStackBegin == NULL )
		{
			Misc::ShowErrMsg( "��ʼ����ջ��%s��ʧ�ܡ�", __FUNCSIG__ );
			return;
		}

		//��¼ÿ�����ӵ��ڴ�����
		m_nAddSize = AddNum * sizeof(T);

		m_pStackTop = m_pStackBegin;
		m_pStackEnd = (T*)( (unsigned char*)m_pStackBegin + m_nStackSize );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷŶ�ջ�ڴ�
	template <typename T> void Stack<T>::Release()
	{
		if( m_pStackBegin != NULL )
		{
			free( m_pStackBegin );
			m_pStackBegin = NULL;
			m_nNumData = m_nStackSize = 0;
			m_pStackTop = m_pStackEnd = NULL;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������ڴ�����ʱ�����С
	template <typename T> FKInline void Stack<T>::ResetAddNum( unsigned int AddNum )
	{
		m_nAddSize = AddNum * sizeof(T);
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������Ԫ��
	template <typename T> void Stack<T>::Clear()
	{
		m_nNumData = 0;
		m_pStackTop = m_pStackBegin;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ջ�Ƿ�Ϊ��
	template <typename T> bool Stack<T>::IsEmpty() const
	{
		if( m_pStackTop == m_pStackBegin )
			return true;
		return false;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ص�ǰԪ����
	template <typename T> FKInline unsigned int Stack<T>::Size() const
	{
		return m_nNumData;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ı�Ԫ������������ڴ治�㽫�Զ����䣩
	template <typename T> void Stack<T>::Resize( unsigned int size )
	{
		//������Ҫ�ڴ�ռ�
		unsigned int nNewSize = sizeof(T) * size;

		//����ڴ治�����������
		if( m_nStackSize < nNewSize )
		{
			T* pOldStackBegin = m_pStackBegin;
			unsigned int OldDataSize = (unsigned int)( (unsigned char*)m_pStackTop - (unsigned char*)m_pStackBegin );
			m_nStackSize = nNewSize;

			//�����µ��ڴ��
			m_pStackBegin = (T*)malloc( m_nStackSize );
			if( m_pStackBegin == NULL )
			{
				Misc::ShowErrMsg( "�����ջģ���ࣨ%s��ʧ�ܣ�", __FUNCSIG__ );
				return;
			}

			memset( m_pStackBegin, 0, m_nStackSize );
			memcpy( m_pStackBegin, pOldStackBegin, OldDataSize );

			//�ͷ�ԭ���ڴ��
			free( pOldStackBegin );

			m_pStackEnd = (T*)( (unsigned char*)m_pStackBegin + m_nStackSize );
		}

		m_pStackTop = (T*)( (unsigned char*)m_pStackBegin + nNewSize );
		m_nNumData = size;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ԫ�ز�������ָ��
	template <typename T> T* Stack<T>::Push()
	{
		//�����δ��ʼ���򱨴�
#ifdef _DEBUG
		if( m_pStackBegin == NULL )
		{
			Misc::ShowErrMsg( "�޷��ڳ�ʼ����ջ��%s��ǰ���� Push() ������", __FUNCSIG__ );
			return NULL;
		}
#endif

		//�����ջ�ѷ����ڴ治����������
		if( m_pStackTop == m_pStackEnd )
		{
			if( !_Expand() )
				return NULL;
		}

		T* pData = m_pStackTop;
		++m_pStackTop;
		++m_nNumData;

		return pData;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ָ����������Ԫ�ز����ص�һ��Ԫ�ص�ָ��
	template <typename T> T* Stack<T>::Push( unsigned int num )
	{
		//�����δ��ʼ���򱨴�
#ifdef _DEBUG
		if( m_pStackBegin == NULL )
		{
			Misc::ShowErrMsg( "�޷��ڳ�ʼ����ջ��%s��ǰ���� Push() ������", __FUNCSIG__ );
			return NULL;
		}
#endif
		//�������ö�ջԪ������
		m_nNumData += num;

		//������Ҫ�ڴ�ռ�
		unsigned int nNewSize = sizeof(T) * m_nNumData;

		T* pFirstPushData = m_pStackTop;

		//����ڴ治�����������
		if( m_nStackSize < nNewSize )
		{
			T* pOldStackBegin = m_pStackBegin;
			unsigned int OldDataSize = (unsigned int)( (unsigned char*)m_pStackTop - (unsigned char*)m_pStackBegin );
			m_nStackSize = nNewSize;

			//�����µ��ڴ��
			m_pStackBegin = (T*)malloc( m_nStackSize );
			if( m_pStackBegin == NULL )
			{
				Misc::ShowErrMsg( "�����ջģ���ࣨ%s��ʧ�ܣ�", __FUNCSIG__ );
				return NULL;
			}

			memset( m_pStackBegin, 0, m_nStackSize );
			memcpy( m_pStackBegin, pOldStackBegin, OldDataSize );

			//�ͷ�ԭ���ڴ��
			free( pOldStackBegin );

			m_pStackEnd = (T*)( (unsigned char*)m_pStackBegin + m_nStackSize );
			pFirstPushData = (T*)( (unsigned char*)m_pStackBegin + OldDataSize );
		}

		m_pStackTop = (T*)( (unsigned char*)m_pStackBegin + nNewSize );

		return pFirstPushData;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ջ��Ԫ�ز�������ָ��
	template <typename T> T* Stack<T>::Pop()
	{
		if( m_pStackTop == m_pStackBegin )
			return NULL;

		--m_nNumData;
		--m_pStackTop;

		return m_pStackTop;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ָ��������ջ��Ԫ�ز�������ָ��
	template <typename T> T* Stack<T>::Pop( unsigned int num )
	{
		if( m_pStackTop == m_pStackBegin )
			return NULL;

		m_pStackTop -= num;
		m_nNumData -= num;

		return m_pStackTop;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡջ�׵ĵ�һ��Ԫ�ص�ָ��
	template <typename T> FKInline T* Stack<T>::Begin() const
	{
		return m_pStackBegin;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡջ�������һ��Ԫ��֮��ĳ�βָ��
	template <typename T> FKInline T* Stack<T>::End() const
	{
		return m_pStackTop;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡջ�������һ��Ԫ�ص�ָ��
	template <typename T> FKInline T* Stack<T>::Back() const
	{
		return m_pStackTop - 1;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ָ��Ԫ��֮ǰ����һ��Ԫ�ز���֮���Ԫ�غ��ƣ�0 Ϊ��һ��Ԫ�أ�
	template <typename T> T* Stack<T>::Insert( unsigned int index )
	{
		//�����ջ�ѷ����ڴ治����������
		if( m_pStackTop == m_pStackEnd )
		{
			if( !_Expand() )
				return NULL;
		}

		//��֮���Ԫ�غ���
		T* pInsPos = m_pStackBegin + index;
		memmove( pInsPos + 1, pInsPos, sizeof(T)*( m_nNumData - index ) );

		++m_pStackTop;
		++m_nNumData;

		return pInsPos;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ָ��λ�õ�Ԫ�ز���֮���Ԫ��ǰ�ƣ�ʹ�õ���������Ԫ�أ�
	template <typename T> T* Stack<T>::Insert( T* ite )
	{
		return Insert( (UINT)( ite - m_pStackBegin ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ָ��λ�õ�Ԫ�ز���֮ǰ��Ԫ��ǰ�ƣ�0 Ϊ��һ��Ԫ�أ�
	template <typename T> void Stack<T>::Erase( unsigned int index, unsigned int num )
	{
		//�����ջΪ���򷵻�
		if( m_pStackTop == m_pStackBegin )
			return;

		//���ɾ��Ԫ��֮�󲻴����κ�Ԫ���򲻽�֮��Ԫ��ǰ��
		unsigned int MoveNum = m_nNumData - index - num;
		if( MoveNum > 0 )
			memcpy( m_pStackBegin + index, m_pStackBegin + index + num, sizeof(T)*MoveNum );

		m_nNumData -= num;
		m_pStackTop -= num;
	}
	//--------------------------------------------------------------------------------------------------------------
	template <typename T> void Stack<T>::Erase( T* ite )
	{
		Erase( (UINT)( ite - m_pStackBegin ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ջ��Ԫ��
	template <typename T> void Stack<T>::PopFront( unsigned int num )
	{
		//�����ջΪ���򷵻�
		if( m_pStackTop == m_pStackBegin )
			return;

		//���ɾ��Ԫ���������ڵ�ǰ�����򷵻�
		if( num > m_nNumData )
		{
			Misc::ShowErrMsg( "ָ�������Ķ�ջģ���ࣨ%s��Ԫ������������ǰԪ��������", __FUNCSIG__ );
			return;
		}

		//��֮��Ԫ��ǰ��
		memcpy( m_pStackBegin, m_pStackBegin + num, sizeof(T) * ( m_nNumData - num ) );

		m_nNumData -= num;
		m_pStackTop -= num;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����������ʲ�������[]��ʹ��ʱע�ⲻҪԽ��
	template <typename T> FKInline T& Stack<T>::operator [] ( int index )
	{
		return *(m_pStackBegin + index);
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ظ��Ʋ����������������ݣ��ڴ����ݴ�С���䡣��
	template <typename T> void Stack<T>::operator = ( const Stack<T>& refStack )
	{
		//�������ֵ�ڴ�ռ䲻�������·�����
		unsigned int copySize = (unsigned int)( refStack.m_pStackTop - refStack.m_pStackBegin );
		if( m_nStackSize < copySize )
		{
			free( m_pStackBegin );
			m_pStackBegin = (T*)malloc( copySize );
			if( m_pStackBegin == NULL )
			{
				Misc::ShowErrMsg( "�����ջģ���ࣨ%s��ʧ�ܣ�", __FUNCSIG__ );
				m_nStackSize = 0;
				m_nNumData = 0;
				return;
			}

			m_nStackSize = copySize;
			m_pStackEnd = m_pStackTop = (T*)( (unsigned char*)m_pStackBegin + copySize );
		}
		else
		{
			m_pStackTop = (T*)( (unsigned char*)m_pStackBegin + copySize );
		}

		m_nNumData = refStack.m_nNumData;

		memcpy( m_pStackBegin, refStack.m_pStackBegin, copySize );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ڴ�ռ�
	template <typename T> bool Stack<T>::_Expand()
	{
		T* pOldStackBegin = m_pStackBegin;
		unsigned int OldStackSize = m_nStackSize;
		m_nStackSize += m_nAddSize;

		//�����µ��ڴ��
		m_pStackBegin = (T*)malloc( m_nStackSize );
		if( m_pStackBegin == NULL )
		{
			Misc::ShowErrMsg( "�����ջģ���ࣨ%s��ʧ�ܣ�", __FUNCSIG__ );
			return false;
		}

		memset( m_pStackBegin, 0, m_nStackSize );
		memcpy( m_pStackBegin, pOldStackBegin, OldStackSize );

		//�ͷ�ԭ���ڴ��
		free( pOldStackBegin );

		m_pStackTop = (T*)( (unsigned char*)m_pStackBegin + OldStackSize );
		m_pStackEnd = (T*)( (unsigned char*)m_pStackBegin + m_nStackSize );

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================


#endif	/* #ifndef FK_NO_TEMPLATE_IMPLEMNTATION */

