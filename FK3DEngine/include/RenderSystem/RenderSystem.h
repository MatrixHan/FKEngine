/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RenderSystem
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

#include "../RenderWrapper/RenderWindow.h"
#include "../RenderWrapper/Light.h"
#include "../RenderWrapper/Material.h"
#include "../RenderWrapper/ConfigDataFormat.h"
#include "Viewport.h"
#include "TextureState.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class SceneManager;
	class Texture;
	class VertexBuffer;
	class IndexBuffer;
	class VertexDeclaration;
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦϵͳ�� �������ࣩ
	class FK_DLL RenderSystem : public Singleton< RenderSystem >
	{
	public:
		friend class SceneManager;

	public:
		RenderSystemType	mSystemType;			//��Ⱦϵͳ����

		bool				mbRun;					//ָʾ��Ⱦϵͳ�Ƿ���������
		RenderWindow*		mpRenderWindow;			//��Ⱦ����ָ��

		RenderSystemCfg*	mpConfig;				//��Ⱦϵͳ������Ϣ

		static bool			mbSoftVerProc;			//�Ƿ�����ʹ��������㴦��ʽ
		static DWORD		mdwDepthMode;			//ʹ����Ȼ���ģʽ
		static DWORD		mdwMaxBlendNum;			//Ӳ��֧�ֶ�����������������
		static DWORD		mdwMaxBlendIndex;		//Ӳ��֧�ֶ�������������������

		static UINT			mnAdpter;				//���������
		static UINT			mRenderWidth;			//��Ⱦ������
		static UINT			mRenderHeight;			//��Ⱦ������

		static PixelFormat	mDisplayFormat;			//��ʾ��ʽ
		static UINT			mDisplayColorDepth;		//��ʾ��ʽɫ���ֽ���
		static UINT			mDisplayAlphaBits;		//��ʾ��ʽ Alpha ֵλ��

		static DWORD		mMaxTextureNum;			//�����������
		static DWORD		mMaxStreamNum;			//��󶥵�������

		static UINT			mNumTriangle;			//��һ֡��Ⱦ��������

		Viewport*			mpViewport;				//��ǰ������ӿ�

		bool				mbUseSwapSrcRect;		//�Ƿ�ʹ����Ⱦҳ�潻����Դ����
		bool				mbUseSwapDestRect;		//�Ƿ�ʹ����Ⱦҳ�潻��Ŀ�����
		RECT				mSwapSrcRect;			//��Ⱦҳ�潻����Դ����
		RECT				mSwapDestRect;			//��Ⱦҳ�潻��Ŀ�����
		HWND				mhSwapDestWindow;		//��Ⱦҳ�潻��Ŀ�괰�ھ��

	protected:
		ViewportList		mViewportList;			//�ӿ��б�

		ULONGStack			mFreeLightIndex;		//���õƹ�����ֵ

		Texture*			mppLastTexture[8];		//����״̬����
		VertexBuffer*		mppLastVB[8];			//������״̬����
		IndexBuffer*		mpLastIB;				//������״̬
		VertexDeclaration*	mpLastVD;				//��������״̬

		RenderState			mRenderState;			//��ǰ��Ⱦ״̬
		TextureState		mpTextureState[8];		//��ǰ����״̬

	public:
		RenderSystem( const RenderSystemType eType );
		virtual ~RenderSystem();

		//������Ⱦϵͳ
		virtual bool Initialize( RenderWindow* pRenderWindow, RenderSystemCfg* pRenderSystemCfg ) = 0;

		//�ر���Ⱦϵͳ
		virtual void Shutdown() = 0;

		//��ȡ�����Դ����ֵ
		virtual UINT GetAvailableTextureMem() = 0;

		//�����ӿ�
		Viewport* CreateViewport( DWORD dwLeft, DWORD dwTop, DWORD dwWidth, DWORD dwHeight,
			float fMinZ = 0.0f, float fMaxZ = 1.0f );

		//ɾ���ӿ�
		void DeleteViewport( Viewport* pViewport );

		//ɾ�������ӿ�
		void DeleteAllViewport();

		//�����ӿ�����
		UINT GetNumViewport();

		//��ȡ��ǰ�����ӿ�
		Viewport* GetActiveViewport();

		//������Ⱦҳ�潻������
		void SetSwapParam( RECT* pSrcRect = NULL, RECT* pDestRect = NULL, HWND hDestWindow = NULL );

		//�����ӿ�
		virtual void FKFastcall _SetViewport( Viewport* pViewport ) = 0;

		//���ù۲����
		virtual void FKFastcall _SetViewMatrix( const Matrix4* pViewMatrix ) = 0;

		//����ͶӰ����
		virtual void FKFastcall _SetProjMatrix( const Matrix4* pProjMatrix ) = 0;

		//��ȡ�۲����
		virtual void FKFastcall _GetViewMatrix( Matrix4* pViewMatrix ) = 0;

		//��ȡͶӰ����
		virtual void FKFastcall _GetProjMatrix( Matrix4* pProjMatrix ) = 0;

		//��ȡ��Ⱦ����
		virtual void FKFastcall _GetWorldMatrix( Matrix4* pWorldMatrix, int nIndex = 0 ) = 0;

		//������Ⱦ����
		virtual void FKFastcall _SetWorldMatrix( const Matrix4* pWorldMatrix, int nIndex = 0 ) = 0;

		//���ò���
		virtual void FKFastcall _SetMaterial( const Material* pMaterial ) = 0;

		//��������
		virtual void FKFastcall _SetTexture( const Texture* pTexture, const DWORD dwStage ) = 0;

		//���ö�������
		virtual void FKFastcall _SetVertexDeclaration( const VertexDeclaration* pVertexDeclaration ) = 0;

		//���ö�����
		virtual void FKFastcall _SetVertexStream( const VertexBuffer* pVertexBuf, const DWORD dwStream ) = 0;

		//����������
		virtual void FKFastcall _SetIndexStream( const IndexBuffer* pIndexBuf ) = 0;

		//��Ⱦ���㣨�������㣩
		virtual void FKFastcall _RenderVertex( PrimitiveType ePrimType, int nVerOffset, UINT nMinIndex,
			UINT nNumVer, UINT nIndexOffset, UINT nPrimCount ) = 0;

		//��Ⱦ����
		virtual void FKFastcall _RenderVertex( PrimitiveType ePrimType, UINT nVerOffset, UINT nPrimCount ) = 0;

		//׼���豸
		virtual void FKFastcall _PrepareDevice() = 0;

		//��ʼ��Ⱦ
		virtual void FKFastcall _BeginRender() = 0;

		//������Ⱦ
		virtual void FKFastcall _EndRender() = 0;

		//������Ⱦҳ��
		virtual void FKFastcall _SwapRenderBuffer() = 0;

		//��ȡ��Ⱦ״̬
		virtual void FKFastcall _GetRenderState( RenderState* pRenderState ) = 0;

		//������Ⱦ״̬
		virtual void FKFastcall _SetRenderState( const RenderState* pRenderState ) = 0;

		//��ȡ����״̬
		virtual void FKFastcall _GetTextureState( TextureState* pTextureState, UINT nStage ) = 0;

		//��������״̬
		virtual void FKFastcall _SetTextureState( const TextureState* pTextureState, UINT nStage ) = 0;

		//�ر�����״̬
		virtual void FKFastcall _DisableTextureState( UINT nStage ) = 0;

		//���ù���״̬
		virtual void FKFastcall _SetLightingState( bool bEnable ) = 0;

		//���ø߹�״̬
		virtual void FKFastcall _SetSpecularState( bool bEnable ) = 0;

		//������״̬
		virtual void FKFastcall _SetFogState( bool bEnable ) = 0;

		//������Ȳ���״̬
		virtual void FKFastcall _SetDepthTestState( bool bEnable ) = 0;

		//�������д��״̬
		virtual void FKFastcall _SetDepthWriteState( bool bEnable ) = 0;

		//���� Alpha ���״̬
		virtual void FKFastcall _SetAlphaState( bool bEnable ) = 0;

		//���� Alpha ����״̬
		virtual void FKFastcall _SetAlphaTestState( bool bEnable ) = 0;

		//���������������
		virtual void FKFastcall _SetTextureFilter( SamplerType eSamplerType, TextureFilterType eFilterType, UINT nStage = 0 ) = 0;

		//��������Ѱַ����
		virtual void FKFastcall _SetTextureAddress( SamplerType eSamplerType, TextureAddressType eAddressType, UINT nStage = 0 ) = 0;

		//����ƹ�
		virtual bool FKFastcall _ActiveLight( Light* pLight, const bool bActive = true ) = 0;

		//���õƹ�״̬
		virtual void FKFastcall _SetLightState( const Light* pLight ) = 0;

		//���û�����
		virtual void FKFastcall _SetAmbient( const ColorValue& color ) = 0;

		//���ò�����ɫ��Դ
		virtual void FKFastcall _SetMaterialSource( const MaterialSource& refMatSor ) = 0;

		//�����������״̬
		virtual void FKFastcall _SetIndexVertexBlend( const UINT nNumBlendMatrix ) = 0;

		//���ö��㴦��ʽ
		virtual void FKFastcall _SetSoftwareVertexProcess( bool bSoftProc ) = 0;
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
