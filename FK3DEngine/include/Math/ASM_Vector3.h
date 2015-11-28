/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ASM_Vector3
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ѧ�� ��άʸ�� �����㺯��
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	// 3DNOW ���㺯��
	//--------------------------------------------------------------------------------------------------------------

	extern void FKFastcall _3DNOW_Vec3Div( Vector3* pOut, const Vector3* pArg1, const Vector3* pArg2 );		//��άʸ�����
	extern void FKFastcall _3DNOW_Vec3DivScalar( Vector3* pOut, const Vector3* pOrg, const float fScalar );	//��άʸ�����Ա���

	extern float FKFastcall _3DNOW_Vec3UnitLength( const Vector3* pIn );									//��άʸ����λ����
	extern void FKFastcall _3DNOW_Vec3Normalize( Vector3* pOut, const Vector3* pIn );						//��λ����άʸ��
	extern void FKFastcall _3DNOW_Vec3NormalizeFast( Vector3* pOut, const Vector3* pIn, float fLength );	//���ٵ�λ����άʸ��

	//--------------------------------------------------------------------------------------------------------------
}
//==================================================================================================================