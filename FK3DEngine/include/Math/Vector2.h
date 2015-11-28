/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Vector2
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
	class FK_DLL Vector2
	{
	public:
		union
		{
			struct
			{
				float x;
				float y;
			};
			float v[2];
		};

	public:
		//����ֵ����
		static Vector2 Identity;
		static Vector2 Zero;
		static Vector2 UnitX;
		static Vector2 UnitY;

	public:
		//��ͬ�Ĺ��캯��
		Vector2();
		Vector2( const Vector2& v2 );
		Vector2( const float fx, const float fy );
		Vector2( const float pVal[2] );

		//���������������
		Vector2& operator = ( const Vector2& v2 );
		bool operator == ( const Vector2& v2 ) const;
		bool operator != ( const Vector2& v2 ) const;
		bool operator > ( const Vector2& v2 ) const;
		bool operator < ( const Vector2& v2 ) const;
		bool operator >= ( const Vector2& v2 ) const;
		bool operator <= ( const Vector2& v2 ) const;
		Vector2 operator + () const;
		Vector2 operator - () const;
		Vector2 operator + ( const Vector2& v2 ) const;
		Vector2 operator - ( const Vector2& v2 ) const;
		Vector2 operator * ( const Vector2& v2 ) const;
		Vector2 operator / ( const Vector2& v2 ) const;
		Vector2 operator * ( const float fScalar ) const;
		Vector2 operator / ( const float fScalar ) const;
		void operator += ( const Vector2& v2 );
		void operator -= ( const Vector2& v2 );
		void operator *= ( const Vector2& v2 );
		void operator /= ( const Vector2& v2 );
		void operator *= ( const float fScalar );
		void operator /= ( const float fScalar );

		//��ȡ��ʸ������һʸ���ĵ�˻�
		float GetDot( const Vector2& v2 ) const;

		//��ȡ��ʸ���ĳ���
		float GetLength() const;

		//��λ����ʸ��
		void Normalize();

		//��ȡ��ʸ���ĵ�λ��ʸ��
		Vector2 GetNormalizedVec() const;

		//���ٵ�λ����ʸ������Ҫ�����ʸ���ĵ�λ���ȣ�
		void NormalizeFast( const float fLenth );

		//���ٻ�ȡ��ʸ���ĵ�λ��ʸ������Ҫ�����ʸ���ĵ�λ���ȣ�
		Vector2 GetNormalizedVecFast( const float fLength ) const;
	};
	//--------------------------------------------------------------------------------------------------------------
	//����Ż���άʸ����ѧ���㺯��ָ��
	extern void		( FKFastcall *Vec2Add )				( Vector2* pOut, const Vector2* pArg1, const Vector2* pArg2 );
	extern void		( FKFastcall *Vec2Sub )				( Vector2* pOut, const Vector2* pOrg, const Vector2* pSub );
	extern void		( FKFastcall *Vec2Mul )				( Vector2* pOut, const Vector2* pArg1, const Vector2* pArg2 );
	extern void		( FKFastcall *Vec2Div )				( Vector2* pOut, const Vector2* pOrg, const Vector2* pDiv );
	extern void		( FKFastcall *Vec2MulScalar )		( Vector2* pOut, const Vector2* pOrg, const float fScalar );
	extern void		( FKFastcall *Vec2DivScalar )		( Vector2* pOut, const Vector2* pOrg, const float fScalar );

	extern float	( FKFastcall *Vec2Dot )				( const Vector2* pArg1, const Vector2* pArg2 );
	extern float	( FKFastcall *Vec2Length )			( const Vector2* pIn );
	extern void		( FKFastcall *Vec2Normalize )		( Vector2* pOut, const Vector2* pIn );
	extern void		( FKFastcall *Vec2NormalizeFast )	( Vector2* pOut, const Vector2* pIn, float fLenth );
	//--------------------------------------------------------------------------------------------------------------
	//Ĭ�϶�άʸ����ѧ���㺯��
	extern void FKFastcall _Def_Vec2Add( Vector2* pOut, const Vector2* pArg1, const Vector2* pArg2 );
	extern void FKFastcall _Def_Vec2Sub( Vector2* pOut, const Vector2* pOrg, const Vector2* pSub );
	extern void FKFastcall _Def_Vec2Mul( Vector2* pOut, const Vector2* pArg1, const Vector2* pArg2 );
	extern void FKFastcall _Def_Vec2Div( Vector2* pOut, const Vector2* pOrg, const Vector2* pDiv );
	extern void FKFastcall _Def_Vec2MulScalar( Vector2* pOut, const Vector2* pOrg, const float fScalar );
	extern void FKFastcall _Def_Vec2DivScalar( Vector2* pOut, const Vector2* pOrg, const float fScalar );

	extern float FKFastcall _Def_Vec2Dot( const Vector2* pArg1, const Vector2* pArg2 );
	extern float FKFastcall _Def_Vec2Length( const Vector2* pIn );
	extern void FKFastcall _Def_Vec2Normalize( Vector2* pOut, const Vector2* pIn );
	extern void FKFastcall _Def_Vec2NormalizeFast( Vector2* pOut, const Vector2* pIn, float fLenth );
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Vector2 >		Vector2Stack;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
