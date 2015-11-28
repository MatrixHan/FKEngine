/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	FileSelectList
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�ļ�ѡ���б���
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "../CommonBase/Stack.h"
#include "../CommonBase/String.h"
#include "../CommonBase/StringArray.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	class FileSelectList;
	typedef Stack< FileSelectList* >	FileSelectLists;

	//--------------------------------------------------------------------------------------------------------------
	//�ļ�ѡ���б���
	class FK_DLL FileSelectList
	{
	public:
		String				mRelPath;		//���б�Ŀ¼�����·��

		StringArray			mDirList;		//��Ŀ¼�����б�
		StringArray			mFileList;		//�ļ������б�

		FileSelectList*		mpFatherList;	//���б�ĸ����ļ�ѡ���б�

		FileSelectLists		mSubSelectLists;//�Ӽ��ļ�ѡ���б�

	public:
		FileSelectList( LPCSTR szRelPath );
		virtual ~FileSelectList();

		//����ָ��Ŀ¼��ѡ���б�
		FileSelectList* AddDirToList( LPCSTR szDirName );

		//����ָ���ļ���ѡ���б�
		void AddFileToList( LPCSTR szFileName );

		//���б���ɾ��ָ��Ŀ¼
		void DelDirFromList( LPCSTR szDirName );

		//���б���ɾ��ָ���ļ�
		void DelFileFromList( LPCSTR szFileName );

		//���б���ɾ������Ŀ¼
		void DelAllDirFromList();

		//���б���ɾ�������ļ�
		void DelAllFileFromList();

		//��ȡ���б����·��
		String& GetRelPath();

		//��ȡ���б����ļ�ѡ���б�
		FileSelectList* GetFatherSelectList();

		//��ȡ�Ӽ�Ŀ¼���ļ�ѡ���б�
		FileSelectList* GetSubDirSelectList( LPCSTR szSubDirName );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
