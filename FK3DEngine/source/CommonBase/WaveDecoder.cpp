/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	WaveDecoder
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
	WaveDecoder::WaveDecoder()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	WaveDecoder::~WaveDecoder()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������ļ�
	SoundFormat* WaveDecoder::OpenSoundFile( FileObject* pFile, LPCSTR szFileName )
	{
		//�������ļ�
		pFile->Open( szFileName, OT_Read );

		//��ȡ WAV �ļ�����ͷ
		WaveHeader sFileHeader;
		pFile->Read( &sFileHeader, sizeof(WaveHeader) );

		//����ļ�ͷ�Ƿ���ȷ
		if( 0 != memcmp( sFileHeader.szRIFF, "RIFF", 4 ) )
			goto ErrorFormat;

		if( 0 != memcmp( sFileHeader.szWAVE, "WAVEfmt ", 8 ) )
			goto ErrorFormat;

		//�����ѹ�� WAV �ļ�
		if( sFileHeader.wFormatTag != 1 )
			Except( Exception::ERR_INTERNAL_ERROR, "�޷�����ѹ���� WAV �ļ���" );

		mSoundFormat.dwChannels		= (DWORD)sFileHeader.wChannels;
		mSoundFormat.dwFrequency	= sFileHeader.dwSamplePerSec;
		mSoundFormat.dwBitRate		= (DWORD)sFileHeader.wBitsPerSample;
		mSoundFormat.dwBytesPerSec	= sFileHeader.dwBytesPerSec;
		mSoundFormat.dwLength		= sFileHeader.dwDataLen;

		//�����ļ�ָ��
		mpSoundFile = pFile;

		return &mSoundFormat;

		//�ļ���ʽ������
ErrorFormat:
		pFile->Close();
		Except( Exception::ERR_CANNOT_OPEN_FILE, "����� WAV �ļ���ʽ��" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ر������ļ�
	void WaveDecoder::CloseSoundFile()
	{
		//�ر������ļ�
		if( mpSoundFile != NULL )
		{
			mpSoundFile->Close();
			mpSoundFile = NULL;
		}		
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������ȡλ�õ����
	void WaveDecoder::ResetReadPos()
	{
		mpSoundFile->SetPosition( sizeof(WaveHeader), BP_Begin );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�������ݵ�ָ������
	void WaveDecoder::ReadSoundData( void* pBuf, DWORD dwLen )
	{
		mpSoundFile->Read( pBuf, dwLen );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
