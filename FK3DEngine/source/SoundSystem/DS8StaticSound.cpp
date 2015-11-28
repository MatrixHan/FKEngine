/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	DS8StaticSound
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/SoundSystem/SoundSystemInsideHeader.h"
#include <MMReg.h>
#include "../../../Depend/dx9/dsound.h"
#include "../../../Depend/dx9/dxerr9.h"
#include "../../include/CommonBase/MemoryMarco.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	DS8StaticSound::DS8StaticSound()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	DS8StaticSound::~DS8StaticSound()
	{
		FKTry
		{
			UnloadStaticSound();
		}
		FKCatch
		{
			ShowExceptionMsg;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���뾲̬����
	void DS8StaticSound::LoadStaticSound( SoundDecoder* pSoundDecoder )
	{
		//���ô����������ʽ
		SoundFormat* pSoundFormat = &pSoundDecoder->mSoundFormat;

		_CreateSoundBuffer( pSoundFormat, pSoundFormat->dwLength, 0 );

		//�����������ݵ�������
		mdwSoundLen = pSoundFormat->dwLength;
		void* pBufPtr = NULL;
		DWORD dwBufLen = 0;

		HRESULT result = mpSoundBuffer->Lock( 0, 0, &pBufPtr, &dwBufLen, NULL, NULL, DSBLOCK_ENTIREBUFFER  );
		if( FAILED( result ) )
			Except( Exception::ERR_SOUND_API_ERROR, (String)"���� DirectSoundBuffer8 ����������ʧ�ܡ�"
			"\nDS8 ����������" + DXGetErrorDescription9( result ) );

		pSoundDecoder->ReadSoundData( pBufPtr, mdwSoundLen );

		result = mpSoundBuffer->Unlock( pBufPtr, dwBufLen, NULL, 0 );
		if( FAILED( result ) )
			Except( Exception::ERR_SOUND_API_ERROR, (String)"���� DirectSoundBuffer8 ����������ʧ�ܡ�"
			"\nDS8 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ж�ؾ�̬����
	void DS8StaticSound::UnloadStaticSound()
	{
		if( mpSoundBuffer != NULL )
		{
			Stop();
			mpSoundBuffer->Release();
			mpSoundBuffer = NULL;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
