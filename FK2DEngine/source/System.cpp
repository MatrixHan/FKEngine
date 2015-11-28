/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	System
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../include/System.h"

#ifdef FK_WINDOWS
	#include <windows.h>
#endif

// ���������ļ�
#ifdef _DEBUG
	#include <crtdbg.h>
#endif

//--------------------------------------------------------------------
namespace FK2DEngine
{
	namespace System
	{
		//--------------------------------------------------------------------
		bool IsCpuSupportMMX()
		{
			int ismmx = 0;

			__asm
			{
				mov eax, 1
				cpuid
				test edx, 0x00800000
				jz  _notmmx
				mov  ismmx, 1
_notmmx:
			}

			return ismmx == 1;
		}
		//--------------------------------------------------------------------
		void EnableMemoryLeakCheck()
		{
			#if defined(DEBUG) | defined(_DEBUG)
				_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
			#endif
		}
		//--------------------------------------------------------------------
		bool CheckDXVersion8()
		{
#ifdef FK_WINDOWS
			HINSTANCE hD3D8DLL = LoadLibrary("D3D8.DLL");
			if (hD3D8DLL == NULL)
			{
				return false;
			}
			else
			{
				FreeLibrary(hD3D8DLL);
				return true;
			}
#else
			return false;
#endif
		}
		//--------------------------------------------------------------------
	}
}