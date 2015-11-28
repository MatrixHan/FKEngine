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
*	�ļ�˵����	�ڴ������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

#define FK_DEBUG_MEMORY_MANAGER			0x10000
#define FK_RELEASE_MEMORY_MANAGER		0x20000

//==================================================================================================================

#include "Misc.h"
#include "FileObject.h"
#include "TextFile.h"

//==================================================================================================================

//��������������Ƿ�ʹ�õ�ʽģʽ���ڴ������
#ifdef _DEBUG
	#define FK_MEMORY_MANAGER		FK_DEBUG_MEMORY_MANAGER
	#pragma message ( "����ģʽ�ڴ�������ѱ�����" )
#else
	#define FK_MEMORY_MANAGER		FK_RELEASE_MEMORY_MANAGER
	#pragma message ( "����ģʽ�ڴ�������ѱ�����" )
#endif

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
	//����ģʽ�ڴ����ӳ�亯��
	//--------------------------------------------------------------------------------------------------------------

	extern FK_DLL FKInline void* FK_Malloc( size_t MemSize, const char* FileName, const char* Function, const int Line );
	extern FK_DLL FKInline void* FK_Realloc( void* pOldMem, size_t MemSize, const char* FileName, const char* Function, const int Line );
	extern FK_DLL FKInline void FK_Free( void* pMem, const char* FileName, const char* Function, const int Line );

	//--------------------------------------------------------------------------------------------------------------

	static const char memBegin[]	= "MEM_BEGIN";	//�ڴ����ʼ��־
	static const char memEnd[]		= "MEM_END";	//�ڴ�������־

	//--------------------------------------------------------------------------------------------------------------

	//�ڴ����Ϣ���С
	#define FK_MEM_BLOCK_INFO_NUM		65535
	#define FK_MEM_BLOCK_INFO_PTR_SIZE	FK_MEM_BLOCK_INFO_NUM * sizeof(BlockInfo*)

	//--------------------------------------------------------------------------------------------------------------
	//����ģʽ�ڴ������
	class FK_DLL MemoryManager
	{
	public:
		static MemoryManager	sMemoryManager;	//�ڴ������

	protected:
		//�ڴ����Ϣ�ṹ
		struct BlockInfo
		{
			void*		pMem;		//�ڴ��ָ��

			size_t		nActSize;	//ʵ�ʷ����С
			size_t		nSize;		//�û������С

			char*		szFileName;	//���������ļ�
			char*		szFunName;	//�������ں���
			int			nLine;		//���������к�

			BlockInfo*	pPrevInfo;	//��һ���ڴ����Ϣ��ָ��
			BlockInfo*	pNextInfo;	//��һ���ڴ����Ϣ��ָ��
		};

		char*					mpTmpStr;		//��ʽ����Ϣ����

		HANDLE					mhInstHeap;		//�ó���ʵ����ջ���

		HANDLE					mhInfoHeap;		//�ڴ���Ϣ�洢��ջ���
		CRITICAL_SECTION		mInfoAccessFlag;//�ڴ���Ϣ���ʱ�־

		UINT					mnBlockCount;	//�ڴ������
		BlockInfo**				mppBlockInfo;	//�ڴ����Ϣָ���б�

		bool					mbCheckMemLeak;	//�Ƿ�����ڴ�й©

	public:
		//��ʼ���ڴ������
		bool _Initialize();

		//�ͷ��ڴ������
		void _Release();

		//C ��׼�ڴ����
		void* Malloc( size_t MemSize, const char* FileName, const char* Function, const int Line );
	
		//C ��׼�ڴ��ط���
		void* Realloc( void* pOldMem, size_t MemSize, const char* FileName, const char* Function, const int Line );

		//C ��׼�ڴ��ͷ�
		void Free( void* pMem, const char* FileName, const char* Function, const int Line );
	
		//����ڴ������־
		void DumpMemoryLogFile( const char* szFileName );

	protected:
		//��ʾ�ڴ���������Ϣ
		void _ShowOverflowMsg( const BlockInfo* pInfo, bool HeadOverflow, bool RearOverflow );
	
		//���ڴ�����ʽ����Ϣ
		char* _FormatMsg( int* pLen, const char* msg, ... );

	};
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
	//����ģʽ�ڴ����ӳ�亯��
	//--------------------------------------------------------------------------------------------------------------

	extern FK_DLL FKInline void* FK_Malloc( size_t MemSize );
	extern FK_DLL FKInline void* FK_Realloc( void* pOldMem, size_t MemSize );
	extern FK_DLL FKInline void FK_Free( void* pMem );

	//--------------------------------------------------------------------------------------------------------------
	//����ģʽ�ڴ������
	class FK_DLL MemoryManager
	{
	public:
		static MemoryManager	sMemoryManager;	//�ڴ������

	protected:
		static HANDLE			mhInstHeap;		//�ó���ʵ����ջ���

	public:
		//��ʼ���ڴ������
		bool _Initialize();

		//�ͷ��ڴ������
		void _Release();

		//C ��׼�ڴ����
		void* Malloc( size_t MemSize );

		//C ��׼�ڴ��ط���
		void* Realloc( void* pOldMem, size_t MemSize );

		//C ��׼�ڴ��ͷ�
		void Free( void* pMem );
	};
	//--------------------------------------------------------------------------------------------------------------
}
//==================================================================================================================


//==================================================================================================================
#endif	/* #if FK_MEMORY_MANAGER == FK_DEBUG_MEMORY_MANAGER */
//==================================================================================================================

//==================================================================================================================
#endif	/* #ifdef FK_MEMORY_MANAGER */
//==================================================================================================================
