/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BSPGenerator
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
	//���ɶ���������
	void BSPGenerator::GenerateBSPScene( const Vector3* pVertex, const FaceIndex* pFaceIndex, UINT nNumVertex,
		UINT nNumFace, UINT nMaxVertex, UINT nMaxFace )
	{
		mNumVertex		= nNumVertex;
		mNumFace		= nNumFace;
		mMaxVertex		= nMaxVertex;
		mMaxFace		= nMaxFace;

		mNumNode = 0;

		//���ɶ�������
		mpVertexBuf = (Vector3*)malloc( sizeof(Vector3) * nMaxVertex );
		memset( mpVertexBuf, 0, sizeof(Vector3) * nMaxVertex );
		memcpy( mpVertexBuf, pVertex, sizeof(Vector3) * nNumVertex );


		//����ÿ��������Ķ������ָ������ݼ�����������
		mpPlane3Buf = (BSPPlane*)malloc( sizeof(BSPPlane) * nMaxFace );
		memset( mpPlane3Buf, 0, sizeof(BSPPlane) * nMaxFace );


		BSPPlaneList sPlane3List;
		sPlane3List.Initialize( nMaxFace, nMaxFace );

		BSPPlane* pPlane3 = mpPlane3Buf;
		FaceIndex* pFace = (FaceIndex*)pFaceIndex;

		for( UINT i=0; i<nNumFace; ++i, ++pFace, ++pPlane3 )
		{
			pPlane3->SetFromPoints( mpVertexBuf, pFace->v1, pFace->v2, pFace->v3 );
			*sPlane3List.Push() = pPlane3;
		}

		//���ɶ�����
		BSPNode* pRootNode = new BSPNode;
		_GenerateBSPTree( pRootNode, &sPlane3List );

		delete pRootNode;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ɶ�����
	void BSPGenerator::_GenerateBSPTree( BSPNode* pBSPNode, const BSPPlaneList* pBSPPlaneList )
	{
		++mNumNode;

		//�����͹����μ���������Ҷ�ڵ�
		if( _IsConvexSet( pBSPPlaneList ) )
		{
			//���ɷָ�����Ƭ����
			return;
		}

		//ѡ��ָ���
		BSPPlane* pDivPlane3 = _ChooseDivPlane3( pBSPPlaneList );
		pBSPNode->mpDivPlane3 = pDivPlane3;

		UINT nNumInputPlane3 = pBSPPlaneList->Size();

		BSPPlaneList sPosPlane3List;
		BSPPlaneList sNegPlane3List;
		sPosPlane3List.Initialize( nNumInputPlane3, nNumInputPlane3 );
		sNegPlane3List.Initialize( nNumInputPlane3, nNumInputPlane3 );

		//ѭ�������е�ÿ�������
		BSPPlaneList::Iterator it = pBSPPlaneList->Begin();
		BSPPlaneList::Iterator end = pBSPPlaneList->End();
		for(; it!=end; ++it )
		{
			BSPPlane* pPlane3 = *it;

			//�жϸ����ڷָ�����һ��
			SpaceRelation eSR = pDivPlane3->GetSide( *pPlane3 );

			if( eSR == SR_POSITIVE || eSR == SR_COINCIDING )
			{
				*sPosPlane3List.Push() = pPlane3;
			}
			else if( eSR == SR_NEGATIVE )
			{
				*sNegPlane3List.Push() = pPlane3;
			}
			else
			{
				//������ָ���������ηָ�
				_SplitPlane3( pPlane3, pDivPlane3, &sPosPlane3List, &sNegPlane3List );
			}
		}

		if( sPosPlane3List.Size() == 0 || sNegPlane3List.Size() == 0 )
			Except( Exception::ERR_INTERNAL_ERROR, "�ö������ڵ㲻��͹����μ��ϣ�����ȴ�޷���ȷ�ؽ��пռ�ָ" );

		//����ǰ�ӽڵ�
		pBSPNode->mpPosNode = new BSPNode;
		_GenerateBSPTree( pBSPNode->mpPosNode, &sPosPlane3List );

		//�������ӽڵ�
		pBSPNode->mpNegNode = new BSPNode;
		_GenerateBSPTree( pBSPNode->mpNegNode, &sNegPlane3List );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ѡ���ʼ�ָ���
	BSPPlane* BSPGenerator::_ChooseDivPlane3( const BSPPlaneList* pBSPPlaneList )
	{
		float fBestRelation = 0.0f;					//��ǰ����ѷָ��ֵ
		UINT nLeastSplits = UINT_MAX;				//��ǰ����С�ָ�����

		BSPPlaneList::Iterator itBestPlane3 = NULL;	//��ѷָ���

		BSPPlaneList::Iterator begin = pBSPPlaneList->Begin();
		BSPPlaneList::Iterator end = pBSPPlaneList->End();

		//ѭ��ÿһ���ڼ����еĶ����
		for( BSPPlaneList::Iterator itA=begin; itA!=end; ++itA )
		{
			//����ö�����ڽ����������Ĺ����б��������ָ������Թ�
			if( (*itA)->mbDivPlane3 )
				continue;

			//�����ڸ÷ָ������桢����ͱ�����ָ�Ķ����������
			UINT nNumPositive = 0;
			UINT nNumNegative = 0;
			UINT nNumSpanning = 0;

			//ѭ���ڼ����г��� itA ֮��Ķ����
			for( BSPPlaneList::Iterator itB=begin; itB!=end; ++itB )
			{
				if( itB == itA )
					continue;

				const BSPPlane* pPlane3A = *itA;
				const BSPPlane* pPlane3B = *itB;

				SpaceRelation eSR = pPlane3A->GetSide( *pPlane3B );
				if( eSR == SR_POSITIVE || eSR == SR_COINCIDING )
					++nNumPositive;
				else if( eSR == SR_NEGATIVE )
					++nNumNegative;
				else
					++nNumSpanning;
			}

			//�����ڸ÷ָ�������ͷ���Ķ����������ֵ��ֵԽ��ָ�Խ���ȣ�
			float fRelation = 0.0f;
			if( nNumPositive != 0 && nNumNegative != 0 )
			{
				fRelation = ( nNumNegative > nNumPositive ) ?
					(float)nNumPositive / (float)nNumNegative : (float)nNumNegative / (float)nNumPositive;

				//�����ǰ����ηָ����Ӽ��ϱ�ֵ�ɽ��ܣ����ҷָ��˸��ٵĶ���Σ�
				//��ô���浱ǰ�Ķ����Ϊ�µĺ�ѡ�ָ��档
				//�����ǰ����κ���ѷָ���һ���ָ�����ͬ�����Ķ���ζ��ָ���
				//�Ӽ��ϱ�ֵ����Ļ�������ǰ�������Ϊ�µĺ�ѡ�ָ��档
				if( fRelation > fBestRelation && nNumSpanning <= nLeastSplits )
					goto SetBestPlane3;
			}
			else if( ( nNumPositive != 0 || nNumNegative != 0 ) && nNumSpanning != 0 )
			{
				if( fBestRelation == 0.0f && nNumSpanning < nLeastSplits )
					goto SetBestPlane3;
			}

			continue;

SetBestPlane3:
			itBestPlane3 = itA;
			nLeastSplits = nNumSpanning;
			fBestRelation = fRelation;
		}

		BSPPlane* pDivPlane3 = *itBestPlane3;
		pDivPlane3->mbDivPlane3 = true;
		return pDivPlane3;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�жϼ������Ƿ�Ϊ͹�����
	bool BSPGenerator::_IsConvexSet( const BSPPlaneList* pBSPPlaneList )
	{
		//ѭ�����ÿ��������ж��Ƿ��������������ڸö���ζ�������
		BSPPlaneList::Iterator begin = pBSPPlaneList->Begin();
		BSPPlaneList::Iterator end = pBSPPlaneList->End();

		for( BSPPlaneList::Iterator itA=begin; itA!=end; ++itA )
		{
			for( BSPPlaneList::Iterator itB=begin; itB!=end; ++itB )
			{
				if( itA == itB )
					continue;

				const BSPPlane* pPlane3A = *itA;
				const BSPPlane* pPlane3B = *itB;

				const SpaceRelation eSR = pPlane3A->GetSide( *pPlane3B );

				if( eSR == SR_NEGATIVE || eSR == SR_SPANNING )
					return false;
			}
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ָ�������ָ���
	void BSPGenerator::_SplitPlane3( BSPPlane* pPlane3, BSPPlane* pDivPlane3,
		BSPPlaneList* pFrontPlane3List, BSPPlaneList* pBackPlane3List )
	{
		static WORD aIndex[] = { 2, 0, 1 };

		static Vector3 vEdge;
		static WORD pFrontVer[4];	//�ָ���ǰ��Ķ���ζ�������
		static WORD pBackVer[4];	//�ָ��ĺ���Ķ���ζ�������

		int nFrontVer = 0;
		int nBackVer = 0;

		const Vector3& vVerDivPlane3 = mpVertexBuf[ pDivPlane3->mV1 ];

		//ѭ������ָ����������Ϸֱ�ķָ������
		for( UINT i=0; i<3; ++i )
		{
			//ʹ��ʸ����ƽ���ཻ������׷�٣���ʽ�����ཻ��������
			const WORD wIndexA = pPlane3->mV[ aIndex[i] ];
			const WORD wIndexB = pPlane3->mV[i];

			const Vector3& vA = mpVertexBuf[ wIndexA ];
			const Vector3& vB = mpVertexBuf[ wIndexB ];

			const float fDistA = pDivPlane3->GetDistance( vA );
			const float fDistB = pDivPlane3->GetDistance( vB );

			//����߷���
			vEdge = ( vB - vA ).GetNormalizedVec();

			if( fDistB > 0.0f )
			{
				if( fDistA < 0.0f )
				{
					//�����µĶ���
					float fEdgeDist = -fDistA / pDivPlane3->mNormal.GetDot( vEdge );
					mpVertexBuf[ mNumVertex ] = vA + ( vEdge * fEdgeDist );

					pFrontVer[nFrontVer++] = pBackVer[nBackVer++] = (WORD)mNumVertex;
					++mNumVertex;
				}
				pFrontVer[nFrontVer++] = wIndexB;
			}
			else if( fDistB < 0.0f )
			{
				if( fDistA > 0.0f )
				{
					//�����µĶ���
					float fEdgeDist = -fDistA / pDivPlane3->mNormal.GetDot( vEdge );
					mpVertexBuf[ mNumVertex ] = vA + ( vEdge * fEdgeDist );

					pFrontVer[nFrontVer++] = pBackVer[nBackVer++] = (WORD)mNumVertex;
					++mNumVertex;
				}
				pBackVer[nBackVer++] = wIndexB;
			}
			else
			{
				pFrontVer[nFrontVer++] = pBackVer[nBackVer++] = wIndexB;
			}
		}

		//�����µ�������
		_BuildNewPlane3( pFrontVer, nFrontVer, pFrontPlane3List );
		_BuildNewPlane3( pBackVer, nBackVer, pBackPlane3List );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����¶������ָ���
	void BSPGenerator::_BuildNewPlane3( WORD pVerIndex[4], int nNumVer, BSPPlaneList* pNewPlane3List )
	{
		//���ݶ��������жϽ���������������
		switch (nNumVer)
		{
		case 3:
			{
				*pNewPlane3List->Push() = mpPlane3Buf + mNumFace;
				mpPlane3Buf[ mNumFace++ ].SetFromPoints( mpVertexBuf, pVerIndex[0], pVerIndex[1], pVerIndex[2] );

				break;
			}
		case 4:
			{
				*pNewPlane3List->Push() = mpPlane3Buf + mNumFace;
				mpPlane3Buf[ mNumFace++ ].SetFromPoints( mpVertexBuf, pVerIndex[0], pVerIndex[1], pVerIndex[2] );

				*pNewPlane3List->Push() = mpPlane3Buf + mNumFace;
				mpPlane3Buf[ mNumFace++ ].SetFromPoints( mpVertexBuf, pVerIndex[0], pVerIndex[2], pVerIndex[3] );

				break;
			}
		default:
			Except( Exception::ERR_INTERNAL_ERROR, "�����ηָ�����ɵ��¶�����������" );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
