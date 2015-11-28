/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	MemPool
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
	//�ڴ�س�Ա����
	//--------------------------------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------------------------------
	template <typename T> MemPool<T>::MemPool()
		: m_pPoolInfo		(NULL)
		, m_nNumPool		(0)
		, m_nPoolDataLen	(0)
		, m_pCurPool		(NULL)
		, m_pCurNum			(NULL)
		, m_pNextPool		(NULL)
		, m_pNextNum		(NULL)
		, m_nPoolSize		(0)
		, m_nNumData		(0)
		, m_nMaxNumData		(0)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	template <typename T> MemPool<T>::~MemPool()
	{
		Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ���ڴ�أ�NumPerPool Ϊ�����ڴ�ص�Ԫ������PoolNum Ϊ��ʼ�ڴ����������
	template <typename T> void MemPool<T>::Initialize( unsigned int NumPerPool, unsigned int PoolNum )
	{
		m_nPoolSize = NumPerPool;
		m_nNumPool = PoolNum;
		m_nMaxNumData = m_nPoolSize * m_nNumPool;

		m_nPoolDataLen = ( sizeof(T)+sizeof(bool) ) * m_nPoolSize;

		//�����ڴ�ص��ڴ��ַ����
		m_pPoolInfo = (PoolInfo*)malloc( sizeof(PoolInfo) * m_nNumPool );
		if( m_pPoolInfo == NULL )
		{
			Misc::ShowErrMsg( "��ʼ���ڴ�أ�%s��ʧ�ܡ�", __FUNCSIG__ );
			return;
		}

		//���������ڴ��
		PoolInfo* pPoolInfo = m_pPoolInfo;
		for( unsigned int i=0; i<m_nNumPool; ++i )
		{
			pPoolInfo->pPool = (T*)malloc( m_nPoolDataLen );
			if( pPoolInfo->pPool == NULL )
			{
				Misc::ShowErrMsg( "��ʼ���ڴ�أ�%s��ʧ�ܡ�", __FUNCSIG__  );
				return;
			}
			pPoolInfo->pbIsUsed = (bool*)( pPoolInfo->pPool + m_nPoolSize );
			memset( pPoolInfo->pPool, 0, m_nPoolDataLen );

			pPoolInfo->nNumEmpty = m_nPoolSize;
			++pPoolInfo;
		}

		//������һ������Ԫ��
		m_pNextPool = m_pPoolInfo;
		m_pNextNum = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷ��ڴ��
	template <typename T> void MemPool<T>::Release()
	{
		//�����¼��ϢΪ���򷵻�
		if( m_pPoolInfo == NULL )
			return;

		//�ͷ������ڴ�ؿռ�
		PoolInfo* pPoolInfo = m_pPoolInfo;
		for( unsigned int i=0; i<m_nNumPool; ++i )
		{
			free( pPoolInfo->pPool );
			++pPoolInfo;
		}

		//�ͷ��ڴ����Ϣ����
		free( m_pPoolInfo );
		m_pPoolInfo = NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ڴ��������Ԫ��
	template <typename T> void MemPool<T>::Clear()
	{
		//ѭ�������ڴ��
		PoolInfo* pPoolInfo = m_pPoolInfo;
		for( unsigned int i=0; i<m_nNumPool; ++j )
		{
			memset( pPoolInfo->pbIsUsed, 0, sizeof(bool)*m_nPoolSize );
			pPoolInfo->nNumEmpty = m_nPoolSize;
			++pPoolInfo;
		}

		m_nNumData = 0;
		m_pNextPool = m_pPoolInfo;
		m_pNextNum = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ԫ��
	template <typename T> T* MemPool<T>::Add()
	{
		//���ָ������һ������λ��
		if( m_pNextPool != NULL )
		{
			m_pCurPool = m_pNextPool;
			m_pCurNum = m_pNextNum;
		}
		//������п���λ��
		else if( m_nNumData < m_nMaxNumData )
		{
			//ѭ�������ڴ��
			PoolInfo* pPoolInfo = m_pPoolInfo;
			for( unsigned int j=0; j<m_nNumPool; ++j )
			{
				//������ڴ���л��п���λ��
				if( pPoolInfo->nNumEmpty != 0 )
				{
					bool* pbIsUsed = pPoolInfo->pbIsUsed;
					for( unsigned int i=0; i<m_nPoolSize; ++i )
					{
						//�����λ�ÿ���
						if( *pbIsUsed == false )
						{
							m_pCurPool = pPoolInfo;
							m_pCurNum = i;

							goto FindEmpty;
						}
						++pbIsUsed;
					}
				}

				++pPoolInfo;
			}

			Misc::ShowErrMsg( "�ڸ��ڴ�أ�%s�����Ѿ��Ҳ����κο�Ԫ��λ�ã�\n���ǿ�Ԫ��λ�ü���ȴ�����㡣",
				__FUNCSIG__ );
			return NULL;
		}
		//����Ѿ�û�п���Ԫ��λ���������ڴ��
		else
			AllocNewPool();

FindEmpty:
		++m_nNumData;

		m_pCurPool->nNumEmpty -= 1;
		m_pCurPool->pbIsUsed[ m_pCurNum ] = true;

		//�����λ�õ���һ��λ��Ҳ������Ԥ�����ø�λ��Ϊ��һ��Ԫ�ش�ſռ�
		unsigned int NumNext = m_pCurNum + 1;
		if( NumNext < m_nPoolSize && m_pCurPool->pbIsUsed[ NumNext ] == false )
		{
			m_pNextPool = m_pCurPool;
			m_pNextNum = NumNext;
		}
		//�������� m_pNextPool Ϊ NULL���Ա�ʾ��Ҫ���ҿ���λ�á�
		else
		{
			m_pNextPool = NULL;
		}

		return m_pCurPool->pPool + m_pCurNum;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ����Ԫ��
	template <typename T> void MemPool<T>::Erase( T* pData )
	{
		//�ж�Ԫ������λ��
		PoolInfo* pPoolInfo = m_pPoolInfo;
		for( unsigned int i=0; i<m_nNumPool; ++i )
		{
			int pos = (int)( pData - pPoolInfo->pPool );
			//����ڸ��ڴ����
			if( pos >= 0 && pos < (int)m_nPoolSize )
			{
				//��־��λ��Ϊ��
				pPoolInfo->pbIsUsed[pos] = false;
				pPoolInfo->nNumEmpty += 1;
				--m_nNumData;
				return;
			}

			++pPoolInfo;
		}

		Misc::ShowErrMsg( "ָ��Ҫɾ����Ԫ�ز����ڴ�أ�%s���С�", __FUNCSIG__ );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����һ���µ��ڴ��
	template <typename T> void MemPool<T>::AllocNewPool()
	{
		//�����ڴ����Ϣ����
		unsigned int oldNumPool = m_nNumPool++;
		PoolInfo* pOldPoolInfo = m_pPoolInfo;

		m_pPoolInfo = (PoolInfo*)malloc( sizeof(PoolInfo)*m_nNumPool );
		if( m_pPoolInfo == NULL )
		{
			Misc::ShowErrMsg( "��ʼ���ڴ�أ�%s��ʧ�ܡ�", __FUNCSIG__ );
			return;
		}
		memcpy( m_pPoolInfo, pOldPoolInfo, sizeof(PoolInfo)*oldNumPool );
		free( pOldPoolInfo );

		//�����ڴ�������ڴ�
		PoolInfo* pNewPool = m_pPoolInfo + oldNumPool;
		pNewPool->pPool = (T*)malloc( m_nPoolDataLen );
		if( pNewPool->pPool == NULL )
		{
			Misc::ShowErrMsg( "��ʼ���ڴ�أ�%s��ʧ�ܡ�", __FUNCSIG__ );
			return;
		}
		pNewPool->pbIsUsed = (bool*)( pNewPool->pPool + m_nPoolSize );
		memset( pNewPool->pPool, 0, m_nPoolDataLen );

		pNewPool->nNumEmpty = m_nPoolSize;

		//�������Ԫ������
		m_nMaxNumData += m_nPoolSize;

		//��¼��ǰ����Ԫ��λ��
		m_pCurPool = pNewPool;
		m_pCurNum = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ָ��λ�õ�Ԫ�ص�����
	template <typename T> typename MemPool<T>::Iterator& MemPool<T>::GetIterator( unsigned int nPos )
	{
		//���õ�����λ��
		m_TmpIterator.pMemPool = this;
		m_TmpIterator.nPoolNum = nPos / m_nPoolSize;
		m_TmpIterator.nDataNum = nPos % m_nPoolSize;
		m_TmpIterator.pPoolInfo = m_pPoolInfo + m_TmpIterator.nPoolNum;
		m_TmpIterator.pData = m_TmpIterator.pPoolInfo->pPool + m_TmpIterator.nDataNum;

		return m_TmpIterator;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ָ��λ�õĿ���Ԫ�ص�����
	template <typename T> typename MemPool<T>::DataIterator& MemPool<T>::GetDataIterator( unsigned int nPos )
	{
		m_TmpDataIterator.pMemPool = this;

		//ѭ�������ڴ��
		unsigned int NumValidData = 0;
		unsigned int NumUsedData = 0;

		PoolInfo* pPoolInfo = m_pPoolInfo;
		for( unsigned int i=0; i<m_nNumPool; ++i )
		{
			//���㵱ǰ�ڴ�صĿ���Ԫ����
			NumUsedData = m_nPoolSize - pPoolInfo->nNumEmpty;
			NumValidData += NumUsedData;

			//���ָ���Ŀ���Ԫ�ؾ��ڸ��ڴ����
			if( NumValidData > nPos )
			{
				m_TmpDataIterator.nPoolNum = i;
				m_TmpDataIterator.pPoolInfo = pPoolInfo;
				goto FindPos;
			}

			++pPoolInfo;
		}

		goto Error;

FindPos:
		//����ָ��Ԫ���ڸ��ڴ�����п���Ԫ���е�λ��
		unsigned int DataNumInThisPool = nPos - ( NumValidData - NumUsedData );

		//�������ڴ�������п���Ԫ��
		unsigned int ValidDataCount = 0;
		bool* pbIsUsed = pPoolInfo->pbIsUsed;
		for( unsigned int i=0; i<m_nPoolSize; ++i )
		{
			//���Ϊ����Ԫ��
			if( *pbIsUsed )
			{
				//������Ǹ�Ԫ��
				if( DataNumInThisPool == ValidDataCount )
				{
					m_TmpDataIterator.nDataNum = i;
					m_TmpDataIterator.pData = pPoolInfo->pPool + i;
					return m_TmpDataIterator;
				}

				++ValidDataCount;
			}
		}

Error:
		Misc::ShowErrMsg( "ָ��Ҫ��ȡ�ڴ�أ�%s������Ԫ�ص�������Ԫ�ز����á�", __FUNCSIG__ );
		return m_TmpDataIterator;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���س�ǰ����Ԫ�ص�����
	template <typename T> typename MemPool<T>::BaseIterator& MemPool<T>::Front()
	{
		m_TmpIterator.pMemPool = this;
		m_TmpIterator.nPoolNum = 0;
		m_TmpIterator.pPoolInfo = m_pPoolInfo;
		m_TmpIterator.nDataNum = 0;
		m_TmpIterator.pData = m_pPoolInfo->pPool - 1;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���س�β����Ԫ�ص�����
	template <typename T> typename MemPool<T>::BaseIterator& MemPool<T>::End()
	{
		m_TmpDataIterator.pMemPool = this;
		m_TmpDataIterator.nPoolNum = m_nNumPool - 1;
		m_TmpDataIterator.pPoolInfo = m_TmpIterator.nPoolNum;
		m_TmpDataIterator.nDataNum = m_nPoolSize;
		m_TmpDataIterator.pData = m_pPoolInfo->pPool + m_nPoolSize;
	}
	//--------------------------------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------------------------------------
	//�ڴ�ػ���Ԫ�ص�������Ա����
	//--------------------------------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------------------------------
	//��ֵ������
	template <typename T> FKInline typename MemPool<T>::BaseIterator&
		MemPool<T>::BaseIterator::operator = ( const BaseIterator& rBaseIterator )
	{
		pMemPool = rBaseIterator.pMemPool;
		nDataNum = rBaseIterator.nDataNum;
		nPoolNum = rBaseIterator.nPoolNum;
		pPoolInfo = rBaseIterator.pPoolInfo;
		pData = rBaseIterator.pData;

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȱȽϲ�����
	template <typename T> FKInline const bool
		MemPool<T>::BaseIterator::operator == ( const BaseIterator& rBaseIterator )
	{
		return ( pData == rBaseIterator.pData );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ȱȽϲ�����
	template <typename T> FKInline const bool
		MemPool<T>::BaseIterator::operator != ( const BaseIterator& rBaseIterator )
	{
		return ( pData != rBaseIterator.pData );
	}
	//--------------------------------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------------------------------------
	//�ڴ��Ԫ���ڴ��������Ա����
	//--------------------------------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------------------------------
	//��ǰ�ƶ����������ȼ��㣩
	template <typename T> typename MemPool<T>::Iterator& MemPool<T>::Iterator::operator ++ ()
	{
		//�����ǰ����Ԫ�ز��ǵ�ǰ�ڴ�������һ��Ԫ��
		if( nDataNum < pMemPool->m_nPoolSize )
		{
			++pData;
			++nDataNum;
		}
		//�����ǰ����Ԫ���Ѿ�Ϊ��ǰ�ڴ�������һ��Ԫ��
		else
		{
			//�����ǰ�ڴ��Ϊ���һ���ڴ��
			if( nPoolNum == pMemPool->m_nNumPool - 1 )
			{
				//���س�βԪ��
				return pMemPool->EndIterator();
			}

			//��ת����һ���ڴ����
			++pPoolInfo;
			++nPoolNum;
			pData = pPoolInfo->pPool;
			nDataNum = 0;
		}

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ǰ�ƶ�������������㣩
	template <typename T> typename MemPool<T>::Iterator MemPool<T>::Iterator::operator ++ (int)
	{
		Iterator tmpIterator = *this;
		++(*this);
		return tmpIterator;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƶ����������ȼ��㣩
	template <typename T> typename MemPool<T>::Iterator& MemPool<T>::Iterator::operator -- ()
	{
		//�����ǰ����Ԫ���Ѿ�Ϊ��ǰ�ڴ���е�һ��Ԫ��
		if( nDataNum == 0 )
		{
			//�����ǰ�ڴ��Ϊ��һ���ڴ��
			if( nPoolNum == 0 )
			{
				//���س�ǰԪ��
				return pMemPool->FrontIterator();
			}

			//��ת����һ���ڴ�ص�β��
			--pPoolInfo;
			--nPoolNum;
			nDataNum = pMemPool->m_nPoolSize - 1;
			pData = pPoolInfo->pPool + nDataNum;
		}
		else
		{
			--pData;
			--nDataNum;
		}

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƶ�������������㣩
	template <typename T> typename MemPool<T>::Iterator MemPool<T>::Iterator::operator -- (int)
	{
		Iterator tmpIterator = *this;
		--(*this);
		return tmpIterator;
	}
	//--------------------------------------------------------------------------------------------------------------


	//--------------------------------------------------------------------------------------------------------------
	//�ڴ�ؿ���Ԫ�ص�������Ա����
	//--------------------------------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------------------------------
	//����ƶ����������ȼ��㣩
	template <typename T> typename MemPool<T>::DataIterator& MemPool<T>::DataIterator::operator ++ ()
	{
		//�����ǰ����Ԫ�ز��ǵ�ǰ�ڴ�������һ��Ԫ��
		if( nDataNum < pMemPool->m_nPoolSize )
		{
			++pData;
			++pbIsUsed;
			++nDataNum;

FindAfterData:
			//�������ڴ����֮������Ԫ��
			bool* pbIsUsed = pPoolInfo->pbIsUsed + nDataNum;
			for( unsigned int i=nDataNum; i<pMemPool->m_nNumPool; ++i )
			{
				//�����ǰԪ�ز��ǿ�Ԫ��
				if( *pbIsUsed )
					return *this;

				++pData;
				++pbIsUsed;
				++nDataNum;
			}

			//�����ǰԪ��֮��û���κο���Ԫ������ת����һ���ڴ��
			goto NextPool;
		}
		//�����ǰ����Ԫ���Ѿ�Ϊ��ǰ�ڴ�������һ��Ԫ��
		else
		{
NextPool:
			//�����ǰ�ڴ��Ϊ���һ���ڴ��
			if( nPoolNum == pMemPool->m_nNumPool - 1 )
			{
				//���س�βԪ��
				return pMemPool->EndDataIterator();
			}

			//��ת����һ���ڴ�ص���ʼ��
			++pPoolInfo;
			++nPoolNum;
			pData = pPoolInfo->pPool;
			nDataNum = 0;

			goto FindAfterData;
		}

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƶ�������������㣩
	template <typename T> typename MemPool<T>::DataIterator MemPool<T>::DataIterator::operator ++ (int)
	{
		DataIterator tmpDataIterator = *this;
		++(*this);
		return tmpDataIterator;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ǰ�ƶ����������ȼ��㣩
	template <typename T> typename MemPool<T>::DataIterator& MemPool<T>::DataIterator::operator -- ()
	{
		//�����ǰ����Ԫ���Ѿ�Ϊ��ǰ�ڴ���е�һ��Ԫ��
		if( nDataNum == 0 )
		{
PrevPool:
			//�����ǰ�ڴ��Ϊ��һ���ڴ��
			if( nPoolNum == 0 )
			{
				//���س�ǰԪ��
				return pMemPool->FrontDataIterator();
			}

			//��ת����һ���ڴ�ص�β��
			--pPoolInfo;
			--nPoolNum;
			nDataNum = pMemPool->m_nPoolSize - 1;
			pData = pPoolInfo->pPool + nDataNum;

			goto FindBeforeData;
		}
		else
		{
			--pData;
			--pbIsUsed;
			--nDataNum;

FindBeforeData:
			//�������ڴ����֮ǰ����Ԫ��
			bool* pbIsUsed = pPoolInfo->pbIsUsed + nDataNum;
			for( unsigned int i=0; i<nDataNum; ++i )
			{
				//�����ǰԪ�ز��ǿ�Ԫ��
				if( *pbIsUsed )
					return *this;

				--pData;
				--pbIsUsed;
				--nDataNum;
			}

			//�����ǰԪ��֮ǰû���κο���Ԫ������ת����һ���ڴ��
			goto PrevPool;
		}

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ǰ�ƶ�������������㣩
	template <typename T> typename MemPool<T>::DataIterator MemPool<T>::DataIterator::operator -- (int)
	{
		DataIterator tmpDataIterator = *this;
		++(*this);
		return tmpDataIterator;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================


#endif	/* #ifndef FK_NO_TEMPLATE_IMPLEMNTATION */

