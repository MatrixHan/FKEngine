/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	TransformNode
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�任�ڵ���
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class TransformNode;
	typedef Stack< TransformNode* >		TransformNodeList;
	//--------------------------------------------------------------------------------------------------------------
	//�任�ڵ���
	class FK_DLL TransformNode
	{
	public:
		//�任�ռ�
		enum TransformSpace
		{
			TS_Local,		//����ھֲ��ռ�ı任
			TS_Parent,		//����ڸ����ռ�ı任
			TS_World		//���������ռ�ı任
		};

	public:
		Matrix4				mLocalMatrix;		//�任�ڵ�ֲ��������
		Matrix4				mWorldMatrix;		//�任�ڵ������������

		TransformNode*		mpParentNode;		//�����任�ڵ�

		Vector3				mPosition;			//λ��ʸ��
		Quaternion			mOrientation;		//��ת��Ԫ��
		Vector3				mScale;				//����ʸ��

		Vector3				mDerivedPosition;	//�̳�λ��ʸ��
		Quaternion			mDerivedOrientation;//�̳���ת��Ԫ��
		Vector3				mDerivedScale;		//�̳�����ʸ��

	protected:
		TransformNodeList	mNodeChildren;		//�ӽڵ��б�

		bool				mbUpdateLocalMatrix;//�Ƿ���Ҫ���¾ֲ��������
		bool				mbUpdateWorldMatrix;//�Ƿ���Ҫ���������������
		bool				mbUpdateChildMatrix;//����ĳЩ�ӽڵ��Ƿ���Ҫ���¾���

		bool				mbUpdateNodeBox;	//�Ƿ���Ҫ���½ڵ��Χ��

		AxisBox3			mNodeBoundBox;		//�ڵ�ֲ������Χ��
		AxisBox3			mWorldBoundBox;		//�ڵ����������Χ��
		Vector3				mBoundBoxVer[8];	//�ڵ����������Χ�ж���

	public:
		TransformNode();
		virtual ~TransformNode();

		//�����ӽڵ�
		TransformNode* CreateChild();

		//ɾ���ӽڵ�
		void DeleteChild( TransformNode* pNode );

		//ɾ�������ӽڵ�
		void DeleteAllChild();

		//�ı��ӽڵ㵽��һ���ڵ���
		void SetParent( TransformNode* pNewParent );

		//λ�ƽڵ㣨��ԣ�
		void Translate( const Vector3& vTrans, TransformSpace eRelativeTo = TS_Parent );
		void Translate( const float x, const float y, const float z, TransformSpace eRelativeTo = TS_Parent );

		//λ�ƽڵ�
		void SetPosition( const Vector3& vTrans );
		void SetPosition( const float x, const float y, const float z );

		//��ת�ڵ㣨��ԣ�
		void Rotate( const Quaternion& rQuat, TransformSpace eRelativeTo = TS_Local );
		void Rotate( const Vector3& vAxis, const float fDegree, TransformSpace eRelativeTo = TS_Local );

		//��ת�ڵ�
		void SetRotate( const Vector3& vAxis, const float fDegree );
		void SetRotate( const Quaternion& rQuat );
		void SetRotate( const float fPitch, const float fYaw, const float fRoll );

		//�� X ����ת����ԣ�
		void Pitch( const float fDegree, TransformSpace eRelativeTo = TS_Local );
		//�� Y ����ת����ԣ�
		void Yaw( const float fDegree, TransformSpace eRelativeTo = TS_Local );
		//�� Z ����ת����ԣ�
		void Roll( const float fDegree, TransformSpace eRelativeTo = TS_Local );

		//���Žڵ㣨��ԣ�
		void Scale( const Vector3& vScl );
		void Scale( const float x, const float y, const float z );

		//���Žڵ�
		void SetScale( const Vector3& vScl );
		void SetScale( const float x, const float y, const float z );

	protected:
		//�ڵ㴴������
		virtual TransformNode* FKFastcall _NodeCreator() = 0;

		//��ȡ�ڵ�ҽ������Χ��
		virtual const AxisBox3& FKFastcall _GetLocalObjectBox() = 0;

		//���¼̳б任����
		void FKFastcall _UpdateDerivedTransform();

		//֪ͨ���ڵ���Ҫ���¾���
		void FKFastcall _NotifyParentUpdateMatrix();

		//֪ͨ���ڵ���Ҫ���°�Χ��
		void FKFastcall _NotifyParentUpdateBox();

	public:
		//���½ڵ����
		void FKFastcall _UpdateMatrix();

		//���½ڵ����������Χ��
		void FKFastcall _UpdateBox();

		//֪ͨ��Χ���Ѹ���
		virtual void FKFastcall _NotifyBoxUpdated() = 0;
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
