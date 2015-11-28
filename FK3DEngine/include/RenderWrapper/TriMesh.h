/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	TriMesh
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	������������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//������������
	class FK_DLL TriMesh : public Geometry
	{
	public:
		UINT				mNumBone;			//������ͷ����
		UINT*				mpBoneIndex;		//������ͷ�ڹ����е�����ֵ
		Skeleton*			mpSkeleton;			//��������

	public:
		TriMesh();
		~TriMesh();

		//�����崴������
		static Geometry* Creator();

		//�������� Z �ᷴ�����ƽ��
		void MakePlane3( float fXMin, float fXMax, float fYMin, float fYMax, float fZ,
			bool bHaveUV = false, bool bHaveNormal = false, Material* pMaterial = NULL );

		//��������������
		void MakeBox( const Vector3& vCenter, float fSideLen, UINT nSegment = 1,
			bool bHaveUV = false, bool bHaveNormal = false, Material* pMaterial = NULL );

		//������������
		void MakeSphere( const Vector3& vCenter, float fRadius, UINT nRing = 20, UINT nSegment = 20,
			bool bHaveUV = false, bool bHaveNormal = false, Material* pMaterial = NULL );

		//���ù�����ͷ��������
		void SetBoneIndex( UINT* pBoneIndex, UINT nNumBone );

		//��������
		void SetSkeleton( Skeleton* pSkeleton );

	protected:
		//��Ⱦ����
		void _RenderObj( const RenderParam* pParam, const Matrix4* pNodeMatrix );

		//��Ⱦ��������
		void _RenderAnimObj( const RenderParam* pParam, const AnimControl* pAnimControl, const Matrix4* pNodeMatrix );
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< TriMesh* >		TriMeshList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
