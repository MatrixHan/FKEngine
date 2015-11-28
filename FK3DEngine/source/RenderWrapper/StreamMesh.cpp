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
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderWrapper/RenderWrapperInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	StreamMesh::StreamMesh()
		: mNumSegment		(0)
		, mNumVertex		(0)
		, mNumIndex			(0)
		, mNumIndexPerFrame	(0)
		, mNumKey			(0)
		, mIntervalTime		(0.0f)
		, mpSegmentsIndex	(NULL)
		, mpSegments		(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	StreamMesh::~StreamMesh()
	{
		FreeSegmentBuf();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����崴������
	Geometry* StreamMesh::Creator()
	{
		return new StreamMesh;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������
	void StreamMesh::AllocSegmentBuf()
	{
		mpSegmentsIndex = (UINT*)malloc( sizeof(UINT) * mNumKey );
		mpSegments = (StreamMeshSegment*)malloc( sizeof(StreamMeshSegment) * mNumSegment );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷŶ�����
	void StreamMesh::FreeSegmentBuf()
	{
		SafeFree( mpSegmentsIndex );
		SafeFree( mpSegments );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ����
	void StreamMesh::_RenderObj( const RenderParam* pParam, const Matrix4* pNodeMatrix )
	{
		//�����������
		RenderSystem::mpSingleton->_SetWorldMatrix( pNodeMatrix );

		//������Ⱦ������Ⱦ
		pParam->RenderByParam();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ��������
	void StreamMesh::_RenderAnimObj( const RenderParam* pParam, const AnimControl* pAnimControl, const Matrix4* pNodeMatrix )
	{
		//������Ⱦ����ƫ��λ��
		static RenderParam sParam;
		memcpy( &sParam, pParam, sizeof(RenderParam) );

		StreamMeshSegment* pSegment = mpSegments + mpSegmentsIndex[ pAnimControl->mCurKey ];
		sParam.sBasicParam.nVerOffset = pSegment->nVertexOffset;
		sParam.sBasicParam.nIndexOffset = pAnimControl->mCurKey * mNumIndexPerFrame;
		sParam.sBasicParam.nVerCount = pSegment->nVertexNum;

		//�����������
		RenderSystem::mpSingleton->_SetWorldMatrix( pNodeMatrix );

		//������Ⱦ������Ⱦ
		sParam.RenderByParam();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
