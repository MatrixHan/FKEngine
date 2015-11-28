/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	DS8SoundSystem
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

	IDirectSound8*		DS8SoundSystem::mpDirectSound8	= NULL;
	IDirectSoundBuffer*	DS8SoundSystem::mpPrimaryBuffer	= NULL;

	//--------------------------------------------------------------------------------------------------------------
	DS8SoundSystem::DS8SoundSystem()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	DS8SoundSystem::~DS8SoundSystem()
	{
		Shutdown();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ������ϵͳ
	void DS8SoundSystem::Initialize( SoundSystemCfg* pSoundSystemCfg, RenderWindow* pRenderWindow )
	{
		//���� DirectSound8 ����
		HRESULT result = DirectSoundCreate8( NULL, &mpDirectSound8, NULL );
		if( FAILED( result ) )
			Except( Exception::ERR_SOUND_API_ERROR, (String)"���� DirectSound8 ����ʧ�ܡ�"
			"\nDS8 ����������" + DXGetErrorDescription9( result ) );

		//���� DirectSound8 Э����
		result = mpDirectSound8->SetCooperativeLevel( pRenderWindow->mhWnd, DSSCL_PRIORITY );
		if( FAILED( result ) )
			Except( Exception::ERR_SOUND_API_ERROR, (String)"���� DirectSound8 Э����ʧ�ܡ�"
			"\nDS8 ����������" + DXGetErrorDescription9( result ) );

		//���� DirectSound8 ����������
		DWORD pSpeakerType[] =
		{
			DSSPEAKER_DIRECTOUT,		// Speaker_Unknown		= 0	δ֪���������������ã�
			DSSPEAKER_HEADPHONE,		// Speaker_Headphone	= 1	������Ͳ
			DSSPEAKER_MONO,				// Speaker_Mono			= 2	������
			DSSPEAKER_STEREO,			// Speaker_Stereo		= 3	˫����
			DSSPEAKER_QUAD,				// Speaker_Quad			= 4	������
			DSSPEAKER_SURROUND,			// Speaker_Surround		= 5	����������
			DSSPEAKER_5POINT1,			// Speaker_5Point1		= 6	5.1 ����
			DSSPEAKER_7POINT1,			// Speaker_7Point1		= 7	7.1 ����
		};

		result = mpDirectSound8->SetSpeakerConfig( pSpeakerType[ pSoundSystemCfg->eSpeakerType ] );
		if( FAILED( result ) )
			Except( Exception::ERR_SOUND_API_ERROR, (String)"���� DirectSound8 Э����ʧ�ܡ�"
			"\nDS8 ����������" + DXGetErrorDescription9( result ) );


		//��������������
		DSBUFFERDESC dsbd;
		memset( &dsbd, 0, sizeof(DSBUFFERDESC) );
		dsbd.dwSize		= sizeof(DSBUFFERDESC);
		dsbd.dwFlags	= DSBCAPS_PRIMARYBUFFER;

		result = mpDirectSound8->CreateSoundBuffer( &dsbd, &mpPrimaryBuffer, NULL );
		if( FAILED( result ) )
			Except( Exception::ERR_SOUND_API_ERROR, (String)"���� DirectSound8 ����������ʧ�ܡ�"
			"\nDS8 ����������" + DXGetErrorDescription9( result ) );

		//���������������ʽ
		SetPlayFormat( pSoundSystemCfg->dwChannels, pSoundSystemCfg->dwFrequency, pSoundSystemCfg->dwBitRate );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ر�����ϵͳ
	void DS8SoundSystem::Shutdown()
	{
		DeleteAllStaticSound();
		DeleteAllStreamSound();

		SafeRelease( mpPrimaryBuffer );

		SafeRelease( mpDirectSound8 );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����������Ÿ�ʽ
	void DS8SoundSystem::SetPlayFormat( DWORD dwChannels, DWORD dwFrequency, DWORD dwBitRate )
	{
		if( mpPrimaryBuffer == NULL )
			Except( Exception::ERR_INVALIDPARAMS, "�ڴ�������������֮ǰ�޷����ò��Ÿ�ʽ��" );

		//���������������ʽ
		WAVEFORMATEX wfx;
		wfx.wFormatTag      = (WORD)WAVE_FORMAT_PCM; 
		wfx.nChannels       = (WORD)dwChannels; 
		wfx.nSamplesPerSec  = dwFrequency; 
		wfx.wBitsPerSample  = (WORD)dwBitRate; 
		wfx.nBlockAlign     = (WORD)( dwBitRate / 8 * dwChannels );
		wfx.nAvgBytesPerSec = (DWORD)( dwFrequency * wfx.nBlockAlign );
		wfx.cbSize			= 0;

		HRESULT result = mpPrimaryBuffer->SetFormat( &wfx );
		if( FAILED( result ) )
			Except( Exception::ERR_SOUND_API_ERROR, (String)"���� DirectSound8 ���������沥�Ÿ�ʽ��"
			"\nDS8 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//������̬����
	StaticSound* DS8SoundSystem::CreateStaticSound()
	{
		DS8StaticSound* pStaticSound = new DS8StaticSound;
		*mStaticSounds.Push() = pStaticSound;
		return pStaticSound;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ʽ����
	StreamSound* DS8SoundSystem::CreateStreamSound()
	{
		DS8StreamSound* pStreamSound = new DS8StreamSound;
		*mStreamSounds.Push() = pStreamSound;
		return pStreamSound;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
