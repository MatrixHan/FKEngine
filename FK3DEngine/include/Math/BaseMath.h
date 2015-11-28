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
*	�ļ�˵����	��ѧ��������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	// ��ѧ���ú궨��
	//--------------------------------------------------------------------------------------------------------------

	//Բ���ʶ���
	#define FK_PI		3.14159265358979323846f
	#define FK_TWO_PI	6.28318530717958647692f
	#define FK_HALF_PI	1.57079632679489661923f

	//�����ֵ����
	#define FK_EPSILON	0.0001f

	//���Ƕ�ת��Ϊ�¶�
	#define FK_DegreeToRadian( Degree ) ( (Degree) * ( FK_PI / 180.0f ) )

	//���¶�ת��Ϊ�Ƕ�
	#define FK_RadianToDegree( Radian ) ( (Radian) * ( 180.0f / FK_PI ) )

	#define SINCOS_TABLE_SIZE	256		//���Ǻ������С

	//--------------------------------------------------------------------------------------------------------------

	//��ռ��ϵ
	enum AxisSpaceRelation
	{
		ASR_Less		= 0,		//����ֵ����
		ASR_More		= 1,		//����ֵ��С
		ASR_Overlap		= 2,		//�ص�
		ASR_Invalid		= 0xFF,		//������
	};

	//ƽ�����Ŀռ佻���ϵ
	enum SpaceRelation
	{
		SR_POSITIVE,	//��ƽ������
		SR_NEGATIVE,	//��ƽ�汳��
		SR_COINCIDING,	//��ƽ��һ��
		SR_SPANNING,	//��ƽ�����
	};

	//--------------------------------------------------------------------------------------------------------------
	// ��ѧ��Ԥ����
	//--------------------------------------------------------------------------------------------------------------

	class Vector3;
	class Quaternion;
	class Matrix3;
	class Matrix4;
	class BoundBox;

	//--------------------------------------------------------------------------------------------------------------
	// ������ѧ���㺯��ָ��
	//--------------------------------------------------------------------------------------------------------------

	extern float	( FKFastcall *Sin )		( float radian );							//��������
	extern float	( FKFastcall *Cos )		( float radian );							//��������
	extern void		( FKFastcall *SinCos )	( float radian, float* pSin, float* pCos );	//�������Һ�����
	extern float	( FKFastcall *ASin )	( float sin );								//�������Ҽ������
	extern float	( FKFastcall *ACos )	( float cos );								//�������Ҽ������
	extern float	( FKFastcall *Tan )		( float radian );							//��������
	extern float	( FKFastcall *Cot )		( float radian );							//��������
	extern float	( FKFastcall *ATan )	( float x, float y );						//�������м������
	extern float	( FKFastcall *Abs )		( float val );								//�����ֵ
	extern float	( FKFastcall *Sqrt )	( float val );								//����ƽ����
	extern float	( FKFastcall *RSqrt )	( float val );								//����ƽ�����ĵ���

	//����Ƿ�Ϊ 2 �����޷�������
	extern FKForceInline bool IsPow2( UINT value );

	//���޷�������ת��Ϊ��ӽ�������С�� 2 �����޷�������
	extern FKForceInline UINT FloorToPow2( UINT value );

	//���޷�������ת��Ϊ��ӽ���������� 2 �����޷�������
	extern FKForceInline UINT CeilToPow2( UINT value );

	//�з�����������
	extern FKForceInline void Div( const int value, const int divisor,
		int& quotient, int& remainder );

	//�޷�����������
	extern FKForceInline void Div( const unsigned int value, const unsigned int divisor,
		unsigned int& quotient, unsigned int& remainder );

	//��������ת��Ϊ��ӽ�������С������
	extern FKForceInline int FloorToInt( float value );

	//��������ת��Ϊ��ӽ��������������
	extern FKForceInline int CeilToInt( float value );

	//--------------------------------------------------------------------------------------------------------------
	// Ĭ����ѧ���㺯��
	//--------------------------------------------------------------------------------------------------------------

	extern float	FKFastcall _Def_Sin( float radian );								//��������
	extern float	FKFastcall _Def_Cos( float radian );								//��������
	extern void		FKFastcall _Def_SinCos( float radian, float* pSin, float* pCos );	//�������Һ�����
	extern float	FKFastcall _Def_ASin( float sin );									//�������Ҽ������
	extern float	FKFastcall _Def_ACos( float cos );									//�������Ҽ������
	extern float	FKFastcall _Def_Tan( float radian );								//��������
	extern float	FKFastcall _Def_Cot( float radian );								//��������
	extern float	FKFastcall _Def_ATan( float x, float y );							//�������м������
	extern float	FKFastcall _Def_Abs( float val );									//�����ֵ
	extern float	FKFastcall _Def_Sqrt( float val );									//����ƽ����
	extern float	FKFastcall _Def_RSqrt( float val );									//����ƽ�����ĵ���

	//--------------------------------------------------------------------------------------------------------------

	//��ʼ����ѧ��
	extern bool InitializeMathLibrary( const CPUInfo* pCPUInfo );

	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
