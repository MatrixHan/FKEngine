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
*	�ļ�˵����	D3D9 ��Ⱦϵͳ��
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
struct IDirect3D9;
struct IDirect3DDevice9;
//--------------------------------------------------------------------------------------------------------------

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//D3D9 ��Ⱦϵͳ��
	class FK_DLL D3D9RenderSystem : public RenderSystem
	{
	public:
		static IDirect3D9*				mpD3D9;				// D3D9 ������
		static D3DCAPS9					mD3D9HardCaps;		// D3D9 Ӳ��֧��������Ϣ
		static D3DCAPS9					mD3D9CurCaps;		// D3D9 ��ǰģʽ������Ϣ
		static IDirect3DDevice9*		mpD3D9Device;		// D3D9 �豸

		static D3DDEVTYPE				mDeviceType;		// D3D9 �豸����
		static DWORD					mD3DBehavior;		// D3D9 �豸���㴦��ʽ

		static D3DPRESENT_PARAMETERS	mD3Dpp;				// D3D9 �豸��Ϣ

	public:
		D3D9RenderSystem();
		~D3D9RenderSystem();

		//������Ⱦϵͳ
		bool Initialize( RenderWindow* pRenderWindow, RenderSystemCfg* pRenderSystemCfg );

		//�ر���Ⱦϵͳ
		void Shutdown();

		//��ȡ�����Դ����ֵ
		UINT GetAvailableTextureMem();

	public:
		//�����ʾģʽ�Ƿ����
		PixelFormat _CheckDisplayMode( UINT nAdapter, UINT nWidth, UINT nHeight, PixelFormat ePF, int nRefreshRate );

		//���� D3D9 �豸��Ϣ
		void _SetD3DPresentParam();

		//�ͷ��豸��Դ
		void _InvalidateDeviceObjects();

		//�����豸��Դ
		void _RestoreDeviceObjects();

	public:
		//�����ӿ�
		void FKFastcall _SetViewport( Viewport* pViewport );

		//���ù۲����
		void FKFastcall _SetViewMatrix( const Matrix4* pViewMatrix );

		//����ͶӰ����
		void FKFastcall _SetProjMatrix( const Matrix4* pProjMatrix );

		//������Ⱦ����
		void FKFastcall _SetWorldMatrix( const Matrix4* pWorldMatrix, int nIndex = 0 );

		//��ȡ�۲����
		void FKFastcall _GetViewMatrix( Matrix4* pViewMatrix );

		//��ȡͶӰ����
		void FKFastcall _GetProjMatrix( Matrix4* pProjMatrix );

		//��ȡ��Ⱦ����
		void FKFastcall _GetWorldMatrix( Matrix4* pWorldMatrix, int nIndex = 0 );

		//���ò���
		void FKFastcall _SetMaterial( const Material* pMaterial );

		//��������
		void FKFastcall _SetTexture( const Texture* pTexture, const DWORD dwStage );

		//���ö�������
		void FKFastcall _SetVertexDeclaration( const VertexDeclaration* pVertexDeclaration );

		//���ö�����
		void FKFastcall _SetVertexStream( const VertexBuffer* pVertexBuf, const DWORD dwStream );

		//����������
		void FKFastcall _SetIndexStream( const IndexBuffer* pIndexBuf );

		//��Ⱦ���㣨�������㣩
		void FKFastcall _RenderVertex( PrimitiveType ePrimType, int nVerOffset, UINT nMinIndex,
			UINT nNumVer, UINT nIndexOffset, UINT nPrimCount );

		//��Ⱦ����
		void FKFastcall _RenderVertex( PrimitiveType ePrimType, UINT nVerOffset, UINT nPrimCount );

		//׼���豸
		void FKFastcall _PrepareDevice();

		//��ʼ��Ⱦ
		void FKFastcall _BeginRender();

		//������Ⱦ
		void FKFastcall _EndRender();

		//������Ⱦҳ��
		void FKFastcall _SwapRenderBuffer();

		//��ȡ��Ⱦ״̬
		void FKFastcall _GetRenderState( RenderState* pRenderState );

		//������Ⱦ״̬
		void FKFastcall _SetRenderState( const RenderState* pRenderState );

		//��ȡ����״̬
		void FKFastcall _GetTextureState( TextureState* pTextureState, UINT nStage );

		//��������״̬
		void FKFastcall _SetTextureState( const TextureState* pTextureState, UINT nStage );

		//�ر�����״̬
		void FKFastcall _DisableTextureState( UINT nStage );

		//���ù���״̬
		void FKFastcall _SetLightingState( bool bEnable );

		//���ø߹�״̬
		void FKFastcall _SetSpecularState( bool bEnable );

		//������״̬
		void FKFastcall _SetFogState( bool bEnable );

		//������Ȳ���״̬
		void FKFastcall _SetDepthTestState( bool bEnable );

		//�������д��״̬
		void FKFastcall _SetDepthWriteState( bool bEnable );

		//���� Alpha ���״̬
		void FKFastcall _SetAlphaState( bool bEnable );

		//���� Alpha ����״̬
		void FKFastcall _SetAlphaTestState( bool bEnable );

		//���������������
		void FKFastcall _SetTextureFilter( SamplerType eSamplerType, TextureFilterType eFilterType, UINT nStage = 0 );

		//��������Ѱַ����
		void FKFastcall _SetTextureAddress( SamplerType eSamplerType, TextureAddressType eAddressType, UINT nStage = 0 );

		//����ƹ�
		bool FKFastcall _ActiveLight( Light* pLight, const bool bActive = true );

		//���õƹ�״̬
		void FKFastcall _SetLightState( const Light* pLight );

		//���û�����
		void FKFastcall _SetAmbient( const ColorValue& color );

		//���ò�����ɫ��Դ
		void FKFastcall _SetMaterialSource( const MaterialSource& refMatSor );

		//�����������״̬
		void FKFastcall _SetIndexVertexBlend( const UINT nNumBlendMatrix );

		//���ö��㴦��ʽ
		void FKFastcall _SetSoftwareVertexProcess( bool bSoftProc );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
