/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ObjectFileFormat
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�����ļ���ʽ
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

#include "../RenderSystem/TypeDefine.h"
#include "../RenderSystem/VertexDeclaration.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	const char FK_OBJ_FILE_HEADER[]					= "FK Object File";		//�ļ�ͷ�ַ���
	const char FK_OBJ_FILE_VERSION_STR[]			= "1.3.02";				//�ļ��汾���ַ���
	const UINT FK_OBJ_FILE_VERSION					= 1302;					//�ļ��汾��
	const UINT FK_OBJ_FILE_MIN_COMPATIBLE_VERSION	= 1302;					//��ͼ��ݰ汾��

	//--------------------------------------------------------------------------------------------------------------

	//�����ļ��α�ʶ
	enum ObjectChunkID
	{
		//�������ļ���
		FK_CID_Invaild				= 0x0000,

		//������
		FK_CID_End					= 0x0001,

		//�ļ�ͷ��
		FK_CID_Header				= 0x1000,
			// char*			�ļ�ͷ�ַ���	ӦΪ FK_OBJ_FILE_HEADER 
			// UINT				�ļ��汾��		ӦΪ FK_OBJ_FILE_VERSION

		//���ʶ�
		FK_CID_Material				= 0x2000,
			// MaterialData		�������ݽṹ

		//����������
		FK_CID_TriMesh				= 0x3100,
			// TriMeshInfo		������������Ϣ
			// UINT*			��ͷ�������� ���� = sizeof(UINT) * TriMeshInfo.nNumBone

		//����������
		FK_CID_StreamMesh			= 0x3200,
			// StreamMeshInfo		������������Ϣ
			// UINT*				����������֡������ ���� = sizeof(UINT) * StreamMeshInfo.nNumFrames
			// StreamMeshSegment*	�������������Ϣ ���� = sizeof(StreamMeshSegment) * StreamMeshInfo.nNumSegment

			//��Χ�ж�
			FK_CID_BoundBox				= 0x3001,
				// Vector3			��Χ������
				// Vector3			��Χ����С��

			//���������ݶ�
			FK_CID_IndexStream			= 0x3002,
				// IndexStreamInfo	��������Ϣ
				// void*			�������� ���� = IndexStreamInfo.eIndexType * IndexStreamInfo.nNumIndex

			//���������ݶ�
			FK_CID_VertexStream			= 0x3003,
				// VertexStreamInfo	��������Ϣ
				// void*			�������� ���� = VertexStreamInfo.nVerSize * VertexStreamInfo.nNumVer

			//����Ԫ�ض�
			FK_CID_VertexElement		= 0x3004,
				// VertexElement	����Ԫ������

			//�������
			FK_CID_SubMesh				= 0x3005,
				// SubMeshInfo		��������Ϣ

		//����
		FK_CID_Skeleton			= 0x4100,
			// SkeletonInfo		������Ϣ
			// Matrix4*			�ؼ�֡�������� ���� = sizeof(Matrix4) * SkeletonInfo.nNumKey * SkeletonInfo.nNumBone

		//�����
		FK_CID_Billboard		= 0x5100,
			// BillboardInfo	�������Ϣ
			// Vector3*			������������� ���� = sizeof(Vector3) * BillboardInfo.nNumBillboard

		//��ײ����
		FK_CID_BoundMesh		= 0x6100,
			// BoundInfo		��ײ����Ϣ
			// BoundFace*		��ײ������ ���� = sizeof(BoundFace) * BoundInfo.nNumFace
			// Vector3*			��ײ�涥������ ���� = sizeof(Vector3) * BoundInfo.nNumVertex
	};

	//--------------------------------------------------------------------------------------------------------------

	//��������
	enum MaterialType
	{
		Opacity,		//��ȫ��͸��
		Transparent,	//��͸��
		AlphaMask,		//͸������
	};

	//��������
	struct MaterialData
	{
		ColorValue		Diffuse;				//����ɫ
		ColorValue		Ambient;				//����ɫ
		ColorValue		Specular;				//�߹�ɫ
		ColorValue		Emissive;				//����ɫ
		float			Power;					//�߹�����ֵ

		MaterialType	eType;					//��������
		bool			bHaveTexture;			//�Ƿ��������

		char			szMaterialName[32];		//��������
		char			szTexFileName[32];		//�����ļ�����
	};
	typedef Stack< MaterialData >	MaterialDataStack;

	//--------------------------------------------------------------------------------------------------------------

	//����������
	struct FaceIndex
	{
		union
		{
			struct
			{
				WORD v1;
				WORD v2;
				WORD v3;
			};
			WORD v[3];
		};
	};
	typedef Stack< FaceIndex >	FaceIndexStack;

	//--------------------------------------------------------------------------------------------------------------

	//˫����ֵ���� UV ����
	struct UV2
	{
		float u;
		float v;
	};
	typedef Stack< UV2 >		UV2Stack;

	//��ɫ����
	typedef Stack< DWORD >		ColorStack;

	//--------------------------------------------------------------------------------------------------------------

	//������������Ϣ
	struct TriMeshInfo
	{
		UINT		nNumVertex;			//���񶥵�����
		UINT		nNumFace;			//��������������
		
		UINT		nNumVertexStream;	//����������
		UINT		nNumSubMesh;		//����������

		UINT		nNumBone;			//������ͷ����
		UINT		nNumBonePerVer;		//ÿ�����Ϲ�ͷ����
		bool		bHaveNormal;		//�Ƿ���ڷ�����
	};

	//�������������Ϣ
	struct StreamMeshSegment
	{
		UINT		nVertexOffset;		//�ζ���ƫ����
		UINT		nVertexNum;			//�ζ�������

		UINT		nNumFrames;			//�ΰ���֡��
	};
	typedef Stack< StreamMeshSegment >	StreamMeshSegmentStack;

	//������������Ϣ
	struct StreamMeshInfo
	{
		UINT		nNumVertex;			//���񶥵�����
		UINT		nNumFace;			//��������������

		UINT		nNumVertexStream;	//����������
		UINT		nNumSubMesh;		//����������

		UINT		nNumSegment;		//����

		UINT		nNumFacePerFrame;	//����������
		UINT		nNumFrames;			//����֡��

		float		fIntervalTime;		//ÿ֡��ͣ��ʱ�䣨�룩
	};

	//��������Ϣ
	struct IndexStreamInfo
	{
		IndexType	eIndexType;			//����������
		UINT		nNumIndex;			//��������
		bool		bDynamic;			//�Ƿ�Ϊ��̬������
	};

	//��������Ϣ
	struct VertexStreamInfo
	{
		UINT		nVerSize;			//ÿ���㳤��
		UINT		nNumVer;			//��������
		bool		bDynamic;			//�Ƿ�Ϊ��̬������
	};

	//��������Ϣ
	struct SubMeshInfo
	{
		UINT		nIndexOffset;		//��������ƫ����
		UINT		nVerCount;			//���ƶ�������
		UINT		nPrimCount;			//����ͼԪ����
		int			nMaterialIndex;		//ʹ�ò�������
	};
	typedef Stack< SubMeshInfo >	SubMeshInfoStack;

	//--------------------------------------------------------------------------------------------------------------

	//������Ϣͷ
	struct SkeletonInfo
	{
		UINT	nNumBone;			//��ͷ����
		UINT	nNumKey;			//֡����
		float	fIntervalTime;		//ÿ֡��ͣ��ʱ�䣨�룩
	};

	//--------------------------------------------------------------------------------------------------------------

	//�������Ϣͷ
	struct BillboardInfo
	{
		UINT	nNumBillboard;		//���������
		float	fSizeX;				//����� X �ߴ�
		float	fSizeY;				//����� Y �ߴ�
		int		nMaterialIndex;		//������������ֵ
		char	szUVAFileName[32];	//����� UV �����ļ���
	};

	//--------------------------------------------------------------------------------------------------------------

	//��ײ����������
	struct BoundFace
	{
		Vector3	vNormal;		//�淨��
		UINT	nV1Index;		//���� 1 ����ֵ
		UINT	nV2Index;		//���� 2 ����ֵ
		UINT	nV3Index;		//���� 3 ����ֵ
	};
	typedef Stack< BoundFace >	BoundFaceStack;

	//��ײ������ͷ
	struct BoundInfo
	{
		//��ײ������
		enum Type
		{
			General,	//��ͨ��ײ��
			Stair,		//¥����ײ��
			Ladder,		//������ײ��
		};

		Type		eType;			//��ײ������
		UINT		nNumFace;		//��ײ��������
		UINT		nNumVertex;		//��ײ�����涥����
		Vector3		vBoundBoxMax;	//��ײ���Χ������
		Vector3		vBoundBoxMin;	//��ײ���Χ����С��
	};

	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================