/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Math
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#pragma warning( disable : 4244 )
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//! Pi
	const double PI = 3.1415926536;

	//! �ض�һ��������С������
	inline long Trunc( double p_dValue )
	{
		return static_cast< long >( p_dValue );
	}

	//! ��������һ��������������������
	inline long Round( double p_dValue )
	{
		if( p_dValue >= 0 )
		{
			return static_cast< long >( p_dValue + 0.5 );
		}
		else
		{
			return static_cast< long >( p_dValue - 0.5 );
		}
	}

	//! ����һ���� min �� max �ڵ�һ���������ֵ��
	//! �ڲ�ʹ�� std::rand �������ڵ��øú���֮ǰ�����ȵ��� std::random
	double Random( double p_dMin, double p_dMax );

	//! ��FKAngle��תΪ����
	inline double FKAngleToRadians( double p_dAngle )
	{
		return ( p_dAngle - 90 ) * PI / 180;
	}

	//! ������ת��ΪFKAngle
	inline double RadiansToFKAngle( double p_dAngle )
	{
		return p_dAngle * 180 / PI + 90;
	}

	//! �Ƕ�ת��Ϊ����
	inline double DegreesToRadians( double p_dAngle )
	{
		return p_dAngle * PI / 180;
	}

	//! ����ת��Ϊ�Ƕ�
	inline double RadiansToDegrees( double p_dAngle )
	{
		return p_dAngle * 180 / PI;
	}

	//! ����һ������ԭ��� X ����ƫ��
	//! \param p_dAngle �õ㵽ԭ��֮����߶νǶȡ����� 0 �Ƚ��������ϡ�
	//! \param p_dRadius �õ���ԭ��֮����߶ξ��롣
	double OffsetX( double p_dAngle, double p_dRadius );

	//! ����ͬ OffsetX ,����һ������ԭ��� Y ����ƫ��
	double OffsetY( double p_dAngle, double p_dRadius );

	//! �����������ߵĽǶȡ����� 0 �ȴ���ֱ���ϡ�
	//! ���������غ�ʱ�������� p_dDefaultValue Ĭ��ֵ��
	double Angle( double p_dFromX, double p_dFromY, double p_dToX, 
		double p_dToY, double p_dDefaultValue = 0 );

	//! �� Angle1 ת��Ϊ Angle2 ����Ҫ��ת����С�Ƕ�
	//! \note ��ֵ����Ϊ��ֵ
	double AngleDiff( double p_dAngle1, double p_dAngle2 );

	//! ��λ��һ���Ƕȣ�����ֵ������ [0, 360] ֮��
	double NormalizeAngle( double p_dAngle );

	//! ����ֵƽ��
	template< typename T >
	T Square( T p_Value )
	{
		return p_Value * p_Value;
	}

	//! ��p_ValueС��p_Min�򷵻�p_Min,��p_Value����p_Max,�򷵻�p_Max,���򷵻�p_Value
	template< typename T >
	T Clamp( T p_Value, T p_Min, T p_Max )
	{
		if( p_Value < p_Min )
		{
			return p_Min;
		}
		if( p_Value > p_Max )
		{
			return p_Max;
		}
		return p_Value;
	}

	//! ��Χ���
	template< typename T >
	T BoundBy( T p_Value, T p_Min, T p_Max )
	{
		return Clamp( p_Value, p_Min, p_Max );
	}

	//! ����( Value - Min ) % ( Max - Min ) + Min
	int Wrap( int p_nValue, int p_nMin, int p_nMax );
	float Wrap( float p_fValue, float p_fMin, float p_fMax );
	double Wrap( double p_dValue, double p_dMin, double p_dMax );

	//! ����������֮������ƽ��
	double DistanceSqr( double p_dX1, double p_dY1, double p_dX2, double p_dY2 );

	//! ����������֮�����
	double Distance( double p_dX1, double p_dY1, double p_dX2, double p_dY2 );

	//! ����Ȩ�ؼ�����ֵ���һ����
	//! ���� Interpolate( 0, 10, 0.2 ) == 2;  Interpolate( 0, 10, 0.6 ) == 6
	template< typename T >
	T Interpolate( T p_A, T p_B, double p_dWeight = 0.5 )
	{
		return p_A * ( 1.0 - p_dWeight ) + p_B * p_dWeight;
	}
}