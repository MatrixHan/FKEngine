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
*	�ļ�˵����	��ѧ�� ��ɫֵ
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	//���ֽ�������ɫֵ����
	typedef unsigned long	ARGB;
	typedef unsigned long	RGBA;
	typedef unsigned long	ABGR;

	//--------------------------------------------------------------------------------------------------------------
	//��ɫֵ
	class FK_DLL ColorValue
	{
	public:
		float R;	//��ɫֵ
		float G;	//��ɫֵ
		float B;	//��ɫֵ
		float A;	//͸��ֵ

	public:
		static ColorValue White;	//��ɫ
		static ColorValue Black;	//��ɫ
		static ColorValue Red;		//��ɫ
		static ColorValue Green;	//��ɫ
		static ColorValue Blue;		//��ɫ
		static ColorValue Yellow;	//��ɫ
		static ColorValue Purple;	//��ɫ
		static ColorValue Azury;	//��ɫ

	public:
		ColorValue();
		ColorValue( const float a, const float r, const float g, const float b );

		//����������
		ColorValue& operator = ( const ColorValue& color );
		FKInline bool operator == ( const ColorValue& color ) const;
		FKInline bool operator != ( const ColorValue& color ) const;

		//����������ɫֵ
		void SetByteColor( const BYTE a, const BYTE r, const BYTE g, const BYTE b );
		void SetARGB( ARGB color );
		void SetRGBA( RGBA color );
		void SetABGR( ABGR color );

		//��ȡ������ɫֵ
		void GetByteColor( BYTE& a, BYTE& r, BYTE& g, BYTE& b ) const;
		ARGB GetARGB() const;
		RGBA GetRGBA() const;
		ABGR GetABGR() const;
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< ColorValue >		ColorValueStack;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
