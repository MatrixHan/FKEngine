/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BoundVolume
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ײ����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	/*
		ʸ����ƽ���ཻ������׷�٣����㹫ʽ��

		������ƽ���ཻ�㣺	RayOnPlane3	��ƽ���ϵ�һ�� �� ������ƽ���ཻ�㣩
		ƽ�淨�ߣ�			Plane3Nor
		ƽ���ԭ����룺	Plane3Dist
		������ʼ�㣺		RayStart
		���߽����㣺		RayEnd
		�����˶�����		MoveDir
		�����˶����룺		MoveLen

		RayOnPlane3	= RayStart + MoveLen * MoveDir
		Plane3Dist	= RayOnPlane3 ��� Plane3Nor

		�ȼ۴��룺
		Plane3Dist	= ( RayStart + MoveLen * MoveDir ) ��� Plane3Normal
		= RayStart ��� Plane3Normal + MoveLen * MoveDir ��� Plane3Normal
		���ҽ�����
		MoveLen	* MoveDir ��� Plane3Nor = Plane3Dist - RayStart ��� Plane3Normal
		MoveLen = ( Plane3Dist - RayStart ��� Plane3Normal )				/ ( MoveDir ��� Plane3Normal )
		= ( RayOnPlane3 ��� Plane3Normal - RayStart ��� Plane3Normal )	/ ( MoveDir ��� Plane3Normal )
		= ( ( RayOnPlane3 - RayStart ) ��� Plane3Normal )			/ ( MoveDir ��� Plane3Normal )

		����ֻ�轫�ϸ������е� RayOnPlane3 �滻Ϊƽ��������һ�㼴�����
		MoveLen ������ù�����ƽ���ʵ���ཻ��  ��ѧ��������������ȥ�� ����
	*/
	//--------------------------------------------------------------------------------------------------------------
	class BoundNode;
	class RigidBody;
	class RigidSphere;
	class RigidCylinder;
	class BoundVolume;
	//--------------------------------------------------------------------------------------------------------------
	//��ײ��Ϣ
	struct CollisionInfo
	{
		bool			bCollision;			//�Ƿ�����ײ
		float			fCollisionDist;		//��ײ����
		Vector3			vCollisionPos;		//��ײ����λ��
		Vector3			vFaceNormal;		//��ײ�淨��
		BoundVolume*	pCollisionVolume;	//��ײ��ָ��
	};
	//--------------------------------------------------------------------------------------------------------------
	//��ײ����
	class FK_DLL BoundVolume
	{
	public:
		//��ײ�崴������
		typedef BoundVolume* (*FnCreator)();

	public:
		BoundNode*		mpBoundNode;		//�ҽ���ײ�ڵ�ָ��

		AxisBox3			mLocalBoundBox;		//��ײ��ֲ������Χ��
		AxisBox3			mWorldBoundBox;		//��ײ�����������Χ��

		BoundInfo::Type	mBoundType;			//��ײ����

	public:
		BoundVolume();
		virtual ~BoundVolume() = 0;

		//�����ཻ����
		virtual bool Intersect( const Ray3* pRay, Vector3* pContactPos ) = 0;

		//�߶��ཻ����
		virtual bool Intersect( const Segment3* pSegment, Vector3* pContactPos ) = 0;

		//����������ײ���
		virtual void DoCollisionDetect( RigidSphere* pRigidSphere, CollisionInfo* pInfo ) = 0;

		//����Բ������ײ���
		virtual void DoCollisionDetect( RigidCylinder* pRigidCylinder, CollisionInfo* pInfo ) = 0;
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< BoundVolume* >	BoundVolumeList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
