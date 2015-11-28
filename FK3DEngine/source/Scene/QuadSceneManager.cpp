/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	QuadSceneManager
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
	QuadSceneManager::QuadSceneManager()
		: mRootSize			(0.0f)
		, mLeafSize			(0.0f)
		, mBoundaryMinX		(0.0f)
		, mBoundaryMaxX		(0.0f)
		, mBoundaryMinZ		(0.0f)
		, mBoundaryMaxZ		(0.0f)
		, mBoundaryMinY		(0.0f)
		, mBoundaryMaxY		(0.0f)
		, mpQuadNode		(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	QuadSceneManager::~QuadSceneManager()
	{
		SafeDeleteArray( mpQuadNode );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����������ڵ�
	SceneNode* QuadSceneManager::CreateSceneRootNode()
	{
		mpRootNode = new QuadSceneNode;
		return mpRootNode;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����Ĳ��������ļ�
	void QuadSceneManager::LoadFromFile( FileObject* pFile )
	{
		//��ȡ�Ĳ�������
		QuadtreeData sQuadtreeData;
		pFile->Read( &sQuadtreeData, sizeof(QuadtreeData) );

		mRootSize		= sQuadtreeData.fRootSize;
		mLeafSize		= sQuadtreeData.fLeafSize;

		mBoundaryMinX	= sQuadtreeData.fBoundaryMinX;
		mBoundaryMaxX	= sQuadtreeData.fBoundaryMaxX;
		mBoundaryMinZ	= sQuadtreeData.fBoundaryMinZ;
		mBoundaryMaxZ	= sQuadtreeData.fBoundaryMaxZ;

		mBoundaryMinY	= sQuadtreeData.fBoundaryMinY;
		mBoundaryMaxY	= sQuadtreeData.fBoundaryMaxY;

		mNumNode		= sQuadtreeData.nNumNode;

		//��ȡ�Ĳ����ڵ�����
		mpQuadNode = new QuadNode [mNumNode];

		const UINT nNumNodeDataBuf = 0x1000;
		QuadNodeData* pQuadNodeDataBuf = (QuadNodeData*)malloc( sizeof(QuadNodeData) * nNumNodeDataBuf );

		QuadNode* pQuadNode = mpQuadNode;
		UINT nRemainNode = mNumNode;

		while( nRemainNode != 0 )
		{
			UINT nNumReadNodeData = ( nRemainNode < nNumNodeDataBuf ) ? nRemainNode : nNumNodeDataBuf;
			pFile->Read( pQuadNodeDataBuf, sizeof(QuadNodeData) * nNumReadNodeData );

			QuadNodeData* pQuadNodeData = pQuadNodeDataBuf;

			for( UINT i=0; i<nNumReadNodeData; ++i )
			{
				pQuadNode->_SetQuadNode( pQuadNodeData, mpQuadNode );
				++pQuadNodeData;
				++pQuadNode;
			}

			nRemainNode -= nNumReadNodeData;
		}

		free( pQuadNodeDataBuf );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ָ����Χ�ռ�������Ĳ����ڵ�
	QuadNode* QuadSceneManager::GetQuadNodeFromBoundary( const AxisBox3& refAxisBox3 )
	{
		if( refAxisBox3.mMinVer.y < mBoundaryMinY || refAxisBox3.mMaxVer.y > mBoundaryMaxY )
			return mpQuadNode;

		return GetQuadNodeFromBoundary(
			refAxisBox3.mMinVer.x, refAxisBox3.mMaxVer.x,
			refAxisBox3.mMinVer.z, refAxisBox3.mMaxVer.z );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ָ����Χ�ռ�������Ĳ����ڵ�
	QuadNode* QuadSceneManager::GetQuadNodeFromBoundary( float fMinX, float fMaxX, float fMinZ, float fMaxZ )
	{
		//���ָ����Χ�ռ��ڳ�������Χ�ռ�֮����ֱ�ӷ��ظ��ڵ�
		if( fMinX < mBoundaryMinX || fMaxX > mBoundaryMaxX || fMinZ < mBoundaryMinZ || fMaxZ > mBoundaryMaxZ )
			return mpQuadNode;

		//�����Χ�ռ�����
		static QuadBoundary sBoundary;

		sBoundary.fMinX = fMinX;
		sBoundary.fMaxX = fMaxX;
		sBoundary.fMinZ = fMinZ;
		sBoundary.fMaxZ = fMaxZ;

		const float fSizeX = fMaxX - fMinX;
		const float fSizeZ = fMaxZ - fMinZ;

		sBoundary.fSize = FK_MAX( fSizeX, fSizeZ );

		return mpQuadNode->_GetQuadNodeFromBoundary( sBoundary );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ɼ���Ⱦʵ��
	void QuadSceneManager::_GetVisableInstance( Camera* pActiveCam )
	{
		//Ԥ�����úó�����Χ�ռ�� Y ֵ
		static Vector3 pBoundaryVer[8];

		pBoundaryVer[0].y = mBoundaryMinY;
		pBoundaryVer[1].y = mBoundaryMinY;
		pBoundaryVer[2].y = mBoundaryMinY;
		pBoundaryVer[3].y = mBoundaryMinY;
		pBoundaryVer[4].y = mBoundaryMaxY;
		pBoundaryVer[5].y = mBoundaryMaxY;
		pBoundaryVer[6].y = mBoundaryMaxY;
		pBoundaryVer[7].y = mBoundaryMaxY;

		//�����Ĳ����ڵ�
		mpQuadNode->_GetVisableInstance( pActiveCam, &mRenderQueue, pBoundaryVer );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
