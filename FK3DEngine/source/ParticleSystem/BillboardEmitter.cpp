/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BillboardEmitter
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
	BillboardParticle::BillboardParticle( const Param* pParam )
		: Particle		(PT_Sprite)
		, mpMaterial	(pParam->pMaterial)
		, mfSizeX		(pParam->fSizeX)
		, mfSizeY		(pParam->fSizeY)
	{
		//�������Ӳ���ʹ�ü���
		mpMaterial->AddRef();
	}
	//--------------------------------------------------------------------------------------------------------------
	BillboardParticle::~BillboardParticle()
	{
		//�������Ӳ���ʹ�ü���
		mpMaterial->DelRef();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���Ӵ�������
	Particle* BillboardParticle::Creator( const void* pParam )
	{
		return new BillboardParticle( (const Param*)pParam );
	}
	//--------------------------------------------------------------------------------------------------------------
	BillboardEmitter::BillboardEmitter( const Param* pParam )
		: SpriteEmitter		(pParam->pParticle)
		, mpParticleData	(NULL)
	{
		BillboardParticle* pParticle = (BillboardParticle*)pParam->pParticle;
		mNumParticle = pParam->nNumBillboard;

		//���ƹ������������
		mpParticleData = (Vector3*)malloc( mNumParticle * ( sizeof(Vector3) +
			sizeof(Vertex) * 4 + sizeof(WORD) * 6 ) );
		mpVertexData = (Vertex*)( mpParticleData + mNumParticle );
		mpIndexData = (WORD*)( mpVertexData + mNumParticle * 4 );

		memcpy( mpParticleData, pParam->pPosition, mNumParticle * sizeof(Vector3) );

		//����̶���������
		WORD wIndex = 0;
		Vertex* pVertexPtr = mpVertexData;
		WORD* pIndexPtr = mpIndexData;
		for( UINT i=0; i<mNumParticle; ++i )
		{
			pVertexPtr->fU = 0.0f;	pVertexPtr->fV = 1.0f;	pVertexPtr->dwColor = 0xFFFFFFFF;	++pVertexPtr;	//���½�
			pVertexPtr->fU = 0.0f;	pVertexPtr->fV = 0.0f;	pVertexPtr->dwColor = 0xFFFFFFFF;	++pVertexPtr;	//���Ͻ�
			pVertexPtr->fU = 1.0f;	pVertexPtr->fV = 1.0f;	pVertexPtr->dwColor = 0xFFFFFFFF;	++pVertexPtr;	//���½�
			pVertexPtr->fU = 1.0f;	pVertexPtr->fV = 0.0f;	pVertexPtr->dwColor = 0xFFFFFFFF;	++pVertexPtr;	//���Ͻ�

			*pIndexPtr++ = wIndex;
			*pIndexPtr++ = wIndex + 1;
			*pIndexPtr++ = wIndex + 2;
			*pIndexPtr++ = wIndex + 3;
			*pIndexPtr++ = wIndex + 2;
			*pIndexPtr++ = wIndex + 1;

			wIndex += 4;
		}

		//������Ⱦ����
		AllocMaterialBuf();
		mppMaterial[0] = pParticle->mpMaterial;

		mpRenderParam->pMaterial = pParticle->mpMaterial;
	}
	//--------------------------------------------------------------------------------------------------------------
	BillboardEmitter::~BillboardEmitter()
	{
		SafeFree( mpParticleData );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ӷ�������������
	Emitter* BillboardEmitter::Creator( const void* pParam )
	{
		return new BillboardEmitter( (const Param*)pParam );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���·�����
	void BillboardEmitter::_UpdateEmitter( const float fFrameTime )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¾������ӷ���
	UINT BillboardEmitter::_UpdateSprite( const Camera* pCamera )
	{
		BillboardParticle* pParticle = (BillboardParticle*)mpParticle;

		//��������任����
		static Matrix4 TransformMat;
		static Vector3 vWorldPos;
		static Vector4 vTransPos;
		const Viewport* pViewport = RenderSystem::mpSingleton->mpViewport;

		TransformMat = pCamera->mViewProjMatrix;
		TransformMat *= pViewport->mViewportMat;

		//���㹫�����ת����
		float fHalfSizeX = pParticle->mfSizeX * 0.5f;
		float fHalfSizeY = pParticle->mfSizeY * 0.5f;

		float fViewX = pCamera->mViewPos.x;
		float fViewZ = pCamera->mViewPos.z;

		//���㹫��嶥������
		Vector3* pPosPtr = mpParticleData;
		Vertex* pVertexPtr = mpVertexData;
		for( UINT i=0; i<mNumParticle; ++i )
		{
			//ת������嶥��λ�õ�����ռ�
			vWorldPos = *pPosPtr;
			vWorldPos *= mpSceneNode->mWorldMatrix;

			//���㹫�����ת�󶥵�����
			float fTransAngle = ATan( fViewX - vWorldPos.x, vWorldPos.z - fViewZ );
			float fSin, fCos;
			SinCos( fTransAngle, &fSin, &fCos );

			float fFactorX = fHalfSizeX * fCos;
			float fFactorZ = fHalfSizeX * fSin;

			//���½�
			vTransPos.x = vWorldPos.x - fFactorX;
			vTransPos.y = vWorldPos.y - fHalfSizeY;
			vTransPos.z = vWorldPos.z - fFactorZ;
			vTransPos.w = 1.0f;
			vTransPos *= TransformMat;
			float fInvW = 1.0f / vTransPos.w;

			pVertexPtr->x = vTransPos.x * fInvW;
			pVertexPtr->y = vTransPos.y * fInvW;
			pVertexPtr->z = vTransPos.z * fInvW;
			pVertexPtr->w = fInvW;
			++pVertexPtr;

			//���Ͻ�
			vTransPos.x = vWorldPos.x - fFactorX;
			vTransPos.y = vWorldPos.y + fHalfSizeY;
			vTransPos.z = vWorldPos.z - fFactorZ;
			vTransPos.w = 1.0f;
			vTransPos *= TransformMat;
			fInvW = 1.0f / vTransPos.w;

			pVertexPtr->x = vTransPos.x * fInvW;
			pVertexPtr->y = vTransPos.y * fInvW;
			pVertexPtr->z = vTransPos.z * fInvW;
			pVertexPtr->w = fInvW;
			++pVertexPtr;

			//���½�
			vTransPos.x = vWorldPos.x + fFactorX;
			vTransPos.y = vWorldPos.y - fHalfSizeY;
			vTransPos.z = vWorldPos.z + fFactorZ;
			vTransPos.w = 1.0f;
			vTransPos *= TransformMat;
			fInvW = 1.0f / vTransPos.w;

			pVertexPtr->x = vTransPos.x * fInvW;
			pVertexPtr->y = vTransPos.y * fInvW;
			pVertexPtr->z = vTransPos.z * fInvW;
			pVertexPtr->w = fInvW;
			++pVertexPtr;

			//���Ͻ�
			vTransPos.x = vWorldPos.x + fFactorX;
			vTransPos.y = vWorldPos.y + fHalfSizeY;
			vTransPos.z = vWorldPos.z + fFactorZ;
			vTransPos.w = 1.0f;
			vTransPos *= TransformMat;
			fInvW = 1.0f / vTransPos.w;

			pVertexPtr->x = vTransPos.x * fInvW;
			pVertexPtr->y = vTransPos.y * fInvW;
			pVertexPtr->z = vTransPos.z * fInvW;
			pVertexPtr->w = fInvW;
			++pVertexPtr;

			++pPosPtr;
		}

		mNumRenderParticle = mNumParticle;
		_ReorderVertexData();

		return mNumRenderParticle;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
