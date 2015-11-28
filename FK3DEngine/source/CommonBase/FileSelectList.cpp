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
	FileSelectList::FileSelectList( LPCSTR szRelPath )
		: mRelPath		(szRelPath)
		, mpFatherList	(NULL)
	{
		mSubSelectLists.Initialize( 8, 16 );
	}
	//--------------------------------------------------------------------------------------------------------------
	FileSelectList::~FileSelectList()
	{
		DelAllDirFromList();
		DelAllFileFromList();

		mSubSelectLists.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ָ��Ŀ¼��ѡ���б�
	FileSelectList* FileSelectList::AddDirToList( LPCSTR szDirName )
	{
		//�����Ƽ����б�
		mDirList.Push( szDirName );

		//���ø���Ŀ¼�����·���ַ���
		String TmpString( mRelPath );
		TmpString.AppendString( "\\" );
		TmpString.AppendString( szDirName );

		//��������Ŀ¼���Ӽ��ļ�ѡ���б�
		FileSelectList* pFileSelectList = new FileSelectList( TmpString.GetCharPtr() );
		pFileSelectList->mpFatherList = this;
		*mSubSelectLists.Push() = pFileSelectList;

		return pFileSelectList;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ָ���ļ���ѡ���б�
	void FileSelectList::AddFileToList( LPCSTR szFileName )
	{
		//�����Ƽ����б�
		mFileList.Push( szFileName );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���б���ɾ��ָ��Ŀ¼
	void FileSelectList::DelDirFromList( LPCSTR szDirName )
	{
		FileSelectLists::Iterator fit = mSubSelectLists.Begin();

		StringArray::Iterator it = mDirList.Begin();
		StringArray::Iterator end = mDirList.End();
		for(; it!=end; ++it, ++fit )
		{
			if( it != NULL && 0 == strcmp( it->mpCharString, szDirName ) )
			{
				mDirList.Erase( it );
				mSubSelectLists.Erase( fit );

				SafeDelete( fit );

				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���б���ɾ��ָ���ļ�
	void FileSelectList::DelFileFromList( LPCSTR szFileName )
	{
		StringArray::Iterator it = mFileList.Begin();
		StringArray::Iterator end = mFileList.End();
		for(; it!=end; ++it )
		{
			if( it != NULL && 0 == strcmp( it->mpCharString, szFileName ) )
			{
				mFileList.Erase( it );
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���б���ɾ������Ŀ¼
	void FileSelectList::DelAllDirFromList()
	{
		FileSelectLists::Iterator fit = mSubSelectLists.Begin();
		FileSelectLists::Iterator fend = mSubSelectLists.End();
		for(; fit!=fend; ++fit )
		{
			if( fit != NULL )
				delete *fit;
		}

		mDirList.Clear();
		mSubSelectLists.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���б���ɾ�������ļ�
	void FileSelectList::DelAllFileFromList()
	{
		mFileList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ���б����·��
	String& FileSelectList::GetRelPath()
	{
		return mRelPath;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ���б����ļ�ѡ���б�
	FileSelectList* FileSelectList::GetFatherSelectList()
	{
		return mpFatherList;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�Ӽ�Ŀ¼���ļ�ѡ���б�
	FileSelectList* FileSelectList::GetSubDirSelectList( LPCSTR szSubDirName )
	{
		FileSelectLists::Iterator fit = mSubSelectLists.Begin();

		StringArray::Iterator it = mDirList.Begin();
		StringArray::Iterator end = mDirList.End();
		for(; it!=end; ++it, ++fit )
		{
			if( it != NULL && 0 == strcmp( it->mpCharString, szSubDirName ) )
				return *fit;
		}

		return NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
