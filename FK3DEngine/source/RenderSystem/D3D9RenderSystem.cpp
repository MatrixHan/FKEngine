/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9RenderSystem
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderSystem/RenderSystemInsideHeader.h"
#include "../../../Depend/dx9/d3dx9.h"
#include "../../../Depend/dx9/dxerr9.h"
#include "../../include/CommonBase/MemoryMarco.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	IDirect3D9*				D3D9RenderSystem::mpD3D9			= NULL;				// D3D9 ������
	D3DCAPS9				D3D9RenderSystem::mD3D9CurCaps;							// D3D9 Ӳ��֧��������Ϣ
	D3DCAPS9				D3D9RenderSystem::mD3D9HardCaps;						// D3D9 ��ǰģʽ������Ϣ
	IDirect3DDevice9*		D3D9RenderSystem::mpD3D9Device		= NULL;				// D3D9 �豸
	D3DDEVTYPE				D3D9RenderSystem::mDeviceType		= D3DDEVTYPE_HAL;	// D3D9 �豸����
	DWORD					D3D9RenderSystem::mD3DBehavior		= 0;				// D3D9 �豸���㴦��ʽ
	D3DPRESENT_PARAMETERS	D3D9RenderSystem::mD3Dpp			= { NULL };			// D3D9 �豸��Ϣ
	//--------------------------------------------------------------------------------------------------------------
	D3D9RenderSystem::D3D9RenderSystem()
		: RenderSystem	( RST_Direct3D9 )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	D3D9RenderSystem::~D3D9RenderSystem()
	{
		Shutdown();
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ⱦϵͳ
	bool D3D9RenderSystem::Initialize( RenderWindow* pRenderWindow, RenderSystemCfg* pRenderSystemCfg )
	{
		HRESULT result = E_FAIL;

		//�洢��Ⱦϵͳ������Ϣָ��
		mpConfig = pRenderSystemCfg;

		//�洢��Ⱦ����ָ��
		mpRenderWindow = pRenderWindow;

		//�洢ʹ�õ����������
		mnAdpter = mpConfig->sD3D9Cfg.nAdapter;

		//�洢��Ⱦ�����ߴ�
		mRenderWidth	= mpConfig->sD3D9Cfg.nWidth;
		mRenderHeight	= mpConfig->sD3D9Cfg.nHeight;

		//������D3D����
		mpD3D9 = Direct3DCreate9( D3D_SDK_VERSION );
		if( mpD3D9 == NULL )
			Except( Exception::ERR_RENDER_API_ERROR, "���� D3D9 ������ʧ�ܡ�" );

		//�����豸��Ϣ
		_SetD3DPresentParam();

		//��ȡ D3D9 Ӳ��֧��������Ϣ
		result = mpD3D9->GetDeviceCaps( mpConfig->sD3D9Cfg.nAdapter, D3DDEVTYPE_HAL, &mD3D9HardCaps );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"�޷���ȡ�Կ�������Ϣ��"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );


		//�ж��Ƿ�֧�� W ��Ȼ���
		mdwDepthMode = ( mD3D9HardCaps.RasterCaps & D3DPRASTERCAPS_WBUFFER ) ? D3DZB_USEW : D3DZB_TRUE;

		//����Ƿ����ʹ��������㴦��
		bool bMustUseSoftVertexProc = false;

		//�ж��Ƿ�֧��ָ������ɫ��
		DWORD dwVerVS = D3DVS_VERSION( mpConfig->sD3D9Cfg.nVS_MajorVer, mpConfig->sD3D9Cfg.nVS_MinorVer );
		DWORD dwVerPS = D3DPS_VERSION( mpConfig->sD3D9Cfg.nPS_MajorVer, mpConfig->sD3D9Cfg.nPS_MinorVer );
		if( dwVerVS > mD3D9HardCaps.VertexShaderVersion || dwVerPS > mD3D9HardCaps.PixelShaderVersion )
			bMustUseSoftVertexProc = true;

		//Ӳ��֧�ֶ�����������þ�������������������ֵ����
		mdwMaxBlendNum = mD3D9HardCaps.MaxVertexBlendMatrices;
		mdwMaxBlendIndex = mD3D9HardCaps.MaxVertexBlendMatrixIndex;
		if( mdwMaxBlendIndex < 32 || mdwMaxBlendNum < 4 )
		{
			bMustUseSoftVertexProc = true;
			mbSoftVerProc = true;
		}

		mD3DBehavior = bMustUseSoftVertexProc ? D3DCREATE_MIXED_VERTEXPROCESSING : D3DCREATE_HARDWARE_VERTEXPROCESSING;


		//���Ҫ�����Ϊ֧�� NVPerfHUD �����ܵ��԰汾
#ifdef _NVPerfHUD

		//Ҫ���� NVPerfHUD �����ܵ��Թ��ܣ���ȷ�������� NVPerfHUD ���������еı�����
		//���ҵ�ǰʹ�õ��Կ��ͺ�Ϊ NVIDIA Geforce3 �������ϵ�У�ͬʱ��װ�� ForceWare 71.80 �����ϰ汾����������

		//����֧�� NVPerfHUD �� Direct3D �豸
		mpConfig->sD3D9Cfg.nAdapter = mpD3D9->GetAdapterCount() - 1;
		mDeviceType = D3DDEVTYPE_REF;

		result = mpD3D9->CreateDevice( mpConfig->sD3D9Cfg.nAdapter, mDeviceType, mpRenderWindow->mhWnd, 
			mD3DBehavior, &mD3Dpp, &mpD3D9Device );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"����֧�� NVIDIA NVPerfHUD ���ܵ�����"
			"�� Direct3D9 ��ʾ�豸ʧ�ܡ�\nD3D9 ����������" + DXGetErrorDescription9( result ) );

#else

		//���� Direct3D �豸
		mDeviceType = D3DDEVTYPE_HAL;
		result = mpD3D9->CreateDevice( mpConfig->sD3D9Cfg.nAdapter, mDeviceType, mpRenderWindow->mhWnd, 
			mD3DBehavior, &mD3Dpp, &mpD3D9Device );
		if( FAILED( result ) )
		{
			//�������ʧ������ʹ��������㴦��
			mD3DBehavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
			result = mpD3D9->CreateDevice( mpConfig->sD3D9Cfg.nAdapter, mDeviceType, mpRenderWindow->mhWnd, 
				mD3DBehavior, &mD3Dpp, &mpD3D9Device );
			if( FAILED( result ) )
			{
				//�������ʧ������ʹ����� 3D ����
				mDeviceType = D3DDEVTYPE_REF;
				result = mpD3D9->CreateDevice( mpConfig->sD3D9Cfg.nAdapter, mDeviceType, mpRenderWindow->mhWnd, 
					mD3DBehavior, &mD3Dpp, &mpD3D9Device );
				if( FAILED( result ) )
				{
					Except( Exception::ERR_RENDER_API_ERROR,
						(String)"���� Direct3D9 ��ʾ�豸ʧ�ܣ����������������Ӳ����֧��ĳЩ���ܻ������������ɵġ�"
						"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
				}
				else
				{
					if( IDCANCEL == Misc::ShowMsg( "��������Ӳ����֧��ĳЩָ�������ԣ�����ʹ�������ʽģ�⣬"
						"����һ���ǳ�����\n���ȷ������ִ�г��򣬵��ȡ���˳�����",
						"ע��", MB_OKCANCEL | MB_ICONINFORMATION ) )
						return false;
				}
			}
			else
			{
				Misc::ShowMsg( "���������豸��֧��Ӳ�����㴦������ʹ��������㴦��",
					"ע��", MB_OK | MB_ICONINFORMATION );
			}
		}

#endif

		//��ȡ D3D9 ��ǰģʽ������Ϣ
		result = mpD3D9->GetDeviceCaps( mpConfig->sD3D9Cfg.nAdapter, mDeviceType, &mD3D9CurCaps );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"�޷���ȡ�Կ�������Ϣ��"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

		//�洢��ǰ��ʾ��ʽ
		mDisplayFormat		= pRenderSystemCfg->sD3D9Cfg.eColorFormat;
		mDisplayColorDepth	= Misc::GetColorDepth( mDisplayFormat );
		mDisplayAlphaBits	= Misc::GetColorAlphaBits( mDisplayFormat );

		//�����п��õƹ�����ֵ�����ջ
		DWORD nNumFreeLight = mD3D9CurCaps.MaxActiveLights;
		for( DWORD index=0; index<nNumFreeLight; ++index )
			*mFreeLightIndex.Push() = index;

		//�洢����ʹ�õ�����Ͷ���������
		mMaxTextureNum	= ( mD3D9CurCaps.MaxSimultaneousTextures <= 8 ) ? mD3D9CurCaps.MaxSimultaneousTextures : 8;
		mMaxStreamNum	= ( mD3D9CurCaps.MaxStreams <= 8 ) ? mD3D9CurCaps.MaxStreams : 8;

		//��ȡ���㴦��ʽ
		mbSoftVerProc = ( mpD3D9Device->GetSoftwareVertexProcessing() == TRUE );

		//���ҳ�滺��
		mpD3D9Device->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 0, 1.0f, 0 );

		//��ȡ��ʼ��Ⱦ״̬
		_GetRenderState( &mRenderState );

		//��ȡ��ʼ����״̬
		for( UINT i=0; i<8; ++i )
			_GetTextureState( &mpTextureState[i], i );

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ر���Ⱦϵͳ
	void D3D9RenderSystem::Shutdown()
	{
		SafeRelease( mpD3D9Device );
		SafeRelease( mpD3D9 );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�����Դ����ֵ
	UINT D3D9RenderSystem::GetAvailableTextureMem()
	{
		return mpD3D9Device->GetAvailableTextureMem();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ʾģʽ�Ƿ����
	PixelFormat D3D9RenderSystem::_CheckDisplayMode( UINT nAdapter, UINT nWidth, UINT nHeight, PixelFormat ePF,
		int nRefreshRate )
	{
		D3DDISPLAYMODE D3Ddm;

		//��ȡҪ������ɫ��ʽ
		D3DFORMAT d3dfmt = D3D9TypeGet::GetPixelFormat( ePF );

		//�������������Ƿ���ȷ
		UINT nAdapterCount = mpD3D9->GetAdapterCount();

		//�����ɫ��ʽ
		if( nAdapter >= 0 && nAdapter <= nAdapterCount )
		{
			//ѭ�����ÿһ����ʾģʽ
			UINT nModeCount = mpD3D9->GetAdapterModeCount( nAdapter, d3dfmt );
			for( UINT i=0; i<nModeCount; ++i )
			{
				//��ȡ��ʾģʽ
				mpD3D9->EnumAdapterModes( nAdapter, d3dfmt, i, &D3Ddm );

				//���Ϊȫ��ģʽ�����ȡ��߶��Ƿ����Ҫ��
				if( mpConfig->bWindowed || ( D3Ddm.Width == nWidth && D3Ddm.Height == nHeight ) )
				{
					//���ˢ�����Ƿ����Ҫ��
					if( D3Ddm.RefreshRate == nRefreshRate )
					{
						return ePF;
					}
				}
			}
		}

		return PF_UNKNOWN;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� D3D9 �豸��Ϣ
	void D3D9RenderSystem::_SetD3DPresentParam()
	{
		//�������ص�ִ�н��
		HRESULT result = E_FAIL;

		//��ʼ���豸��Ϣ����
		memset( &mD3Dpp, 0, sizeof(mD3Dpp) );

		//��Ⲣ��ȡָ�������ظ�ʽ
		PixelFormat DisplayPF = PF_UNKNOWN;
		DisplayPF = _CheckDisplayMode( mnAdpter, mRenderWidth, mRenderHeight,
			mpConfig->sD3D9Cfg.eColorFormat, mpConfig->sD3D9Cfg.nRefreshRate );
		if( DisplayPF == PF_UNKNOWN )
			Except( Exception::ERR_INTERNAL_ERROR, "�Կ���֧�������ļ���ָ������ʾģʽ��" );

		//���� D3D ��ʾģʽ
		mD3Dpp.BackBufferFormat = D3D9TypeGet::GetPixelFormat( DisplayPF );

#ifdef _DEBUG
		mD3Dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
		mD3Dpp.SwapEffect					= D3DSWAPEFFECT_COPY;					//����ҳ��ˢ�·�ʽ����
		mD3Dpp.Windowed						= true;
#else
		//���Ϊ����ģʽ
		if( mpConfig->bWindowed )
		{
			mD3Dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
			mD3Dpp.SwapEffect					= D3DSWAPEFFECT_COPY;				//����ҳ��ˢ�·�ʽ����
			mD3Dpp.Windowed						= true;
			mD3Dpp.BackBufferCount				= 1;								//����ˢ�·�ʽ����ҳ����������Ϊ 1
		}
		//���Ϊȫ��ģʽ
		else
		{
			mD3Dpp.FullScreen_RefreshRateInHz	= mpConfig->sD3D9Cfg.nRefreshRate;	//����ȫ��ˢ����Ϊָ��ˢ����
			mD3Dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;			//����ҳ��ˢ�·�ʽ������ҳ��
			mD3Dpp.Windowed						= false;
			mD3Dpp.BackBufferCount				= mpConfig->sD3D9Cfg.nNumBackBuffer;
		}
#endif

		//�趨�豸��Ϣ
		mD3Dpp.BackBufferWidth				= mRenderWidth;							//�趨����ҳ�棨���������
		mD3Dpp.BackBufferHeight				= mRenderHeight;						//�趨����ҳ�棨�������߶�
		mD3Dpp.hDeviceWindow				= mpRenderWindow->mhWnd;				//�趨���ھ��

		//�ж��Ƿ�����ֱͬ��
		mD3Dpp.PresentationInterval = ( mpConfig->sD3D9Cfg.bVsync ) ?
										D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;

		mD3Dpp.Flags						= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;	//������Ȼ���ģʽ
		mD3Dpp.EnableAutoDepthStencil		= TRUE;									//����Ȼ���
		mD3Dpp.AutoDepthStencilFormat		= D3DFMT_D16;							//�趨��Ȼ������Ϊ16λ

		//���ö���ȡ��ģʽ
		if( mpConfig->sD3D9Cfg.nMultiSampleType == 0 )
		{
			//���δӦ�ö���ȡ��������Ϊ��
			mD3Dpp.MultiSampleType		= D3DMULTISAMPLE_NONE;
			mD3Dpp.MultiSampleQuality	= 0;
		}
		else
		{
			//���Ӧ���˶���ȡ�������ȼ��Ӳ���Ƿ�֧���趨ģʽ
			DWORD Quality = 0;
			BOOL bWindowed = ( mpConfig->bWindowed ) ? TRUE : FALSE;
			result = mpD3D9->CheckDeviceMultiSampleType( mpConfig->sD3D9Cfg.nAdapter, D3DDEVTYPE_HAL,
				mD3Dpp.BackBufferFormat, bWindowed,
				(D3DMULTISAMPLE_TYPE)mpConfig->sD3D9Cfg.nMultiSampleType, &Quality );
			if( result == D3D_OK )
			{
				result = mpD3D9->CheckDeviceMultiSampleType( mpConfig->sD3D9Cfg.nAdapter, D3DDEVTYPE_HAL,
					mD3Dpp.AutoDepthStencilFormat, bWindowed,
					(D3DMULTISAMPLE_TYPE)mpConfig->sD3D9Cfg.nMultiSampleType, &Quality );
			}

			//���Ӳ��֧���趨ģʽ��Ӧ����
			if( result == D3D_OK && mpConfig->sD3D9Cfg.dwMultiSampleQuality < Quality )
			{
				mD3Dpp.MultiSampleType		= (D3DMULTISAMPLE_TYPE)mpConfig->sD3D9Cfg.nMultiSampleType;
				mD3Dpp.MultiSampleQuality	= mpConfig->sD3D9Cfg.dwMultiSampleQuality;
			}
			else
			{
				Except( Exception::ERR_INTERNAL_ERROR, "�Կ���֧�������ļ���ָ���Ķ���ȡ����ȫ������ݣ�ģʽ��" );
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷ��豸��Դ
	void D3D9RenderSystem::_InvalidateDeviceObjects()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����豸��Դ
	void D3D9RenderSystem::_RestoreDeviceObjects()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ӿ�
	void FKFastcall D3D9RenderSystem::_SetViewport( Viewport* pViewport )
	{
		mpViewport = pViewport;
		HRESULT result = mpD3D9Device->SetViewport( (D3DVIEWPORT9*)pViewport );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 �ӿ�ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ù۲����
	void FKFastcall D3D9RenderSystem::_SetViewMatrix( const Matrix4* pViewMatrix )
	{
		HRESULT result = mpD3D9Device->SetTransform( D3DTS_VIEW, (D3DXMATRIX*)pViewMatrix );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 �۲����ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ͶӰ����
	void FKFastcall D3D9RenderSystem::_SetProjMatrix( const Matrix4* pProjMatrix )
	{
		HRESULT result = mpD3D9Device->SetTransform( D3DTS_PROJECTION, (D3DXMATRIX*)pProjMatrix );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 ͶӰ����ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ⱦ����
	void FKFastcall D3D9RenderSystem::_SetWorldMatrix( const Matrix4* pWorldMatrix, int nIndex )
	{
		HRESULT result = mpD3D9Device->SetTransform( D3DTS_WORLDMATRIX( nIndex ), (D3DXMATRIX*)pWorldMatrix );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 �������ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�۲����
	void FKFastcall D3D9RenderSystem::_GetViewMatrix( Matrix4* pViewMatrix )
	{
		HRESULT result = mpD3D9Device->GetTransform( D3DTS_VIEW, (D3DXMATRIX*)pViewMatrix );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"��ȡ D3D9 �۲����ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡͶӰ����
	void FKFastcall D3D9RenderSystem::_GetProjMatrix( Matrix4* pProjMatrix )
	{
		HRESULT result = mpD3D9Device->GetTransform( D3DTS_PROJECTION, (D3DXMATRIX*)pProjMatrix );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"��ȡ D3D9 ͶӰ����ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��Ⱦ����
	void FKFastcall D3D9RenderSystem::_GetWorldMatrix( Matrix4* pWorldMatrix, int nIndex )
	{
		HRESULT result = mpD3D9Device->GetTransform( D3DTS_WORLDMATRIX( nIndex ), (D3DXMATRIX*)pWorldMatrix );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"��ȡ D3D9 �������ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ò���
	void FKFastcall D3D9RenderSystem::_SetMaterial( const Material* pMaterial )
	{
		//���ò���
		HRESULT result = mpD3D9Device->SetMaterial( (D3DMATERIAL9*)pMaterial );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 ����ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void FKFastcall D3D9RenderSystem::_SetTexture( const Texture* pTexture, const DWORD dwStage )
	{
		if( dwStage >= mMaxTextureNum )
			Except( Exception::ERR_INVALIDPARAMS, "ָ�����õ���������������֧�ֵ�����ޡ�" );

		//����������������õ�������ͬ�򷵻�
		if( mppLastTexture[dwStage] == pTexture )
			return;

		IDirect3DBaseTexture9* pD3D9Texture = ( pTexture != NULL ) ?
			( reinterpret_cast< const D3D9Texture* >( pTexture )->mBaseTexture.mpD3D9Texture ) : NULL;

		HRESULT result = mpD3D9Device->SetTexture( dwStage, pD3D9Texture );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 ����ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

		mppLastTexture[dwStage] = (Texture*)pTexture;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ö�������
	void FKFastcall D3D9RenderSystem::_SetVertexDeclaration( const VertexDeclaration* pVertexDeclaration )
	{
		//����ö���������������õĶ���������ͬ�򷵻�
		if( mpLastVD == pVertexDeclaration )
			return;

		const D3D9VertexDeclaration* pVD = static_cast< const D3D9VertexDeclaration* >( pVertexDeclaration );
		HRESULT result = mpD3D9Device->SetVertexDeclaration( pVD->mpD3D9VertexDeclaration );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 ��������ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

		mpLastVD = (VertexDeclaration*)pVertexDeclaration;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ö�����
	void FKFastcall D3D9RenderSystem::_SetVertexStream( const VertexBuffer* pVertexBuf, const DWORD dwStream )
	{
		if( dwStream >= mMaxStreamNum )
			Except( Exception::ERR_INVALIDPARAMS, "ָ�����õĶ���������������֧�ֵ�����ޡ�" );

		//����ö�������������õĶ�������ͬ�򷵻�
		if( mppLastVB[dwStream] == pVertexBuf )
			return;

		const D3D9VertexBuffer* pVB = static_cast< const D3D9VertexBuffer* >( pVertexBuf );
		HRESULT result = mpD3D9Device->SetStreamSource( dwStream, pVB->mpD3D9VertexBuffer, 0, pVB->mVerSize );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 ������ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

		mppLastVB[dwStream] = (VertexBuffer*)pVertexBuf;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������
	void FKFastcall D3D9RenderSystem::_SetIndexStream( const IndexBuffer* pIndexBuf )
	{
		//�������������������õ���������ͬ�򷵻�
		if( mpLastIB == pIndexBuf )
			return;

		HRESULT result = mpD3D9Device->SetIndices( static_cast< const D3D9IndexBuffer* >( pIndexBuf )->mpD3D9IndexBuffer );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 ������ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

		mpLastIB = (IndexBuffer*)pIndexBuf;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ���㣨�������㣩
	void FKFastcall D3D9RenderSystem::_RenderVertex( PrimitiveType ePrimType, int nVerOffset, UINT nMinIndex,
		UINT nNumVer, UINT nIndexOffset, UINT nPrimCount )
	{
		//--------------------------------------------------------------------------------------
		// �����������˵��
		//
		//	1. ʵ�ʻ���ʹ�ö��㣨�Զ��㻺����ʼλ��Ϊ��׼�� = ��������������ֵ + ��������ƫ����
		//	2. ���ƶ������� = ʵ�ʻ���ʹ�õĵ�һ������ �� ʵ�ʻ���ʹ�õ����һ������
		//	3. ��ǰ������ʹ�õ����������е���������ֵ��������С��ʹ����С����ֵ
		//	4. ��������ƫ������ֵ����Ӱ��ʵ�ʵĶ�������ֵ
		//
		//--------------------------------------------------------------------------------------

		D3DPRIMITIVETYPE d3dpt = D3D9TypeGet::GetPrimitiveType( ePrimType );
		HRESULT result = mpD3D9Device->DrawIndexedPrimitive(
			d3dpt,			//����ͼԪ����
			nVerOffset,		//��������ƫ����
			nMinIndex,		//ʹ����С����ֵ
			nNumVer,		//���ƶ�������
			nIndexOffset,	//��������ƫ����
			nPrimCount );	//����ͼԪ����

		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"��������������ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

		//������ȾͼԪ����
		mNumTriangle += nPrimCount;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ����
	void FKFastcall D3D9RenderSystem::_RenderVertex( PrimitiveType ePrimType, UINT nVerOffset, UINT nPrimCount )
	{
		HRESULT result = mpD3D9Device->DrawPrimitive( D3D9TypeGet::GetPrimitiveType( ePrimType ), nVerOffset, nPrimCount );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���ƶ�����ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

		//������ȾͼԪ����
		mNumTriangle += nPrimCount;
	}
	//--------------------------------------------------------------------------------------------------------------
	//׼���豸
	void FKFastcall D3D9RenderSystem::_PrepareDevice()
	{
		//����豸��ʧ���������豸��
		HRESULT result = mpD3D9Device->TestCooperativeLevel();
		if( result != D3D_OK )
		{
			//�ȴ��豸״̬Ϊ D3DERR_DEVICENOTRESET �ſ�������
			while( result != D3DERR_DEVICENOTRESET )
				result = mpD3D9Device->TestCooperativeLevel();

			//�ͷ��豸��Դ
			_InvalidateDeviceObjects();

			//�����豸
			result = mpD3D9Device->Reset( &mD3Dpp );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"�豸��ʧ�������豸ʧ�ܡ�"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

			//�����豸��Դ
			_RestoreDeviceObjects();
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ��Ⱦ
	void FKFastcall D3D9RenderSystem::_BeginRender()
	{
		//�����һ֡����Ⱦͼ��
		DWORD ClearFlag = D3DCLEAR_ZBUFFER;
		if( mpViewport->mbClearPerFrame )
			ClearFlag |= D3DCLEAR_TARGET;

		HRESULT result = mpD3D9Device->Clear( 0, NULL, ClearFlag, mpViewport->mdwClearColor, 1.0f, 0 );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"ʹ�� D3D9 �豸�����һ֡����Ⱦͼ��ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
		//��ʼ��Ⱦ
		result = mpD3D9Device->BeginScene();
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 �豸��ʼ������Ⱦʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ⱦ
	void FKFastcall D3D9RenderSystem::_EndRender()
	{
		//������Ⱦ
		HRESULT result = mpD3D9Device->EndScene();
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 �豸����������Ⱦʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ⱦҳ��
	void FKFastcall D3D9RenderSystem::_SwapRenderBuffer()
	{
		//������ҳ�����ҳ����л�ҳ��ʹ�����ڻ���ҳ������Ⱦ�Ķ�����ʾ�ڣ���ҳ�棩��Ļ�ϡ�
		HRESULT result = mpD3D9Device->Present(
			mbUseSwapSrcRect ? &mSwapSrcRect : NULL,
			mbUseSwapDestRect ? &mSwapDestRect : NULL,
			mhSwapDestWindow,
			NULL );

		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"D3D9 �豸��ҳʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��Ⱦ״̬
	void FKFastcall D3D9RenderSystem::_GetRenderState( RenderState* pRenderState )
	{
		DWORD dwValue = 0;

		mpD3D9Device->GetRenderState( D3DRS_FILLMODE, &dwValue );
		pRenderState->mFillMode = D3D9TypeConvert::GetFillMode( dwValue );

		mpD3D9Device->GetRenderState( D3DRS_SHADEMODE, &dwValue );
		pRenderState->mShadeMode = D3D9TypeConvert::GetShadeMode( dwValue );

		mpD3D9Device->GetRenderState( D3DRS_CULLMODE, &dwValue );
		pRenderState->mCullMode = D3D9TypeConvert::GetCullMode( dwValue );

		mpD3D9Device->GetRenderState( D3DRS_LIGHTING, &dwValue );
		pRenderState->mbLighting = ( dwValue == TRUE ) ? true : false;

		mpD3D9Device->GetRenderState( D3DRS_SPECULARENABLE, &dwValue );
		pRenderState->mbSpecular = ( dwValue == TRUE ) ? true : false;

		mpD3D9Device->GetRenderState( D3DRS_FOGENABLE, &dwValue );
		pRenderState->mbFogEnable = ( dwValue == TRUE ) ? true : false;

		mpD3D9Device->GetRenderState( D3DRS_FOGTABLEMODE, &dwValue );
		pRenderState->mFogMode = D3D9TypeConvert::GetFogMode( dwValue );

		mpD3D9Device->GetRenderState( D3DRS_FOGCOLOR, &dwValue );
		pRenderState->mFogColor = dwValue;

		mpD3D9Device->GetRenderState( D3DRS_FOGSTART, &dwValue );
		pRenderState->mFogStart = *(float*)&dwValue;

		mpD3D9Device->GetRenderState( D3DRS_FOGEND, &dwValue );
		pRenderState->mFogEnd = *(float*)&dwValue;

		mpD3D9Device->GetRenderState( D3DRS_FOGDENSITY, &dwValue );
		pRenderState->mFogDensity = *(float*)&dwValue;

		mpD3D9Device->GetRenderState( D3DRS_ZENABLE, &dwValue );
		pRenderState->mbDepthTestEnable = ( dwValue != D3DZB_FALSE ) ? true : false;

		mpD3D9Device->GetRenderState( D3DRS_ZWRITEENABLE, &dwValue );
		pRenderState->mbDepthWriteEnable = ( dwValue == TRUE ) ? true : false;

		mpD3D9Device->GetRenderState( D3DRS_ALPHABLENDENABLE, &dwValue );
		pRenderState->mbAlphaEnable = ( dwValue == TRUE ) ? true : false;

		mpD3D9Device->GetRenderState( D3DRS_ALPHATESTENABLE, &dwValue );
		pRenderState->mbAlphaTestEnable = ( dwValue == TRUE ) ? true : false;

		mpD3D9Device->GetRenderState( D3DRS_ZFUNC, &dwValue );
		pRenderState->mDepthCompareFun = D3D9TypeConvert::GetCompareFun( dwValue );

		mpD3D9Device->GetRenderState( D3DRS_ALPHAFUNC, &dwValue );
		pRenderState->mAlphaCompareFun = D3D9TypeConvert::GetCompareFun( dwValue );

		mpD3D9Device->GetRenderState( D3DRS_ALPHAREF, &dwValue );
		pRenderState->mdwAlphaRefValue = dwValue;

		mpD3D9Device->GetRenderState( D3DRS_SRCBLEND, &dwValue );
		pRenderState->mSrcBlendFactor = D3D9TypeConvert::GetBlendFactor( dwValue );

		mpD3D9Device->GetRenderState( D3DRS_DESTBLEND, &dwValue );
		pRenderState->mDestBlendFactor = D3D9TypeConvert::GetBlendFactor( dwValue );

		mpD3D9Device->GetRenderState( D3DRS_SRCBLENDALPHA, &dwValue );
		pRenderState->mSrcAlphaBlendFactor = D3D9TypeConvert::GetBlendFactor( dwValue );

		mpD3D9Device->GetRenderState( D3DRS_DESTBLENDALPHA, &dwValue );
		pRenderState->mDestAlphaBlendFactor = D3D9TypeConvert::GetBlendFactor( dwValue );
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ⱦ״̬
	void FKFastcall D3D9RenderSystem::_SetRenderState( const RenderState* pRenderState )
	{
		HRESULT result;

		if( mRenderState.mFillMode != pRenderState->mFillMode )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_FILLMODE, D3D9TypeGet::GetFillMode( pRenderState->mFillMode ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"�������ģʽ����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mFillMode = pRenderState->mFillMode;
		}

		if( mRenderState.mShadeMode != pRenderState->mShadeMode )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_SHADEMODE, D3D9TypeGet::GetShadeMode( pRenderState->mShadeMode ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"������Ӱģʽ����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mShadeMode = pRenderState->mShadeMode;
		}

		if( mRenderState.mCullMode != pRenderState->mCullMode )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_CULLMODE, D3D9TypeGet::GetCullMode( pRenderState->mCullMode ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"���ü�ѡģʽ����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mCullMode = pRenderState->mCullMode;
		}

		if( mRenderState.mbLighting != pRenderState->mbLighting )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_LIGHTING, pRenderState->mbLighting ? TRUE : FALSE );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"���ù���״̬����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mbLighting = pRenderState->mbLighting;
		}

		if( mRenderState.mbSpecular != pRenderState->mbSpecular )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_SPECULARENABLE, pRenderState->mbSpecular ? TRUE : FALSE );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"���ø߹�״̬����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mbSpecular = pRenderState->mbSpecular;
		}

		if( mRenderState.mbFogEnable != pRenderState->mbFogEnable )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_FOGENABLE, pRenderState->mbFogEnable ? TRUE : FALSE );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"������״̬����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mbFogEnable = pRenderState->mbFogEnable;
		}

		if( mRenderState.mFogMode != pRenderState->mFogMode )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_FOGTABLEMODE, D3D9TypeGet::GetFogMode( pRenderState->mFogMode ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"������ģʽ����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mFogMode = pRenderState->mFogMode;
		}

		if( mRenderState.mFogColor != pRenderState->mFogColor )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_FOGCOLOR, pRenderState->mFogColor );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"��������ɫ����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mFogColor = pRenderState->mFogColor;
		}

		if( mRenderState.mFogStart != pRenderState->mFogStart )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_FOGSTART, *(DWORD*)&pRenderState->mFogStart );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"��������ʼλ�ô���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mFogStart = pRenderState->mFogStart;
		}

		if( mRenderState.mFogEnd != pRenderState->mFogEnd )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_FOGEND, *(DWORD*)&pRenderState->mFogEnd );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"����������λ�ô���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mFogEnd = pRenderState->mFogEnd;
		}

		if( mRenderState.mFogDensity != pRenderState->mFogDensity )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_FOGDENSITY, *(DWORD*)&pRenderState->mFogDensity );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"������Ũ�ȴ���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mFogDensity = pRenderState->mFogDensity;
		}

		if( mRenderState.mbDepthTestEnable != pRenderState->mbDepthTestEnable )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_ZENABLE, pRenderState->mbDepthTestEnable ? mdwDepthMode : D3DZB_FALSE );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"������Ȳ���״̬����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mbDepthTestEnable = pRenderState->mbDepthTestEnable;
		}

		if( mRenderState.mbDepthWriteEnable != pRenderState->mbDepthWriteEnable )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_ZWRITEENABLE, pRenderState->mbDepthWriteEnable ? TRUE : FALSE );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"�������д��״̬����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mbDepthWriteEnable = pRenderState->mbDepthWriteEnable;
		}

		if( mRenderState.mbAlphaEnable != pRenderState->mbAlphaEnable )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_ALPHABLENDENABLE, pRenderState->mbAlphaEnable ? TRUE : FALSE );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"���� Alpha ���״̬����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mbAlphaEnable = pRenderState->mbAlphaEnable;
		}

		if( mRenderState.mbAlphaTestEnable != pRenderState->mbAlphaTestEnable )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_ALPHATESTENABLE, pRenderState->mbAlphaTestEnable ? TRUE : FALSE );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"���� Alpha ����״̬����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mbAlphaTestEnable = pRenderState->mbAlphaTestEnable;
		}

		if( mRenderState.mDepthCompareFun != pRenderState->mDepthCompareFun )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_ZFUNC, D3D9TypeGet::GetCompareFun( pRenderState->mDepthCompareFun ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"������ȱȽϺ�������"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mDepthCompareFun = pRenderState->mDepthCompareFun;
		}

		if( mRenderState.mAlphaCompareFun != pRenderState->mAlphaCompareFun )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_ALPHAFUNC, D3D9TypeGet::GetCompareFun( pRenderState->mAlphaCompareFun ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"���� Alpha �ȽϺ�������"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mAlphaCompareFun = pRenderState->mAlphaCompareFun;
		}

		if( mRenderState.mdwAlphaRefValue != pRenderState->mdwAlphaRefValue )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_ALPHAREF, pRenderState->mdwAlphaRefValue );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"���� Alpha ���Բ���ֵ����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mdwAlphaRefValue = pRenderState->mdwAlphaRefValue;
		}

		if( mRenderState.mSrcBlendFactor != pRenderState->mSrcBlendFactor )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_SRCBLEND, D3D9TypeGet::GetBlendFactor( pRenderState->mSrcBlendFactor ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"������Դ��ɫ������ʹ���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mSrcBlendFactor = pRenderState->mSrcBlendFactor;
		}

		if( mRenderState.mDestBlendFactor != pRenderState->mDestBlendFactor )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_DESTBLEND, D3D9TypeGet::GetBlendFactor( pRenderState->mDestBlendFactor ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"����Ŀ����ɫ������ʹ���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mDestBlendFactor = pRenderState->mDestBlendFactor;
		}

		if( mRenderState.mSrcAlphaBlendFactor != pRenderState->mSrcAlphaBlendFactor )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_SRCBLENDALPHA, D3D9TypeGet::GetBlendFactor( pRenderState->mSrcAlphaBlendFactor ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"������Դ Alpha ֵ������ʹ���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mSrcAlphaBlendFactor = pRenderState->mSrcAlphaBlendFactor;
		}

		if( mRenderState.mDestAlphaBlendFactor != pRenderState->mDestAlphaBlendFactor )
		{
			result = mpD3D9Device->SetRenderState( D3DRS_DESTBLENDALPHA, D3D9TypeGet::GetBlendFactor( pRenderState->mDestAlphaBlendFactor ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"����Ŀ�� Alpha ֵ������ʹ���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mDestAlphaBlendFactor = pRenderState->mDestAlphaBlendFactor;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ����״̬
	void FKFastcall D3D9RenderSystem::_GetTextureState( TextureState* pTextureState, UINT nStage )
	{
		DWORD dwValue;

		mpD3D9Device->GetSamplerState( nStage, D3DSAMP_MAGFILTER, &dwValue );
		pTextureState->mFilterMag = D3D9TypeConvert::GetTextureFilter( dwValue );

		mpD3D9Device->GetSamplerState( nStage, D3DSAMP_MINFILTER, &dwValue );
		pTextureState->mFilterMin = D3D9TypeConvert::GetTextureFilter( dwValue );

		mpD3D9Device->GetSamplerState( nStage, D3DSAMP_MIPFILTER, &dwValue );
		pTextureState->mFilterMip = D3D9TypeConvert::GetTextureFilter( dwValue );

		mpD3D9Device->GetSamplerState( nStage, D3DSAMP_ADDRESSU, &dwValue );
		pTextureState->mAddressU = D3D9TypeConvert::GetTextureAddress( dwValue );

		mpD3D9Device->GetSamplerState( nStage, D3DSAMP_ADDRESSV, &dwValue );
		pTextureState->mAddressV = D3D9TypeConvert::GetTextureAddress( dwValue );

		mpD3D9Device->GetSamplerState( nStage, D3DSAMP_ADDRESSW, &dwValue );
		pTextureState->mAddressW = D3D9TypeConvert::GetTextureAddress( dwValue );

		mpD3D9Device->GetTextureStageState( nStage, D3DTSS_COLOROP, &dwValue );
		pTextureState->mColorOp = D3D9TypeConvert::GetTextureOp( dwValue );

		mpD3D9Device->GetTextureStageState( nStage, D3DTSS_ALPHAOP, &dwValue );
		pTextureState->mAlphaOp = D3D9TypeConvert::GetTextureOp( dwValue );

		mpD3D9Device->GetTextureStageState( nStage, D3DTSS_COLORARG1, &dwValue );
		pTextureState->mColorArg1 = D3D9TypeConvert::GetTextureArg( dwValue );

		mpD3D9Device->GetTextureStageState( nStage, D3DTSS_COLORARG2, &dwValue );
		pTextureState->mColorArg2 = D3D9TypeConvert::GetTextureArg( dwValue );

		mpD3D9Device->GetTextureStageState( nStage, D3DTSS_ALPHAARG1, &dwValue );
		pTextureState->mAlphaArg1 = D3D9TypeConvert::GetTextureArg( dwValue );

		mpD3D9Device->GetTextureStageState( nStage, D3DTSS_ALPHAARG2, &dwValue );
		pTextureState->mAlphaArg2 = D3D9TypeConvert::GetTextureArg( dwValue );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������״̬
	void FKFastcall D3D9RenderSystem::_SetTextureState( const TextureState* pTextureState, UINT nStage )
	{
		HRESULT result;

		if( mpTextureState[nStage].mFilterMag != pTextureState->mFilterMag )
		{
			result = mpD3D9Device->SetSamplerState( nStage, D3DSAMP_MAGFILTER,
				D3D9TypeGet::GetTextureFilter( pTextureState->mFilterMag ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"���÷Ŵ�����������ʹ���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mpTextureState[nStage].mFilterMag = pTextureState->mFilterMag;
		}

		if( mpTextureState[nStage].mFilterMin != pTextureState->mFilterMin )
		{
			result = mpD3D9Device->SetSamplerState( nStage, D3DSAMP_MINFILTER,
				D3D9TypeGet::GetTextureFilter( pTextureState->mFilterMin ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"������С����������ʹ���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mpTextureState[nStage].mFilterMin = pTextureState->mFilterMin;
		}

		if( mpTextureState[nStage].mFilterMip != pTextureState->mFilterMip )
		{
			result = mpD3D9Device->SetSamplerState( nStage, D3DSAMP_MIPFILTER,
				D3D9TypeGet::GetTextureFilter( pTextureState->mFilterMip ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"���ö༶����������ʹ���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mpTextureState[nStage].mFilterMip = pTextureState->mFilterMip;
		}

		if( mpTextureState[nStage].mAddressU != pTextureState->mAddressU )
		{
			result = mpD3D9Device->SetSamplerState( nStage, D3DSAMP_ADDRESSU,
				D3D9TypeGet::GetTextureAddress( pTextureState->mAddressU ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"�������� U ����Ѱַ���ʹ���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mpTextureState[nStage].mAddressU = pTextureState->mAddressU;
		}

		if( mpTextureState[nStage].mAddressV != pTextureState->mAddressV )
		{
			result = mpD3D9Device->SetSamplerState( nStage, D3DSAMP_ADDRESSV,
				D3D9TypeGet::GetTextureAddress( pTextureState->mAddressV ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"�������� V ����Ѱַ���ʹ���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mpTextureState[nStage].mAddressV = pTextureState->mAddressV;
		}

		if( mpTextureState[nStage].mAddressW != pTextureState->mAddressW )
		{
			result = mpD3D9Device->SetSamplerState( nStage, D3DSAMP_ADDRESSW,
				D3D9TypeGet::GetTextureAddress( pTextureState->mAddressW ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"�������� W ����Ѱַ���ʹ���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mpTextureState[nStage].mAddressW = pTextureState->mAddressW;
		}

		if( mpTextureState[nStage].mColorOp != pTextureState->mColorOp )
		{
			result = mpD3D9Device->SetTextureStageState( nStage, D3DTSS_COLOROP,
				D3D9TypeGet::GetTextureOp( pTextureState->mColorOp ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"����������ɫ�������ʹ���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mpTextureState[nStage].mColorOp = pTextureState->mColorOp;
		}

		if( mpTextureState[nStage].mAlphaOp != pTextureState->mAlphaOp )
		{
			result = mpD3D9Device->SetTextureStageState( nStage, D3DTSS_ALPHAOP,
				D3D9TypeGet::GetTextureOp( pTextureState->mAlphaOp ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"�������� Alpha �������ʹ���"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mpTextureState[nStage].mAlphaOp = pTextureState->mAlphaOp;
		}

		if( mpTextureState[nStage].mColorArg1 != pTextureState->mColorArg1 )
		{
			result = mpD3D9Device->SetTextureStageState( nStage, D3DTSS_COLORARG1,
				D3D9TypeGet::GetTextureArg( pTextureState->mColorArg1 ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"����������ɫ�������� 1 ����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mpTextureState[nStage].mColorArg1 = pTextureState->mColorArg1;
		}

		if( mpTextureState[nStage].mColorArg2 != pTextureState->mColorArg2 )
		{
			result = mpD3D9Device->SetTextureStageState( nStage, D3DTSS_COLORARG2,
				D3D9TypeGet::GetTextureArg( pTextureState->mColorArg2 ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"����������ɫ�������� 2 ����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mpTextureState[nStage].mColorArg2 = pTextureState->mColorArg2;
		}

		if( mpTextureState[nStage].mAlphaArg1 != pTextureState->mAlphaArg1 )
		{
			result = mpD3D9Device->SetTextureStageState( nStage, D3DTSS_ALPHAARG1,
				D3D9TypeGet::GetTextureArg( pTextureState->mAlphaArg1 ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"�������� Alpha �������� 1 ����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mpTextureState[nStage].mAlphaArg1 = pTextureState->mAlphaArg1;
		}

		if( mpTextureState[nStage].mAlphaArg2 != pTextureState->mAlphaArg2 )
		{
			result = mpD3D9Device->SetTextureStageState( nStage, D3DTSS_ALPHAARG2,
				D3D9TypeGet::GetTextureArg( pTextureState->mAlphaArg2 ) );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"�������� Alpha �������� 2 ����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mpTextureState[nStage].mAlphaArg2 = pTextureState->mAlphaArg2;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ر�����״̬
	void FKFastcall D3D9RenderSystem::_DisableTextureState( UINT nStage )
	{
		HRESULT result;

		result = mpD3D9Device->SetTextureStageState( nStage, D3DTSS_COLOROP, D3DTOP_DISABLE );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"�ر�������ɫ��������"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

		result = mpD3D9Device->SetTextureStageState( nStage, D3DTSS_ALPHAOP, D3DTOP_DISABLE );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"�ر����� Alpha ��������"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

		mpTextureState[nStage].mColorOp = TO_DISABLE;
		mpTextureState[nStage].mAlphaOp = TO_DISABLE;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ù���״̬
	void FKFastcall D3D9RenderSystem::_SetLightingState( bool bEnable )
	{
		if( mRenderState.mbLighting != bEnable )
		{
			HRESULT result = mpD3D9Device->SetRenderState( D3DRS_LIGHTING, bEnable ? TRUE : FALSE );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"���ù���״̬����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mbLighting = bEnable;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ø߹�״̬
	void FKFastcall D3D9RenderSystem::_SetSpecularState( bool bEnable )
	{
		if( mRenderState.mbSpecular != bEnable )
		{
			HRESULT result = mpD3D9Device->SetRenderState( D3DRS_SPECULARENABLE, bEnable ? TRUE : FALSE );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"���ø߹�״̬����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mbSpecular = bEnable;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//������״̬
	void FKFastcall D3D9RenderSystem::_SetFogState( bool bEnable )
	{
		if( mRenderState.mbFogEnable != bEnable )
		{
			HRESULT result = mpD3D9Device->SetRenderState( D3DRS_FOGENABLE, bEnable ? TRUE : FALSE );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"������״̬����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mbFogEnable = bEnable;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ȳ���״̬
	void FKFastcall D3D9RenderSystem::_SetDepthTestState( bool bEnable )
	{
		if( mRenderState.mbDepthTestEnable != bEnable )
		{
			HRESULT result = mpD3D9Device->SetRenderState( D3DRS_ZENABLE, bEnable ? mdwDepthMode : D3DZB_FALSE );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"������Ȳ���״̬����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mbDepthTestEnable = bEnable;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������д��״̬
	void FKFastcall D3D9RenderSystem::_SetDepthWriteState( bool bEnable )
	{
		if( mRenderState.mbDepthWriteEnable != bEnable )
		{
			HRESULT result = mpD3D9Device->SetRenderState( D3DRS_ZWRITEENABLE, bEnable ? TRUE : FALSE );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"�������д��״̬����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mbDepthWriteEnable = bEnable;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� Alpha ���״̬
	void FKFastcall D3D9RenderSystem::_SetAlphaState( bool bEnable )
	{
		if( mRenderState.mbAlphaEnable != bEnable )
		{
			HRESULT result = mpD3D9Device->SetRenderState( D3DRS_ALPHABLENDENABLE, bEnable ? TRUE : FALSE );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"���� Alpha ���״̬����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mbAlphaEnable = bEnable;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� Alpha ����״̬
	void FKFastcall D3D9RenderSystem::_SetAlphaTestState( bool bEnable )
	{
		if( mRenderState.mbAlphaTestEnable != bEnable )
		{
			HRESULT result = mpD3D9Device->SetRenderState( D3DRS_ALPHATESTENABLE, bEnable ? TRUE : FALSE );
			if( FAILED( result ) )
				Except( Exception::ERR_RENDER_API_ERROR, (String)"���� Alpha ����״̬����"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			mRenderState.mbAlphaTestEnable = bEnable;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������������
	void FKFastcall D3D9RenderSystem::_SetTextureFilter( SamplerType eSamplerType, TextureFilterType eFilterType, UINT nStage )
	{
		TextureFilterType* pFilterType;
		D3DSAMPLERSTATETYPE eD3DSamplerType;

		switch (eSamplerType)
		{
		case ST_MAGFILTER:		pFilterType = &mpTextureState[nStage].mFilterMag;		eD3DSamplerType = D3DSAMP_MAGFILTER;	break;
		case ST_MINFILTER:		pFilterType = &mpTextureState[nStage].mFilterMin;		eD3DSamplerType = D3DSAMP_MINFILTER;	break;
		case ST_MIPFILTER:		pFilterType = &mpTextureState[nStage].mFilterMip;		eD3DSamplerType = D3DSAMP_MIPFILTER;	break;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "ȡ�����ʹ����޷������������������Ⱦ״̬��" );
		}

		if( *pFilterType == eFilterType )
			return;

		HRESULT result = mpD3D9Device->SetSamplerState( nStage, eD3DSamplerType, D3D9TypeGet::GetTextureFilter( eFilterType ) );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"��������������ʹ���"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

		*pFilterType = eFilterType;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������Ѱַ����
	void FKFastcall D3D9RenderSystem::_SetTextureAddress( SamplerType eSamplerType, TextureAddressType eAddressType, UINT nStage )
	{
		TextureAddressType* pAddressType;
		D3DSAMPLERSTATETYPE eD3DSamplerType;

		switch (eSamplerType)
		{
		case ST_ADDRESSU:		pAddressType = &mpTextureState[nStage].mAddressU;		eD3DSamplerType = D3DSAMP_ADDRESSU;		break;
		case ST_ADDRESSV:		pAddressType = &mpTextureState[nStage].mAddressV;		eD3DSamplerType = D3DSAMP_ADDRESSV;		break;
		case ST_ADDRESSW:		pAddressType = &mpTextureState[nStage].mAddressW;		eD3DSamplerType = D3DSAMP_ADDRESSW;		break;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "ȡ�����ʹ����޷���������Ѱַ������Ⱦ״̬��" );
		}

		if( *pAddressType == eAddressType )
			return;

		HRESULT result = mpD3D9Device->SetSamplerState( nStage, eD3DSamplerType, D3D9TypeGet::GetTextureAddress( eAddressType ) );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"��������Ѱַ���ʹ���"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

		*pAddressType = eAddressType;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƹ�
	bool FKFastcall D3D9RenderSystem::_ActiveLight( Light* pLight, const bool bActive )
	{
		HRESULT result;

		//���Ҫ�����õƹ�
		if( bActive )
		{
			//����޿��õƹ������򷵻�
			if( mFreeLightIndex.Size() == 0 )
				return false;

			//��ȡ����ֵ
			pLight->mIndex = *mFreeLightIndex.Pop();

			//���� D3D9 �ƹ�����
			static D3DLIGHT9 LightData;
			LightData.Type = D3D9TypeGet::GetLightType( pLight->mLightType );
			memcpy( &LightData.Diffuse, &pLight->mDiffuse, sizeof(D3DLIGHT9) - sizeof(D3DLIGHTTYPE) );

			//����ƹ�
			result = mpD3D9Device->SetLight( pLight->mIndex, &LightData );
			pLight->mbActived = true;
		}
		else
		{
			//�ͷ�����ֵ
			*mFreeLightIndex.Push() = pLight->mIndex;

			//������ƹ�
			result = mpD3D9Device->SetLight( pLight->mIndex, NULL );
			pLight->mbActived = false;
		}
		
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���õƹ����"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���õƹ�״̬
	void FKFastcall D3D9RenderSystem::_SetLightState( const Light* pLight )
	{
		BOOL nEnable = pLight->mbEnable ? TRUE : FALSE;

		HRESULT result = mpD3D9Device->LightEnable( pLight->mIndex, nEnable );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���õƹ�״̬����"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���û�����
	void FKFastcall D3D9RenderSystem::_SetAmbient( const ColorValue& color )
	{
		HRESULT result = mpD3D9Device->SetRenderState( D3DRS_AMBIENT, color.GetARGB() );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���û��������"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ò�����ɫ��Դ
	void FKFastcall D3D9RenderSystem::_SetMaterialSource( const MaterialSource& refMatSor )
	{
		//������κ���ʹ�ö�����ɫ��Ϊ������Դ
		int eFlag =
			refMatSor.DiffuseSource | refMatSor.SpecularSource |
			refMatSor.AmbientSource | refMatSor.EmissiveSource;

		//������رն�����ɫ״̬
		HRESULT result;
		if( eFlag == 0 )
			result = mpD3D9Device->SetRenderState( D3DRS_COLORVERTEX, FALSE );
		else
			result = mpD3D9Device->SetRenderState( D3DRS_COLORVERTEX, TRUE );

		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���ö�����ɫ״̬����"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

		//���ò�����Դ
		result = mpD3D9Device->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE, (DWORD)refMatSor.DiffuseSource );
		result |= mpD3D9Device->SetRenderState( D3DRS_SPECULARMATERIALSOURCE, (DWORD)refMatSor.SpecularSource );
		result |= mpD3D9Device->SetRenderState( D3DRS_AMBIENTMATERIALSOURCE, (DWORD)refMatSor.AmbientSource );
		result |= mpD3D9Device->SetRenderState( D3DRS_EMISSIVEMATERIALSOURCE, (DWORD)refMatSor.EmissiveSource );

		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���ò�����ɫ��Դ����"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����������״̬
	void FKFastcall D3D9RenderSystem::_SetIndexVertexBlend( const UINT nNumBlendMatrix )
	{
		HRESULT result;

		//���Ҫ����������
		if( nNumBlendMatrix > 0 )
		{
			D3DVERTEXBLENDFLAGS eVertexBlendType;

			switch (nNumBlendMatrix)
			{
			case 1:		eVertexBlendType = D3DVBF_0WEIGHTS;		break;
			case 2:		eVertexBlendType = D3DVBF_1WEIGHTS;		break;
			case 3:		eVertexBlendType = D3DVBF_2WEIGHTS;		break;
			case 4:		eVertexBlendType = D3DVBF_3WEIGHTS;		break;
			default:
				Except( Exception::ERR_INVALIDPARAMS, "�������Ƥ����������" );
			}

			result =	mpD3D9Device->SetRenderState( D3DRS_INDEXEDVERTEXBLENDENABLE, TRUE );
			result |=	mpD3D9Device->SetRenderState( D3DRS_VERTEXBLEND, eVertexBlendType );
		}
		//���Ҫ��ر��������
		else
		{
			result =	mpD3D9Device->SetRenderState( D3DRS_INDEXEDVERTEXBLENDENABLE, FALSE );
			result |=	mpD3D9Device->SetRenderState( D3DRS_VERTEXBLEND, D3DVBF_DISABLE );
		}

		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"�����������״̬����"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ö��㴦��ʽ
	void FKFastcall D3D9RenderSystem::_SetSoftwareVertexProcess( bool bSoftProc )
	{
		if( mbSoftVerProc == bSoftProc || mD3DBehavior == D3DCREATE_SOFTWARE_VERTEXPROCESSING )
			return;

		HRESULT result = mpD3D9Device->SetSoftwareVertexProcessing( bSoftProc ? TRUE : FALSE );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"�л�Ϊ���㴦��ʽʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );

		mbSoftVerProc = bSoftProc;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
