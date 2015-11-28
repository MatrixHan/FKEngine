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

#pragma once

//==================================================================================================================

struct IDirectSound8;
struct IDirectSoundBuffer;

//--------------------------------------------------------------------------------------------------------------

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	// DirectSound 8 ����ϵͳ��
	class DS8SoundSystem : public SoundSystem
	{
	protected:
		friend class DS8BaseSound;

		static IDirectSound8*		mpDirectSound8;
		static IDirectSoundBuffer*	mpPrimaryBuffer;

	public:
		DS8SoundSystem();
		~DS8SoundSystem();

		//��ʼ������ϵͳ
		void Initialize( SoundSystemCfg* pSoundSystemCfg, RenderWindow* pRenderWindow );

		//�ر�����ϵͳ
		void Shutdown();

		//�����������Ÿ�ʽ
		void SetPlayFormat( DWORD dwChannels, DWORD dwFrequency, DWORD dwBitRate );

		//������̬����
		StaticSound* CreateStaticSound();

		//������ʽ����
		StreamSound* CreateStreamSound();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
