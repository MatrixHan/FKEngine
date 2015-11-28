/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ASM_BaseMath
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ѧ�� ���� �����㺯��
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	//�رղ���Ҫ�ľ���
	#pragma warning ( disable : 4244 )	//�� 'const int' ǿ��ת��Ϊ 'float' ���ܵ������ݶ�ʧ
	#pragma warning ( disable : 4730 )	//��� _m64 �͸�����ʽ���ܵ��²���ȷ�Ĵ���

	//--------------------------------------------------------------------------------------------------------------
	// ����ʹ�� SSE ������Ҫ�ĺ�ͳ���
	//--------------------------------------------------------------------------------------------------------------

	#define _PS_EXTERN_CONST( Name, Val ) \
	const FKAlign16 float _ps_##Name[4] = { Val, Val, Val, Val }

	#define _PS_EXTERN_CONST_TYPE( Name, Type, Val ) \
	const FKAlign16 Type _ps_##Name[4] = { Val, Val, Val, Val }

	#define _EPI32_CONST( Name, Val ) \
	static FKAlign16 __int32 _epi32_##Name[4] = { Val, Val, Val, Val }

	#define _PS_CONST( Name, Val ) \
	static FKAlign16 float _ps_##Name[4] = { Val, Val, Val, Val }

	_PS_EXTERN_CONST( am_0, 0.0f );
	_PS_EXTERN_CONST( am_1, 1.0f );
	_PS_EXTERN_CONST( am_m1, -1.0f );
	_PS_EXTERN_CONST( am_0p5, 0.5f );
	_PS_EXTERN_CONST( am_1p5, 1.5f );
	_PS_EXTERN_CONST( am_pi, (float)FK_PI );
	_PS_EXTERN_CONST( am_pi_o_2, (float)( FK_PI / 2.0 ) );
	_PS_EXTERN_CONST( am_2_o_pi, (float)( 2.0 / FK_PI ) );
	_PS_EXTERN_CONST( am_pi_o_4, (float)( FK_PI / 4.0 ) );
	_PS_EXTERN_CONST( am_4_o_pi, (float)( 4.0 / FK_PI ) );
	_PS_EXTERN_CONST_TYPE( am_sign_mask, long, 0x80000000 );
	_PS_EXTERN_CONST_TYPE( am_inv_sign_mask, long, ~0x80000000 );
	_PS_EXTERN_CONST_TYPE( am_min_norm_pos, long, 0x00800000);
	_PS_EXTERN_CONST_TYPE( am_mant_mask, long, 0x7f800000);
	_PS_EXTERN_CONST_TYPE( am_inv_mant_mask, long, ~0x7f800000 );

	_EPI32_CONST( 1, 1 );
	_EPI32_CONST( 2, 2 );

	_PS_CONST( sincos_p0, 0.15707963267948963959e1f );
	_PS_CONST( sincos_p1, -0.64596409750621907082e0f );
	_PS_CONST( sincos_p2, 0.7969262624561800806e-1f );
	_PS_CONST( sincos_p3, -0.468175413106023168e-2f );

	static const unsigned long CONST_SINCOS_MASK[]		= { (unsigned long)0x0,  (unsigned long)~0x0 };
	static const unsigned long CONST_SINCOS_INV_MASK[]	= { (unsigned long)~0x0, (unsigned long)0x0 };

	//--------------------------------------------------------------------------------------------------------------
	// 3DNOW ���㺯��
	//--------------------------------------------------------------------------------------------------------------

	extern float FKFastcall _3DNOW_Sqrt( float val );	//����ƽ����
	extern float FKFastcall _3DNOW_RSqrt( float val );	//����ƽ�����ĵ���

	//--------------------------------------------------------------------------------------------------------------
	// SSE ���㺯��
	//--------------------------------------------------------------------------------------------------------------

	extern float FKFastcall _SSE_Cos( float degree );								//��������
	extern void FKFastcall _SSE_SinCos( float degree, float* pSin, float* pCos );	//�������Һ�����
	extern float FKFastcall _SSE_Sqrt( float val );									//����ƽ����
	extern float FKFastcall _SSE_RSqrt( float val );								//����ƽ�����ĵ���

	//--------------------------------------------------------------------------------------------------------------
	// SSE2 ���㺯��
	//--------------------------------------------------------------------------------------------------------------

	extern float FKFastcall _SSE2_Cos( float degree );								//��������
	extern void FKFastcall _SSE2_SinCos( float degree, float* pSin, float* pCos );	//�������Һ�����

	//--------------------------------------------------------------------------------------------------------------
}
//==================================================================================================================
