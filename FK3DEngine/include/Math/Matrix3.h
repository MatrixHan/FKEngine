/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Matrix3
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ѧ�� 3x3 ����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	// 3x3 ����
	class FK_DLL FKAlign16 Matrix3
	{
	public:
		union
		{
			struct
			{
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
			float m[3][3];
			float _m[9];
		};

	public:
		//����ֵ����
		static Matrix3 Identity;
		static Matrix3 Zero;

	public:
		//��ͬ�Ĺ��캯��
		Matrix3();
		Matrix3( const Matrix3& mat3ref );
		Matrix3( const Matrix4& mat4ref );
		Matrix3(	const float f11, const float f12, const float f13,
							const float f21, const float f22, const float f23,
							const float f31, const float f32, const float f33 );
		Matrix3( const float pVal[9] );

		//���������������
		Matrix3& operator = ( const Matrix3& mat3ref );
		bool operator == ( const Matrix3& mat3ref ) const;
		bool operator != ( const Matrix3& mat3ref ) const;
		Matrix3 operator * ( const Matrix3& mat3ref ) const;
		void operator *= ( const Matrix3& mat3ref );
		Vector3 operator * ( const Vector3& vec3ref ) const;

		//��ȡ������ֵ����
		String GetDescription();

		//���ɵ�λ����
		void SetIdentity();

		//���������
		void SetZero();

		//����ת�þ���
		void SetTranspose();

		//��ȡת�þ���
		Matrix3 GetTranspose() const;

		//���ɷ�����
		void SetInverse();

		//��ȡ������
		Matrix3 GetInverse() const;

		//�����Զ�����������ת����
		void SetRotationAxis( const float Degree, const Vector3& Axis );

		//������Ԫ��������ת����
		void SetRotationQuaternion( const Quaternion& Quat );

		//����ŷ����������ת����
		void SetRotationPitchYawRoll( const float Pitch, const float Yaw, const float Roll );

		//������ X ����ת����
		void SetRotationX( const float Degree );

		//������ Y ����ת����
		void SetRotationY( const float Degree );

		//������ Z ����ת����
		void SetRotationZ( const float Degree );

		//�������ž���
		void SetScaling( const float sx, const float sy, const float sz );

		//�������ž���
		void SetScaling( const Vector3& Scl );
	};
	//--------------------------------------------------------------------------------------------------------------
	//����Ż� 3x3 ������ѧ���㺯��ָ��
	extern void		( FKFastcall *Mat3TransMat3 )	( Matrix3* pOut, const Matrix3* pMat1, const Matrix3* pMat2 );
	extern void		( FKFastcall *Mat3TransVec3 )	( Vector3* pOutV3, const Matrix3* pMat3, const Vector3* pInV3 );
	extern void		( FKFastcall *Mat3Inverse )		( Matrix3* pOut, const Matrix3* pIn );
	extern void		( FKFastcall *Mat3Transpose )	( Matrix3* pOut, const Matrix3* pIn );
	//--------------------------------------------------------------------------------------------------------------
	//Ĭ��3x3 ������ѧ���㺯��
	extern void FKFastcall _Def_Mat3TransMat3( Matrix3* pOut, const Matrix3* pMat1, const Matrix3* pMat2 );
	extern void FKFastcall _Def_Mat3TransVec3( Vector3* pOutV3, const Matrix3* pMat3, const Vector3* pInV3 );
	extern void FKFastcall _Def_Mat3Inverse( Matrix3* pOut, const Matrix3* pIn );
	extern void	FKFastcall _Def_Mat3Transpose( Matrix3* pOut, const Matrix3* pIn );
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Matrix3 >		Matrix3Stack;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
