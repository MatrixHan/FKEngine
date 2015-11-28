/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BoundMesh
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/PhysiceSystem/PhysicsSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	BoundMesh::BoundMesh()
		: mNumFace			(0)
		, mNumVertex		(0)
		, mpBoundFace		(NULL)
		, mpFaceVertex		(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	BoundMesh::~BoundMesh()
	{
		SafeFree( mpBoundFace );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ײ�崴������
	BoundMesh::BoundVolume* BoundMesh::Creator()
	{
		return new BoundMesh;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ײ��������
	void BoundMesh::LoadBoundMesh( BoundInfo* pBoundInfo, BoundFace* pBoundFace, Vector3* pVertex )
	{
		//�����������������ݼ��䶥������
		size_t nFaceBufLen = pBoundInfo->nNumFace * sizeof(BoundFace);
		size_t nVerBufLen = pBoundInfo->nNumVertex * sizeof(Vector3);

		mpBoundFace = (BoundFace*)malloc( nFaceBufLen + nVerBufLen );
		mpFaceVertex = (Vector3*)( mpBoundFace + pBoundInfo->nNumFace );

		memcpy( mpBoundFace, pBoundFace, nFaceBufLen );
		memcpy( mpFaceVertex, pVertex, nVerBufLen );

		mNumFace = pBoundInfo->nNumFace;
		mNumVertex = pBoundInfo->nNumVertex;

		//���ð�Χ������
		mLocalBoundBox.SetMaxMin( pBoundInfo->vBoundBoxMax, pBoundInfo->vBoundBoxMin );
		mWorldBoundBox = mLocalBoundBox;

		//�洢��ײ����
		mBoundType = pBoundInfo->eType;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ײ���
	bool BoundMesh::Intersect( const Ray3* pRay, Vector3* pContactPos )
	{
		return false;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�߶���ײ���
	bool BoundMesh::Intersect( const Segment3* pSegment, Vector3* pContactPos )
	{
		return false;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������ײ���
	void BoundMesh::DoCollisionDetect( RigidSphere* pRigidSphere, CollisionInfo* pInfo )
	{
		//ת����������������ƶ�������ײ��ռ�
		BoundFace* pCollisionFace = NULL;

		static Vector3 vSpherePos;
		static Vector3 vMoveDir;
		static Vector3 vCollisionPos;

		const float fRadius = pRigidSphere->mRadius;

		Mat4TransVec3( &vSpherePos, &mpBoundNode->mInvWorldMatrix, &pRigidSphere->mMassCenter );
		Mat4TransVec3( &vMoveDir, &mpBoundNode->mInvWorldMatrix, &pRigidSphere->mLinearMoveDir );

		//ѭ�������ײ����������������
		for( UINT i=0; i<mNumFace; ++i )
		{
			const BoundFace& rFace = mpBoundFace[i];
			const Vector3& vA = mpFaceVertex[ rFace.nV1Index ];
			const Vector3& vB = mpFaceVertex[ rFace.nV2Index ];
			const Vector3& vC = mpFaceVertex[ rFace.nV3Index ];

			//���������ľ���
			//MoveLen = ( ( RayOnPlane3 - RayStart ) ��� Plane3Nor ) / ( MoveDir ��� Plane3Nor )
			float fDotProduct = vMoveDir.GetDot( rFace.vNormal );

			//����ƶ��������ײ�淨�߷�����ͬ��������
			if( fDotProduct >= 0.0f )
				continue;

			float fDist = ( ( vA - vSpherePos ).GetDot( rFace.vNormal ) + fRadius ) / fDotProduct;

			//���δ�������ཻ
			if( fDist < -fRadius )
				continue;

			//����ཻ��������ƶ�������������
			if( fDist > pRigidSphere->mLinearMoveLen )
				continue;

			//���������֪�����ײ����Ҳ������
			if( fDist > pInfo->fCollisionDist )
				continue;

			//�����ཻ������
			static Vector3 vIntersectPos;
			vIntersectPos = vSpherePos + vMoveDir * fDist;

			//���������α߽��ж�����
			static Vector3 vSideJudgePos;

			//������彫Ҫ������ײ��
			if( fDist > 0.0f )
				vSideJudgePos = vIntersectPos;
			//�����������ײ������
			else
				vSideJudgePos = vSpherePos + rFace.vNormal * fDist;

			//����ཻ���Ƿ�����������

			//���������������ߵ�����
			static Vector3 vAB, vBC, vCA;
			static Vector3 vSideNormal;
			float fSideDist;

			Vec3Sub( &vAB, &vB, &vA );
			Vec3Sub( &vBC, &vC, &vB );
			Vec3Sub( &vCA, &vA, &vC );


			//�ж���ײ���Ƿ��� AB ����

			//���㴹ֱ�� AB �ߺ������η��ߵ��������� AB �����ڵĴ�ֱ�������ε�ƽ�棩
			Vec3Cross( &vSideNormal, &rFace.vNormal, &vAB );
			vSideNormal.Normalize();

			//�������� AC �� AB ��ƽ���ϵ�ͶӰ���ȣ����Ϊ��ֵ����֤���÷���ָ���������⣬��˷�ת����
			if( vSideNormal.GetDot( -vCA ) < 0.0f )
				vSideNormal = -vSideNormal;

			//�����ײ���� AB ���⣨���������⣩��û������淢����ײ
			fSideDist = vSideNormal.GetDot( vA ) - fRadius;
			if( vSideNormal.GetDot( vSideJudgePos ) - fSideDist < 0.0f )
				continue;

			//����������ȥ AB �߶Խ� C �Ķ��ಿ�ֵ�ƽ����ԭ��ľ���
			//�����ڸ�ƽ���� AB ��ƽ�У�����ֱ���� AB ��ķ��߽��м��㡣��
			fSideDist = vSideNormal.GetDot( vC ) + fRadius;
			//�������ĵ�ǰλ�ò��ڸ�ƽ������˵��δ��������η�����ײ�����ط�
			if( vSideNormal.GetDot( vSideJudgePos ) - fSideDist > 0.0f )
				continue;


			//�ж���ײ���Ƿ��� BC ����
			Vec3Cross( &vSideNormal, &rFace.vNormal, &vBC );
			vSideNormal.Normalize();

			if( vSideNormal.GetDot( -vAB ) < 0.0f )
				vSideNormal = -vSideNormal;

			fSideDist = vSideNormal.GetDot( vB ) - fRadius;
			if( vSideNormal.GetDot( vSideJudgePos ) - fSideDist < 0.0f )
				continue;

			fSideDist = vSideNormal.GetDot( vA ) + fRadius;
			if( vSideNormal.GetDot( vSideJudgePos ) - fSideDist > 0.0f )
				continue;


			//�ж���ײ���Ƿ��� CA ����
			Vec3Cross( &vSideNormal, &rFace.vNormal, &vCA );
			vSideNormal.Normalize();

			if( vSideNormal.GetDot( -vBC ) < 0.0f )
				vSideNormal = -vSideNormal;

			fSideDist = vSideNormal.GetDot( vC ) - fRadius;
			if( vSideNormal.GetDot( vSideJudgePos ) - fSideDist < 0.0f )
				continue;

			fSideDist = vSideNormal.GetDot( vB ) + fRadius;
			if( vSideNormal.GetDot( vSideJudgePos ) - fSideDist > 0.0f )
				continue;

			//�����ε���ײ�������
			if( fDist < pInfo->fCollisionDist )
			{
				vCollisionPos = vIntersectPos;
				pCollisionFace = &mpBoundFace[i];
				pInfo->fCollisionDist = fDist;
			}
		}

		//���������ײ
		if( pCollisionFace != NULL )
		{
			//����ײĿ���ӷ��߷���ƽ��һС�ξ��룬�Է���һ֡��Խƽ�档
			pInfo->vCollisionPos = ( vCollisionPos + pCollisionFace->vNormal * 0.0001f ) * mpBoundNode->mWorldMatrix;
			pInfo->vFaceNormal = pCollisionFace->vNormal * mpBoundNode->mWorldMatrix;
			pInfo->pCollisionVolume = this;
			pInfo->bCollision = true;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//����Բ������ײ���
	void BoundMesh::DoCollisionDetect( RigidCylinder* pRigidCylinder, CollisionInfo* pInfo )
	{
		//ת������Բ����������ƶ�������ײ��ռ�
		BoundFace* pCollisionFace = NULL;

		static Vector3 vCylinderPos;
		static Vector3 vCylinderDir;
		static Vector3 vMoveDir;
		static Vector3 vCollisionPos;

		Mat4TransVec3( &vCylinderPos, &mpBoundNode->mInvWorldMatrix, &pRigidCylinder->mMassCenter );
		Mat4TransVec3( &vCylinderDir, &mpBoundNode->mInvWorldMatrix, &Vector3::UnitY );
		Mat4TransVec3( &vMoveDir, &mpBoundNode->mInvWorldMatrix, &pRigidCylinder->mLinearMoveDir );

		//ѭ�������ײ����������������
		for( UINT i=0; i<mNumFace; ++i )
		{
			const BoundFace& rFace = mpBoundFace[i];
			const Vector3& vA = mpFaceVertex[ rFace.nV1Index ];
			const Vector3& vB = mpFaceVertex[ rFace.nV2Index ];
			const Vector3& vC = mpFaceVertex[ rFace.nV3Index ];

			//���������ľ���
			//MoveLen = ( ( RayOnPlane3 - RayStart ) ��� Plane3Nor ) / ( MoveDir ��� Plane3Nor )
			float fDotProduct = vMoveDir.GetDot( rFace.vNormal );

			//����ƶ��������ײ�淨�߷�����ͬ��������
			if( fDotProduct >= 0.0f )
				continue;

			//����Բ�����⾶
			float fTerm = pRigidCylinder->_GetCylinderTerm( vCylinderDir, rFace.vNormal );
			float fDist = ( ( vA - vCylinderPos ).GetDot( rFace.vNormal ) + fTerm ) / fDotProduct;

			//���δ��Բ�����ཻ
			if( fDist < -fTerm )
				continue;

			//����ཻ��������ƶ�������������
			if( fDist > pRigidCylinder->mLinearMoveLen )
				continue;

			//���������֪�����ײ����Ҳ������
			if( fDist > pInfo->fCollisionDist )
				continue;

			//�����ཻ������
			static Vector3 vIntersectPos;
			vIntersectPos = vCylinderPos + vMoveDir * fDist;

			//���������α߽��ж�����
			static Vector3 vSideJudgePos;

			//���Բ���彫Ҫ������ײ��
			if( fDist > 0.0f )
				vSideJudgePos = vIntersectPos;
			//���Բ��������ײ������
			else
				vSideJudgePos = vCylinderPos + rFace.vNormal * fDist;

			//����ཻ���Ƿ�����������

			//���������������ߵ�����
			static Vector3 vAB, vBC, vCA;
			static Vector3 vSideNormal;
			float fSideDist;

			Vec3Sub( &vAB, &vB, &vA );
			Vec3Sub( &vBC, &vC, &vB );
			Vec3Sub( &vCA, &vA, &vC );


			//�ж���ײ���Ƿ��� AB ����

			//���㴹ֱ�� AB �ߺ������η��ߵ��������� AB �����ڵĴ�ֱ�������ε�ƽ�棩
			Vec3Cross( &vSideNormal, &rFace.vNormal, &vAB );
			vSideNormal.Normalize();

			//�������� AC �� AB ��ƽ���ϵ�ͶӰ���ȣ����Ϊ��ֵ����֤���÷���ָ���������⣬��˷�ת����
			if( vSideNormal.GetDot( -vCA ) < 0.0f )
				vSideNormal = -vSideNormal;

			fTerm = pRigidCylinder->_GetCylinderTerm( vCylinderDir, vSideNormal );

			//�����ײ���� AB ���⣨���������⣩��û������淢����ײ
			fSideDist = vSideNormal.GetDot( vA ) - fTerm;
			if( vSideNormal.GetDot( vSideJudgePos ) - fSideDist < 0.0f )
				continue;

			//����������ȥ AB �߶Խ� C �Ķ��ಿ�ֵ�ƽ����ԭ��ľ���
			//�����ڸ�ƽ���� AB ��ƽ�У�����ֱ���� AB ��ķ��߽��м��㡣��
			fSideDist = vSideNormal.GetDot( vC ) + fTerm;
			//�������ĵ�ǰλ�ò��ڸ�ƽ������˵��δ��������η�����ײ�����ط�
			if( vSideNormal.GetDot( vSideJudgePos ) - fSideDist > 0.0f )
				continue;


			//�ж���ײ���Ƿ��� BC ����
			Vec3Cross( &vSideNormal, &rFace.vNormal, &vBC );
			vSideNormal.Normalize();

			if( vSideNormal.GetDot( -vAB ) < 0.0f )
				vSideNormal = -vSideNormal;

			fTerm = pRigidCylinder->_GetCylinderTerm( vCylinderDir, vSideNormal );

			fSideDist = vSideNormal.GetDot( vB ) - fTerm;
			if( vSideNormal.GetDot( vSideJudgePos ) - fSideDist < 0.0f )
				continue;

			fSideDist = vSideNormal.GetDot( vA ) + fTerm;
			if( vSideNormal.GetDot( vSideJudgePos ) - fSideDist > 0.0f )
				continue;


			//�ж���ײ���Ƿ��� CA ����
			Vec3Cross( &vSideNormal, &rFace.vNormal, &vCA );
			vSideNormal.Normalize();

			if( vSideNormal.GetDot( -vBC ) < 0.0f )
				vSideNormal = -vSideNormal;

			fTerm = pRigidCylinder->_GetCylinderTerm( vCylinderDir, vSideNormal );

			fSideDist = vSideNormal.GetDot( vC ) - fTerm;
			if( vSideNormal.GetDot( vSideJudgePos ) - fSideDist < 0.0f )
				continue;

			fSideDist = vSideNormal.GetDot( vB ) + fTerm;
			if( vSideNormal.GetDot( vSideJudgePos ) - fSideDist > 0.0f )
				continue;

			//�����ε���ײ�������
			if( fDist < pInfo->fCollisionDist )
			{
				vCollisionPos = vIntersectPos;
				pCollisionFace = &mpBoundFace[i];
				pInfo->fCollisionDist = fDist;
			}
		}

		//���������ײ
		if( pCollisionFace != NULL )
		{
			//����ײĿ���ӷ��߷���ƽ��һС�ξ��룬�Է���һ֡��Խƽ�档
			pInfo->vCollisionPos = ( vCollisionPos + pCollisionFace->vNormal * FK_EPSILON ) * mpBoundNode->mWorldMatrix;
			pInfo->vFaceNormal = pCollisionFace->vNormal * mpBoundNode->mWorldMatrix;
			pInfo->pCollisionVolume = this;
			pInfo->bCollision = true;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
