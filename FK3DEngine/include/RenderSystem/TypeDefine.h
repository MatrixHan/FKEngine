/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	TypeDefine
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//������
	struct Box3
	{
		UINT	nLeft;
		UINT	nTop;
		UINT	nRight;
		UINT	nBottom;
		UINT	nFront;
		UINT	nBack;
	};
	//--------------------------------------------------------------------------------------------------------------
	//����������
	struct LockBox3
	{
		int		nRowPitch;
		int		nSlicePitch;
		void*	pBits;
	};
	//--------------------------------------------------------------------------------------------------------------
	//������������
	enum CubeFace
	{
		CF_POSITIVE_X		= 0,
		CF_NEGATIVE_X		= 1,
		CF_POSITIVE_Y		= 2,
		CF_NEGATIVE_Y		= 3,
		CF_POSITIVE_Z		= 4,
		CF_NEGATIVE_Z		= 5,
	};
	//--------------------------------------------------------------------------------------------------------------
	//�ƹ�����
	enum LightType
	{
		LT_POINT,			//���
		LT_SPOT,			//�۹��
		LT_DIRECTIONAL,		//ֱ���
	};
	//--------------------------------------------------------------------------------------------------------------
	//������ɫ��Դ
	struct MaterialSource
	{
		//��Դ����
		enum SourceType
		{
			MST_Material		= 0,
			MST_VertexDiffuse	= 1,
			MST_VertexSpecular	= 2,
		};

		SourceType	DiffuseSource;	//����ɫ��Դ
		SourceType	SpecularSource;	//�߹�ɫ��Դ
		SourceType	AmbientSource;	//����ɫ��Դ
		SourceType	EmissiveSource;	//����ɫ��Դ
	};
	//--------------------------------------------------------------------------------------------------------------
	//������������
	enum IndexType
	{
		IT_UNKNOWN	= 0,
		IT_INDEX16	= 2,
		IT_INDEX32	= 4,
	};
	//--------------------------------------------------------------------------------------------------------------
	//��������
	enum TextureUsage
	{
		TU_UNKNOWN	= 0x0,
		TU_NORMAL	= 0x1,
		TU_DYNAMIC	= 0x2,
		TU_TARGET	= 0x4,
	};
	//--------------------------------------------------------------------------------------------------------------
	//��ģʽ
	enum FogMode
	{
		FOG_NONE	= 0,	//����
		FOG_EXP		= 1,	//ָ����
		FOG_EXP2	= 2,	//���η�ָ����
		FOG_LINEAR	= 3,	//������
	};
	//--------------------------------------------------------------------------------------------------------------
	//���ģʽ
	enum FillMode
	{
		FM_POINT		= 1,
		FM_WIREFRAME	= 2,
		FM_SOLID		= 3,
	};
	//--------------------------------------------------------------------------------------------------------------
	//��Ӱģʽ
	enum ShadeMode
	{
		SM_FLAT		= 1,
		SM_GOURAUD	= 2,
		SM_PHONG	= 3,
	};
	//--------------------------------------------------------------------------------------------------------------
	//�ȽϺ���
	enum CompareFunction
	{
		CMP_NEVER,			//����ʧ��
		CMP_LESS,			//С��ʱͨ��
		CMP_EQUAL,			//����ʱͨ��
		CMP_LESSEQUAL,		//С�ڵ���ʱͨ��
		CMP_GREATER,		//����ʱͨ��
		CMP_NOTEQUAL,		//������ʱͨ��
		CMP_GREATEREQUAL,	//���ڵ���ʱͨ��
		CMP_ALWAYS,			//����ͨ��
	};
	//--------------------------------------------------------------------------------------------------------------
	//��ϲ�������
	enum BlendType
	{
		BT_SRCBLEND,		//��Դ��ɫ�������
		BT_DESTBLEND,		//Ŀ����ɫ�������
		BT_SRCBLENDALPHA,	//��Դ ALPHA ֵ������ͣ�Ҫ�����ֿ���� ALPHA ֵѡ�
		BT_DESTBLENDALPHA,	//Ŀ�� ALPHA ֵ������ͣ�Ҫ�����ֿ���� ALPHA ֵѡ�
	};
	//--------------------------------------------------------------------------------------------------------------
	//��ϲ�������
	enum BlendFactor
	{
		BF_ZERO,
		BF_ONE,
		BF_SRCCOLOR,
		BF_INVSRCCOLOR,
		BF_DESTCOLOR,
		BF_INVDESTCOLOR,
		BF_SRCALPHA,
		BF_INVSRCALPHA,
		BF_DESTALPHA,
		BF_INVDESTALPHA,
		BF_SRCALPHASAT,
		BF_BOTHSRCALPHA,
		BF_BOTHINVSRCALPHA,
		BF_BLENDFACTOR,
		BF_INVBLENDFACTOR,
	};
	//--------------------------------------------------------------------------------------------------------------
	//��ϲ�����ʽ
	enum BlendOperation
	{
		BO_ADD,
		BO_SUBTRACT,
		BO_REVSUBTRACT,
		BO_MIN,
		BO_MAX,
	};
	//--------------------------------------------------------------------------------------------------------------
	//��ѡģʽ
	enum CullMode
	{
		CM_NOCULL,			//����ѡ
		CM_CLOCKWISE,		//˳ʱ�뷽���ѡ
		CM_ANTICLOCKWISE,	//��ʱ�뷽���ѡ
	};
	//--------------------------------------------------------------------------------------------------------------
	//����״̬����
	enum TextureStateType
	{
		TST_COLOROP,
		TST_COLORARG1,
		TST_COLORARG2,
		TST_ALPHAOP,
		TST_ALPHAARG1,
		TST_ALPHAARG2,
		TST_BUMPENVMAT00,
		TST_BUMPENVMAT01,
		TST_BUMPENVMAT10,
		TST_BUMPENVMAT11,
		TST_COLORARG0,
		TST_ALPHAARG0,
	};
	//--------------------------------------------------------------------------------------------------------------
	//�����������
	enum TextureOperation
	{
		TO_DISABLE,
		TO_SELECTARG1,
		TO_SELECTARG2,
		TO_MODULATE,
		TO_ADD,
		TO_SUBTRACT,
		TO_BUMPENVMAP,
		TO_BUMPENVMAPLUMINANCE,
	};
	//--------------------------------------------------------------------------------------------------------------
	//�����������
	enum TextureArgument
	{
		TA_CURRENT,
		TA_DIFFUSE,
		TA_SELECTMASK,
		TA_SPECULAR,
		TA_TEMP,
		TA_TEXTURE,
		TA_TFACTOR,
	};
	//--------------------------------------------------------------------------------------------------------------
	//ȡ������
	enum SamplerType
	{
		ST_ADDRESSU			= 0x1,
		ST_ADDRESSV			= 0x2,
		ST_ADDRESSW			= 0x4,
		ST_MAGFILTER		= 0x10,
		ST_MINFILTER		= 0x20,
		ST_MIPFILTER		= 0x40,
	};
	//--------------------------------------------------------------------------------------------------------------
	//�����������
	enum TextureFilterType
	{
		TFT_NONE,
		TFT_POINT,
		TFT_LINEAR,
		TFT_ANISOTROPIC,
	};
	//--------------------------------------------------------------------------------------------------------------
	//����Ѱַ����
	enum TextureAddressType
	{
		TAT_UNKNOWN		= 0,
		TAT_WRAP		= 1,
		TAT_MIRROR		= 2,
		TAT_CLAMP		= 3,
		TAT_BORDER		= 4,
		TAT_MIRRORONCE	= 5,
	};
	//--------------------------------------------------------------------------------------------------------------
	//�ڴ����ʽ
	enum MemoryPoolMode
	{
		MPM_UNKNOWN		= 0,		//δ֪�ڴ�ģʽ
		MPM_VIDEOMEM	= 1,		//��ʾ�ڴ�
		MPM_SYSTEMMEM	= 2,		//ϵͳ�ڴ�
		MPM_AGPMEM		= 3,		//AGP �ڴ����ʾ�ڴ�
	};
	//--------------------------------------------------------------------------------------------------------------
	//ͼԪ��������
	enum PrimitiveType
	{
		PT_POINT_LIST		= 1,
		PT_LINE_LIST		= 2,
		PT_LINE_STRIP		= 3,
		PT_TRIANGLE_LIST	= 4,
		PT_TRIANGLE_STRIP	= 5,
		PT_TRIANGLE_FAN		= 6,
	};
	//--------------------------------------------------------------------------------------------------------------
	//������������
	enum VertexElementType
	{
		VET_FLOAT1		= 0,	// 0	D3DDECLTYPE_FLOAT1
		VET_FLOAT2,				// 1	D3DDECLTYPE_FLOAT2
		VET_FLOAT3,				// 2	D3DDECLTYPE_FLOAT3
		VET_FLOAT4,				// 3	D3DDECLTYPE_FLOAT4
		VET_ARGBCOLOR,			// 4	D3DDECLTYPE_D3DCOLOR
		VET_UBYTE4,				// 5	D3DDECLTYPE_UBYTE4
		VET_SHORT2,				// 6	D3DDECLTYPE_SHORT2
		VET_SHORT4,				// 7	D3DDECLTYPE_SHORT4
		VET_UBYTE4N,			// 8	D3DDECLTYPE_UBYTE4N
		VET_SHORT2N,			// 9	D3DDECLTYPE_SHORT2N
		VET_SHORT4N,			// 10	D3DDECLTYPE_SHORT4N
		VET_USHORT2N,			// 11	D3DDECLTYPE_USHORT2N
		VET_USHORT4N,			// 12	D3DDECLTYPE_USHORT4N
		VET_UDEC3,				// 13	D3DDECLTYPE_UDEC3
		VET_DEC3N,				// 14	D3DDECLTYPE_DEC3N
		VET_FLOAT16_2,			// 15	D3DDECLTYPE_FLOAT16_2
		VET_FLOAT16_4,			// 16	D3DDECLTYPE_FLOAT16_4
		VET_UNUSED,				// 17	D3DDECLTYPE_UNUSED
	};
	//--------------------------------------------------------------------------------------------------------------
	enum VertexElementMethod
	{
		VEM_DEFAULT		= 0,	// 0	D3DDECLMETHOD_DEFAULT
		VEM_PARTIALU,			// 1	D3DDECLMETHOD_PARTIALU
		VEM_PARTIALV,			// 2	D3DDECLMETHOD_PARTIALV
		VEM_CROSSUV,			// 3	D3DDECLMETHOD_CROSSUV
		VEM_UV,					// 4	D3DDECLMETHOD_UV
		VEM_LOOKUP,				// 5	D3DDECLMETHOD_LOOKUP
		VEM_LOOKUPPRESAMPLED,	// 6	D3DDECLMETHOD_LOOKUPPRESAMPLED
	};
	//--------------------------------------------------------------------------------------------------------------
	//����������;
	enum VertexElementUsage
	{
		VEU_POSITION		= 0,// 0	D3DDECLUSAGE_POSITION
		VEU_BLENDWEIGHT,		// 1	D3DDECLUSAGE_BLENDWEIGHT
		VEU_BLENDINDICES,		// 2	D3DDECLUSAGE_BLENDINDICES
		VEU_NORMAL,				// 3	D3DDECLUSAGE_NORMAL
		VEU_PSIZE,				// 4	D3DDECLUSAGE_PSIZE
		VEU_TEXCOORD,			// 5	D3DDECLUSAGE_TEXCOORD
		VEU_TANGENT,			// 6	D3DDECLUSAGE_TANGENT
		VEU_BINORMAL,			// 7	D3DDECLUSAGE_BINORMAL
		VEU_TESSFACTOR,			// 8	D3DDECLUSAGE_TESSFACTOR
		VEU_POSITIONT,			// 9	D3DDECLUSAGE_POSITIONT
		VEU_COLOR,				// 10	D3DDECLUSAGE_COLOR
		VEU_FOG,				// 11	D3DDECLUSAGE_FOG
		VEU_DEPTH,				// 12	D3DDECLUSAGE_DEPTH
		VEU_SAMPLE,				// 13	D3DDECLUSAGE_SAMPLE
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
