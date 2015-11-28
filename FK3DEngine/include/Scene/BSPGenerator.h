/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BSPGenerator
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	����������������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "../RenderWrapper/ObjectFileFormat.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//����������������
	class FK_DLL BSPGenerator
	{
	protected:
		BSPPlane*		mpPlane3Buf;
		Vector3*		mpVertexBuf;

		UINT			mMaxFace;
		UINT			mMaxVertex;

		UINT			mNumFace;
		UINT			mNumVertex;

		UINT			mNumNode;

	public:
		//���ɶ���������
		void GenerateBSPScene( const Vector3* pVertex, const FaceIndex* pFaceIndex, UINT nNumVertex,
			UINT nNumFace, UINT nMaxVertex, UINT nMaxFace );

	protected:
		//���ɶ�����
		void _GenerateBSPTree( BSPNode* pBSPNode, const BSPPlaneList* pBSPPlaneList );

		//ѡ���ʼ�ָ���
		BSPPlane* _ChooseDivPlane3( const BSPPlaneList* pBSPPlaneList );

		//�жϼ������Ƿ�Ϊ͹�����
		bool _IsConvexSet( const BSPPlaneList* pBSPPlaneList );

		//�ָ�������ָ���
		void _SplitPlane3( BSPPlane* pPlane3, BSPPlane* pDivPlane3,
			BSPPlaneList* pFrontPlane3List, BSPPlaneList* pBackPlane3List );

		//�����¶������ָ���
		void _BuildNewPlane3( WORD pVerIndex[4], int nNumVer, BSPPlaneList* pNewPlane3List );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
