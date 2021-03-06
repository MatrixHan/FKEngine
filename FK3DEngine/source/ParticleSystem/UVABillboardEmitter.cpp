/********************************************************************
*
*	本文件是FKMMORPG的一部分。本文件版权归属FreeKnightDuzhi(王宏张)所有。
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	文件名：	UVABillboardEmitter
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*
*	修改人:		
*	修改内容:
*********************************************************************/

#include "../../include/ParticleSystem/ParticleSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	UVABillboardParticle::UVABillboardParticle( const Param* pParam )
		: Particle		(PT_Sprite)
		, mpMaterial	(pParam->pMaterial)
		, mfSizeX		(pParam->fSizeX)
		, mfSizeY		(pParam->fSizeY)
	{
		//增加粒子材质使用计数
		mpMaterial->AddRef();

		//载入 UV 动画数据
		mpUVAnimation = UVAManager::mpSingleton->CreateUVAnimation( pParam->pUVAFileName );
	}
	//--------------------------------------------------------------------------------------------------------------
	UVABillboardParticle::~UVABillboardParticle()
	{
		//减少粒子材质使用计数
		mpMaterial->DelRef();

		//删除 UV 动画数据
		UVAManager::mpSingleton->DeleteUVAnimation( mpUVAnimation );
	}
	//--------------------------------------------------------------------------------------------------------------
	//粒子创建函数
	Particle* UVABillboardParticle::Creator( const void* pParam )
	{
		return new UVABillboardParticle( (const Param*)pParam );
	}
	//--------------------------------------------------------------------------------------------------------------
	UVABillboardEmitter::UVABillboardEmitter( const Param* pParam )
		: SpriteEmitter		(pParam->pParticle)
		, mpParticleData	(NULL)
	{
		UVABillboardParticle* pUVAParticle = (UVABillboardParticle*)pParam->pParticle;
		mNumParticle = pParam->nNumBillboard;

		//设置 UV 动画数据
		mUVAControl.SetUVAnimation( pUVAParticle->mpUVAnimation );

		//复制公告板坐标数据
		mpParticleData = (Vector3*)malloc( mNumParticle * ( sizeof(Vector3) +
			sizeof(Vertex) * 4 + sizeof(WORD) * 6 ) );
		mpVertexData = (Vertex*)( mpParticleData + mNumParticle );
		mpIndexData = (WORD*)( mpVertexData + mNumParticle * 4 );

		memcpy( mpParticleData, pParam->pPosition, mNumParticle * sizeof(Vector3) );

		//计算固定顶点数据
		WORD wIndex = 0;
		Vertex* pVertexPtr = mpVertexData;
		WORD* pIndexPtr = mpIndexData;
		for( UINT i=0; i<mNumParticle; ++i )
		{
			pVertexPtr[0].dwColor = 0xFFFFFFFF;
			pVertexPtr[1].dwColor = 0xFFFFFFFF;
			pVertexPtr[2].dwColor = 0xFFFFFFFF;
			pVertexPtr[3].dwColor = 0xFFFFFFFF;
			pVertexPtr += 4;

			*pIndexPtr++ = wIndex;
			*pIndexPtr++ = wIndex + 1;
			*pIndexPtr++ = wIndex + 2;
			*pIndexPtr++ = wIndex + 3;
			*pIndexPtr++ = wIndex + 2;
			*pIndexPtr++ = wIndex + 1;

			wIndex += 4;
		}

		//设置渲染参数
		AllocMaterialBuf();
		mppMaterial[0] = pUVAParticle->mpMaterial;

		mpRenderParam->pMaterial = pUVAParticle->mpMaterial;
	}
	//--------------------------------------------------------------------------------------------------------------
	UVABillboardEmitter::~UVABillboardEmitter()
	{
		SafeFree( mpParticleData );
	}
	//--------------------------------------------------------------------------------------------------------------
	//粒子发射器创建函数
	Emitter* UVABillboardEmitter::Creator( const void* pParam )
	{
		return new UVABillboardEmitter( (const Param*)pParam );
	}
	//--------------------------------------------------------------------------------------------------------------
	//更新发射器
	void UVABillboardEmitter::_UpdateEmitter( const float fFrameTime )
	{
		//更新 UV 动画帧
		mUVAControl.UpdateFrameTime( fFrameTime );
	}
	//--------------------------------------------------------------------------------------------------------------
	//更新精灵粒子方向
	UINT UVABillboardEmitter::_UpdateSprite( const Camera* pCamera )
	{
		UVABillboardParticle* pParticle = (UVABillboardParticle*)mpParticle;

		const UV4* pUV = mUVAControl.GetCurrentUV();

		//计算坐标变换矩阵
		static Matrix4 TransformMat;
		static Vector3 vWorldPos;
		static Vector4 vTransPos;
		const Viewport* pViewport = RenderSystem::mpSingleton->mpViewport;

		TransformMat = pCamera->mViewProjMatrix;
		TransformMat *= pViewport->mViewportMat;

		//计算公告板旋转方向
		float fHalfSizeX = pParticle->mfSizeX * 0.5f;
		float fHalfSizeY = pParticle->mfSizeY * 0.5f;

		float fViewX = pCamera->mViewPos.x;
		float fViewZ = pCamera->mViewPos.z;

		//计算公告板顶点数据
		Vector3* pPosPtr = mpParticleData;
		Vertex* pVertexPtr = mpVertexData;
		for( UINT i=0; i<mNumParticle; ++i )
		{
			//转换公告板顶点位置到世界空间
			vWorldPos = *pPosPtr;
			vWorldPos *= mpSceneNode->mWorldMatrix;

			//计算公告板旋转后顶点坐标
			float fTransAngle = ATan( fViewX - vWorldPos.x, vWorldPos.z - fViewZ );
			float fSin, fCos;
			SinCos( fTransAngle, &fSin, &fCos );

			float fFactorX = fHalfSizeX * fCos;
			float fFactorZ = fHalfSizeX * fSin;

			//左下角
			vTransPos.x = vWorldPos.x - fFactorX;
			vTransPos.y = vWorldPos.y - fHalfSizeY;
			vTransPos.z = vWorldPos.z - fFactorZ;
			vTransPos.w = 1.0f;
			vTransPos *= TransformMat;
			float fInvW = 1.0f / vTransPos.w;

			pVertexPtr->fU = pUV->u1;		pVertexPtr->fV = pUV->v2;
			pVertexPtr->x = vTransPos.x * fInvW;
			pVertexPtr->y = vTransPos.y * fInvW;
			pVertexPtr->z = vTransPos.z * fInvW;
			pVertexPtr->w = fInvW;
			++pVertexPtr;

			//左上角
			vTransPos.x = vWorldPos.x - fFactorX;
			vTransPos.y = vWorldPos.y + fHalfSizeY;
			vTransPos.z = vWorldPos.z - fFactorZ;
			vTransPos.w = 1.0f;
			vTransPos *= TransformMat;
			fInvW = 1.0f / vTransPos.w;

			pVertexPtr->fU = pUV->u1;		pVertexPtr->fV = pUV->v1;
			pVertexPtr->x = vTransPos.x * fInvW;
			pVertexPtr->y = vTransPos.y * fInvW;
			pVertexPtr->z = vTransPos.z * fInvW;
			pVertexPtr->w = fInvW;
			++pVertexPtr;

			//右下角
			vTransPos.x = vWorldPos.x + fFactorX;
			vTransPos.y = vWorldPos.y - fHalfSizeY;
			vTransPos.z = vWorldPos.z + fFactorZ;
			vTransPos.w = 1.0f;
			vTransPos *= TransformMat;
			fInvW = 1.0f / vTransPos.w;

			pVertexPtr->fU = pUV->u2;		pVertexPtr->fV = pUV->v2;
			pVertexPtr->x = vTransPos.x * fInvW;
			pVertexPtr->y = vTransPos.y * fInvW;
			pVertexPtr->z = vTransPos.z * fInvW;
			pVertexPtr->w = fInvW;
			++pVertexPtr;

			//右上角
			vTransPos.x = vWorldPos.x + fFactorX;
			vTransPos.y = vWorldPos.y + fHalfSizeY;
			vTransPos.z = vWorldPos.z + fFactorZ;
			vTransPos.w = 1.0f;
			vTransPos *= TransformMat;
			fInvW = 1.0f / vTransPos.w;

			pVertexPtr->fU = pUV->u2;		pVertexPtr->fV = pUV->v1;
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
