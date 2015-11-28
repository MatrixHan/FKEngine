/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	FKPFile
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
	FKPFile::FKPFile()
		: mpCurFileInfo	(NULL)
		, mnRemainLen	(0)
		, mnCurPos		(0)
	{
		memset( &mPackInfo, 0, sizeof(FKPPackInfo) );

		mDirInfoList.Initialize( 32, 32 );
		mFileInfoList.Initialize( 256, 256 );
	}
	//--------------------------------------------------------------------------------------------------------------
	FKPFile::~FKPFile()
	{
		ClosePack();

		mDirInfoList.Release();
		mFileInfoList.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ļ�
	void FKPFile::CreatePack( LPCSTR szPackName, LPCSTR szBasePath, StringArray* pFileNames, int nSubLevel )
	{
		//���ȹر��ļ���
		ClosePack();

		//���ݵ�ǰ����·��
		char szPathBackup[MAX_PATH];
		if( FALSE == GetCurrentDirectory( MAX_PATH, szPathBackup ) )
			Except( Exception::ERR_WINAPI_ERROR, "��ȡ����ǰ·��ʧ�ܡ�" );

		//����ǰ·������Ϊ��Ҫ����ļ��Ļ�׼·��
		if( szBasePath != NULL )
		{
			if( FALSE == SetCurrentDirectory( szBasePath ) )
				Except( Exception::ERR_WINAPI_ERROR, (String)"����ָ����·�� '" + szBasePath + "' ʧ�ܡ�" );
		}


		//������Ŀ¼����Ҫ������ļ�
		StringArray::Iterator it = pFileNames->Begin();
		StringArray::Iterator end = pFileNames->End();
		for(; it!=end; ++it )
		{
			//�ж��ļ�״̬�Ƿ�����
			int nFileStatus = FileObject::GetFileStatus( it->mpCharString );
			if( nFileStatus == FS_NotExist )
			{
				Except( Exception::ERR_INVALIDPARAMS, (String)"�ļ� '" + it->mpCharString + "' �����ڣ��޷������" );
			}
			else if( nFileStatus & FS_Compressed )
			{
				Except( Exception::ERR_INVALIDPARAMS, (String)"�ļ� '" + it->mpCharString + "' ��ѹ���ļ����޷������" );
			}

			//��ȥ·����������ļ�������
			int nFileTitlePos = it->GetLastCharIndex('\\') + 1;
			int nFileTitleLen = (int)it->mnCharLength - nFileTitlePos;
			char* pFileName = it->mpCharString + nFileTitlePos;
			if( nFileTitleLen > FKP_FileNameLen - 1 )
			{
				Except( Exception::ERR_INVALIDPARAMS, (String)"�ļ� '" + it->mpCharString + "' ���ƹ������޷������" );
			}

			//����ļ�ΪĿ¼
			if( nFileStatus & FS_Directory )
			{
				//�������Ŀ¼�б�
				FKPDirInfo* pDirInfo = mDirInfoList.Push();

				memcpy( pDirInfo->szDirName, pFileName, nFileTitleLen + 1 );
				pDirInfo->nNameID = Misc::HashString( pFileName );
			}
			//�������ͨ�ļ�����Ŀ¼��
			else
			{
				//��������ļ��б�
				FKPFileInfo* pFileInfo = mFileInfoList.Push();

				memcpy( pFileInfo->szFileName, pFileName, nFileTitleLen + 1 );
				pFileInfo->nNameID = Misc::HashString( pFileName );
			}
		}

		mPackInfo.nRootDirEnd		= mDirInfoList.Size();
		mPackInfo.nRootFileEnd		= mFileInfoList.Size();

		//�����Ŀ¼�µ��ļ���Ŀ¼��Ϣ�б�
		_SortDirInfoByName( mDirInfoList.Begin(), mPackInfo.nRootDirEnd );
		_SortFileInfoByName( mFileInfoList.Begin(), mPackInfo.nRootFileEnd );


		//�������Ŀ¼����Ҫ������Ŀ¼�ڵ��ļ�
		if( mDirInfoList.Size() > 0 && ( nSubLevel > 0 || nSubLevel == -1 ) )
		{
			FKPDirInfoList::Iterator it = mDirInfoList.Begin();
			FKPDirInfoList::Iterator end = mDirInfoList.End();
			for(; it!=end; ++it )
				_GetFileInfoList( it, nSubLevel );
		}


		//���ô���ļ�ͷ��Ϣ
		mPackInfo.nNumFiles			= mFileInfoList.Size();
		mPackInfo.nNumDirs			= mDirInfoList.Size();
		mPackInfo.nUncompLen		= 0;
		mPackInfo.nCompLen			= 0;

		mPackInfo.nDirInfoLen		= sizeof(FKPDirInfo) * mPackInfo.nNumDirs;
		mPackInfo.nFileInfoLen		= sizeof(FKPFileInfo) * mPackInfo.nNumFiles;


		//��������ļ�
		mPackFile.Open( szPackName, OT_Write );

		//д���ļ���ʶ
		mPackFile.Write( szFKPFileHeader, sizeof(szFKPFileHeader) );

		//Ϊ�����Ϣ���ݶ�Ԥ���ռ�
		UINT nPackHeaderChunkSize = sizeof(FKPPackInfo) + mPackInfo.nDirInfoLen + mPackInfo.nFileInfoLen;

		mPackFile.SetPosition( nPackHeaderChunkSize, BP_Curpos );
		mPackFile.SetEndOfFile();

		//�����б�ѹ���ļ�

		//ѹ����Ŀ¼���ļ�
		FKPFileInfoList::Iterator fit = mFileInfoList.Begin();
		FKPFileInfoList::Iterator fend = mFileInfoList.Begin() + mPackInfo.nRootFileEnd;
		for(; fit!=fend; ++fit )
			_CompressFile( fit );

		//ѹ����Ŀ¼��Ŀ¼�е��ļ�
		FKPDirInfoList::Iterator dit = mDirInfoList.Begin();
		FKPDirInfoList::Iterator dend = mDirInfoList.Begin() + mPackInfo.nRootDirEnd;
		for(; dit!=dend; ++dit )
			_CompressFilesInDir( dit );

		//д����ͳ����ɵ��ļ�ͷ���ݶ���Ϣ
		PRTDataChunk sHeaderData;
		sHeaderData.SetPassword( pFKPPassword );
		sHeaderData.Allocate( nPackHeaderChunkSize );

		sHeaderData.Code( &mPackInfo, sizeof(FKPPackInfo) );

		//д��Ŀ¼��Ϣ�б���ļ���Ϣ�б�
		sHeaderData.Code( mDirInfoList.Begin(), mPackInfo.nDirInfoLen );
		sHeaderData.Code( mFileInfoList.Begin(), mPackInfo.nFileInfoLen );

		mPackFile.SetPosition( sizeof(szFKPFileHeader) );
		sHeaderData.SetPosition( 0 );

		mPackFile.Write( sHeaderData.GetPointer(), nPackHeaderChunkSize );

		//�ر��ļ�
		mPackFile.Close();

		sHeaderData.Free();


		//�ָ�ԭ·��
		if( FALSE == SetCurrentDirectory( szPathBackup ) )
			Except( Exception::ERR_WINAPI_ERROR, (String)"����ָ����·�� '" + szPathBackup + "' ʧ�ܡ�" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�򿪴���ļ�
	void FKPFile::OpenPack( LPCSTR szPackName )
	{
		//���ȹر��ļ���
		ClosePack();

		//�򿪴���ļ�
		mPackFile.Open( szPackName, OT_Read );

		//��ȡ�ļ���ʶ
		char szHeaderString[ sizeof(szFKPFileHeader) ];
		mPackFile.Read( szHeaderString, sizeof(szFKPFileHeader) );

		//��֤�ļ���ȷ��
		if( 0 != memcmp( szHeaderString, szFKPFileHeader, sizeof(szFKPFileHeader) ) )
			Except( Exception::ERR_INTERNAL_ERROR, (String)"�ļ� '" + szPackName + "' ������ȷ�� FKP ����ļ���" );

		//��ȡ����ļ�ͷ���ݶ�
		PRTDataChunk sHeaderData;
		sHeaderData.SetPassword( pFKPPassword );

		sHeaderData.Allocate( sizeof(FKPPackInfo) );
		mPackFile.Read( sHeaderData.GetPointer(), sizeof(FKPPackInfo) );

		//��������ļ�ͷ��Ϣ
		sHeaderData.Decode( &mPackInfo, sizeof(FKPPackInfo) );

		//��������ļ���Ŀ¼��Ϣ�б��ͷ���ݶγ���
		UINT nPackHeaderChunkSize = sizeof(FKPPackInfo) + mPackInfo.nDirInfoLen + mPackInfo.nFileInfoLen;
		sHeaderData.Reallocate( nPackHeaderChunkSize );

		mPackFile.Read( sHeaderData.GetPointer(), mPackInfo.nDirInfoLen + mPackInfo.nFileInfoLen );

		FKPDirInfo* pDirInfo = mDirInfoList.Push( mPackInfo.nNumDirs );
		FKPFileInfo* pFileInfo = mFileInfoList.Push( mPackInfo.nNumFiles );

		sHeaderData.Decode( pDirInfo, mPackInfo.nDirInfoLen );
		sHeaderData.Decode( pFileInfo, mPackInfo.nFileInfoLen );

		sHeaderData.Free();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ڴ���ļ��������ļ�
	void FKPFile::AddToPack( StringArray* pFileNames, int nSubLevel )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Ӵ���ļ���ɾ���ļ�
	void FKPFile::DelFromPack( StringArray* pFileNames )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�����ļ��б�
	void FKPFile::GetFileListInPack( FileSelectList* pFileList )
	{
		//����·���µ��ļ������б�
		FKPFileInfoList::Iterator fit = mFileInfoList.Begin();
		FKPFileInfoList::Iterator fend = mFileInfoList.Begin() + mPackInfo.nRootFileEnd;
		for(; fit!=fend; ++fit )
			pFileList->AddFileToList( fit->szFileName );

		//����·���µ�Ŀ¼�����б�
		FKPDirInfoList::Iterator dit = mDirInfoList.Begin();
		FKPDirInfoList::Iterator dend = mDirInfoList.Begin() + mPackInfo.nRootDirEnd;
		for(; dit!=dend; ++dit )
		{
			FileSelectList* pSubFileList = pFileList->AddDirToList( dit->szDirName );

			//���ɸ���Ŀ¼���ļ��б�
			_MakeFileListOfDir( dit, pSubFileList );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�رմ���ļ�
	bool FKPFile::ClosePack()
	{
		//�رհ��д򿪵��ļ�
		if( !Close() )
			return false;

		if( !mPackFile.Close() )
			return false;

		memset( &mPackInfo, 0, sizeof(FKPPackInfo) );

		mDirInfoList.Clear();
		mFileInfoList.Clear();

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ļ�
	void FKPFile::Open( LPCSTR szFileName, OpenType eOpenType, bool bOverlapped )
	{
		UINT nBeginDir = 0;
		UINT nEndDir = mPackInfo.nRootDirEnd;
		UINT nBeginFile = 0;
		UINT nEndFile = mPackInfo.nRootFileEnd;

		//����·���е�Ŀ¼
		static char szPathNameBuf[ MAX_PATH ] = { NULL };

		int nStrLen = (int)strlen( szFileName );
		memcpy( szPathNameBuf, szFileName, nStrLen + 1 );

		char* pPathName = szPathNameBuf;

		//ѭ������ÿһ��Ŀ¼
		for(;;)
		{
			//Ѱ�ҵ�һ�� '\' �ַ�
			char* pChar = pPathName;
			for( int i=0; i<nStrLen; ++i )
			{
				if( *pChar == '\\' )
					goto FoundDir;

				++pChar;
			}

			//����Ҳ���Ŀ¼���˳�ѭ��
			break;

			//��ȥĿ¼����
FoundDir:
			*pChar = '\0';
			char* pDirName = pPathName;
			pPathName = ++pChar;

			//�����Ŀ¼����ϣֵ
			UINT nDirNameID = Misc::HashString( pDirName );

			//��Ŀ¼��Ϣ�б���Ѱ�Ҹü�Ŀ¼
			FKPDirInfo* pDirInfo = mDirInfoList.Begin() + nBeginDir;

			//ʹ���۰���ҷ������Ŀ¼��Ϣ��λ��
			int nFindBegin = 0;
			int nFindEnd = nEndDir - nBeginDir - 1;
			int nFindMiddle;
			FKPDirInfo* pFindDirInfo = NULL;
			
			while( nFindBegin <= nFindEnd )
			{
				nFindMiddle = ( nFindBegin + nFindEnd ) / 2;

				pFindDirInfo = pDirInfo + nFindMiddle;

				//����ҵ���ϣֵ��ͬ����
				if( pFindDirInfo->nNameID == nDirNameID )
				{
					//�ٴν����ַ����ȶ�
					if( 0 == strcmp( pFindDirInfo->szDirName, pDirName ) )
						goto FoundDirInfo;
				}

				if( nDirNameID >= pFindDirInfo->nNameID )
					nFindBegin = nFindMiddle + 1;
				else
					nFindEnd = nFindMiddle - 1;
			}

			Except( Exception::ERR_INVALIDPARAMS, (String)"�ڰ����Ҳ���ָ����Ŀ¼ '" + pDirName + "'��" );

			//�ҵ�ָ����Ŀ¼
FoundDirInfo:
			nBeginDir	= pFindDirInfo->nSubDirInfoBegin;
			nEndDir		= pFindDirInfo->nSubDirInfoEnd;
			nBeginFile	= pFindDirInfo->nFileInfoBegin;
			nEndFile	= pFindDirInfo->nFileInfoEnd;
		}
		

		//������ļ�����ϣֵ
		char* pFileName = pPathName;
		UINT nFileNameID = Misc::HashString( pFileName );

		//ʹ���۰���ҷ�������ļ���Ϣ��λ��
		FKPFileInfo* pFileInfo = mFileInfoList.Begin() + nBeginFile;

		int nFindBegin = 0;
		int nFindEnd = nEndFile - nBeginFile - 1;
		int nFindMiddle;
		FKPFileInfo* pFindFileInfo = NULL;

		while( nFindBegin <= nFindEnd )
		{
			nFindMiddle = ( nFindBegin + nFindEnd ) / 2;

			pFindFileInfo = pFileInfo + nFindMiddle;

			//����ҵ���ϣֵ��ͬ����
			if( pFindFileInfo->nNameID == nFileNameID )
			{
				//�ٴν����ַ����ȶ�
				if( 0 == strcmp( pFindFileInfo->szFileName, pFileName ) )
					goto FoundFileInfo;
			}

			if( nFileNameID >= pFindFileInfo->nNameID )
				nFindBegin = nFindMiddle + 1;
			else
				nFindEnd = nFindMiddle - 1;
		}

		Except( Exception::ERR_INVALIDPARAMS, (String)"�ڰ����Ҳ���ָ�����ļ� '" + pFileName + "'��" );

		//�ҵ�ָ���ļ�
FoundFileInfo:
		mpCurFileInfo = pFindFileInfo;
		mnRemainLen = pFindFileInfo->nUncompLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ر��ļ�
	bool FKPFile::Close()
	{
		mpCurFileInfo = NULL;
		mnCurPos = mnRemainLen = 0;

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ļ�����
	DWORD FKPFile::GetLength()
	{
		if( mpCurFileInfo == NULL )
			return 0;

		return mpCurFileInfo->nUncompLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ļ���дָ��λ��
	void FKPFile::SetPosition( long Offset, BasePos eBasePos )
	{
		long TmpRemainLen = (long)mnRemainLen;

		//����ʣ��ɶ�д����
		switch (eBasePos)
		{
		case BP_Begin:
			TmpRemainLen = (long)mpCurFileInfo->nUncompLen - Offset;
			break;
		case BP_End:
			TmpRemainLen = -Offset;
			break;
		case BP_Curpos:
			TmpRemainLen -= Offset;
			break;
		}

		//����Ƿ񳬳��ɶ�ȡ��Χ
		if( TmpRemainLen > (long)mpCurFileInfo->nUncompLen || TmpRemainLen < 0 )
			Except( Exception::ERR_INVALIDPARAMS, "���������ݿ��дָ���ƶ��� FKP �ļ���д��Χ֮�⡣" );

		mnRemainLen = TmpRemainLen;

		mnCurPos = mpCurFileInfo->nUncompLen - mnRemainLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ļ���дָ��λ��
	DWORD FKPFile::GetPosition()
	{
		return mpCurFileInfo->nUncompLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ļ�����
	void FKPFile::Read( void* pBuf, DWORD dwLen )
	{
		//���ʣ�೤�Ȳ������ֹ��ȡ
		if( dwLen > mnRemainLen )
			Except( Exception::ERR_INVALIDPARAMS, "�޷���ȡ�ļ���β֮������ݡ�" );

		//������ļ���дָ���Ƶ����ļ����ݴ洢��ʼλ��
		mPackFile.SetPosition( mpCurFileInfo->nOffset );

		UINT nBeginBlock = mnCurPos / FKP_BlockLen;		//��ǰ��Ҫ��ȡ����ʼ���ݿ�
		UINT nBeginOffset = mnCurPos % FKP_BlockLen;	//��ʼ���ݿ��еĶ�ȡ��ʼλ��

		UINT nEndBlock;
		UINT nEndOffset;
		
		//�����ȡ�ܳ������׸����ݿ��ȡ����
		if( dwLen > FKP_BlockLen - nBeginOffset )
		{
			//��ȥ��һ����ȡ���ݿ�Ķ�ȡ���Ⱥ��ʣ�೤��
			DWORD dwRemainLen = dwLen - ( FKP_BlockLen - nBeginOffset );

			nEndBlock = dwRemainLen / FKP_BlockLen + 1;	//��ǰ��Ҫ��ȡ�Ľ������ݿ�
			nEndOffset = dwRemainLen % FKP_BlockLen;	//�������ݿ��еĶ�ȡ����λ��
		}
		else
		{
			nEndBlock = nBeginBlock;
			nEndOffset = nBeginOffset + dwLen;
		}

		//���Ƚ���дָ���ƶ�����һ����ȡ���ݿ��λ��
		FKPBlockHeader sBlockHeader;
		UINT nBlock = 0;
		for(; nBlock<nBeginBlock; ++nBlock )
		{
			//��ȡ���ݿ�ͷ
			mPackFile.Read( &sBlockHeader, sizeof(FKPBlockHeader) );

			//�Թ������ݿ�
			mPackFile.SetPosition( sBlockHeader.nCompLen, BP_Curpos );
		}

		//ѭ����ȡ�������ݿ�
		for(; nBlock<nEndBlock+1; ++nBlock )
		{
			mPackFile.Read( &sBlockHeader, sizeof(FKPBlockHeader) );//��ȡ���ݿ�ͷ			
			mPackFile.Read( mpCompData, sBlockHeader.nCompLen );	//��ȡԭʼ����

			if( sBlockHeader.nUncompLen > FKP_BlockLen )
				Except( Exception::ERR_INTERNAL_ERROR, "ѹ�������ݿ鳤�ȴ���" );

			BYTE* pDecodeData;
			size_t nCopyLen = FKP_BlockLen;

			//�����ѹ�����ݶ�
			if( sBlockHeader.nCompLen != sBlockHeader.nUncompLen )
			{
				if( sBlockHeader.nUncompLen != (UINT)_Decompress( mpCompData, sBlockHeader.nCompLen, mpUncompData ) )
					Except( Exception::ERR_INTERNAL_ERROR, "��ѹ��������ݳ��ȴ���" );

				pDecodeData = mpUncompData;
			}
			//�����δѹ�����ݶ�
			else
			{
				pDecodeData = mpCompData;
			}

			//����ǽ������ݿ�
			if( nBlock == nEndBlock )
			{
				nCopyLen = nEndOffset;
			}

			//�������ʼ���ݿ�
			if( nBlock == nBeginBlock )
			{
				pDecodeData += nBeginOffset;
				nCopyLen -= nBeginOffset;
			}

			memcpy( pBuf, pDecodeData, nCopyLen );
			pBuf = (BYTE*)pBuf + nCopyLen;
		}

		mnCurPos += dwLen;
		mnRemainLen -= dwLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//д���ļ�����
	void FKPFile::Write( const void* pBuf, DWORD dwLen )
	{
		Except( Exception::ERR_INVALIDPARAMS, "�޷��� FKP ����ļ���д�����ݡ�" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�첽��ȡ�ļ�����
	bool FKPFile::AsynRead( void* pBuf, DWORD dwLen, LPOVERLAPPED pOverlapped )
	{
		Except( Exception::ERR_INVALIDPARAMS, "�޷��� FKP ����ļ����첽��ȡ���ݡ�" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�첽д���ļ�����
	bool FKPFile::AsynWrite( const void* pBuf, DWORD dwLen, LPOVERLAPPED pOverlapped )
	{
		Except( Exception::ERR_INVALIDPARAMS, "�޷��� FKP ����ļ����첽д�����ݡ�" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�첽��д���
	DWORD FKPFile::GetAsynResult( LPOVERLAPPED pOverlapped, bool bWait )
	{
		Except( Exception::ERR_CANNOT_WRITE_FILE, "�޷���ȡ FKP ����ļ����첽���ݶ�д�����" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ļ�������һ��Ψһ���� ID ���������ԣ��ظ����ʷǳ�΢С�������ұ�֤���Բ��ظ�����
	unsigned int FKPFile::FileNameToID( const char* szFileName )
	{
		return Misc::HashString( szFileName );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ɰ���һ��Ŀ¼�µ��ļ��б�
	void FKPFile::_MakeFileListOfDir( FKPDirInfo* pDirInfo, FileSelectList* pFileList )
	{
		//����·���µ��ļ������б�
		FKPFileInfoList::Iterator fit = mFileInfoList.Begin() + pDirInfo->nFileInfoBegin;
		FKPFileInfoList::Iterator fend = mFileInfoList.Begin() + pDirInfo->nFileInfoEnd;
		for(; fit!=fend; ++fit )
			pFileList->AddFileToList( fit->szFileName );

		//����·���µ�Ŀ¼�����б�
		FKPDirInfoList::Iterator dit = mDirInfoList.Begin() + pDirInfo->nSubDirInfoBegin;
		FKPDirInfoList::Iterator dend = mDirInfoList.Begin() + pDirInfo->nSubDirInfoEnd;
		for(; dit!=dend; ++dit )
		{
			FileSelectList* pSubFileList = pFileList->AddDirToList( dit->szDirName );

			//���ɸ���Ŀ¼���ļ��б�
			_MakeFileListOfDir( dit, pSubFileList );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡָ��·���µ��ļ���Ϣ�б�
	void FKPFile::_GetFileInfoList( FKPDirInfo* pDirInfo, int nSubLevel )
	{
		//���õ�ǰ·��
		if( FALSE == SetCurrentDirectory( pDirInfo->szDirName ) )
			Except( Exception::ERR_WINAPI_ERROR, (String)"����ָ����·�� '" + pDirInfo->szDirName + "' ʧ�ܡ�" );

		//���ҵ�һ���ļ�
		WIN32_FIND_DATA FileData;
		HANDLE hFind = FindFirstFile( "*.*", &FileData );
		if( hFind == INVALID_HANDLE_VALUE )
		{
			//�������ʧ��
			if( GetLastError() != ERROR_NO_MORE_FILES )
				Except( Exception::ERR_WINAPI_ERROR, (String)"��·�� '" + pDirInfo->szDirName + "' �²����ļ�ʧ�ܡ�" );
		}

		//��¼��Ŀ¼���ļ�����Ŀ¼���б��еĿ�ʼλ��
		UINT nFileListPos = mFileInfoList.Size();
		UINT nDirListPos = mDirInfoList.Size();
		pDirInfo->nFileInfoBegin = nFileListPos;
		pDirInfo->nSubDirInfoBegin = nDirListPos;

		//ѭ�����������ļ�
		for(;;)
		{
			//��ȡ�ļ�������
			size_t nNameLen = strlen( FileData.cFileName ) + 1;
			if( nNameLen > FKP_FileNameLen )
				Except( Exception::ERR_INVALIDPARAMS, (String)"Ŀ¼ '" + pDirInfo->szDirName +
				"' ���ƹ������޷������" );

			//�����Ŀ¼
			if( FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				if( 0 == strcmp( FileData.cFileName, "." ) || 0 == strcmp( FileData.cFileName, ".." ) )
					goto FindNext;

				//�������Ŀ¼�б�
				FKPDirInfo* pSubDirInfo = mDirInfoList.Push();

				memcpy( pSubDirInfo->szDirName, FileData.cFileName, nNameLen );
				pSubDirInfo->nNameID = Misc::HashString( pSubDirInfo->szDirName );

				++nDirListPos;
			}
			//�������ͨ�ļ�
			else if( FileData.dwFileAttributes )
			{
				//��������ļ��б�
				FKPFileInfo* pSubFileInfo = mFileInfoList.Push();

				memcpy( pSubFileInfo->szFileName, FileData.cFileName, nNameLen );
				pSubFileInfo->nNameID = Misc::HashString( pSubFileInfo->szFileName );

				++nFileListPos;
			}

FindNext:
			//Ѱ����һ���ļ�
			if( FALSE == FindNextFile( hFind, &FileData ) )
			{
				//����Ҳ����ļ�
				if( GetLastError() == ERROR_NO_MORE_FILES )
				{
					break;
				}
				//�������ʧ��
				else
				{
					Except( Exception::ERR_WINAPI_ERROR, (String)"��·�� '" + pDirInfo->szDirName + "' �²����ļ�ʧ�ܡ�" );
				}
			}
		}

		//�رղ���
		FindClose( hFind );

		//��¼��Ŀ¼���ļ�����Ŀ¼���б��еĽ�������β��λ��
		pDirInfo->nFileInfoEnd = nFileListPos;
		pDirInfo->nSubDirInfoEnd = nDirListPos;

		//�����Ŀ¼�µ��ļ���Ŀ¼��Ϣ�б�
		_SortDirInfoByName( mDirInfoList.Begin() + pDirInfo->nSubDirInfoBegin,
			pDirInfo->nSubDirInfoEnd - pDirInfo->nSubDirInfoBegin );
		_SortFileInfoByName( mFileInfoList.Begin() + pDirInfo->nFileInfoBegin,
			pDirInfo->nFileInfoEnd - pDirInfo->nFileInfoBegin );


		//���Ҫ�������ȡ��Ŀ¼�µ��ļ���Ϣ
		if( nSubLevel == -1 || ( --nSubLevel >= 0 ) )
		{
			//��ȡ��Ŀ¼�µ��ļ���Ϣ�б�
			FKPDirInfoList::Iterator it = mDirInfoList.Begin() + pDirInfo->nSubDirInfoBegin;
			FKPDirInfoList::Iterator end = mDirInfoList.Begin() + pDirInfo->nSubDirInfoEnd;
			for(; it!=end; ++it )
				_GetFileInfoList( it, nSubLevel );
		}

		//�����ϼ�·��
		if( FALSE == SetCurrentDirectory( ".." ) )
			Except( Exception::ERR_WINAPI_ERROR, "�����ϼ�·��ʧ�ܡ�" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������ƹ�ϣ������Ŀ¼��Ϣ
	void FKPFile::_SortDirInfoByName( FKPDirInfo* pDirInfo, UINT nNumInfos )
	{
		if( nNumInfos < 2 )
			return;

		FKPDirInfo TmpDirInfo;
		for( UINT i=0; i<nNumInfos-1; i++ )
		{
			for( unsigned j=i+1; j<nNumInfos; j++ )
			{
				if( pDirInfo[i].nNameID > pDirInfo[j].nNameID )
				{
					memcpy( &TmpDirInfo, pDirInfo + i, sizeof(FKPDirInfo) );
					memcpy( pDirInfo + i, pDirInfo + j, sizeof(FKPDirInfo) );
					memcpy( pDirInfo + j, &TmpDirInfo, sizeof(FKPDirInfo) );
				}
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������ƹ�ϣ�������ļ���Ϣ
	void FKPFile::_SortFileInfoByName( FKPFileInfo* pFileInfo, UINT nNumInfos )
	{
		if( nNumInfos < 2 )
			return;

		FKPFileInfo TmpFileInfo;
		for( UINT i=0; i<nNumInfos-1; i++ )
		{
			for( unsigned j=i+1; j<nNumInfos; j++ )
			{
				if( pFileInfo[i].nNameID > pFileInfo[j].nNameID )
				{
					memcpy( &TmpFileInfo, pFileInfo + i, sizeof(FKPFileInfo) );
					memcpy( pFileInfo + i, pFileInfo + j, sizeof(FKPFileInfo) );
					memcpy( pFileInfo + j, &TmpFileInfo, sizeof(FKPFileInfo) );
				}
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����б���Ϣѹ���ļ�
	void FKPFile::_CompressFilesInDir( FKPDirInfo* pDirInfo )
	{
		//���õ�ǰ·��
		if( FALSE == SetCurrentDirectory( pDirInfo->szDirName ) )
			Except( Exception::ERR_WINAPI_ERROR, (String)"����ָ����·�� '" + pDirInfo->szDirName + "' ʧ�ܡ�" );

		//ѭ��ѹ����Ŀ¼�������ļ�
		FKPFileInfoList::Iterator fit = mFileInfoList.Begin() + pDirInfo->nFileInfoBegin;
		FKPFileInfoList::Iterator fend = mFileInfoList.Begin() + pDirInfo->nFileInfoEnd;
		for(; fit!=fend; ++fit )
			_CompressFile( fit );

		//ѭ��ѹ����Ŀ¼��������Ŀ¼
		FKPDirInfoList::Iterator dit = mDirInfoList.Begin() + pDirInfo->nSubDirInfoBegin;
		FKPDirInfoList::Iterator dend = mDirInfoList.Begin() + pDirInfo->nSubDirInfoEnd;
		for(; dit!=dend; ++dit )
			_CompressFilesInDir( dit );

		//�����ϼ�·��
		if( FALSE == SetCurrentDirectory( ".." ) )
			Except( Exception::ERR_WINAPI_ERROR, "�����ϼ�·��ʧ�ܡ�" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ѹ��ָ���ļ�
	void FKPFile::_CompressFile( FKPFileInfo* pFileInfo )
	{
		//��Ҫ���д�����ļ�
		BaseFile SrcFile;
		SrcFile.Open( pFileInfo->szFileName );

		//��ȡ��ǰ��дλ��
		pFileInfo->nOffset = mPackFile.GetPosition();

		//��ȡ�ļ�Ҫ���д�����ļ�����
		pFileInfo->nUncompLen = SrcFile.GetLength();
		pFileInfo->nCompLen = 0;

		//�����ļ�ѹ���ֿ��������һ�鳤��
		UINT nNumFullBlock = (UINT)( pFileInfo->nUncompLen / FKP_BlockLen );
		UINT nRemLen = pFileInfo->nUncompLen % FKP_BlockLen;

		pFileInfo->nNumBlocks = ( nRemLen > 0 ) ? ( nNumFullBlock + 1 ) : nNumFullBlock;

		FKPBlockHeader sBlockHeader;
		void* pBlockData;

		//�ֿ�ѹ���ļ�
		for( UINT i=0; i<nNumFullBlock; ++i )
		{
			//��ȡδѹ������
			SrcFile.Read( mpUncompData, FKP_BlockLen );

			//ѹ������
			sBlockHeader.nUncompLen = FKP_BlockLen;
			sBlockHeader.nCompLen = (UINT)_Compress( mpUncompData, FKP_BlockLen, mpCompData );

			//���ѹ��������ݱ�Դ���ݳ��Ȼ�����д��δѹ������
			if( sBlockHeader.nCompLen > FKP_BlockLen )
			{
				sBlockHeader.nCompLen = FKP_BlockLen;
				pBlockData = mpUncompData;
			}
			//����д��ѹ���������
			else
			{
				pBlockData = mpCompData;
			}

			pFileInfo->nCompLen += sBlockHeader.nCompLen;

			//д�����ݶ�ͷ
			mPackFile.Write( &sBlockHeader, sizeof(FKPBlockHeader) );

			//д�������
			mPackFile.Write( pBlockData, sBlockHeader.nCompLen );
		}

		//д��ʣ�೤�ȿ�
		if( nRemLen > 0 )
		{
			//��ȡδѹ������
			SrcFile.Read( mpUncompData, nRemLen );

			//ѹ������
			sBlockHeader.nUncompLen = nRemLen;
			sBlockHeader.nCompLen = (UINT)_Compress( mpUncompData, nRemLen, mpCompData );

			//���ѹ��������ݱ�Դ���ݳ��Ȼ�����д��δѹ������
			if( sBlockHeader.nCompLen > nRemLen )
			{
				sBlockHeader.nCompLen = nRemLen;
				pBlockData = mpUncompData;
			}
			//����д��ѹ���������
			else
			{
				pBlockData = mpCompData;
			}

			pFileInfo->nCompLen += sBlockHeader.nCompLen;

			//д�����ݶ�ͷ
			mPackFile.Write( &sBlockHeader, sizeof(FKPBlockHeader) );

			//д�������
			mPackFile.Write( pBlockData, sBlockHeader.nCompLen );
		}

		//�ر�Ҫ���д�����ļ�
		SrcFile.Close();

		//�ۼƴ���ļ�ѹ����δѹ�����ݳ���
		mPackInfo.nUncompLen += pFileInfo->nUncompLen;
		mPackInfo.nCompLen += pFileInfo->nCompLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ر�ת��ָ���ַ����ֵ�ľ���
	#pragma warning( disable: 4311 )
	//--------------------------------------------------------------------------------------------------------------
	//����ѹ���������
	unsigned int FKPFile::_DoCompress( unsigned char* in, unsigned in_len, unsigned char* out, unsigned* out_len )
	{
		static long wrkmem [16384L] ;
		register unsigned char* ip;
		unsigned char* op;
		unsigned char* in_end = in + in_len;
		unsigned char* ip_end = in + in_len - 13;
		unsigned char* ii;
		unsigned char** dict = (unsigned char**)wrkmem;

		op = out;
		ip = in;
		ii = ip;

		ip += 4;

		for(;;) 
		{
			register unsigned char* m_pos;
			unsigned m_off;
			unsigned m_len;
			unsigned dindex;

			dindex = ((0x21 * (((((((unsigned)(ip[3]) << 6) ^ ip[2]) << 5) ^ ip[1]) << 5) ^ ip[0])) >> 5) & 0x3fff;
			m_pos = dict[dindex];

			if( ((unsigned)m_pos < (unsigned)in) || (m_off = (unsigned)((unsigned)ip-(unsigned)m_pos) ) <= 0 || m_off > 0xbfff )
			{
				goto literal;
			}

			if( m_off <= 0x0800  || m_pos[3] == ip[3])
				goto try_match;
			dindex  = (dindex  & 0x7ff) ^ 0x201f ;

			m_pos = dict[dindex];
			if( (unsigned)(m_pos)  < (unsigned)(in) || (m_off = (unsigned)( (int)((unsigned)ip-(unsigned)m_pos))) <= 0 || m_off>0xbfff )
			{
				goto literal;
			}
			if( m_off <= 0x0800  || m_pos[3] == ip[3])
				goto try_match;
			goto literal;

	try_match:
			if( *( unsigned short*)m_pos == *( unsigned short*)ip && m_pos[2] == ip[2]) 
				goto match;

	literal:
			dict[dindex] = ip;
			++ip;
			if( ip >= ip_end)
				break;
			continue;

	match:
			dict[dindex] =  ip;
			if( ip - ii > 0)
			{
				register unsigned t = (unsigned)ip - (unsigned)ii;

				if( t <= 3) 
					op[-2] |= (unsigned char)t;
				else if( t <= 18)
					*op++ = (unsigned char) (t - 3);
				else 
				{
					register unsigned tt = t - 18;
					*op++ = 0;
					while( tt > 255)
					{
						tt -= 255;
						*op++ = 0;
					}
					*op ++ = (unsigned char)tt;
				}
				do
				{
					*op ++ = *ii ++;
				}while( --t>0 );
			}

			ip += 3;

			if( m_pos[3] != *ip++ || m_pos[4] != *ip++ || m_pos[5] != *ip++ ||
				m_pos[6] != *ip++ || m_pos[7] != *ip++ || m_pos[8] != *ip++ )
			{
				--ip;
				m_len = (unsigned)ip - (unsigned)ii;

				if( m_off <= 0x0800)
				{
					-- m_off;
					*op ++ = (unsigned char)( ((m_len - 1) << 5) | ((m_off & 7) << 2) );
					*op ++ = (unsigned char)( m_off >> 3 );
				}
				else if( m_off <= 0x4000)
				{
					-- m_off;
					*op ++ = (unsigned char) (32  | (m_len - 2));
					goto m3_m4_offset;
				}
				else 
				{
					m_off -= 0x4000;
					*op ++ = (unsigned char) (16 | ((m_off & 0x4000) >> 11) | (m_len - 2) );
					goto m3_m4_offset;
				}
			}
			else
			{
				{
					unsigned char *end = in_end;
					unsigned char *m = m_pos + 9;
					while( ip < end && *m == *ip)
						m++, ip++;
					m_len = ( (unsigned)ip - (unsigned)ii );
				}

				if( m_off <= 0x4000) 
				{
					-- m_off;
					if( m_len <= 33)
						*op ++ = (unsigned char) (32  | (m_len - 2));
					else
					{
						m_len -= 33;
						*op ++=32;
						goto m3_m4_len;
					}
				}
				else
				{
					m_off -= 0x4000;
					if( m_len <= 9)
						*op++ = (unsigned char)(16|((m_off & 0x4000) >> 11) | (m_len - 2));
					else 
					{
						m_len -= 9;
						*op++ = (unsigned char) ( 16  | ((m_off & 0x4000) >> 11) );
	m3_m4_len:
						while( m_len > 255)
						{
							m_len -= 255;
							*op ++ = 0;
						}
						*op++ = (unsigned char)m_len;
					}
				}

	m3_m4_offset:
				*op ++ = (unsigned char) ((m_off & 63) << 2);
				*op ++ = (unsigned char) (m_off >> 6);
			}

			ii = ip;
			if( ip >= ip_end)
				break;
		}

		*out_len = (unsigned)op - (unsigned)out;
		return (unsigned)( in_end - ii );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ѹ������
	int FKPFile::_Decompress( void* in, unsigned in_len, void* out )
	{
		register unsigned char* op;
		register unsigned char* ip;
		register unsigned t;
		register unsigned char* m_pos;

		unsigned char* IpEnd = (unsigned char *)in + in_len;

		op = (unsigned char*)out;
		ip = (unsigned char*)in;

		if(*ip > 17)
		{
			t = *ip++ - 17;
			if(t < 4) goto match_next;
			do
			{
				*op++ = *ip++;
			}while (-- t > 0);
			goto first_literal_run;
		}

		while(1)
		{
			t = *ip++;
			if(t >= 16) goto match;
			if(t == 0)
			{
				while(*ip == 0)
				{
					t += 255;
					ip++;
				}
				t += 15 + *ip ++;
			}
			*(unsigned *)op = *(unsigned *)ip;
			op += 4;
			ip += 4;
			if(--t > 0)
			{
				if(t >= 4)
				{
					do
					{
						*(unsigned *) op = *(unsigned *) ip;
						op += 4;
						ip += 4;
						t -= 4;
					} while(t >= 4);
				if(t > 0) 
					do *op++ = *ip++; 
					while (--t > 0);
				}
				else
				{
					do
					{
						*op++ = *ip++;
					}while(-- t > 0);
				}
			}
	first_literal_run:
			t = *ip ++;
			if(t >= 16) goto match;

			m_pos = op - 0x0801;
			m_pos -= t >> 2;
			m_pos -= *ip ++ << 2;

			*op ++ = *m_pos ++;
			*op ++ = *m_pos ++;
			*op ++ = *m_pos;

			goto match_done;

			while(1)
			{
	match:
				if(t >= 64)
				{
					m_pos = op - 1;
					m_pos -= (t >> 2) & 7;
					m_pos -= *ip++ << 3;
					t = (t >> 5) - 1;

					goto copy_match;
				}
				else if(t >= 32)
				{
					t &= 31;
					if(t == 0)
					{
						while (*ip == 0)
						{
							t += 255;
							ip++;
						}
					t += 31 + *ip ++;
					}
					m_pos = op - 1;
					m_pos -= (*(unsigned short *)ip) >> 2;
					ip += 2;
				}
				else if(t >= 16)
				{
					m_pos = op;
					m_pos -= (t & 8) << 11;
					t &= 7;
					if(t == 0)
					{
						while (*ip == 0)
						{
							t += 255;
							ip++;
						}
						t += 7 + *ip ++;
					}
					m_pos -= (*(unsigned short *)ip) >> 2;
					ip += 2;
					if(m_pos == op) goto eof_found;
					m_pos -= 0x4000;
				}
				else
				{
					m_pos = op - 1;
					m_pos -= t >> 2;
					m_pos -= *ip ++ << 2;
					*op ++ = *m_pos ++;
					*op ++ = *m_pos;
					goto match_done;
				}

				if(t >= 6 && (op - m_pos) >= 4)
				{
					*(unsigned *)op = *(unsigned *)m_pos;
					op += 4;
					m_pos += 4;
					t -= 2;
					do
					{
						*(unsigned *)op = *(unsigned *)m_pos;
						op += 4;
						m_pos += 4;
						t -= 4;
					} while(t >= 4);
					if(t > 0)
					{
						do
						{
							*op ++ = *m_pos ++;
						}
						while (--t > 0);
					}
				}
				else
				{
	copy_match:
				*op ++ = *m_pos ++;
				*op ++ = *m_pos ++;
				do *op ++ = *m_pos ++; while(--t > 0);
				}
	match_done:
				t = ip[-2] & 3;
				if(t == 0) break;
	match_next:
				do
				{
					*op ++ = *ip ++;
				}while (--t > 0);
				t = *ip ++;
			}
		}
	eof_found:
		if(ip != IpEnd)
			return -1;
		return int(op - (unsigned char*)out);
	}
	//--------------------------------------------------------------------------------------------------------------
	//ѹ������
	int FKPFile::_Compress( void* in, unsigned in_len, void* out )
	{
		unsigned char* op = (unsigned char*)out;
		unsigned t, out_len;

		if(in_len <= 13)
			t = in_len;
		else
		{
			t = _DoCompress( (unsigned char*)in, in_len, op, &out_len );
			op += out_len;
		}

		if(t > 0)
		{
			unsigned char *ii = (unsigned char*)in + in_len - t;
			if( op == (unsigned char*)out && t <= 238 )
				*op ++ = (unsigned char) ( 17 + t );
			else if( t <= 3 )
				op[-2] |= (unsigned char)t ;
			else if( t <= 18 )
				*op ++ = (unsigned char)(t - 3);
			else
			{
				unsigned tt = t - 18;

				*op ++ = 0;
				while( tt > 255 )
				{
					tt -= 255;
					*op++ = 0;
				}
				*op ++ = (unsigned char)tt;
			}
			do
			{
				*op++ = *ii++;
			}while( --t > 0 );
		}

		*op++ = 17;
		*op++ = 0;
		*op++ = 0;

		return ( (unsigned)op - (unsigned)( (unsigned char*)out ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ָ�ת��ָ���ַ����ֵ�ľ���
	#pragma warning( default: 4311 )
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
