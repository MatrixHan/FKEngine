/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Vector4
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
	class FK_DLL Vector4
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
		static Vector4 Identity;
		static Vector4 Zero;
		static Vector4 UnitX;
		static Vector4 UnitY;
		static Vector4 UnitZ;

	public:
		//��ͬ�Ĺ��캯��
		Vector4();
		Vector4( const Vector4& v4 );
		Vector4( const Vector3& v3 );
		Vector4( const float fx, const float fy, const float fz, const float fw );
		Vector4( const float pVal[4] );

		//���������������
		Vector4& operator = ( const Vector4& v4 );
		Vector4& operator = ( const Vector3& v3 );
		bool operator == ( const Vector4& v4 ) const;
		bool operator != ( const Vector4& v4 ) const;
		bool operator > ( const Vector4& v4 ) const;
		bool operator < ( const Vector4& v4 ) const;
		bool operator >= ( const Vector4& v4 ) const;
		bool operator <= ( const Vector4& v4 ) const;
		Vector4 operator + () const;
		Vector4 operator - () const;
		Vector4 operator + ( const Vector4& v4 ) const;
		Vector4 operator - ( const Vector4& v4 ) const;
		Vector4 operator * ( const Vector4& v4 ) const;
		Vector4 operator / ( const Vector4& v4 ) const;
		Vector4 operator * ( const float fScalar ) const;
		Vector4 operator / ( const float fScalar ) const;
		Vector4 operator * ( const Matrix4& mat4ref ) const;
		void operator += ( const Vector4& v4 );
		void operator -= ( const Vector4& v4 );
		void operator *= ( const Vector4& v4 );
		void operator /= ( const Vector4& v4 );
		void operator *= ( const float fScalar );
		void operator /= ( const float fScalar );
		void operator *= ( const Matrix4& mat4ref );

		//��ȡ��ʸ������һʸ���ĵ�˻�
		float GetDot( const Vector4& v4 ) const;

		//��ȡ��ʸ���ĳ���
		float GetLength() const;

		//��λ����ʸ��
		void Normalize();

		//��ȡ��ʸ���ĵ�λ��ʸ��
		Vector4 GetNormalizedVec() const;

		//���ٵ�λ����ʸ������Ҫ�����ʸ���ĵ�λ���ȣ�
		void NormalizeFast( const float fLength );

		//���ٻ�ȡ��ʸ���ĵ�λ��ʸ������Ҫ�����ʸ���ĵ�λ���ȣ�
		Vector4 GetNormalizedVecFast( const float fLength ) const;
	};
	//--------------------------------------------------------------------------------------------------------------
	//����Ż���άʸ����ѧ���㺯��ָ��
	extern void		( FKFastcall *Vec4Add )				( Vector4* pOut, const Vector4* pArg1, const Vector4* pArg2 );
	extern void		( FKFastcall *Vec4Sub )				( Vector4* pOut, const Vector4* pOrg, const Vector4* pSub );
	extern void		( FKFastcall *Vec4Mul )				( Vector4* pOut, const Vector4* pArg1, const Vector4* pArg2 );
	extern void		( FKFastcall *Vec4Div )				( Vector4* pOut, const Vector4* pOrg, const Vector4* pDiv );
	extern void		( FKFastcall *Vec4MulScalar )		( Vector4* pOut, const Vector4* pOrg, const float fScalar );
	extern void		( FKFastcall *Vec4DivScalar )		( Vector4* pOut, const Vector4* pOrg, const float fScalar );

	extern float	( FKFastcall *Vec4Dot )				( const Vector4* pArg1, const Vector4* pArg2 );
	extern float	( FKFastcall *Vec4Length )			( const Vector4* pIn );
	extern void		( FKFastcall *Vec4Normalize )		( Vector4* pOut, const Vector4* pIn );
	extern void		( FKFastcall *Vec4NormalizeFast )	( Vector4* pOut, const Vector4* pIn, float fLength );
	//--------------------------------------------------------------------------------------------------------------
	//Ĭ����άʸ����ѧ���㺯��
	extern void FKFastcall _Def_Vec4Add( Vector4* pOut, const Vector4* pArg1, const Vector4* pArg2 );
	extern void FKFastcall _Def_Vec4Sub( Vector4* pOut, const Vector4* pOrg, const Vector4* pSub );
	extern void FKFastcall _Def_Vec4Mul( Vector4* pOut, const Vector4* pArg1, const Vector4* pArg2 );
	extern void FKFastcall _Def_Vec4Div( Vector4* pOut, const Vector4* pOrg, const Vector4* pDiv );
	extern void FKFastcall _Def_Vec4MulScalar( Vector4* pOut, const Vector4* pOrg, const float fScalar );
	extern void FKFastcall _Def_Vec4DivScalar( Vector4* pOut, const Vector4* pOrg, const float fScalar );

	extern float FKFastcall _Def_Vec4Dot( const Vector4* pArg1, const Vector4* pArg2 );
	extern float FKFastcall _Def_Vec4Length( const Vector4* pIn );
	extern void FKFastcall _Def_Vec4Normalize( Vector4* pOut, const Vector4* pIn );
	extern void FKFastcall _Def_Vec4NormalizeFast( Vector4* pOut, const Vector4* pIn, float fLength );
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Vector4 >		Vector4Stack;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
