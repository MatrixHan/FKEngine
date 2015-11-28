/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9BaseTexture
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
	D3D9BaseTexture::D3D9BaseTexture()
		: mpBaseTexture		(NULL)
		, mpD3D9Texture		(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	D3D9BaseTexture::~D3D9BaseTexture()
	{
		SafeRelease( mpD3D9Texture );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Զ����ɶ༶����ӳ��
	void D3D9BaseTexture::_GenerateMipSubLevels( TextureFilterType eFilterType )
	{
		HRESULT result = mpD3D9Texture->SetAutoGenFilterType( D3D9TypeGet::GetTextureFilter( eFilterType ) );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"Direct3D 9 �Զ����ɶ༶����ӳ�����"
			"\n���ɼ���" + mpBaseTexture->mNumLevel + "\nD3D9 ����������" + DXGetErrorDescription9(result) );

		mpD3D9Texture->GenerateMipSubLevels();
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������;��ȡ�����ڴ����ʽ�� D3D ������;��ʶ
	DWORD D3D9BaseTexture::_GetPoolModeAndUsage()
	{
		//��ȡ�����ڴ����ʽ
		switch (mpBaseTexture->mType)
		{
		case TU_NORMAL:
			mpBaseTexture->mPoolMode = MPM_AGPMEM;
			break;
		case TU_DYNAMIC:
		case TU_TARGET:
			mpBaseTexture->mPoolMode = MPM_VIDEOMEM;
			break;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "����� Direct3D 9 ���������͡�" );
		}

		//�����������������Ҫ���Զ����� Mipmap
		DWORD dwUsage = D3D9TypeGet::GetTextureUsage( mpBaseTexture->mType );
		if( mpBaseTexture->mNumLevel == 0 )
			dwUsage |= D3DUSAGE_AUTOGENMIPMAP;

		return dwUsage;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
