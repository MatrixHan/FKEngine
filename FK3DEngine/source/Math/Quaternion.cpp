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
	//����Ż���Ԫ����ѧ���㺯��ָ��
	//--------------------------------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------------------------------
	//����ֵ����
	//--------------------------------------------------------------------------------------------------------------
	Quaternion Quaternion::Identity( 0.0f, 0.0f, 0.0f, 1.0f );
	Quaternion Quaternion::Zero( 0.0f, 0.0f, 0.0f, 0.0f );
	//--------------------------------------------------------------------------------------------------------------
	//��ͬ�Ĺ��캯��
	//--------------------------------------------------------------------------------------------------------------
	Quaternion::Quaternion()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	Quaternion::Quaternion( const Quaternion& quat )
		: x		(quat.x)
		, y		(quat.y)
		, z		(quat.z)
		, w		(quat.w)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	Quaternion::Quaternion( const float fx, const float fy, const float fz, const float fw )
		: x		(fx)
		, y		(fy)
		, z		(fz)
		, w		(fw)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	Quaternion::Quaternion( const float* pVal )
		: x		(pVal[0])
		, y		(pVal[1])
		, z		(pVal[2])
		, w		(pVal[3])
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	Quaternion::Quaternion( const float Pitch, const float Yaw, const float Roll )
	{
		SetRotationPitchYawRoll( Pitch, Yaw, Roll );
	}
	//--------------------------------------------------------------------------------------------------------------
	Quaternion::Quaternion( const float Degree, const Vector3& Axis )
	{
		SetRotationAxis( Degree, Axis );
	}
	//--------------------------------------------------------------------------------------------------------------
	Quaternion::Quaternion( const Matrix3& mat3 )
	{
		SetRotationMatrix3( mat3 );
	}
	//--------------------------------------------------------------------------------------------------------------
	Quaternion::Quaternion( const Matrix4& mat4 )
	{
		SetRotationMatrix4( mat4 );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������������
	//--------------------------------------------------------------------------------------------------------------
	Quaternion& Quaternion::operator = ( const Quaternion& quat )
	{
		x = quat.x;
		y = quat.y;
		z = quat.z;
		w = quat.w;

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	bool Quaternion::operator == ( const Quaternion& quat ) const
	{
		return ( x == quat.x && y == quat.y && z == quat.z && w == quat.w );
	}
	//--------------------------------------------------------------------------------------------------------------
	bool Quaternion::operator != ( const Quaternion& quat ) const
	{
		return ( x != quat.x || y != quat.y || z != quat.z || w != quat.w );
	}
	//--------------------------------------------------------------------------------------------------------------
	Quaternion Quaternion::operator + ( const Quaternion& quat ) const
	{
		static Quaternion tmp;
		tmp.x = x + quat.x;
		tmp.y = y + quat.y;
		tmp.z = z + quat.z;
		tmp.w = w + quat.w;
		return tmp;
	}
	//--------------------------------------------------------------------------------------------------------------
	Quaternion Quaternion::operator - ( const Quaternion& quat ) const
	{
		static Quaternion tmp;
		tmp.x = x - quat.x;
		tmp.y = y - quat.y;
		tmp.z = z - quat.z;
		tmp.w = w - quat.w;
		return tmp;
	}
	//--------------------------------------------------------------------------------------------------------------
	Quaternion Quaternion::operator * ( const Quaternion& quat ) const
	{
		static Quaternion tmp;
		tmp.x = w * quat.x + x * quat.w + y * quat.z - z * quat.y;
		tmp.y = w * quat.y + y * quat.w + z * quat.x - x * quat.z;
		tmp.z = w * quat.z + z * quat.w + x * quat.y - y * quat.x;
		tmp.w = w * quat.w - x * quat.x - y * quat.y - z * quat.z;
		return tmp;
	}
	//--------------------------------------------------------------------------------------------------------------
	Quaternion Quaternion::operator * ( const float fScalar ) const
	{
		static Quaternion tmp;
		tmp.x = x * fScalar;
		tmp.y = y * fScalar;
		tmp.z = z * fScalar;
		tmp.w = w * fScalar;
		return tmp;
	}
	//--------------------------------------------------------------------------------------------------------------
	Vector3 Quaternion::operator * ( const Vector3 v3 ) const
	{
		static Vector3 uv, uuv;

		// uv = quat( x y z ) cross v3
		uv.x = y * v3.z - z * v3.y;
		uv.y = z * v3.x - x * v3.z;
		uv.z = x * v3.y - y * v3.x;

		// uuv = quat( x y z ) cross uv
		uuv.x = y * uv.z - z * uv.y;
		uuv.y = z * uv.x - x * uv.z;
		uuv.z = x * uv.y - y * uv.x;

		uv *= 2.0f * w;
		uuv *= 2.0f;

		// return v3 + uv + uuv
		uuv += uv + v3;

		return uuv;
	}
	//--------------------------------------------------------------------------------------------------------------
	void Quaternion::operator += ( const Quaternion& quat )
	{
		x += quat.x;
		y += quat.y;
		z += quat.z;
		w += quat.w;
	}
	//--------------------------------------------------------------------------------------------------------------
	void Quaternion::operator -= ( const Quaternion& quat )
	{
		x -= quat.x;
		y -= quat.y;
		z -= quat.z;
		w -= quat.w;
	}
	//--------------------------------------------------------------------------------------------------------------
	void Quaternion::operator *= ( const Quaternion& quat )
	{
		static Quaternion tmp;
		tmp.x = w * quat.x + x * quat.w + y * quat.z - z * quat.y;
		tmp.y = w * quat.y + y * quat.w + z * quat.x - x * quat.z;
		tmp.z = w * quat.z + z * quat.w + x * quat.y - y * quat.x;
		tmp.w = w * quat.w - x * quat.x - y * quat.y - z * quat.z;
		x = tmp.x;
		y = tmp.y;
		z = tmp.z;
		w = tmp.w;
	}
	//--------------------------------------------------------------------------------------------------------------
	void Quaternion::operator *= ( const float fScalar )
	{
		x *= fScalar;
		y *= fScalar;
		z *= fScalar;
		w *= fScalar;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ŷ����������Ԫ��
	void Quaternion::SetRotationPitchYawRoll( const float Pitch, const float Yaw, const float Roll )
	{
		float SinX, CosX;
		float SinY, CosY;
		float SinZ, CosZ;

		SinCos( FK_DegreeToRadian(Pitch) * 0.5f,	&SinX, &CosX );
		SinCos( FK_DegreeToRadian(Yaw) * 0.5f,		&SinY, &CosY );
		SinCos( FK_DegreeToRadian(Roll) * 0.5f,		&SinZ, &CosZ );

		//������ X Y Z ����ת����Ԫ�����������
		//
		// QuatPitch	= [	sin(X/2),	0,			0,			cos(X/2) ]
		// QuatYaw		= [	0,			sin(Y/2),	0,			cos(Y/2) ]
		// QuatRoll		= [	0,			0,			sin(Z/2),	cos(Z/2) ]
		//
		// QuatResult = QuatRoll * QuatPitch * QuatYaw		ZXY

		float CosYCosZ = CosY * CosZ;   
		float SinYSinZ = SinY * SinZ;
		float SinYCosZ = SinY * CosZ;
		float CosYSinZ = CosY * SinZ;

		x = CosYCosZ * SinX + SinYSinZ * CosX;
		y = SinYCosZ * CosX - CosYSinZ * SinX;
		z = CosYSinZ * CosX - SinYCosZ * SinX;
		w = CosYCosZ * CosX + SinYSinZ * SinX;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����Զ�����������Ԫ��
	void Quaternion::SetRotationAxis( const float Degree, const Vector3& Axis )
	{
		float sin;
		SinCos( FK_DegreeToRadian(Degree) * 0.5, &sin, &w );

		x = sin * Axis.x;
		y = sin * Axis.y;
		z = sin * Axis.z;

		Normalize();
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ת����������Ԫ��
	void Quaternion::SetRotationMatrix3( const Matrix3& mat3 )
	{
		float fTrace = mat3._11 + mat3._22 + mat3._33;
        float fRoot;

        if( fTrace > 0.0f )
        {
            fRoot = Sqrt( fTrace + 1.0f );
            w = 0.5f * fRoot;
            fRoot = 0.5f / fRoot;
			x = ( mat3._32 - mat3._23 ) * fRoot;
			y = ( mat3._13 - mat3._31 ) * fRoot;
			z = ( mat3._21 - mat3._12 ) * fRoot;
        }
        else
        {
            static int nNext[3] = { 1, 2, 0 };

            int i = 0;
            if( mat3._22 > mat3._11 )
                i = 1;
            if( mat3._33 > mat3.m[i][i] )
                i = 2;
            int j = nNext[i];
            int k = nNext[j];

            fRoot = Sqrt( mat3.m[i][i] - mat3.m[j][j] - mat3.m[k][k] + 1.0f );
            float* apkQuat[3] = { &x, &y, &z };
            *apkQuat[i] = 0.5 * fRoot;
            fRoot = 0.5 / fRoot;
            w = ( mat3.m[k][j] - mat3.m[j][k] ) * fRoot;
            *apkQuat[j] = ( mat3.m[j][i]+mat3.m[i][j] ) * fRoot;
            *apkQuat[k] = ( mat3.m[k][i]+mat3.m[i][k] ) * fRoot;
        }
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ת����������Ԫ��
	void Quaternion::SetRotationMatrix4( const Matrix4& mat4 )
	{
		float fTrace = mat4._11 + mat4._22 + mat4._33;
		float fRoot;

		if( fTrace > 0.0f )
		{
			fRoot = Sqrt( fTrace + 1.0f );
			w = 0.5f * fRoot;
			fRoot = 0.5f / fRoot;
			x = ( mat4._32 - mat4._23 ) * fRoot;
			y = ( mat4._13 - mat4._31 ) * fRoot;
			z = ( mat4._21 - mat4._12 ) * fRoot;
		}
		else
		{
			static int nNext[3] = { 1, 2, 0 };

			int i = 0;
			if( mat4._22 > mat4._11 )
				i = 1;
			if( mat4._33 > mat4.m[i][i] )
				i = 2;
			int j = nNext[i];
			int k = nNext[j];

			fRoot = Sqrt( mat4.m[i][i] - mat4.m[j][j] - mat4.m[k][k] + 1.0f );
			float* apkQuat[3] = { &x, &y, &z };
			*apkQuat[i] = 0.5 * fRoot;
			fRoot = 0.5 / fRoot;
			w = ( mat4.m[k][j] - mat4.m[j][k] ) * fRoot;
			*apkQuat[j] = ( mat4.m[j][i]+mat4.m[i][j] ) * fRoot;
			*apkQuat[k] = ( mat4.m[k][i]+mat4.m[i][k] ) * fRoot;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��Ԫ�����Զ�������ת����
	void Quaternion::GetRotationAxis( float* pDegree, Vector3* pAxis )
	{
		float fSqrLength = x * x + y * y + z * z;
		if( fSqrLength > 0.0f )
		{
			*pDegree = 2.0f * ACos( w );
			float fInvLength = RSqrt( fSqrLength );
			pAxis->x = x * fInvLength;
			pAxis->y = y * fInvLength;
			pAxis->z = z * fInvLength;
		}
		else
		{
			*pDegree = 0.0f;
			pAxis->x = 1.0f;
			pAxis->y = 0.0f;
			pAxis->z = 0.0f;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��Ԫ����ת��������
	void Quaternion::GetRotationMatrix3( Matrix3* pMat3 )
	{
		float fTx  = 2.0f * x;
		float fTy  = 2.0f * y;
		float fTz  = 2.0f * z;
		float fTwx = fTx * w;
		float fTwy = fTy * w;
		float fTwz = fTz * w;
		float fTxx = fTx * x;
		float fTxy = fTy * x;
		float fTxz = fTz * x;
		float fTyy = fTy * y;
		float fTyz = fTz * y;
		float fTzz = fTz * z;

		pMat3->_11 = 1.0f - ( fTyy + fTzz );
		pMat3->_12 = fTxy - fTwz;
		pMat3->_13 = fTxz + fTwy;

		pMat3->_21 = fTxy + fTwz;
		pMat3->_22 = 1.0f - ( fTxx + fTzz );
		pMat3->_23 = fTyz - fTwx;

		pMat3->_31 = fTxz - fTwy;
		pMat3->_32 = fTyz + fTwx;
		pMat3->_33 = 1.0f - ( fTxx + fTyy );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��Ԫ����ת��������
	void Quaternion::GetRotationMatrix4( Matrix4* pMat4 )
	{
		float fTx  = 2.0f * x;
		float fTy  = 2.0f * y;
		float fTz  = 2.0f * z;
		float fTwx = fTx * w;
		float fTwy = fTy * w;
		float fTwz = fTz * w;
		float fTxx = fTx * x;
		float fTxy = fTy * x;
		float fTxz = fTz * x;
		float fTyy = fTy * y;
		float fTyz = fTz * y;
		float fTzz = fTz * z;

		pMat4->_11 = 1.0f - ( fTyy + fTzz );
		pMat4->_12 = fTxy - fTwz;
		pMat4->_13 = fTxz + fTwy;
		pMat4->_14 = 0.0f;

		pMat4->_21 = fTxy + fTwz;
		pMat4->_22 = 1.0f - ( fTxx + fTzz );
		pMat4->_23 = fTyz - fTwx;
		pMat4->_24 = 0.0f;

		pMat4->_31 = fTxz - fTwy;
		pMat4->_32 = fTyz + fTwx;
		pMat4->_33 = 1.0f - ( fTxx + fTyy );
		pMat4->_34 = 0.0f;

		pMat4->_41 = 0.0f;
		pMat4->_42 = 0.0f;
		pMat4->_43 = 0.0f;
		pMat4->_44 = 1.0f;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��Ԫ����˻�
	float Quaternion::GetDot( const Quaternion& quat )
	{
		return w * quat.w + x * quat.x + y * quat.y + z * quat.z;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��Ԫ������
	float Quaternion::GetLength()
	{
		return w * w + x * x + y * y + z * z;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ԫ����λ��
	void Quaternion::Normalize()
	{
		float len = w * w + x * x + y * y + z * z;
		*this = *this * RSqrt( len );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��Ԫ������
	Quaternion Quaternion::GetInverse()
	{
		float len = w * w + x * x + y * y + z * z;
		if( len > 0.0f )
		{
			float fInvLen = 1.0 / len;
			static Quaternion tmp;
			tmp.w = w * fInvLen;
			tmp.x = -x * fInvLen;
			tmp.y = -y * fInvLen;
			tmp.z = -z * fInvLen;
			return tmp;
		}
		else
		{
			return Zero;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ԫ������
	void Quaternion::SetInverse()
	{
		float len = w * w + x * x + y * y + z * z;
		if( len > 0.0f )
		{
			float fInvLen = 1.0 / len;
			w *= fInvLen;
			x = -x * fInvLen;
			y = -y * fInvLen;
			z = -z * fInvLen;
		}
		else
		{
			*this = Zero;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
