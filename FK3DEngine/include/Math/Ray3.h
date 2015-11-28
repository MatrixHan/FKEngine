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
*	�ļ�˵����	��ѧ�� ��ά������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��ά������
	class FK_DLL Ray3
	{
	public:
		Vector3		mOrigin;	//����ԭ��
		Vector3		mDirection;	//���߷���

	public:
		//��ͬ�Ĺ��캯��
		Ray3();
		Ray3( const Vector3& vOrigin, const Vector3& vDirection );

		//���������������
		Ray3& operator = ( const Ray3& ray3ref );
		Ray3 operator * ( const Matrix4& mat4ref ) const;
		void operator *= ( const Matrix4& mat4ref );

		//��ȡ��ָ������ཻ������
		float FKFastcall GetIntersectPos( const Vector3& vNormal, const Vector3& vVerOnPlane3, Vector3* pIntersectPos ) const;
		float FKFastcall GetIntersectPos( const Plane3& sPlane3, Vector3* pIntersectPos ) const;
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
