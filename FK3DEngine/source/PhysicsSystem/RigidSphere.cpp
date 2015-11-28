/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RigidSphere
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
	RigidSphere::RigidSphere()
		: mRadius		(0.0f)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ײ�崴������
	RigidBody* RigidSphere::Creator()
	{
		return new RigidSphere;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ø�������
	void FKFastcall RigidSphere::SetRigidSphere( float fRadius )
	{
		mRadius = fRadius;

		mBoundBox.SetMaxMin( fRadius, fRadius, fRadius, -fRadius, -fRadius, -fRadius );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����˶�״̬
	bool FKFastcall RigidSphere::_UpdateMovement()
	{
		//���������ƶ����Ⱥͷ���
		mLinearMoveLen = mLinearMove.GetLength();
		mLinearMoveDir = mLinearMove.GetNormalizedVecFast( mLinearMoveLen );

		//�����˶���Χ��Χ��
		mMovementBox.mMaxVer = mBoundBox.mMaxVer + mMassCenter;
		mMovementBox.mMinVer = mBoundBox.mMinVer + mMassCenter;
		mMovementBox.mbEmpty = false;

		if( mLinearMove.x >= 0 )
			mMovementBox.mMaxVer.x += mLinearMove.x;
		else
			mMovementBox.mMinVer.x += mLinearMove.x;

		if( mLinearMove.y >= 0 )
			mMovementBox.mMaxVer.y += mLinearMove.y;
		else
			mMovementBox.mMinVer.y += mLinearMove.y;

		if( mLinearMove.z >= 0 )
			mMovementBox.mMaxVer.z += mLinearMove.z;
		else
			mMovementBox.mMinVer.z += mLinearMove.z;

		//���û���˶���ֱ�ӷ���
		if( mLinearMove == Vector3::Zero )
			return false;

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ײ���
	void FKFastcall RigidSphere::_DoCollisionDetect( BoundVolume* pBoundVolume, CollisionInfo* pInfo )
	{
		//������ײ���
		if( mLinearMoveLen == 0.0f )
			return;

		pBoundVolume->DoCollisionDetect( this, pInfo );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
