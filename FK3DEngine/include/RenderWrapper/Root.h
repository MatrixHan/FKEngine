/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Root
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	������������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
class ParticleSystem;
#include "../../include/UISystem/GuiManager.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//������������
	class FK_DLL Root : public Singleton< Root >
	{
	public:
		ConfigManager			mConfigManager;			//���ù�����

		ConfigData*				mpCurConfigData;		//��ǰ��������ָ��

		InputSystem*			mpInputSystem;			//����ϵͳ
		SoundSystem*			mpSoundSystem;			//����ϵͳ
		RenderSystem*			mpRenderSystem;			//��Ⱦϵͳ
		BufferManager*			mpBufferManager;		//���㻺�������
		ShaderManager*			mpShaderManager;		//������ɫ��������
		TextureManager*			mpTextureManager;		//���������
		OverlayManager*			mpOverlayManager;		//ƽ��ͼ�������
		ParticleSystem*			mpParticleSystem;		//����ϵͳ

		SceneManager*			mpSceneManager;			//����������
		PhysicsSystem			mPhysicsSystem;			//����ϵͳ

		GuiManager				mGuiManager;			//�û����������
		FontManager				mFontManager;			//���������
		TextManager				mTextManager;			//���ֹ�����
		MaterialManager			mMaterialManager;		//���ʹ�����
		UVAManager				mUVAManager;			// UV ����������
		SkeletonManager			mSkeletonManager;		//����������
		AnimControlManager		mAnimControlManager;	//����������������
		GeometryManager			mGeometryManager;		//�����������

		ObjectFileLoader		mObjectFileLoader;		//�����ļ�������

		RenderWindow*			mpRenderWindow;			//��Ⱦ����
		FrameListener*			mpFrameListener;		//֡������
		Timer					mFrameTimer;			//֡��ʱ��
		Timer					mFPSTimer;				//֡����ͳ�Ƽ�ʱ��

		UINT					mRenderFrame;			//����Ⱦ֡
		float					mFPS;					//֡����
		float					mTimeSinceLastFrame;	//��һ֡����ǰ֡��ʱ��

	public:
		Root();
		~Root();

		//��ʼ�����棨pConfigFileData Ϊ�����ļ�����ָ�룩
		void Initialize( DataChunk* pConfigFileData = NULL );

		//�ر�����
		void Shutdown();

		//������Ϸ����
		RenderWindow* CreateGameWindow( WindowInfo* pWindowInfo = NULL, WNDPROC fnWndProc = NULL );

		//ʹ���Ѵ��ڴ��ڴ�����Ϸ����
		RenderWindow* CreateGameWindow( HWND hWnd );

		//��������ϵͳ
		InputSystem* CreateInputSystem();

		//��������ϵͳ
		SoundSystem* CreateSoundSystem();

		//������Ⱦϵͳ
		RenderSystem* CreateRenderSystem();

		//��������ϵͳ
		ParticleSystem* CreateParticleSystem( UINT nMaxParticle = 10000 );

		//��������������
		SceneManager* CreateSceneManager( SceneManagerType eType );

		//����֡
		void ProcessFrame();

		//��Ⱦ֡
		void RenderFrame( const float fTimeSinceLastFrame );

		//��ʼ������ѭ��
		void StartLooping();

		//�˳���Ϸ��ѭ��
		void ExitLooping();

		//��Ϸ�����ڲ���Ϣ�������������ڴ���Ĵ�����Ϣ�����е��ã�
		LRESULT WinProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

		//��ȡ��Ϸ����ָ��
		RenderWindow* GetGameWindow();

		//����֡������
		void SetFrameListener( FrameListener* pFrameListener );

		//��������ƶ���ΧΪȫ��Ļ
		void ApplyMouseRectToScreen();

	protected:
		//ͳ��֡����
		void _GetFPS();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
