/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9VertexDeclaration
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
	D3D9VertexDeclaration::D3D9VertexDeclaration()
		: mpD3D9VertexDeclaration		(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	D3D9VertexDeclaration::~D3D9VertexDeclaration()
	{
		ReleaseVertexDeclaration();
	}
	//--------------------------------------------------------------------------------------------------------------
	//������������
	void D3D9VertexDeclaration::CreateVertexDeclaration()
	{
		static D3DVERTEXELEMENT9 D3DElement[nMaxElementNum];
		D3DVERTEXELEMENT9* pD3DElement = D3DElement;

		if( mNumElement > nMaxElementNum )
			Except( Exception::ERR_INVALIDPARAMS, "���������������Ķ���Ԫ���������������ֵ��" );

		//������Ԫ�ظ��Ƶ� D3D9 ����Ԫ�ؽṹ��
		VertexElement* pElement = mVertexElements.Begin();
		for( UINT i=0; i<mNumElement; ++i )
		{
			pD3DElement->Stream		= pElement->nStream;
			pD3DElement->Offset		= pElement->nOffset;
			pD3DElement->Type		= (BYTE)pElement->Type;
			pD3DElement->Method		= (BYTE)pElement->Method;
			pD3DElement->Usage		= (BYTE)pElement->Usage;
			pD3DElement->UsageIndex	= pElement->UsageIndex;

			++pD3DElement;
			++pElement;
		}

		//���ý�β����Ԫ��
		pD3DElement->Stream		= 0xFF;
		pD3DElement->Offset		= 0;
		pD3DElement->Type		= D3DDECLTYPE_UNUSED;
		pD3DElement->Method		= 0;
		pD3DElement->Usage		= 0;
		pD3DElement->UsageIndex	= 0;

		HRESULT result = D3D9RenderSystem::mpD3D9Device->CreateVertexDeclaration( D3DElement,
			&mpD3D9VertexDeclaration );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 ������������ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ����������
	void D3D9VertexDeclaration::ReleaseVertexDeclaration()
	{
		SafeRelease( mpD3D9VertexDeclaration );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
