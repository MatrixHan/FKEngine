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
*	�ļ�˵����	�����ڵ���
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "TransformNode.h"
#include "Light.h"
#include "RenderInstance.h"
#include "Camera.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class SceneNode;
	class RenderQueue;
	typedef Stack< SceneNode* >		SceneNodeList;
	//--------------------------------------------------------------------------------------------------------------
	//�����ڵ���
	class FK_DLL SceneNode : public TransformNode
	{
	protected:
		LightList			mLightList;			//�ýڵ��¹ҽӵĵƹ�
		CameraList			mCameraList;		//�ýڵ��¹ҽӵ������
		RenderInstList		mRenderInstList;	//�ýڵ��¹ҽӵ���Ⱦʵ��

		bool				mbUpdateObjBox;		//�Ƿ���Ҫ���¹ҽ������Χ��
		AxisBox3			mObjBoundBox;		//�ҽ������Χ��

	public:
		SceneNode();
		virtual ~SceneNode();

		//�ҽӵƹ�
		void AttachLight( Light* pLight );

		//�Ͽ��ƹ�
		void DetachLight( Light* pLight );

		//�ҽ������
		void AttachCamera( Camera* pCamera );

		//�Ͽ������
		void DetachCamera( Camera* pCamera );

		//�ҽ���Ⱦʵ��
		void AttachRenderInstance( RenderInstance* pInstance );

		//�Ͽ���Ⱦʵ��
		void DetachRenderInstance( RenderInstance* pInstance );

		//�Ͽ�������Ⱦʵ��
		void DetachAllRenderInstance();

	protected:
		//�ڵ㴴������
		virtual TransformNode* FKFastcall _NodeCreator();

		//��ȡ�ڵ�ҽ������Χ��
		const AxisBox3& FKFastcall _GetLocalObjectBox();

		//���ýڵ��µ�������Ⱦʵ��������Ⱦ����
		void FKFastcall _AddInstanceToQueue( RenderQueue* pRenderQueue );

	public:
		//��ȡ�ýڵ㼰���ӽڵ��µĿɼ���Ⱦʵ��
		void FKFastcall _GetVisibleInstance( Camera* pActiveCam, RenderQueue* pRenderQueue );

		//֪ͨ��Χ���Ѹ���
		virtual void FKFastcall _NotifyBoxUpdated();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
