/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SceneNode
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
	SceneNode::SceneNode()
	{
		mLightList.Initialize( 2, 6 );
		mCameraList.Initialize( 2, 6 );
		mRenderInstList.Initialize( 20, 20 );
	}
	//--------------------------------------------------------------------------------------------------------------
	SceneNode::~SceneNode()
	{
		DetachAllRenderInstance();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ҽӵƹ�
	void SceneNode::AttachLight( Light* pLight )
	{
		*mLightList.Push() = pLight;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Ͽ��ƹ�
	void SceneNode::DetachLight( Light* pLight )
	{
		LightList::Iterator it = mLightList.Begin();
		LightList::Iterator end = mLightList.End();
		for(; it!=end; ++it )
		{
			if( *it == pLight )
			{
				mLightList.Erase( it );
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ҽ������
	void SceneNode::AttachCamera( Camera* pCamera )
	{
		*mCameraList.Push() = pCamera;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Ͽ������
	void SceneNode::DetachCamera( Camera* pCamera )
	{
		CameraList::Iterator it = mCameraList.Begin();
		CameraList::Iterator end = mCameraList.End();
		for(; it!=end; ++it )
		{
			if( *it == pCamera )
			{
				mCameraList.Erase( it );
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ҽ���Ⱦʵ��
	void SceneNode::AttachRenderInstance( RenderInstance* pInstance )
	{
		*mRenderInstList.Push() = pInstance;

		//����ʵ�������ڵ�ָ��
		pInstance->mpSceneNode = this;

		//����ҽ�ʵ��Ϊ�ɼ�ѡ��Ⱦʵ��
		if( pInstance->mbCullable )
		{
			//֪ͨ���ڵ���Ҫ���¹ҽ������Χ��
			mbUpdateObjBox = true;
			_NotifyParentUpdateBox();
		}
		//����ҽ�ʵ��Ϊ�Ǽ�ѡ��Ⱦʵ��
		else
		{
			//������ӵ������������Ǽ�ѡ��Ⱦʵ��������
			*Root::mpSingleton->mpSceneManager->mNoCullRenderInsts.Push() = pInstance;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Ͽ���Ⱦʵ��
	void SceneNode::DetachRenderInstance( RenderInstance* pInstance )
	{
		//��ָ����Ⱦʵ���Ӹýڵ����Ⱦʵ���б���ɾ��
		RenderInstList::Iterator it = mRenderInstList.Begin();
		RenderInstList::Iterator end = mRenderInstList.End();
		for(; it!=end; ++it )
		{
			if( *it == pInstance )
			{
				mRenderInstList.Erase( it );
				break;
			}
		}
		pInstance->mpSceneNode = NULL;

		//����Ͽ�ʵ��Ϊ�ɼ�ѡ��Ⱦʵ��
		if( pInstance->mbCullable )
		{
			//֪ͨ���ڵ���Ҫ���¹ҽ������Χ��
			mbUpdateObjBox = true;
			_NotifyParentUpdateBox();
		}
		//����Ͽ�ʵ��Ϊ�Ǽ�ѡ��Ⱦʵ��
		else
		{
			//�����ӳ����������ķǼ�ѡʵ���б���ɾ��
			RenderInstList& NoCullInsts = Root::mpSingleton->mpSceneManager->mNoCullRenderInsts;
			RenderInstList::Iterator it = NoCullInsts.Begin();
			RenderInstList::Iterator end = NoCullInsts.End();
			for(; it!=end; ++it )
			{
				if( *it == pInstance )
				{
					NoCullInsts.Erase( it );
					return;
				}
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Ͽ�������Ⱦʵ��
	void SceneNode::DetachAllRenderInstance()
	{
		//��ָ��ʵ���Ӹýڵ����Ⱦʵ���б���ɾ��
		RenderInstList::Iterator it = mRenderInstList.Begin();
		RenderInstList::Iterator end = mRenderInstList.End();
		for(; it!=end; ++it )
		{
			RenderInstance* pInstance = *it;
			pInstance->mpSceneNode = NULL;

			//����Ͽ�ʵ��Ϊ�Ǽ�ѡʵ��
			if( !pInstance->mbCullable )
			{
				//�����ӳ����������ķǼ�ѡʵ���б���ɾ��
				RenderInstList& NoCullInsts = Root::mpSingleton->mpSceneManager->mNoCullRenderInsts;
				RenderInstList::Iterator it = NoCullInsts.Begin();
				RenderInstList::Iterator end = NoCullInsts.End();
				for(; it!=end; ++it )
				{
					if( *it == pInstance )
					{
						NoCullInsts.Erase( it );
						continue;
					}
				}
			}
		}

		mRenderInstList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ڵ㴴������
	TransformNode* FKFastcall SceneNode::_NodeCreator()
	{
		return new SceneNode;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ڵ�ҽ������Χ��
	const AxisBox3& FKFastcall SceneNode::_GetLocalObjectBox()
	{
		//����ýڵ�ҽ������Χ����Ҫ����
		if( mbUpdateObjBox )
		{
			mObjBoundBox.SetEmpty( true );

			RenderInstList::Iterator it = mRenderInstList.Begin();
			RenderInstList::Iterator end = mRenderInstList.End();
			for(; it!=end; ++it )
				mObjBoundBox.Combine( (*it)->mpRenderObject->mBoundBox );

			mbUpdateObjBox = false;
		}

		return mObjBoundBox;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ýڵ��µ�������Ⱦʵ��������Ⱦ����
	void FKFastcall SceneNode::_AddInstanceToQueue( RenderQueue* pRenderQueue )
	{
		RenderInstList::Iterator it = mRenderInstList.Begin();
		RenderInstList::Iterator end = mRenderInstList.End();
		for(; it!=end; ++it )
		{
			RenderInstance* pInstance = *it;

			//���Ϊ�Ǽ�ѡ��Ⱦʵ�����Թ��������ڳ����������Ǽ�ѡ��Ⱦʵ�������б�������
			if( !pInstance->mbCullable )
				continue;

			//�����Ⱦʵ���ɼ�
			if( pInstance->mbVisable )
			{
				//���������Ⱦ����
				pRenderQueue->AddRenderInstance( pInstance );
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ýڵ㼰���ӽڵ��µĿɼ���Ⱦʵ��
	void FKFastcall SceneNode::_GetVisibleInstance( Camera* pActiveCam, RenderQueue* pRenderQueue )
	{
		//�жϱ��ڵ��Ƿ�ɼ�����Ϊ�ڵ�İ�Χ�а����˸ýڵ���������Ⱦʵ������������ɼ��������е�ʵ�������ɼ�����
		if( mNodeBoundBox.mbEmpty || !pActiveCam->mViewFrustum.IsIntersect( mBoundBoxVer ) )
			return;

		//��ӱ��ڵ��������Ⱦʵ������Ⱦ������
		_AddInstanceToQueue( pRenderQueue );

		//���е��ӽڵ�һ��һ����ѭ�����ж��Ƿ�ɼ���
		TransformNodeList::Iterator itChild = mNodeChildren.Begin();
		TransformNodeList::Iterator itChildEnd = mNodeChildren.End();
		for(; itChild != itChildEnd; ++itChild )
		{
			SceneNode* pNode = static_cast< SceneNode* >( *itChild );
			pNode->_GetVisibleInstance( pActiveCam, pRenderQueue );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//֪ͨ��Χ���Ѹ���
	void FKFastcall SceneNode::_NotifyBoxUpdated()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
