/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BSPPlane
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
	BSPPlane::BSPPlane()
		: mpVertex		(NULL)
		, mbDivPlane3	(false)
		, mV1			(0)
		, mV2			(0)
		, mV3			(0)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	BSPPlane::BSPPlane( Vector3* pVertex, WORD v1, WORD v2, WORD v3 )
		: mpVertex		(pVertex)
		, mbDivPlane3	(false)
		, mV1			(v1)
		, mV2			(v2)
		, mV3			(v3)
	{
		Plane3::SetFromPoints( pVertex[v1], pVertex[v2], pVertex[v3] );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ö������ָ���
	void BSPPlane::SetFromPoints( Vector3* pVertex, WORD v1, WORD v2, WORD v3 )
	{
		mbDivPlane3 = false;
		mpVertex = pVertex;

		mV1 = v1;
		mV2 = v2;
		mV3 = v3;

		Plane3::SetFromPoints( pVertex[v1], pVertex[v2], pVertex[v3] );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ж���һ���������ָ�����÷ָ���Ŀռ佻���ϵ
	SpaceRelation FKFastcall BSPPlane::GetSide( const BSPPlane& rBSPPlane ) const
	{
		UINT nNumPositive = 0;
		UINT nNumNegative = 0;

		//���ÿ�����������Ĺ�ϵ
		for( UINT i=0; i<3; ++i )
		{
			SpaceRelation eSR = Plane3::GetSide( mpVertex[ rBSPPlane.mV[i] ] );

			if( eSR == SR_POSITIVE )
				++nNumPositive;
			else if( eSR == SR_NEGATIVE )
				++nNumNegative;
		}

		if( nNumPositive > 0 && nNumNegative == 0 )
			return SR_POSITIVE;
		else if( nNumPositive == 0 && nNumNegative > 0 )
			return SR_NEGATIVE;
		else if( nNumPositive == 0 && nNumNegative == 0 )
			return SR_COINCIDING;
		else
			return SR_SPANNING;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
