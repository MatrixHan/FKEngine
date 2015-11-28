/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BaseFile
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�����ļ���
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//�����ļ���
	class FK_DLL BaseFile : public FileObject
	{
	public:
		//��д�����С 64 KB
		static const DWORD	mCacheLen =	0x10000;

	protected:
		//�����������
		enum BuffedOpType
		{
			BOT_None,		//δ���л������
			BOT_Read,		//��ȡ����
			BOT_Write,		//д������
		};

	protected:
		HANDLE			mFileHandle;			//�ļ����

		BYTE			mpCache[ mCacheLen ];	//��д����
		BYTE*			mpCachePtr;				//��д����ָ��
		DWORD			mdwCachedLen;			//�ѻ������ݳ���

		BuffedOpType	mLastBuffedOp;			//�����еĻ����������

		DWORD			mPosition;				//��дָ��λ��

	public:
		BaseFile();
		BaseFile( LPCSTR szFileName, OpenType eOpenType = OT_Read, bool bOverlapped = false );
		~BaseFile();

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

		//���õ�ǰ��дλ��Ϊ�ļ���β
		void SetEndOfFile();

		//����������д���ļ�
		void Flush();

	protected:
		//ͬ����д����
		void _SyncOperation();

		//�ڲ���ȡ�ļ�����
		DWORD _InternalRead( BYTE* pBuf, DWORD dwLen );

		//�ڲ�д���ļ�����
		DWORD _InternalWrite( const BYTE* pBuf, DWORD dwLen );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
