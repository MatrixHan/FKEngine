/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SpriteEmitter
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
	SpriteEmitter::SpriteEmitter( Particle* pParticle )
		: Emitter				( PET_Sprite, pParticle )
		, mpVertexData			(NULL)
		, mpIndexData			(NULL)
		, mNumRenderParticle	(0)
	{
		//���ö�����
		AllocStreamBuf( 1 );

		mppVertexBuffer[0]	= ParticleSystem::mpSingleton->mpVertexBuffer;
		mpIndexBuffer		= ParticleSystem::mpSingleton->mpIndexBuffer;
		mpVertexDeclaration	= ParticleSystem::mpSingleton->mpVertexDeclaration;

		//������Ⱦ����
		AllocRenderParamBuf();
		mpRenderParam->eDrawType				= RenderParam::DT_Basic;

		mpRenderParam->sBasicParam.ePrimType	= PT_TRIANGLE_LIST;
		mpRenderParam->sBasicParam.nMinIndex	= 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	SpriteEmitter::~SpriteEmitter()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ݾ���������Ļ�ռ�����������򶥵�����
	void SpriteEmitter::_ReorderVertexData()
	{
		if( mNumRenderParticle == 0 )
		{
			mbVisable = false;
			return;
		}

		mbVisable = true;
		UINT nNumVertex = mNumRenderParticle * 4;
		static Vertex tmpVertex;

		//�����͸������
		if( !mpRenderParam->pMaterial->mRenderState.mbDepthTestEnable )
		{
			//���մ�Զ������˳������������Ƭ��ѡ�����򷨣�
			for( UINT i=0; i<nNumVertex; i+=4 )
			{
				int nMaxIndex = i;

				for( UINT j=i; j<nNumVertex; j+=4 )
					if( mpVertexData[nMaxIndex].z < mpVertexData[j].z )
						nMaxIndex = j;

				if( nMaxIndex == i )
					continue;

				memcpy( &tmpVertex, &mpVertexData[i], sizeof(Vertex)*4 );
				memcpy( &mpVertexData[i], &mpVertexData[nMaxIndex], sizeof(Vertex)*4 );
				memcpy( &mpVertexData[nMaxIndex], &tmpVertex, sizeof(Vertex)*4 );
			}
		}
		//�������͸������
		else
		{
			//���մӽ���Զ��˳������������Ƭ��ѡ�����򷨣�
			for( UINT i=0; i<nNumVertex; i+=4 )
			{
				int nMinIndex = i;

				for( UINT j=i; j<nNumVertex; j+=4 )
					if( mpVertexData[nMinIndex].z > mpVertexData[j].z )
						nMinIndex = j;

				if( nMinIndex == i )
					continue;

				memcpy( &tmpVertex, &mpVertexData[i], sizeof(Vertex)*4 );
				memcpy( &mpVertexData[i], &mpVertexData[nMinIndex], sizeof(Vertex)*4 );
				memcpy( &mpVertexData[nMinIndex], &tmpVertex, sizeof(Vertex)*4 );
			}
		}

		//������������
		WORD wIndex = 0;
		WORD* pIndexPtr = mpIndexData;
		for( UINT i=0; i<mNumRenderParticle; ++i )
		{
			*pIndexPtr++ = wIndex;
			*pIndexPtr++ = wIndex + 1;
			*pIndexPtr++ = wIndex + 2;
			*pIndexPtr++ = wIndex + 3;
			*pIndexPtr++ = wIndex + 2;
			*pIndexPtr++ = wIndex + 1;
			wIndex += 4;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¾������ӷ�������������
	void SpriteEmitter::_UpdateVertexData( Vertex* pVerBuf, WORD* pIndexBuf, UINT nVertexOffset, UINT nIndexOffset )
	{
		memcpy( pVerBuf, mpVertexData, mNumRenderParticle * sizeof(Vertex) * 4 );
		memcpy( pIndexBuf, mpIndexData, mNumRenderParticle * sizeof(WORD) * 6 );

		mpRenderParam->sBasicParam.nVerOffset	= nVertexOffset;
		mpRenderParam->sBasicParam.nIndexOffset	= nIndexOffset;
		mpRenderParam->sBasicParam.nVerCount	= mNumRenderParticle << 2;
		mpRenderParam->sBasicParam.nPrimCount	= mNumRenderParticle << 1;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
