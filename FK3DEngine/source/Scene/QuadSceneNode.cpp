/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	QuadSceneNode
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/Scene/SceneInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	QuadSceneNode::QuadSceneNode()
		: mpQuadNode	(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	QuadSceneNode::~QuadSceneNode()
	{
		if( mpQuadNode != NULL )
			mpQuadNode->_DetachQuadSceneNode( this );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ڵ㴴������
	TransformNode* FKFastcall QuadSceneNode::_NodeCreator()
	{
		return new QuadSceneNode;
	}
	//--------------------------------------------------------------------------------------------------------------
	//֪ͨ��Χ���Ѹ���
	void FKFastcall QuadSceneNode::_NotifyBoxUpdated()
	{
		//����ýڵ�û�йҽ��κ���Ⱦʵ����ֱ�ӷ���
		if( mRenderInstList.Size() == 0 )
			return;

		QuadSceneManager* pQuadSceneManager = (QuadSceneManager*)SceneManager::mpSingleton;

		//����Ѿ��ҽ���ĳ���Ĳ����ڵ���
		if( mpQuadNode != NULL )
		{
			//�жϸó����ڵ��Χ���Ƿ���ԭ�ȵ��Ĳ����ڵ�֮��
			if( mpQuadNode->_IsInside( mWorldBoundBox ) )
			{
				//�������ԭ�Ƚڵ���ֱ�ӷ���
				return;
			}
			//����ó����ڵ��Χ���Ѳ���ԭ�ȹҽӵ��Ĳ����ڵ��Χ�ռ���
			else
			{
				//�����ԭ���Ĳ����ڵ��϶Ͽ�
				mpQuadNode->_DetachQuadSceneNode( this );
			}
		}

		//�������Χ�н��ó����ڵ�ҽ����ʵ����Ĳ����ڵ���
		QuadNode* pQuadNode = pQuadSceneManager->GetQuadNodeFromBoundary( mWorldBoundBox );

		pQuadNode->_AttachQuadSceneNode( this );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
