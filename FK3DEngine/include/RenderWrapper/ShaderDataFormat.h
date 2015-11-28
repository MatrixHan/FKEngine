/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ShaderDataFormat
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ɫ�����ݸ�ʽ
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	// Cg ��������
	enum CgLanguageType
	{
		Unknown		= 0,		//δ֪����

		DX_VS_11	= 1,		// DirectX VS 1.1 for vertex shader
		DX_VS_20	= 2,		// DirectX VS 2.0 for vertex shader
		DX_VS_2X	= 3,		// DirectX VS 2.0 for extended vertex shader
		DX_PS_11	= 4,		// DirectX PS 1.1 for pixel shader
		DX_PS_12	= 5,		// DirectX PS 1.2 for pixel shader
		DX_PS_13	= 6,		// DirectX PS 1.3 for pixel shader
		DX_PS_20	= 7,		// DirectX PS 2.0 for pixel shader
		DX_PS_2X	= 8,		// DirectX PS 2.0 for extended pixel shader

		OGL_VP_20	= 9,		// vertex program for OpenGL NV_vertex_program 1.0
		OGL_VP_30	= 10,		// vertex program for OpenGL NV_vertex_program 2.0
		OGL_ARB_VP1	= 11,		// vertex program for OpenGL ARB Vertex Program
		OGL_FP_20	= 12,		// fragment program for OpenGL NV_texture_shader and NV_register_combiners
		OGL_FP_30	= 13,		// fragment program for OpenGL NV_fragment_program
		OGL_ARB_FP1	= 14,		// fragment program for OpenGL ARB Fragment Program
	};

	//--------------------------------------------------------------------------------------------------------------

	//�����ļ�ͷ��ʶ
	const char szScgFileHeader[] = "FK Cg Shader File";

	// Cg ��ɫ����Ϣͷ
	struct CgShaderData
	{
		CgLanguageType	eShaderLangType;		//��ɫ����������
		UINT			nNumVaryingParam;		//�ɱ��������
		UINT			nNumUniformParam;		//ͳһ��������
		UINT			nNumConstantParam;		//������������
		DWORD			nShaderCodeLen;			//��ɫ�����볤��
	};

	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
