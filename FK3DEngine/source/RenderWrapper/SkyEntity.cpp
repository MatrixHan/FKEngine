/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SkyEntity
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
	SkyEntity::SkyEntity()
		: mMatWorld		(Matrix4::Identity)
	{
		//��ʼ���������Ⱦ״̬
		mRenderOpacity.mbLighting				= false;
		mRenderOpacity.mbFogEnable				= false;
		mRenderOpacity.mbDepthTestEnable		= false;
		mRenderOpacity.mbDepthWriteEnable		= false;

		mRenderTransparent.mbLighting			= false;
		mRenderTransparent.mbFogEnable			= false;

		mRenderTransparent.SetTransparent();
	}
	//--------------------------------------------------------------------------------------------------------------
	SkyEntity::~SkyEntity()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������״̬
	void FKFastcall SkyEntity::_SetTextureState()
	{
		//ʹ�����Թ���
		RenderSystem::mpSingleton->_SetTextureFilter( ST_MAGFILTER, TFT_LINEAR, 0 );
		RenderSystem::mpSingleton->_SetTextureFilter( ST_MINFILTER, TFT_LINEAR, 0 );
		RenderSystem::mpSingleton->_SetTextureFilter( ST_MIPFILTER, TFT_LINEAR, 0 );

		//��������Ѱַ�Ա�����ֽӷ�
		RenderSystem::mpSingleton->_SetTextureAddress( ST_ADDRESSU, TAT_MIRROR, 0 );
		RenderSystem::mpSingleton->_SetTextureAddress( ST_ADDRESSV, TAT_MIRROR, 0 );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
