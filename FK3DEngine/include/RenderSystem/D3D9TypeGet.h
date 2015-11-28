/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9TypeGet
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	D3D9 API �������ͻ�ȡ��
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

#include "../../../Depend/dx9/d3dx9.h"
#include "../../../Depend/dx9/dxerr9.h"
#include "../CommonBase/MemoryMarco.h"

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	// D3D9 API �������ͻ�ȡ��
	class FK_DLL D3D9TypeGet
	{
	public:
		//���ظ�ʽ
		static D3DFORMAT GetPixelFormat( PixelFormat pf );

		//������������
		static D3DFORMAT GetIndexType( IndexType it );

		//������;
		static DWORD GetTextureUsage( TextureUsage tu );

		//��Ӱģʽ
		static D3DSHADEMODE GetShadeMode( ShadeMode sm );

		//�ƹ�����
		static D3DLIGHTTYPE GetLightType( LightType lt );

		//��ģʽ
		static D3DFOGMODE GetFogMode( FogMode fm );

		//���ģʽ
		static D3DFILLMODE GetFillMode( FillMode fm );

		//��ѡģʽ
		static D3DCULL GetCullMode( CullMode cm );

		//�ȽϺ���
		static D3DCMPFUNC GetCompareFun( CompareFunction cf );

		//�������
		static D3DRENDERSTATETYPE GetBlendType( BlendType bt );

		//�����������
		static D3DBLEND GetBlendFactor( BlendFactor bf );

		//��Ϸ�ʽ
		static D3DBLENDOP GetBlendOp( BlendOperation bo );

		//����״̬����
		static D3DTEXTURESTAGESTATETYPE GetTextureState( TextureStateType tst );

		//�����������
		static D3DTEXTUREOP GetTextureOp( TextureOperation to );

		//�����������
		static DWORD GetTextureArg( TextureArgument ta );

		//ȡ������
		static D3DSAMPLERSTATETYPE GetSamplerType( SamplerType st );

		//�����������
		static D3DTEXTUREFILTERTYPE GetTextureFilter( TextureFilterType tft );

		//����Ѱַ����
		static D3DTEXTUREADDRESS GetTextureAddress( TextureAddressType tat );

		//�ڴ��������
		static D3DPOOL GetPoolMode( MemoryPoolMode mpm );

		//ͼԪ��������
		static D3DPRIMITIVETYPE GetPrimitiveType( PrimitiveType pt );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
