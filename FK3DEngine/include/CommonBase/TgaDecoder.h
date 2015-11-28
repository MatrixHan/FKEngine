/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	TgaDecoder
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	TGA ͼ�������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	#pragma pack( push )
	#pragma pack( 1 )

	// TGA �ļ�ͷ
	struct TgaFileHeader
	{
		BYTE	bIDLen;			//�ļ����� ID �ַ�������
		BYTE	bHavePal;		//�Ƿ���ڵ�ɫ��

		BYTE	bCompFlag;		//ͼ��ѹ������

								// 0 - ��ͼ��
								// 1 - ��ɫ�� δѹ��
								// 2 - ���ɫ δѹ��
								// 3 - �ڰ�ɫ δѹ��
								// 9 - ��ɫ�� �г�ѹ��
								// 10 - ���ɫ �г�ѹ��
								// 11 - �ڰ�ɫ �г�ѹ��

		WORD	wPalFirstUnit;	//ͼ����ʹ�õĵ�һ����ɫ��������ֵ
		WORD	wPalSize;		//��ɫ������

		BYTE	bPalUnitBits;	//��ɫ����λ��

								// 15 - RRRRR GGGGG BBBBB
								// 16 - A RRRRR GGGGG BBBBB
								// 24 - BBBBBBBB GGGGGGGG RRRRRRRR
								// 32 - BBBBBBBB GGGGGGGG RRRRRRRR AAAAAAAA

		WORD	wPicX;			//ͼ���������Ļ��� ���ؾ���
		WORD	wPicY;			//ͼ��ױ�����Ļ�ױ� ���ؾ���
		WORD	wPicWidth;		//ͼ����
		WORD	wPicHeight;		//ͼ��߶�

		BYTE	bPixelBits;		//ÿ����λ��

		BYTE	bPicInfoBits;	//ͼ��������

								//����λ	ÿ��������λ��Ŀ

								//�м���λ	�������ش洢˳��������ļ��д洢˳��

								//			0x00 - ���� �µ���
								//			0x10 - �ҵ��� �µ���
								//			0x20 - ���� �ϵ���
								//			0x30 - �ҵ��� �ϵ���

								//����λ	ɨ���н�������

								//			0x00 - �޽���
								//			0x40 - ��·��ż����
								//			0x80 - ��·����
	};

	// TGA �ļ�β
	struct TgaFileFooter
	{
		int		nExtOffset;		//��չ����ƫ����
		int		nDevListOffset;	//����Ա�б�ƫ����
		char	szFooter[18];	// "TRUEVISION-TARGA." �ַ���
	};

	#pragma pack( pop )

	//--------------------------------------------------------------------------------------------------------------

	// TGA ͼ������������
	struct TgaExtData
	{
		TgaFileHeader	sTgaFileHeader;	// TGA �ļ�ͷ

		BYTE*			pPalData;		//��ɫ������

		bool			bUsePal;		//�Ƿ�ʹ�õ�ɫ��
		bool			bUseRLE;		//�Ƿ�ʹ���г�ѹ��
		bool			bYReversed;		//�Ƿ�����ת
		long			nPicDataOffset;	//ͼ������ƫ����
	};

	//--------------------------------------------------------------------------------------------------------------

	//���� TGA ͼ��ͷ
	extern void TgaParseHeader( ImageDecoder* pThis );

	//��� TGA ͼ�����
	extern void TgaEndDecode( ImageDecoder* pThis );

	//���� TGA ͼ������
	extern void TgaDecode( ImageDecoder* pThis, BYTE* pDstBuf, RECT* srcRect, RECT* dstRect,
		int pitch, PixelFormat ePixelFormat );

	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
