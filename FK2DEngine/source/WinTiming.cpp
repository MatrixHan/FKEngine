/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	WinTiming
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../include/Timing.h"
#include <windows.h>
#include <cstdlib>

//--------------------------------------------------------------------
void FK2DEngine::FKSleep( unsigned int p_unMilliSeconds )
{
	::Sleep( p_unMilliSeconds );
}
//--------------------------------------------------------------------
namespace
{
	void ResetTGT()
	{
		::timeEndPeriod(1);
	}
}
//--------------------------------------------------------------------
unsigned long FK2DEngine::MilliSeconds()
{
	static bool bInit = false;
	if( !bInit )
	{
		if( ::timeBeginPeriod(1) != TIMERR_NOERROR )
		{
			std::atexit( ResetTGT );
		}
		bInit = true;
	}
	return ::timeGetTime();
}
//--------------------------------------------------------------------