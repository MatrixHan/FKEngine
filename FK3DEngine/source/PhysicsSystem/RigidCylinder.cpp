/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RigidCylinder
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
	RigidCylinder::RigidCylinder()
		: mRadius		(0.0f)
		, mHeight		(0.0f)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ײ�崴������
	RigidBody* RigidCylinder::Creator()
	{
		return new RigidCylinder;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ø���Բ����
	void FKFastcall RigidCylinder::SetRigidCylinder( float fRadius, float fHeight )
	{
		mRadius = fRadius;
		mHeight = fHeight;

		float fHalfHeight = fHeight * 0.5f;

		mBoundBox.SetMaxMin( fRadius, fHalfHeight, fRadius, -fRadius, -fHalfHeight, -fRadius );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����˶�״̬
	bool FKFastcall RigidCylinder::_UpdateMovement()
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
	void FKFastcall RigidCylinder::_DoCollisionDetect( BoundVolume* pBoundVolume, CollisionInfo* pInfo )
	{
		//������ײ���
		if( mLinearMoveLen == 0.0f )
			return;

		pBoundVolume->DoCollisionDetect( this, pInfo );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ĳ�����ϵ�Բ�����⾶
	float FKFastcall RigidCylinder::_GetCylinderTerm( const Vector3& vDirection, const Vector3& vNormal )
	{
		float fAbsNdW = Abs( vNormal.GetDot( vDirection ) );
		float fRoot = Sqrt( Abs( 1.0 - fAbsNdW * fAbsNdW ) );
		return mRadius * fRoot + mHeight * 0.5f * fAbsNdW;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
