/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ColorValue
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

	ColorValue ColorValue::White	= ColorValue( 1.0f, 1.0f, 1.0f, 1.0f );	//��ɫ
	ColorValue ColorValue::Black	= ColorValue( 1.0f, 0.0f, 0.0f, 0.0f );	//��ɫ
	ColorValue ColorValue::Red		= ColorValue( 1.0f, 1.0f, 0.0f, 0.0f );	//��ɫ
	ColorValue ColorValue::Green	= ColorValue( 1.0f, 0.0f, 1.0f, 0.0f );	//��ɫ
	ColorValue ColorValue::Blue		= ColorValue( 1.0f, 0.0f, 0.0f, 1.0f );	//��ɫ
	ColorValue ColorValue::Yellow	= ColorValue( 1.0f, 1.0f, 1.0f, 0.0f );	//��ɫ
	ColorValue ColorValue::Purple	= ColorValue( 1.0f, 1.0f, 0.0f, 1.0f );	//��ɫ
	ColorValue ColorValue::Azury	= ColorValue( 1.0f, 0.0f, 1.0f, 1.0f );	//��ɫ

	//--------------------------------------------------------------------------------------------------------------
	ColorValue::ColorValue()
		: A	(1.0f)
		, R	(1.0f)
		, G	(1.0f)
		, B	(1.0f)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	ColorValue::ColorValue( const float a, const float r, const float g, const float b )
		: A	(a)
		, R	(r)
		, G	(g)
		, B	(b)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������
	ColorValue& ColorValue::operator = ( const ColorValue& color )
	{
		A = color.A;
		R = color.R;
		G = color.G;
		B = color.B;

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	FKInline bool ColorValue::operator == ( const ColorValue& color ) const
	{
		if( A != color.A || R != color.R || G != color.G || B != color.B )
			return false;
		else
			return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	FKInline bool ColorValue::operator != ( const ColorValue& color ) const
	{
		if( A != color.A || R != color.R || G != color.G || B != color.B )
			return true;
		else
			return false;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������ɫֵ
	void ColorValue::SetByteColor( const BYTE a, const BYTE r, const BYTE g, const BYTE b )
	{
		const float Inv255 = 1.0f / 255.0f;

		A = (float)a * Inv255;
		R = (float)r * Inv255;
		G = (float)g * Inv255;
		B = (float)b * Inv255;
	}
	//--------------------------------------------------------------------------------------------------------------
	void ColorValue::SetARGB( ARGB color )
	{
		const float Inv255 = 1.0f / 255.0f;

		A = (float)( (BYTE)( color >> 24 ) ) * Inv255;
		R = (float)( (BYTE)( color >> 16 ) ) * Inv255;
		G = (float)( (BYTE)( color >> 8 ) ) * Inv255;
		B = (float)( (BYTE)color ) * Inv255;
	}
	//--------------------------------------------------------------------------------------------------------------
	void ColorValue::SetRGBA( RGBA color )
	{
		const float Inv255 = 1.0f / 255.0f;

		R = (float)( (BYTE)( color >> 24 ) ) * Inv255;
		G = (float)( (BYTE)( color >> 16 ) ) * Inv255;
		B = (float)( (BYTE)( color >> 8 ) ) * Inv255;
		A = (float)( (BYTE)color ) * Inv255;
	}
	//--------------------------------------------------------------------------------------------------------------
	void ColorValue::SetABGR( ABGR color )
	{
		const float Inv255 = 1.0f / 255.0f;

		A = (float)( (BYTE)( color >> 24 ) ) * Inv255;
		B = (float)( (BYTE)( color >> 16 ) ) * Inv255;
		G = (float)( (BYTE)( color >> 8 ) ) * Inv255;
		R = (float)( (BYTE)color ) * Inv255;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ������ɫֵ
	void ColorValue::GetByteColor( BYTE& a, BYTE& r, BYTE& g, BYTE& b ) const
	{
		a = (BYTE)CeilToInt( A * 255.0f );
		r = (BYTE)CeilToInt( R * 255.0f );
		g = (BYTE)CeilToInt( G * 255.0f );
		b = (BYTE)CeilToInt( B * 255.0f );
	}
	//--------------------------------------------------------------------------------------------------------------
	ARGB ColorValue::GetARGB() const
	{
		ARGB valARGB = 0;

		valARGB = (unsigned long)( CeilToInt( A * 255.0f ) << 24 );
		valARGB |= (unsigned long)( CeilToInt( R * 255.0f ) << 16 );
		valARGB |= (unsigned long)( CeilToInt( G * 255.0f ) << 8 );
		valARGB |= (unsigned long)CeilToInt( B * 255.0f );

		return valARGB;
	}
	//--------------------------------------------------------------------------------------------------------------
	RGBA ColorValue::GetRGBA() const
	{
		ARGB valARGB = 0;

		valARGB = (unsigned long)( CeilToInt( R * 255.0f ) << 24 );
		valARGB |= (unsigned long)( CeilToInt( G * 255.0f ) << 16 );
		valARGB |= (unsigned long)( CeilToInt( B * 255.0f ) << 8 );
		valARGB |= (unsigned long)CeilToInt( A * 255.0f );

		return valARGB;
	}
	//--------------------------------------------------------------------------------------------------------------
	ABGR ColorValue::GetABGR() const
	{
		ARGB valARGB = 0;

		valARGB = (unsigned long)( CeilToInt( A * 255.0f ) << 24 );
		valARGB |= (unsigned long)( CeilToInt( B * 255.0f ) << 16 );
		valARGB |= (unsigned long)( CeilToInt( G * 255.0f ) << 8 );
		valARGB |= (unsigned long)CeilToInt( R * 255.0f );

		return valARGB;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
