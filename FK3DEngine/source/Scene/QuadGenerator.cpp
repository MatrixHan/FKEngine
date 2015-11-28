/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	QuadGenerator
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
	QuadGenerator::QuadGenerator()
		: mRootSize			(0.0f)
		, mLeafSize			(0.0f)
		, mBoundaryMinX		(0.0f)
		, mBoundaryMaxX		(0.0f)
		, mBoundaryMinZ		(0.0f)
		, mBoundaryMaxZ		(0.0f)
		, mBoundaryMinY		(0.0f)
		, mBoundaryMaxY		(0.0f)
		, mNumNode			(0)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	QuadGenerator::~QuadGenerator()
	{
		DestroyQuadScene();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ɷ�ϡ��Ԫ���Ĳ�������
	void QuadGenerator::GenerateThickQuadScene( float fMidX, float fMidZ, float fMinY, float fMaxY, float fLeafSize, UINT nDepth )
	{
		mNumNode = _SetSceneBoundary( fMidX, fMidZ, fMinY, fMaxY, fLeafSize, nDepth );

		mNodeDataStack.Initialize( mNumNode, 100 );

		//�ݹ鴴�������Ĳ����ڵ�
		_CreateNode( fMidX, fMidZ, mRootSize, nDepth );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ϡ��Ԫ���Ĳ�������
	void QuadGenerator::GenerateLooseQuadScene( float fMidX, float fMidZ, float fMinY, float fMaxY, float fLeafSize, UINT nDepth )
	{
		UINT nNumNode = _SetSceneBoundary( fMidX, fMidZ, fMinY, fMaxY, fLeafSize, nDepth );

		mNodeDataStack.Initialize( nNumNode, 100 );

		//�������ڵ�
		_CreateNode( fMidX, fMidZ, mRootSize, 0 );

		mNumNode = 1;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ָ����Χ�ռ����������ϡ��Ԫ���Ĳ����ڵ�
	UINT QuadGenerator::GenerateNodeFromBoundary( const AxisBox3& refAxisBox3 )
	{
		return GenerateNodeFromBoundary(
			refAxisBox3.mMinVer.x, refAxisBox3.mMaxVer.x, refAxisBox3.mMinVer.z, refAxisBox3.mMaxVer.z );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ָ����Χ�ռ����������ϡ��Ԫ���Ĳ����ڵ�
	UINT QuadGenerator::GenerateNodeFromBoundary( float fMinX, float fMaxX, float fMinZ, float fMaxZ )
	{
		//���ָ����Χ�ռ䳬���˳�����Χ�ռ��򷵻ظ��ڵ�
		if( fMinX < mBoundaryMinX || fMaxX > mBoundaryMaxX || fMinZ < mBoundaryMinZ || fMaxZ > mBoundaryMaxZ )
			return 0;

		//�����Χ�ռ�����
		QuadBoundary sBoundary;

		sBoundary.fMinX = fMinX;
		sBoundary.fMaxX = fMaxX;
		sBoundary.fMinZ = fMinZ;
		sBoundary.fMaxZ = fMaxZ;

		const float fSizeX = fMaxX - fMinX;
		const float fSizeZ = fMaxZ - fMinZ;

		sBoundary.fSize = FK_MAX( fSizeX, fSizeZ );

		UINT nIndex = _CreateNodeFromBoundary( sBoundary, 0 );

		//���½ڵ�����
		mNumNode = mNodeDataStack.Size();

		return nIndex;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����Ĳ�������
	void QuadGenerator::DestroyQuadScene()
	{
		mRootSize		= 0.0f;
		mLeafSize		= 0.0f;
		mBoundaryMinX	= 0.0f;
		mBoundaryMaxX	= 0.0f;
		mBoundaryMinZ	= 0.0f;
		mBoundaryMaxZ	= 0.0f;
		mNumNode		= 0.0f;

		mNodeDataStack.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���Ĳ�����������д���ļ�
	void QuadGenerator::WriteToFile( FileObject* pFile )
	{
		if( mNumNode == 0 )
			Except(Exception::ERR_INVALIDPARAMS, "�����������ɵ��Ĳ����������ݿ���д���ļ���" );

		//д���Ĳ�������
		QuadtreeData sQuadtreeData;

		sQuadtreeData.fRootSize		= mRootSize;
		sQuadtreeData.fLeafSize		= mLeafSize;

		sQuadtreeData.fBoundaryMinX	= mBoundaryMinX;
		sQuadtreeData.fBoundaryMaxX	= mBoundaryMaxX;
		sQuadtreeData.fBoundaryMinZ	= mBoundaryMinZ;
		sQuadtreeData.fBoundaryMaxZ	= mBoundaryMaxZ;

		sQuadtreeData.fBoundaryMinY = mBoundaryMinY;
		sQuadtreeData.fBoundaryMaxY = mBoundaryMaxY;

		sQuadtreeData.nNumNode		= mNumNode;

		pFile->Write( &sQuadtreeData, sizeof(QuadtreeData) );

		//д�������Ĳ����ڵ�����
		pFile->Write( mNodeDataStack.Begin(), sizeof(QuadNodeData) * mNumNode );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����Ĳ���������Χ�ռ�
	UINT QuadGenerator::_SetSceneBoundary( float fMidX, float fMidZ, float fMinY, float fMaxY, float fLeafSize, UINT nDepth )
	{
		if( nDepth > mMaxDepth )
		{
			Except( Exception::ERR_INVALIDPARAMS,
			Misc::FormatString( NULL, "ָ�����Ĳ������ֵ��%d�������������������ֵ��%d����", nDepth, mMaxDepth ) );
		}

		//������ڵ�ߴ�
		mLeafSize = fLeafSize;

		UINT nSegment = pow( static_cast< float >( 2 ), static_cast< float >( nDepth ) );
		mRootSize = fLeafSize * (float)nSegment;

		//��������Χ�ռ�����
		const float fHalfSize = mRootSize / 2.0f;

		mBoundaryMinX = fMidX - fHalfSize;
		mBoundaryMaxX = fMidX + fHalfSize;
		mBoundaryMinZ = fMidZ - fHalfSize;
		mBoundaryMaxZ = fMidZ + fHalfSize;

		mBoundaryMinY = fMinY;
		mBoundaryMaxY = fMaxY;

		//����ڵ�����
		UINT nNumNode = 1;
		UINT nCount = 1;
		for( UINT i=0; i<nDepth; ++i )
		{
			nCount *= 4;
			nNumNode += nCount;
		}

		return nNumNode;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����Ĳ����ڵ�
	UINT QuadGenerator::_CreateNode( float fMidX, float fMidZ, float fHalfSize, UINT nDepth )
	{
		UINT nIndex = mNodeDataStack.Size();
		QuadNodeData* pNodeData = mNodeDataStack.Push();

		//���õ�ǰ�������
		pNodeData->fMinX = fMidX - fHalfSize;
		pNodeData->fMaxX = fMidX + fHalfSize;
		pNodeData->fMinZ = fMidZ - fHalfSize;
		pNodeData->fMaxZ = fMidZ + fHalfSize;

		pNodeData->fHalfSize = fHalfSize;

		//���δ����ָ������򴴽��ӽڵ�
		if( nDepth != 0 )
		{
			const UINT nChildDepth = nDepth - 1;
			const float fHalfChildSize = fHalfSize / 2.0f;

			float pMidX[2];
			float pMidZ[2];

			pMidX[0] = fMidX - fHalfChildSize;
			pMidX[1] = fMidX + fHalfChildSize;
			pMidZ[0] = fMidZ - fHalfChildSize;
			pMidZ[1] = fMidZ + fHalfChildSize;

			for( UINT i=0; i<2; ++i )
				for( UINT j=0; j<2; ++j )
					pNodeData->ppChildIndex[i][j] = _CreateNode( pMidX[i], pMidZ[j], fHalfChildSize, nChildDepth );
		}
		else
		{
			pNodeData->ppChildIndex[0][0] = 0;
			pNodeData->ppChildIndex[1][0] = 0;
			pNodeData->ppChildIndex[0][1] = 0;
			pNodeData->ppChildIndex[1][1] = 0;
		}

		return nIndex;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ָ����Χ�ռ䴴���Ĳ����ڵ�򷵻ض�Ӧ���Ĳ����ڵ�
	UINT QuadGenerator::_CreateNodeFromBoundary( const QuadBoundary& sBoundary, UINT nNodeIndex )
	{
		QuadNodeData* pNodeData = mNodeDataStack.Begin() + nNodeIndex;

		const float fChildSize = pNodeData->fHalfSize;

		//���ָ����Χ�ռ�ߴ�С�ڵ�ǰ�ڵ���ӽڵ�ĳߴ粢��С��Ҷ�ڵ�ĳߴ�
		if( sBoundary.fSize <= fChildSize && sBoundary.fSize >= mLeafSize )
		{
			//��ȡָ����Χ�ռ��ڸýڵ�ռ��ڵ�λ��
			AxisSpaceRelation eRelationX;
			AxisSpaceRelation eRelationZ;

			//���ָ����Χ�ռ�û����ȫ�������κ�һ���ӽڵ�Ŀռ�����ֱ�ӷ��ص�ǰ�ڵ�
			const float fMidX = pNodeData->fMinX + fChildSize;
			const float fMidZ = pNodeData->fMinZ + fChildSize;

			if( sBoundary.fMinX > fMidX )
				eRelationX = ASR_More;
			else if( sBoundary.fMaxX < fMidX )
				eRelationX = ASR_Less;
			else
				return nNodeIndex;

			if( sBoundary.fMinZ > fMidZ )
				eRelationZ = ASR_More;
			else if( sBoundary.fMaxX < fMidZ )
				eRelationZ = ASR_Less;
			else
				return nNodeIndex;

			//���ָ����Χ�ռ��Ӧ���ӽڵ㲻����
			UINT& nChildIndex = pNodeData->ppChildIndex[eRelationX][eRelationZ];
			if( nChildIndex == 0 )
			{
				//����ָ����Χ�ռ��Ӧ���ӽڵ�
				const float fHalfChildSize = fChildSize / 2.0f;

				float pMidX[2];
				float pMidZ[2];

				pMidX[0] = fMidX - fHalfChildSize;
				pMidX[1] = fMidX + fHalfChildSize;
				pMidZ[0] = fMidZ - fHalfChildSize;
				pMidZ[1] = fMidZ + fHalfChildSize;

				nChildIndex = _CreateNode( pMidX[eRelationX], pMidZ[eRelationZ], fHalfChildSize, 0 );
			}

			//�����ݹ鴴���ӽڵ�
			return _CreateNodeFromBoundary( sBoundary, nChildIndex );
		}

		return nNodeIndex;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
