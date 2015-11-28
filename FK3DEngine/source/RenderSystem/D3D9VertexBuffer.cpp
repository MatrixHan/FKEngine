/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9VertexBuffer
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderSystem/RenderSystemInsideHeader.h"
#include "../../../Depend/dx9/d3dx9.h"
#include "../../../Depend/dx9/dxerr9.h"
#include "../../include/CommonBase/MemoryMarco.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	D3D9VertexBuffer::D3D9VertexBuffer()
		: mpD3D9VertexBuffer	(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	D3D9VertexBuffer::~D3D9VertexBuffer()
	{
		ReleaseVertexBuffer();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������㻺��
	void D3D9VertexBuffer::CreateVertexBuffer( UINT nVerSize, UINT nVerNum, bool bDynamic, bool bSoftProc )
	{
		//�洢������Ϣ
		mnBufLen = nVerSize * nVerNum;
		mVerSize = nVerSize;
		mbDynamic = bDynamic;

		D3DPOOL D3DPool = D3DPOOL_MANAGED;
		DWORD dwUsage = D3DUSAGE_WRITEONLY;

		//���Ҫ��ʹ�ö�̬����
		if( bDynamic )
		{
			D3DPool = D3DPOOL_DEFAULT;
			dwUsage |= D3DUSAGE_DYNAMIC;
		}

		//���Ҫ��������㴦��
		if( bSoftProc )
		{
			D3DPool = D3DPOOL_MANAGED;
			dwUsage |= D3DUSAGE_SOFTWAREPROCESSING;
		}

		//�������㻺��
		HRESULT result = D3D9RenderSystem::mpD3D9Device->CreateVertexBuffer( mnBufLen, dwUsage, 0, D3DPool,
			&mpD3D9VertexBuffer, NULL );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� Direct3D 9 ���㻺�����"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷŶ��㻺��
	void D3D9VertexBuffer::ReleaseVertexBuffer()
	{
		SafeRelease( mpD3D9VertexBuffer );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������㻺��
	void* D3D9VertexBuffer::Lock( UINT nOffsetVer, UINT nLockVer, bool bNoOverwrite )
	{
		UINT nOffset = nOffsetVer * mVerSize;
		UINT nLockSize = nLockVer * mVerSize;

		//���Ϊ����ģʽ������������
#ifdef _DEBUG
		if( nOffset != 0 && nLockSize == 0 )
		{
			Except( Exception::ERR_INVALIDPARAMS, "�������㻺�泤��Ϊ�㡣�����Ҫ�����������棬�뽫����ƫ����Ҳ��Ϊ�㡣" );
			return NULL;
		}

		if( nOffset + nLockSize > mnBufLen )
		{
			Except( Exception::ERR_INVALIDPARAMS, "���� D3D9 ���㻺�������" );
			return NULL;
		}
#endif

		//��������ģʽ
		DWORD dwFlags = mbDynamic ? D3DLOCK_DISCARD : D3DLOCK_NOSYSLOCK;

		if( bNoOverwrite )
		{
			if( mbDynamic )
				dwFlags = D3DLOCK_NOOVERWRITE;
			else
				dwFlags |= D3DLOCK_NOOVERWRITE;
		}

		//����
		void* pBuffer = NULL;
		HRESULT result = mpD3D9VertexBuffer->Lock( nOffset, nLockSize, &pBuffer, dwFlags );
		if( FAILED( result ) )
		{
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 ���㻺��ʧ�ܡ�"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			return NULL;
		}

		return pBuffer;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������㻺��
	void D3D9VertexBuffer::Unlock()
	{
		HRESULT result = mpD3D9VertexBuffer->Unlock();
		if( FAILED( result ) )
		{
			Except( Exception::ERR_RENDER_API_ERROR, (String)"������� D3D9 ���㻺��ʧ�ܡ�"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
