/********************************************************************
*
*	本文件是FKMMORPG的一部分。本文件版权归属FreeKnightDuzhi(王宏张)所有。
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	文件名：	CollisionRecord
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*
*	修改人:		
*	修改内容:
*********************************************************************/

#include "../../include/PhysiceSystem/PhysicsSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	CollisionRecord::CollisionRecord()
	{
		mContactStack.Initialize( 10, 20 );
	}
	//--------------------------------------------------------------------------------------------------------------
	//增加碰撞接触
	FKInline Contact* CollisionRecord::AddContact()
	{
		return mContactStack.Push();
	}
	//--------------------------------------------------------------------------------------------------------------
	//删除碰撞接触
	FKInline void CollisionRecord::DelContact( Contact* pContact )
	{
		mContactStack.Erase( pContact );
	}
	//--------------------------------------------------------------------------------------------------------------
	//删除所有碰撞接触
	FKInline void CollisionRecord::DelAllContact()
	{
		mContactStack.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
