/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	DS8BaseSound
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/SoundSystem/SoundSystemInsideHeader.h"
//#include "../../include/CommonBase/NoMemoryMarco.h"
#include <MMReg.h>
#include "../../../Depend/dx9/dsound.h"
#include "../../../Depend/dx9/dxerr9.h"
#include "../../include/CommonBase/MemoryMarco.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	DS8BaseSound::DS8BaseSound()
		: mpSoundBuffer		(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void DS8BaseSound::Play()
	{
		HRESULT result = mpSoundBuffer->Play( 0, 0, DSBPLAY_LOOPING );
		if( FAILED( result ) )
			Except( Exception::ERR_SOUND_API_ERROR, (String)"ʹ�� DirectSoundBuffer8 ���������沥������ʧ�ܡ�"
			"\nDS8 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ֹͣ��������
	void DS8BaseSound::Stop()
	{
		HRESULT result = mpSoundBuffer->Stop();
		if( FAILED( result ) )
			Except( Exception::ERR_SOUND_API_ERROR, (String)"ֹͣ���� DirectSoundBuffer8 ����������ʧ�ܡ�"
			"\nDS8 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void DS8BaseSound::SetVolume( float fVolume )
	{
		//����������������
		float fScaling = 0.0f;
		if( fVolume > 0.0f )
		{
			// log10( ��ǰ�������� * 100.0f ) / log10( ����������� * 100.0f )
			fScaling = log10( fVolume * 100.0f ) / 2.0f;
		}

		LONG nVolume = FloorToInt( ( fScaling - 1.0f ) * 10000.0f );

		HRESULT result = mpSoundBuffer->SetVolume( nVolume );
		if( FAILED( result ) )
			Except( Exception::ERR_SOUND_API_ERROR, (String)"���� DirectSoundBuffer8 ��������������ʧ�ܡ�"
			"\nDS8 ����������" + DXGetErrorDescription9( result ) );

		mfVolume = fVolume;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������������
	void FKFastcall DS8BaseSound::_CreateSoundBuffer( const SoundFormat* pSoundFmt, DWORD dwLength, DWORD dwFlags )
	{
		WAVEFORMATEX wfx;
		wfx.wFormatTag      = (WORD)WAVE_FORMAT_PCM; 
		wfx.nChannels       = (WORD)pSoundFmt->dwChannels; 
		wfx.nSamplesPerSec  = pSoundFmt->dwFrequency; 
		wfx.wBitsPerSample  = (WORD)pSoundFmt->dwBitRate; 
		wfx.nBlockAlign     = (WORD)( pSoundFmt->dwBitRate / 8 * pSoundFmt->dwChannels );
		wfx.nAvgBytesPerSec = pSoundFmt->dwBytesPerSec;
		wfx.cbSize			= 0;

		DSBUFFERDESC dsbd;
		memset( &dsbd, 0, sizeof(DSBUFFERDESC) );
		dsbd.dwSize				= sizeof(DSBUFFERDESC);
		dsbd.dwBufferBytes		= dwLength;
		dsbd.lpwfxFormat		= &wfx;
		dsbd.dwFlags			= dwFlags | DSBCAPS_CTRLVOLUME;

		//��������������
		HRESULT result = DS8SoundSystem::mpDirectSound8->CreateSoundBuffer( &dsbd, &mpSoundBuffer, NULL );
		if( FAILED( result ) )
			Except( Exception::ERR_SOUND_API_ERROR, (String)"���� DirectSound8 ����������ʧ�ܡ�"
			"\nDS8 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
