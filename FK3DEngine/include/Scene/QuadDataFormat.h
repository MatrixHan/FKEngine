/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	QuadDataFormat
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�Ĳ������ݽṹ
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	//ָ����Χ�ռ�����
	struct QuadBoundary
	{
		float fMinX;
		float fMaxX;
		float fMinZ;
		float fMaxZ;
		float fSize;
	};

	//�Ĳ����ڵ�����
	struct QuadNodeData
	{
		float		fMinX;				//��Χ�ռ� X ��Сֵ
		float		fMaxX;				//��Χ�ռ� X ���ֵ
		float		fMinZ;				//��Χ�ռ� Z ��Сֵ
		float		fMaxZ;				//��Χ�ռ� Z ���ֵ
		float		fHalfSize;			//��Χ�ռ��ߴ�

		UINT		ppChildIndex[2][2];	//�ӽڵ�����
	};
	typedef Stack< QuadNodeData >	QuadNodeDataStack;

	//�Ĳ�������
	struct QuadtreeData
	{
		float		fRootSize;			//���ڵ�ߴ�
		float		fLeafSize;			//Ҷ�ڵ�ߴ�

		float		fBoundaryMinX;		//��Χ�ռ� X ��Сֵ
		float		fBoundaryMaxX;		//��Χ�ռ� X ���ֵ
		float		fBoundaryMinZ;		//��Χ�ռ� Z ��Сֵ
		float		fBoundaryMaxZ;		//��Χ�ռ� Z ���ֵ

		float		fBoundaryMinY;		//��Χ�ռ� Y ��Сֵ
		float		fBoundaryMaxY;		//��Χ�ռ� Y ���ֵ

		UINT		nNumNode;			//�Ĳ����ڵ�����
	};

	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
