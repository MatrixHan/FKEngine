/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SkyBox
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
	SkyBox::SkyBox()
		: mpTopTexture		(NULL)
		, mpFrontTexture	(NULL)
		, mpBackTexture		(NULL)
		, mpLeftTexture		(NULL)
		, mpRightTexture	(NULL)
		, mpVD				(NULL)
		, mpPositionVB		(NULL)
		, mpTexcoordVB		(NULL)
	{
		BufferManager* pBufMgr = BufferManager::GetSingletonPtr();

		//������������
		mpVD = pBufMgr->AddVertexDeclaration();
		mpVD->AddElement( 0, 0, VET_FLOAT3, VEM_DEFAULT, VEU_POSITION, 0 );
		mpVD->AddElement( 1, 0, VET_FLOAT2, VEM_DEFAULT, VEU_TEXCOORD, 0 );
		mpVD->CreateVertexDeclaration();

		//�������㻺��
		mpPositionVB = pBufMgr->AddVertexBuffer();
		mpPositionVB->CreateVertexBuffer( sizeof(float)*3, 20 );

		mpTexcoordVB = pBufMgr->AddVertexBuffer();
		mpTexcoordVB->CreateVertexBuffer( sizeof(float)*2, 20 );

		//���ɶ�����������
		float* pPos = (float*)mpPositionVB->Lock( 0, 0 );

		//����
		*pPos++ = -10.0f;	*pPos++ = 10.0f;	*pPos++ = 10.0f;
		*pPos++ = -10.0f;	*pPos++ = 10.0f;	*pPos++ = -10.0f;
		*pPos++ = 10.0f;	*pPos++ = 10.0f;	*pPos++ = -10.0f;
		*pPos++ = 10.0f;	*pPos++ = 10.0f;	*pPos++ = 10.0f;

		//ǰ��
		*pPos++ = -10.0f;	*pPos++ = -10.0f;	*pPos++ = 10.0f;
		*pPos++ = -10.0f;	*pPos++ = 10.0f;	*pPos++ = 10.0f;
		*pPos++ = 10.0f;	*pPos++ = 10.0f;	*pPos++ = 10.0f;
		*pPos++ = 10.0f;	*pPos++ = -10.0f;	*pPos++ = 10.0f;

		//����
		*pPos++ = 10.0f;	*pPos++ = -10.0f;	*pPos++ = -10.0f;
		*pPos++ = 10.0f;	*pPos++ = 10.0f;	*pPos++ = -10.0f;
		*pPos++ = -10.0f;	*pPos++ = 10.0f;	*pPos++ = -10.0f;
		*pPos++ = -10.0f;	*pPos++ = -10.0f;	*pPos++ = -10.0f;

		//����
		*pPos++ = -10.0f;	*pPos++ = -10.0f;	*pPos++ = -10.0f;
		*pPos++ = -10.0f;	*pPos++ = 10.0f;	*pPos++ = -10.0f;
		*pPos++ = -10.0f;	*pPos++ = 10.0f;	*pPos++ = 10.0f;
		*pPos++ = -10.0f;	*pPos++ = -10.0f;	*pPos++ = 10.0f;

		//����
		*pPos++ = 10.0f;	*pPos++ = -10.0f;	*pPos++ = 10.0f;
		*pPos++ = 10.0f;	*pPos++ = 10.0f;	*pPos++ = 10.0f;
		*pPos++ = 10.0f;	*pPos++ = 10.0f;	*pPos++ = -10.0f;
		*pPos++ = 10.0f;	*pPos++ = -10.0f;	*pPos++ = -10.0f;

		mpPositionVB->Unlock();

		float pUVdata [] =
		{
			0.0f,	1.0f,
			0.0f,	0.0f,
			1.0f,	0.0f,
			1.0f,	1.0f,
		};

		//����������������
		float* pUV = (float*)mpTexcoordVB->Lock( 0, 0 );

		for( UINT i=0; i<5; ++i )
		{
			memcpy( pUV, pUVdata, sizeof(pUVdata) );
			pUV += 8;
		}

		mpTexcoordVB->Unlock();
	}
	//--------------------------------------------------------------------------------------------------------------
	SkyBox::~SkyBox()
	{
		BufferManager* pBufMgr = BufferManager::GetSingletonPtr();

		//�ͷŶ������������㻺��
		pBufMgr->DelVertexDeclaration( mpVD );
		pBufMgr->DelVertexBuffer( mpPositionVB );
		pBufMgr->DelVertexBuffer( mpTexcoordVB );
	}
	//--------------------------------------------------------------------------------------------------------------
	//������պ�����
	void SkyBox::SetSkyBoxTexture( SkyBoxTexture* pSkyBoxTexture )
	{
		mpTopTexture	= pSkyBoxTexture->pTopTexture;
		mpFrontTexture	= pSkyBoxTexture->pFrontTexture;
		mpBackTexture	= pSkyBoxTexture->pBackTexture;
		mpLeftTexture	= pSkyBoxTexture->pLeftTexture;
		mpRightTexture	= pSkyBoxTexture->pRightTexture;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������
	void SkyBox::_UpdateSky( float fTimeSinceLastFrame )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	void SkyBox::_RenderSky()
	{
		//���ݵ�ǰ�������͹ۿ�����
		RenderSystem::mpSingleton->_GetViewMatrix( &mMatViewSave );
		RenderSystem::mpSingleton->_GetWorldMatrix( &mMatWorldSave );

		//������Ⱦ�����Ĺۿ�����ֻ�ı���ۿ�λ�ã�
		mMatView = mMatViewSave;
		mMatView._41 = 0.0f;	mMatView._42 = 0.0f;	mMatView._43 = 0.0f;

		RenderSystem::mpSingleton->_SetViewMatrix( &mMatView );

		//�������������״̬
		_SetTextureState();

		//������Ⱦ�������������
		RenderSystem::mpSingleton->_SetWorldMatrix( &mMatWorld );

		//��������岻͸����Ⱦ״̬
		RenderSystem::mpSingleton->_SetRenderState( &mRenderOpacity );

		//���ö���������Դ�Ͷ�������
		RenderSystem::mpSingleton->_SetVertexStream( mpPositionVB, 0 );
		RenderSystem::mpSingleton->_SetVertexStream( mpTexcoordVB, 1 );
		RenderSystem::mpSingleton->_SetVertexDeclaration( mpVD );

		//��Ⱦ��պ�
		RenderSystem::mpSingleton->_SetTexture( mpTopTexture, 0 );
		RenderSystem::mpSingleton->_RenderVertex( PT_TRIANGLE_FAN, 0, 2 );

		RenderSystem::mpSingleton->_SetTexture( mpFrontTexture, 0 );
		RenderSystem::mpSingleton->_RenderVertex( PT_TRIANGLE_FAN, 4, 2 );

		RenderSystem::mpSingleton->_SetTexture( mpBackTexture, 0 );
		RenderSystem::mpSingleton->_RenderVertex( PT_TRIANGLE_FAN, 8, 2 );

		RenderSystem::mpSingleton->_SetTexture( mpLeftTexture, 0 );
		RenderSystem::mpSingleton->_RenderVertex( PT_TRIANGLE_FAN, 12, 2 );

		RenderSystem::mpSingleton->_SetTexture( mpRightTexture, 0 );
		RenderSystem::mpSingleton->_RenderVertex( PT_TRIANGLE_FAN, 16, 2 );

		//�ָ�ԭ�����������͹ۿ�����
		RenderSystem::mpSingleton->_SetViewMatrix( &mMatViewSave );
		RenderSystem::mpSingleton->_SetWorldMatrix( &mMatWorldSave );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
