/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SkyPlane
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
	SkyPlane::SkyPlane()
		: mpBackgroundTexture	(NULL)
		, mpSurfaceTexture		(NULL)
		, mpVD					(NULL)
		, mpPositionVB			(NULL)
		, mpTexcoordVB			(NULL)
		, mCloudUFactor			(0.005f)
		, mCloudVFactor			(0.005f)
		, mCloudU				(0.0f)
		, mCloudV				(0.0f)
	{
		BufferManager* pBufMgr = BufferManager::GetSingletonPtr();

		//������������
		mpVD = pBufMgr->AddVertexDeclaration();
		mpVD->AddElement( 0, 0, VET_FLOAT3, VEM_DEFAULT, VEU_POSITION, 0 );
		mpVD->AddElement( 1, 0, VET_FLOAT2, VEM_DEFAULT, VEU_TEXCOORD, 0 );
		mpVD->CreateVertexDeclaration();

		//�������㻺��
		mpPositionVB = pBufMgr->AddVertexBuffer();
		mpPositionVB->CreateVertexBuffer( sizeof(float)*3, 8, false );

		mpTexcoordVB = pBufMgr->AddVertexBuffer();
		mpTexcoordVB->CreateVertexBuffer( sizeof(float)*2, 8, true );


		//��ղ��������
		float pRectPos [] =
		{
			-800.0f,	10.0f,		800.0f,		//Զ��
			-800.0f,	10.0f,		-800.0f,	//����
			800.0f,		10.0f,		-800.0f,	//����
			800.0f,		10.0f,		800.0f,		//Զ��
		};

		//���ɶ�������
		float* pPos = (float*)mpPositionVB->Lock( 0, 0 );

		for( UINT i=0; i<2; ++i )
		{
			memcpy( pPos, pRectPos, sizeof(pRectPos) );
			pPos += 12;
		}

		mpPositionVB->Unlock();


		//������������
		float* pUV = mpUV;

		*pUV++ = 0.0f;		*pUV++ = 1.0f;
		*pUV++ = 0.0f;		*pUV++ = 0.0f;
		*pUV++ = 1.0f;		*pUV++ = 0.0f;
		*pUV++ = 1.0f;		*pUV++ = 1.0f;
	}
	//--------------------------------------------------------------------------------------------------------------
	SkyPlane::~SkyPlane()
	{
		BufferManager* pBufMgr = BufferManager::GetSingletonPtr();

		//�ͷŶ������������㻺��
		pBufMgr->DelVertexDeclaration( mpVD );
		pBufMgr->DelVertexBuffer( mpPositionVB );
		pBufMgr->DelVertexBuffer( mpTexcoordVB );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����������
	void SkyPlane::SetSkyTexture( Texture* pBackground, Texture* pSurface )
	{
		mpBackgroundTexture = pBackground;
		mpSurfaceTexture = pSurface;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ƶ�����
	void SkyPlane::SetMoveDirection( float fMoveFront, float fMoveRight )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������
	void SkyPlane::_UpdateSky( float fTimeSinceLastFrame )
	{
		//����ϵ���ı������ UV ֵ
		mCloudU += mCloudUFactor * fTimeSinceLastFrame;
		mCloudV += mCloudVFactor * fTimeSinceLastFrame;

		if( mCloudU > 1.0f )
			mCloudU -= 1.0f;
		else if( mCloudU < -1.0f )
			mCloudU += 1.0f;

		if( mCloudV > 1.0f )
			mCloudV -= 1.0f;
		else if( mCloudV < -1.0f )
			mCloudV += 1.0f;

		//������������
		float* pUV = mpUV;
		pUV += 8;

		*pUV++ = 0.0f + mCloudU;	*pUV++	= 1.0f + mCloudV;
		*pUV++ = 0.0f + mCloudU;	*pUV++	= 0.0f + mCloudV;
		*pUV++ = 1.0f + mCloudU;	*pUV++	= 0.0f + mCloudV;
		*pUV++ = 1.0f + mCloudU;	*pUV	= 1.0f + mCloudV;

		void* pData = mpTexcoordVB->Lock( 0, 0 );
		memcpy( pData, mpUV, sizeof(float)*16 );
		mpTexcoordVB->Unlock();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ�����
	void SkyPlane::_RenderSky()
	{
		//���ݵ�ǰ�������͹ۿ�����
		RenderSystem::mpSingleton->_GetViewMatrix( &mMatViewSave );
		RenderSystem::mpSingleton->_GetWorldMatrix( &mMatWorldSave );

		//������Ⱦ�����Ĺۿ�����ֻ�ı���ۿ�λ�ã�
		mMatView = mMatViewSave;
		mMatView._41 = 0.0f;	mMatView._42 = 0.0f;	mMatView._43 = 0.0f;

		RenderSystem::mpSingleton->_SetViewMatrix( &mMatView );

		//������Ⱦ�������������
		RenderSystem::mpSingleton->_SetWorldMatrix( &mMatWorld );

		//�������������״̬
		_SetTextureState();

		//��������岻͸����Ⱦ״̬
		RenderSystem::mpSingleton->_SetRenderState( &mRenderOpacity );

		//���ö���������Դ�Ͷ�������
		RenderSystem::mpSingleton->_SetVertexStream( mpPositionVB, 0 );
		RenderSystem::mpSingleton->_SetVertexStream( mpTexcoordVB, 1 );
		RenderSystem::mpSingleton->_SetVertexDeclaration( mpVD );

		//��Ⱦ������
		RenderSystem::mpSingleton->_SetTexture( mpBackgroundTexture, 0 );
		RenderSystem::mpSingleton->_RenderVertex( PT_TRIANGLE_FAN, 0, 2 );

		//���������͸����Ⱦ״̬
		RenderSystem::mpSingleton->_SetRenderState( &mRenderTransparent );

		//��Ⱦ���
		RenderSystem::mpSingleton->_SetTexture( mpSurfaceTexture, 0 );

		RenderSystem::mpSingleton->_RenderVertex( PT_TRIANGLE_FAN, 4, 2 );

		//�ָ�ԭ�����������͹ۿ�����
		RenderSystem::mpSingleton->_SetViewMatrix( &mMatViewSave );
		RenderSystem::mpSingleton->_SetWorldMatrix( &mMatWorldSave );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
