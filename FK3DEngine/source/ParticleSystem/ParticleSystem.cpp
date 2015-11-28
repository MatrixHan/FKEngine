/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ParticleSystem
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
	ParticleSystem::ParticleSystem( UINT nMaxNumSpriteParticle )
		: mpVertexBuffer		(NULL)
		, mpIndexBuffer			(NULL)
		, mpVertexDeclaration	(NULL)
		, mMaxNumSParticle		(nMaxNumSpriteParticle)
		, mOffsetSParticle		(0)
		, mRenderSParticle		(0)
	{
		mParticleList.Initialize( 10, 10 );
		mEmitterList.Initialize( 60, 20 );

		//�������Ӷ�������
		mpVertexDeclaration = BufferManager::mpSingleton->AddVertexDeclaration();

		mpVertexDeclaration->AddElement( 0, 0, VET_FLOAT4, VEM_DEFAULT, VEU_POSITIONT, 0 );
		mpVertexDeclaration->AddElement( 0, 16, VET_ARGBCOLOR, VEM_DEFAULT, VEU_COLOR, 0 );
		mpVertexDeclaration->AddElement( 0, 20, VET_FLOAT2, VEM_DEFAULT, VEU_TEXCOORD, 0 );
		mpVertexDeclaration->CreateVertexDeclaration();

		//�������Ӷ��㻺�����������
		mpVertexBuffer = BufferManager::mpSingleton->AddVertexBuffer();
		mpIndexBuffer = BufferManager::mpSingleton->AddIndexBuffer();

		mpVertexBuffer->CreateVertexBuffer( sizeof(SpriteEmitter::Vertex), nMaxNumSpriteParticle * 4, true );
		mpIndexBuffer->CreateIndexBuffer( nMaxNumSpriteParticle * 6, IT_INDEX16, true );
	}
	//--------------------------------------------------------------------------------------------------------------
	ParticleSystem::~ParticleSystem()
	{
		DeleteAllParticle();
		DeleteAllEmitter();

		mParticleList.Release();
		mEmitterList.Release();

		if( mpIndexBuffer != NULL )
		{
			BufferManager::mpSingleton->DelIndexBuffer( mpIndexBuffer );
			mpIndexBuffer = NULL;
		}

		if( mpVertexBuffer != NULL )
		{
			BufferManager::mpSingleton->DelVertexBuffer( mpVertexBuffer );
			mpVertexBuffer = NULL;
		}

		if( mpVertexDeclaration != NULL )
		{
			BufferManager::mpSingleton->DelVertexDeclaration( mpVertexDeclaration );
			mpVertexDeclaration = NULL;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	Particle* ParticleSystem::CreateParticle( Particle::FnCreator fnCreator, void* pParam )
	{
		Particle* pParticle = fnCreator( pParam );
		*mParticleList.Push() = pParticle;
		return pParticle;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ������
	void ParticleSystem::DeleteParticle( Particle* pParticle )
	{
		if( pParticle == NULL )
			return;

		ParticleList::Iterator it = mParticleList.Begin();
		ParticleList::Iterator end = mParticleList.End();
		for(; it!=end; ++it )
		{
			if( *it == pParticle )
			{
				mParticleList.Erase( it );
				delete pParticle;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ����������
	void ParticleSystem::DeleteAllParticle()
	{
		ParticleList::Iterator it = mParticleList.Begin();
		ParticleList::Iterator end = mParticleList.End();
		for(; it!=end; ++it )
		{
			if( *it != NULL )
				delete *it;
		}

		mParticleList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������ӷ�����
	Emitter* ParticleSystem::CreateEmitter( Emitter::FnCreator fnCreator, void* pParam )
	{
		Emitter* pEmitter = fnCreator( pParam );
		*mEmitterList.Push() = pEmitter;
		return pEmitter;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����ӷ�����
	void ParticleSystem::DeleteEmitter( Emitter* pEmitter )
	{
		if( pEmitter == NULL )
			return;

		EmitterList::Iterator it = mEmitterList.Begin();
		EmitterList::Iterator end = mEmitterList.End();
		for(; it!=end; ++it )
		{
			if( *it == pEmitter )
			{
				mEmitterList.Erase( it );
				delete pEmitter;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ���������ӷ�����
	void ParticleSystem::DeleteAllEmitter()
	{
		EmitterList::Iterator it = mEmitterList.Begin();
		EmitterList::Iterator end = mEmitterList.End();
		for(; it!=end; ++it )
		{
			if( *it != NULL )
				delete *it;
		}

		mEmitterList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���·�����
	void ParticleSystem::_UpdateEmitter( float fFrameTime )
	{
		//�����������ӷ�����
		EmitterList::Iterator it = mEmitterList.Begin();
		EmitterList::Iterator end = mEmitterList.End();
		for(; it!=end; ++it )
		{
			//�������ӷ�����
			(*it)->_UpdateEmitter( fFrameTime );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¾������ӷ���
	void ParticleSystem::_UpdateSprite( const Camera* pCamera )
	{
		mRenderSParticle = 0;

		//���¾���������Ⱦ����
		EmitterList::Iterator begin = mEmitterList.Begin();
		EmitterList::Iterator end = mEmitterList.End();
		for( EmitterList::Iterator it=begin; it!=end; ++it )
		{
			Emitter* pEmitter = *it;

			//����Ǿ������ӷ�����
			if( pEmitter->mType == Emitter::PET_Sprite )
			{
				//�������δ�ҽ��ڳ����ڵ��������Ϊ����ֱ���Թ�
				if( pEmitter->mpSceneNode == NULL || pEmitter->mNumParticle == 0 )
				{
					pEmitter->mbVisable = false;
					continue;
				}

				//����������Ⱦ����
				SpriteEmitter* pSpriteEmitter = reinterpret_cast< SpriteEmitter* >( pEmitter );
				mRenderSParticle += pSpriteEmitter->_UpdateSprite( pCamera );
			}
		}

		//���û����Ҫ��Ⱦ�ľ��������򷵻�
		if( mRenderSParticle == 0 )
			return;

		//���������������򷵻���ʼλ����������������һ֡ʹ�� D3DLOCK_DISCARD ������
		bool bNoOverwrite = true;
		if( mOffsetSParticle + mRenderSParticle > mMaxNumSParticle )
		{
			mOffsetSParticle = 0;
			bNoOverwrite = false;
		}

		//�������㻺�����������
		UINT nVertexOffset = mOffsetSParticle * 4;
		UINT nIndexOffset = mOffsetSParticle * 6;

		SpriteEmitter::Vertex* pVertexPtr = (SpriteEmitter::Vertex*)mpVertexBuffer->Lock( nVertexOffset,
			mRenderSParticle * 4, bNoOverwrite );

		WORD* pIndexPtr = (WORD*)mpIndexBuffer->Lock( nIndexOffset, mRenderSParticle * 6, bNoOverwrite );

		//���ƾ������Ӷ�������
		for( EmitterList::Iterator it=begin; it!=end; ++it )
		{
			Emitter* pEmitter = *it;

			//����Ǿ������ӷ�����
			if( pEmitter->mType == Emitter::PET_Sprite )
			{
				SpriteEmitter* pSpriteEmitter = reinterpret_cast< SpriteEmitter* >( pEmitter );

				//������Ӳ��ɼ����Թ�
				if( !pSpriteEmitter->mbVisable )
					continue;

				//�������Ӷ�������
				pSpriteEmitter->_UpdateVertexData( pVertexPtr, pIndexPtr, nVertexOffset, nIndexOffset );

				//��������ƫ����
				UINT nNumVertex = pSpriteEmitter->mNumRenderParticle * 4;
				UINT nNumIndex = pSpriteEmitter->mNumRenderParticle * 6;

				pVertexPtr += nNumVertex;
				pIndexPtr += nNumIndex;

				nVertexOffset += nNumVertex;
				nIndexOffset += nNumIndex;
			}
		}

		//�������㻺�����������
		mpVertexBuffer->Unlock();
		mpIndexBuffer->Unlock();

		mOffsetSParticle += mRenderSParticle;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
