/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ConfigManager
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

	//Ĭ��������Ϣ
	ConfigData ConfigManager::mDefConfigData;

	//--------------------------------------------------------------------------------------------------------------
	ConfigManager::ConfigManager()
	{
		//��ʼ��������Ϣ��ջ
		mConfigDataStack.Initialize( 2, 2 );

		//����Ĭ��������Ϣ
		strcpy( mDefConfigData.szConfigName, "Default Config" );

		//��������
		strcpy( mDefConfigData.sWindowCfg.szCaption, "Free Knight Game Engine Default Window" );
		mDefConfigData.sWindowCfg.bCenter = true;
		mDefConfigData.sWindowCfg.nLeft = 0;
		mDefConfigData.sWindowCfg.nTop = 0;
		mDefConfigData.sWindowCfg.nWidth = 800;
		mDefConfigData.sWindowCfg.nHeight = 600;
		mDefConfigData.sWindowCfg.dwStyle = WS_DLGFRAME;

		//����ϵͳ����
		mDefConfigData.sInputSystemCfg.eInputSystemType		= IST_DirectInput8;
#ifdef _DEBUG
		mDefConfigData.sInputSystemCfg.bExclusiveKeyboard	= false;
		mDefConfigData.sInputSystemCfg.bExclusiveMouse		= false;
#else
		mDefConfigData.sInputSystemCfg.bExclusiveKeyboard	= true;
		mDefConfigData.sInputSystemCfg.bExclusiveMouse		= true;
#endif

		//����ϵͳ����
		mDefConfigData.sSoundSystemCfg.eSoundSystemType		= SST_DirectSound8;
		mDefConfigData.sSoundSystemCfg.eSpeakerType			= Speaker_Stereo;

		mDefConfigData.sSoundSystemCfg.dwChannels			= 2;
		mDefConfigData.sSoundSystemCfg.dwFrequency			= 44100;
		mDefConfigData.sSoundSystemCfg.dwBitRate			= 16;

		//��Ⱦϵͳ����
		mDefConfigData.sRenderSystemCfg.eRenderSystemType = RST_Direct3D9;
		mDefConfigData.sRenderSystemCfg.bWindowed = false;

		//Ĭ��ʹ�� D3D9 ��Ⱦϵͳ
		mDefConfigData.sRenderSystemCfg.sD3D9Cfg.nDeviceType			= (int)D3DDEVTYPE_HAL;
		mDefConfigData.sRenderSystemCfg.sD3D9Cfg.nAdapter				= 0;
		mDefConfigData.sRenderSystemCfg.sD3D9Cfg.nWidth					= 1024;
		mDefConfigData.sRenderSystemCfg.sD3D9Cfg.nHeight				= 768;
		mDefConfigData.sRenderSystemCfg.sD3D9Cfg.bVsync					= true;
		mDefConfigData.sRenderSystemCfg.sD3D9Cfg.nNumBackBuffer			= 2;
		mDefConfigData.sRenderSystemCfg.sD3D9Cfg.eColorFormat			= PF_X8R8G8B8;
		mDefConfigData.sRenderSystemCfg.sD3D9Cfg.nRefreshRate			= 60;
		mDefConfigData.sRenderSystemCfg.sD3D9Cfg.nMultiSampleType		= (int)D3DMULTISAMPLE_NONE;
		mDefConfigData.sRenderSystemCfg.sD3D9Cfg.dwMultiSampleQuality	= 0;

		mDefConfigData.sRenderSystemCfg.sD3D9Cfg.nVS_MajorVer	= 0;	//������ɫ�����汾
		mDefConfigData.sRenderSystemCfg.sD3D9Cfg.nVS_MinorVer	= 0;	//������ɫ���ΰ汾
		mDefConfigData.sRenderSystemCfg.sD3D9Cfg.nPS_MajorVer	= 0;	//������ɫ�����汾
		mDefConfigData.sRenderSystemCfg.sD3D9Cfg.nPS_MinorVer	= 0;	//������ɫ���ΰ汾
	}
	//--------------------------------------------------------------------------------------------------------------
	ConfigManager::~ConfigManager()
	{
		//�ͷų�ʼ��������Ϣ��ջ
		mConfigDataStack.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ָ���������ļ�����������������Ϣ
	void ConfigManager::LoadConfigFileData( DataChunk* pConfigFileData )
	{
		//���ö�ȡָ�뵽�ļ�ͷ
		pConfigFileData->SetPosition( 0 );

		//��֤�ļ�ͷ
		char szFileHeader[ sizeof(szConfigFileHeader) ];
		pConfigFileData->Read( szFileHeader, sizeof(szConfigFileHeader) );
		if( 0 != memcmp( szConfigFileHeader, szFileHeader, sizeof(szConfigFileHeader) ) )
			Except( Exception::ERR_INTERNAL_ERROR, "�Ƿ��������ļ����ݡ�" );

		//��ȡ������Ϣ����
		UINT nNumConfig = 0;
		pConfigFileData->Read( &nNumConfig, sizeof(UINT) );

		//��ȡ����������Ϣ
		ConfigData* pConfigData = mConfigDataStack.Push( nNumConfig );
		pConfigFileData->Read( pConfigData, sizeof(ConfigData) * nNumConfig );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����һ��������Ϣ
	void ConfigManager::AddConfig( ConfigData* pConfigData )
	{
		ConfigData* pDst = mConfigDataStack.Push();
		memcpy( pDst, pConfigData, sizeof(ConfigData) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��һ��������Ϣ
	void ConfigManager::DelConfig( UINT nIndex )
	{
		mConfigDataStack.Erase( nIndex );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ������������Ϣ
	void ConfigManager::DelAllConfig()
	{
		mConfigDataStack.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡĬ��������Ϣ
	void ConfigManager::GetDefaultConfig( ConfigData* pConfigData )
	{
		if( pConfigData == NULL )
			Except( Exception::ERR_INVALIDPARAMS, "�����������Ϣָ��Ϊ�գ��޷���ȡĬ��������Ϣ��" );

		memcpy( pConfigData, &mDefConfigData, sizeof(ConfigData) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡָ����������Ϣ
	ConfigData* ConfigManager::GetConfig( UINT nIndex )
	{
		if( nIndex >= mConfigDataStack.Size() )
			return NULL;

		return mConfigDataStack.Begin() + nIndex;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���õ�ǰ������Ϣ
	void ConfigManager::SetCurrenConfig( UINT nIndex )
	{
		if( nIndex >= mConfigDataStack.Size() )
			Except( Exception::ERR_INVALIDPARAMS, "ָ����������Ϣ�����ڡ�" );

		mCurConfigIndex = nIndex;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ǰ������Ϣ
	ConfigData* ConfigManager::GetCurrenConfig()
	{
		return GetConfig( mCurConfigIndex );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
