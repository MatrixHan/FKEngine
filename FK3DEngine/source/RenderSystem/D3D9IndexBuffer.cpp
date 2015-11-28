/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9IndexBuffer
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
	D3D9IndexBuffer::D3D9IndexBuffer()
		: mpD3D9IndexBuffer	(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	D3D9IndexBuffer::~D3D9IndexBuffer()
	{
		ReleaseIndexBuffer();
	}
	//--------------------------------------------------------------------------------------------------------------
	//������������
	void D3D9IndexBuffer::CreateIndexBuffer( UINT nIndexNum, IndexType eIndexType, bool bDynamic, bool bSoftProc )
	{
		//�洢������Ϣ
		mIndexType = eIndexType;
		mbDynamic = bDynamic;

		//�ж���������
		switch (eIndexType)
		{
		case IT_INDEX16:
			{
				mIndexSize = sizeof(WORD);
				mnBufLen = mIndexSize * nIndexNum;
				break;
			}
		case IT_INDEX32:
			{
				mIndexSize = sizeof(DWORD);
				mnBufLen = mIndexSize * nIndexNum;
				break;
			}
		default:
			Except( Exception::ERR_INVALIDPARAMS, "����������������͡�" );
		}

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

		//���Ϊ������㴦����
		if( D3D9RenderSystem::mD3DBehavior == D3DCREATE_SOFTWARE_VERTEXPROCESSING )
			dwUsage |= D3DUSAGE_SOFTWAREPROCESSING;

		//������������
		HRESULT result = D3D9RenderSystem::mpD3D9Device->CreateIndexBuffer( mnBufLen, dwUsage,
			D3D9TypeGet::GetIndexType( eIndexType ), D3DPool, &mpD3D9IndexBuffer, NULL );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� Direct3D 9 �����������"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷ���������
	void D3D9IndexBuffer::ReleaseIndexBuffer()
	{
		SafeRelease( mpD3D9IndexBuffer );
	}
	//--------------------------------------------------------------------------------------------------------------
	//������������
	void* D3D9IndexBuffer::Lock( UINT nOffsetNum, UINT nLockNum, bool bNoOverwrite )
	{
		UINT nOffset = nOffsetNum * mIndexSize;
		UINT nLockSize = nLockNum * mIndexSize;

		//���Ϊ����ģʽ������������
#ifdef _DEBUG
		if( nOffset != 0 && nLockSize == 0 )
		{
			Except( Exception::ERR_INVALIDPARAMS, "�����������泤��Ϊ�㡣�����Ҫ�����������棬�뽫����ƫ����Ҳ��Ϊ�㡣" );
			return NULL;
		}

		if( nOffset + nLockSize > mnBufLen )
		{
			Except( Exception::ERR_INVALIDPARAMS, "���� D3D9 �������������" );
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
		HRESULT result = mpD3D9IndexBuffer->Lock( nOffset, nLockSize, &pBuffer, dwFlags );
		if( FAILED( result ) )
		{
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 ��������ʧ�ܡ�"
				+ DXGetErrorDescription9( result ) );
			return NULL;
		}

		return pBuffer;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������������
	void D3D9IndexBuffer::Unlock()
	{
		HRESULT result = mpD3D9IndexBuffer->Unlock();
		if( FAILED( result ) )
		{
			Except( Exception::ERR_RENDER_API_ERROR, (String)"������� D3D9 ��������ʧ�ܡ�"
				+ DXGetErrorDescription9( result ) );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
