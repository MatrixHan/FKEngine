/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RenderQueue
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
	RenderQueue::RenderQueue()
	{
		mRenderUnitStack.Initialize( 1000, 1000 );
		mRenderGroupStack.Initialize( 20, 20 );
		mRenderSubGroupStack.Initialize( 200, 200 );
	}
	//--------------------------------------------------------------------------------------------------------------
	RenderQueue::~RenderQueue()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����Ⱦ����
	void RenderQueue::ClearRenderQueue()
	{
		mRenderUnitStack.Clear();
		mRenderGroupStack.Clear();
		mRenderSubGroupStack.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ⱦ����
	void RenderQueue::SortRenderQueue( const Camera* pCamera )
	{
		//������Ⱦ�����ȼ�������Ⱦ��Ԫ��ѡ�����򷨣�
		RenderUnit* pUnit = mRenderUnitStack.Begin();
		UINT nNumUnit = mRenderUnitStack.Size();

		if( nNumUnit == 0 )
			return;

		for( UINT i=0; i<nNumUnit; ++i )
		{
			int nMinIndex = i;

			for( UINT j=i; j<nNumUnit; ++j )
				if( pUnit[nMinIndex].pRenderInstance->mnGroupPriority > pUnit[j].pRenderInstance->mnGroupPriority )
					nMinIndex = j;

			SwapRenderUnit( pUnit + i, pUnit + nMinIndex );
		}

		//������Ⱦ��
		RenderGroup* pGroup = mRenderGroupStack.Push();

		pGroup->mnPriority = pUnit->pRenderInstance->mnGroupPriority;
		pGroup->mpHeadRenderUnit = pUnit;
		pGroup->mpRearRenderUnit = pUnit;

		for( UINT i=1; i<nNumUnit; ++i )
		{
			if( pUnit[i].pRenderInstance->mnGroupPriority == pGroup->mnPriority )
			{
				pGroup->mpRearRenderUnit += 1;
			}
			else
			{
				pGroup->SortRenderGroup( &mRenderSubGroupStack, pCamera );

				pGroup = mRenderGroupStack.Push();

				pGroup->mnPriority = pUnit->pRenderInstance->mnGroupPriority;
				pGroup->mpHeadRenderUnit = pUnit + i;
				pGroup->mpRearRenderUnit = pUnit + i;
			}
		}

		pGroup->SortRenderGroup( &mRenderSubGroupStack, pCamera );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ
	void RenderQueue::Render( const Camera* pCamera )
	{
		Material*		pLastMaterial	= NULL;
		RenderObject*	pLastRenderObj	= NULL;

		RenderUnitStack::Iterator it = mRenderUnitStack.Begin();
		RenderUnitStack::Iterator end = mRenderUnitStack.End();
		for(; it!=end; ++it )
		{
			//��ȡ��Ⱦ����
			RenderParam*		pParam		= it->pRenderParam;
			RenderInstance*		pInstance	= it->pRenderInstance;
			RenderObject*		pRenderObj	= pInstance->mpRenderObject;
			Material*			pMaterial	= pParam->pMaterial;

			if( !pParam->NeedRender() )
				continue;

			//�����ǰ���ʺ����һ�����ò��ʲ�ͬ��Ӧ���²���
			if( pMaterial != pLastMaterial )
			{
				//Ӧ������״̬
				pMaterial->ApplyTextureState();

				//���ò��ʺͲ�����Ⱦ״̬
				RenderSystem::mpSingleton->_SetMaterial( pMaterial );
				RenderSystem::mpSingleton->_SetRenderState( &pMaterial->mRenderState );

				pLastMaterial = pMaterial;
			}

			//�������Ⱦʵ��ʹ�õ���Ⱦ���岻��������õ���Ⱦ����
			if( pRenderObj != pLastRenderObj )
			{
				//���ö�������������������������
				RenderSystem::mpSingleton->_SetVertexDeclaration( pRenderObj->mpVertexDeclaration );

				for( UINT i=0; i<pRenderObj->mNumVertexBuffer; ++i )
					RenderSystem::mpSingleton->_SetVertexStream( pRenderObj->mppVertexBuffer[i], i );

				RenderSystem::mpSingleton->_SetIndexStream( pRenderObj->mpIndexBuffer );

				pLastRenderObj = pRenderObj;
			}

			//��Ⱦ��ʵ��
			pInstance->Render( pParam );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����Ⱦʵ��
	void FKFastcall RenderQueue::AddRenderInstance( RenderInstance* pInstance )
	{
		const UINT nNumParam = pInstance->mpRenderObject->mNumRenderParam;
		RenderParam* pParams = pInstance->mpRenderObject->mpRenderParam;

		RenderUnit* pUnits = mRenderUnitStack.Push( nNumParam );

		for( UINT i=0; i<nNumParam; ++i )
		{
			pUnits[i].pRenderInstance = pInstance;
			pUnits[i].pRenderParam = pParams + i;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����Ⱦʵ���б�
	void FKFastcall RenderQueue::AddRenderInstList( RenderInstList* pRenderInstList )
	{
		RenderInstList::Iterator it = pRenderInstList->Begin();
		RenderInstList::Iterator end = pRenderInstList->End();
		for(; it!=end; ++it )
			AddRenderInstance( *it );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
