/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	QuadGenerator
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�Ĳ�������������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//�Ĳ�������������
	//
	//     ���Ĳ���������ϡ��Ԫ���Ĳ�������ÿ���Ĳ����ڵ㲢��һ���������е��ĸ��ӽڵ㡣��������ʵ��ֲ����Ǻܾ���ʱ��
	// ϡ��Ԫ���Ĳ������Ժܺõ�����Ĳ����ı���Ч�ʡ����ǣ��������еĿ��ƶ�ʵ��϶�ʱ��ʹ��ϡ��Ԫ���Ĳ�������ܻ���
	// ��ĳЩ��λ��ѡ���ȵĽ��ͣ���ˣ������������ʹ�÷�ϡ��Ԫ���Ĳ������ܻ���á�
	//
	//     ���Ҫ���ɷ�ϡ��Ԫ�ص��Ĳ�������ͨ�����ø��ڵ�ĳߴ���Ĳ����ڵ����������Ĳ����Ĵ��������Ҫ����ϡ��Ԫ
	// �ص��Ĳ���������Ҳ��Ҫ����Ҷ�ڵ�ĳߴ���Ĳ����ڵ���ȣ������ͨ����һ�ֶ�ָ�����ܵ���Ⱦʵ���Χ�ռ����Զ�
	// ���ɺ��ʵ��Ĳ����ڵ㡣����ָ���İ�Χ�ռ䲻С��Ҷ�ڵ���С�ߴ��ǰ���£�����ᾡ���ܵ����ɸ�С����ȸ��ߵ��Ĳ�
	// ��Ҷ�ڵ㡣��
	//
	//--------------------------------------------------------------------------------------------------------------
	class FK_DLL QuadGenerator
	{
	public:
		static const UINT	mMaxDepth = 8;		//�Ĳ���������

	protected:
		float				mRootSize;			//���ڵ�ߴ�
		float				mLeafSize;			//Ҷ�ڵ�ߴ�

		float				mBoundaryMinX;		//��Χ�ռ� X ��Сֵ
		float				mBoundaryMaxX;		//��Χ�ռ� X ���ֵ
		float				mBoundaryMinZ;		//��Χ�ռ� Z ��Сֵ
		float				mBoundaryMaxZ;		//��Χ�ռ� Z ���ֵ

		float				mBoundaryMinY;		//��Χ�ռ� Y ��Сֵ
		float				mBoundaryMaxY;		//��Χ�ռ� Y ���ֵ

		UINT				mNumNode;			//�Ĳ����ڵ�����

		QuadNodeDataStack	mNodeDataStack;		//�Ĳ����ڵ����ݶ�ջ

	public:
		QuadGenerator();
		~QuadGenerator();

		//���ɷ�ϡ��Ԫ���Ĳ�������
		void GenerateThickQuadScene( float fMidX, float fMidZ, float fMinY, float fMaxY, float fLeafSize, UINT nDepth );

		//����ϡ��Ԫ���Ĳ�������
		void GenerateLooseQuadScene( float fMidX, float fMidZ, float fMinY, float fMaxY, float fLeafSize, UINT nDepth );

		//����ָ����Χ�ռ����������ϡ��Ԫ���Ĳ����ڵ�
		UINT GenerateNodeFromBoundary( const AxisBox3& refAxisBox3 );

		//����ָ����Χ�ռ����������ϡ��Ԫ���Ĳ����ڵ�
		UINT GenerateNodeFromBoundary( float fMinX, float fMaxX, float fMinZ, float fMaxZ );

		//�����Ĳ�������
		void DestroyQuadScene();

		//���Ĳ�����������д���ļ�
		void WriteToFile( FileObject* pFile );

	protected:
		//�����Ĳ���������Χ�ռ�
		UINT _SetSceneBoundary( float fMidX, float fMidZ, float fMinY, float fMaxY, float fLeafSize, UINT nDepth );

		//�����Ĳ����ڵ�
		UINT _CreateNode( float fMidX, float fMidZ, float fHalfSize, UINT nDepth );

		//����ָ����Χ�ռ䴴���Ĳ����ڵ�򷵻ض�Ӧ���Ĳ����ڵ�
		UINT _CreateNodeFromBoundary( const QuadBoundary& sBoundary, UINT nNodeIndex );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
