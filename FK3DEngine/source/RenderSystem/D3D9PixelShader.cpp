/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9PixelShader
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
	D3D9PixelShader::D3D9PixelShader()
		: mpD3D9PS		(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	D3D9PixelShader::~D3D9PixelShader()
	{
		ReleasePixelShader();
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������ɫ��
	void D3D9PixelShader::BuildPixelShader()
	{
		//������ϴ����õ�ָ����ͬ�������ظ�����
		if( mpLastSetPS == this )
			return;

		HRESULT result = D3D9RenderSystem::mpD3D9Device->CreatePixelShader( mpShaderCode, &mpD3D9PS );
		if( FAILED( result ) )
		{
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 ������ɫ��ʧ�ܡ�"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������ɫ��
	void D3D9PixelShader::SetPixelShader()
	{
		HRESULT result = D3D9RenderSystem::mpD3D9Device->SetPixelShader( mpD3D9PS );
		if( FAILED( result ) )
		{
			Except( Exception::ERR_RENDER_API_ERROR, (String)"���� D3D9 ������ɫ��ʧ�ܡ�"
				"\nD3D9 ����������" + DXGetErrorDescription9( result ) );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������ɫ������
	void D3D9PixelShader::SetPixelShaderParam()
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
					result = D3D9RenderSystem::mpD3D9Device->SetPixelShaderConstantF(
						pParam->nRegIndex, (float*)pParam->pData, pParam->nNumUnits );
					break;
				}
			case SPT_INT:
				{
					result = D3D9RenderSystem::mpD3D9Device->SetPixelShaderConstantI(
						pParam->nRegIndex, (int*)pParam->pData, pParam->nNumUnits );
					break;
				}
			case SPT_BOOL:
				{
					result = D3D9RenderSystem::mpD3D9Device->SetPixelShaderConstantB(
						pParam->nRegIndex, (BOOL*)pParam->pData, pParam->nNumUnits );
					break;
				}
			default:
				Except( Exception::ERR_INTERNAL_ERROR, "�����������ɫ���������͡�" );
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
	//�ͷ�������ɫ��
	void D3D9PixelShader::ReleasePixelShader()
	{
		SafeRelease( mpD3D9PS );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
