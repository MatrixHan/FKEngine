/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	MemoryManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/CommonBase/MemoryManager.h"
//#include "../../include/CommonBase/NoMemoryMarco.h"
#include <stdio.h>


//==================================================================================================================
//���������ʹ���ڴ������
#ifdef FK_MEMORY_MANAGER
//==================================================================================================================

//==================================================================================================================
//���Ϊ����ģʽ�ڴ������
#if FK_MEMORY_MANAGER == FK_DEBUG_MEMORY_MANAGER
//==================================================================================================================


//==================================================================================================================
namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	//�ڴ������
	MemoryManager	MemoryManager::sMemoryManager;

	//--------------------------------------------------------------------------------------------------------------
	//����ģʽ�ڴ����ӳ�亯��
	//--------------------------------------------------------------------------------------------------------------
	FKInline void* FK_Malloc( size_t MemSize, const char* FileName, const char* Function, const int Line )
	{
		return MemoryManager::sMemoryManager.Malloc( MemSize, FileName, Function, Line );
	}
	//--------------------------------------------------------------------------------------------------------------
	FKInline void* FK_Realloc( void* pOldMem, size_t MemSize, const char* FileName, const char* Function, const int Line )
	{
		return MemoryManager::sMemoryManager.Realloc( pOldMem, MemSize, FileName, Function, Line );
	}
	//--------------------------------------------------------------------------------------------------------------
	FKInline void FK_Free( void* pMem, const char* FileName, const char* Function, const int Line )
	{
		MemoryManager::sMemoryManager.Free( pMem, FileName, Function, Line );
	}
	//--------------------------------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------------------------------
	//�ڴ����������
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ���ڴ������
	bool MemoryManager::_Initialize()
	{
		//��ȡ�ó���ʵ����ջ���
		mhInstHeap = GetProcessHeap();
		if( mhInstHeap == NULL )
			return false;

		//�����ڴ���Ϣ���ݴ洢��ջ
		mhInfoHeap = HeapCreate( 0, FK_MEM_BLOCK_INFO_PTR_SIZE * 4, 0 );
		if( mhInfoHeap == NULL )
			return false;

		//��ʼ���ڴ���Ϣ���ݷ��ʱ�־
		InitializeCriticalSection( &mInfoAccessFlag );

		//�����ڴ���Ϣ���ݴ洢�ڴ�
		EnterCriticalSection( &mInfoAccessFlag );
		mppBlockInfo = (BlockInfo**)HeapAlloc( mhInfoHeap, HEAP_ZERO_MEMORY, FK_MEM_BLOCK_INFO_PTR_SIZE );
		LeaveCriticalSection( &mInfoAccessFlag );

		if( mppBlockInfo == NULL )
			return false;

		mnBlockCount = 0;
		mbCheckMemLeak = true;

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷ��ڴ������
	void MemoryManager::_Release()
	{
		//����ڴ������־
		SafeFree( mpTmpStr );

		//��ʼ�ڴ���Ϣ���ݷ���
		EnterCriticalSection( &mInfoAccessFlag );

		//�ͷ������ڴ����Ϣ
		UINT CheckedCount = 0;
		BlockInfo** ppInfo = mppBlockInfo;
		for( UINT i=0; i<FK_MEM_BLOCK_INFO_NUM; ++i )
		{
			BlockInfo* pInfo = *ppInfo;

			//������ڴ��δ���ͷ�
			while( pInfo != NULL )
			{
				pInfo = pInfo->pNextInfo;
				++CheckedCount;

				HeapFree( mhInfoHeap, 0, pInfo );
			}

			if( CheckedCount > i )
				break;

			++ppInfo;
		}

		//�ͷ��ڴ���Ϣ���ݴ洢�ڴ�
		HeapFree( mhInfoHeap, 0, mppBlockInfo );
		mppBlockInfo = NULL;

		//�����ڴ���Ϣ���ݷ���
		LeaveCriticalSection( &mInfoAccessFlag );

		//ɾ���ڴ���Ϣ���ݷ��ʱ�־
		DeleteCriticalSection( &mInfoAccessFlag );

		//ɾ���ڴ���Ϣ���ݴ洢��ջ
		HeapDestroy( mhInfoHeap );
	}
	//--------------------------------------------------------------------------------------------------------------
	//C ��׼�ڴ����
	void* MemoryManager::Malloc( size_t MemSize, const char* FileName, const char* Function, const int Line )
	{
		if( MemSize == 0 )
			return NULL;

		size_t ActSize = MemSize + 16;	//�ڴ��ʵ��ʹ���ڴ�
		void* pMem;

		//��ʼ�ڴ���Ϣ���ݷ���
		EnterCriticalSection( &mInfoAccessFlag );

		//�����ڴ�
		pMem = HeapAlloc( mhInstHeap, 0, ActSize );
		if( pMem == NULL )
		{
			LeaveCriticalSection( &mInfoAccessFlag );
			return NULL;
		}

		//���ø��ڴ��ͷβ�����־
		memcpy( pMem, memBegin, 9 );
		memcpy( (char*)pMem + ActSize - 7, memEnd, 7 );


		//�����������ڴ�й©
		if( mbCheckMemLeak )
		{
			//������ڴ��λ��
			size_t BlockNum = ( (size_t)pMem >> 4 ) & ( FK_MEM_BLOCK_INFO_NUM - 1 );

			//�����ڴ���ڴ�
			BlockInfo* pBlockInfo = mppBlockInfo[BlockNum];
			BlockInfo* pNewInfo = (BlockInfo*)HeapAlloc( mhInfoHeap, HEAP_ZERO_MEMORY, sizeof(BlockInfo) );

			if( pBlockInfo != NULL )
			{
				if( pBlockInfo->pNextInfo != NULL )
				{
					pNewInfo->pNextInfo = pBlockInfo->pNextInfo;
					pBlockInfo->pNextInfo->pPrevInfo = pNewInfo;
				}

				pBlockInfo->pNextInfo = pNewInfo;
				pNewInfo->pPrevInfo = pBlockInfo;
			}
			else
			{
				mppBlockInfo[BlockNum] = pNewInfo;
			}

			//�����ڴ����Ϣ
			pNewInfo->pMem			= pMem;
			pNewInfo->nActSize		= ActSize;
			pNewInfo->nSize			= MemSize;
			pNewInfo->szFileName	= (char*)FileName;
			pNewInfo->szFunName		= (char*)Function;
			pNewInfo->nLine			= Line;

			++mnBlockCount;
		}

		//�����ڴ���Ϣ���ݷ���
		LeaveCriticalSection( &mInfoAccessFlag );

		return (char*)pMem + 9;
	}
	//--------------------------------------------------------------------------------------------------------------
	//C ��׼�ڴ��ط���
	void* MemoryManager::Realloc( void* pOldMem, size_t MemSize, const char* FileName,
		const char* Function, const int Line )
	{
		if( MemSize == 0 || pOldMem == NULL )
			return NULL;

		pOldMem = (void*)( (char*)pOldMem - 9 );

		size_t ActSize = MemSize + 16;	//�ڴ��ʵ��ʹ���ڴ�

		//��ʼ�ڴ���Ϣ���ݷ���
		EnterCriticalSection( &mInfoAccessFlag );

		//�����������ڴ�й©
		if( mbCheckMemLeak )
		{
			//����þ��ڴ��λ��
			size_t OldBlockNum = ( (size_t)pOldMem >> 4 ) & ( FK_MEM_BLOCK_INFO_NUM - 1 );

			//Ѱ�Ҿ��ڴ���Ϣλ��
			BlockInfo* pOldInfo = mppBlockInfo[OldBlockNum];

			//�����λ���Ѿ����ظ���¼
			while( pOldInfo->pMem != pOldMem )
			{
				if( pOldInfo->pNextInfo == NULL )
				{
					Misc::ShowErrMsg( "�Ҳ���ָ������Ҫ�ٷ�����ڴ�顣" );
					LeaveCriticalSection( &mInfoAccessFlag );
					return NULL;
				}

				pOldInfo = pOldInfo->pNextInfo;
			}

			//�����ڴ���Ϣ�Ӹ�λ�õ���Ϣ�б���ɾ��
			if( pOldInfo->pNextInfo != NULL )
			{
				if( pOldInfo->pPrevInfo != NULL )
				{
					pOldInfo->pNextInfo->pPrevInfo = pOldInfo->pPrevInfo;
					pOldInfo->pPrevInfo->pNextInfo = pOldInfo->pNextInfo;
				}
				else
				{
					pOldInfo->pNextInfo->pPrevInfo = NULL;
					mppBlockInfo[OldBlockNum] = pOldInfo->pNextInfo;
				}
			}
			else if( pOldInfo->pPrevInfo == NULL )
			{
				mppBlockInfo[OldBlockNum] = NULL;
			}

			//ɾ����λ���ڴ���Ϣ
			HeapFree( mhInfoHeap, 0, pOldInfo );
		}


		//�����ڴ�
		void* pMem = HeapReAlloc( mhInstHeap, 0, pOldMem, ActSize );
		if( pMem == NULL )
		{
			LeaveCriticalSection( &mInfoAccessFlag );
			return NULL;
		}

		//���ø��ڴ��ͷβ�����־
		memcpy( pMem, memBegin, 9 );
		memcpy( (char*)pMem + ActSize - 7, memEnd, 7 );


		//�����������ڴ�й©
		if( mbCheckMemLeak )
		{
			//������ڴ��λ��
			size_t BlockNum = ( (size_t)pMem >> 4 ) & ( FK_MEM_BLOCK_INFO_NUM - 1 );

			//�����ڴ���ڴ�
			BlockInfo* pBlockInfo = mppBlockInfo[BlockNum];
			BlockInfo* pNewInfo = (BlockInfo*)HeapAlloc( mhInfoHeap, HEAP_ZERO_MEMORY, sizeof(BlockInfo) );

			if( pBlockInfo != NULL )
			{
				pBlockInfo->pNextInfo = pNewInfo;
				pNewInfo->pPrevInfo = pBlockInfo;
			}
			else
			{
				mppBlockInfo[BlockNum] = pNewInfo;
			}

			//�����ڴ����Ϣ
			pNewInfo->pMem			= pMem;
			pNewInfo->nActSize		= ActSize;
			pNewInfo->nSize			= MemSize;
			pNewInfo->szFileName	= (char*)FileName;
			pNewInfo->szFunName		= (char*)Function;
			pNewInfo->nLine			= Line;
		}


		//�����ڴ���Ϣ���ݷ���
		LeaveCriticalSection( &mInfoAccessFlag );

		return (char*)pMem + 9;
	}
	//--------------------------------------------------------------------------------------------------------------
	//C ��׼�ڴ��ͷ�
	void MemoryManager::Free( void* pMem, const char* FileName, const char* Function, const int Line )
	{
		if( pMem == NULL )
			return;

		pMem = (void*)( (char*)pMem - 9 );

		//��ʼ�ڴ���Ϣ���ݷ���
		EnterCriticalSection( &mInfoAccessFlag );

		//�����������ڴ�й©
		if( mbCheckMemLeak )
		{
			//����þ��ڴ��λ��
			size_t BlockNum = ( (size_t)pMem >> 4 ) & ( FK_MEM_BLOCK_INFO_NUM - 1 );

			//Ѱ�Ҿ��ڴ���Ϣλ��
			BlockInfo* pInfo = mppBlockInfo[BlockNum];
			if( pInfo == NULL )
			{
				Misc::ShowErrMsg( "�Ҳ���ָ������Ҫ�ͷŵ��ڴ�顣" );
				goto FreeMem;
			}

			//�����λ���Ѿ����ظ���¼
			while( pInfo->pMem != pMem )
			{
				if( pInfo->pNextInfo == NULL )
				{
					Misc::ShowErrMsg( "�Ҳ���ָ������Ҫ�ͷŵ��ڴ�顣" );
					goto FreeMem;
				}

				pInfo = pInfo->pNextInfo;
			}

			//����ڴ�������
			bool HeadOverflow = ( 0 != memcmp( pMem, memBegin, 9 ) ) ? true : false;
			bool RearOverflow = ( 0 != memcmp( (char*)pMem + pInfo->nActSize - 7, memEnd, 7 ) ) ? true : false;
			if( HeadOverflow || RearOverflow )
				_ShowOverflowMsg( pInfo, HeadOverflow, RearOverflow );

			//�����ڴ���Ϣ�Ӹ�λ�õ���Ϣ�б���ɾ��
			if( pInfo->pNextInfo != NULL )
			{
				if( pInfo->pPrevInfo != NULL )
				{
					pInfo->pNextInfo->pPrevInfo = pInfo->pPrevInfo;
					pInfo->pPrevInfo->pNextInfo = pInfo->pNextInfo;
				}
				else
				{
					pInfo->pNextInfo->pPrevInfo = NULL;
					mppBlockInfo[BlockNum] = pInfo->pNextInfo;
				}
			}
			else
			{
				if( pInfo->pPrevInfo != NULL )
					pInfo->pPrevInfo->pNextInfo = NULL;
				else
					mppBlockInfo[BlockNum] = NULL;
			}

			//ɾ����λ���ڴ���Ϣ
			HeapValidate( mhInfoHeap, 0, pInfo );
			HeapFree( mhInfoHeap, 0, pInfo );

			--mnBlockCount;
		}

FreeMem:
		//ɾ�����ڴ��
		HeapValidate( mhInstHeap, 0, pMem );
		HeapFree( mhInstHeap, 0, pMem );

		//�����ڴ���Ϣ���ݷ���
		LeaveCriticalSection( &mInfoAccessFlag );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ڴ������־
	void MemoryManager::DumpMemoryLogFile( const char* szFileName )
	{
		//���ȹر��ڴ�й©���
		mbCheckMemLeak = false;

		//������־�ļ�
		TextFile File( szFileName, OT_Write );

		//��ȡ���ں�ʱ��
		char szDate[20] = { NULL };
		GetDateFormat( LOCALE_SYSTEM_DEFAULT, NULL, NULL, "yyyy �� MM �� dd ��", szDate, sizeof(szDate) );

		char szTime[18] = { NULL };
		GetTimeFormat( LOCALE_SYSTEM_DEFAULT, NULL, NULL, "HH ʱ mm �� ss ��", szTime, sizeof(szTime) );

		//д����־ͷ
		int StrLen = 0;
		char* pStr = _FormatMsg( &StrLen,
			"--------------------------------------------------------------------------------------------\n"
			"-                               ������ʿ3D��Ϸ�����ڴ������־                             -\n"
			"--------------------------------------------------------------------------------------------\n"
			"\n���ڣ�%s\nʱ�䣺%s\n\n", szDate, szTime );
		File.Write( pStr, StrLen );

		//����������κ��ڴ�й©
		if( mnBlockCount == 0 )
		{
			const char szNoOverflow[] = "\n��ϲ��������û�з����κε��ڴ�й©��\n";
			File.Write( szNoOverflow, sizeof(szNoOverflow) );
		}
		else
		{
			pStr = _FormatMsg( &StrLen, "\n�����ܹ����� %d ���ڴ�й©��\n\n", mnBlockCount );
			File.Write( pStr, StrLen );

			//�������м�¼��Ϣ����ڴ�й©
			UINT CheckedCount = 0;
			BlockInfo** ppInfo = mppBlockInfo;
			for( UINT i=0; i<FK_MEM_BLOCK_INFO_NUM; ++i )
			{
				BlockInfo* pInfo = *ppInfo;

				//������ڴ��δ���ͷ�
				while( pInfo != NULL )
				{
					pStr = _FormatMsg( &StrLen,
						"\n�ڴ��ַ�� 0x%X\n"
						"ʵ�ʴ�С�� %d\n"
						"��Ч��С�� %d\n"
						"�����ļ��� %s\n"
						"���亯���� %s\n"
						"�����кţ� %d\n",
						pInfo->pMem, pInfo->nActSize, pInfo->nSize, pInfo->szFileName, pInfo->szFunName, pInfo->nLine );

					File.Write( pStr, StrLen );

					pInfo = pInfo->pNextInfo;
					++CheckedCount;
				}

				if( CheckedCount > i )
					break;

				++ppInfo;
			}
		}

		File.Close();

		//�����ڴ�й©���
		mbCheckMemLeak = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʾ�ڴ���������Ϣ
	void MemoryManager::_ShowOverflowMsg( const BlockInfo* pInfo, bool HeadOverflow, bool RearOverflow )
	{
		char* pOverflowDesc = NULL;
		if( HeadOverflow && RearOverflow )
			pOverflowDesc = "�ײ���β��";
		else if( HeadOverflow )
			pOverflowDesc = "�ײ�";
		else if( RearOverflow )
			pOverflowDesc = "β��";
		else
			return;

		char* pStr = _FormatMsg( NULL,
			"�ڴ��%s���������\n\n"
			"�ڴ��ַ�� 0x%X\n"
			"ʵ�ʴ�С�� %d\n"
			"��Ч��С�� %d\n"
			"�����ļ��� %s\n"
			"���亯���� %s\n"
			"�����кţ� %d",
			pOverflowDesc,
			pInfo->pMem, pInfo->nActSize, pInfo->nSize, pInfo->szFileName, pInfo->szFunName, pInfo->nLine );
		MessageBox( GetActiveWindow(), pStr, "����", MB_OK | MB_ICONERROR );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ڴ�����ʽ����Ϣ
	char* MemoryManager::_FormatMsg( int* pLen, const char* msg, ... )
	{
		//��ȡ�����б�
		va_list args;
		va_start( args, msg );

		//��ȡ��ʽ����ʾ��Ϣ������ַ������ȣ�����Ҫһ�� NULL ��β�ַ��ռ䣩
		int len = _vscprintf( msg, args ) + 1;

		//�ͷ���һ��ʹ�õ��ַ����ڴ�
		SafeFree( mpTmpStr );

		//�����ַ����ڴ�
		mpTmpStr = (char*)malloc( len );
		if( mpTmpStr == NULL )
		{
			MessageBox( GetActiveWindow(), "���ø�ʽ����Ϣ����ʱ�������ʽ����Ϣ�ַ������ڴ�ʧ�ܡ�", "����", MB_OK );
			return NULL;
		}

		//��ʽ������ʾ��Ϣ
		vsprintf( mpTmpStr, msg, args );

		if( pLen != NULL )
			*pLen = len;

		return mpTmpStr;
	}
	//--------------------------------------------------------------------------------------------------------------
}
//==================================================================================================================


//==================================================================================================================
//���Ϊ����ģʽ�ڴ������
#else if FK_MEMORY_MANAGER == FK_RELEASE_MEMORY_MANAGER
//==================================================================================================================


//==================================================================================================================
namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------------------------------
	//����ģʽ�ڴ����ӳ�亯��
	//--------------------------------------------------------------------------------------------------------------
	FKInline void* FK_Malloc( size_t MemSize )
	{
		return MemoryManager::sMemoryManager.Malloc( MemSize );
	}
	//--------------------------------------------------------------------------------------------------------------
	FKInline void* FK_Realloc( void* pOldMem, size_t MemSize )
	{
		return MemoryManager::sMemoryManager.Realloc( pOldMem, MemSize );
	}
	//--------------------------------------------------------------------------------------------------------------
	FKInline void FK_Free( void* pMem )
	{
		MemoryManager::sMemoryManager.Free( pMem );
	}
	//--------------------------------------------------------------------------------------------------------------

	
	//--------------------------------------------------------------------------------------------------------------

	MemoryManager	MemoryManager::sMemoryManager;	//�ڴ������
	HANDLE			MemoryManager::mhInstHeap;		//�ó���ʵ����ջ���

	//--------------------------------------------------------------------------------------------------------------
	//�ڴ����������
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ���ڴ������
	bool MemoryManager::_Initialize()
	{
		//��ȡ�ó���ʵ����ջ���
		mhInstHeap = GetProcessHeap();
		if( mhInstHeap == NULL )
			return false;

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷ��ڴ������
	void MemoryManager::_Release()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//C ��׼�ڴ����
	void* MemoryManager::Malloc( size_t MemSize )
	{
		if( MemSize == 0 )
			return NULL;

		//�����ڴ�
		return HeapAlloc( mhInstHeap, 0, MemSize );
	}
	//--------------------------------------------------------------------------------------------------------------
	//C ��׼�ڴ��ط���
	void* MemoryManager::Realloc( void* pOldMem, size_t MemSize )
	{
		if( MemSize == 0 || pOldMem == NULL )
			return NULL;

		//�����ڴ�
		return HeapReAlloc( mhInstHeap, 0, pOldMem, MemSize );
	}
	//--------------------------------------------------------------------------------------------------------------
	//C ��׼�ڴ��ͷ�
	void MemoryManager::Free( void* pMem )
	{
		//ɾ�����ڴ��
		HeapValidate( mhInstHeap, 0, pMem );
		HeapFree( mhInstHeap, 0, pMem );
	}
	//--------------------------------------------------------------------------------------------------------------
}
//==================================================================================================================


//==================================================================================================================
#endif	/* #if FK_MEMORY_MANAGER == FK_DEBUG_MEMORY_MANAGER */
//==================================================================================================================

//==================================================================================================================
#endif	/* #ifdef FK_MEMORY_MANAGER */
//==================================================================================================================

#include "../../include/CommonBase/MemoryMarco.h"