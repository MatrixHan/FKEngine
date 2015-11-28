/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Quaternion
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ѧ�� ��Ԫ��
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��Ԫ��
	class FK_DLL FKAlign16 Quaternion
	{
	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
			float v[4];
		};

	public:
		//����ֵ����
		static Quaternion Identity;
		static Quaternion Zero;

	public:
		//��ͬ�Ĺ��캯��
		Quaternion();
		Quaternion( const Quaternion& quat );
		Quaternion( const float fx, const float fy, const float fz, const float fw );
		Quaternion( const float* pVal );
		Quaternion( const float Pitch, const float Yaw, const float Roll );
		Quaternion( const float Degree, const Vector3& Axis );
		Quaternion( const Matrix3& mat3 );
		Quaternion( const Matrix4& mat4 );

		//���������������
		Quaternion& operator = ( const Quaternion& quat );
		bool operator == ( const Quaternion& quat ) const;
		bool operator != ( const Quaternion& quat ) const;
		Quaternion operator + ( const Quaternion& quat ) const;
		Quaternion operator - ( const Quaternion& quat ) const;
		Quaternion operator * ( const Quaternion& quat ) const;
		Quaternion operator * ( const float fScalar ) const;
		Vector3 operator * ( const Vector3 v3 ) const;
		void operator += ( const Quaternion& quat );
		void operator -= ( const Quaternion& quat );
		void operator *= ( const Quaternion& quat );
		void operator *= ( const float fScalar );

		//����ŷ����������Ԫ��
		void SetRotationPitchYawRoll( const float Pitch, const float Yaw, const float Roll );

		//�����Զ�����������Ԫ��
		void SetRotationAxis( const float Degree, const Vector3& Axis );

		//������ת����������Ԫ��
		void SetRotationMatrix3( const Matrix3& mat3 );

		//������ת����������Ԫ��
		void SetRotationMatrix4( const Matrix4& mat4 );

		//��ȡ��Ԫ�����Զ�������ת����
		void GetRotationAxis( float* pDegree, Vector3* pAxis );

		//��ȡ��Ԫ����ת��������
		void GetRotationMatrix3( Matrix3* pMat3 );

		//��ȡ��Ԫ����ת��������
		void GetRotationMatrix4( Matrix4* pMat4 );

		//��ȡ��Ԫ����˻�
		float GetDot( const Quaternion& quat );

		//��ȡ��Ԫ������
		float GetLength();

		//��Ԫ����λ��
		void Normalize();

		//��ȡ��Ԫ������
		Quaternion GetInverse();

		//��Ԫ������
		void SetInverse();
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Quaternion >		QuaternionStack;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
