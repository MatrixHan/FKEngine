/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RenderInstance
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
	RenderInstance::RenderInstance( UINT nGroupPriority )
		: mpRenderObject	(NULL)
		, mpSceneNode		(NULL)
		, mpAnimControl		(NULL)
		, mnGroupPriority	(nGroupPriority)
		, mbVisable			(true)
		, mbCullable		(true)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	RenderInstance::RenderInstance( RenderObject* pRenderObj, UINT nGroupPriority )
		: mpRenderObject	(pRenderObj)
		, mpSceneNode		(NULL)
		, mpAnimControl		(NULL)
		, mnGroupPriority	(nGroupPriority)
		, mbVisable			(true)
		, mbCullable		(true)
		, mfViewDepth		(0.0f)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	RenderInstance::~RenderInstance()
	{
		//�Զ�����Ⱦʵ���ӹҽӵĳ����ڵ��϶Ͽ�
		if( mpSceneNode != NULL )
			mpSceneNode->DetachRenderInstance( this );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ��ʵ��
	void FKFastcall RenderInstance::Render( RenderParam* pParam )
	{
		//������ڶ���������
		if( mpAnimControl != NULL )
		{
			mpRenderObject->_RenderAnimObj( pParam, mpAnimControl, &mpSceneNode->mWorldMatrix );
		}
		//��������ڶ���������
		else
		{
			mpRenderObject->_RenderObj( pParam, &mpSceneNode->mWorldMatrix );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¹۲����
	void FKFastcall RenderInstance::UpdateViewDepth( const Camera* pCamera )
	{
		if( mpSceneNode == NULL )
			return;

		mfViewDepth = ( pCamera->mViewPos - mpSceneNode->mDerivedPosition ).GetLength();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
