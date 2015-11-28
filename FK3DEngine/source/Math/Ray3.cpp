/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Ray3
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/Math/MathInsideHead.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	Ray3::Ray3()
		: mOrigin		(Vector3::Zero)
		, mDirection	(Vector3::Zero)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	Ray3::Ray3( const Vector3& vOrigin, const Vector3& vDirection )
		: mOrigin		(vOrigin)
		, mDirection	(vDirection)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	Ray3& Ray3::operator = ( const Ray3& ray3ref )
	{
		memcpy( this, &ray3ref, sizeof(Ray3) );
		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	Ray3 Ray3::operator * ( const Matrix4& mat4ref ) const
	{
		static Ray3 tmp;
		tmp.mOrigin = mOrigin * mat4ref;
		tmp.mDirection = mDirection * mat4ref;
		tmp.mDirection.Normalize();
		return tmp;
	}
	//--------------------------------------------------------------------------------------------------------------
	void Ray3::operator *= ( const Matrix4& mat4ref )
	{
		mOrigin *= mat4ref;
		mDirection *= mat4ref;
		mDirection.Normalize();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ָ������ཻ������
	float FKFastcall Ray3::GetIntersectPos( const Vector3& vNormal, const Vector3& vVerOnPlane3, Vector3* pIntersectPos ) const
	{
		//�����ཻ������
		//
		//ԭ��Ϊ��	ײ������ = ( RayOnPlane3 ��� Plane3Normal - RayStart ��� Plane3Normal ) / ( MoveDir ��� Plane3Normal )
		//			RayOnPlane3 = RayStart + MoveDir * ײ������
		float fDot = mDirection.GetDot( vNormal );

		//�����˻����ڵ�������֤�����ཻ
		if( fDot >= 0.0f )
			return -1.0f;

		float fDist = ( vVerOnPlane3 - mOrigin ).GetDot( vNormal ) / fDot;
		*pIntersectPos = mOrigin + mDirection * fDist;

		return fDist;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ָ������ཻ������
	float FKFastcall Ray3::GetIntersectPos( const Plane3& sPlane3, Vector3* pIntersectPos ) const
	{
		float fDot = mDirection.GetDot( sPlane3.mNormal );

		if( fDot >= 0.0f )
			return -1.0f;

		float fDist = ( -sPlane3.mDistance - mOrigin.GetDot( sPlane3.mNormal ) ) / fDot;
		*pIntersectPos = mOrigin + mDirection * fDist;

		return fDist;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
