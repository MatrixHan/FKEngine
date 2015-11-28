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
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderWrapper/RenderWrapperInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	Root::Root()
		: mpCurConfigData		(NULL)
		, mpRenderWindow		(NULL)
		, mpInputSystem			(NULL)
		, mpSoundSystem			(NULL)
		, mpRenderSystem		(NULL)
		, mpBufferManager		(NULL)
		, mpShaderManager		(NULL)
		, mpTextureManager		(NULL)
		, mpOverlayManager		(NULL)
		, mpParticleSystem		(NULL)
		, mpSceneManager		(NULL)
		, mpFrameListener		(NULL)
		, mRenderFrame			(0)
		, mFPS					(0.0f)
		, mTimeSinceLastFrame	(0.0f)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	Root::~Root()
	{
		Shutdown();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ������
	void Root::Initialize( DataChunk* pConfigFileData )
	{
		//��ȡ CPU ��Ϣ
		const CPUInfo* pCPUInfo = ProcessorInfo::GetCPUInfo();

		//��ʼ����ѧ��
		InitializeMathLibrary( pCPUInfo );

		//������������ļ�����ָ��
		if( pConfigFileData != NULL )
		{
			mConfigManager.LoadConfigFileData( pConfigFileData );
		}
		else
		{
			mConfigManager.AddConfig( &ConfigManager::mDefConfigData );
		}

		//��ȡ��ǰ��������ָ��
		mConfigManager.SetCurrenConfig( 0 );
		mpCurConfigData = mConfigManager.GetCurrenConfig();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ر�����
	void Root::Shutdown()
	{
		SafeDelete( mpSceneManager );
		SafeDelete( mpParticleSystem );

		mGuiManager.DeleteAllDialog();
		mGuiManager.DeleteCursor();
		mFontManager.DeleteAllFont();
		mTextManager.DeleteAllTextSurface();
		mSkeletonManager.DeleteAllSkeleton();
		mAnimControlManager.DeleteAllAnimControl();
		mGeometryManager.DeleteAllGeometry();
		mMaterialManager.DeleteAllMaterial();

		mPhysicsSystem.DeleteAllRigidBody();
		mPhysicsSystem.DeleteAllBoundVolume();

		SafeDelete( mpOverlayManager );
		SafeDelete( mpTextureManager );
		SafeDelete( mpShaderManager );
		SafeDelete( mpBufferManager );

		SafeDelete( mpRenderSystem );
		SafeDelete( mpSoundSystem );
		SafeDelete( mpInputSystem );

		SafeDelete( mpRenderWindow );
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ϸ����
	RenderWindow* Root::CreateGameWindow( WindowInfo* pWindowInfo, WNDPROC fnWndProc )
	{
		mpRenderWindow = new RenderWindow;

		//������ڴ��ڴ�������
		if( pWindowInfo != NULL )
		{
			mpRenderWindow->Create( pWindowInfo );
			return mpRenderWindow;
		}

		//����ʹ��������Ϣ��������
		WindowInfo WndInfo;
		WndInfo.sCaption	= mpCurConfigData->sWindowCfg.szCaption;
		WndInfo.bCenter		= mpCurConfigData->sWindowCfg.bCenter;
		WndInfo.nLeft		= mpCurConfigData->sWindowCfg.nLeft;
		WndInfo.nTop		= mpCurConfigData->sWindowCfg.nTop;
		WndInfo.nWidth		= mpCurConfigData->sWindowCfg.nWidth;
		WndInfo.nHeight		= mpCurConfigData->sWindowCfg.nHeight;
		WndInfo.dwStyle		= mpCurConfigData->sWindowCfg.dwStyle;
		WndInfo.fnWndProc	= fnWndProc;
		WndInfo.hIcon		= LoadIcon( NULL, IDI_WINLOGO );
		WndInfo.hCursor		= LoadCursor( NULL, IDC_ARROW );

		mpRenderWindow->Create( &WndInfo );

		return mpRenderWindow;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ʹ���Ѵ��ڴ��ڴ�����Ϸ����
	RenderWindow* Root::CreateGameWindow( HWND hWnd )
	{
		if( hWnd == NULL )
			return NULL;

		mpRenderWindow = new RenderWindow;
		mpRenderWindow->CreateByExist( hWnd );
		return mpRenderWindow;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ϵͳ
	InputSystem* Root::CreateInputSystem()
	{
		//��������ϵͳ�������ʹ�������ϵͳ
		switch ( mpCurConfigData->sInputSystemCfg.eInputSystemType )
		{
		case IST_DirectInput8:
			{
				mpInputSystem = new DI8InputSystem;
				break;
			}
		default:
			Except( Exception::ERR_INTERNAL_ERROR, "�޷�ʶ�������ϵͳ���͡�" );
		}

		//��ʼ������ϵͳ
		mpInputSystem->Initialize();

		//��ʼ�����̺����
		mpInputSystem->InitializeKeyboard( mpRenderWindow->mhWnd, mpCurConfigData->sInputSystemCfg.bExclusiveKeyboard );
		mpInputSystem->InitializeMouse( mpRenderWindow->mhWnd, mpCurConfigData->sInputSystemCfg.bExclusiveMouse );

		return mpInputSystem;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ϵͳ
	SoundSystem* Root::CreateSoundSystem()
	{
		//��������ϵͳ�������ʹ�������ϵͳ
		switch ( mpCurConfigData->sSoundSystemCfg.eSoundSystemType )
		{
		case SST_DirectSound8:
			{
				mpSoundSystem = new DS8SoundSystem;
				break;
			}
		default:
			Except( Exception::ERR_INTERNAL_ERROR, "�޷�ʶ�������ϵͳ���͡�" );
		}

		mpSoundSystem->Initialize( &mpCurConfigData->sSoundSystemCfg, mpRenderWindow );

		return mpSoundSystem;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ⱦϵͳ
	RenderSystem* Root::CreateRenderSystem()
	{
		//������Ⱦϵͳ�������ʹ�����Ⱦϵͳ
		switch ( mpCurConfigData->sRenderSystemCfg.eRenderSystemType )
		{
		case RST_Direct3D9:
			{
				mpRenderSystem = new D3D9RenderSystem;
				if( !mpRenderSystem->Initialize( mpRenderWindow, &mpCurConfigData->sRenderSystemCfg ) )
					return NULL;

				mpBufferManager		= new D3D9BufferManager;
				mpShaderManager		= new D3D9ShaderManager;
				mpTextureManager	= new D3D9TextureManager;
				break;
			}
		case RST_OpenGL:
			{
				break;
			}
		default:
			Except( Exception::ERR_INTERNAL_ERROR, "�޷�ʶ�����Ⱦϵͳ���͡�" );
		}

		//��ʼ�����ֹ�����
		mpOverlayManager = new OverlayManager;

		mpBufferManager->Initialize();
		mpOverlayManager->Initialize();

		mMaterialManager.Initialize( 100 );
		mGeometryManager.Initialize( 200, 200 );

		return mpRenderSystem;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ϵͳ
	ParticleSystem* Root::CreateParticleSystem( UINT nMaxParticle )
	{
		mpParticleSystem = new ParticleSystem( nMaxParticle );
		return mpParticleSystem;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������������
	SceneManager* Root::CreateSceneManager( SceneManagerType eType )
	{
		//���ݳ������������ʹ�������������
		switch (eType)
		{
		case SMT_Basic:
			{
				mpSceneManager = new SceneManager;
				break;
			}
		case SMT_BSP:
			{
				mpSceneManager = new BSPSceneManager;
				break;
			}
		case SMT_Quadtree:
			{
				mpSceneManager = new QuadSceneManager;
				break;
			}
		case SMT_Octree:
			{
				mpSceneManager = new OctSceneManager;
				break;
			}
		default:
			Except( Exception::ERR_INVALIDPARAMS, "�޷�ʶ��ĳ������������͡�" );
		}

		return mpSceneManager;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����֡
	void Root::ProcessFrame()
	{
		//��ȡ������Ϣ
		mpInputSystem->UpdateKeyboard();
		mpInputSystem->UpdateMouse();


		//���¿�ʼ��ʱ
		float fTimeSinceLastFrame = mFrameTimer.GetTimeDouble();
		mFrameTimer.Start();

		//����֡��ʼ�¼�
		static FrameListenerData sFrameData;
		sFrameData.fTimeSinceLastFrame = fTimeSinceLastFrame;
		mpFrameListener->FrameStart( &sFrameData );

		//�����û���������
		mGuiManager.ProcGuiInput( mpInputSystem, fTimeSinceLastFrame );

		//��Ⱦ֡
		RenderFrame( fTimeSinceLastFrame );

		//����֡�����¼�
		mpFrameListener->FrameEnd( &sFrameData );


		//ͳ��֡����
		_GetFPS();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ֡
	void Root::RenderFrame( const float fTimeSinceLastFrame )
	{
		mTimeSinceLastFrame = fTimeSinceLastFrame;

		RenderSystem::mNumTriangle = 0;

		//���¶���֡��ʱ
		mAnimControlManager.UpdateFrameTime( fTimeSinceLastFrame );
		mpOverlayManager->_UpdateFrameTime( fTimeSinceLastFrame );

		//��Ⱦ����
		mpSceneManager->RenderScene( fTimeSinceLastFrame );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ������ѭ��
	void Root::StartLooping()
	{
		//��ʼ����֡��ʱ
		mFrameTimer.Start();
		mFPSTimer.Start();

		//������Ϸ��ѭ��

		//��������˳���Ϣ
		while( mpRenderWindow->mMsg.message != WM_QUIT )
		{
			//�������Ϣ
			if( PeekMessage( &mpRenderWindow->mMsg, NULL, 0, 0, PM_REMOVE ) )
			{
				//������Ϣ
				TranslateMessage( &mpRenderWindow->mMsg );
				DispatchMessage( &mpRenderWindow->mMsg );
			}
			//���û����Ϣ
			else
			{
				//������ڴ��ڼ���״̬
				if( mpRenderWindow->mbActive )
				{
					//������Ϸ֡
					ProcessFrame();
				}
				//������ڱ�����
				else if( mpRenderWindow->mbDestroy )
				{
					return;
				}
				//����Ϣ�Ҳ�����ʱ��ȴ���Ϣ��������Ȩ��������ϵͳ��
				else
				{
					WaitMessage();
				}
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�˳���Ϸ��ѭ��
	void Root::ExitLooping()
	{
		PostQuitMessage( 0 );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ϸ�����ڲ���Ϣ�������������ڴ���Ĵ�����Ϣ�����е��ã�
	LRESULT Root::WinProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		return mpRenderWindow->WinProc( hWnd, msg, wParam, lParam );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��Ϸ����ָ��
	RenderWindow* Root::GetGameWindow()
	{
		return mpRenderWindow;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����֡������
	void Root::SetFrameListener( FrameListener* pFrameListener )
	{
		mpFrameListener = pFrameListener;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ƶ���ΧΪȫ��Ļ
	void Root::ApplyMouseRectToScreen()
	{
		MouseRect sMouseRect;
		sMouseRect.Left		= 0;
		sMouseRect.Right	= mpRenderSystem->mRenderWidth;
		sMouseRect.Top		= 0;
		sMouseRect.Bottom	= mpRenderSystem->mRenderHeight;
		sMouseRect.WheelMin	= -180;
		sMouseRect.WheelMax	= 180;

		mpInputSystem->SetMouseRect( &sMouseRect );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ͳ��֡����
	void Root::_GetFPS()
	{
		//��������Ⱦ֡��¼ֵ
		++mRenderFrame;

		//��ȡ����һ��ͳ��֡���ʵ����ڵ���ʱ
		double DelayTime = mFPSTimer.GetTimeDouble();

		//ÿ�� 0.25 ���Ӽ��һ�Σ�ע�⣺����ʱ�������Ƶ��Խ�ߣ����Խ�󡣣�
		if( DelayTime > 0.25 )
		{
			//����Ⱦ��֡��������Ⱦʱ��ó�֡/��
			mFPS = (float)( (double)mRenderFrame / DelayTime );

			mFPSTimer.Start();	//���¿�ʼ��ʱ
			mRenderFrame = 0;	//����֡����
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
