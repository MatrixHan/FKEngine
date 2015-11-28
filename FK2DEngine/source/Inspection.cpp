/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Inspection
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../include/Inspection.h"
#include "../include/Timing.h"

//--------------------------------------------------------------------

namespace FK2DEngine
{
	namespace FPS
	{
		int g_nFps;
		int g_nAccum;
		int g_nSec;

		void RegisterFrame()
		{
			++g_nAccum;
			int nNewSec = FK2DEngine::MilliSeconds() / 1000;
			if( nNewSec != g_nSec )
			{
				g_nSec = nNewSec;
				g_nFps = g_nAccum;
				g_nAccum = 0;
			}
		}
	}
	//--------------------------------------------------------------------
	int GetFPS()
	{
		return FPS::g_nFps;
	}
}