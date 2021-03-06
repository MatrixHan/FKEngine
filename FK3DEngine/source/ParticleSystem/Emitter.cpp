/********************************************************************
*
*	本文件是FKMMORPG的一部分。本文件版权归属FreeKnightDuzhi(王宏张)所有。
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	文件名：	Emitter
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*
*	修改人:		
*	修改内容:
*********************************************************************/

#include "../../include/ParticleSystem/ParticleSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	Emitter::Emitter( Type eType, Particle* pParticle )
		: RenderObject		()
		, RenderInstance	()
		, mType				(eType)
		, mpParticle		(pParticle)
		, mNumParticle		(0)
	{
		mpRenderObject = this;
		mbCullable = false;
	}
	//--------------------------------------------------------------------------------------------------------------
	Emitter::~Emitter()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//渲染物体
	void Emitter::_RenderObj( const RenderParam* pParam, const Matrix4* pNodeMatrix )
	{
		//设置世界矩阵
		RenderSystem::mpSingleton->_SetWorldMatrix( pNodeMatrix );

		//根据渲染参数渲染
		pParam->RenderByParam();
	}
	//--------------------------------------------------------------------------------------------------------------
	//渲染动画物体
	void Emitter::_RenderAnimObj( const RenderParam* pParam, const AnimControl* pAnimControl, const Matrix4* pNodeMatrix )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
