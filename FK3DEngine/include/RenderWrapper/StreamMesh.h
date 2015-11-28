/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	StreamMesh
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
	class FK_DLL StreamMesh : public Geometry
	{
	public:
		UINT				mNumVertex;			//��������
		UINT				mNumIndex;			//��������
		UINT				mNumIndexPerFrame;	//ÿ֡��������

		UINT				mNumKey;			//֡����
		UINT				mNumSegment;		//����

		float				mIntervalTime;		//ÿ֡��ͣ��ʱ��

		UINT*				mpSegmentsIndex;	//ÿ֡����������
		StreamMeshSegment*	mpSegments;			//����Ϣ

	public:
		StreamMesh();
		~StreamMesh();

		//�����崴������
		static Geometry* Creator();

		//���������
		void AllocSegmentBuf();

		//�ͷŶ�����
		void FreeSegmentBuf();

	protected:
		//��Ⱦ����
		void _RenderObj( const RenderParam* pParam, const Matrix4* pNodeMatrix );

		//��Ⱦ��������
		void _RenderAnimObj( const RenderParam* pParam, const AnimControl* pAnimControl, const Matrix4* pNodeMatrix );
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< StreamMesh* >		StreamMeshList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
