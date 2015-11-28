/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Vector3
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ѧ�� ��άʸ��
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��άʸ��
	class FK_DLL Vector3
	{
	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};
			float v[3];
		};

	public:
		//����ֵ����
		static Vector3 Identity;
		static Vector3 Zero;
		static Vector3 UnitX;
		static Vector3 UnitY;
		static Vector3 UnitZ;

	public:
		//��ͬ�Ĺ��캯��
		Vector3();
		Vector3( const Vector3& v3 );
		Vector3( const float fx, const float fy, const float fz );
		Vector3( const float pVal[3] );

		//���������������
		Vector3& operator = ( const Vector3& v3 );
		bool operator == ( const Vector3& v3 ) const;
		bool operator != ( const Vector3& v3 ) const;
		bool operator > ( const Vector3& v3 ) const;
		bool operator < ( const Vector3& v3 ) const;
		bool operator >= ( const Vector3& v3 ) const;
		bool operator <= ( const Vector3& v3 ) const;
		Vector3 operator + () const;
		Vector3 operator - () const;
		Vector3 operator + ( const Vector3& v3 ) const;
		Vector3 operator - ( const Vector3& v3 ) const;
		Vector3 operator * ( const Vector3& v3 ) const;
		Vector3 operator / ( const Vector3& v3 ) const;
		Vector3 operator * ( const float fScalar ) const;
		Vector3 operator / ( const float fScalar ) const;
		Vector3 operator * ( const Matrix4& mat4ref ) const;
		void operator += ( const Vector3& v3 );
		void operator -= ( const Vector3& v3 );
		void operator *= ( const Vector3& v3 );
		void operator /= ( const Vector3& v3 );
		void operator *= ( const float fScalar );
		void operator /= ( const float fScalar );
		void operator *= ( const Matrix4& mat4ref );

		//��ʸ������һʸ�����
		void Cross( const Vector3& v3 );

		//��ȡ��ʸ������һʸ���ĵ�˻�
		float GetDot( const Vector3& v3 ) const;

		//��ȡ��ʸ������һʸ���Ĳ�˻�
		Vector3 GetCross( const Vector3& v3 ) const;

		//��ȡ��ʸ���ĳ���
		float GetLength() const;

		//��λ����ʸ��
		void Normalize();

		//��ȡ��ʸ���ĵ�λ��ʸ��
		Vector3 GetNormalizedVec() const;

		//���ٵ�λ����ʸ������Ҫ�����ʸ���ĵ�λ���ȣ�
		void NormalizeFast( const float fLenth );

		//���ٻ�ȡ��ʸ���ĵ�λ��ʸ������Ҫ�����ʸ���ĵ�λ���ȣ�
		Vector3 GetNormalizedVecFast( const float fLength ) const;
	};
	//--------------------------------------------------------------------------------------------------------------
	//����Ż���άʸ����ѧ���㺯��ָ��
	extern void		( FKFastcall *Vec3Add )				( Vector3* pOut, const Vector3* pArg1, const Vector3* pArg2 );
	extern void		( FKFastcall *Vec3Sub )				( Vector3* pOut, const Vector3* pOrg, const Vector3* pSub );
	extern void		( FKFastcall *Vec3Mul )				( Vector3* pOut, const Vector3* pArg1, const Vector3* pArg2 );
	extern void		( FKFastcall *Vec3Div )				( Vector3* pOut, const Vector3* pOrg, const Vector3* pDiv );
	extern void		( FKFastcall *Vec3MulScalar )		( Vector3* pOut, const Vector3* pOrg, const float fScalar );
	extern void		( FKFastcall *Vec3DivScalar )		( Vector3* pOut, const Vector3* pOrg, const float fScalar );

	extern float	( FKFastcall *Vec3Dot )				( const Vector3* pArg1, const Vector3* pArg2 );
	extern void		( FKFastcall *Vec3Cross )			( Vector3* pOut, const Vector3* pArg1, const Vector3* pArg2 );
	extern float	( FKFastcall *Vec3Length )			( const Vector3* pIn );
	extern void		( FKFastcall *Vec3Normalize )		( Vector3* pOut, const Vector3* pIn );
	extern void		( FKFastcall *Vec3NormalizeFast )	( Vector3* pOut, const Vector3* pIn, float fLenth );
	//--------------------------------------------------------------------------------------------------------------
	//Ĭ����άʸ����ѧ���㺯��
	extern void FKFastcall _Def_Vec3Add( Vector3* pOut, const Vector3* pArg1, const Vector3* pArg2 );
	extern void FKFastcall _Def_Vec3Sub( Vector3* pOut, const Vector3* pOrg, const Vector3* pSub );
	extern void FKFastcall _Def_Vec3Mul( Vector3* pOut, const Vector3* pArg1, const Vector3* pArg2 );
	extern void FKFastcall _Def_Vec3Div( Vector3* pOut, const Vector3* pOrg, const Vector3* pDiv );
	extern void FKFastcall _Def_Vec3MulScalar( Vector3* pOut, const Vector3* pOrg, const float fScalar );
	extern void FKFastcall _Def_Vec3DivScalar( Vector3* pOut, const Vector3* pOrg, const float fScalar );

	extern float FKFastcall _Def_Vec3Dot( const Vector3* pArg1, const Vector3* pArg2 );
	extern void FKFastcall _Def_Vec3Cross( Vector3* pOut, const Vector3* pArg1, const Vector3* pArg2 );
	extern float FKFastcall _Def_Vec3Length( const Vector3* pIn );
	extern void FKFastcall _Def_Vec3Normalize( Vector3* pOut, const Vector3* pIn );
	extern void FKFastcall _Def_Vec3NormalizeFast( Vector3* pOut, const Vector3* pIn, float fLenth );
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Vector3 >		Vector3Stack;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
