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
*	�ļ�˵����	����Բ������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//����Բ����
	class FK_DLL RigidCylinder : public RigidBody
	{
	public:
		float		mRadius;	//Բ����뾶
		float		mHeight;	//Բ����߶�

	public:
		RigidCylinder();

		//��ײ�崴������
		static RigidBody* Creator();

		//���ø���Բ����
		void FKFastcall SetRigidCylinder( float fRadius, float fHeight );

	protected:
		//�����˶�״̬
		bool FKFastcall _UpdateMovement();

		//������ײ���
		void FKFastcall _DoCollisionDetect( BoundVolume* pBoundVolume, CollisionInfo* pInfo );

	public:
		//����ĳ�����ϵ�Բ�����⾶
		float FKFastcall _GetCylinderTerm( const Vector3& vDirection, const Vector3& vNormal );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
