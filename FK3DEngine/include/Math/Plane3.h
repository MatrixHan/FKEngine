/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Plane3
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ѧ�� ��άƽ��
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��άƽ��
	class FK_DLL Plane3
	{
	public:
		Vector3		mNormal;	//ƽ�淨��
		float		mDistance;	//ƽ����ԭ��ľ���

	public:
		Plane3();
		Plane3( const Plane3& refPlane3 );
		Plane3( const Vector3& vNormal, const float fDistance );
		Plane3( const Vector3& vNormal, const Vector3& vPoint );

		//���Ʋ�����
		Plane3& operator = ( const Plane3& refPlane3 );

		//��ȡƽ�����֮��ľ���
		float FKFastcall GetDistance( const Vector3& vPoint ) const;

		//�ж�ƽ�����Ŀռ佻���ϵ
		SpaceRelation FKFastcall GetSide( const Vector3& vPoint ) const;

		//���ݷ��ߺ�һ��������ƽ��
		void SetFromNormal( const Vector3& vNormal, const Vector3& vPoint );

		//��������������ƽ��
		void SetFromPoints( const Vector3& v1, const Vector3& v2, const Vector3& v3 );

		//��ȡ������ X ��ͶӰ��Ӧ�Ķ�άƽ��
		bool GetOrthoPlaneAloneX( Plane2* pOutPlane2, const Vector3& vPointOnPlane, const float fX );

		//��ȡ������ Y ��ͶӰ��Ӧ�Ķ�άƽ��
		bool GetOrthoPlaneAloneY( Plane2* pOutPlane2, const Vector3& vPointOnPlane, const float fY );

		//��ȡ������ Z ��ͶӰ��Ӧ�Ķ�άƽ��
		bool GetOrthoPlaneAloneZ( Plane2* pOutPlane2, const Vector3& vPointOnPlane, const float fZ );
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Plane3 >		Plane3Stack;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
