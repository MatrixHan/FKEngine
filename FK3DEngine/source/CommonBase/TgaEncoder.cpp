/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	TgaEncoder
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/CommonBase/CommonBaseInsideHead.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//���� TGA ͼ������
	FK_DLL void EncodeTgaImage( FileObject* pDstFile, BYTE* pSrcBuf, int nPitch, PixelFormat ePixelFormat,
		UINT nWidth, UINT nHeight )
	{
		//����ÿ�����ֽ���
		UINT nPixelBytes = Misc::GetColorDepth( ePixelFormat );

		//���� TGA ͼ���ļ�ͷ����
		TgaFileHeader sTgaHeader = { NULL };

		sTgaHeader.bCompFlag	= 2;			// 2 - ���ɫ δѹ��
		sTgaHeader.wPicWidth	= (WORD)nWidth;	//ͼ����
		sTgaHeader.wPicHeight	= (WORD)nHeight;//ͼ��߶�

		//ÿ����λ��
		sTgaHeader.bPixelBits	= (BYTE)( nPixelBytes << 3 );

		//ͼ��������
		UINT nAlphaBits = Misc::GetColorAlphaBits( ePixelFormat ) & 15;

		//������ ���ϵ���
		sTgaHeader.bPicInfoBits	= nAlphaBits | 0x20;

		//д��ͼ��ͷ
		pDstFile->Write( &sTgaHeader, sizeof(TgaFileHeader) );

		//д��ͼ������
		int nRowLen = nWidth * nPixelBytes;
		for( UINT i=0; i<nHeight; ++i )
		{
			pDstFile->Write( pSrcBuf, nRowLen );
			pSrcBuf += nPitch;
		}

		//д���ļ�β
		TgaFileFooter sTgaFooter = { NULL };
		memcpy( sTgaFooter.szFooter, "TRUEVISION-TARGA.", 18 );

		pDstFile->Write( &sTgaFooter, sizeof(TgaFileFooter) );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
