/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	PhysicsSystem
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
	PhysicsSystem::PhysicsSystem()
	{
		mBoundVolumeList.Initialize( 50, 50 );
		mRigidBodyList.Initialize( 10, 10 );

		mIntersectVolumeList.Initialize( 20, 20 );
	}
	//--------------------------------------------------------------------------------------------------------------
	PhysicsSystem::~PhysicsSystem()
	{
		DeleteAllBoundVolume();
		DeleteAllRigidBody();
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ײ��
	BoundVolume* PhysicsSystem::CreateBoundVolume( BoundVolume::FnCreator fnCreator )
	{
		BoundVolume* pBoundVolume = fnCreator();
		*mBoundVolumeList.Push() = pBoundVolume;
		return pBoundVolume;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	RigidBody* PhysicsSystem::CreateRigidBody( RigidBody::FnCreator fnCreator )
	{
		RigidBody* pRigidBody = fnCreator();
		*mRigidBodyList.Push() = pRigidBody;
		return pRigidBody;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ָ����ײ��
	void PhysicsSystem::DeleteBoundVolume( BoundVolume* pBoundVolume )
	{
		BoundVolumeList::Iterator it = mBoundVolumeList.Begin();
		BoundVolumeList::Iterator end = mBoundVolumeList.End();
		for(; it!=end; ++it )
		{
			if( *it == pBoundVolume )
			{
				mBoundVolumeList.Erase( it );
				delete pBoundVolume;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ָ������
	void PhysicsSystem::DeleteRigidBody( RigidBody* pRigidBody )
	{
		RigidBodyList::Iterator it = mRigidBodyList.Begin();
		RigidBodyList::Iterator end = mRigidBodyList.End();
		for(; it!=end; ++it )
		{
			if( *it == pRigidBody )
			{
				mRigidBodyList.Erase( it );
				delete pRigidBody;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��������ײ��
	void PhysicsSystem::DeleteAllBoundVolume()
	{
		BoundVolumeList::Iterator it = mBoundVolumeList.Begin();
		BoundVolumeList::Iterator end = mBoundVolumeList.End();
		for(; it!=end; ++it )
			SafeDelete( *it );

		mBoundVolumeList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����и���
	void PhysicsSystem::DeleteAllRigidBody()
	{
		RigidBodyList::Iterator it = mRigidBodyList.Begin();
		RigidBodyList::Iterator end = mRigidBodyList.End();
		for(; it!=end; ++it )
			SafeDelete( *it );

		mRigidBodyList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ײ���
	void PhysicsSystem::DoCollisionDetect( RigidBody* pRigidBody, CollisionInfo* pCollisionInfo )
	{
		memset( pCollisionInfo, 0, sizeof(CollisionInfo) );
		pCollisionInfo->fCollisionDist = FLT_MAX;

		//�����˶�����
		if( !pRigidBody->_UpdateMovement() )
			return;

		//��ȡ�����˶���Χ��Χ���ڵ���ײ��
		mIntersectVolumeList.Clear();
		mRootBoundNode._GetIntersectBoundVolume( &mIntersectVolumeList, pRigidBody->mMovementBox );

		//ѭ�����ÿ�����˶���Χ�ڵ���ײ��
		BoundVolumeList::Iterator it = mIntersectVolumeList.Begin();
		BoundVolumeList::Iterator end = mIntersectVolumeList.End();
		for(; it!=end; ++it )
			pRigidBody->_DoCollisionDetect( *it, pCollisionInfo );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
