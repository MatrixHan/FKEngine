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
	const char STR_ERR_READ_LEN[]	= "�޷���ȡָ�����ȵ����ݣ����������ڶ�ȡλ�ó������ļ�β����";
	const char STR_ERR_WRITE_LEN[]	= "�޷�д��ָ�����ȵ����ݣ�������������û��ָ�����������ļ���ģʽ�������"
		"д��λ�ó������ļ�β����";
	//--------------------------------------------------------------------------------------------------------------
	BaseFile::BaseFile()
		: mFileHandle	(NULL)
		, mpCachePtr	(NULL)
		, mdwCachedLen	(0)
		, mLastBuffedOp	(BOT_None)
		, mPosition		(0)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	BaseFile::BaseFile( LPCSTR szFileName, OpenType eOpenType, bool bOverlapped )
		: mFileHandle	(NULL)
	{
		Open( szFileName, eOpenType, bOverlapped );
	}
	//--------------------------------------------------------------------------------------------------------------
	BaseFile::~BaseFile()
	{
		Close();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ļ�
	void BaseFile::Open( LPCSTR szFileName, OpenType eOpenType, bool bOverlapped )
	{
		//���ļ�
		_InternalOpen( szFileName, eOpenType, bOverlapped, &mFileHandle );

		mpCachePtr		= mpCache;
		mdwCachedLen	= 0;
		mLastBuffedOp	= BOT_None;
		mPosition		= 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ر��ļ�
	bool BaseFile::Close()
	{
		if( mFileHandle != NULL )
		{
			//ͬ����д����
			_SyncOperation();

			//�ر��ļ�
			if( FALSE == CloseHandle( mFileHandle ) )
			{
				SetLastException( Exception::ERR_WINAPI_ERROR, "�ر��ļ�ʧ�ܡ�" );
				return false;
			}

			mFileHandle = NULL;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ļ�����
	DWORD BaseFile::GetLength()
	{
		DWORD dwLength = GetFileSize( mFileHandle, NULL );
		if( dwLength == INVALID_FILE_SIZE )
			Except( Exception::ERR_WINAPI_ERROR, "��ȡ�ļ�����ʧ�ܡ�" );

		return dwLength;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ļ���дָ��λ��
	void BaseFile::SetPosition( long Offset, BasePos eBasePos )
	{
		//ͬ����д����
		_SyncOperation();

		switch (eBasePos)
		{
		case BP_Begin:
			mPosition = (DWORD)Offset;
			break;
		case BP_End:
			mPosition = (DWORD)( (long)GetLength() + Offset );
			break;
		case BP_Curpos:
			mPosition = (DWORD)( (long)mPosition + Offset );
			break;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "������ļ���дָ���ƶ���׼���͡�" );
		}

		if( SetFilePointer( mFileHandle, mPosition, NULL, FILE_BEGIN ) == INVALID_SET_FILE_POINTER )
			Except( Exception::ERR_WINAPI_ERROR, "�ƶ��ļ���дָ��ʧ�ܡ�" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ļ���дָ��λ��
	DWORD BaseFile::GetPosition()
	{
		return mPosition;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ļ�����
	void BaseFile::Read( void* pBuf, DWORD dwLen )
	{
		//��������еĻ���������Ƕ�ȡ����
		if( mLastBuffedOp != BOT_Read )
			_SyncOperation();

		BYTE* pDstBuf = (BYTE*)pBuf;

		while( dwLen != 0 )
		{
			//����������Ѵ�������
			if( mdwCachedLen != 0 )
			{
				//��ȡ�����е�ʣ������
				DWORD dwCopyLen = ( dwLen < mdwCachedLen ) ? dwLen : mdwCachedLen;
				memcpy( pBuf, mpCachePtr, dwCopyLen );
				mdwCachedLen -= dwCopyLen;
				mpCachePtr += dwCopyLen;
				dwLen -= dwCopyLen;
				pDstBuf += dwCopyLen;
			}
			//����������Ѳ����������Ҷ�ȡ���ȴ��ڵ��ڻ��泤��
			else if( dwLen >= mCacheLen )
			{
				//ֱ�Ӵ��ļ��ж�ȡ����
				if( dwLen != _InternalRead( pDstBuf, dwLen ) )
					Except( Exception::ERR_CANNOT_READ_FILE, STR_ERR_READ_LEN );

				break;
			}
			//����������Ѳ����������Ҷ�ȡ����С�ڻ��泤��
			else
			{
				//���ļ��ж�ȡ������仺��
				DWORD dwReadLen = _InternalRead( mpCache, mCacheLen );
				if( dwReadLen < dwLen )
					Except( Exception::ERR_CANNOT_READ_FILE, STR_ERR_READ_LEN );

				//�ӻ����ж�ȡָ�����ȵ�����
				memcpy( pDstBuf, mpCache, dwLen );

				mpCachePtr = mpCache + dwLen;
				mdwCachedLen = dwReadLen - dwLen;

				break;
			}
		}

		//��¼���Ļ����������
		mLastBuffedOp = BOT_Read;
		mPosition += dwLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//д���ļ�����
	void BaseFile::Write( const void* pBuf, DWORD dwLen )
	{
		//��������еĻ����������д�����
		if( mLastBuffedOp != BOT_Write )
			_SyncOperation();

		BYTE* pSrcBuf = (BYTE*)pBuf;

		while( dwLen != 0 )
		{
			//�������δ��
			if( mdwCachedLen < mCacheLen )
			{
				//������д�뻺��
				DWORD dwRemainCacheLen = mCacheLen - mdwCachedLen;
				DWORD dwCopyLen = ( dwLen < dwRemainCacheLen ) ? dwLen : dwRemainCacheLen;
				memcpy( mpCachePtr, pSrcBuf, dwCopyLen );
				mdwCachedLen += dwCopyLen;
				mpCachePtr += dwCopyLen;
				dwLen -= dwCopyLen;
				pSrcBuf += dwCopyLen;
			}
			//�������������д�볤�ȴ��ڵ��ڻ��泤��
			else if( dwLen >= mCacheLen )
			{
				//����ǰ����������д���ļ�
				Flush();

				//ֱ�ӽ�����д���ļ�
				if( dwLen != _InternalWrite( pSrcBuf, dwLen ) )
					Except( Exception::ERR_CANNOT_WRITE_FILE, STR_ERR_WRITE_LEN );

				break;
			}
			//�������������д�볤��С�ڻ��泤��
			else
			{
				//����ǰ����������д���ļ�
				Flush();

				//��ʣ������д�뻺����
				memcpy( mpCache, pSrcBuf, dwLen );

				mpCachePtr = mpCache + dwLen;
				mdwCachedLen = dwLen;

				break;
			}
		}

		//��¼���Ļ����������
		mLastBuffedOp = BOT_Write;
		mPosition += dwLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�첽��ȡ�ļ�����
	bool BaseFile::AsynRead( void* pBuf, DWORD dwLen, LPOVERLAPPED pOverlapped )
	{
		//ͬ����д����
		_SyncOperation();

		DWORD dwReadLen;
		BOOL bResult = ReadFile( mFileHandle, pBuf, dwLen, &dwReadLen, pOverlapped );
		if( bResult == FALSE )
		{
			if( ERROR_IO_PENDING == GetLastError() )
				return false;
			else
				Except( Exception::ERR_CANNOT_READ_FILE, "�첽��ȡ�ļ�����ʧ�ܡ�" );
		}

		if( dwReadLen != dwLen )
			Except( Exception::ERR_CANNOT_READ_FILE, "�첽��ȡ�ļ����ݳ��ȴ���" );

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�첽д���ļ�����
	bool BaseFile::AsynWrite( const void* pBuf, DWORD dwLen, LPOVERLAPPED pOverlapped )
	{
		//ͬ����д����
		_SyncOperation();

		DWORD dwWroteLen;
		BOOL bResult = WriteFile( mFileHandle, pBuf, dwLen, &dwWroteLen, pOverlapped );
		if( bResult == FALSE )
		{
			if( ERROR_IO_PENDING == GetLastError() )
				return false;
			else
				Except( Exception::ERR_CANNOT_WRITE_FILE, "�첽д���ļ�����ʧ�ܡ�" );
		}

		if( dwWroteLen != dwLen )
			Except( Exception::ERR_CANNOT_WRITE_FILE, "�첽д���ļ����ݳ��ȴ���" );

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�첽��д���
	DWORD BaseFile::GetAsynResult( LPOVERLAPPED pOverlapped, bool bWait )
	{
		DWORD dwTransLen = 0;
		if( FALSE == GetOverlappedResult( mFileHandle, pOverlapped, &dwTransLen, bWait ? TRUE : FALSE ) )
			return 0;

		return dwTransLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���õ�ǰ��дλ��Ϊ�ļ���β
	void BaseFile::SetEndOfFile()
	{
		//ͬ����д����
		_SyncOperation();

		if( FALSE == ::SetEndOfFile( mFileHandle ) )
			Except( Exception::ERR_WINAPI_ERROR, "�����ļ���βʧ�ܡ�" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������д���ļ�
	void BaseFile::Flush()
	{
		if( mLastBuffedOp != BOT_Write )
			Except( Exception::ERR_INVALIDPARAMS,
			"�ϴν��еĻ������������д�����������޷�ִ�н���������д���ļ������" );

		if( mdwCachedLen == 0 )
			return;

		if( mdwCachedLen != _InternalWrite( mpCache, mdwCachedLen ) )
			Except( Exception::ERR_CANNOT_WRITE_FILE, STR_ERR_WRITE_LEN );

		mpCachePtr = mpCache;
		mdwCachedLen = 0;

		mLastBuffedOp = BOT_None;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ͬ����д����
	void BaseFile::_SyncOperation()
	{
		//���δ���л��������ֱ�ӷ���
		if( mLastBuffedOp == BOT_None )
			return;

		//������ڻ�������
		if( mdwCachedLen != 0 )
		{
			//�ж������еĲ���
			switch (mLastBuffedOp)
			{
				//��ȡ����
			case BOT_Read:
				{
					//ͬ����дָ��λ��
					if( SetFilePointer( mFileHandle, -(long)mdwCachedLen, NULL, FILE_CURRENT )
						== INVALID_SET_FILE_POINTER )
						Except( Exception::ERR_WINAPI_ERROR, "ͬ����дָ��λ��ʧ�ܡ�" );

					mpCachePtr = mpCache;
					mdwCachedLen = 0;
					break;
				}
				//д�����
			case BOT_Write:
				{
					//����������д���ļ�
					Flush();
					break;
				}
			}
		}

		mLastBuffedOp = BOT_None;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ڲ���ȡ�ļ�����
	DWORD BaseFile::_InternalRead( BYTE* pBuf, DWORD dwLen )
	{
		DWORD dwReadLen;
		BOOL bResult = ReadFile( mFileHandle, pBuf, dwLen, &dwReadLen, NULL );
		if( bResult == FALSE )
			Except( Exception::ERR_CANNOT_READ_FILE, "��ȡ�ļ�����ʧ�ܡ�" );

		return dwReadLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ڲ�д���ļ�����
	DWORD BaseFile::_InternalWrite( const BYTE* pBuf, DWORD dwLen )
	{
		DWORD dwWroteLen;
		BOOL bResult = WriteFile( mFileHandle, pBuf, dwLen, &dwWroteLen, NULL );
		if( bResult == FALSE )
			Except( Exception::ERR_CANNOT_WRITE_FILE, "д���ļ�����ʧ�ܡ�" );

		return dwWroteLen;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
