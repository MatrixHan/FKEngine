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
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderWrapper/RenderWrapperInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	TransformNode::TransformNode()
		: mpParentNode			(NULL)
		, mPosition				(Vector3::Zero)
		, mScale				(Vector3::Identity)
		, mOrientation			(Quaternion::Identity)
		, mDerivedPosition		(Vector3::Zero)
		, mDerivedScale			(Vector3::Identity)
		, mDerivedOrientation	(Quaternion::Identity)
		, mLocalMatrix			(Matrix4::Identity)
		, mWorldMatrix			(Matrix4::Identity)
		, mbUpdateLocalMatrix	(false)
		, mbUpdateWorldMatrix	(false)
		, mbUpdateChildMatrix	(false)
		, mbUpdateNodeBox		(false)
	{
		mNodeChildren.Initialize( 20, 20 );
	}
	//--------------------------------------------------------------------------------------------------------------
	TransformNode::~TransformNode()
	{
		DeleteAllChild();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ӽڵ�
	TransformNode* TransformNode::CreateChild()
	{
		TransformNode* pNewNode = _NodeCreator();

		pNewNode->SetParent( this );

		return pNewNode;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ���ӽڵ�
	void TransformNode::DeleteChild( TransformNode* pNode )
	{
		if( pNode == NULL )
			return;

		TransformNodeList::Iterator it = mNodeChildren.Begin();
		TransformNodeList::Iterator end = mNodeChildren.End();
		for(; it!=end; ++it )
		{
			if( *it == pNode )
			{
				SafeDelete( pNode );
				mNodeChildren.Erase( it );
				return;
			}
		}

		//֪ͨ���ڵ���Ҫ���°�Χ��
		_NotifyParentUpdateBox();
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�������ӽڵ�
	void TransformNode::DeleteAllChild()
	{
		TransformNodeList::Iterator it = mNodeChildren.Begin();
		TransformNodeList::Iterator end = mNodeChildren.End();
		for(; it!=end; ++it )
			SafeDelete( *it );

		mNodeChildren.Clear();

		//֪ͨ���ڵ���Ҫ���°�Χ��
		_NotifyParentUpdateBox();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ı䱾�ڵ㵽��һ���ڵ���
	void TransformNode::SetParent( TransformNode* pNewParent )
	{
		if( pNewParent == NULL )
			return;

		//���ýڵ�����ĸ��ڵ���ӽڵ��б���ɾ��
		if( mpParentNode != NULL )
		{
			TransformNodeList::Iterator it = mpParentNode->mNodeChildren.Begin();
			TransformNodeList::Iterator end = mpParentNode->mNodeChildren.End();
			for(; it!=end; ++it )
			{
				if( *it == this )
				{
					mpParentNode->mNodeChildren.Erase(it);
					break;
				}
			}

			//֪ͨԭ���ڵ���Ҫ���°�Χ��
			mpParentNode->_NotifyParentUpdateBox();
		}

		//֪ͨ�¸��ڵ���Ҫ���°�Χ��
		pNewParent->_NotifyParentUpdateBox();

		//Ȼ������뵽�µĸ��ڵ���
		*pNewParent->mNodeChildren.Push() = this;
		mpParentNode = pNewParent;

		//���¼̳б任����
		_UpdateDerivedTransform();
	}
	//--------------------------------------------------------------------------------------------------------------
	//λ�ƽڵ㣨��ԣ�
	void TransformNode::Translate( const Vector3& vTrans, TransformSpace eRelativeTo )
	{
		switch (eRelativeTo)
		{
		case TS_Local:
			{
				mPosition += mOrientation * vTrans;
				break;
			}
		case TS_World:
			{
				if( mpParentNode != NULL )
					mPosition += mpParentNode->mDerivedOrientation * vTrans;
				else
					mPosition += vTrans;
				break;
			}
		case TS_Parent:
			{
				mPosition += vTrans;
				break;
			}
		}

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	void TransformNode::Translate( const float x, const float y, const float z, TransformSpace eRelativeTo )
	{
		Translate( Vector3( x, y, z ), eRelativeTo );
	}
	//--------------------------------------------------------------------------------------------------------------
	//λ�ƽڵ�
	void TransformNode::SetPosition( const Vector3& vTrans )
	{
		mPosition = vTrans;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	void TransformNode::SetPosition( const float x, const float y, const float z )
	{
		mPosition.x = x;
		mPosition.y = y;
		mPosition.z = z;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ת�ڵ㣨��ԣ�
	void TransformNode::Rotate( const Quaternion& rQuat, TransformSpace eRelativeTo )
	{
		switch (eRelativeTo)
		{
		case TS_Parent:
			{
				mOrientation = rQuat * mOrientation;
				break;
			}
		case TS_World:
			{
				mOrientation = mOrientation * mDerivedOrientation.GetInverse() * rQuat * mDerivedOrientation;
				break;
			}
		case TS_Local:
			{
				mOrientation = mOrientation * rQuat;
				break;
			}
		}

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	void TransformNode::Rotate( const Vector3& vAxis, const float fDegree, TransformSpace eRelativeTo )
	{
		Rotate( Quaternion( fDegree, vAxis ), eRelativeTo );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ת�ڵ�
	void TransformNode::SetRotate( const Vector3& vAxis, const float fDegree )
	{
		mOrientation.SetRotationAxis( fDegree, vAxis );

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	void TransformNode::SetRotate( const Quaternion& rQuat )
	{
		mOrientation = rQuat;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	void TransformNode::SetRotate( const float fPitch, const float fYaw, const float fRoll )
	{
		mOrientation.SetRotationPitchYawRoll( fPitch, fYaw, fRoll );

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�� X ����ת����ԣ�
	void TransformNode::Pitch( const float fDegree, TransformSpace eRelativeTo )
	{
		Rotate( Quaternion( fDegree, Vector3::UnitX ), eRelativeTo );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�� Y ����ת����ԣ�
	void TransformNode::Yaw( const float fDegree, TransformSpace eRelativeTo )
	{
		Rotate( Quaternion( fDegree, Vector3::UnitY ), eRelativeTo );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�� Z ����ת����ԣ�
	void TransformNode::Roll( const float fDegree, TransformSpace eRelativeTo )
	{
		Rotate( Quaternion( fDegree, Vector3::UnitZ ), eRelativeTo );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���Žڵ㣨��ԣ�
	void TransformNode::Scale( const Vector3& vScl )
	{
		mScale *= vScl;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	void TransformNode::Scale( const float x, const float y, const float z )
	{
		static Vector3 scalVec;

		scalVec.x = x;	scalVec.y = y;	scalVec.z = z;
		mScale *= scalVec;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���Žڵ�
	void TransformNode::SetScale( const Vector3& vScl )
	{
		mScale = vScl;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	void TransformNode::SetScale( const float x, const float y, const float z )
	{
		mScale.x = x;
		mScale.y = y;
		mScale.z = z;

		mbUpdateLocalMatrix = true;
		_NotifyParentUpdateMatrix();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¼̳б任����
	void FKFastcall TransformNode::_UpdateDerivedTransform()
	{
		if( mpParentNode != NULL )
		{
			mDerivedOrientation = mpParentNode->mDerivedOrientation * mOrientation;
			mDerivedPosition = mpParentNode->mDerivedOrientation * ( mPosition * mpParentNode->mDerivedScale );
			mDerivedScale = mScale * mpParentNode->mDerivedScale;

			Mat4TransMat4( &mWorldMatrix, &mLocalMatrix, &mpParentNode->mWorldMatrix );
		}
		else
		{
			mDerivedOrientation = mOrientation;
			mDerivedPosition = mPosition;
			mDerivedScale = mScale;

			mWorldMatrix = mLocalMatrix;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//֪ͨ���ڵ���Ҫ���¾���
	void FKFastcall TransformNode::_NotifyParentUpdateMatrix()
	{
		//������ڸ��ڵ���֪ͨ���ڵ���������Ҫ���µ��ӽڵ�
		if( mpParentNode != NULL && !mpParentNode->mbUpdateChildMatrix )
		{
			mpParentNode->mbUpdateChildMatrix = true;
			mpParentNode->_NotifyParentUpdateMatrix();
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//֪ͨ���ڵ���Ҫ���°�Χ��
	void FKFastcall TransformNode::_NotifyParentUpdateBox()
	{
		mbUpdateNodeBox = true;

		//������ڸ��ڵ���֪ͨ���ڵ���������Ҫ���µ��ӽڵ�
		if( mpParentNode != NULL && !mpParentNode->mbUpdateNodeBox )
			mpParentNode->_NotifyParentUpdateBox();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���½ڵ����
	void FKFastcall TransformNode::_UpdateMatrix()
	{
		//�Ӹ��ڵ�ݹ����������Ҫ���µĽڵ�
		TransformNode* pNode = NULL;

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
			TransformNodeList::Iterator it = mNodeChildren.Begin();
			TransformNodeList::Iterator itend = mNodeChildren.End();
			for(; it!=itend; ++it )
				(*it)->_UpdateMatrix();

			mbUpdateChildMatrix = false;
		}

		//����ýڵ���������������Ҫ����
		if( mbUpdateWorldMatrix )
		{
UpdateWorldMatrix:
			//���¸ýڵ�̳б任����
			_UpdateDerivedTransform();

			//���������ӽڵ�����������������Ҫ���ͬʱ������ֲ��������
			TransformNodeList::Iterator it = mNodeChildren.Begin();
			TransformNodeList::Iterator itend = mNodeChildren.End();
			for(; it!=itend; ++it )
			{
				pNode = *it;
				pNode->mbUpdateWorldMatrix = true;
				pNode->_UpdateMatrix();
			}

			mbUpdateWorldMatrix = false;
			mbUpdateChildMatrix = false;

			//֪ͨ�������½ڵ��Χ��
			_NotifyParentUpdateBox();
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���½ڵ����������Χ��
	void FKFastcall TransformNode::_UpdateBox()
	{
		//�ݹ����������Ҫ���°�Χ�е��ӽڵ㣨���ȸ���ĩ���ӽڵ�İ�Χ�У�
		TransformNode* pNode = NULL;

		//����ýڵ���Ҫ���°�Χ��
		if( mbUpdateNodeBox )
		{
			//���������ӽڵ�İ�Χ��
			TransformNodeList::Iterator itbeg = mNodeChildren.Begin();
			TransformNodeList::Iterator itend = mNodeChildren.End();
			for( TransformNodeList::Iterator it=itbeg; it!=itend; ++it )
				(*it)->_UpdateBox();

			//���¸ýڵ�ľֲ������Χ��

			//��ȡ�ڵ�ҽ������Χ��
			mNodeBoundBox = _GetLocalObjectBox();

			//�ϲ��ýڵ��������ӽڵ�ľֲ������Χ��
			for( TransformNodeList::Iterator it=itbeg; it!=itend; ++it )
				mNodeBoundBox.Combine( (*it)->mNodeBoundBox );

			if( mNodeBoundBox.mbEmpty )
				return;

			//��ȡ�ڵ����������Χ�м�ת������
			mNodeBoundBox.GetTransform( &mWorldBoundBox, mWorldMatrix, mBoundBoxVer );

			//����Χ��ת�����ýڵ�ֲ�����
			mNodeBoundBox.Transform( mLocalMatrix );

			//֪ͨ��Χ���Ѹ���
			_NotifyBoxUpdated();

			mbUpdateNodeBox = false;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
