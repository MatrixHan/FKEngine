/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	MissileEmitter
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/ParticleSystem/ParticleSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	MissileParticle::MissileParticle( const Param* pParam )
		: Particle		(PT_Sprite)
		, mpMaterial	(pParam->pMaterial)
		, mfLife		(pParam->fLife)
		, mfSize		(pParam->fBeginSize)
		, mnAlpha		(pParam->nBeginAlpha)
	{
		//�������ӱ仯ϵ��
		mfSizeFactor = ( pParam->fEndSize - pParam->fBeginSize ) / pParam->fLife;
		mfAlphaFactor = (float)( pParam->nEndAlpha - pParam->nBeginAlpha ) / pParam->fLife;

		//�������Ӳ���ʹ�ü���
		mpMaterial->AddRef();
	}
	//--------------------------------------------------------------------------------------------------------------
	MissileParticle::~MissileParticle()
	{
		//�������Ӳ���ʹ�ü���
		mpMaterial->DelRef();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���Ӵ�������
	Particle* MissileParticle::Creator( const void* pParam )
	{
		return new MissileParticle( (const Param*)pParam );
	}
	//--------------------------------------------------------------------------------------------------------------
	MissileEmitter::MissileEmitter( const Param* pParam )
		: SpriteEmitter		(pParam->pParticle)
		, mfEmitRate		(pParam->fEmitRate)
		, mfInterval		(0.0f)
	{
		MissileParticle* pParticle = (MissileParticle*)mpParticle;
		UINT nMaxParticle = CeilToInt( pParticle->mfLife / mfEmitRate );

		mParticleData.Initialize( nMaxParticle, nMaxParticle );

		UINT nVertexDataLen = nMaxParticle * ( sizeof(Vertex)*4 + sizeof(WORD)*6 );
		mVertexData.Initialize( nVertexDataLen, nVertexDataLen );

		//������Ⱦ����
		AllocMaterialBuf();
		mppMaterial[0] = pParticle->mpMaterial;

		mpRenderParam->pMaterial = pParticle->mpMaterial;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ӷ�������������
	Emitter* MissileEmitter::Creator( const void* pParam )
	{
		return new MissileEmitter( (const Param*)pParam );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���·�����
	void MissileEmitter::_UpdateEmitter( const float fFrameTime )
	{
		MissileParticle* pParticle = (MissileParticle*)mpParticle;

		//������������
		const float fSizeFactor = pParticle->mfSizeFactor;
		const float fAlphaFactor = pParticle->mfAlphaFactor;

		UINT nNumDead = 0;

		DataStack::Iterator it = mParticleData.Begin();
		DataStack::Iterator end = mParticleData.End();
		for(; it!=end; ++it )
		{
			Data* pData = it;

			//���㵱ǰ��������
			pData->fLifeTime += fFrameTime;
			const float fLifeTime = pData->fLifeTime;

			//�������������
			if( fLifeTime >= pParticle->mfLife )
			{
				++nNumDead;
				continue;
			}

			//����ߴ�
			pData->fSize = pParticle->mfSize + fSizeFactor * fLifeTime;

			//����͸��ֵ
			pData->nAlpha = pParticle->mnAlpha + FloorToInt( fAlphaFactor * fLifeTime );
		}

		//ɾ����������
		mParticleData.PopFront( nNumDead );

		mNumParticle = mParticleData.Size();

		//����֡��ʱ
		mfInterval += fFrameTime;

		//���֡��ʱ������������ʱ��
		while( mfInterval >= mfEmitRate )
		{
			mfInterval -= mfEmitRate;

			//���ʣ��ʱ��С����������
			if( mfInterval < pParticle->mfLife )
			{
				//�����µ�����
				Data* pData = mParticleData.Push();

				pData->fLifeTime = mfInterval;

				pData->vPosition.x = 0.0f;
				pData->vPosition.y = 10.0f;
				pData->vPosition.z = 0.0f;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¾������ӷ���
	UINT MissileEmitter::_UpdateSprite( const Camera* pCamera )
	{
		//���¶�������
		mVertexData.Clear();

		//���㶥��任����
		static Matrix4 TransformMat;
		static Vector4 vTransPos;
		const Viewport* pViewport = RenderSystem::mpSingleton->mpViewport;

		TransformMat = mpSceneNode->mWorldMatrix;
		TransformMat *= pCamera->mViewProjMatrix;
		TransformMat *= pViewport->mViewportMat;

		//����ÿ�����ӵĶ�������
		mNumRenderParticle = 0;
		Data* pData = mParticleData.Begin();
		for( UINT i=0; i<mNumParticle; ++i, ++pData )
		{
			//������ɫֵ
			const DWORD dwAlpha = ( (DWORD)pData->nAlpha ) << 24;
			DWORD dwColor = 0x00FFFFFF | dwAlpha;

			//ת���������굽��Ļ�ռ�
			vTransPos = pData->vPosition;
			vTransPos.z = 20.0f * pData->fLifeTime;

			vTransPos *= TransformMat;

			const float fInvW = 1.0f / vTransPos.w;
			vTransPos.x *= fInvW;
			vTransPos.y *= fInvW;
			vTransPos.z *= fInvW;
			vTransPos.w = fInvW;

			//�������Ӵ�С
			const float fDist = ( pData->vPosition - pCamera->mViewPos ).GetLength();
			const float fHalfSize = pViewport->mHeight * pData->fSize * 0.5f / fDist; 

			//����������Ļ������вü�
			if( vTransPos.x < pViewport->mLeft - fHalfSize || vTransPos.x > pViewport->mWidth + fHalfSize ||
				vTransPos.y < pViewport->mLeft - fHalfSize || vTransPos.y > pViewport->mHeight + fHalfSize ||
				vTransPos.z < pViewport->mMinZ || vTransPos.z > pViewport->mMaxZ )
				continue;

			//����µ����Ӷ�������
			++mNumRenderParticle;
			Vertex* pVertexPtr = (Vertex*)mVertexData.Push( sizeof(Vertex)*4 );

			//���½�
			pVertexPtr[0].x = vTransPos.x - fHalfSize;
			pVertexPtr[0].y = vTransPos.y + fHalfSize;
			pVertexPtr[0].z = vTransPos.z;
			pVertexPtr[0].w = vTransPos.w;
			pVertexPtr[0].fU = 0.0f;
			pVertexPtr[0].fV = 1.0f;
			pVertexPtr[0].dwColor = dwColor;

			//���Ͻ�
			pVertexPtr[1].x = vTransPos.x - fHalfSize;
			pVertexPtr[1].y = vTransPos.y - fHalfSize;
			pVertexPtr[1].z = vTransPos.z;
			pVertexPtr[1].w = vTransPos.w;
			pVertexPtr[1].fU = 0.0f;
			pVertexPtr[1].fV = 0.0f;
			pVertexPtr[1].dwColor = dwColor;

			//���½�
			pVertexPtr[2].x = vTransPos.x + fHalfSize;
			pVertexPtr[2].y = vTransPos.y + fHalfSize;
			pVertexPtr[2].z = vTransPos.z;
			pVertexPtr[2].w = vTransPos.w;
			pVertexPtr[2].fU = 1.0f;
			pVertexPtr[2].fV = 1.0f;
			pVertexPtr[2].dwColor = dwColor;

			//���Ͻ�
			pVertexPtr[3].x = vTransPos.x + fHalfSize;
			pVertexPtr[3].y = vTransPos.y - fHalfSize;
			pVertexPtr[3].z = vTransPos.z;
			pVertexPtr[3].w = vTransPos.w;
			pVertexPtr[3].fU = 1.0f;
			pVertexPtr[3].fV = 0.0f;
			pVertexPtr[3].dwColor = dwColor;
		}

		//�洢��������ָ��
		mpIndexData = (WORD*)mVertexData.Push( mNumRenderParticle * sizeof(WORD) * 6 );
		mpVertexData = (Vertex*)mVertexData.Begin();

		_ReorderVertexData();

		if( mNumRenderParticle == 0 )
			mpRenderParam->sBasicParam.nPrimCount = 0;

		return mNumRenderParticle;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
