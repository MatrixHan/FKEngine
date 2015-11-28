/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	HashMap
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
	template <typename T> HashMap<T>::HashMap()
		: mnTableSize	(0)
		, mpHashTable	(NULL)
		, mNumData		(0)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	template <typename T> HashMap<T>::~HashMap()
	{
		Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ����ϣ��nTableSize Ϊ��ϣ���С�������ӵ�Ԫ�س����˴���ֵ������ظ��ʼ��ߡ���
	template <typename T> void HashMap<T>::Initialize( unsigned int nTableSize )
	{
		//��ʼ����ջ
		mHashDataStack.Initialize( nTableSize, nTableSize >> 2 );

		//��ʼ����ϣԪ���������ڴ�
		mnTableSize = nTableSize;

		size_t nTableLen = sizeof(HashData*) * nTableSize;
		mpHashTable = (HashData**)malloc( nTableLen );
		if( mpHashTable == NULL )
		{
			Misc::ShowErrMsg( "��ʼ����ϣ��%s���ڴ�ʧ�ܡ�", __FUNCSIG__ );
			return;
		}

		memset( mpHashTable, 0, nTableLen );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��չ�ϣ��
	template <typename T> void HashMap<T>::Clear()
	{
		//�ͷ����й�ϣԪ��
		unsigned int nStackSize = mHashDataStack.Size();
		HashData** ppHashData = mHashDataStack.Begin();
		for( unsigned int i=0; i<nStackSize; ++i )
		{
			SafeFree( *ppHashData );
			++ppHashData;
		}

		mHashDataStack.Clear();
		memset( mpHashTable, 0, sizeof(HashData*) * mnTableSize );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷŹ�ϣ��
	template <typename T> void HashMap<T>::Release()
	{
		//�ͷ����й�ϣԪ��
		unsigned int nStackSize = mHashDataStack.Size();
		HashData** ppHashData = mHashDataStack.Begin();
		for( unsigned int i=0; i<nStackSize; ++i )
		{
			if( *ppHashData != NULL )
				free( *ppHashData );

			ppHashData++;
		}

		mHashDataStack.Release();
		SafeFree( mpHashTable );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����Ԫ��
	template <typename T> bool HashMap<T>::Add( const T& refData, const char* szKeyName )
	{
		//���������ϣֵ��Ϊ��Ԫ�����������е�λ��
		size_t nStrLen = 0;
		unsigned int nPos = Misc::HashString( szKeyName, &nStrLen ) % mnTableSize;

		//�������ַ�������
		if( nStrLen >= 32 )
		{
			Misc::ShowErrMsg( "��ϣ��%s�������������� %d ���ַ���", __FUNCSIG__, mMaxHashStrLen );
			return false;
		}

		//�����µĹ�ϣԪ��
		HashData* pHashData = (HashData*)malloc( sizeof(HashData) );
		if( pHashData == NULL )
		{
			Misc::ShowErrMsg( "�����ϣ��%s���ڴ�ʧ�ܡ�", __FUNCSIG__ );
			return false;
		}
		
		//����Ԫ������
		pHashData->nKeyNameLen = (unsigned short)nStrLen;
		memcpy( pHashData->szKeyName, szKeyName, nStrLen + 1 );

		pHashData->Data = refData;
		pHashData->pPrev = NULL;
		pHashData->pNext = NULL;
		pHashData->nStackIndex = mHashDataStack.Size();

		//�����λ���Ѿ����ڹ�ϣԪ��
		if( mpHashTable[nPos] != NULL )
		{
			HashData* pExistData = mpHashTable[nPos];

CheckNextKey:
			//�������������ͬ
			if( pExistData->nKeyNameLen == (unsigned short)nStrLen )
			{
				//�Ҽ�����ͬ
				if( 0 == memcmp( pExistData->szKeyName, szKeyName, nStrLen ) )
				{
					return false;
				}
			}
			
			if( pExistData->pNext != NULL )
			{
				pExistData = pExistData->pNext;
				goto CheckNextKey;
			}

			pExistData->pNext = pHashData;
			pHashData->pPrev = pExistData;
		}
		//�����λ��Ϊ��
		else
		{
			mpHashTable[nPos] = pHashData;
		}

		//����Ԫ��ָ������ջ������
		*mHashDataStack.Push() = pHashData;

		++mNumData;

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��Ԫ��
	template <typename T> void HashMap<T>::Del( const char* szKeyName )
	{
		//���������ϣֵ��Ϊ��Ԫ�����������е�λ��
		size_t nStrLen = 0;
		unsigned int nPos = Misc::HashString( szKeyName, &nStrLen ) % mnTableSize;

		//�������ַ�������
		if( nStrLen >= 32 )
		{
			Misc::ShowErrMsg( "��ϣ��%s�������������� %d ���ַ���", __FUNCSIG__, mMaxHashStrLen );
			return;
		}

		//����ڹ�ϣ�����Ҳ�����Ԫ��
		if( mpHashTable[nPos] == NULL )
		{
			Misc::ShowErrMsg( "�ڹ�ϣ��%s�����Ҳ�������Ϊ '%s' ��Ԫ�ء�", __FUNCSIG__, szKeyName );
			return;
		}

		//����ҵ�
		HashData* pHashData = mpHashTable[nPos];

		//�����λ�ò�ֻ��һ��Ԫ��
		if( pHashData->pNext != NULL )
		{
CheckNextKey:
			//�������������ͬ
			if( pHashData->nKeyNameLen == (unsigned short)nStrLen )
			{
				//�Ҽ�����ͬ
				if( 0 == memcmp( pHashData->szKeyName, szKeyName, nStrLen ) )
					goto FoundKey;
			}

			//�����λ��û������Ԫ����
			if( pHashData->pNext == NULL )
			{
				Misc::ShowErrMsg( "�ڹ�ϣ��%s�����Ҳ�������Ϊ '%s' ��Ԫ�ء�", __FUNCSIG__, szKeyName );
				return;
			}
			//���������ѯ��һ����
			else
			{
				pHashData = pHashData->pNext;
				goto CheckNextKey;
			}
		}

FoundKey:
		//�����Ԫ��֮ǰ��������Ԫ��
		if( pHashData->pPrev != NULL )
		{
			HashData* pParent = pHashData->pPrev;

			//�������֮��Ҳ��Ԫ��������ǰһ��Ԫ�غ����ĺ�һ��Ԫ����������
			if( pHashData->pNext != NULL )
			{
				pParent->pNext = pHashData->pNext;
				pHashData->pNext->pPrev = pParent;
			}
			//����ֻ�������ǰ���Ԫ��ָ���Ԫ�ص�ָ��
			else
			{
				pParent->pNext = NULL;
			}
		}
		//�����Ԫ��֮ǰû������Ԫ��
		else
		{
			//�������֮����Ԫ����֮���Ԫ����Ϊ��λ�õ�һ��Ԫ��
			if( pHashData->pNext != NULL )
			{
				mpHashTable[nPos] = pHashData->pNext;
				mpHashTable[nPos]->pPrev = NULL;
			}
			//�������֮��û��Ԫ���򽫸�λ�����
			else
				mpHashTable[nPos] = NULL;
		}

		//��ոù�ϣԪ����������ջ�е�ָ��
		*( mHashDataStack.Begin() + pHashData->nStackIndex ) = NULL;

		//�ͷŸù�ϣԪ���ڴ�
		free( pHashData );

		--mNumData;
	}
	//--------------------------------------------------------------------------------------------------------------
	//Ѱ��Ԫ��
	template <typename T> T* HashMap<T>::Find( const char* szKeyName )
	{
		//���������ϣֵ��Ϊ��Ԫ�����������е�λ��
		size_t nStrLen = 0;
		int nPos = Misc::HashString( szKeyName, &nStrLen ) % mnTableSize;

		//�������ַ�������
		if( nStrLen >= 32 )
		{
			Misc::ShowErrMsg( "��ϣ��%s�������������� %d ���ַ���", __FUNCSIG__, mMaxHashStrLen );
			return NULL;
		}

		//����ڹ�ϣ�����Ҳ�����Ԫ��
		if( mpHashTable[nPos] == NULL )
		{
			Misc::ShowErrMsg( "�ڹ�ϣ��%s�����Ҳ�������Ϊ '%s' ��Ԫ�ء�", __FUNCSIG__, szKeyName );
			return NULL;
		}

		//����ҵ�
		HashData* pHashData = mpHashTable[nPos];

		//�����λ�ò�ֻ��һ��Ԫ��
		if( pHashData->pNext != NULL )
		{
CheckNextKey:
			//�������������ͬ
			if( pHashData->nKeyNameLen == (unsigned short)nStrLen )
			{
				//�Ҽ�����ͬ
				if( 0 == memcmp( pHashData->szKeyName, szKeyName, nStrLen ) )
				{
					goto FoundKey;
				}
			}

			//�����λ��û������Ԫ����
			if( pHashData->pNext == NULL )
			{
				Misc::ShowErrMsg( "�ڹ�ϣ��%s�����Ҳ�������Ϊ '%s' ��Ԫ�ء�", __FUNCSIG__, szKeyName );
				return NULL;
			}
			//���������ѯ��һ����
			else
			{
				pHashData = pHashData->pNext;
				goto CheckNextKey;
			}
		}

FoundKey:
		return &pHashData->Data;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ص�ǰԪ����
	template <typename T> FKInline unsigned int HashMap<T>::Size() const
	{
		return mNumData;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================


#endif	/* #ifndef FK_NO_TEMPLATE_IMPLEMNTATION */

