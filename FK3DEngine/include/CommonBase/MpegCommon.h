/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	MpegCommon
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	MPEG �������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

#include "MpegInterface.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	#ifndef M_PI
	#define M_PI		3.14159265358979323846f
	#endif

	#ifndef M_SQRT2
	#define M_SQRT2		1.41421356237309504880f
	#endif

	//--------------------------------------------------------------------------------------------------------------

	// MPEG ��Ƶ�������ݽṹ
	struct MPEGDecodeData
	{
		int				nPrevSize;
		unsigned char	pBuffer[2][ MPEG_MaxFrameSize + 512 ];
		int				nBuffer;

		float			ppHybridBlock[2][2][ MPEG_SBLimit * MPEG_SSLimit ];
		int				pHybridBlock[2];

		float			ppSynthBuf[2][2][0x110];
		int				nSynthBo;
	};

	struct MEPGHuffman 
	{
		unsigned int	nLinBits;
		short*			pTable;
	};

	//--------------------------------------------------------------------------------------------------------------

	extern MPEGDecodeData		g_DecodeData;		// MPEG ��Ƶ��������

	extern int					g_nBitIndex;
	extern unsigned char*		g_pDataPtr;
	extern float				g_pMuls[27][64];

	extern float				MPEG_DecWin[512+32];
	extern float*				MPEG_CosPtr[];

	extern MEPGHuffman			MPEG_HuffmanT[];
	extern MEPGHuffman			MPEG_HuffmanTC[];

	//--------------------------------------------------------------------------------------------------------------

	extern void FKFastcall SetPointer( long nBackstep );

	unsigned int FKFastcall GetBitOne();
	unsigned int FKFastcall GetBit( int nNumBits );
	unsigned int FKFastcall GetBitFast( int nNumBits );

	extern void InitLayer3( int nSBLimit );
	extern void InitLayer2();
	extern void BuildTables( long nScal );

	extern int DecodeLayer1( MPEGFrameInfo* pFrameInfo, unsigned char* pOut, int* pOutSize );
	extern int DecodeLayer2( MPEGFrameInfo* pFrameInfo, unsigned char* pOut, int* pOutSize );
	extern int DecodeLayer3( MPEGFrameInfo* pFrameInfo, unsigned char* pOut, int* pOutSize );

	extern int Synth_1to1( float* pBand, int nChannel, unsigned char* pOut, int* pPoint );
	extern int Synth_1to1_Mono( float* pBand, unsigned char* pSamples, int* pPoint );

	extern void Dct64( float* pA, float* pB, float* pC );

	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
