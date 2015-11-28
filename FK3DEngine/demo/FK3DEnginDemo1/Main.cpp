/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Main
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/CommonBase/CommonBaseInsideHead.h"
#include "../../include/Math/MathInsideHead.h"
#include "../../include/Control/ControlInsideHeader.h"
#include "../../include/PhysiceSystem/PhysicsSystemInsideHeader.h"
#include "../../include/RenderSystem/RenderSystemInsideHeader.h"
#include "../../include/SoundSystem/SoundSystemInsideHeader.h"
#include "../../include/UISystem/UISystemInsideHeader.h"
#include "../../include/ParticleSystem/ParticleSystemInsideHeader.h"
#include "../../include/Scene/SceneInsideHeader.h"
#include "../../include/RenderWrapper/RenderWrapperInsideHeader.h"
#include "../../include/CommonBase/AppEntry.h"
using namespace FK3DEngine;

#ifdef _DEBUG 
	#pragma comment( lib, "FK3DEngine_D.lib ")
	#pragma comment( lib, "JpegLib_D.lib" )
	#pragma comment( lib, "freetype_D.lib" )
#else
	#pragma comment( lib, "FK3DEngine.lib ")
	#pragma comment( lib, "JpegLib.lib" )
	#pragma comment( lib, "freetype.lib" )
#endif


//--------------------------------------------------------------------------------------------------------------
#include "resource.h"
#include "Player.h"
class CTestFrameListener;
//--------------------------------------------------------------------------------------------------------------
Root*					g_pEngRoot				= NULL;		// ���������
RenderWindow*			g_pRenderWindow			= NULL;		// ��Ϸ������
CTestFrameListener*		g_pTestFrameListener	= NULL;		// ֡������
SceneManager*			g_pSceneMgr				= NULL;		// ����������
StaticSound*			g_pSound				= NULL;		// ��������
//--------------------------------------------------------------------------------------------------------------
void PlaySound( LONG_PTR pParam )
{
	GuiCheckBox* pChk = (GuiCheckBox*)pParam;

	if( pChk->mbChecked )
		g_pSound->Play();
	else
		g_pSound->Stop();
}
//--------------------------------------------------------------------------------------------------------------
void SetSoundVolume( LONG_PTR pParam )
{
	GuiTrackBar* pTrackBar = (GuiTrackBar*)pParam;

	float fVolume = (float)pTrackBar->mValue / (float)pTrackBar->mRange;
	g_pSound->SetVolume( fVolume );
}
//--------------------------------------------------------------------------------------------------------------
class CTestFrameListener : public FrameListener
{
public:
	CTestFrameListener()
		: mpTextFPS		(NULL)
		, mpTextTrangle	(NULL)
		, mpCamera		(NULL)
		, mbControlView	(true)
		, mbControlPos	(true)
		, mbFreeLook	(true)
	{

	}
	~CTestFrameListener()
	{

	}
public:
	//֡��ʼ�¼�
	void FrameStart( FrameListenerData* pFrameData )
	{
		//������˳���
		if( InputSystem::mpSingleton->mbKeyDown[DIK_ESCAPE] )
			g_pEngRoot->ExitLooping();

		//�Ƿ�������������
		if( InputSystem::mpSingleton->mbKeyDown[DIK_CAPITAL] )
		{
			mbControlView = !mbControlView;
			mbControlPos = !mbControlPos;
		}

		//�Ƿ�Ϊ���ɹۿ�ģʽ
		if( InputSystem::mpSingleton->mbKeyDown[DIK_NUMLOCK] )
			mbFreeLook = !mbFreeLook;

		//�������״̬
		static Player::Input sInput;
		memset( &sInput, 0, sizeof(Player::Input) );

		if( mbControlPos )
		{
			sInput.bForward =		( InputSystem::mpSingleton->mbKeyState[DIK_UP]		|| InputSystem::mpSingleton->mbKeyState[DIK_W] );
			sInput.bBackward =		( InputSystem::mpSingleton->mbKeyState[DIK_DOWN]	|| InputSystem::mpSingleton->mbKeyState[DIK_S] );
			sInput.bShiftLeft =		( InputSystem::mpSingleton->mbKeyState[DIK_LEFT]	|| InputSystem::mpSingleton->mbKeyState[DIK_A] );
			sInput.bShiftRight =	( InputSystem::mpSingleton->mbKeyState[DIK_RIGHT]	|| InputSystem::mpSingleton->mbKeyState[DIK_D] );

			sInput.bJump =			( InputSystem::mpSingleton->mbKeyState[DIK_SPACE] );
		}

		if( mbControlView )
		{
			sInput.fViewPitch	= InputSystem::mpSingleton->mMouseRelY;
			sInput.fViewYaw		= InputSystem::mpSingleton->mMouseRelX;
		}

		sInput.fFrameTime = pFrameData->fTimeSinceLastFrame;

		mPlayer.UpdatePlayer( sInput, mbFreeLook ? Player::FreeLook : Player::Walk );

		//���������
		if( mpCamera != NULL )
			mPlayer.UpdateCamera( mpCamera );

		//����֡���ʺ�����������ʾ����
		static wchar_t szFPS[32] = { NULL };
		NumConvert::FloatToUnicode( g_pEngRoot->mFPS, szFPS, 2 );

		static wchar_t szTri[32] = { NULL };
		NumConvert::IntToUnicode( RenderSystem::mNumTriangle, szTri );

		//mpTextFPS->SetText( szFPS );
		//mpTextTrangle->SetText( szTri );

		//����֡�¼�
		ProcFrameEvent();
	}

	//֡����ʱ��
	void FrameEnd( FrameListenerData* pFrameData )
	{

	}

	//���������
	void SetCamera( Camera* pCamera )
	{
		mpCamera = pCamera;
	}
public:
	TextSurface*	mpTextFPS;		//֡������ʾ����
	TextSurface*	mpTextTrangle;	//����������ʾ����

	Camera*			mpCamera;		//�����
	Player			mPlayer;		//���

	bool			mbControlView;	//�Ƿ�ɿ�������ӽ�
	bool			mbControlPos;	//�Ƿ�ɿ������λ��
	bool			mbFreeLook;		//�Ƿ�Ϊ���ɹۿ�ģʽ
};
//--------------------------------------------------------------------------------------------------------------
//��������Ϣ
LRESULT WINAPI DemoProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if( g_pEngRoot == NULL )
		return 0;

	// ��һ����Ϣ����ʽ
	//switch( msg )
	//{
	//case WM_KEYDOWN:
	//	{
	//		Misc::ShowErrMsg( "��Windows������Ϣ��" );
	//		return 0;
	//	}
	//}

	return g_pEngRoot->WinProc( hWnd, msg, wParam, lParam );
}
//--------------------------------------------------------------------------------------------------------------
int WinMainEntry()
{
	BaseFile sTextureFile;			// �����
	BaseFile sObjectFile;			// ��������
	BaseFile sOverlayFile;			// ����
	BaseFile sUVAFile;				// UV������
	BaseFile sFontFile;				// �����
	BaseFile sShaderFile;			// Shader��
	FKTry
	{
		// ��������
		g_pEngRoot = new Root;

		// �޸�����
		ConfigData sConfigData;
		ConfigManager::GetSingletonPtr()->GetDefaultConfig( &sConfigData );
		sConfigData.sWindowCfg.dwStyle	= WS_OVERLAPPEDWINDOW;
		ConfigManager::GetSingletonPtr()->AddConfig( &sConfigData );
		ConfigManager::GetSingletonPtr()->SetCurrenConfig( 0 );

		// ��ʼ������
		g_pEngRoot->Initialize();

		// ������Ϸ����
		WindowInfo sWndInfo;
		sWndInfo.sCaption		= "FK3D������� �� Demo1";
		sWndInfo.bCenter		= true;
		sWndInfo.nLeft			= 0;
		sWndInfo.nTop			= 0;
		sWndInfo.nWidth			= 800;
		sWndInfo.nHeight		= 600;
		sWndInfo.dwStyle		= WS_OVERLAPPEDWINDOW | WS_POPUP | WS_SYSMENU;
		sWndInfo.fnWndProc		= DemoProc;
		sWndInfo.hIcon			= LoadIcon( GetModuleHandle( NULL ), MAKEINTRESOURCE(IDI_ICON1) );
		sWndInfo.hCursor		= NULL;//LoadCursor( NULL, IDC_ARROW );

		// ������Ⱦ����
		g_pRenderWindow	= g_pEngRoot->CreateGameWindow( &sWndInfo );

		if( g_pRenderWindow == NULL )
		{
			Misc::ShowErrMsg( "������Ⱦ����ʧ�ܣ�" );
			SafeDelete( g_pEngRoot );
			return 0;
		}

		g_pEngRoot->CreateInputSystem();		//��������ϵͳ
		g_pEngRoot->CreateSoundSystem();		//��������ϵͳ
		g_pEngRoot->CreateRenderSystem();		//������Ⱦϵͳ
		g_pEngRoot->CreateParticleSystem();		//��������ϵͳ

		// ���������
		TextureManager::GetSingletonPtr()->SetTexturePack( &sTextureFile );
		ObjectFileLoader::GetSingletonPtr()->SetObjectPackFile( &sObjectFile );
		OverlayManager::GetSingletonPtr()->SetOverlayPack( &sOverlayFile );
		UVAManager::GetSingletonPtr()->SetUVAPackFile( &sUVAFile );
		FontManager::GetSingletonPtr()->SetFontPack( &sFontFile );
		
		// ���ű�������
		BaseFile		mp3File;
		MP3Decoder		mp3Decoder;
		mp3Decoder.OpenSoundFile( &mp3File, "rc\\BackGroundMusic.mp3" );
	
		g_pSound = SoundSystem::mpSingleton->CreateStaticSound();
		g_pSound->LoadStaticSound( &mp3Decoder );
		g_pSound->Play();

		// ��������������
		g_pSceneMgr = g_pEngRoot->CreateSceneManager( SMT_Quadtree );
		// �����������ڵ�
		SceneNode* pRootNode = g_pSceneMgr->CreateSceneRootNode();

		// ��������
		BaseFile		mapFile;
		mapFile.Open( "rc\\Quadtree.map", OT_Read );
		((QuadSceneManager*)g_pSceneMgr)->LoadFromFile( &mapFile );
		mapFile.Close();

		// ���������
		Texture* pSkyTex = TextureManager::mpSingleton->LoadFromFile( "rc\\Sphere.tga" );
		SkySphere* pSkySphere = g_pSceneMgr->CreateSkySphere();
		pSkySphere->SetSphereTexture( pSkyTex );
		pSkySphere->SetSurfaceRotation( 0.8f, Vector3( 0.0f, 1.0f, 0.0f ) );

		////���붥����ɫ��
		//ShaderManager::GetSingletonPtr()->SetProgramPackFile( &sShaderFile );
		//ShaderManager::GetSingletonPtr()->CreateShaderFromFile( "rc\\Shader.scg" );

		//VertexShader* pVS = ShaderManager::GetSingletonPtr()->GetVertexShader( 0 );
		//pVS->SetTransformMatrixParam( 0 );
		//pVS->SetShdaerDiffuseParam( 1 );

		// ���������
		Camera* pCamera = g_pSceneMgr->CreateCamera();
		if( pCamera != NULL )
		{
			pCamera->SetViewPos( Vector3( 0.0f, 0.0f, -30.0f ) );
		}

		// ���������ӽڵ�
		SceneNode* pNode = (SceneNode*)pRootNode->CreateChild();
		// �����ƹ�
		Light* pLight1 = g_pSceneMgr->CreateLight();
		// �󶨵ƹ����ӽڵ���
		pNode->AttachLight( pLight1 );
		// ���õƹ�����
		pLight1->mLightType = LT_DIRECTIONAL;
		pLight1->mDiffuse = ColorValue( 1.0f, 0.91f, 0.83f, 0.76f );
		pLight1->mSpecular = ColorValue( 1.0f, 0.95f, 0.81f, 0.67f );
		pLight1->mAmbient = ColorValue( 1.0f, 0.52f, 0.458f, 0.38f );
		pLight1->mDirection = Vector3( -1.0f, -1.0f, 1.0f );
		// ����ƹ�
		pLight1->ActiveLight();
		pLight1->EnableLight();

		// ����֡������
		g_pTestFrameListener = new CTestFrameListener;

		g_pTestFrameListener->SetCamera( pCamera );
		// ����֡������
		g_pEngRoot->SetFrameListener( (FrameListener*)g_pTestFrameListener );

		// �����ӿ�
		Viewport* pViewport = RenderSystem::mpSingleton->CreateViewport( 0, 0,
			RenderSystem::mRenderWidth, RenderSystem::mRenderHeight );
		pViewport->SetCamera( pCamera );

		//��������
		TriMeshList::Iterator tit = ObjectFileLoader::mpSingleton->mLoadedTriMeshList.Begin();
		TriMeshList::Iterator tend = ObjectFileLoader::mpSingleton->mLoadedTriMeshList.End();
		for(; tit!=tend; ++tit )
		{
			TriMesh* pMesh = *tit;
			pMesh->InitializeInstanceList( 100, 100 );
			RenderInstance* pInstance = pMesh->CreateInstance();

			if( ObjectFileLoader::mpSingleton->mLoadedSkeletonList.Size() != 0 )
			{
				Skeleton* pSkeleton = ObjectFileLoader::mpSingleton->mLoadedSkeletonList[0];

				pMesh->SetSkeleton( pSkeleton );

				AnimControl* pAnimControl = AnimControlManager::mpSingleton->CreateAnimControl();
				pAnimControl->SetAnimationInfo( pSkeleton->mNumKey, pSkeleton->mIntervalTime );
				pInstance->mpAnimControl = pAnimControl;
			}

			SceneNode* pSubNode = (SceneNode*)pNode->CreateChild();
			pSubNode->AttachRenderInstance( pInstance );
		}

		// ���ò���
		Material* pBumpMat = MaterialManager::mpSingleton->CreateMaterial( "JianDunMaterial" );
		pBumpMat->mAmbient = ColorValue::Black;
		pBumpMat->mDiffuse = ColorValue::Black;
		pBumpMat->mSpecular = ColorValue::Black;
		pBumpMat->mEmissive = ColorValue::Black;

		Texture* pBaseTex = TextureManager::mpSingleton->LoadFromFile( "rc\\jiandun.tga" );
		TextureState* pBaseTexState = pBumpMat->CreateTextureState( 0 );
		pBaseTexState->SetTexture( pBaseTex );

		TriMesh* pMesh = (TriMesh*)GeometryManager::mpSingleton->CreateGeometry( TriMesh::Creator );

		pMesh->InitializeInstanceList( 1, 1 );
		RenderInstance* pInst = pMesh->CreateInstance();

		pNode->AttachRenderInstance( pInst );

		// ��������
		Material* pParticleMat = MaterialManager::GetSingletonPtr()->CreateMaterial( "rc\\IceBall.tga", Transparent );
		MissileParticle::Param sParticleParam;
		sParticleParam.pMaterial		= pParticleMat;
		sParticleParam.fLife			= 4.0f;
		sParticleParam.nBeginAlpha		= 0xFF;
		sParticleParam.nEndAlpha		= 0x0;
		sParticleParam.fBeginSize		= 0.8f;
		sParticleParam.fEndSize			= 3.0f;
		Particle* pParticle = FK3DEngine::ParticleSystem::GetSingletonPtr()->CreateParticle( MissileParticle::Creator, &sParticleParam );\

		// �������ӷ�����
		MissileEmitter::Param sEmitterParam;
		sEmitterParam.pParticle			= pParticle;
		sEmitterParam.fEmitRate			= 0.3f;
		// �����ӱ༭��
		Emitter* pEmitter = FK3DEngine::ParticleSystem::GetSingletonPtr()->CreateEmitter( MissileEmitter::Creator, &sEmitterParam );
		pNode->AttachRenderInstance( pEmitter );

		// ������UI���
		OverlayManager* pOverMgr = g_pEngRoot->mpOverlayManager;
		pOverMgr->SetRenderPlaneSize( RenderSystem::mRenderWidth, RenderSystem::mRenderHeight );

		JointSurface* pBK = pOverMgr->LoadJointSurfaceFromFile( 820.0f, 666.0f, 200.0f, 100.0f, ZOT_Bottom, NULL,
			"rc\\bkg.jpg", PF_A8R8G8B8, TFT_POINT );

		// ����2D UVͼƬ
		UV4 sUV = { 0.0f, 1.0f, 0.0f, 1.0f };
		// ��ȡDDS�ļ�
		SpriteSet* pImgSpriteSet = pOverMgr->LoadSpriteSetFromFile( "rc\\water.dds", PF_DXT1, 10, 10 );
		pImgSpriteSet->CreateSprite( 0.0f, RenderSystem::mRenderHeight - 250.0f, 128.0f, 128.0f, ZOT_Top, NULL, &sUV );

		// ���� UVA ����
		UVAnimation* pCursorUVA = UVAManager::GetSingletonPtr()->CreateUVAnimation( "rc\\cursor.uva" );
		SpriteSet* pCursorSpriteSet = pOverMgr->LoadSpriteSetFromFile( "rc\\cursor.tga", PF_A8R8G8B8, 1, 1, TFT_POINT );
		// �������
		GuiManager::GetSingletonPtr()->CreateCursor( 32, 32, 3, 3, pCursorSpriteSet, pCursorUVA );

		// �����������
		FontFace* pFont = FontManager::GetSingletonPtr()->CreateFontFace( "rc\\NGULIM.TTF", 32, 512, 32, 32);

		// ����������ʾ����
		OverlaySurface* pCursorOverlay = GuiManager::mpSingleton->mpCursorGui->GetZOrder( ZOT_Bottom );
		TextManager::GetSingletonPtr()->CreateTextSurface( ZOT_Top, pCursorOverlay, pFont, L"FK3DEngine_Demo", 10, 10, 0, 0, 0xFF7FFF7F, TFT_LINEAR );

		TextSurface* pAGPMemText = TextManager::GetSingletonPtr()->CreateTextSurface( ZOT_Top, pCursorOverlay,
			pFont, L"0", 100, 54, 600, 32, 0xffff0000 );

		// ��ȡ�����Դ�
		UINT nAGPMem = RenderSystem::mpSingleton->GetAvailableTextureMem() >> 20;
		wchar_t szAGPMem[10] = { NULL };
		NumConvert::IntToUnicode( nAGPMem, szAGPMem );
		pAGPMemText->SetText( szAGPMem );

		// �����Ի���
		GuiLoca sDlgLoca = { 0, 0, RenderSystem::mRenderWidth, RenderSystem::mRenderHeight };
		GuiClient sDlgClient( 0, 0, RenderSystem::mRenderWidth, RenderSystem::mRenderHeight );
		GuiDialog* pDialog = GuiManager::GetSingletonPtr()->CreateDialog( ZOT_Top, NULL, &sDlgLoca, &sDlgClient );
		// ������Ͽ�
		FontFace* pComboFont = FontManager::GetSingletonPtr()->CreateFontFace( "rc\\NGULIM.TTF", 16, 512, 16, 16 );
		SpriteSet* pComboSpriteSet = pOverMgr->LoadSpriteSetFromFile( "rc\\ComboBox.tga", PF_A8R8G8B8, 1, 1, TFT_POINT );
		GuiComboBox::Param sParam1;
		sParam1.pSpriteSet		= pComboSpriteSet;
		sParam1.pFontFace		= pComboFont;
		sParam1.nItemNum		= 10;
		sParam1.nX				= 10;
		sParam1.nY				= 300;
		sParam1.nWidth			= 140;
		sParam1.nChoosenHeight	= 24;
		sParam1.nTextLeft		= 1;
		sParam1.nTextTop		= 1;
		sParam1.nBoarderHeight	= 3;
		sParam1.nItemHeight		= 18;
		sParam1.sChoosenClient.SetClient( 3, 3, 137, 21 );

		GuiComboBox* pCombo = pDialog->CreateComboBox( &sParam1 );
		pCombo->AddItem( L"Free", 0 );
		pCombo->AddItem( L"Knight", 1 );
		pCombo->AddItem( L"Katelinda", 2 );

		// ����������
		SpriteSet* pSliderSpriteSet = pOverMgr->LoadSpriteSetFromFile( "rc\\TrackBar.tga", PF_A8R8G8B8, 1, 1, TFT_POINT );

		GuiTrackBar::Param sParam2;
		sParam2.pSpriteSet		= pSliderSpriteSet;
		sParam2.nRange			= 100;
		sParam2.nValue			= 100;
		sParam2.nX				= 150;
		sParam2.nY				= 400;
		sParam2.nBkgY			= 7;
		sParam2.nBkgWidth		= 206;
		sParam2.nBkgHeight		= 14;
		sParam2.nProgLeft		= 12;
		sParam2.nProgTop		= 3;
		sParam2.nProgWidth		= 182;
		sParam2.nProgHeight		= 8;
		sParam2.nSliderY		= 0;
		sParam2.nSliderMinX		= 6;
		sParam2.nSliderMaxX		= 188;
		sParam2.nSliderWidth	= 12;
		sParam2.nSliderHeight	= 28;
		sParam2.fnEvent			= SetSoundVolume;	// �����������ص�����

		GuiTrackBar* pTrackBar = pDialog->CreateTrackBar( &sParam2 );

		// ������ѡ��
		SpriteSet* pCheckSpriteSet = pOverMgr->LoadSpriteSetFromFile( "rc\\CheckBox.tga", PF_A8R8G8B8, 1, 1, TFT_POINT );
		
		GuiCheckBox::Param sParam3;
		sParam3.pSpriteSet = pCheckSpriteSet;
		sParam3.sClient.SetClient( 0.0f, 0.0f, 25, 25 );
		sParam3.sLoca.X = 190;
		sParam3.sLoca.Y = 450;
		sParam3.sLoca.Width = 25;
		sParam3.sLoca.Height = 25;
		sParam3.fnEvent = PlaySound;				// ������ѡ��ص�����
		pDialog->CreateCheckBox( &sParam3 );

		// ��ʾ���
		g_pRenderWindow->ShowCursor( true );
		// ��������ƶ���Χ
		g_pEngRoot->ApplyMouseRectToScreen();

		// ������������
		g_pTestFrameListener->mPlayer.SetPlayerPos( Vector3( 0.0f, 0.0f, -30.0f ) );
		//�������ģ�ͼ�����
		g_pTestFrameListener->mPlayer.LoadPlayerModel( "" );

		// ��ʾ��Ϸ����
		g_pRenderWindow->ShowGameWindow();

		// ������Ⱦ״̬
		RenderSystem::GetSingletonPtr()->_SetAmbient( ColorValue::Yellow );

		//��ʼ��Ϸ��ѭ��
		g_pEngRoot->StartLooping();

		// ɾ�������
		g_pSceneMgr->DeleteCamera( pCamera );

		// �ͷ�����
		g_pEngRoot->Shutdown();

	}
	FKCatch
	{
		SafeDelete( g_pTestFrameListener );
		SafeDelete( g_pEngRoot );
		ShowExceptionMsg;
	}
#ifndef _DEBUG
	{
		SafeDelete( g_pTestFrameListener );
		SafeDelete( g_pEngRoot );
		ShowUnknownExceptionMsg;
	}
#endif

	SafeDelete( g_pTestFrameListener );
	SafeDelete( g_pEngRoot );
	return 0;
}