/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	DDSDecoder
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	DDS ͼ�������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	// DirectDraw ���ظ�ʽ�ṹ
	struct DDPIXELFORMAT
	{
		DWORD	dwSize;				//�ṹ��С������Ϊ 32��
		DWORD	dwFlags;			//��ʽѡ���־��DDPF_RGB δѹ����ʽ DDPF_FOURCC ѹ����ʽ��
		DWORD	dwFourCC;			//ѹ����ʽ���ͱ�־
		DWORD	dwRGBBitCount;		//δѹ������λ��
		DWORD	dwRBitMask;			//��ɫͨ������
		DWORD	dwGBitMask;			//��ɫͨ������
		DWORD	dwBBitMask;			//��ɫͨ������
		DWORD	dwRGBAlphaBitMask;	//͸��ͨ������
	};

	// DirectDraw ѡ��
	struct DDCAPS2
	{
		DWORD	dwCaps1;			//ѡ�� 1
		DWORD	dwCaps2;			//ѡ�� 2
		DWORD	dwReserved[2];		//����
	};

	// DirectDraw ���������ṹ
	struct DDSURFACEDESC2
	{
		DWORD			dwSize;					//�ṹ��С������Ϊ 124��
		DWORD			dwFlags;				//ѡ���־�������� DDSD_CAPS, DDSD_PIXELFORMAT, DDSD_WIDTH, DDSD_HEIGHT.��
		DWORD			dwHeight;				//��ͼ��߶�
		DWORD			dwWidth;				//��ͼ����
		DWORD			dwPitchOrLinearSize;	//δѹ����ͼ���ȣ�DDSD_PITCH����ѹ����ͼ���С��DDSD_LINEARSIZE��
		DWORD			dwDepth;				//����������
		DWORD			dwMipMapCount;			//ͼ����������DDSD_MIPMAPCOUNT��
		DWORD			dwReserved1[11];		//���� 1
		DDPIXELFORMAT	ddpfPixelFormat;		//���ظ�ʽ
		DDCAPS2			ddsCaps;				//DirectDraw ѡ��
		DWORD			dwReserved2;			//���� 2
	};

	//����ѹ����ʽ��־
	const DWORD TEXC_DXT1			= FK_FOURCC( 'D', 'X', 'T', '1' );
	const DWORD TEXC_DXT2			= FK_FOURCC( 'D', 'X', 'T', '2' );
	const DWORD TEXC_DXT3			= FK_FOURCC( 'D', 'X', 'T', '3' );
	const DWORD TEXC_DXT4			= FK_FOURCC( 'D', 'X', 'T', '4' );
	const DWORD TEXC_DXT5			= FK_FOURCC( 'D', 'X', 'T', '5' );

	// DirectDraw ���������ṹѡ���־
	const DWORD DDSD_CAPS			= 0x00000001;
	const DWORD DDSD_HEIGHT			= 0x00000002;
	const DWORD DDSD_WIDTH			= 0x00000004;
	const DWORD DDSD_PITCH			= 0x00000008;
	const DWORD DDSD_PIXELFORMAT	= 0x00001000;
	const DWORD DDSD_MIPMAPCOUNT	= 0x00020000;
	const DWORD DDSD_LINEARSIZE		= 0x00080000;
	const DWORD DDSD_DEPTH			= 0x00800000;

	// DirectDraw ���ظ�ʽ�ṹѡ���־
	const DWORD DDPF_ALPHAPIXELS	= 0x00000001;
	const DWORD DDPF_FOURCC			= 0x00000004;
	const DWORD DDPF_RGB			= 0x00000040;

	// DirectDraw ѡ�� 1
	const DWORD DDSCAPS_COMPLEX		= 0x00000008;
	const DWORD DDSCAPS_TEXTURE		= 0x00001000;
	const DWORD DDSCAPS_MIPMAP		= 0x00400000;

	// DirectDraw ѡ�� 2
	const DWORD DDSCAPS2_CUBEMAP			= 0x00000200;
	const DWORD DDSCAPS2_CUBEMAP_POSITIVEX	= 0x00000400;
	const DWORD DDSCAPS2_CUBEMAP_NEGATIVEX	= 0x00000800;
	const DWORD DDSCAPS2_CUBEMAP_POSITIVEY	= 0x00001000;
	const DWORD DDSCAPS2_CUBEMAP_NEGATIVEY	= 0x00002000;
	const DWORD DDSCAPS2_CUBEMAP_POSITIVEZ	= 0x00004000;
	const DWORD DDSCAPS2_CUBEMAP_NEGATIVEZ	= 0x00008000;
	const DWORD DDSCAPS2_VOLUME				= 0x00200000;
	
	const DWORD DDSCAPS2_CUBEMAP_ALL = DDSCAPS2_CUBEMAP_POSITIVEX | DDSCAPS2_CUBEMAP_NEGATIVEX |
		DDSCAPS2_CUBEMAP_POSITIVEY | DDSCAPS2_CUBEMAP_NEGATIVEY | DDSCAPS2_CUBEMAP_POSITIVEZ | DDSCAPS2_CUBEMAP_NEGATIVEZ;

	// DDS ͼ������
	enum DDSImageType
	{
		DDS_Normal,		//��ͨ����
		DDS_Cube,		//��״����
		DDS_Volume,		//��������
	};

	// DDS ͼ����Ϣ�ṹ
	struct DDSImageLevel
	{
		DWORD			dwWidth;		//ͼ����
		DWORD			dwHeight;		//ͼ��߶�

		DWORD			dwDataLen;		//ͼ�����ݳ���
		DWORD			dwDataOffset;	//ͼ������ƫ����
	};

	// DDS ͼ���ļ�������Ϣ�ṹ
	struct DDSDecodeInfo
	{
		DWORD			dwLevelCount;	//ͼ�񼶱�����
		DWORD			dwDecodeLevel;	//��ǰ���뼶��

		DDSImageType	eImageType;		//ͼ������
		DDSImageLevel*	pImageLevel;	//ͼ�񼶱���Ϣ
	};

	//--------------------------------------------------------------------------------------------------------------

	//���� DDS ͼ��ͷ
	extern void DDSParseHeader( ImageDecoder* pThis );

	//��� DDS ͼ�����
	extern void DDSEndDecode( ImageDecoder* pThis );

	//���� DDS ͼ������
	extern void DDSDecode( ImageDecoder* pThis, BYTE* pDstBuf, RECT* srcRect, RECT* dstRect,
		int pitch, PixelFormat ePixelFormat );

	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
