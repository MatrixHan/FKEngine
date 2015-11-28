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
*	�ļ�˵����	FKP ����ļ�������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	//FKP �ļ�ͷ��ʶ
	const char szFKPFileHeader[] = "FK Pack File";

	const BYTE pFKPPassword[16] = {	0x29, 0x73, 0x0b, 0x27, 0xa0, 0x8d, 0x18, 0x02,
									0x5a, 0x58, 0xba, 0x3c, 0x67, 0x60, 0x25, 0x32 };

	const int		FKP_FileNameLen		= 32;			//�ļ�����󳤶�
	const UINT		FKP_BlockLen		= 0x20000;		//�γ���
	const UINT		FKP_ProcBufLen		= 0x30000;		//���ݴ������С

	//--------------------------------------------------------------------------------------------------------------
	//FKP ����ļ�������
	class FK_DLL FKPFile : public PackObject
	{
	protected:
		//����ļ�ͷ��Ϣ
		struct FKPPackInfo
		{
			UINT	nNumFiles;					//�����ļ�����
			UINT	nNumDirs;					//����Ŀ¼����
			DWORD	nUncompLen;					//�����ļ�δѹ����С
			DWORD	nCompLen;					//�����ļ�ѹ����С

			DWORD	nDirInfoLen;				//Ŀ¼��Ϣ�γ���
			DWORD	nFileInfoLen;				//�ļ���Ϣ�γ���

			UINT	nRootDirEnd;				//��Ŀ¼��Ŀ¼�������
			UINT	nRootFileEnd;				//��Ŀ¼���ļ��������
		};

		//�������Ŀ¼��Ϣ
		struct FKPDirInfo
		{
			char	szDirName[FKP_FileNameLen];	//Ŀ¼����
			UINT	nNameID;					//Ŀ¼����ϣ��
			UINT	nSubDirInfoBegin;			//��Ŀ¼����Ŀ¼��ʼ���
			UINT	nSubDirInfoEnd;				//��Ŀ¼����Ŀ¼�������
			UINT	nFileInfoBegin;				//��Ŀ¼���ļ���ʼ���
			UINT	nFileInfoEnd;				//��Ŀ¼���ļ��������
		};
		typedef Stack< FKPDirInfo >		FKPDirInfoList;

		//��������ļ���Ϣ
		struct FKPFileInfo
		{
			char	szFileName[FKP_FileNameLen];//�ļ�����
			UINT	nNameID;					//�ļ�����ϣ��
			UINT	nOffset;					//���ļ���ʼ���ݶ��ڴ���ļ��ڵ�λ��
			UINT	nNumBlocks;					//���ļ������ݶ�����
			DWORD	nUncompLen;					//�ļ�δѹ����С
			DWORD	nCompLen;					//�ļ�ѹ�����С
		};
		typedef Stack< FKPFileInfo >	FKPFileInfoList;

		//���ݶ�ͷ��Ϣ
		struct FKPBlockHeader
		{
			UINT nCompLen;		//��ѹ�����ݳ���
			UINT nUncompLen;	//�ν�ѹ�����ݳ���
		};

	protected:
		BYTE			mpUncompData[FKP_BlockLen];		//δѹ�����ݻ�����ָ��
		BYTE			mpCompData[FKP_ProcBufLen];		//��ѹ�����ݻ�����ָ��

		FKPPackInfo		mPackInfo;		//����ļ�ͷ��Ϣ
		FKPDirInfoList	mDirInfoList;	//���Ŀ¼��Ϣ�б�
		FKPFileInfoList	mFileInfoList;	//����ļ���Ϣ�б�

		FKPFileInfo*	mpCurFileInfo;	//��ǰ���ļ����ļ���Ϣ
		DWORD			mnRemainLen;	//��ǰ�ļ�δ��ȡ����
		DWORD			mnCurPos;		//��ǰ�ļ���дλ��

	public:
		FKPFile();
		virtual ~FKPFile();

		//--------------------------------
		// ����Ϊ PackObject ��ļ̳к���
		//--------------------------------

		//��������ļ�
		void CreatePack( LPCSTR szPackName, LPCSTR szBasePath, StringArray* pFileNames, int nSubLevel );

		//�򿪴���ļ�
		void OpenPack( LPCSTR szPackName );

		//�ڴ���ļ��������ļ�
		void AddToPack( StringArray* pFileNames, int nSubLevel );

		//�Ӵ���ļ���ɾ���ļ�
		void DelFromPack( StringArray* pFileNames );

		//��ȡ�����ļ��б�
		void GetFileListInPack( FileSelectList* pFileList );

		//�رմ���ļ�
		bool ClosePack();

		//--------------------------------
		// ����Ϊ FileObject ��ļ̳к���
		//--------------------------------

		//���ļ�
		void Open( LPCSTR szFileName, OpenType eOpenType = OT_Read, bool bOverlapped = false );

		//�ر��ļ�
		bool Close();

		//��ȡ�ļ�����
		DWORD GetLength();

		//�����ļ���дָ��λ��
		void SetPosition( long Offset, BasePos eBasePos = BP_Begin );

		//��ȡ�ļ���дָ��λ��
		DWORD GetPosition();

		//��ȡ�ļ�����
		void Read( void* pBuf, DWORD dwLen );

		//д���ļ�����
		void Write( const void* pBuf, DWORD dwLen );

		//�첽��ȡ�ļ�����
		bool AsynRead( void* pBuf, DWORD dwLen, LPOVERLAPPED pOverlapped );

		//�첽д���ļ�����
		bool AsynWrite( const void* pBuf, DWORD dwLen, LPOVERLAPPED pOverlapped );

		//��ȡ�첽��д���
		DWORD GetAsynResult( LPOVERLAPPED pOverlapped, bool bWait = true );

		//�����ļ�������һ��Ψһ���� ID ���������ԣ��ظ����ʷǳ�΢С�������ұ�֤���Բ��ظ�����
		unsigned int FileNameToID( const char* szFileName );

	protected:
		//���ɰ���һ��Ŀ¼�µ��ļ��б�
		void _MakeFileListOfDir( FKPDirInfo* pDirInfo, FileSelectList* pFileList );

		//��ȡָ��·���µ��ļ���Ϣ�б�
		void _GetFileInfoList( FKPDirInfo* pDirInfo, int nSubLevel );

		//�������ƹ�ϣ������Ŀ¼��Ϣ
		void _SortDirInfoByName( FKPDirInfo* pDirInfo, UINT nNumInfos );

		//�������ƹ�ϣ�������ļ���Ϣ
		void _SortFileInfoByName( FKPFileInfo* pFileInfo, UINT nNumInfos );

		//�����б���Ϣѹ���ļ�
		void _CompressFilesInDir( FKPDirInfo* pDirInfo );

		//ѹ��ָ���ļ�
		void _CompressFile( FKPFileInfo* pFileInfo );
		
		//����ѹ���������
		unsigned int _DoCompress( unsigned char* in, unsigned in_len, unsigned char* out, unsigned* out_len );

		//��ѹ������
		int _Decompress( void* in, unsigned in_len, void* out );

		//ѹ������
		int _Compress( void* in, unsigned in_len, void* out );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
