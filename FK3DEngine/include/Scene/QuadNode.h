/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	QuadNode
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�Ĳ����ڵ���
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//�Ĳ����ڵ���
	class FK_DLL QuadNode
	{
	public:
		friend class QuadSceneNode;
		friend class QuadSceneManager;

	public:
		float				mfMinX;			//��Χ�ռ� X ��Сֵ
		float				mfMaxX;			//��Χ�ռ� X ���ֵ
		float				mfMinZ;			//��Χ�ռ� Z ��Сֵ
		float				mfMaxZ;			//��Χ�ռ� Z ���ֵ

		float				mfHalfSize;		//��Χ�ռ��ߴ�

		QuadNode*			mppChild[2][2];	//�ӽڵ�

		QuadSceneNodeList	mSceneNodeList;	//�ҽ��Ĳ��������ڵ��б�

	public:
		QuadNode();
		~QuadNode();

	protected:
		//�����Ĳ����ڵ�
		void FKFastcall _SetQuadNode( const QuadNodeData* pQuadNodeData, QuadNode* pQuadNode );

		//�ҽ�ָ���Ĳ��������ڵ�
		void FKFastcall _AttachQuadSceneNode( QuadSceneNode* pQuadSceneNode );

		//�Ͽ�ָ�����Ĳ��������ڵ�
		void FKFastcall _DetachQuadSceneNode( QuadSceneNode* pQuadSceneNode );

		//�Ͽ����е��Ĳ��������ڵ�
		void FKFastcall _DetachAllQuadSceneNode();

		//�ж�ָ���İ�Χ���Ƿ��ڽڵ�İ�Χ�ռ���
		bool FKFastcall _IsInside( const AxisBox3& refBox3 );

		//��ȡ��ָ����Χ�ռ�������Ĳ����ڵ�
		QuadNode* _GetQuadNodeFromBoundary( const QuadBoundary& sBoundary );

		//��ȡ�ýڵ㼰���ӽڵ��µĿɼ���Ⱦʵ��
		void _GetVisableInstance( Camera* pActiveCam, RenderQueue* pRenderQueue, Vector3 pBoundaryVer[8] );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
