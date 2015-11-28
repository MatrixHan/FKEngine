/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9VertexShader
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
	D3D9VertexShader::D3D9VertexShader()
		: mpD3D9VS		(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	D3D9VertexShader::~D3D9VertexShader()
	{
		ReleaseVertexShader();
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������ɫ��
	void D3D9VertexShader::BuildVertexShader()
	{
		HRESULT result = D3D9RenderSystem::mpD3D9Device->CreateVertexShader( mpShaderCode, &mpD3D9VS );
		if( FAILED( result ) )
		{
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 ������ɫ��ʧ�ܡ�"
			"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ö�����ɫ��
	void D3D9VertexShader::SetVertexShader()
	{
		//������ϴ����õ�ָ����ͬ�������ظ�����
		if( mpLastSetVS == this )
			return;

		//������ɫ��
		HRESULT result = D3D9RenderSystem::mpD3D9Device->SetVertexShader( mpD3D9VS );
		if( FAILED( result ) )
		{
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 ������ɫ��ʧ�ܡ�"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ö�����ɫ������
	void D3D9VertexShader::SetVertexShaderParam()
	{
		HRESULT result;

		//ѭ������������ɫ������
		ShaderParam* pParam = mShaderParams.Begin();
		for( UINT i=0; i<mNumUniformParam; ++i )
		{
			switch ( pParam->eParamType )
			{
			case SPT_FLOAT:
				{
					result = D3D9RenderSystem::mpD3D9Device->SetVertexShaderConstantF(
						pParam->nRegIndex, (float*)pParam->pData, pParam->nNumUnits );
					break;
				}
			case SPT_INT:
				{
					result = D3D9RenderSystem::mpD3D9Device->SetVertexShaderConstantI(
						pParam->nRegIndex, (int*)pParam->pData, pParam->nNumUnits );
					break;
				}
			case SPT_BOOL:
				{
					result = D3D9RenderSystem::mpD3D9Device->SetVertexShaderConstantB(
						pParam->nRegIndex, (BOOL*)pParam->pData, pParam->nNumUnits );
					break;
				}
			default:
				Except( Exception::ERR_INTERNAL_ERROR, "����Ķ�����ɫ���������͡�" );
			}

			if( FAILED( result ) )
			{
				Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 ������ɫ������ʧ�ܡ�"
					"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
			}

			++pParam;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷŶ�����ɫ��
	void D3D9VertexShader::ReleaseVertexShader()
	{
		SafeRelease( mpD3D9VS );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
