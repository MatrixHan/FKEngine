/********************************************************************
*
*	本文件是FKMMORPG的一部分。本文件版权归属FreeKnightDuzhi(王宏张)所有。
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	文件名：	Dct64_i386
*	作者：		FreeKnightDuzhi[ 王宏张 ]
*	文件说明：	
*
*	修改人:		
*	修改内容:
*********************************************************************/

#include "../../include/CommonBase/CommonBaseInsideHead.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	static void Dct64_1( float* out0, float* out1, float* b1, float* b2, float* samples )
	{
		{
			register float* pCosTab = MPEG_CosPtr[0];

			b1[0x00] = samples[0x00] + samples[0x1F];
			b1[0x1F] = (samples[0x00] - samples[0x1F]) * pCosTab[0x0];

			b1[0x01] = samples[0x01] + samples[0x1E];
			b1[0x1E] = (samples[0x01] - samples[0x1E]) * pCosTab[0x1];

			b1[0x02] = samples[0x02] + samples[0x1D];
			b1[0x1D] = (samples[0x02] - samples[0x1D]) * pCosTab[0x2];

			b1[0x03] = samples[0x03] + samples[0x1C];
			b1[0x1C] = (samples[0x03] - samples[0x1C]) * pCosTab[0x3];

			b1[0x04] = samples[0x04] + samples[0x1B];
			b1[0x1B] = (samples[0x04] - samples[0x1B]) * pCosTab[0x4];

			b1[0x05] = samples[0x05] + samples[0x1A];
			b1[0x1A] = (samples[0x05] - samples[0x1A]) * pCosTab[0x5];

			b1[0x06] = samples[0x06] + samples[0x19];
			b1[0x19] = (samples[0x06] - samples[0x19]) * pCosTab[0x6];

			b1[0x07] = samples[0x07] + samples[0x18];
			b1[0x18] = (samples[0x07] - samples[0x18]) * pCosTab[0x7];

			b1[0x08] = samples[0x08] + samples[0x17];
			b1[0x17] = (samples[0x08] - samples[0x17]) * pCosTab[0x8];

			b1[0x09] = samples[0x09] + samples[0x16];
			b1[0x16] = (samples[0x09] - samples[0x16]) * pCosTab[0x9];

			b1[0x0A] = samples[0x0A] + samples[0x15];
			b1[0x15] = (samples[0x0A] - samples[0x15]) * pCosTab[0xA];

			b1[0x0B] = samples[0x0B] + samples[0x14];
			b1[0x14] = (samples[0x0B] - samples[0x14]) * pCosTab[0xB];

			b1[0x0C] = samples[0x0C] + samples[0x13];
			b1[0x13] = (samples[0x0C] - samples[0x13]) * pCosTab[0xC];

			b1[0x0D] = samples[0x0D] + samples[0x12];
			b1[0x12] = (samples[0x0D] - samples[0x12]) * pCosTab[0xD];

			b1[0x0E] = samples[0x0E] + samples[0x11];
			b1[0x11] = (samples[0x0E] - samples[0x11]) * pCosTab[0xE];

			b1[0x0F] = samples[0x0F] + samples[0x10];
			b1[0x10] = (samples[0x0F] - samples[0x10]) * pCosTab[0xF];
		}


		{
			register float* pCosTab = MPEG_CosPtr[1];

			b2[0x00] = b1[0x00] + b1[0x0F]; 
			b2[0x0F] = (b1[0x00] - b1[0x0F]) * pCosTab[0];
			b2[0x01] = b1[0x01] + b1[0x0E]; 
			b2[0x0E] = (b1[0x01] - b1[0x0E]) * pCosTab[1];
			b2[0x02] = b1[0x02] + b1[0x0D]; 
			b2[0x0D] = (b1[0x02] - b1[0x0D]) * pCosTab[2];
			b2[0x03] = b1[0x03] + b1[0x0C]; 
			b2[0x0C] = (b1[0x03] - b1[0x0C]) * pCosTab[3];
			b2[0x04] = b1[0x04] + b1[0x0B]; 
			b2[0x0B] = (b1[0x04] - b1[0x0B]) * pCosTab[4];
			b2[0x05] = b1[0x05] + b1[0x0A]; 
			b2[0x0A] = (b1[0x05] - b1[0x0A]) * pCosTab[5];
			b2[0x06] = b1[0x06] + b1[0x09]; 
			b2[0x09] = (b1[0x06] - b1[0x09]) * pCosTab[6];
			b2[0x07] = b1[0x07] + b1[0x08]; 
			b2[0x08] = (b1[0x07] - b1[0x08]) * pCosTab[7];

			b2[0x10] = b1[0x10] + b1[0x1F];
			b2[0x1F] = (b1[0x1F] - b1[0x10]) * pCosTab[0];
			b2[0x11] = b1[0x11] + b1[0x1E];
			b2[0x1E] = (b1[0x1E] - b1[0x11]) * pCosTab[1];
			b2[0x12] = b1[0x12] + b1[0x1D];
			b2[0x1D] = (b1[0x1D] - b1[0x12]) * pCosTab[2];
			b2[0x13] = b1[0x13] + b1[0x1C];
			b2[0x1C] = (b1[0x1C] - b1[0x13]) * pCosTab[3];
			b2[0x14] = b1[0x14] + b1[0x1B];
			b2[0x1B] = (b1[0x1B] - b1[0x14]) * pCosTab[4];
			b2[0x15] = b1[0x15] + b1[0x1A];
			b2[0x1A] = (b1[0x1A] - b1[0x15]) * pCosTab[5];
			b2[0x16] = b1[0x16] + b1[0x19];
			b2[0x19] = (b1[0x19] - b1[0x16]) * pCosTab[6];
			b2[0x17] = b1[0x17] + b1[0x18];
			b2[0x18] = (b1[0x18] - b1[0x17]) * pCosTab[7];
		}

		{
			register float* pCosTab = MPEG_CosPtr[2];

			b1[0x00] = b2[0x00] + b2[0x07];
			b1[0x07] = (b2[0x00] - b2[0x07]) * pCosTab[0];
			b1[0x01] = b2[0x01] + b2[0x06];
			b1[0x06] = (b2[0x01] - b2[0x06]) * pCosTab[1];
			b1[0x02] = b2[0x02] + b2[0x05];
			b1[0x05] = (b2[0x02] - b2[0x05]) * pCosTab[2];
			b1[0x03] = b2[0x03] + b2[0x04];
			b1[0x04] = (b2[0x03] - b2[0x04]) * pCosTab[3];

			b1[0x08] = b2[0x08] + b2[0x0F];
			b1[0x0F] = (b2[0x0F] - b2[0x08]) * pCosTab[0];
			b1[0x09] = b2[0x09] + b2[0x0E];
			b1[0x0E] = (b2[0x0E] - b2[0x09]) * pCosTab[1];
			b1[0x0A] = b2[0x0A] + b2[0x0D];
			b1[0x0D] = (b2[0x0D] - b2[0x0A]) * pCosTab[2];
			b1[0x0B] = b2[0x0B] + b2[0x0C];
			b1[0x0C] = (b2[0x0C] - b2[0x0B]) * pCosTab[3];

			b1[0x10] = b2[0x10] + b2[0x17];
			b1[0x17] = (b2[0x10] - b2[0x17]) * pCosTab[0];
			b1[0x11] = b2[0x11] + b2[0x16];
			b1[0x16] = (b2[0x11] - b2[0x16]) * pCosTab[1];
			b1[0x12] = b2[0x12] + b2[0x15];
			b1[0x15] = (b2[0x12] - b2[0x15]) * pCosTab[2];
			b1[0x13] = b2[0x13] + b2[0x14];
			b1[0x14] = (b2[0x13] - b2[0x14]) * pCosTab[3];

			b1[0x18] = b2[0x18] + b2[0x1F];
			b1[0x1F] = (b2[0x1F] - b2[0x18]) * pCosTab[0];
			b1[0x19] = b2[0x19] + b2[0x1E];
			b1[0x1E] = (b2[0x1E] - b2[0x19]) * pCosTab[1];
			b1[0x1A] = b2[0x1A] + b2[0x1D];
			b1[0x1D] = (b2[0x1D] - b2[0x1A]) * pCosTab[2];
			b1[0x1B] = b2[0x1B] + b2[0x1C];
			b1[0x1C] = (b2[0x1C] - b2[0x1B]) * pCosTab[3];
		}

		{
			register float const cos0 = MPEG_CosPtr[3][0];
			register float const cos1 = MPEG_CosPtr[3][1];

			b2[0x00] = b1[0x00] + b1[0x03];
			b2[0x03] = (b1[0x00] - b1[0x03]) * cos0;
			b2[0x01] = b1[0x01] + b1[0x02];
			b2[0x02] = (b1[0x01] - b1[0x02]) * cos1;

			b2[0x04] = b1[0x04] + b1[0x07];
			b2[0x07] = (b1[0x07] - b1[0x04]) * cos0;
			b2[0x05] = b1[0x05] + b1[0x06];
			b2[0x06] = (b1[0x06] - b1[0x05]) * cos1;

			b2[0x08] = b1[0x08] + b1[0x0B];
			b2[0x0B] = (b1[0x08] - b1[0x0B]) * cos0;
			b2[0x09] = b1[0x09] + b1[0x0A];
			b2[0x0A] = (b1[0x09] - b1[0x0A]) * cos1;

			b2[0x0C] = b1[0x0C] + b1[0x0F];
			b2[0x0F] = (b1[0x0F] - b1[0x0C]) * cos0;
			b2[0x0D] = b1[0x0D] + b1[0x0E];
			b2[0x0E] = (b1[0x0E] - b1[0x0D]) * cos1;

			b2[0x10] = b1[0x10] + b1[0x13];
			b2[0x13] = (b1[0x10] - b1[0x13]) * cos0;
			b2[0x11] = b1[0x11] + b1[0x12];
			b2[0x12] = (b1[0x11] - b1[0x12]) * cos1;

			b2[0x14] = b1[0x14] + b1[0x17];
			b2[0x17] = (b1[0x17] - b1[0x14]) * cos0;
			b2[0x15] = b1[0x15] + b1[0x16];
			b2[0x16] = (b1[0x16] - b1[0x15]) * cos1;

			b2[0x18] = b1[0x18] + b1[0x1B];
			b2[0x1B] = (b1[0x18] - b1[0x1B]) * cos0;
			b2[0x19] = b1[0x19] + b1[0x1A];
			b2[0x1A] = (b1[0x19] - b1[0x1A]) * cos1;

			b2[0x1C] = b1[0x1C] + b1[0x1F];
			b2[0x1F] = (b1[0x1F] - b1[0x1C]) * cos0;
			b2[0x1D] = b1[0x1D] + b1[0x1E];
			b2[0x1E] = (b1[0x1E] - b1[0x1D]) * cos1;
		}

		{
			register float const cos0 = MPEG_CosPtr[4][0];

			b1[0x00] = b2[0x00] + b2[0x01];
			b1[0x01] = (b2[0x00] - b2[0x01]) * cos0;
			b1[0x02] = b2[0x02] + b2[0x03];
			b1[0x03] = (b2[0x03] - b2[0x02]) * cos0;
			b1[0x02] += b1[0x03];

			b1[0x04] = b2[0x04] + b2[0x05];
			b1[0x05] = (b2[0x04] - b2[0x05]) * cos0;
			b1[0x06] = b2[0x06] + b2[0x07];
			b1[0x07] = (b2[0x07] - b2[0x06]) * cos0;
			b1[0x06] += b1[0x07];
			b1[0x04] += b1[0x06];
			b1[0x06] += b1[0x05];
			b1[0x05] += b1[0x07];

			b1[0x08] = b2[0x08] + b2[0x09];
			b1[0x09] = (b2[0x08] - b2[0x09]) * cos0;
			b1[0x0A] = b2[0x0A] + b2[0x0B];
			b1[0x0B] = (b2[0x0B] - b2[0x0A]) * cos0;
			b1[0x0A] += b1[0x0B];

			b1[0x0C] = b2[0x0C] + b2[0x0D];
			b1[0x0D] = (b2[0x0C] - b2[0x0D]) * cos0;
			b1[0x0E] = b2[0x0E] + b2[0x0F];
			b1[0x0F] = (b2[0x0F] - b2[0x0E]) * cos0;
			b1[0x0E] += b1[0x0F];
			b1[0x0C] += b1[0x0E];
			b1[0x0E] += b1[0x0D];
			b1[0x0D] += b1[0x0F];

			b1[0x10] = b2[0x10] + b2[0x11];
			b1[0x11] = (b2[0x10] - b2[0x11]) * cos0;
			b1[0x12] = b2[0x12] + b2[0x13];
			b1[0x13] = (b2[0x13] - b2[0x12]) * cos0;
			b1[0x12] += b1[0x13];

			b1[0x14] = b2[0x14] + b2[0x15];
			b1[0x15] = (b2[0x14] - b2[0x15]) * cos0;
			b1[0x16] = b2[0x16] + b2[0x17];
			b1[0x17] = (b2[0x17] - b2[0x16]) * cos0;
			b1[0x16] += b1[0x17];
			b1[0x14] += b1[0x16];
			b1[0x16] += b1[0x15];
			b1[0x15] += b1[0x17];

			b1[0x18] = b2[0x18] + b2[0x19];
			b1[0x19] = (b2[0x18] - b2[0x19]) * cos0;
			b1[0x1A] = b2[0x1A] + b2[0x1B];
			b1[0x1B] = (b2[0x1B] - b2[0x1A]) * cos0;
			b1[0x1A] += b1[0x1B];

			b1[0x1C] = b2[0x1C] + b2[0x1D];
			b1[0x1D] = (b2[0x1C] - b2[0x1D]) * cos0;
			b1[0x1E] = b2[0x1E] + b2[0x1F];
			b1[0x1F] = (b2[0x1F] - b2[0x1E]) * cos0;
			b1[0x1E] += b1[0x1F];
			b1[0x1C] += b1[0x1E];
			b1[0x1E] += b1[0x1D];
			b1[0x1D] += b1[0x1F];
		}

		out0[0x10*16] = b1[0x00];
		out0[0x10*12] = b1[0x04];
		out0[0x10* 8] = b1[0x02];
		out0[0x10* 4] = b1[0x06];
		out0[0x10* 0] = b1[0x01];
		out1[0x10* 0] = b1[0x01];
		out1[0x10* 4] = b1[0x05];
		out1[0x10* 8] = b1[0x03];
		out1[0x10*12] = b1[0x07];

		b1[0x08] += b1[0x0C];
		out0[0x10*14] = b1[0x08];
		b1[0x0C] += b1[0x0a];
		out0[0x10*10] = b1[0x0C];
		b1[0x0A] += b1[0x0E];
		out0[0x10* 6] = b1[0x0A];
		b1[0x0E] += b1[0x09];
		out0[0x10* 2] = b1[0x0E];
		b1[0x09] += b1[0x0D];
		out1[0x10* 2] = b1[0x09];
		b1[0x0D] += b1[0x0B];
		out1[0x10* 6] = b1[0x0D];
		b1[0x0B] += b1[0x0F];
		out1[0x10*10] = b1[0x0B];
		out1[0x10*14] = b1[0x0F];

		b1[0x18] += b1[0x1C];
		out0[0x10*15] = b1[0x10] + b1[0x18];
		out0[0x10*13] = b1[0x18] + b1[0x14];
		b1[0x1C] += b1[0x1a];
		out0[0x10*11] = b1[0x14] + b1[0x1C];
		out0[0x10* 9] = b1[0x1C] + b1[0x12];
		b1[0x1A] += b1[0x1E];
		out0[0x10* 7] = b1[0x12] + b1[0x1A];
		out0[0x10* 5] = b1[0x1A] + b1[0x16];
		b1[0x1E] += b1[0x19];
		out0[0x10* 3] = b1[0x16] + b1[0x1E];
		out0[0x10* 1] = b1[0x1E] + b1[0x11];
		b1[0x19] += b1[0x1D];
		out1[0x10* 1] = b1[0x11] + b1[0x19];
		out1[0x10* 3] = b1[0x19] + b1[0x15];
		b1[0x1D] += b1[0x1B];
		out1[0x10* 5] = b1[0x15] + b1[0x1D];
		out1[0x10* 7] = b1[0x1D] + b1[0x13];
		b1[0x1B] += b1[0x1F];
		out1[0x10* 9] = b1[0x13] + b1[0x1B];
		out1[0x10*11] = b1[0x1B] + b1[0x17];
		out1[0x10*13] = b1[0x17] + b1[0x1F];
		out1[0x10*15] = b1[0x1F];
	}
	//--------------------------------------------------------------------------------------------------------------
	void Dct64( float* pA, float* pB, float* pC )
	{
		float bufs[0x40];
		Dct64_1( pA, pB, bufs, bufs+0x20, pC );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
