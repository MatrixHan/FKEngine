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

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//����ϵͳ�� �������ࣩ
	class SoundSystem : public Singleton< SoundSystem >
	{
	public:
		SoundSystemCfg*		mpConfig;			//����ϵͳ������Ϣ

		StaticSoundList		mStaticSounds;		//��̬�����б�
		StreamSoundList		mStreamSounds;		//��ʽ�����б�

	protected:

	public:
		SoundSystem();
		virtual ~SoundSystem();

		//��ʼ������ϵͳ
		virtual void Initialize( SoundSystemCfg* pSoundSystemCfg, RenderWindow* pRenderWindow ) = 0;

		//�ر�����ϵͳ
		virtual void Shutdown() = 0;

		//�����������Ÿ�ʽ
		virtual void SetPlayFormat( DWORD dwChannels, DWORD dwFrequency, DWORD dwBitRate ) = 0;

		//������̬����
		virtual StaticSound* CreateStaticSound() = 0;

		//������ʽ����
		virtual StreamSound* CreateStreamSound() = 0;

		//ɾ����̬����
		void DeleteStaticSound( StaticSound* pStaticSound );

		//ɾ����ʽ����
		void DeleteStreamSound( StreamSound* pStreamSound );

		//ɾ�����о�̬����
		void DeleteAllStaticSound();

		//ɾ��������ʽ����
		void DeleteAllStreamSound();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
