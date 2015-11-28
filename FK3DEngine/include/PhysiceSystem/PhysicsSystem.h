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
*	�ļ�˵����	����ϵͳ
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//����ϵͳ
	class FK_DLL PhysicsSystem : public Singleton< PhysicsSystem >
	{
	public:
		BoundVolumeList		mBoundVolumeList;		//��ײ���б�
		RigidBodyList		mRigidBodyList;			//�����б�

		BoundNode			mRootBoundNode;			//������ײ�ڵ�

	protected:
		BoundVolumeList		mIntersectVolumeList;	//�ཻ��ײ���ջ

	public:
		PhysicsSystem();
		~PhysicsSystem();

		//������ײ��
		BoundVolume* CreateBoundVolume( BoundVolume::FnCreator fnCreator );

		//��������
		RigidBody* CreateRigidBody( RigidBody::FnCreator fnCreator );

		//ɾ��ָ����ײ�ڵ�
		void DeleteBoundNode( BoundNode* pBoundNode );

		//ɾ��ָ����ײ��
		void DeleteBoundVolume( BoundVolume* pBoundVolume );

		//ɾ��ָ������
		void DeleteRigidBody( RigidBody* pRigidBody );

		//ɾ��������ײ��
		void DeleteAllBoundVolume();

		//ɾ�����и���
		void DeleteAllRigidBody();

		//������ײ���
		void DoCollisionDetect( RigidBody* pRigidBody, CollisionInfo* pCollisionInfo );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
