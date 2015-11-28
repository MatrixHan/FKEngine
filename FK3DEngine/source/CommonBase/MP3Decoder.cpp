/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	MP3Decoder
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
	static const char ERR_DECODE_MPEG_FRAME_INFO[] = "���� MPEG ��������֡��Ϣͷ����";
	//--------------------------------------------------------------------------------------------------------------
	MP3Decoder::MP3Decoder()
		: mdwID3v1Len		(0)
		, mdwID3v2Len		(0)
		, mdwFramePCMSize	(0)
		, mdwNumFrames		(0)
		, mdwPlayTime		(0)
		, mdwPrefectchLen	(0)
		, mdwReadDataLen	(0)
		, mpFramePCMBuffer	(NULL)
	{
		//��ʼ�� MPEG ��Ƶ�������
		InitAudioDecoder();
	}
	//--------------------------------------------------------------------------------------------------------------
	MP3Decoder::~MP3Decoder()
	{
		CloseSoundFile();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������ļ�
	SoundFormat* MP3Decoder::OpenSoundFile( FileObject* pFile, LPCSTR szFileName )
	{
		//�������ļ�
		pFile->Open( szFileName, OT_Read, true );

		mdwID3v2Len = mdwID3v1Len = 0;


		//��ȡ ID3v1 ����
		DWORD dwFileLen = pFile->GetLength();

		memset( &mOverlapped, 0, sizeof(OVERLAPPED) );
		mOverlapped.Offset = dwFileLen - 128;

		if( !pFile->AsynRead( &mID3v1Data, 128, &mOverlapped ) )
		{
			if( 128 != pFile->GetAsynResult( &mOverlapped ) )
				Except( Exception::ERR_INTERNAL_ERROR, "��ȡ MP3 �ļ� ID3v1 ��Ϣʧ�ܡ�" );
		}

		//������� ID3v1 ����
		if( 0 == memcmp( mID3v1Data.szTAG, "TAG", 3 ) )
			mdwID3v1Len = 128;


		//��ȡ ID3v2 ����ͷ
		ID3v2Header sID3v2Header;
		mOverlapped.Offset = 0;

		if( !pFile->AsynRead( &sID3v2Header, sizeof(ID3v2Header), &mOverlapped ) )
		{
			if( sizeof(ID3v2Header) != pFile->GetAsynResult( &mOverlapped ) )
				Except( Exception::ERR_INTERNAL_ERROR, "��ȡ MP3 �ļ� ID3v2 ��Ϣʧ�ܡ�" );
		}

		//������� ID3v2 ����ͷ
		if( 0 == memcmp( sID3v2Header.szID3, "ID3", 3 ) )
		{
			//���� ID3v2 ���ݳ��ȣ���ȫͬ������ֵ��
			mdwID3v2Len = sID3v2Header.szSize[3] |
				( (DWORD)sID3v2Header.szSize[2] << 7 ) |
				( (DWORD)sID3v2Header.szSize[1] << 14 ) |
				( (DWORD)sID3v2Header.szSize[0] << 21 );

			//�����Ƿ���� ID3v2 ��ע����ƫ��ֵ
			mdwID3v2Len = ( sID3v2Header.bFlag & 32 ) ? ( mdwID3v2Len + 20 ) : ( mdwID3v2Len + 10 );
		}

		//�洢�����ļ�ָ��
		mpSoundFile = pFile;

		//�����ļ�����֡
		_CheckAllFrames();

		//����������ʽ��Ϣ
		DWORD dwBytesPerSec = mFrameInfo.dwFrequency * mFrameInfo.dwChannels * 2;

		mSoundFormat.dwChannels		= mFrameInfo.dwChannels;		//����������
		mSoundFormat.dwFrequency	= mFrameInfo.dwFrequency;		//����Ƶ��
		mSoundFormat.dwBitRate		= 16;							//����������
		mSoundFormat.dwBytesPerSec	= dwBytesPerSec;				//����ÿ���ֽ���

		//����������ݳ���
		mdwFramePCMSize = 144 * 16 * mFrameInfo.dwChannels;
		mSoundFormat.dwLength = mdwNumFrames * mdwFramePCMSize;

		//�ܲ���ʱ�䣨����ֵ��
		mdwPlayTime = mSoundFormat.dwLength / dwBytesPerSec;

		//�����ļ�Ԥ������ͽ����������ݻ���
		mpFramePCMBuffer = (char*)malloc( 2 * mdwFileCacheLen + mdwFramePCMSize );
		mpFileReadPtr = mpFramePCMBuffer + mdwFramePCMSize;
		mpFileWorkPtr = mpFileReadPtr + mdwFileCacheLen;

		//����������ȡλ�õ����
		ResetReadPos();

		return &mSoundFormat;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ر������ļ�
	void MP3Decoder::CloseSoundFile()
	{
		//�ر������ļ�
		if( mpSoundFile != NULL )
		{
			//�������Ԥ���ļ�
			if( mdwPrefectchLen > 0 )
				_EndPrefectch();

			mpSoundFile->Close();
			mpSoundFile = NULL;

			free( mpFramePCMBuffer );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������ȡλ�õ����
	void MP3Decoder::ResetReadPos()
	{
		//�������Ԥ���ļ�
		if( mdwPrefectchLen > 0 )
			_EndPrefectch();

		//������ʼ����λ��
		mdwFramePCMLen = 0;
		mdwFrameOffset = 0;

		//��ȡ��ʼ�ļ�����
		_BeginPrefectch();
		_EndPrefectch();

		//��ʼԤ���ڶ����ļ�����
		_BeginPrefectch();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�������ݵ�ָ������
	void MP3Decoder::ReadSoundData( void* pBuf, DWORD dwLen )
	{
		static char pFrameDataBuf[MPEG_MaxFrameSize] = { NULL };

		DWORD dwFinishLen = 0;
		char* pDstPtr = (char*)pBuf;

		//����ϴ��Ѿ������˵�ǰ֡������������
		if( mdwFramePCMLen != 0 )
		{
			char* pFramePCMPtr = mpFramePCMBuffer + mdwFramePCMSize - mdwFramePCMLen;

			//�����ȡ���ȴ����ѽ��볤��
			if( dwLen > mdwFramePCMLen  )
			{
				memcpy( pDstPtr, pFramePCMPtr, mdwFramePCMLen );
				pDstPtr += mdwFramePCMLen;
				dwFinishLen += mdwFramePCMLen;
			}
			//�����ȡ����С���ѽ��볤��
			else
			{
				memcpy( pDstPtr, pFramePCMPtr, dwLen );
				mdwFramePCMLen -= dwLen;
				return;
			}
		}

		//ѭ������ÿһ֡
		while( dwFinishLen < dwLen )
		{
			char* pFrameDataPtr;
			DWORD dwRemainDataLen = mdwReadDataLen - mdwFrameOffset;

			//�����ǰ֡��Ϣͷ�ļ����ݲ���ȫ�ڻ�����
			if( dwRemainDataLen < 4 )
			{
				//����ʣ������
				memcpy( pFrameDataBuf, mpFileWorkPtr + mdwFrameOffset, dwRemainDataLen );

				//�����ϴ�Ԥ������ʼ��һ��Ԥ��
				_EndPrefectch();
				_BeginPrefectch();

				//�����¶�ȡ����һ��������
				mdwFrameOffset = 4 - dwRemainDataLen;
				memcpy( pFrameDataBuf + dwRemainDataLen, mpFileWorkPtr, mdwFrameOffset );

				//����֡����ͷ
				if( !_DecodeFrameHeader( (BYTE*)pFrameDataBuf, &mFrameInfo ) )
					Except( Exception::ERR_INTERNAL_ERROR, ERR_DECODE_MPEG_FRAME_INFO );

				//����֡��������
				memcpy( pFrameDataBuf + 4, mpFileWorkPtr + 4, mFrameInfo.dwFrameSize );
				mdwFrameOffset += mFrameInfo.dwFrameSize;

				pFrameDataPtr = pFrameDataBuf + 4;
			}
			//�����ǰ֡��Ϣͷ�ļ������ڻ�����
			else
			{
				pFrameDataPtr = mpFileWorkPtr + mdwFrameOffset;

				//����֡����ͷ
				if( !_DecodeFrameHeader( (BYTE*)pFrameDataPtr, &mFrameInfo ) )
					Except( Exception::ERR_INTERNAL_ERROR, ERR_DECODE_MPEG_FRAME_INFO );

				dwRemainDataLen -= 4;
				mdwFrameOffset += 4;

				//���ʣ�����ݻ��治����ȫ��֡��������
				if( dwRemainDataLen < mFrameInfo.dwFrameSize )
				{
					//����ʣ������
					if( dwRemainDataLen > 0 )
						memcpy( pFrameDataBuf, mpFileWorkPtr + mdwFrameOffset, dwRemainDataLen );

					//�����ϴ�Ԥ������ʼ��һ��Ԥ��
					_EndPrefectch();
					_BeginPrefectch();

					//�����¶�ȡ����һ��������
					mdwFrameOffset = mFrameInfo.dwFrameSize - dwRemainDataLen;
					memcpy( pFrameDataBuf + dwRemainDataLen, mpFileWorkPtr, mdwFrameOffset );
					pFrameDataPtr = pFrameDataBuf;
				}
				//���ʣ�����ݻ������ȫ��֡��������
				else
				{
					pFrameDataPtr += 4;
					mdwFrameOffset += mFrameInfo.dwFrameSize;
				}
			}

			//����֡��������
			DWORD dwDecodePCMLen = (DWORD)DecodeAudioFrame( &mFrameInfo, pFrameDataPtr, mpFramePCMBuffer );
			if( dwDecodePCMLen != mdwFramePCMSize )
				Except( Exception::ERR_INTERNAL_ERROR, "MPEG ��Ƶ����������ݳ��ȴ���" );

			//������Ҫ���Ƶ���ȡĿ������ݳ���
			DWORD dwReamainReadLen = dwLen - dwFinishLen;
			DWORD dwCopyLen = ( dwReamainReadLen > mdwFramePCMSize ) ? mdwFramePCMSize : dwReamainReadLen;
			memcpy( pDstPtr, mpFramePCMBuffer, dwCopyLen );
			mdwFramePCMLen = mdwFramePCMSize - dwCopyLen;
			dwFinishLen += dwCopyLen;
			pDstPtr += dwCopyLen;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ļ�����֡
	void MP3Decoder::_CheckAllFrames()
	{
		//�Թ� ID3v2 ���ݶ�
		mOverlapped.Offset = mdwID3v2Len;

		DWORD dwFileLen = mpSoundFile->GetLength();
		BYTE szFrameHeader[4];

		for(;;)
		{
			//����ѵ����ļ���β
			if( dwFileLen - mOverlapped.Offset < 4 )
				break;

			//��ȡ֡��Ϣͷ����
			if( !mpSoundFile->AsynRead( szFrameHeader, 4, &mOverlapped ) )
			{
				if( 4 != mpSoundFile->GetAsynResult( &mOverlapped ) )
					Except( Exception::ERR_INTERNAL_ERROR, "��ȡ MPEG ��������֡��Ϣͷ����" );
			}

			//����֡��Ϣͷ
			if( !_DecodeFrameHeader( szFrameHeader, &mFrameInfo ) )
				break;

			//���ʣ���ļ�����С�ڵ�ǰ֡���ݳ���
			DWORD dwFrameLen = mFrameInfo.dwFrameSize + 4;
			if( dwFileLen - mOverlapped.Offset < dwFrameLen )
				break;

			//�ƶ�����һ֡
			++mdwNumFrames;

			mOverlapped.Offset += dwFrameLen;
		}

		//��¼�������ݽ�βλ��
		mSoundDataEnd = mOverlapped.Offset;
		mOverlapped.Offset = mdwID3v2Len;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����֡��Ϣͷ
	bool MP3Decoder::_DecodeFrameHeader( BYTE szFrameHeader[4], MPEGFrameInfo* pFrameInfo )
	{
		//����ͷ����˳��
		DWORD dwFrameHeader;
		BYTE* pFrameHeader = (BYTE*)&dwFrameHeader;
		pFrameHeader[0] = szFrameHeader[3];
		pFrameHeader[1] = szFrameHeader[2];
		pFrameHeader[2] = szFrameHeader[1];
		pFrameHeader[3] = szFrameHeader[0];

		//����Ƿ�Ϊ��ȷ֡��Ϣͷ��ǰ 11 λ��Ϊ�棩
		if( ( dwFrameHeader >> 21 ) != 0x7FF )
			return false;

		DWORD dwBitRateIndex = ( dwFrameHeader >> 12 ) & 15;
		DWORD dwFrequencyIndex = ( dwFrameHeader >> 10 ) & 3;

		//��ȡ MPEG ֡��Ϣ
		pFrameInfo->bCRC			= ( ( dwFrameHeader >> 16 ) & 1 ) ? false : true;	//�Ƿ���� CRC У������
		pFrameInfo->bPadding		= ( ( dwFrameHeader >> 9 ) & 1 ) ? true : false;	//�Ƿ���ڲ���λ
		pFrameInfo->bCopyright		= ( ( dwFrameHeader >> 3 ) & 1 ) ? true : false;	//�Ƿ����а�Ȩ
		pFrameInfo->bOriginal		= ( ( dwFrameHeader >> 2 ) & 1 ) ? true : false;	//�Ƿ�Ϊԭ��
		pFrameInfo->bJointMode		= (BYTE)( ( dwFrameHeader >> 4 ) & 3 );				// Joint stereo ģʽ
		pFrameInfo->bEmphasis		= (BYTE)( dwFrameHeader & 3 );						// Emphasis ģʽ

		//�����������
		pFrameInfo->nChannelMode = ( dwFrameHeader >> 6 ) & 3;
		pFrameInfo->dwChannels = ( pFrameInfo->nChannelMode == 3 ) ? 1 : 2;

		//���� MPEG �汾�Ͳ���
		int nMpegVersion = ( dwFrameHeader >> 19 ) & 3;
		switch (nMpegVersion)
		{
		case 3:
			pFrameInfo->bMpegVersion = MPEG_Version1;
			pFrameInfo->nFreqIndex = dwFrequencyIndex;
			break;
		case 2:
			pFrameInfo->bMpegVersion = MPEG_Version2;
			pFrameInfo->nFreqIndex = dwFrequencyIndex + 3;
			break;
		case 0:
			pFrameInfo->bMpegVersion = MPEG_Version25;
			pFrameInfo->nFreqIndex = dwFrequencyIndex + 6;
			break;
		default:
			Except( Exception::ERR_INTERNAL_ERROR, "����� MPEG ��Ƶ֡ѹ���汾��" );
		}

		pFrameInfo->bMpegLayer = (BYTE)( 3 - ( ( dwFrameHeader >> 17 ) & 3 ) );

		//ӳ��� MPEG ���������ʺ�Ƶ��
		pFrameInfo->dwBitRate	= MPEG_BitRateTable[ pFrameInfo->bMpegVersion ][ pFrameInfo->bMpegLayer ][ dwBitRateIndex ];
		pFrameInfo->dwFrequency	= MPEG_FrequencyTable[ pFrameInfo->nFreqIndex ];
		pFrameInfo->nBitRateIndex = dwBitRateIndex;

		if( pFrameInfo->dwBitRate == 0 )
			Except( Exception::ERR_INTERNAL_ERROR, "����� MPEG ��Ƶ֡�����ʡ�" );

		//����֡�������ݳ���
		DWORD dwFrameSize;
		switch (pFrameInfo->bMpegLayer)
		{
		case MPEG_Layer1:
			dwFrameSize  = pFrameInfo->dwBitRate * 12000;
			dwFrameSize /= pFrameInfo->dwFrequency;
			dwFrameSize  = ( ( dwFrameSize + ( pFrameInfo->bPadding ? 1 : 0 ) ) << 2 ) - 4;
			break;
		case MPEG_Layer2:
			dwFrameSize  = pFrameInfo->dwBitRate * 144000;
			dwFrameSize /= pFrameInfo->dwFrequency;
			dwFrameSize += ( pFrameInfo->bPadding ? 1 : 0 ) - 4;
			break;
		case MPEG_Layer3:
			dwFrameSize  = pFrameInfo->dwBitRate * 144000;
			dwFrameSize /= pFrameInfo->dwFrequency << ( pFrameInfo->bMpegVersion ? 1 : 0 );
			dwFrameSize += ( pFrameInfo->bPadding ? 1 : 0 ) - 4;
			break; 
		default:
			Except( Exception::ERR_INTERNAL_ERROR, "����� MPEG ��Ƶ֡ѹ����������" );
		}

		pFrameInfo->dwFrameSize = dwFrameSize;

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼԤ���ļ�����
	void FKFastcall MP3Decoder::_BeginPrefectch()
	{
		//���ʣ�����ݳ���С�ڻ��泤��
		DWORD dwReamainLen = mSoundDataEnd - mOverlapped.Offset;
		if( dwReamainLen <= mdwFileCacheLen )
			mdwPrefectchLen = dwReamainLen;
		else
			mdwPrefectchLen = mdwFileCacheLen;

		//Ԥ���ļ�����
		mpSoundFile->AsynRead( mpFileReadPtr, mdwPrefectchLen, &mOverlapped );

		if( dwReamainLen <= mdwFileCacheLen )
			mOverlapped.Offset = mdwID3v2Len;
		else
			mOverlapped.Offset += mdwFileCacheLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����Ԥ���ļ�����
	void FKFastcall MP3Decoder::_EndPrefectch()
	{
		if( mdwPrefectchLen != mpSoundFile->GetAsynResult( &mOverlapped ) )
			Except( Exception::ERR_WINAPI_ERROR, "�첽��ȡ MP3 �ļ�����ʧ�ܡ�" );

		//�л��ļ����ݽ���/��ȡ����
		char* pTmpPtr = mpFileWorkPtr;
		mpFileWorkPtr = mpFileReadPtr;
		mpFileReadPtr = pTmpPtr;

		mdwReadDataLen = mdwPrefectchLen;
		mdwPrefectchLen = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
