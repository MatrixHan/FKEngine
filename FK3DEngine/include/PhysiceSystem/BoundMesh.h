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
*	�ļ�˵����	��ײ������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��ײ������
	class FK_DLL BoundMesh : public BoundVolume
	{
	public:
		UINT			mNumFace;			//��������������
		UINT			mNumVertex;			//�����涥������

		BoundFace*		mpBoundFace;		//��ײ����������
		Vector3*		mpFaceVertex;		//�����涥������

	public:
		BoundMesh();
		~BoundMesh();

		//��ײ�崴������
		static BoundVolume* Creator();

		//������ײ��������
		void LoadBoundMesh( BoundInfo* pBoundInfo, BoundFace* pBoundFace, Vector3* pVertex );

		//�����ཻ����
		bool Intersect( const Ray3* pRay, Vector3* pContactPos );

		//�߶��ཻ����
		bool Intersect( const Segment3* pSegment, Vector3* pContactPos );

		//����������ײ���
		void DoCollisionDetect( RigidSphere* pRigidSphere, CollisionInfo* pInfo );

		//����Բ������ײ���
		void DoCollisionDetect( RigidCylinder* pRigidCylinder, CollisionInfo* pInfo );
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< BoundMesh* >		BoundMeshList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
