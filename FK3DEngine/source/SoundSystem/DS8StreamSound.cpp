/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	DS8StreamSound
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
	DS8StreamSound::DS8StreamSound()
		: mbStopFill		(false)
		, mhFillThread		(NULL)
		, mhFillEvent		(NULL)
		, mpFillCache		(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	DS8StreamSound::~DS8StreamSound()
	{
		FKTry
		{
			UnloadStreamSound();
		}
		FKCatch
		{
			ShowExceptionMsg;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ʽ����
	void DS8StreamSound::LoadStreamSound( SoundDecoder* pSoundDecoder, DWORD dwCacheTime )
	{
		//�洢����������ָ��
		mpSoundDecoder = pSoundDecoder;

		//������������֪ͨ�¼�
		mhFillEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
		if( mhFillEvent == NULL )
			Except( Exception::ERR_WINAPI_ERROR, "������ʽ������������¼�ʧ�ܡ�" );

		//������������
		DWORD dwNumNotifys = 32;
		mdwFillLen = pSoundDecoder->mSoundFormat.dwBytesPerSec * dwCacheTime / ( 1000 * dwNumNotifys );
		mdwBufSize = mdwFillLen * dwNumNotifys;
		mdwFillPos = 0;

		_CreateSoundBuffer( &pSoundDecoder->mSoundFormat, mdwBufSize,
			DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GETCURRENTPOSITION2 );

		//��������������仺��
		mpFillCache = (BYTE*)malloc( mdwBufSize * 2 );

		//��ȡ��������֪ͨ���ýӿ�
		IDirectSoundNotify* pDSNotify = NULL;
		HRESULT result = mpSoundBuffer->QueryInterface( IID_IDirectSoundNotify, (void**)&pDSNotify );
		if( FAILED( result ) )
			Except( Exception::ERR_INTERNAL_ERROR, (String)"��ȡ DirectSound8 ��������֪ͨ���ýӿ�ʧ�ܡ�"
			"\nDS8 ����������" + DXGetErrorDescription9( result ) );

		//������������֪ͨλ��
		DSBPOSITIONNOTIFY* pDSPosNotify = (DSBPOSITIONNOTIFY*)malloc( sizeof(DSBPOSITIONNOTIFY) * dwNumNotifys );
		DSBPOSITIONNOTIFY* pDSPosNotifyPtr = pDSPosNotify;
		for( DWORD i=0; i<dwNumNotifys; ++i, ++pDSPosNotifyPtr )
		{
			pDSPosNotifyPtr->dwOffset = mdwFillLen * i;
			pDSPosNotifyPtr->hEventNotify = mhFillEvent;
		}

		result = pDSNotify->SetNotificationPositions( dwNumNotifys, pDSPosNotify );

		free( pDSPosNotify );
		pDSNotify->Release();

		if( FAILED( result ) )
			Except( Exception::ERR_INTERNAL_ERROR, (String)"���� DirectSound8 ��������֪ͨʧ�ܡ�"
			"\nDS8 ����������" + DXGetErrorDescription9( result ) );

		//�����ʼ��������
		_FillSoundData( this );

		//����������������߳�
		mbStopFill = false;
		mhFillThread = CreateThread( NULL, 0, _FillSoundThread, (LPVOID)this, 0, NULL );
		if( mhFillThread == NULL )
			Except( Exception::ERR_WINAPI_ERROR, "������ʽ������������߳�ʧ�ܡ�" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ж����ʽ����
	void DS8StreamSound::UnloadStreamSound()
	{
		//ֹͣ��������
		if( mpSoundBuffer != NULL )
			Stop();

		//��ֹ��������߳�
		if( mhFillThread != NULL )
		{
			//�����������������ֹ�¼�
			mbStopFill = true;
			if( FALSE == SetEvent( mhFillEvent ) )
				Except( Exception::ERR_WINAPI_ERROR, "�����������������ֹ�¼�ʧ�ܡ�" );

			//�ȴ���������߳���ֹ
			DWORD dwResult = WaitForSingleObject( mhFillThread, 10000 );
			CloseHandle( mhFillThread );
			mhFillThread = NULL;
			if( dwResult != WAIT_OBJECT_0 )
				Except( Exception::ERR_WINAPI_ERROR, "�ȴ�������������߳���ֹ����" );
		}

		//ɾ����������¼�
		if( mhFillEvent != NULL )
		{
			CloseHandle( mhFillEvent );
			mhFillEvent = NULL;
		}

		//�ͷ���������
		SafeRelease( mpSoundBuffer );
		SafeFree( mpFillCache );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʽ������������߳�
	DWORD WINAPI DS8StreamSound::_FillSoundThread( LPVOID pVoid )
	{
		DS8StreamSound* pThis = (DS8StreamSound*)pVoid;

		FKTry
		{
			for(;;)
			{
				//�ȴ�������������¼�
				DWORD dwResult = WaitForSingleObject( pThis->mhFillEvent, INFINITE );
				if( dwResult != WAIT_OBJECT_0 )
					Except( Exception::ERR_WINAPI_ERROR, "�ȴ�������������߳��¼�����" );

				//���Ҫ���߳���ֹ
				if( pThis->mbStopFill )
					break;

				//�����������
				_FillSoundData( pThis );
			}
		}
		FKCatch
		{
			ShowExceptionMsg;
		}

		return 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����������
	void DS8StreamSound::_FillSoundData( DS8StreamSound* pThis )
	{
		//������������
		DWORD dwFillLen = pThis->mdwFillLen;
		BYTE* pSrcPtr = pThis->mpFillCache;
		
		pThis->mpSoundDecoder->ReadSoundData( pSrcPtr, dwFillLen );

		//������������
		BYTE* pDstPtr1 = NULL;
		BYTE* pDstPtr2 = NULL;
		DWORD dwLockSize1;
		DWORD dwLockSize2;

		HRESULT result = pThis->mpSoundBuffer->Lock( pThis->mdwFillPos, dwFillLen,
			(void**)&pDstPtr1, &dwLockSize1, (void**)pDstPtr2, &dwLockSize2, 0 );
		if( FAILED( result ) )
			Except( Exception::ERR_INTERNAL_ERROR, "���� DirectSoundBuffer8 ����������ʧ�ܡ�" );

		//������������
		memcpy( pDstPtr1, pSrcPtr, dwLockSize1 );
		if( pDstPtr2 != NULL )
			memcpy( pDstPtr2, pSrcPtr + dwLockSize1, dwLockSize2 );

		//������������
		result = pThis->mpSoundBuffer->Unlock( pDstPtr1, dwLockSize1, pDstPtr2, dwLockSize2 );
		if( FAILED( result ) )
			Except( Exception::ERR_INTERNAL_ERROR, "���� DirectSoundBuffer8 ����������ʧ�ܡ�" );


		pThis->mdwFillPos += dwFillLen;

		//����ѵ���������β
		if( pThis->mdwFillPos >= pThis->mdwBufSize )
			pThis->mdwFillPos -= pThis->mdwBufSize;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
