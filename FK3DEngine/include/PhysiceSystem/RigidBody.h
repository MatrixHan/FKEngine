/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RigidBody
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//������
	class FK_DLL RigidBody
	{
	public:
		friend class PhysicsSystem;

		//���崴������
		typedef RigidBody* (*FnCreator)();

	public:
		Vector3			mMassCenter;	//������������

		Vector3			mLinearMove;	//�����ƶ���
		Vector3			mLinearMoveDir;	//�����ƶ�����
		float			mLinearMoveLen;	//�����ƶ�����

		AxisBox3			mBoundBox;		//�����Χ�У��ֲ����꣩
		AxisBox3			mMovementBox;	//�˶���Χ��Χ�У��������꣩

	public:
		RigidBody();
		virtual ~RigidBody() = 0;

		//����������������
		void FKFastcall SetMassCenter( const Vector3& vMassCenter );

		//���������ƶ���
		void FKFastcall SetLinearMove( const Vector3& vLinearMove );

	protected:
		//�����˶�״̬
		virtual bool FKFastcall _UpdateMovement() = 0;

		//������ײ���
		virtual void FKFastcall _DoCollisionDetect( BoundVolume* pBoundVolume, CollisionInfo* pInfo ) = 0;
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< RigidBody* >		RigidBodyList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
