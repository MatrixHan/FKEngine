/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BaseMath
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
	// ��ѧ�����ú���
	//--------------------------------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------------------------------
	//��ʼ����ѧ��
	bool InitializeMathLibrary( const CPUInfo* pCPUInfo )
	{
		//������� CPU ָ�֧����Ϣ
		if( pCPUInfo != NULL )
		{
			//���ݲ�ͬ�� CPU ָ�֧��������ú���ָ��
			if( pCPUInfo->_Ext._3DNOW_InstructionExtensions )
			{
				Sqrt	= _3DNOW_Sqrt;
				RSqrt	= _3DNOW_RSqrt;

				Vec2Div				= _3DNOW_Vec2Div;
				Vec2DivScalar		= _3DNOW_Vec2DivScalar;

				Vec2Normalize		= _3DNOW_Vec2Normalize;
				Vec2NormalizeFast	= _3DNOW_Vec2NormalizeFast;

				Vec3Div				= _3DNOW_Vec3Div;
				Vec3DivScalar		= _3DNOW_Vec3DivScalar;

				Vec3Normalize		= _3DNOW_Vec3Normalize;
				Vec3NormalizeFast	= _3DNOW_Vec3NormalizeFast;

				Vec4Div				= _3DNOW_Vec4Div;
				Vec4DivScalar		= _3DNOW_Vec4DivScalar;

				Vec4Normalize		= _3DNOW_Vec4Normalize;
				Vec4NormalizeFast	= _3DNOW_Vec4NormalizeFast;

				Mat4TransVec4		= _3DNOW_Mat4TransVec4;
			}
			else if( pCPUInfo->_Ext.SSE_StreamingSIMD_Extensions )
			{
				Sqrt	= _SSE_Sqrt;
				RSqrt	= _SSE_RSqrt;
			}

			if( pCPUInfo->_Ext.SSE2_StreamingSIMD2_Extensions )
			{
				Cos		= _SSE2_Cos;
				SinCos	= _SSE2_SinCos;
			}
			else if( pCPUInfo->_Ext.SSE_StreamingSIMD_Extensions )
			{
				Cos		= _SSE_Cos;
				SinCos	= _SSE_SinCos;
			}
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------------------------------
	// ������ѧ���㺯��ָ��
	//--------------------------------------------------------------------------------------------------------------

	float	( FKFastcall *Sin )		( float radian )							= _Def_Sin;		//��������
	float	( FKFastcall *Cos )		( float radian )							= _Def_Cos;		//��������
	void	( FKFastcall *SinCos )	( float radian, float* pSin, float* pCos )	= _Def_SinCos;	//�������Һ�����
	float	( FKFastcall *ASin )	( float sin )								= _Def_ASin;	//�������Ҽ������
	float	( FKFastcall *ACos )	( float cos )								= _Def_ACos;	//�������Ҽ������
	float	( FKFastcall *Tan )		( float radian )							= _Def_Tan;		//��������
	float	( FKFastcall *Cot )		( float radian )							= _Def_Cot;		//��������
	float	( FKFastcall *ATan )	( float x, float y )						= _Def_ATan;	//�������м������
	float	( FKFastcall *Abs )		( float val )								= _Def_Abs;		//�����ֵ
	float	( FKFastcall *Sqrt )	( float val )								= _Def_Sqrt;	//����ƽ����
	float	( FKFastcall *RSqrt )	( float val )								= _Def_RSqrt;	//����ƽ�����ĵ���

	//--------------------------------------------------------------------------------------------------------------
	// Ĭ����ѧ���㺯��
	//--------------------------------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------------------------------
	//��������
	float FKFastcall _Def_Sin( float radian )
	{
		__asm
		{
			fld radian;
			fsin;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	float FKFastcall _Def_Cos( float radian )
	{
		__asm
		{
			fld radian;
			fcos;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������Һ�����
	void FKFastcall _Def_SinCos( float radian, float* pSin, float* pCos )
	{
		__asm
		{
			fld			radian;
			fsincos;

			mov			eax, pCos;
			mov			ebx, pSin;

			fstp		[eax];
			fstp		[ebx];
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������Ҽ������
	float FKFastcall _Def_ASin( float sin )
	{
		return asinf( sin );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������Ҽ������
	float FKFastcall _Def_ACos( float cos )
	{
		return acosf( cos );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	float FKFastcall _Def_Tan( float radian )
	{
		__asm
		{
			fld		radian;			// st0 = radian
			fptan;					// y / x = tan( radian ) st0 = x, st1 = y
			fdivp	st(1), st(0);	// st0 = y / x
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	float FKFastcall _Def_Cot( float radian )
	{
		__asm
		{
			fld		radian;			// st0 = radian
			fptan;					// y / x = tan( radian ) st0 = x, st1 = y
			fdiv	st(0), st(1);	// st0 = x / y
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������м������
	float FKFastcall _Def_ATan( float x, float y )
	{
		__asm
		{
			fld		x;		// st0 = �Ա�
			fld		y;		// st0 = �ڱ�, st1 = �Ա�
			fpatan;			// st0 = ����
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ֵ
	float FKFastcall _Def_Abs( float val )
	{
		__asm
		{
			fld val;
			fabs;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƽ����
	float FKFastcall _Def_Sqrt( float val )
	{
		__asm
		{
			fld val;
			fsqrt;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƽ�����ĵ���
	float FKFastcall _Def_RSqrt( float val )
	{
		__asm
		{
			fld		val;			// st0 = val
			fsqrt;					// st0 = sqrt( val )
			fld1;					// st0 = 1.0, st1 = sqrt( val )
			fdiv	st(0), st(1);	// st0 = 1.0 / sqrt( val )
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//����Ƿ�Ϊ 2 �����޷�������
	FKForceInline bool IsPow2( UINT value )
	{
		//�����
		bool bTrueBit = false;

		while( value != 0 )
		{
			if( value & 1 )
			{
				if( bTrueBit )
					return false;
				else
					bTrueBit = true;
			}

			value >>= 1;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���޷�������ת��Ϊ��ӽ�������С�� 2 �����޷�������
	FKForceInline UINT FloorToPow2( UINT value )
	{
		UINT nNearest = 0x80000000;

		while( nNearest != 0 )
		{
			if( nNearest <= value )
				return nNearest;

			nNearest >>= 1;
		}

		return nNearest;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���޷�������ת��Ϊ��ӽ���������� 2 �����޷�������
	FKForceInline UINT CeilToPow2( UINT value )
	{
		UINT nNearest = 1;

		while( nNearest != 0x80000000 )
		{
			if( nNearest >= value )
				return nNearest;

			nNearest <<= 1;
		}

		return nNearest;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�з�����������
	FKForceInline void Div( const int value, const int divisor, int& quotient, int& remainder )
	{
		__asm
		{
			mov		eax, value;
			cdq;
			idiv	divisor;
			mov		ebx, quotient;
			mov		ecx, remainder;
			mov		[ebx], eax;
			mov		[ecx], edx;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�޷�����������
	FKForceInline void Div( const unsigned int value, const unsigned int divisor,
		unsigned int& quotient, unsigned int& remainder )
	{
		__asm
		{
			mov		eax, value;
			xor		edx, edx;
			div		divisor;
			mov		ebx, quotient;
			mov		ecx, remainder;
			mov		[ebx], eax;
			mov		[ecx], edx;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ת��Ϊ��ӽ�������С���������� (int)floor(value) �� 5 �����ң�
	FKForceInline int FloorToInt( float value )
	{
		int CtrlwdHolder;
		int CtrlwdSetter;
		int ReturnValue;

		__asm
		{
			fld    value;
			fnstcw CtrlwdHolder;
			movzx  eax, CtrlwdHolder;
			and    eax, 0xFFFFF3FF;
			or     eax, 0x00000400;
			mov    CtrlwdSetter, eax;
			fldcw  CtrlwdSetter;
			fistp  ReturnValue;
			fldcw  CtrlwdHolder;
		}

		return ReturnValue;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ת��Ϊ��ӽ������������������ (int)ceil(value) �� 5 �����ң�
	FKForceInline int CeilToInt( float value )
	{
		int CtrlwdHolder;
		int CtrlwdSetter;
		int ReturnValue;

		__asm
		{
			fld    value;
			fnstcw CtrlwdHolder;
			movzx  eax, CtrlwdHolder;
			and    eax, 0xFFFFF3FF;
			or     eax, 0x00000800;
			mov    CtrlwdSetter, eax;
			fldcw  CtrlwdSetter;
			fistp  ReturnValue;
			fldcw  CtrlwdHolder;
		}

		return ReturnValue;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
