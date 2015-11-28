/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Macros
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	����궨��
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
//���ú궨��
#define FKExport					__declspec(dllexport)		// DLL ����
#define FKImport					__declspec(dllimport)		// DLL ����
#define FKFastcall					__fastcall					//���ٺ������ù���
#define FKInline					__inline					//������������
#define FKForceInline				__forceinline				//ǿ����������
#define FKAlign16					__declspec(align(16))		//���� 16 �ֽڶ���
#define FKNaked						__declspec(naked)			//��������������Ӻ�����ʼ���ͽ�������


//����ڰ�����ͷ�ļ�ǰ���� FK_DLL_EXPORT ��Ϊ DLL ���������� FK_DLL_IMPORT ��Ϊ DLL ���룬�������򲻽��� DLL ���������롣
#ifdef FK_DLL_EXPORT
	#define FK_DLL		FKExport
#else
	#ifdef FK_DLL_IMPORT
		#define FK_DLL		FKImport
	#else
		#define FK_DLL
	#endif
#endif


//�ڴ�����
#define SafeFree( Pointer )			{ if( Pointer != NULL )		{ free( Pointer ); Pointer = NULL; } }
#define SafeDelete( Pointer )		{ if( Pointer != NULL )		{ delete Pointer; Pointer = NULL; } }
#define SafeDeleteArray( Array )	{ if( Array != NULL )		{ delete [] Array; Array = NULL; } }
#define SafeRelease( Interface )	{ if( Interface != NULL )	{ Interface->Release(); Interface = NULL; } }


//�����Ƿ�Ϊ����ģʽ��һЩ�ڴ��ͷź�ӳ�䵽��ͬ�ĺ�
#ifdef _DEBUG
	#define FKFree( Pointer )			SafeFree( Pointer )
	#define FKDelete( Pointer )			SafeDelete( Pointer )
	#define FKDeleteArray( Array )		SafeDeleteArray( Array )
	#define FKRelease( Interface )		SafeRelease( Interface )
#else
	#define FKFree( Pointer )			{ free( Pointer ); }
	#define FKDelete( Pointer )			{ delete Pointer; }
	#define FKDeleteArray( Array )		{ delete [] Array; }
	#define FKRelease( Interface )		{ Interface->Release(); }
#endif


#define FK_MAX( a, b )						( ( (a) > (b) ) ? (a) : (b) )	//���ֵ��
#define FK_MIN( a, b )						( ( (a) < (b) ) ? (a) : (b) )	//��Сֵ��

// FOURCC ���ɺ�
#define FK_FOURCC( ch1, ch2, ch3, ch4 )		((DWORD)(BYTE)(ch1) | ((DWORD)(BYTE)(ch2) << 8) | \
											((DWORD)(BYTE)(ch3) << 16) | ((DWORD)(BYTE)(ch4) << 24 ))
