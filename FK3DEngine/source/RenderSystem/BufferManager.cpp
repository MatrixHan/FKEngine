/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BufferManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderSystem/RenderSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	BufferManager::BufferManager()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	BufferManager::~BufferManager()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ�����������
	void BufferManager::Initialize()
	{
		mVBList.Initialize( 300, 200 );
		mIBList.Initialize( 150, 100 );
		mVDList.Initialize( 150, 100 );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷŻ��������
	void BufferManager::Release()
	{
		DelAllVertexBuffer();
		DelAllIndexBuffer();
		DelAllVertexDeclaration();

		mVBList.Release();
		mIBList.Release();
		mVDList.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����㻺��
	void BufferManager::DelVertexBuffer( VertexBuffer* pVB )
	{
		VertexBufferList::Iterator it = mVBList.Begin();
		VertexBufferList::Iterator end = mVBList.End();
		for(; it!=end; ++it )
		{
			if( *it == pVB )
			{
				mVBList.Erase( it );
				delete pVB;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ����������
	void BufferManager::DelIndexBuffer( IndexBuffer* pIB )
	{
		IndexBufferList::Iterator it = mIBList.Begin();
		IndexBufferList::Iterator end = mIBList.End();
		for(; it!=end; ++it )
		{
			if( *it == pIB )
			{
				mIBList.Erase( it );
				delete pIB;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ����������
	void BufferManager::DelVertexDeclaration( VertexDeclaration* pVD )
	{
		VertexDeclarationList::Iterator it = mVDList.Begin();
		VertexDeclarationList::Iterator end = mVDList.End();
		for(; it!=end; ++it )
		{
			if( *it == pVD )
			{
				mVDList.Erase( it );
				delete pVD;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����ж��㻺��
	void BufferManager::DelAllVertexBuffer()
	{
		UINT NumVB = mVBList.Size();
		VertexBuffer** ppVB = mVBList.Begin();
		for( UINT i=0; i<NumVB; ++i )
		{
			SafeDelete( *ppVB++ );
		}

		mVBList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��������������
	void BufferManager::DelAllIndexBuffer()
	{
		UINT NumIB = mIBList.Size();
		IndexBuffer** ppIB = mIBList.Begin();
		for( UINT i=0; i<NumIB; ++i )
		{
			SafeDelete( *ppIB++ );
		}

		mIBList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����ж�������
	void BufferManager::DelAllVertexDeclaration()
	{
		UINT NumVD = mVDList.Size();
		VertexDeclaration** ppVD = mVDList.Begin();
		for( UINT i=0; i<NumVD; ++i )
		{
			SafeDelete( *ppVD++ );
		}

		mVDList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ���㻺������
	UINT BufferManager::GetNumVertexBuffer()
	{
		return mVBList.Size();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ������������
	UINT BufferManager::GetNumIndexBuffer()
	{
		return mIBList.Size();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ������������
	UINT BufferManager::GetNumVertexDeclaration()
	{
		return mVDList.Size();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
