/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	AppEntry
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	������ڴ��� ͷ�ļ�
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include <iostream>
#include "MemoryManager.h"
//==================================================================================================================

#ifndef _WINDOWS
#error ֻ�� Windows ���������������ڴ���
#endif

//==================================================================================================================

// C ����ʱ�⺯������
extern "C" int __cdecl _heap_init( int );
extern "C" int __cdecl _mtinit();
extern "C" int __cdecl _ioinit();
extern "C" int __cdecl _cinit( int );
extern "C" _CRTIMP void __cdecl _cexit();
extern "C" void __cdecl __crtExitProcess( int );

//Ӧ�ó�����ں���
extern int WinMainEntry();

//==================================================================================================================

#ifndef _FK_WIDECHAR_
	extern "C" int __cdecl main( int, char**, char** )
	{
		return 0;
	}
#else
	extern "C" int __cdecl wmain( int, wchar_t**, wchar_t** )
	{
		return 0;
	}
#endif

//==================================================================================================================

//��ʾ��ڳ��������Ϣ
void ShowEntryErrMsg( const char* szErrMsg )
{
	MessageBox( GetActiveWindow(), szErrMsg, "��ڳ������", MB_OK | MB_ICONERROR | MB_TASKMODAL );
}

//==================================================================================================================

//ϵͳ��ں���
#ifdef _FK_WIDECHAR_
	extern "C" int wWinMainCRTStartup()
#else
	extern "C" int WinMainCRTStartup()
#endif

{
	int nResult;

	//�����Ҫ����ڴ������־�������ȼ�¼��������·����
#if FK_MEMORY_MANAGER == FK_DEBUG_MEMORY_MANAGER
	char szMemLogPath[ MAX_PATH+1 ] = { NULL };
	GetCurrentDirectory( MAX_PATH+1, szMemLogPath );
	strcat_s( szMemLogPath, "\\FKMemLog.log" );
#endif

	//��ʼ��������ڴ�
#ifdef _MT
	if( !_heap_init(1) )
#else  /* _MT */
	if( !_heap_init(0) )
#endif /* _MT */
	{
		ShowEntryErrMsg( "��ʼ��������ڴ棨Heap������" );
		return -1;
	}

	//��ʼ�����̹߳������
#ifdef _MT
	if( !_mtinit() )
	{
		ShowEntryErrMsg( "��ʼ�����̹߳���������" );
		return -1;
	}
#endif  /* _MT */

	if( _ioinit() < 0 )
	{
		ShowEntryErrMsg( "��ʼ�� IO ����������" );
		return -1;
	}

	//��ʼ���ڴ������
	if( !MemoryManager::sMemoryManager._Initialize() )
	{
		ShowEntryErrMsg( "��ʼ���ڴ����������" );
		return -1;
	}

	//��ʼ��ȫ������
	if( 0 != _cinit( TRUE ) )
	{
		ShowEntryErrMsg( "��ʼ��ȫ�����ݴ���" );
		return -1;
	}

	//����Ӧ�ó�����ں���
	nResult = WinMainEntry();

	//�ͷ�ȫ������
	_cexit();

	//�ͷ��ڴ������
	//д���ڴ������־
#if FK_MEMORY_MANAGER == FK_DEBUG_MEMORY_MANAGER
	MemoryManager::sMemoryManager.DumpMemoryLogFile( szMemLogPath );
#endif

	MemoryManager::sMemoryManager._Release();

	//��ֹ����
	__crtExitProcess( nResult );

	return nResult;
}

//==================================================================================================================
