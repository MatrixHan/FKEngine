/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SoundSystem
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/SoundSystem/SoundSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	SoundSystem::SoundSystem()
		: mpConfig		(NULL)
	{
		mStaticSounds.Initialize( 20, 20 );
		mStreamSounds.Initialize( 20, 10 );
	}
	//--------------------------------------------------------------------------------------------------------------
	SoundSystem::~SoundSystem()
	{
		mStaticSounds.Release();
		mStreamSounds.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ����̬����
	void SoundSystem::DeleteStaticSound( StaticSound* pStaticSound )
	{
		StaticSoundList::Iterator it = mStaticSounds.Begin();
		StaticSoundList::Iterator end = mStaticSounds.End();
		for(; it!=end; ++it )
		{
			if( *it == pStaticSound )
			{
				mStaticSounds.Erase( it );
				delete pStaticSound;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ����ʽ����
	void SoundSystem::DeleteStreamSound( StreamSound* pStreamSound )
	{
		StreamSoundList::Iterator it = mStreamSounds.Begin();
		StreamSoundList::Iterator end = mStreamSounds.End();
		for(; it!=end; ++it )
		{
			if( *it == pStreamSound )
			{
				mStreamSounds.Erase( it );
				delete pStreamSound;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����о�̬����
	void SoundSystem::DeleteAllStaticSound()
	{
		StaticSoundList::Iterator it = mStaticSounds.Begin();
		StaticSoundList::Iterator end = mStaticSounds.End();
		for(; it!=end; ++it )
			SafeDelete( *it );

		mStaticSounds.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��������ʽ����
	void SoundSystem::DeleteAllStreamSound()
	{
		StreamSoundList::Iterator it = mStreamSounds.Begin();
		StreamSoundList::Iterator end = mStreamSounds.End();
		for(; it!=end; ++it )
			SafeDelete( *it );

		mStreamSounds.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
