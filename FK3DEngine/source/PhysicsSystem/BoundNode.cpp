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
	Quaternion BoundNode::mTmpQuat;	//������ʱ��Ԫ��
	//--------------------------------------------------------------------------------------------------------------
	BoundNode::BoundNode()
		: mpParentNode			(NULL)
		, mLocalMatrix			(Matrix4::Identity)
		, mWorldMatrix			(Matrix4::Identity)
		, mInvWorldMatrix		(Matrix4::Identity)
		, mbUpdateLocalMatrix	(false)
		, mbUpdateWorldMatrix	(false)
		, mbUpdateChildMatrix	(false)
		, mPosition				(Vector3::Zero)
		, mScale				(Vector3::Identity)
		, mOrientation			(Quaternion::Identity)
	{
		mChildNodeList.Initialize( 20, 20 );
		mBoundVolumeList.Initialize( 20, 20 );
	}
	//--------------------------------------------------------------------------------------------------------------
	BoundNode::~BoundNode()
	{
		DeleteAllChild();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ײ�ڵ�
	BoundNode* BoundNode::CreateChild()
	{
		BoundNode* pChild = new BoundNode;
		*mChildNodeList.Push() = pChild;
		pChild->mpParentNode = this;
		return pChild;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ָ���ӽڵ�
	void BoundNode::DeleteChild( BoundNode* pChild )
	{
		if( pChild == NULL )
			return;

		BoundNodeList::Iterator it = mChildNodeList.Begin();
		BoundNodeList::Iterator end = mChildNodeList.End();
		for(; it!=end; ++it )
		{
			if( *it == pChild )
			{
				SafeDelete( pChild );
				mChildNodeList.Erase( it );
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�������ӽڵ�
	void BoundNode::DeleteAllChild()
	{
		BoundNodeList::Iterator it = mChildNodeList.Begin();
		BoundNodeList::Iterator end = mChildNodeList.End();
		for(; it!=end; ++it )
			SafeDelete( *it );

		mChildNodeList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ҽ���ײ��
	void BoundNode::AttachBoundVolume( BoundVolume* pBoundVolume )
	{
		*mBoundVolumeList.Push() = pBoundVolume;
		pBoundVolume->mpBoundNode = this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Ͽ���ײ��
	void BoundNode::DetachBoundVolume( BoundVolume* pBoundVolume )
	{
		BoundVolumeList::Iterator it = mBoundVolumeList.Begin();
		BoundVolumeList::Iterator end = mBoundVolumeList.End();
		for(; it!=end; ++it )
		{
			if( *it == pBoundVolume )
			{
				mBoundVolumeList.Erase( it );
				pBoundVolume->mpBoundNode = NULL;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//λ�ƽڵ㣨��ԣ�
	void BoundNode::TranslateNode( const Vector3& vTrans )
	{
		mPosition += vTrans;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	void BoundNode::TranslateNode( const float x, const float y, const float z )
	{
		mPosition.x += x;
		mPosition.y += y;
		mPosition.z += z;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	//λ�ƽڵ�
	void BoundNode::SetPosition( const Vector3& vTrans )
	{
		mPosition = vTrans;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	void BoundNode::SetPosition( const float x, const float y, const float z )
	{
		mPosition.x = x;
		mPosition.y = y;
		mPosition.z = z;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ת�ڵ㣨��ԣ�
	void BoundNode::RotateNode( const Vector3& vAxis, const float fDegree )
	{
		mTmpQuat.SetRotationAxis( fDegree, vAxis );
		mOrientation *= mTmpQuat;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	void BoundNode::RotateNode( const Quaternion& rQuat )
	{
		mOrientation *= rQuat;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ת�ڵ�
	void BoundNode::SetRotate( const Vector3& vAxis, const float fDegree )
	{
		mOrientation.SetRotationAxis( fDegree, vAxis );

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	void BoundNode::SetRotate( const Quaternion& rQuat )
	{
		mOrientation = rQuat;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	void BoundNode::SetRotate( const float fPitch, const float fYaw, const float fRoll )
	{
		mOrientation.SetRotationPitchYawRoll( fPitch, fYaw, fRoll );

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�� X ����ת����ԣ�
	void BoundNode::Pitch( const float fDegree )
	{
		mTmpQuat.SetRotationAxis( fDegree, Vector3::UnitX );
		mOrientation *= mTmpQuat;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�� Y ����ת����ԣ�
	void BoundNode::Yaw( const float fDegree )
	{
		mTmpQuat.SetRotationAxis( fDegree, Vector3::UnitY );
		mOrientation *= mTmpQuat;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�� Z ����ת����ԣ�
	void BoundNode::Roll( const float fDegree )
	{
		mTmpQuat.SetRotationAxis( fDegree, Vector3::UnitZ );
		mOrientation *= mTmpQuat;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���Žڵ㣨��ԣ�
	void BoundNode::ScaleNode( const Vector3& vScl )
	{
		mScale *= vScl;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	void BoundNode::ScaleNode( const float x, const float y, const float z )
	{
		static Vector3 scalVec;

		scalVec.x = x;	scalVec.y = y;	scalVec.z = z;
		mScale *= scalVec;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���Žڵ�
	void BoundNode::SetScale( const Vector3& vScl )
	{
		mScale = vScl;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	void BoundNode::SetScale( const float x, const float y, const float z )
	{
		mScale.x = x;
		mScale.y = y;
		mScale.z = z;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	//֪ͨ���ڵ���Ҫ���¾���
	void FKFastcall BoundNode::_NotifyParentUpdateMatrix()
	{
		//������ڸ��ڵ���֪ͨ���ڵ���������Ҫ���µ��ӽڵ�
		if( mpParentNode != NULL && !mpParentNode->mbUpdateChildMatrix )
		{
			mpParentNode->mbUpdateChildMatrix = true;
			mpParentNode->_NotifyParentUpdateMatrix();
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���½ڵ����
	void FKFastcall BoundNode::_UpdateMatrix()
	{
		//�Ӹ��ڵ�ݹ����������Ҫ���µĽڵ�
		BoundNode* pNode = NULL;

		//����ýڵ�ֲ����������Ҫ����
		if( mbUpdateLocalMatrix )
		{
			//������ת����
			static Matrix4 matRota;
			mOrientation.GetRotationMatrix4( &matRota );

			//�������ž���
			static Matrix4 matScl;
			matScl.SetScaling( mScale.x, mScale.y, mScale.z );

			//���ɵ�ǰ�ڵ�ֲ��������
			Mat4TransMat4( &mLocalMatrix, &matScl, &matRota );

			//���þֲ��������ƽ��
			mLocalMatrix._41 = mPosition.x;	mLocalMatrix._42 = mPosition.y;	mLocalMatrix._43 = mPosition.z;

			mbUpdateLocalMatrix = false;

			//���¸ýڵ���������
			goto UpdateWorldMatrix;
		}
		//���߸ýڵ���ӽڵ���Ҫ����
		else if( mbUpdateChildMatrix )
		{
			//���������ӽڵ�ľ���
			BoundNodeList::Iterator it = mChildNodeList.Begin();
			BoundNodeList::Iterator itend = mChildNodeList.End();
			for(; it!=itend; ++it )
				(*it)->_UpdateMatrix();

			mbUpdateChildMatrix = false;
		}

		//����ýڵ���������������Ҫ����
		if( mbUpdateWorldMatrix )
		{
UpdateWorldMatrix:
			//�븸�����������ɸýڵ������������
			if( mpParentNode != NULL )
				Mat4TransMat4( &mWorldMatrix, &mLocalMatrix, &mpParentNode->mWorldMatrix );
			else
				mWorldMatrix = mLocalMatrix;

			Mat4Inverse( &mInvWorldMatrix, &mWorldMatrix );

			//���������ӽڵ�����������������Ҫ���ͬʱ������ֲ��������
			BoundNodeList::Iterator it = mChildNodeList.Begin();
			BoundNodeList::Iterator itend = mChildNodeList.End();
			for(; it!=itend; ++it )
			{
				pNode = *it;
				pNode->mbUpdateWorldMatrix = true;
				pNode->_UpdateMatrix();
			}

			mbUpdateWorldMatrix = false;

			//����������ײ�����������Χ��
			_UpdateBoundVolumeBox();
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ײ�����������Χ��
	void FKFastcall BoundNode::_UpdateBoundVolumeBox()
	{
		BoundVolumeList::Iterator it = mBoundVolumeList.Begin();
		BoundVolumeList::Iterator end = mBoundVolumeList.End();
		for(; it!=end; ++it )
		{
			BoundVolume* pBoundVolume = *it;
			pBoundVolume->mLocalBoundBox.GetTransform( &pBoundVolume->mWorldBoundBox, mWorldMatrix );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ָ����Χ���ཻ����ײ��
	void FKFastcall BoundNode::_GetIntersectBoundVolume( BoundVolumeList* pBoundVolumeList, const AxisBox3& refBoundBox )
	{
		//�����ýڵ���������ײ��
		BoundVolumeList::Iterator vit = mBoundVolumeList.Begin();
		BoundVolumeList::Iterator vend = mBoundVolumeList.End();
		for(; vit!=vend; ++vit )
		{
			BoundVolume* pBoundVolume = *vit;

			//���ָ����Χ����ð�Χ���ཻ
			if( pBoundVolume->mWorldBoundBox.IsIntersect( refBoundBox ) )
				*pBoundVolumeList->Push() = pBoundVolume;
		}

		//�ݹ��ȡ�ӽڵ���ཻ��ײ��
		BoundNodeList::Iterator nit = mChildNodeList.Begin();
		BoundNodeList::Iterator nend = mChildNodeList.End();
		for(; nit!=nend; ++nit )
			(*nit)->_GetIntersectBoundVolume( pBoundVolumeList, refBoundBox );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
