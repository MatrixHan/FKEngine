/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Geometry
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
	Geometry::Geometry()
		: mbSoftVertexProc		(false)
		, mNumBlendMatrix		(0)
		, mMaxBlendIndex		(0)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	Geometry::~Geometry()
	{
		DeleteAllInstance();

		DelMaterialRef();

		DestroyMeshStream();
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������
	void Geometry::BuildMeshStream( UINT nVerNum, UINT nIndexNum, bool bHaveUV,
		bool bHaveNormal, bool bHaveColor, UINT nNumBlendMatrix, UINT nMaxBlendIndex )
	{
		mNumBlendMatrix	= nNumBlendMatrix;
		mMaxBlendIndex	= nMaxBlendIndex;

		//�ж��Ƿ���Ҫʹ��������㴦��
		DWORD dwHardMaxBlendIndex = bHaveNormal ? ( RenderSystem::mdwMaxBlendIndex / 2 ) : RenderSystem::mdwMaxBlendIndex;
		mbSoftVertexProc = ( dwHardMaxBlendIndex < nMaxBlendIndex || RenderSystem::mdwMaxBlendNum < nNumBlendMatrix );

		//������������
		mpVertexDeclaration = BufferManager::mpSingleton->AddVertexDeclaration();

		//���㶥��������
		UINT nNumVertexBuffer = 1;

		if( bHaveUV )
			++nNumVertexBuffer;
		if( bHaveNormal )
			++nNumVertexBuffer;
		if( bHaveColor )
			++nNumVertexBuffer;

		AllocStreamBuf( nNumVertexBuffer );

		nNumVertexBuffer = 0;

		//����������
		mpVertexDeclaration->AddElement( nNumVertexBuffer, 0, VET_FLOAT3, VEM_DEFAULT, VEU_POSITION, 0 );

		mppVertexBuffer[nNumVertexBuffer] = BufferManager::mpSingleton->AddVertexBuffer();
		mppVertexBuffer[nNumVertexBuffer]->CreateVertexBuffer( sizeof(float)*3, nVerNum, false, mbSoftVertexProc );
		++nNumVertexBuffer;

		//�����Ҫ���ж�����
		if( nNumBlendMatrix > 0 )
		{
			if( nNumBlendMatrix > 4 )
				Except( Exception::ERR_INTERNAL_ERROR, "ÿ������Ĺ��������������� 4 ����" );

			//��Ⱦ��ҪȨ��������ʵ��ֵ��һ
			//����������Ȩ�� 0.6f 0.4f����ֻ��Ҫ���� 0.6f��0.4f ��ͨ�� 1.0 - 0.6f = 0.4f ����õ���
			UINT nNumWeightPerVer = nNumBlendMatrix - 1;

			//�����ҪȨ������
			if( nNumWeightPerVer > 0 )
			{
				//Ȩ����
				VertexElementType vet = (VertexElementType)( nNumWeightPerVer - 1 );

				mpVertexDeclaration->AddElement( nNumVertexBuffer, 0, vet, VEM_DEFAULT, VEU_BLENDWEIGHT, 0 );

				mppVertexBuffer[nNumVertexBuffer] = BufferManager::mpSingleton->AddVertexBuffer();
				mppVertexBuffer[nNumVertexBuffer]->CreateVertexBuffer( sizeof(float)*nNumWeightPerVer, nVerNum,
					false, mbSoftVertexProc );
				++nNumVertexBuffer;
			}

			//��Ͼ���������
			mpVertexDeclaration->AddElement( nNumVertexBuffer, 0, VET_UBYTE4, VEM_DEFAULT, VEU_BLENDINDICES, 0 );

			mppVertexBuffer[nNumVertexBuffer] = BufferManager::mpSingleton->AddVertexBuffer();
			mppVertexBuffer[nNumVertexBuffer]->CreateVertexBuffer( sizeof(DWORD), nVerNum, false, mbSoftVertexProc );
			++nNumVertexBuffer;
		}

		//����������
		if( bHaveNormal )
		{
			mpVertexDeclaration->AddElement( nNumVertexBuffer, 0, VET_FLOAT3, VEM_DEFAULT, VEU_NORMAL, 0 );

			mppVertexBuffer[nNumVertexBuffer] = BufferManager::mpSingleton->AddVertexBuffer();
			mppVertexBuffer[nNumVertexBuffer]->CreateVertexBuffer( sizeof(float)*3, nVerNum, false, mbSoftVertexProc );
			++nNumVertexBuffer;
		}

		//������ɫ��
		if( bHaveColor )
		{
			mpVertexDeclaration->AddElement( nNumVertexBuffer, 0, VET_ARGBCOLOR, VEM_DEFAULT, VEU_COLOR, 0 );

			mppVertexBuffer[nNumVertexBuffer] = BufferManager::mpSingleton->AddVertexBuffer();
			mppVertexBuffer[nNumVertexBuffer]->CreateVertexBuffer( sizeof(DWORD), nVerNum, false, mbSoftVertexProc );
			++nNumVertexBuffer;
		}

		//��������������
		if( bHaveUV )
		{
			mpVertexDeclaration->AddElement( nNumVertexBuffer, 0, VET_FLOAT2, VEM_DEFAULT, VEU_TEXCOORD, 0 );

			mppVertexBuffer[nNumVertexBuffer] = BufferManager::mpSingleton->AddVertexBuffer();
			mppVertexBuffer[nNumVertexBuffer]->CreateVertexBuffer( sizeof(float)*2, nVerNum, false, mbSoftVertexProc );
			++nNumVertexBuffer;
		}


		//��ɶ�����������
		mpVertexDeclaration->CreateVertexDeclaration();

		//����������������
		mpIndexBuffer = BufferManager::mpSingleton->AddIndexBuffer();
		mpIndexBuffer->CreateIndexBuffer( nIndexNum, IT_INDEX16, false, mbSoftVertexProc );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��������
	void Geometry::DestroyMeshStream()
	{
		for( UINT i=0; i<mNumVertexBuffer; ++i )
		{
			if( mppVertexBuffer[i] != NULL )
			{
				BufferManager::mpSingleton->DelVertexBuffer( mppVertexBuffer[i] );
				mppVertexBuffer[i] = NULL;
			}
		}

		if( mpIndexBuffer != NULL )
		{
			BufferManager::mpSingleton->DelIndexBuffer( mpIndexBuffer );
			mpIndexBuffer = NULL;
		}

		if( mpVertexDeclaration != NULL )
		{
			BufferManager::mpSingleton->DelVertexDeclaration( mpVertexDeclaration );
			mpVertexDeclaration = NULL;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ����Ⱦʵ���б�
	void Geometry::InitializeInstanceList( UINT nInitNum, UINT nAddNum )
	{
		mRenderInstList.Initialize( nInitNum, nAddNum );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷ���Ⱦʵ���б�
	void Geometry::ReleaseInstanceList()
	{
		mRenderInstList.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ⱦʵ��
	RenderInstance* Geometry::CreateInstance()
	{
		RenderInstance* pInstance = new RenderInstance( this );
		*mRenderInstList.Push() = pInstance;
		return pInstance;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ָ����Ⱦʵ��
	void Geometry::DeleteInstance( RenderInstance* pInstance )
	{
		RenderInstList::Iterator it = mRenderInstList.Begin();
		RenderInstList::Iterator end = mRenderInstList.End();
		for(; it!=end; ++it )
		{
			if( *it == pInstance )
			{
				mRenderInstList.Erase( it );
				delete *it;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��������Ⱦʵ��
	void Geometry::DeleteAllInstance()
	{
		RenderInstList::Iterator it = mRenderInstList.Begin();
		RenderInstList::Iterator end = mRenderInstList.End();
		for(; it!=end; ++it )
		{
			if( *it != NULL )
				delete *it;
		}

		mRenderInstList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
