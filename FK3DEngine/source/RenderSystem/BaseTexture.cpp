/********************************************************************
*
*	本文件是FKMMORPG的一部分。本文件版权归属FreeKnightDuzhi(王宏张)所有。
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	文件名：	BaseTexture
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*
*	修改人:		
*	修改内容:
*********************************************************************/

#include "../../include/RenderSystem/RenderSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	BaseTexture::BaseTexture()
		: mPixelFormat		(PF_UNKNOWN)
		, mNumLevel			(0)
		, mPoolMode			(MPM_UNKNOWN)
		, mType				(TU_UNKNOWN)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	BaseTexture::BaseTexture( PixelFormat ePixelFormat, UINT nNumLevel, TextureUsage Type )
		: mPixelFormat		(ePixelFormat)
		, mNumLevel			(nNumLevel)
		, mPoolMode			(MPM_UNKNOWN)
		, mType				(Type)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	BaseTexture::~BaseTexture()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
