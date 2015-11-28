/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	FileObject
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
	FileObject::FileObject()
		: mnCurDirLen	(0)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	FileObject::~FileObject()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ļ���ǰĿ¼
	void FileObject::SetFileDirectory( LPCSTR szCurDir )
	{
		if( szCurDir == NULL )
		{
			mszCurDir[0] = '\0';
			mnCurDirLen = 0;
		}

		mnCurDirLen = (UINT)strlen( szCurDir );
		memcpy( mszCurDir, szCurDir, mnCurDirLen );

		mszCurDir[ mnCurDirLen ] = '\\';
		mszCurDir[ ++mnCurDirLen ] = '\0';
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡָ���ļ���״̬
	int FileObject::GetFileStatus( LPCSTR szFileName )
	{
		//��ȡ�ļ�����
		DWORD dwAttributes = GetFileAttributes( szFileName );

		//�����ж��ļ��Ƿ����
		int nFileStatus;
		if( dwAttributes == INVALID_FILE_ATTRIBUTES )
			return FS_NotExist;
		else
			nFileStatus = FS_Exist;

		//�Ƿ�ΪĿ¼
		if( dwAttributes & FILE_ATTRIBUTE_DIRECTORY )
			nFileStatus |= FS_Directory;
		//�Ƿ�Ϊֻ��
		if( dwAttributes & FILE_ATTRIBUTE_READONLY )
			nFileStatus |= FS_ReadOnly;
		//�Ƿ�Ϊ����
		if( dwAttributes & FILE_ATTRIBUTE_HIDDEN )
			nFileStatus |= FS_Hidden;
		//�Ƿ�Ϊϵͳ
		if( dwAttributes & FILE_ATTRIBUTE_SYSTEM )
			nFileStatus |= FS_System;
		//�Ƿ�Ϊ�浵
		if( dwAttributes & FILE_ATTRIBUTE_ARCHIVE )
			nFileStatus |= FS_Archive;
		//�Ƿ�Ϊѹ��
		if( dwAttributes & FILE_ATTRIBUTE_COMPRESSED )
			nFileStatus |= FS_Compressed;

		return nFileStatus;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ���ļ�
	bool FileObject::Delete( LPCSTR szFileName, bool bDeleteReadOnly )
	{
		//ɾ���ļ�
		BOOL nResult = DeleteFile( szFileName );

		//���ɾ��ʧ��
		if( nResult == FALSE )
		{
			//�������Ϊ���ļ�Ϊֻ������������ɾ��ֻ���ļ�
			if( ERROR_ACCESS_DENIED == GetLastError() && bDeleteReadOnly )
			{
				//ȥ���ļ�ֻ������
				if( FALSE == SetFileAttributes( szFileName, FILE_ATTRIBUTE_NORMAL ) )
					return false;

				//ɾ���ļ�
				return ( FALSE == DeleteFile( szFileName ) ) ? false : true;
			}
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ڲ����ļ�����
	void FileObject::_InternalOpen( LPCSTR szFileName, OpenType eOpenType, bool bOverlapped, HANDLE* pHandle )
	{
		//����ļ���
		if( szFileName[0] == '\0' )
			Except( Exception::ERR_INVALIDPARAMS, "���ļ���Ϊ�ա�" );

		char* pFilePath = (char*)szFileName;

		//�ж�����·���Ƿ�Ϊ����·��
		bool bAbsPath = false;
		for( char* pChar = (char*)szFileName; *pChar != '\0'; ++pChar )
		{
			if( *pChar == ':' )
			{
				bAbsPath = true;
				break;
			}
		}

		//������Ǿ���·�������ļ���ǰĿ¼�������ļ���
		if( !bAbsPath )
		{
			UINT nFileNameLen = (UINT)strlen( szFileName );
			memcpy( mszCurDir + mnCurDirLen, szFileName, nFileNameLen + 1 );
			pFilePath = mszCurDir;
		}

		//����Ƿ��Ѵ��ļ�
		if( *pHandle != NULL )
			Except( Exception::ERR_INTERNAL_ERROR, "�޷��ظ����ļ���" );

		DWORD dwAccessFlag, dwShareMode, dwCreationDisposition;
		DWORD dwFlags = bOverlapped ? FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED : FILE_ATTRIBUTE_NORMAL;

		//����ļ�������
		switch (eOpenType)
		{
			//ֻ�����ȡ���ļ�������ڣ�
		case OT_Read:
			dwAccessFlag			= GENERIC_READ;
			dwShareMode				= FILE_SHARE_READ;
			dwCreationDisposition	= OPEN_EXISTING;
			break;
			//ֻ����д�루����ԭ�ļ���
		case OT_Write:
			dwAccessFlag			= GENERIC_WRITE;
			dwShareMode				= FILE_SHARE_WRITE;
			dwCreationDisposition	=
				( FileObject::GetFileStatus( szFileName ) != FS_NotExist ) ? TRUNCATE_EXISTING : CREATE_NEW;
			break;
			//ֻ����д�루���������ݣ�
		case OT_WriteAppend:
			dwAccessFlag			= GENERIC_WRITE;
			dwShareMode				= FILE_SHARE_WRITE;
			dwCreationDisposition	= OPEN_ALWAYS;
			break;
			//��ȡ��д�루�ļ�������ڣ�
		case OT_ReadWirte:
			dwAccessFlag			= GENERIC_READ | GENERIC_WRITE;
			dwShareMode				= FILE_SHARE_READ | FILE_SHARE_WRITE;
			dwCreationDisposition	= OPEN_ALWAYS;
			break;
		default:
			Except( Exception::ERR_INVALIDPARAMS,
				(String)"ʹ�÷Ƿ��Ĵ����ʹ��ļ�'" + (String)szFileName + "'��" );
		}

		//�����ļ����
		*pHandle = CreateFile( pFilePath, dwAccessFlag, dwShareMode, NULL, dwCreationDisposition, dwFlags, NULL );
		if( *pHandle == INVALID_HANDLE_VALUE )
			Except( Exception::ERR_CANNOT_OPEN_FILE, (String)"�޷����ļ� '" + pFilePath + "'��" );

		//�ָ���ǰĿ¼����β
		if( !bAbsPath )
			mszCurDir[ mnCurDirLen ] = '\0';
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
