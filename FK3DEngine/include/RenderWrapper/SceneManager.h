/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SceneManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	����������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "RenderQueue.h"
#include "RenderInstance.h"
#include "Camera.h"
#include "Light.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class SceneNode;
	class SkyEntity;
	class SkyPlane;
	class SkyBox;
	class SkySphere;
	//--------------------------------------------------------------------------------------------------------------
	//��������������
	enum SceneManagerType
	{
		SMT_Basic,		//��������������
		SMT_BSP,		//����������������
		SMT_Quadtree,	//�Ĳ�������������
		SMT_Octree,		//�˲�������������
	};
	//--------------------------------------------------------------------------------------------------------------
	//����������
	class FK_DLL SceneManager : public Singleton< SceneManager >
	{
	public:
		friend class SceneNode;

	protected:
		RenderQueue				mRenderQueue;			//��Ⱦ����

		RenderInstList			mNoCullRenderInsts;		//�Ǽ�ѡ��Ⱦʵ������

		CameraList				mCameraList;			//������б�
		LightList				mLightList;				//�ƹ��б�

	public:
		SceneNode*				mpRootNode;				//�������ڵ�

		SkyEntity*				mpSkyEntity;			//�����

	public:
		SceneManager();
		virtual ~SceneManager();

		//���볡���ļ�
		virtual void LoadFromFile( FileObject* pFile );

		//���³����ڵ���
		void UpdateSceneNodeTree();

		//��Ⱦ����
		void RenderScene( float fTimeSinceLastFrame );

		//�����������ڵ�
		virtual SceneNode* CreateSceneRootNode();

		//��ȡ�������ڵ�
		SceneNode* GetSceneRootNode();

		//���������
		Camera* CreateCamera();

		//�����ƹ�
		Light* CreateLight();

		//ɾ�������
		void DeleteCamera( Camera* pCamera );

		//ɾ���ƹ�
		void DeleteLight( Light* pLight );

		//ɾ�����������
		void DeleteAllCamera();

		//ɾ�����еƹ�
		void DeleteAllLight();

		//���������
		SkyPlane* CreateSkyPlane();

		//������պ�
		SkyBox* CreateSkyBox();

		//���������
		SkySphere* CreateSkySphere( UINT nNumRing = 20, UINT nNumSegment = 20 );

		//�ݻ������
		void DestroySky();

	protected:
		//��ȡ�ɼ���Ⱦʵ��
		virtual void _GetVisableInstance( Camera* pActiveCam );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
