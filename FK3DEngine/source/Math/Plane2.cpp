/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Plane2
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
	Plane2::Plane2()
		: mNormal	( Vector2( 0.0f, 0.0f ) )
		, mDistance	(0.0f)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	Plane2::Plane2( const Plane2& refPlane2 )
		: mNormal	(refPlane2.mNormal)
		, mDistance	(refPlane2.mDistance)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	Plane2::Plane2( const Vector2& vNormal, const float fDistance )
		: mNormal	(vNormal)
		, mDistance	(fDistance)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	Plane2::Plane2( const Vector2& vNormal, const Vector2& vPoint )
		: mNormal	(vNormal)
	{
		mDistance = -vNormal.GetDot( vPoint );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���Ʋ�����
	Plane2& Plane2::operator = ( const Plane2& refPlane2 )
	{
		mNormal = refPlane2.mNormal;
		mDistance = refPlane2.mDistance;

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡƽ�����֮��ľ���
	float FKFastcall Plane2::GetDistance( const Vector2& vPoint ) const
	{
		return mDistance + mNormal.GetDot( vPoint );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ж�ƽ�����Ŀռ佻���ϵ
	SpaceRelation FKFastcall Plane2::GetSide( const Vector2& vPoint ) const
	{
		float Distance = mDistance + mNormal.GetDot( vPoint );

		if( Distance > 0.001f )
			return SR_POSITIVE;
		else if( Distance < -0.001f )
			return SR_NEGATIVE;
		else
			return SR_COINCIDING;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ݷ��ߺ�һ��������ƽ��
	void Plane2::SetFromNormal( const Vector2& vNormal, const Vector2& vPoint )
	{
		mNormal = vNormal;
		mDistance = -vNormal.GetDot( vPoint );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������������ƽ��
	void Plane2::SetFromPoints( const Vector2& v1, const Vector2& v2 )
	{
		mNormal.x = v2.y - v1.y;
		mNormal.y = v2.x - v1.x;

		mNormal.Normalize();

		mDistance = -mNormal.GetDot( v1 );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
