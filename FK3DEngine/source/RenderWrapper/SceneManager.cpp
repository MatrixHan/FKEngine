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
	SceneManager::SceneManager()
		: mpRootNode	(NULL)
		, mpSkyEntity	(NULL)
	{
		mCameraList.Initialize( 10, 10 );
		mLightList.Initialize( 50, 50 );

		mNoCullRenderInsts.Initialize( 50, 50 );
	}
	//--------------------------------------------------------------------------------------------------------------
	SceneManager::~SceneManager()
	{
		DeleteAllCamera();
		DeleteAllLight();

		SafeDelete( mpRootNode );

		SafeDelete( mpSkyEntity );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���볡���ļ�
	void SceneManager::LoadFromFile( FileObject* pFile )
	{

	}
	//--------------------------------------------------------------------------------------------------------------
	//���³����ڵ���
	void SceneManager::UpdateSceneNodeTree()
	{
		//���½ڵ����
		mpRootNode->_UpdateMatrix();

		//���½ڵ��Χ��
		mpRootNode->_UpdateBox();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ����
	void SceneManager::RenderScene( float fTimeSinceLastFrame )
	{
		//���³����ڵ���
		UpdateSceneNodeTree();

		//���������
		if( mpSkyEntity != NULL )
			mpSkyEntity->_UpdateSky( fTimeSinceLastFrame );

		//����ƽ��ͼ����Ⱦ����
		OverlayManager* pOverlayManager = OverlayManager::GetSingletonPtr();
		pOverlayManager->_UpdateVertexData();

		//�������ӷ�����
		ParticleSystem::mpSingleton->_UpdateEmitter( fTimeSinceLastFrame );


		//׼���豸
		RenderSystem::mpSingleton->_PrepareDevice();

		//ѭ����Ⱦ�����ӿ�
		ViewportList::Iterator it = RenderSystem::mpSingleton->mViewportList.Begin();
		ViewportList::Iterator end = RenderSystem::mpSingleton->mViewportList.End();
		for(; it!=end; ++it )
		{
			Viewport* pViewport = *it;

			//���û�м���������������
			Camera* pCamera = pViewport->mpCamera;
			if( pCamera == NULL )
				continue;

			//�����ӿ�
			RenderSystem::mpSingleton->_SetViewport( pViewport );

			//���������
			pCamera->_UpdateCamera();

			//���¹�������ӷ���
			ParticleSystem::mpSingleton->_UpdateSprite( pCamera );

			//���ù۲�����ͶӰ����
			RenderSystem::mpSingleton->_SetViewMatrix( &pCamera->GetViewMatrix() );
			RenderSystem::mpSingleton->_SetProjMatrix( &pCamera->GetProjMatrix() );

			//���ԭ����Ⱦ����
			mRenderQueue.ClearRenderQueue();

			//�������еĿɼ���Ⱦʵ����ӵ���Ⱦ������
			_GetVisableInstance( pCamera );

			//��ӷǼ�ѡ��Ⱦ���嵽��Ⱦ������
			mRenderQueue.AddRenderInstList( &mNoCullRenderInsts );

			//������Ⱦ����
			mRenderQueue.SortRenderQueue( pCamera );


			//֪ͨ�豸��ʼ��Ⱦ
			RenderSystem::mpSingleton->_BeginRender();

			//��Ⱦ�����
			if( mpSkyEntity != NULL )
				mpSkyEntity->_RenderSky();

			//��Ⱦ
			mRenderQueue.Render( pCamera );

			//��Ⱦƽ��ͼ��GUI��
			pOverlayManager->_RenderAllOverlays();

			//֪ͨ�豸������Ⱦ
			RenderSystem::mpSingleton->_EndRender();
		}

		//������Ⱦҳ��
		RenderSystem::mpSingleton->_SwapRenderBuffer();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����������ڵ�
	SceneNode* SceneManager::CreateSceneRootNode()
	{
		mpRootNode = new SceneNode;
		return mpRootNode;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�������ڵ�
	SceneNode* SceneManager::GetSceneRootNode()
	{
		return mpRootNode;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������
	Camera* SceneManager::CreateCamera()
	{
		Camera* pCamera = new Camera;
		*mCameraList.Push() = pCamera;
		return pCamera;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ƹ�
	Light* SceneManager::CreateLight()
	{
		Light* pLight = new Light;
		*mLightList.Push() = pLight;
		return pLight;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�������
	void SceneManager::DeleteCamera( Camera* pCamera )
	{
		CameraList::Iterator it = mCameraList.Begin();
		CameraList::Iterator end = mCameraList.End();
		for(; it!=end; ++it )
		{
			if( *it == pCamera )
			{
				mCameraList.Erase( it );
				delete pCamera;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ���ƹ�
	void SceneManager::DeleteLight( Light* pLight )
	{
		LightList::Iterator it = mLightList.Begin();
		LightList::Iterator end = mLightList.End();
		for(; it!=end; ++it )
		{
			if( *it == pLight )
			{
				mLightList.Erase( it );
				delete pLight;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����������
	void SceneManager::DeleteAllCamera()
	{
		CameraList::Iterator it = mCameraList.Begin();
		CameraList::Iterator end = mCameraList.End();
		for(; it!=end; ++it )
			SafeDelete( *it );

		mCameraList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����еƹ�
	void SceneManager::DeleteAllLight()
	{
		LightList::Iterator it = mLightList.Begin();
		LightList::Iterator end = mLightList.End();
		for(; it!=end; ++it )
			SafeDelete( *it );

		mLightList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������
	SkyPlane* SceneManager::CreateSkyPlane()
	{
		mpSkyEntity = new SkyPlane;
		return (SkyPlane*)mpSkyEntity;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������պ�
	SkyBox* SceneManager::CreateSkyBox()
	{
		mpSkyEntity = new SkyBox;
		return (SkyBox*)mpSkyEntity;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������
	SkySphere* SceneManager::CreateSkySphere( UINT nNumRing, UINT nNumSegment )
	{
		mpSkyEntity = new SkySphere( nNumRing, nNumSegment );
		return (SkySphere*)mpSkyEntity;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ݻ������
	void SceneManager::DestroySky()
	{
		SafeDelete( mpSkyEntity );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ɼ���Ⱦʵ��
	void SceneManager::_GetVisableInstance( Camera* pActiveCam )
	{
		mpRootNode->_GetVisibleInstance( pActiveCam, &mRenderQueue );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
