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
	class FK_DLL Plane2
	{
	public:
		Vector2		mNormal;	//ƽ�淨��
		float		mDistance;	//ƽ����ԭ��ľ���

	public:
		Plane2();
		Plane2( const Plane2& refPlane2 );
		Plane2( const Vector2& vNormal, const float fDistance );
		Plane2( const Vector2& vNormal, const Vector2& vPoint );

		//���Ʋ�����
		Plane2& operator = ( const Plane2& refPlane2 );

		//��ȡƽ�����֮��ľ���
		float FKFastcall GetDistance( const Vector2& vPoint ) const;

		//�ж�ƽ�����Ŀռ佻���ϵ
		SpaceRelation FKFastcall GetSide( const Vector2& vPoint ) const;

		//���ݷ��ߺ�һ��������ƽ��
		void SetFromNormal( const Vector2& vNormal, const Vector2& vPoint );

		//��������������ƽ��
		void SetFromPoints( const Vector2& v1, const Vector2& v2 );
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Plane2 >		Plane2Stack;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
