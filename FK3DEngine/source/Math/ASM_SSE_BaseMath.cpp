/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ASM_SSE_BaseMath
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ѧ�� SSE ���� �����㺯��
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/Math/MathInsideHead.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	float FKFastcall _SSE_Cos( float degree )
	{
		// shufps ָ��˵����
		//
		//    shufps xmm0, xmm1, 0;
		//
		//    ���� xmm0 ΪĿ�Ĳ������ͼ������洢��ַ��xmm1 ΪԴ��������0 Ϊ 8 λ��ѡ�����롣
		//
		//  1. ����Ŀ�Ĳ�������4 ����ֵ��ѡ�����������ֵ�ƶ����������ĵ� 8 �ֽ�
		//  2. ����Դ��������4 ����ֵ��ѡ�����������ֵ�ƶ����������ĸ� 8 �ֽ�
		//
		//    ѡ������� 0��1 λ��ʾ��Ŀ�Ĳ������ƶ�������ĵ�һ����������������
		//    ѡ������� 2��3 λ��ʾ��Ŀ�Ĳ������ƶ�������ĵڶ�����������������
		//    ѡ������� 4��5 λ��ʾ��Դ�������ƶ�������ĵ�������������������
		//    ѡ������� 6��7 λ��ʾ��Դ�������ƶ�������ĵ��ĸ���������������
		//
		//  ����
		//		xmm0 = { 0.1f, 0.2f, 0.3f, 0.4f };     xmm1 = { 0.5f, 0.6f, 0.7f, 0.8f };
		//
		//      shufps xmm0, xmm1, ( 1 | 2<<2 | 0<<4 | 3<<6 );
		//
		//      xmm0 = { 0.2f, 0.3f, 0.5f, 0.8f );

		float temp;
		__asm
		{
			movss	xmm0, degree;
			movss	xmm1, _ps_am_inv_sign_mask;
			andps	xmm0, xmm1;
			addss	xmm0, _ps_am_pi_o_2;
			mulss	xmm0, _ps_am_2_o_pi;

			cvttss2si	ecx, xmm0;
			movss	xmm5, _ps_am_1;
			mov		edx, ecx;
			shl		edx, (31 - 1);
			cvtsi2ss	xmm1, ecx;
			and		edx, 0x80000000;
			and		ecx, 0x1;

			subss	xmm0, xmm1;
			movss	xmm6, CONST_SINCOS_MASK[ecx * 4];
			minss	xmm0, xmm5;

			movss	xmm1, _ps_sincos_p3;
			subss	xmm5, xmm0;

			andps	xmm5, xmm6;
			movss	xmm7, _ps_sincos_p2;
			andnps	xmm6, xmm0;
			mov		temp, edx;
			orps	xmm5, xmm6;
			movss	xmm0, xmm5;

			mulss	xmm5, xmm5;
			movss	xmm4, _ps_sincos_p1;
			movss	xmm2, xmm5;
			mulss	xmm5, xmm1;
			movss	xmm1, _ps_sincos_p0;
			addss	xmm5, xmm7;
			mulss	xmm5, xmm2;
			movss	xmm3, temp;
			addss	xmm5, xmm4;
			mulss	xmm5, xmm2;
			orps	xmm0, xmm3;
			addss	xmm5, xmm1;
			mulss	xmm0, xmm5;

			movss   degree, xmm0;
		}

		return degree;
	}
	//--------------------------------------------------------------------------------------------------------------
	void FKFastcall _SSE_SinCos( float degree, float* pSin, float* pCos )
	{
		float t4, t8, t12;
		__asm
		{
			movss	xmm0, degree;
			movss	t12, xmm0;
			movss	xmm1, _ps_am_inv_sign_mask;
			mov		eax, t12;
			mulss	xmm0, _ps_am_2_o_pi;
			andps	xmm0, xmm1;
			and		eax, 0x80000000;

			cvttss2si	edx, xmm0;
			mov		ecx, edx;
			mov		t12, esi;
			mov		esi, edx;
			add		edx, 0x1;
			shl		ecx, (31 - 1);
			shl		edx, (31 - 1);

			movss	xmm4, _ps_am_1;
			cvtsi2ss	xmm3, esi;
			mov		t8, eax;
			and		esi, 0x1;

			subss	xmm0, xmm3;
			movss	xmm3, CONST_SINCOS_INV_MASK[esi * 4];
			minss	xmm0, xmm4;

			subss	xmm4, xmm0;

			movss	xmm6, xmm4;
			andps	xmm4, xmm3;
			and		ecx, 0x80000000;
			movss	xmm2, xmm3;
			andnps	xmm3, xmm0;
			and		edx, 0x80000000;
			movss	xmm7, t8;
			andps	xmm0, xmm2;
			mov		t8, ecx;
			mov		t4, edx;
			orps	xmm4, xmm3;

			mov		eax, pSin; //mov eax, [esp + 4 + 16]
			mov		edx, pCos; //mov edx, [esp + 4 + 16 + 4]

			andnps	xmm2, xmm6;
			orps	xmm0, xmm2;

			movss	xmm2, t8;
			movss	xmm1, xmm0;
			movss	xmm5, xmm4;
			xorps	xmm7, xmm2;
			movss	xmm3, _ps_sincos_p3;
			mulss	xmm0, xmm0;
			mulss	xmm4, xmm4;
			movss	xmm2, xmm0;
			movss	xmm6, xmm4;
			orps	xmm1, xmm7;
			movss	xmm7, _ps_sincos_p2;
			mulss	xmm0, xmm3;
			mulss	xmm4, xmm3;
			movss	xmm3, _ps_sincos_p1;
			addss	xmm0, xmm7;
			addss	xmm4, xmm7;
			movss	xmm7, _ps_sincos_p0;
			mulss	xmm0, xmm2;
			mulss	xmm4, xmm6;
			addss	xmm0, xmm3;
			addss	xmm4, xmm3;
			movss	xmm3, t4;
			mulss	xmm0, xmm2;
			mulss	xmm4, xmm6;
			orps	xmm5, xmm3;
			mov		esi, t12;
			addss	xmm0, xmm7;
			addss	xmm4, xmm7;
			mulss	xmm0, xmm1;
			mulss	xmm4, xmm5;

			movss	[eax], xmm0;
			movss	[edx], xmm4;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	float FKFastcall _SSE_Sqrt( float val )
	{
		float Root;

		__asm
		{
			sqrtss xmm0, val;
			movss Root, xmm0;
		}

		return Root;
	}
	//--------------------------------------------------------------------------------------------------------------
	float FKFastcall _SSE_RSqrt( float val )
	{
		float Root;

		__asm
		{
			rsqrtss xmm0, val;
			movss Root, xmm0;
		}

		return Root;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
