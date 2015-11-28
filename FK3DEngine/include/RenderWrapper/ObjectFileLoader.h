/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ObjectFileLoader
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�����ļ�������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "../../include/ParticleSystem/Particle.h"
#include "../../include/ParticleSystem/Emitter.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//�����ļ�������
	class FK_DLL ObjectFileLoader : public Singleton< ObjectFileLoader >
	{
	public:
		FileObject*		mpObjectPack;			//�������ļ�

		MaterialList	mLoadedMaterialList;	//���ز����б�
		TriMeshList		mLoadedTriMeshList;		//���������������б�
		StreamMeshList	mLoadedStreamMeshList;	//���ض����������б�
		SkeletonList	mLoadedSkeletonList;	//���ع����б�
		ParticleList	mLoadedParticleList;	//���������б�
		EmitterList		mLoadedEmitterList;		//�������ӷ������б�
		BoundMeshList	mLoadedBoundMeshList;	//������ײ�ڵ��б�

		DWORD			mFileLength;			//�ļ�����

	public:
		ObjectFileLoader();
		~ObjectFileLoader();

		//�����������ļ�
		void SetObjectPackFile( FileObject* pPackFile );

		//���������ļ�
		void LoadObjectFile( const char* szFileName );

	protected:
		//��ȡ�ļ��α�ʶ
		bool _ReadChunkID( ObjectChunkID& eChunkID );

		//��ȡ�ļ�ͷ��
		void _ReadChunkHeader();

		//��ȡ���ʶ�
		void _ReadChunkMaterial();

		//��ȡ�����������
		void _ReadChunkTriMesh();

		//��ȡ�����������
		void _ReadChunkStreamMesh();

		//��ȡ��Χ�ж�
		void _ReadChunkBoundBox( RenderObject* pRenderObject );

		//��ȡ���������ݶ�
		void _ReadChunkIndexStream( RenderObject* pRenderObject, bool bSoftProc );

		//��ȡ���������ݶ�
		void _ReadChunkVertexStream( RenderObject* pRenderObject, UINT nIndex, bool bSoftProc );

		//����������
		void _ReadChunkVertexElement( RenderObject* pRenderObject );

		//��ȡ�������
		void _ReadChunkSubMesh( RenderObject* pRenderObject, UINT nIndex );

		//��ȡ������
		void _ReadChunkSkeleton();

		//��ȡ������
		void _ReadChunkBillboard();

		//��ȡ��ײ�����
		void _ReadChunkBoundMesh();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
