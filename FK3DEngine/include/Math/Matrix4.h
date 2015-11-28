/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Matrix4
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ѧ�� 4x4 ����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	// 4x4 ����
	class FK_DLL FKAlign16 Matrix4
	{
	public:
		union
		{
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[4][4];
			float _m[16];
		};

	public:
		//����ֵ����
		static Matrix4 Identity;
		static Matrix4 Zero;

	public:
		//��ͬ�Ĺ��캯��
		Matrix4();
		Matrix4( const Matrix4& mat4ref );
		Matrix4( const Matrix3& mat3ref );
		Matrix4(	const float f11, const float f12, const float f13, const float f14,
							const float f21, const float f22, const float f23, const float f24,
							const float f31, const float f32, const float f33, const float f34,
							const float f41, const float f42, const float f43, const float f44 );
		Matrix4( const float pVal[16] );

		//���������������
		Matrix4& operator = ( const Matrix4& mat4ref );
		bool operator == ( const Matrix4& mat4ref ) const;
		bool operator != ( const Matrix4& mat4ref ) const;
		Matrix4 operator * ( const Matrix4& mat4ref ) const;
		void operator *= ( const Matrix4& mat4ref );
		Vector3 operator * ( const Vector3& vec3ref ) const;
		Vector4 operator * ( const Vector4& vec4ref ) const;

		//��ȡ������ֵ����
		String GetDescription();

		//���ɵ�λ����
		void SetIdentity();

		//���������
		void SetZero();

		//����ת�þ���
		void SetTranspose();

		//��ȡת�þ���
		Matrix4 GetTranspose() const;

		//���ɷ�����
		void SetInverse();

		//��ȡ������
		Matrix4 GetInverse() const;

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

		//����ƽ�ƾ���
		void SetTranslation( const float x, const float y, const float z );

		//����ƽ�ƾ���
		void SetTranslation( const Vector3& Pos );

		//�������ž���
		void SetScaling( const float sx, const float sy, const float sz );

		//�������ž���
		void SetScaling( const Vector3& Scl );

		//�������ֹ۲����
		void SetLookAtLH( const Vector3& Eye, const Vector3& At, const Vector3& Up );

		//�������ֹ۲����
		void SetLookAtRH( const Vector3& Eye, const Vector3& At, const Vector3& Up );

		//������������ͶӰ����
		void SetOrthoLH( float Width, float Height, float Near, float Far );

		//������������ͶӰ����
		void SetOrthoRH( float Width, float Height, float Near, float Far );

		//������������ͶӰ����
		void SetOrthoOffCenterLH( float Left, float Right, float Top, float Bottom, float Near, float Far );

		//������������ͶӰ����
		void SetOrthoOffCenterRH( float Left, float Right, float Top, float Bottom, float Near, float Far );

		//��������͸��ͶӰ����
		void SetPerspectiveLH( float Width, float Height, float Near, float Far );

		//��������͸��ͶӰ����
		void SetPerspectiveRH( float Width, float Height, float Near, float Far );

		//��������͸��ͶӰ����
		void SetPerspectiveFovLH( float FOV, float Aspect, float Near, float Far );

		//��������͸��ͶӰ����
		void SetPerspectiveFovRH( float FOV, float Aspect, float Near, float Far );

		//��������͸��ͶӰ����
		void SetPerspectiveOffCenterLH( float Left, float Right, float Top, float Bottom, float Near, float Far );

		//��������͸��ͶӰ����
		void SetPerspectiveOffCenterRH( float Left, float Right, float Top, float Bottom, float Near, float Far );
	};
	//--------------------------------------------------------------------------------------------------------------
	//����Ż� 4x4 ������ѧ���㺯��ָ��
	extern void		( FKFastcall *Mat4TransMat4 )	( Matrix4* pOut, const Matrix4* pMat1, const Matrix4* pMat2 );
	extern void		( FKFastcall *Mat4TransVec3 )	( Vector3* pOutV3, const Matrix4* pMat4, const Vector3* pInV3 );
	extern void		( FKFastcall *Mat4TransVec4 )	( Vector4* pOutV4, const Matrix4* pMat4, const Vector4* pInV4 );
	extern void		( FKFastcall *Mat4Inverse )		( Matrix4* pOut, const Matrix4* pIn );
	extern void		( FKFastcall *Mat4Transpose )	( Matrix4* pOut, const Matrix4* pIn );
	//--------------------------------------------------------------------------------------------------------------
	//Ĭ��4x4 ������ѧ���㺯��
	extern void FKFastcall _Def_Mat4TransMat4( Matrix4* pOut, const Matrix4* pMat1, const Matrix4* pMat2 );
	extern void FKFastcall _Def_Mat4TransVec3( Vector3* pOutV3, const Matrix4* pMat4, const Vector3* pInV3 );
	extern void FKFastcall _Def_Mat4TransVec4( Vector4* pOutV4, const Matrix4* pMat4, const Vector4* pInV4 );
	extern float _Def_Mat4Inv3x3( float a1, float a2, float a3, float b1, float b2, float b3,
		float c1, float c2, float c3 );
	extern void FKFastcall _Def_Mat4Inverse( Matrix4* pOut, const Matrix4* pIn );
	extern void FKFastcall _Def_Mat4Transpose( Matrix4* pOut, const Matrix4* pIn );
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Matrix4 >		Matrix4Stack;
	typedef Stack< Matrix4* >		Matrix4List;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
