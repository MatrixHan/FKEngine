/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Light
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
	Light::Light()
		: mLightType		(LT_DIRECTIONAL)
		, mRange			(1000.0f)
		, mAttenConst		(1.0f)
		, mAttenLinear		(0.0f)
		, mAttenQuad		(0.0f)
		, mFallOff			(1.0f)
		, mTheta			( FK_DegreeToRadian( 20.0f ) )
		, mPhi				( FK_DegreeToRadian( 45.0f ) )
		, mIndex			( 0.0f )
		, mbActived			(false)
		, mbEnable			(false)
		, mpAttachedNode	(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	Light::~Light()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//���õƹ���������ӵĽڵ��϶Ͽ�
	void Light::DetachFromNode()
	{
		mpAttachedNode->DetachLight( this );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƹ�
	void Light::ActiveLight( const bool bActive )
	{
		if( bActive == mbActived )
			Except( Exception::ERR_INVALIDPARAMS, "�޷��ظ�����򷴼���ƹ⡣" );

		if( !RenderSystem::mpSingleton->_ActiveLight( this, bActive ) )
			Except( Exception::ERR_INVALIDPARAMS, "�Ѿ��ﵽӲ��֧�ֵ����ƹ�����������ʧ�ܡ�" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����/�رյƹ�
	void Light::EnableLight( const bool bEnable )
	{
		if( !mbActived )
			Except( Exception::ERR_INVALIDPARAMS, "�޷�����δ���õĵƹ⡣" );

		mbEnable = bEnable;

		RenderSystem::mpSingleton->_SetLightState( this );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
