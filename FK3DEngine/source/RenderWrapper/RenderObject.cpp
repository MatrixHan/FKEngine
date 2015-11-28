/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RenderObject
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
	RenderObject::RenderObject()
		: mNumVertexBuffer		(0)
		, mppVertexBuffer		(NULL)
		, mpIndexBuffer			(NULL)
		, mpVertexDeclaration	(NULL)
		, mppMaterial			(NULL)
		, mNumMaterial			(0)
		, mpRenderParam			(NULL)
		, mNumRenderParam		(0)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	RenderObject::~RenderObject()
	{
		FreeStreamBuf();
		FreeMaterialBuf();
		FreeRenderParamBuf();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���䶥����ָ�뻺��
	void RenderObject::AllocStreamBuf( UINT nNumber )
	{
		SafeFree( mppVertexBuffer );

		mppVertexBuffer = (VertexBuffer**)malloc( sizeof(VertexBuffer*) * nNumber );
		memset( mppVertexBuffer, 0, sizeof(VertexBuffer*) * nNumber );
		mNumVertexBuffer = nNumber;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷŶ�����ָ�뻺��
	void RenderObject::FreeStreamBuf()
	{
		SafeFree( mppVertexBuffer );
		mNumVertexBuffer = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������ָ�뻺��
	void RenderObject::AllocMaterialBuf( UINT nNumber )
	{
		SafeFree( mppMaterial );

		mppMaterial = (Material**)malloc( sizeof(Material*) * nNumber );
		memset( mppMaterial, 0, sizeof(Material*) * nNumber );
		mNumMaterial = nNumber;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷŲ���ָ�뻺��
	void RenderObject::FreeMaterialBuf()
	{
		SafeFree( mppMaterial );
		mNumMaterial = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������в���ʹ�ü���
	void RenderObject::AddMaterialRef()
	{
		for( UINT i=0; i<mNumMaterial; ++i )
		{
			if( mppMaterial[i] != NULL )
				mppMaterial[i]->AddRef();
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������в���ʹ�ü���
	void RenderObject::DelMaterialRef()
	{
		for( UINT i=0; i<mNumMaterial; ++i )
		{
			if( mppMaterial[i] != NULL )
				mppMaterial[i]->DelRef();
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ⱦ��������
	void RenderObject::AllocRenderParamBuf( UINT nNumParam )
	{
		SafeFree( mpRenderParam );

		//����ÿ����������Ϣ����һ����Ⱦ�����ṹ
		mpRenderParam = (RenderParam*)malloc( sizeof(RenderParam) * nNumParam );
		memset( mpRenderParam, 0, sizeof(RenderParam) * nNumParam );
		mNumRenderParam = nNumParam;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷ���Ⱦ��������
	void RenderObject::FreeRenderParamBuf()
	{
		SafeFree( mpRenderParam );
		mNumRenderParam = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
