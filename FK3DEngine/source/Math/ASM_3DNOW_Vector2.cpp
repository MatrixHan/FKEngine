/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ASM_3DNOW_Vector2
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ѧ�� 3DNOW ��άʸ�� �����㺯��
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/Math/MathInsideHead.h"
#include "../../include/Math/amd3dx.h"
//#include "../../include/CommonBase/NoMemoryMarco.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��άʸ�����
	void FKFastcall _3DNOW_Vec2Div( Vector2* pOut, const Vector2* pArg1, const Vector2* pArg2 )
	{
		__asm
		{
			mov		eax, pArg1;
			mov		ebx, pArg2;

			movq	mm0, [eax];			//mm0 = ( x1, y1 )
			movq	mm1, [ebx];			//mm1 = ( x2, y2 )

			pfrcp	mm1, mm1;			//mm1 = ( 1.0f / x2, 1.0f / y2 )
			pfmul	mm0, mm1;			//mm0 = ( x1 / x2, y1 / y2 )

			mov		eax, pOut;
			movq	[eax], mm0;

			femms;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��άʸ�����Ա���
	void FKFastcall _3DNOW_Vec2DivScalar( Vector2* pOut, const Vector2* pOrg, const float fScalar )
	{
		if( fScalar != 0 )
		{
			__asm
			{
				mov			eax, pOrg;
				mov			ebx, pOut;

				movq		mm0, [eax];			//mm0 = ( x1, y1 )

				movd		mm1, fScalar;		//mm1 = ( fScalar, N );
				punpckldq	mm1, mm1;			//mm1 = ( fScalar, fScalar );
				pfrcp		mm1, mm1;			//mm1 = ( 1.0f/fScalar, 1.0f/fScalar )

				pfmul		mm0, mm1;			//mm0 = ( x1/fScalar, y1/fScalar )

				movq		[ebx], mm0;

				femms;
			}
		}
		else
		{
			pOut->x = 0.0f;
			pOut->y = 0.0f;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��άʸ����λ����
	float FKFastcall _3DNOW_Vec2UnitLength( const Vector2* pIn )
	{
		float UnitLength;

		__asm
		{
			mov			eax, pIn;

			movq		mm0, [eax];			//mm0 = ( x, y )

			pfmul		mm0, mm0;			//mm0 = ( x*x, y*y )
			pfacc		mm0, mm0;			//mm0 = ( x*x + y*y, N )

			pfrsqrt		mm1, mm0;			//mm1 = ( 1.0f / Sqrt( x*x + y*y ), N )
			pfmul		mm0, mm1;			//mm0 = ( Sqrt( x*x + y*y ), N )

			movd		UnitLength, mm0;	//Length = mm0;

			femms;
		}

		return UnitLength;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��λ����άʸ��
	void FKFastcall _3DNOW_Vec2Normalize( Vector2* pOut, const Vector2* pIn )
	{
		if( pIn->x != 0.0f || pIn->y != 0.0f )
		{
			__asm
			{
				mov			eax, pIn;
				mov			ebx, pOut;

				movq		mm0, [eax];			//mm0 = ( x, y )
				movq		mm1, mm0;			//mm1 = ( x, y )

				pfmul		mm0, mm0;			//mm0 = ( x*x, y*y )
				pfacc		mm0, mm0;			//mm0 = ( x*x + y*y, N )

				pfrsqrt		mm0, mm0;			//mm0 = ( RUnitLen = 1.0f / Sqrt( x*x + y*y ), N )
				punpckldq	mm0, mm0;			//mm0 = ( RUnitLen, RUnitLen );

				pfmul		mm1, mm0;			//mm1 = ( x / UnitLen, y / UnitLen );

				movq		[ebx], mm1;

				femms;
			}
		}
		else
		{
			pOut->x = 0.0f;
			pOut->y = 0.0f;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ٵ�λ����άʸ��
	void FKFastcall _3DNOW_Vec2NormalizeFast( Vector2* pOut, const Vector2* pIn, float fLength )
	{
		if( fLength != 0 && ( pIn->x != 0.0f || pIn->y != 0.0f ) )
		{
			__asm
			{
				mov			eax, pIn;
				mov			ebx, pOut;

				movq		mm0, [eax];			//mm0 = ( x, y )

				movd		mm1, fLength;		//mm1 = ( UnitLen, N )
				punpckldq	mm1, mm1;			//mm1 = ( UnitLen, UnitLen )
				pfrcp		mm1, mm1;			//mm1 = ( 1.0f / UnitLen, 1.0f / UnitLen )

				pfmul		mm0, mm1;			//mm0 = ( x / UnitLen, y / UnitLen )

				movq		[ebx], mm0;

				femms;
			}
		}
		else
		{
			pOut->x = 0.0f;
			pOut->y = 0.0f;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}
#include "../../include/CommonBase/MemoryMarco.h"
//==================================================================================================================
