/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9TypeConvert
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	D3D9 API ��������ת����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	// D3D9 API ��������ת����
	class FK_DLL D3D9TypeConvert
	{
	public:
		//���ظ�ʽ
		static PixelFormat GetPixelFormat( DWORD fmt );

		//������������
		static IndexType GetIndexType( DWORD it );

		//������;
		static TextureUsage GetTextureUsage( DWORD tu );

		//��Ӱģʽ
		static ShadeMode GetShadeMode( DWORD sm );

		//�ƹ�����
		static LightType GetLightType( DWORD lt );

		//��ģʽ
		static FogMode GetFogMode( DWORD fm );

		//���ģʽ
		static FillMode GetFillMode( DWORD fm );

		//��ѡģʽ
		static CullMode GetCullMode( DWORD cm );

		//�ȽϺ���
		static CompareFunction GetCompareFun( DWORD cf );

		//�������
		static BlendType GetBlendType( DWORD bt );

		//�����������
		static BlendFactor GetBlendFactor( DWORD bf );

		//��Ϸ�ʽ
		static BlendOperation GetBlendOp( DWORD bo );

		//����״̬����
		static TextureStateType GetTextureState( DWORD tst );

		//�����������
		static TextureOperation GetTextureOp( DWORD to );

		//�����������
		static TextureArgument GetTextureArg( DWORD ta );

		//ȡ������
		static SamplerType GetSamplerType( DWORD st );

		//�����������
		static TextureFilterType GetTextureFilter( DWORD tft );

		//����Ѱַ����
		static TextureAddressType GetTextureAddress( DWORD tat );

		//�ڴ��������
		static MemoryPoolMode GetPoolMode( DWORD mpm );

		//ͼԪ��������
		static PrimitiveType GetPrimitiveType( DWORD pt );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
