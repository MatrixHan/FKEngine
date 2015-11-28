/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	TextFile
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
	TextFile::TextFile()
		: mFileHandle	(NULL)
		, mFileLen		(0)
		, mCurPos		(0)
		, mbIsChanged	(false)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	TextFile::TextFile( LPCSTR szFileName, OpenType eOpenType, bool bOverlapped )
		: mFileHandle	(NULL)
		, mFileLen		(0)
		, mCurPos		(0)
		, mbIsChanged	(false)
	{
		Open( szFileName, eOpenType, bOverlapped );
	}
	//--------------------------------------------------------------------------------------------------------------
	TextFile::~TextFile()
	{
		Close();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ļ�
	void TextFile::Open( LPCSTR szFileName, OpenType eOpenType, bool bOverlapped )
	{
		//���ļ�
		DWORD dwOrigFileLen;
		_InternalOpen( szFileName, eOpenType, bOverlapped, &mFileHandle );
		dwOrigFileLen = GetLength();

		//���Դ�ļ���������
		if( dwOrigFileLen > 0 )
		{
			//�������ݷ��뻺��
			mTranslateBuf.Initialize( dwOrigFileLen, 1024 );
			char* pTransBuf = mTranslateBuf.Push( dwOrigFileLen );

			//�������ļ����ݶ��뻺��
			DWORD dwReadLen;
			BOOL bResult = ReadFile( mFileHandle, pTransBuf, dwOrigFileLen, &dwReadLen, NULL );
			if( bResult == FALSE || dwReadLen != dwOrigFileLen )
				Except( Exception::ERR_CANNOT_READ_FILE, "���ı��ļ�ʱ��ȡ�ļ�����ʧ�ܡ�" );

			//���������ļ�����
			mFileLen = dwOrigFileLen;

			char* pChar = pTransBuf;
			for( DWORD i=0; i<dwOrigFileLen; ++i, ++pChar )
			{
				if( pChar[0] == '\r' && pChar[1] == '\n' )
				{
					mTranslateBuf.Erase( i );
					++i;
					++pChar;
					--mFileLen;
				}
			}
		}
		else
		{
			mTranslateBuf.Initialize( 1024, 1024 );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ر��ļ�
	bool TextFile::Close()
	{
		if( mFileHandle != NULL )
		{
			//������Ĺ��ı�����
			if( mbIsChanged )
			{
				//�����ı�����
				char* pTransBuf = mTranslateBuf.Begin();
				char* pChar = pTransBuf;

				for( DWORD i=0; i<mFileLen; ++i, ++pChar )
				{
					if( *pChar == '\n' )
					{
						pChar = mTranslateBuf.Insert( i );
						*pChar = '\r';
						++pChar;
						++i;
						++mFileLen;
					}
				}

				//���ļ���дָ���Ƶ��ļ�ͷ��
				if( SetFilePointer( mFileHandle, 0, NULL, FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
				{
					SetLastException( Exception::ERR_WINAPI_ERROR, "�ƶ��ļ���дָ��ʧ�ܡ�" );
					return false;
				}

				//д���ļ�����
				DWORD dwUntransLen = mTranslateBuf.Size();
				void* pUntransData = (void*)mTranslateBuf.Begin();

				DWORD dwWroteLen;
				BOOL bResult = WriteFile( mFileHandle, pUntransData, dwUntransLen, &dwWroteLen, NULL );
				if( bResult == FALSE || dwWroteLen != dwUntransLen )
				{
					SetLastException( Exception::ERR_CANNOT_READ_FILE, "д����ĺ���ı��ļ�����ʧ�ܡ�" );
					return false;
				}
			}

			//�ر��ļ�
			if( CloseHandle( mFileHandle ) == FALSE )
			{
				SetLastException( Exception::ERR_INTERNAL_ERROR, "�ر��ļ�ʧ�ܡ�" );
				return false;
			}

			mFileHandle = NULL;
		}

		mFileLen = 0;
		mCurPos = 0;
		mbIsChanged = false;

		//�ͷ����ݷ��뻺��
		mTranslateBuf.Release();

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ļ�����
	DWORD TextFile::GetLength()
	{
		return mFileLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ļ���дָ��λ��
	void TextFile::SetPosition( long Offset, BasePos eBasePos )
	{
		switch (eBasePos)
		{
		case BP_Begin:
			mCurPos = Offset;
			break;
		case BP_End:
			mCurPos = mFileLen + Offset;
			break;
		case BP_Curpos:
			mCurPos += Offset;
			break;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "������ļ���дָ���ƶ���׼���͡�" );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ļ���дָ��λ��
	DWORD TextFile::GetPosition()
	{
		return mCurPos;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ļ�����
	void TextFile::Read( void* pBuf, DWORD dwLen )
	{
		char* pTransData = mTranslateBuf.Begin();

		memcpy( pBuf, pTransData + mCurPos, dwLen );

		mCurPos += dwLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//д���ļ�����
	void TextFile::Write( const void* pBuf, DWORD dwLen )
	{
		//��������ı�����β��д���������ļ�����
		DWORD dwDataRear = mCurPos + dwLen;
		if( dwDataRear > mFileLen )
		{
			DWORD dwAppendLen = dwDataRear - mFileLen;
			mTranslateBuf.Push( dwAppendLen );

			mFileLen = dwDataRear;
		}

		char* pTransData = mTranslateBuf.Begin();

		memcpy( pTransData + mCurPos, pBuf, dwLen );

		mCurPos += dwLen;
		mbIsChanged = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�첽��ȡ�ļ�����
	bool TextFile::AsynRead( void* pBuf, DWORD dwLen, LPOVERLAPPED pOverlapped )
	{
		Except( Exception::ERR_CANNOT_READ_FILE, "�޷����ı��ļ���������ļ��Ͻ����첽���ݶ�ȡ��" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�첽д���ļ�����
	bool TextFile::AsynWrite( const void* pBuf, DWORD dwLen, LPOVERLAPPED pOverlapped )
	{
		Except( Exception::ERR_CANNOT_WRITE_FILE, "�޷����ı��ļ���������ļ��Ͻ����첽����д�롣" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�첽��д���
	DWORD TextFile::GetAsynResult( LPOVERLAPPED pOverlapped, bool bWait )
	{
		Except( Exception::ERR_CANNOT_WRITE_FILE, "�޷���ȡ�ı��ļ�����첽���ݶ�д�����" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//д���ʽ���ļ�����
	void TextFile::WriteFormat( const char* szFormat, ... )
	{
		//��ȡ�����б�
		va_list args;
		va_start( args, szFormat );

		//��ȡ��ʽ����Ϣ������ַ������ȣ�����Ҫһ�� NULL ��β�ַ��ռ䣩
		DWORD dwLen = (DWORD)_vscprintf( szFormat, args ) + 1;

		//�����ַ����ڴ�
		char* pBuf = (char*)malloc( dwLen );
		if( pBuf == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "д���ʽ���ļ�����ʱ�������ʽ�����ݵ��ڴ�ʧ�ܡ�" );

		//��ʽ������
		vsprintf( pBuf, szFormat, args );

		//д������
		Write( pBuf, dwLen - 1 );
		SafeFree( pBuf );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
