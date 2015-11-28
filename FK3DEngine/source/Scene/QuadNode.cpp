/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	QuadNode
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/Scene/SceneInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	QuadNode::QuadNode()
	{
		mSceneNodeList.Initialize( 10, 10 );
	}
	//--------------------------------------------------------------------------------------------------------------
	QuadNode::~QuadNode()
	{
		_DetachAllQuadSceneNode();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����Ĳ����ڵ�
	void FKFastcall QuadNode::_SetQuadNode( const QuadNodeData* pQuadNodeData, QuadNode* pQuadNode )
	{
		mfMinX		= pQuadNodeData->fMinX;
		mfMaxX		= pQuadNodeData->fMaxX;
		mfMinZ		= pQuadNodeData->fMinZ;
		mfMaxZ		= pQuadNodeData->fMaxZ;

		mfHalfSize	= pQuadNodeData->fHalfSize;

		for( UINT i=0; i<2; ++i )
		{
			for( UINT j=0; j<2; ++j )
			{
				mppChild[i][j] = ( pQuadNodeData->ppChildIndex[i][j] != 0 ) ?
					( pQuadNode + pQuadNodeData->ppChildIndex[i][j] ) : NULL;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ҽ�ָ���Ĳ��������ڵ�
	void FKFastcall QuadNode::_AttachQuadSceneNode( QuadSceneNode* pQuadSceneNode )
	{
		*mSceneNodeList.Push() = pQuadSceneNode;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Ͽ�ָ�����Ĳ��������ڵ�
	void FKFastcall QuadNode::_DetachQuadSceneNode( QuadSceneNode* pQuadSceneNode )
	{
		QuadSceneNodeList::Iterator it = mSceneNodeList.Begin();
		QuadSceneNodeList::Iterator end = mSceneNodeList.End();
		for(; it!=end; ++it )
		{
			if( *it == pQuadSceneNode )
			{
				//���ó����ڵ�Ͽ�
				mSceneNodeList.Erase( it );
				pQuadSceneNode->mpQuadNode = NULL;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Ͽ����е��Ĳ��������ڵ�
	void FKFastcall QuadNode::_DetachAllQuadSceneNode()
	{
		QuadSceneNodeList::Iterator it = mSceneNodeList.Begin();
		QuadSceneNodeList::Iterator end = mSceneNodeList.End();
		for(; it!=end; ++it )
		{
			if( *it != NULL )
				(*it)->mpQuadNode = NULL;
		}

		mSceneNodeList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ж�ָ���İ�Χ���Ƿ��ڽڵ�İ�Χ�ռ���
	bool FKFastcall QuadNode::_IsInside( const AxisBox3& refBox3 )
	{
		const float fMinY = ( (QuadSceneManager*)SceneManager::mpSingleton )->mBoundaryMinY;
		const float fMaxY = ( (QuadSceneManager*)SceneManager::mpSingleton )->mBoundaryMaxY;

		if( refBox3.mMinVer.x < mfMinX || refBox3.mMaxVer.x > mfMaxX ||
			refBox3.mMinVer.z < mfMinZ || refBox3.mMaxVer.z > mfMaxZ ||
			refBox3.mMinVer.y < fMinY || refBox3.mMaxVer.y > fMaxY )
			return false;

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ָ����Χ�ռ�������Ĳ����ڵ�
	QuadNode* QuadNode::_GetQuadNodeFromBoundary( const QuadBoundary& sBoundary )
	{
		//���ָ����Χ�ռ�ߴ�С�ڵ�ǰ�ڵ���ӽڵ�ĳߴ�
		if( sBoundary.fSize <= mfHalfSize )
		{
			//��ȡָ����Χ�ռ��ڸýڵ�ռ��ڵ�λ��
			AxisSpaceRelation eRelationX;
			AxisSpaceRelation eRelationZ;

			//���ָ����Χ�ռ�û����ȫ�������κ�һ���ӽڵ�Ŀռ�����ֱ�ӷ��ص�ǰ�ڵ�
			const float fMidX = mfMinX + mfHalfSize;
			const float fMidZ = mfMinZ + mfHalfSize;

			if( sBoundary.fMinX > fMidX )
				eRelationX = ASR_More;
			else if( sBoundary.fMaxX < fMidX )
				eRelationX = ASR_Less;
			else
				return this;

			if( sBoundary.fMinZ > fMidZ )
				eRelationZ = ASR_More;
			else if( sBoundary.fMaxX < fMidZ )
				eRelationZ = ASR_Less;
			else
				return this;

			//���ָ����Χ�ռ��Ӧ���ӽڵ����
			QuadNode* pQuadNode = mppChild[eRelationX][eRelationZ];
			if( pQuadNode != NULL )
				return pQuadNode->_GetQuadNodeFromBoundary( sBoundary );
		}

		//��������ڰ�Χ�ռ��Ӧ��Ҷ�ڵ��򷵻ظýڵ�
		return this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ýڵ㼰���ӽڵ��µĿɼ���Ⱦʵ��
	void QuadNode::_GetVisableInstance( Camera* pActiveCam, RenderQueue* pRenderQueue, Vector3 pBoundaryVer[8] )
	{
		//�����Ĳ����ڵ��Χ�ռ�
		pBoundaryVer[0].x = mfMinX;		pBoundaryVer[0].z = mfMinZ;
		pBoundaryVer[1].x = mfMaxX;		pBoundaryVer[1].z = mfMinZ;
		pBoundaryVer[2].x = mfMinX;		pBoundaryVer[2].z = mfMaxZ;
		pBoundaryVer[3].x = mfMaxX;		pBoundaryVer[3].z = mfMaxZ;

		pBoundaryVer[4].x = mfMinX;		pBoundaryVer[4].z = mfMinZ;
		pBoundaryVer[5].x = mfMaxX;		pBoundaryVer[5].z = mfMinZ;
		pBoundaryVer[6].x = mfMinX;		pBoundaryVer[6].z = mfMaxZ;
		pBoundaryVer[7].x = mfMaxX;		pBoundaryVer[7].z = mfMaxZ;

		//�����Ĳ����ڵ����������Ƿ�ɼ�
		if( pActiveCam->mViewFrustum.IsIntersect( pBoundaryVer ) )
		{
			//�����¹ҽӵ��Ĳ��������ڵ��е���Ⱦʵ���������
			QuadSceneNodeList::Iterator it = mSceneNodeList.Begin();
			QuadSceneNodeList::Iterator end = mSceneNodeList.End();
			for(; it!=end; ++it )
				(*it)->_AddInstanceToQueue( pRenderQueue );

			//�ݹ���ýڵ���ĸ��ӽ��
			for( UINT i=0; i<2; ++i )
				for( UINT j=0; j<2; ++j )
					if( mppChild[i][j] != NULL )
						mppChild[i][j]->_GetVisableInstance( pActiveCam, pRenderQueue, pBoundaryVer );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
