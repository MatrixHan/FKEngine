/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BoundNode
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ײ�ڵ���
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class BoundNode;
	typedef Stack< BoundNode* >		BoundNodeList;
	//--------------------------------------------------------------------------------------------------------------
	//��ײ�ڵ���
	class FK_DLL BoundNode
	{
	public:
		BoundNodeList		mChildNodeList;		//����ײ�ڵ��б�
		BoundVolumeList		mBoundVolumeList;	//�ҽ���ײ���б�

		BoundNode*			mpParentNode;		//������ײ�ڵ�

		Matrix4				mLocalMatrix;		//��ײ�ڵ�ֲ��������
		Matrix4				mWorldMatrix;		//��ײ�ڵ������������
		Matrix4				mInvWorldMatrix;	//��ײ�ڵ��������귴����

		bool				mbUpdateLocalMatrix;//�Ƿ���Ҫ���¾ֲ��������
		bool				mbUpdateWorldMatrix;//�Ƿ���Ҫ���������������
		bool				mbUpdateChildMatrix;//����ĳЩ�ӽڵ��Ƿ���Ҫ���¾���

		Vector3				mPosition;			//λ��ʸ��
		Quaternion			mOrientation;		//��ת��Ԫ��
		Vector3				mScale;				//����ʸ��

		static Quaternion	mTmpQuat;			//������ʱ��Ԫ��

	public:
		BoundNode();
		~BoundNode();

		//��������ײ�ڵ�
		BoundNode* CreateChild();

		//ɾ��ָ���ӽڵ�
		void DeleteChild( BoundNode* pChild );

		//ɾ�������ӽڵ�
		void DeleteAllChild();

		//�ҽ���ײ��
		void AttachBoundVolume( BoundVolume* pBoundVolume );

		//�Ͽ���ײ��
		void DetachBoundVolume( BoundVolume* pBoundVolume );

		//λ�ƽڵ㣨��ԣ�
		void TranslateNode( const Vector3& vTrans );
		void TranslateNode( const float x, const float y, const float z );
		//λ�ƽڵ�
		void SetPosition( const Vector3& vTrans );
		void SetPosition( const float x, const float y, const float z );

		//��ת�ڵ㣨��ԣ�
		void RotateNode( const Vector3& vAxis, const float fDegree );
		void RotateNode( const Quaternion& rQuat );
		//��ת�ڵ�
		void SetRotate( const Vector3& vAxis, const float fDegree );
		void SetRotate( const Quaternion& rQuat );
		void SetRotate( const float fPitch, const float fYaw, const float fRoll );

		//�� X ����ת����ԣ�
		void Pitch( const float fDegree );
		//�� Y ����ת����ԣ�
		void Yaw( const float fDegree );
		//�� Z ����ת����ԣ�
		void Roll( const float fDegree );

		//���Žڵ㣨��ԣ�
		void ScaleNode( const Vector3& vScl );
		void ScaleNode( const float x, const float y, const float z );
		//���Žڵ�
		void SetScale( const Vector3& vScl );
		void SetScale( const float x, const float y, const float z );

		//֪ͨ���ڵ���Ҫ���¾���
		void FKFastcall _NotifyParentUpdateMatrix();

		//���½ڵ����
		void FKFastcall _UpdateMatrix();

		//������ײ�����������Χ��
		void FKFastcall _UpdateBoundVolumeBox();

		//��ȡ��ָ����Χ���ཻ����ײ��
		void FKFastcall _GetIntersectBoundVolume( BoundVolumeList* pBoundVolumeList, const AxisBox3& refBoundBox );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
