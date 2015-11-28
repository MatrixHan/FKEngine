/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ProcessorInfo
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

	__int64		ProcessorInfo::mqwFrequency		= 0;		// CPU Ƶ��
	char		ProcessorInfo::mCPUName[128]	= { NULL };	// CPU ����
	CPUInfo		ProcessorInfo::mCPUInfo			= { NULL };	// CPU ��Ϣ

	//--------------------------------------------------------------------------------------------------------------

	//������������
	FKForceInline static char* TranslateAssociativeWays( unsigned int nWays, char* buf );
	FKForceInline static void TranslateTLB( ProcessorTLB* tlb );
	FKForceInline static void TranslateCache( ProcessorCache* cache );

	//λ����
	#define CheckBit( var, bit )	( ( var & (1<<bit) ) ? true : false )

	//--------------------------------------------------------------------------------------------------------------
	//��ȡ CPU Ƶ��
	__int64 ProcessorInfo::GetCPUFrequency( unsigned int nMeasureTime )
	{
		//��� CPUID ָ������򷵻�
		if( !_CheckCPUIDPresence() )
			return 0;

		//����Ի�ȡ CPU Ƶ����ֱ�ӷ���
		if( mqwFrequency > 0 )
			return mqwFrequency;

		//���� CPUID ָ��
		unsigned long reg;
		__asm
		{
			mov eax, 1;
			cpuid
			mov reg, edx;
		}

		//����Ƿ�֧�֣�Real Date Time Stamp Counter��ʵʱʱ�����������
		if( !( reg & (1<<4) ) )
			return 0;

		//ʹ�ø߾��ȼ�ʱ���Լ�� CPU Ƶ��
		__int64 starttime, endtime, timedif, freq, start, end, dif;
		if( !QueryPerformanceFrequency( (LARGE_INTEGER*)&freq ) )
			return 0;

		//���õ�ǰ�߳�Ϊ�������Ȩ��ʵʱ�������ڶദ����ϵͳ��ʹ�õ�һ�鴦����
		HANDLE hProcess = GetCurrentProcess();
		HANDLE hThread = GetCurrentThread();
		unsigned long dwCurPriorityClass = GetPriorityClass( hProcess );
		int iCurThreadPriority = GetThreadPriority( hThread );
		unsigned long dwProcessMask, dwSystemMask, dwNewMask = 1;
		GetProcessAffinityMask( hProcess, &dwProcessMask, &dwSystemMask );

		SetPriorityClass( hProcess, REALTIME_PRIORITY_CLASS );
		SetThreadPriority( hThread, THREAD_PRIORITY_TIME_CRITICAL );
		SetProcessAffinityMask( hProcess, dwNewMask );

		//�������� CPUID ָ��
		__asm cpuid

		//��ʼ�߾��ȼ�ʱ
		QueryPerformanceCounter( (LARGE_INTEGER*)&starttime );

		//��ȡ��ǰ CPU ʱ��
		__asm 
		{
			rdtsc;
			mov dword ptr [start+4], edx;
			mov dword ptr [start], eax;
		}

		//��ͣ�߳�ָ���Ĳ���ʱ��
		Sleep( nMeasureTime );

		//��ȡ��ʱ����
		QueryPerformanceCounter( (LARGE_INTEGER*)&endtime );

		//�ڴ˻�ȡ CPU ʱ��
		__asm 
		{
			rdtsc;
			mov dword ptr [end+4], edx;
			mov dword ptr [end], eax;
		}

		//�ָ�Ĭ���߳����ȼ��� CPU ״̬
		SetProcessAffinityMask( hProcess, dwProcessMask );
		SetThreadPriority( hThread, iCurThreadPriority );
		SetPriorityClass( hProcess, dwCurPriorityClass );

		//����ʱ���ʱ�Ӳ�ֵ
		dif = end - start;
		timedif = endtime - starttime;

		//���㲢���� CPU Ƶ��
		mqwFrequency = (__int64)( (float)dif / ( (float)timedif / freq ) );

		return mqwFrequency;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ CPU ��Ϣ
	const CPUInfo* ProcessorInfo::GetCPUInfo()
	{
		unsigned long eaxreg, ebxreg, ecxreg, edxreg;

		//��� CPUID ָ������򷵻�
		if( !_CheckCPUIDPresence() )
			return NULL;

		//��ȡ���� CPUID ָ��
		__asm
		{
			mov eax, 0;
			cpuid
			mov eaxreg, eax;
			mov ebxreg, ebx;
			mov edxreg, edx;
			mov ecxreg, ecx;
		}

		//��ȡ CPU �����ַ���
		*( (unsigned long*)mCPUInfo.szVendor ) = ebxreg;
		*( (unsigned long*)(mCPUInfo.szVendor+4) ) = edxreg;
		*( (unsigned long*)(mCPUInfo.szVendor+8) ) = ecxreg;

		//��ȡ CPUID ���֧�ֵȼ�
		mCPUInfo.MaxSupportedLevel = eaxreg & 0xFFFF;

		//��ȡ��չ CPUID ���֧�ֵȼ�
		__asm
		{
			mov eax, 0x80000000;
			cpuid
			mov eaxreg, eax;
		}
		mCPUInfo.MaxSupportedExtendedLevel = eaxreg;

		//���� CPU �������͵��ò�ͬ�Ľ�������
		switch (ebxreg)
		{
		case 0x756E6547:	//GennneIntel
			_AnalyzeIntelProcessor();
			break;
		case 0x68747541:	//AuthenticAMD
			_AnalyzeAMDProcessor();
			break;
		case 0x69727943:	//CyrixInstead
		default:			//δ֪ CPU ����
			_AnalyzeUnknownProcessor();
			break;
		}

		//���� CPU ��Ϣ����ָ��
		return &mCPUInfo;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ CPU ˵����Ϣ�ַ���
	String ProcessorInfo::GetCPUInfoText()
	{
		//���� CPU Ƶ��
		GetCPUFrequency( 50 );

		//��ȡ CPU ��Ϣ
		GetCPUInfo();

		//��Ϣ�洢�ַ���
		String strInfo;
		strInfo.SetString(
			"--------------------------------------------------------------------------------------------\n"
			"-                              ������ʿ3D��Ϸ���� CPU ͳ����Ϣ                             -\n"
			"--------------------------------------------------------------------------------------------\n"
			"\nCPU ��׼��Ϣ��\n" );

		strInfo += "\n����             ";		strInfo += mCPUName;
		strInfo += "\nƵ��             ";		strInfo += (int)( (float)mqwFrequency / 1000000.0f );
		strInfo += "\n����             ";		strInfo += mCPUInfo.szVendor;
		strInfo += "\nϵ��             ";		strInfo += mCPUInfo.szFamily;
		strInfo += "\n��չϵ��         ";		strInfo += (int)mCPUInfo.nExtendedFamily;
		strInfo += "\n�ͺ�             ";		strInfo += mCPUInfo.szModel;
		strInfo += "\n��չ�ͺ�         ";		strInfo += (int)mCPUInfo.nExtendedModel;
		strInfo += "\n����             ";		strInfo += mCPUInfo.szType;
		strInfo += "\n�̱�             ";		strInfo += mCPUInfo.szBrandID;

		if( mCPUInfo._Ext.PN_ProcessorSerialNumber )
		{
			strInfo += "\n���������к�     ";		strInfo += mCPUInfo.szProcessorSerial;
		}
		else
		{
			strInfo += "\n���������к�     �ر�";
		}


		strInfo += "\n\n\nCPU ������Ϣ��\n";

		strInfo += "\nһ��ָ���            ";		strInfo += mCPUInfo._L1.Instruction.szCache;
		strInfo += "\nһ�����ݻ���            ";		strInfo += mCPUInfo._L1.Data.szCache;
		strInfo += "\n��������                ";		strInfo += mCPUInfo._L2.szCache;
		strInfo += "\n��������                ";		strInfo += mCPUInfo._L3.szCache;
		strInfo += "\n���Ի���                ";		strInfo += mCPUInfo._Trace.szCache;
		strInfo += "\nָ��TLB                 ";		strInfo += mCPUInfo._Instruction.szTLB;
		strInfo += "\n����TLB                 ";		strInfo += mCPUInfo._Data.szTLB;


		char szCPUIDLevelNum [128] = { NULL };

		itoa( mCPUInfo.MaxSupportedLevel, szCPUIDLevelNum, 16 );
		strInfo += "\n\n���֧�� CPUID ָ��ȼ�           0x";		strInfo += szCPUIDLevelNum;

		itoa( mCPUInfo.MaxSupportedExtendedLevel, szCPUIDLevelNum, 16 );
		strInfo += "\n���֧����չ CPUID ָ��ȼ�       0x";		strInfo += szCPUIDLevelNum;


		strInfo += "\n\n\nCPU ��չ��Ϣ��\n";

		const char szYes[]	= "��";
		const char szNo[]	= "��";

		strInfo += "\nAA64   AMD 64 λ�ܹ�                  ";		strInfo += mCPUInfo._Ext.AA64_AMD64BitArchitecture							? szYes : szNo;
		strInfo += "\nACPI   �¶�̽��/ʱ�ӿ���              ";		strInfo += mCPUInfo._Ext.ACPI_ThermalMonitorAndClockControl					? szYes : szNo;
		strInfo += "\nAPIC   �߼��ɱ���жϿ�����           ";		strInfo += mCPUInfo._Ext.APIC_AdvancedProgrammableInterruptController		? szYes : szNo;
		strInfo += "\n       �߼��ɱ���жϿ��������       ";		strInfo += (int)mCPUInfo._Ext.APIC_ID;
		strInfo += "\nCLFSH  CLFLUSH ָ��֧��               ";		strInfo += mCPUInfo._Ext.CLFSH_CFLUSH_Instruction							? szYes : szNo;
		strInfo += "\n       CLFLUSH ָ����С           ";		strInfo += (int)mCPUInfo._Ext.CLFLUSH_InstructionCacheLineSize;
		strInfo += "\nCMOV   �������ݴ��ͺͱȽ�ָ�       ";		strInfo += mCPUInfo._Ext.CMOV_ConditionalMoveAndCompareInstructions			? szYes : szNo;
		strInfo += "\nCX8    COMPXCHG8B ָ��                ";		strInfo += mCPUInfo._Ext.CX8_COMPXCHG8B_Instruction							? szYes : szNo;
		strInfo += "\nDE     ��չ����ָ��                   ";		strInfo += mCPUInfo._Ext.DE_DebuggingExtensions								? szYes : szNo;
		strInfo += "\nDS     ���Դ洢��                     ";		strInfo += mCPUInfo._Ext.DS_DebugStore										? szYes : szNo;
		strInfo += "\nFGPAT  ҳ���Ա�                       ";		strInfo += mCPUInfo._Ext.FGPAT_PageAttributeTable							? szYes : szNo;


		strInfo += "\nFPU    ���㴦��Ԫ                   ";		strInfo += mCPUInfo._Ext.FPU_FloatingPointUnit								? szYes : szNo;
		strInfo += "\nFXSR   ���� SIMD ָ��洢/�ָ�      ";		strInfo += mCPUInfo._Ext.FXSR_FastStreamingSIMD_ExtensionsSaveRestore		? szYes : szNo;
		strInfo += "\nHT     ���߳�                         ";		strInfo += mCPUInfo._Ext.HT_HyperThreading									? szYes : szNo;
		strInfo += "\nIA64   Intel 64 λ�ܹ�                ";		strInfo += mCPUInfo._Ext.IA64_Intel64BitArchitecture						? szYes : szNo;
		strInfo += "\nMCA    �������ܹ�                   ";		strInfo += mCPUInfo._Ext.MCA_MachineCheckArchitecture						? szYes : szNo;
		strInfo += "\nMCE    ��������쳣                   ";		strInfo += mCPUInfo._Ext.MCE_MachineCheckException							? szYes : szNo;
		strInfo += "\nMMX    ��ý��ָ�                   ";		strInfo += mCPUInfo._Ext.MMX_MultimediaExtensions							? szYes : szNo;
		strInfo += "\nMMX+   ��չ��ý��ָ�               ";		strInfo += mCPUInfo._Ext.EMMX_MultimediaExtensions							? szYes : szNo;
		strInfo += "\nMSR    ģ��ϸ�ڼĴ���                 ";		strInfo += mCPUInfo._Ext.MSR_ModelSpecificRegisters							? szYes : szNo;
		strInfo += "\nMTRR   �ڴ����ͷ�Χ�Ĵ���             ";		strInfo += mCPUInfo._Ext.MTRR_MemoryTypeRangeRegisters						? szYes : szNo;

		strInfo += "\nPAE    �����ַ��չ                   ";		strInfo += mCPUInfo._Ext.PAE_PhysicalAddressExtension						? szYes : szNo;
		strInfo += "\nPGE    PTE ȫ�ֱ�־                   ";		strInfo += mCPUInfo._Ext.PGE_PTE_GlobalFlag									? szYes : szNo;
		strInfo += "\nPSE    ҳ��С��չ                     ";		strInfo += mCPUInfo._Ext.PSE_PageSizeExtensions								? szYes : szNo;
		strInfo += "\nPSE36  36 λҳ��С��չ                ";		strInfo += mCPUInfo._Ext.PSE36_36bitPageSizeExtension						? szYes : szNo;

		strInfo += "\nSEP    ����ϵͳ������                 ";		strInfo += mCPUInfo._Ext.SEP_FastSystemCall									? szYes : szNo;
		strInfo += "\nSS     ��̽��                         ";		strInfo += mCPUInfo._Ext.SS_SelfSnoop										? szYes : szNo;
		strInfo += "\nSSE    ��������ָ���������չָ�   ";		strInfo += mCPUInfo._Ext.SSE_StreamingSIMD_Extensions						? szYes : szNo;
		strInfo += "\nSSE2   ��������ָ���������չָ� 2 ";		strInfo += mCPUInfo._Ext.SSE2_StreamingSIMD2_Extensions						? szYes : szNo;

		strInfo += "\nTM     �¶�̽��                       ";		strInfo += mCPUInfo._Ext.TM_ThermalMonitor									? szYes : szNo;
		strInfo += "\nTSC    ʱ�������                     ";		strInfo += mCPUInfo._Ext.TSC_TimeStampCounter								? szYes : szNo;
		strInfo += "\nVME    ���� 8086 ģʽ��ǿ             ";		strInfo += mCPUInfo._Ext.VME_Virtual8086ModeEnhancements					? szYes : szNo;
		strInfo += "\n       3DNow! ָ�                  ";		strInfo += mCPUInfo._Ext._3DNOW_InstructionExtensions						? szYes : szNo;
		strInfo += "\n       ��ǿ 3DNow! ָ�             ";		strInfo += mCPUInfo._Ext._E3DNOW_InstructionExtensions						? szYes : szNo;

		return strInfo;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�� CPU ˵����Ϣд��ָ���ı��ļ�
	bool ProcessorInfo::WriteCPUInfoTextFile( const char* szFileName )
	{
		//��ȡ CPU ˵����Ϣ
		String& szInfo = GetCPUInfoText();

		//�� CPU ˵����Ϣд��ָ���ļ���
		FILE* pFile = fopen( szFileName, "wt" );
		if( pFile == NULL )
			return false;

		fwrite( szInfo.GetCharPtr(), 1, szInfo.mnCharLength, pFile );

		fclose( pFile );

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� AMD ��������Ϣ
	bool ProcessorInfo::_AnalyzeAMDProcessor()
	{
		unsigned long eaxreg, ebxreg, ecxreg, edxreg;

		//��� CPUID ָ������򷵻�
		if( !_CheckCPUIDPresence() )
			return false;

		//���� CPUID ָ��
		__asm
		{
			mov eax, 1;
			cpuid
			mov eaxreg, eax;
			mov ebxreg, ebx;
			mov edxreg, edx;
		}

		//��ȡ�ͺţ�model����ϵ�У�family�����ΰ汾��stepping�������ͣ�type����
		mCPUInfo.nStepping	= eaxreg & 0xF;
		mCPUInfo.nModel		= (eaxreg >> 4) & 0xF;
		mCPUInfo.nFamily	= (eaxreg >> 8) & 0xF;
		mCPUInfo.nType		= (eaxreg >> 12) & 0x3;

		//���� CPU ����
		switch (mCPUInfo.nType)
		{
		case 0:
			strcpy( mCPUInfo.szType, "ԭʼ OEM" );
			strcpy( mCPUName, mCPUInfo.szType );
			strcat( mCPUName, " " );
			break;
		case 1:
			strcpy( mCPUInfo.szType, "��Ƶ" );
			strcpy( mCPUName, mCPUInfo.szType);
			strcat( mCPUName, " " );
			break;
		case 2:
			strcpy( mCPUInfo.szType, "��Ƶ" );
			strcpy( mCPUName, mCPUInfo.szType );
			strcat( mCPUName, " " );
			break;
		case 3:
			strcpy( mCPUInfo.szType, "����" );
			break;
		default:
			strcpy( mCPUInfo.szType, "δ֪" );
			break;
		}

		//��⴦�����Ƿ�֧���̱��ַ��� CPUID ָ���
		if (mCPUInfo.MaxSupportedExtendedLevel >= 0x80000004)
		{
			//���֧�����ȡ����
			char tmp[52];
			memset( tmp, 0, sizeof(tmp) );

			__asm
			{
				mov eax, 0x80000002;
				cpuid
				mov dword ptr [tmp], eax;
				mov dword ptr [tmp+4], ebx;
				mov dword ptr [tmp+8], ecx;
				mov dword ptr [tmp+12], edx;
				mov eax, 0x80000003;
				cpuid
				mov dword ptr [tmp+16], eax;
				mov dword ptr [tmp+20], ebx;
				mov dword ptr [tmp+24], ecx;
				mov dword ptr [tmp+28], edx;
				mov eax, 0x80000004;
				cpuid
				mov dword ptr [tmp+32], eax;
				mov dword ptr [tmp+36], ebx;
				mov dword ptr [tmp+40], ecx;
				mov dword ptr [tmp+44], edx;
			}

			strcpy( mCPUInfo.szBrandID, tmp );
		}
		else
		{
			strcpy( mCPUInfo.szBrandID, "��֧��" );
		}

		//���� CPU ϵ��
		switch (mCPUInfo.nFamily)
		{
		case 4:			// Family = 4:  486 (80486) �� 5x86 (80486) ϵ��
			switch (mCPUInfo.nModel)
			{
			case 3:
			case 7:
			case 8:
			case 9:
				strcpy( mCPUInfo.szFamily, "AMD 80486" );
				break;
			case 0xE:
			case 0xF:
				strcpy( mCPUInfo.szFamily, "AMD 5x86" );
				break;
			default:
				strcpy( mCPUInfo.szFamily, "δ֪ϵ��" );
				break;
			}
			break;
		case 5:			// Family = 5:  K5 �� K6 ϵ��
			switch (mCPUInfo.nModel)
			{
			case 0:
			case 1:
			case 2:
			case 3:
				strcpy( mCPUInfo.szFamily, "AMD K5" );
				break;
			case 6:
			case 7:
			case 8:
			case 9:
				strcpy( mCPUInfo.szFamily, "AMD K6" );
				break;
			default:
				strcpy( mCPUInfo.szFamily, "δ֪ϵ��" );
				break;
			}
			break;
		case 6:			// Family = 6:  K7 Athlon ϵ��
			strcpy( mCPUInfo.szFamily, "AMD K7" );
			break;
		default:
			strcpy( mCPUInfo.szFamily, "δ֪ϵ��" );
			break;
		}

		//���� CPU �ͺ�
		switch (mCPUInfo.nFamily)
		{
		case 4:			// Family = 4:  486 (80486) �� 5x85 (80486) ϵ��
			switch (mCPUInfo.nModel)
			{
			case 3:			// Model = 3:  80486 DX2
				strcpy( mCPUInfo.szModel, "AMD 80486 DX2" );
				strcat( mCPUName, "AMD 80486 DX2" );
				break;
			case 7:			// Model = 7:  80486 ��д��ǿ DX2
				strcpy( mCPUInfo.szModel, "AMD 80486 ��д��ǿ DX2" );
				strcat( mCPUName, "AMD 80486 ��д��ǿ DX2" );
				break;
			case 8:			// Model = 8:  80486 DX4
				strcpy( mCPUInfo.szModel, "AMD 80486 DX4" );
				strcat( mCPUName, "AMD 80486 DX4" );
				break;
			case 9:			// Model = 9:  80486 ��д��ǿ DX4
				strcpy( mCPUInfo.szModel, "AMD 80486 ��д��ǿ DX4" );
				strcat( mCPUName, "AMD 80486 ��д��ǿ DX4" );
				break;
			case 0xE:		// Model = 0xE:  5x86
				strcpy( mCPUInfo.szModel, "AMD 5x86" );
				strcat( mCPUName, "AMD 5x86" );
				break;
			case 0xF:		// Model = 0xF:  5x86 ��д��ǿ
				strcpy( mCPUInfo.szModel, "AMD 5x86 ��д��ǿ" );
				strcat( mCPUName, "AMD 5x86 ��д��ǿ" );
				break;
			default:		// ...
				strcpy( mCPUInfo.szModel, "δ֪ AMD 80486 �� 5x86 �ͺ�" );
				strcat( mCPUName, "AMD 80486 �� 5x86 (δ֪�ͺ�)" );
				break;
			}
			break;
		case 5:			// Family = 5:  K5 �� K6 ϵ��
			switch (mCPUInfo.nModel)
			{
			case 0:			// Model = 0:  K5 SSA 5 (Pentium Rating 75, 90 and 100 Mhz)
				strcpy( mCPUInfo.szModel, "AMD K5 SSA5 (PR75, PR90, PR100)" );
				strcat( mCPUName, "AMD K5 SSA5 (PR75, PR90, PR100)" );
				break;
			case 1:			// Model = 1:  K5 5k86 (PR 120 and 133 MHz)
				strcpy( mCPUInfo.szModel, "AMD K5 5k86 (PR120, PR133)" );
				strcat( mCPUName, "AMD K5 5k86 (PR120, PR133)" );
				break;
			case 2:			// Model = 2:  K5 5k86 (PR 166 MHz)
				strcpy( mCPUInfo.szModel, "AMD K5 5k86 (PR166)" );
				strcat( mCPUName, "AMD K5 5k86 (PR166)" );
				break;
			case 3:			// Model = 3:  K5 5k86 (PR 200 MHz)
				strcpy( mCPUInfo.szModel, "AMD K5 5k86 (PR200)" );
				strcat( mCPUName, "AMD K5 5k86 (PR200)" );
				break;
			case 6:			// Model = 6:  K6
				strcpy( mCPUInfo.szModel, "AMD K6 (0.30 ΢��)" );
				strcat( mCPUName, "AMD K6 (0.30 ΢��)" );
				break;
			case 7:			// Model = 7:  K6 (0.25 ΢��)
				strcpy( mCPUInfo.szModel, "AMD K6 (0.25 ΢��)" );
				strcat( mCPUName, "AMD K6 (0.25 ΢��)" );
				break;
			case 8:			// Model = 8:  K6-2
				strcpy( mCPUInfo.szModel, "AMD K6-2" );
				strcat( mCPUName, "AMD K6-2" );
				break;
			case 9:			// Model = 9:  K6-III
				strcpy( mCPUInfo.szModel, "AMD K6-III" );
				strcat( mCPUName, "AMD K6-III" );
				break;
			case 0xD:		// Model = 0xD:  K6-2+ / K6-III+
				strcpy( mCPUInfo.szModel, "AMD K6-2+ �� K6-III+ (0.18 ΢��)" );
				strcat( mCPUName, "AMD K6-2+ �� K6-III+ (0.18 ΢��)" );
				break;
			default:		// ...
				strcpy( mCPUInfo.szModel, "δ֪ AMD K5 �� K6 δ֪" );
				strcat( mCPUName, "AMD K5 �� K6 (δ֪�ͺ�)" );
				break;
			}
			break;
		case 6:			// Family = 6:  K7 ϵ��
			switch (mCPUInfo.nModel)
			{
			case 1:			// Athlon
				strcpy( mCPUInfo.szModel, "AMD Athlon (0.25 ΢��)" );
				strcat( mCPUName, "AMD Athlon (0.25 ΢��)" );
				break;
			case 2:			// Athlon (0.18 ΢��)
				strcpy( mCPUInfo.szModel, "AMD Athlon (0.18 ΢��)" );
				strcat( mCPUName, "AMD Athlon (0.18 ΢��)" );
				break;
			case 3:			// Duron (�һ����)
				strcpy( mCPUInfo.szModel, "AMD Duron (�һ����)" );
				strcat( mCPUName, "AMD Duron (�һ����)" );
				break;
			case 4:			// Athlon (�������)
				strcpy( mCPUInfo.szModel, "AMD Athlon (�������)" );
				strcat( mCPUName, "AMD Athlon (�������)" );
				break;
			case 6:			// Athlon MP / Mobile Athlon (Palomino ����)
				strcpy( mCPUInfo.szModel, "AMD Athlon XP (Palomino ����)" );
				strcat( mCPUName, "AMD Athlon XP (Palomino ����)" );
				break;
			case 7:			// Mobile Duron (Ħ������)
				strcpy( mCPUInfo.szModel, "AMD Mobile Duron (Ħ������)" );
				strcat( mCPUName, "AMD Mobile Duron (Ħ������)" );
				break;
			default:
				strcpy( mCPUInfo.szModel, "δ֪ AMD K7 �ͺ�" );
				strcat( mCPUName, "AMD K7 (δ֪�ͺ�)" );
				break;
			}
			break;
		default:
			strcpy( mCPUInfo.szModel, "δ֪ AMD �ͺ�" );
			strcat( mCPUName, "AMD (δ֪�ͺ�)" );
			break;
		}

		_GetStandardProcessorExtensions();

		if( mCPUInfo.MaxSupportedExtendedLevel >= 0x80000001 )
		{
			__asm
			{
				mov eax, 0x80000001;
				cpuid
				mov edxreg, edx;
			}

			mCPUInfo._Ext.EMMX_MultimediaExtensions			= CheckBit(edxreg, 22);
			mCPUInfo._Ext.AA64_AMD64BitArchitecture			= CheckBit(edxreg, 29);
			mCPUInfo._Ext._E3DNOW_InstructionExtensions		= CheckBit(edxreg, 30);
			mCPUInfo._Ext._3DNOW_InstructionExtensions		= CheckBit(edxreg, 31);
		}

		if( mCPUInfo.MaxSupportedExtendedLevel >= 0x80000006 )
		{
			__asm
			{
				mov eax, 0x80000005;
				cpuid
				mov eaxreg, eax;
				mov ebxreg, ebx;
				mov ecxreg, ecx;
				mov edxreg, edx;
			}

			if( (ebxreg >> 16) && (eaxreg >> 16) )
			{
				mCPUInfo._Data.bPresent = true;
				strcpy( mCPUInfo._Data.szPageSize, "4 KB / 2 MB / 4MB" );
				mCPUInfo._Data.nAssociativeWays = (eaxreg >> 24) & 0xFF;
				mCPUInfo._Data.nEntries = (eaxreg >> 16) & 0xFF;
			}
			else if( eaxreg >> 16 )
			{
				mCPUInfo._Data.bPresent = true;
				strcpy( mCPUInfo._Data.szPageSize, "2 MB / 4MB" );
				mCPUInfo._Data.nAssociativeWays = (eaxreg >> 24) & 0xFF;
				mCPUInfo._Data.nEntries = (eaxreg >> 16) & 0xFF;
			}
			else if( ebxreg >> 16 )
			{
				mCPUInfo._Data.bPresent = true;
				strcpy( mCPUInfo._Data.szPageSize, "4 KB" );
				mCPUInfo._Data.nAssociativeWays = (ebxreg >> 24) & 0xFF;
				mCPUInfo._Data.nEntries = (ebxreg >> 16) & 0xFF;
			}
			if( mCPUInfo._Data.nAssociativeWays == 0xFF )
				mCPUInfo._Data.nAssociativeWays = (unsigned int) -1;

			//һ��ָ��/���뻺����Ϣ
			if( (ebxreg & 0xFFFF) && (eaxreg & 0xFFFF) )
			{
				mCPUInfo._Instruction.bPresent = true;
				strcpy( mCPUInfo._Instruction.szPageSize, "4 KB / 2 MB / 4MB" );
				mCPUInfo._Instruction.nAssociativeWays = (eaxreg >> 8) & 0xFF;
				mCPUInfo._Instruction.nEntries = eaxreg & 0xFF;
			}
			else if( eaxreg & 0xFFFF )
			{
				mCPUInfo._Instruction.bPresent = true;
				strcpy( mCPUInfo._Instruction.szPageSize, "2 MB / 4MB" );
				mCPUInfo._Instruction.nAssociativeWays = (eaxreg >> 8) & 0xFF;
				mCPUInfo._Instruction.nEntries = eaxreg & 0xFF;
			}
			else if( ebxreg & 0xFFFF )
			{
				mCPUInfo._Instruction.bPresent = true;
				strcpy( mCPUInfo._Instruction.szPageSize, "4 KB" );
				mCPUInfo._Instruction.nAssociativeWays = (ebxreg >> 8) & 0xFF;
				mCPUInfo._Instruction.nEntries = ebxreg & 0xFF;
			}
			if( mCPUInfo._Instruction.nAssociativeWays == 0xFF )
				mCPUInfo._Instruction.nAssociativeWays = (unsigned int) -1;

			//һ�����ݻ�����Ϣ
			if( (ecxreg >> 24) > 0 )
			{
				mCPUInfo._L1.Data.bPresent = true;
				sprintf( mCPUInfo._L1.Data.szSize, "%d KB", ecxreg >> 24 );
				mCPUInfo._L1.Data.nAssociativeWays = (ecxreg >> 15) & 0xFF;
				mCPUInfo._L1.Data.nLineSize = ecxreg & 0xFF;
			}

			//����ָ��/���뻺����Ϣ
			if( (edxreg >> 24) > 0 )
			{
				mCPUInfo._L1.Instruction.bPresent = true;
				sprintf( mCPUInfo._L1.Instruction.szSize, "%d KB", edxreg >> 24 );
				mCPUInfo._L1.Instruction.nAssociativeWays = (edxreg >> 15) & 0xFF;
				mCPUInfo._L1.Instruction.nLineSize = edxreg & 0xFF;
			}

			__asm
			{
				mov eax, 0x80000006;
				cpuid
				mov eaxreg, eax;
				mov ebxreg, ebx;
				mov ecxreg, ecx;
			}

			if( ( (ecxreg >> 12) & 0xF ) > 0 )
			{
				mCPUInfo._L2.bPresent = true;
				sprintf( mCPUInfo._L2.szSize, "%d KB", ecxreg >> 16 );
				switch ( (ecxreg >> 12) & 0xF )
				{
				case 1:
					mCPUInfo._L2.nAssociativeWays = 1;
					break;
				case 2:
					mCPUInfo._L2.nAssociativeWays = 2;
					break;
				case 4:
					mCPUInfo._L2.nAssociativeWays = 4;
					break;
				case 6:
					mCPUInfo._L2.nAssociativeWays = 8;
					break;
				case 8:
					mCPUInfo._L2.nAssociativeWays = 16;
					break;
				case 0xF:
					mCPUInfo._L2.nAssociativeWays = (unsigned int) -1;
					break;
				default:
					mCPUInfo._L2.nAssociativeWays = 0;
					break;
				}
				mCPUInfo._L2.nLineSize = ecxreg & 0xFF;
			}
		}
		else
		{
			_GetStandardProcessorConfiguration();
		}

		_TranslateProcessorConfiguration();

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� Intel ��������Ϣ
	bool ProcessorInfo::_AnalyzeIntelProcessor()
	{
		unsigned long eaxreg, ebxreg, edxreg;

		//��� CPUID ָ������򷵻�
		if( !_CheckCPUIDPresence() )
			return false;

		//��ȡ���� CPUID ָ��
		__asm
		{
			mov eax, 1;
			cpuid
			mov eaxreg, eax;
			mov ebxreg, ebx;
			mov edxreg, edx;
		}

		//��ȡ�ͺţ�model����ϵ�У�family�����ΰ汾��stepping�������ͣ�type�����̱��ţ�brand id����
		mCPUInfo.nStepping = eaxreg & 0xF;
		mCPUInfo.nModel    = (eaxreg >> 4) & 0xF;
		mCPUInfo.nFamily   = (eaxreg >> 8) & 0xF;
		mCPUInfo.nType     = (eaxreg >> 12) & 0x3;
		mCPUInfo.nBrandID  = ebxreg & 0xF;

		//���� CPU �����ַ���
		switch (mCPUInfo.nType)
		{
		case 0:
			strcpy( mCPUInfo.szType, "ԭʼ OEM" );
			strcpy( mCPUName, mCPUInfo.szType);
			strcat( mCPUName, " " );
			break;
		case 1:			// Type = 1:  ��Ƶ
			strcpy( mCPUInfo.szType, "��Ƶ" );
			strcpy( mCPUName, mCPUInfo.szType);
			strcat( mCPUName, " " );
			break;
		case 2:			// Type = 2:  ��Ƶ
			strcpy( mCPUInfo.szType, "��Ƶ" );
			strcpy( mCPUName, mCPUInfo.szType);
			strcat( mCPUName, " " );
			break;
		case 3:			// Type = 3:  ����
			strcpy( mCPUInfo.szType, "����" );
			break;
		default:
			strcpy( mCPUInfo.szType, "δ֪" );
			break;
		}

		//�����̱�
		switch (mCPUInfo.nBrandID)
		{
		case 0:			// Brand id = 0:  ��֧��
			strcpy( mCPUInfo.szBrandID, "Not supported" );
			break;
		case 1:			// Brand id = 1:  Intel Celeron (0.18 ΢��) ������
			strcpy( mCPUInfo.szBrandID, "0.18 ΢�� Intel Celeron" );
			break;
		case 2:			// Brand id = 2:  Intel Pentium III (0.18 ΢��) ������
			strcpy( mCPUInfo.szBrandID, "0.18 ΢�� Intel Pentium III" );
			break;
		case 3:			// Brand id = 3:  Model dependent
			if (mCPUInfo.nModel == 6)
				strcpy( mCPUInfo.szBrandID, "0.13 ΢�� Intel Celeron" );
			else
				strcpy( mCPUInfo.szBrandID, "0.18 ΢�� Intel Pentium III Xeon" );
			break;
		case 4:			// Brand id = 4:  Intel Pentium III Tualatin (0.13 ΢��) ������
			strcpy( mCPUInfo.szBrandID, "0.13 ΢�� Intel Pentium III" );
			break;
		case 6:			// Brand id = 6:  Intel Pentium III mobile (0.13 ΢��) ������
			strcpy( mCPUInfo.szBrandID, "0.13 ΢�� Intel Pentium III mobile" );
			break;
		case 7:			// Brand id = 7:  Intel Celeron mobile (0.13 ΢��) ������
			strcpy( mCPUInfo.szBrandID, "0.13 ΢�� Intel Celeron mobile" );
			break;
		case 8:			// Brand id = 8:  Intel Pentium 4 Willamette (0.18 ΢��) ������
			strcpy( mCPUInfo.szBrandID, "0.18 ΢�� Intel Pentium 4" );
			break;
		case 9:			// Brand id = 9:  Intel Pentium 4 Northwood (0.13 ΢��) ������
			strcpy( mCPUInfo.szBrandID, "0.13 ΢�� Intel Pentium 4" );
			break;
		case 0xA:		// Brand id = 0xA:  Intel Pentium 4 Northwood (0.13 ΢�� ������) 
			strcpy( mCPUInfo.szBrandID, "0.13 ΢�� Intel Pentium 4" );
			break;
		case 0xB:		// Brand id = 0xB:  Intel Pentium 4 Northwood Xeon (0.13 ΢�� ������)
			strcpy( mCPUInfo.szBrandID, "0.13 ΢�� Intel Pentium 4 Xeon" );
			break;
		case 0xE:		// Brand id = 0xE:  Intel Pentium 4 Willamette Xeon (0.18 ΢�� ������)
			strcpy( mCPUInfo.szBrandID, "0.18 ΢�� Intel Pentium 4 Xeon" );
			break;
		default:		// Should be never called, but sure is sure
			strcpy( mCPUInfo.szBrandID, "δ֪" );
			break;
		}

		//���� CPU ϵ��
		switch (mCPUInfo.nFamily)
		{
		case 3:			// Family = 3:  i386 (80386) ϵ��
			strcpy( mCPUInfo.szFamily, "Intel i386" );
			break;
		case 4:			// Family = 4:  i486 (80486) ϵ��
			strcpy( mCPUInfo.szFamily, "Intel i486" );
			break;
		case 5:			// Family = 5:  Pentium (80586) ϵ��
			strcpy( mCPUInfo.szFamily, "Intel Pentium" );
			break;
		case 6:			// Family = 6:  Pentium Pro (80686) ϵ��
			strcpy( mCPUInfo.szFamily, "Intel Pentium Pro" );
			break;
		case 15:		// Family = 15:  ��չϵ��

			mCPUInfo.nExtendedFamily = (eaxreg >> 20) & 0xFF;
			switch (mCPUInfo.nExtendedFamily)
			{
			case 0:			// Family = 15, Ext. Family = 0:  Pentium 4 ϵ��
				strcpy( mCPUInfo.szFamily, "Intel Pentium 4" );
				break;
			case 1:			// Family = 15, Ext. Family = 1:  McKinley (64-bit) ϵ��
				strcpy( mCPUInfo.szFamily, "Intel McKinley (IA-64)" );
				break;
			default:
				strcpy( mCPUInfo.szFamily, "δ֪ Intel Pentium 4+" );
				break;
			}
			break;
		default:
			strcpy( mCPUInfo.szFamily, "δ֪" );
			break;
		}

		//���� CPU �ͺ�
		switch (mCPUInfo.nFamily)
		{
		case 3:			// i386 (80386) ϵ��
			strcpy( mCPUInfo.szModel, "δ֪ Intel i386" );
			strcat( mCPUName, "Intel i386" );
			break;
		case 4:			// i486 (80486) ϵ��
			switch (mCPUInfo.nModel)
			{
			case 0:			// Model = 0:  i486 DX-25/33 �ͺ�
				strcpy( mCPUInfo.szModel, "Intel i486 DX-25/33" );
				strcat( mCPUName, "Intel i486 DX-25/33" );
				break;
			case 1:			// Model = 1:  i486 DX-50 �ͺ�
				strcpy( mCPUInfo.szModel, "Intel i486 DX-50" );
				strcat( mCPUName, "Intel i486 DX-50" );
				break;
			case 2:			// Model = 2:  i486 SX �ͺ�
				strcpy( mCPUInfo.szModel, "Intel i486 SX" );
				strcat( mCPUName, "Intel i486 SX" );
				break;
			case 3:			// Model = 3:  i486 DX2 ��ʹ�� i487 ����Э�������� �ͺ�
				strcpy( mCPUInfo.szModel, "Intel i486 487/DX2" );
				strcat( mCPUName, "Intel i486 DX2 ʹ�� i487 ����Э������" );
				break;
			case 4:			// Model = 4:  i486 SL �ͺ�
				strcpy( mCPUInfo.szModel, "Intel i486 SL" );
				strcat( mCPUName, "Intel i486 SL" );
				break;
			case 5:			// Model = 5:  i486 SX2 �ͺ�
				strcpy( mCPUInfo.szModel, "Intel i486 SX2" );
				strcat( mCPUName, "Intel i486 SX2" );
				break;
			case 7:			// Model = 7:  i486 ��д��ǿ DX2 �ͺ�
				strcpy( mCPUInfo.szModel, "Intel i486 ��д��ǿ DX2" );
				strcat( mCPUName, "Intel i486 ��д��ǿ DX2" );
				break;
			case 8:			// Model = 8:  i486 DX4 �ͺ�
				strcpy( mCPUInfo.szModel, "Intel i486 DX4" );
				strcat( mCPUName, "Intel i486 DX4" );
				break;
			case 9:			// Model = 9:  i486 ��д��ǿ DX4 �ͺ�
				strcpy( mCPUInfo.szModel, "Intel i486 ��д��ǿ DX4" );
				strcat( mCPUName, "Intel i486 DX4" );
				break;
			default:		// ...
				strcpy( mCPUInfo.szModel, "δ֪ Intel i486" );
				strcat( mCPUName, "Intel i486 (δ֪�ͺ�)" );
				break;
			}
			break;
		case 5:			// Pentium (80586) ϵ��
			switch (mCPUInfo.nModel)
			{
			case 0:			// Model = 0:  Pentium (P5 A-Step) �ͺ�
				strcpy( mCPUInfo.szModel, "Intel Pentium (P5 A-Step)" );
				strcat( mCPUName, "Intel Pentium (P5 A-Step ����)" );
				break;
			case 1:			// Model = 1:  Pentium 60/66 �ͺ�
				strcpy( mCPUInfo.szModel, "Intel Pentium 60/66 (P5)" );
				strcat( mCPUName, "Intel Pentium 60/66 (P5 ����)" );
				break;
			case 2:			// Model = 2:  Pentium 75-200 (P54C) �ͺ�
				strcpy( mCPUInfo.szModel, "Intel Pentium 75-200 (P54C)" );
				strcat( mCPUName, "Intel Pentium 75-200 (P54C ����)" );
				break;
			case 3:			// Model = 3:  486 ϵͳʹ�õ� Pentium ��Ƶ�������ͺ�
				strcpy( mCPUInfo.szModel, "Intel Pentium 486 ϵͳ (P24T ��Ƶ)" );
				strcat( mCPUName, "486 ϵͳʹ�õ� Intel Pentium (P24T ���ĳ�Ƶ)" );
				break;
			case 4:			// Model = 4:  Pentium MMX �ͺ�
				strcpy( mCPUInfo.szModel, "Intel Pentium MMX (P55C)" );
				strcat( mCPUName, "Intel Pentium MMX (P55C ����)" );
				break;
			case 7:			// Model = 7:  Pentium �ͺ�
				strcpy( mCPUInfo.szModel, "Intel Pentium (P54C)" );
				strcat( mCPUName, "Intel Pentium (P54C ����)" );
				break;
			case 8:			// Model = 8:  Pentium MMX (0.25 ΢��) �ͺ�
				strcpy( mCPUInfo.szModel, "Intel Pentium MMX (P55C), 0.25 ΢��" );
				strcat( mCPUName, "Intel Pentium MMX (P55C ����), 0.25 ΢��" );
				break;
			default:		// ...
				strcpy( mCPUInfo.szModel, "δ֪ Intel Pentium" );
				strcat( mCPUName, "Intel Pentium (δ֪ P5 �ͺ�)" );
				break;
			}
			break;
		case 6:			// Pentium Pro (80686) ϵ��
			switch (mCPUInfo.nModel)
			{
			case 0:			// Model = 0:  Pentium Pro (P6 A-Step) �ͺ�
				strcpy( mCPUInfo.szModel, "Intel Pentium Pro (P6 A-Step)" );
				strcat( mCPUName, "Intel Pentium Pro (P6 A-Step ����)" );
				break;
			case 1:			// Model = 1:  Pentium Pro
				strcpy( mCPUInfo.szModel, "Intel Pentium Pro (P6)" );
				strcat( mCPUName, "Intel Pentium Pro (P6 ����)" );
				break;
			case 3:			// Model = 3:  Pentium II (66 MHz FSB ) �ͺ�
				strcpy( mCPUInfo.szModel, "Intel Pentium II Model 3, 0.28 ΢��" );
				strcat( mCPUName, "Intel Pentium II (Model 3 ����, 0.28 ΢��)" );
				break;
			case 5:			// Model = 5:  Pentium II/Xeon/Celeron (0.25 ΢��) �ͺ�
				strcpy( mCPUInfo.szModel, "Intel Pentium II Model 5/Xeon/Celeron, 0.25 ΢��" );
				strcat( mCPUName, "Intel Pentium II/Xeon/Celeron (Model 5 ����, 0.25 ΢��)" );
				break;
			case 6:			// Model = 6:  Celoron (���ö�������) �ͺ�
				strcpy( mCPUInfo.szModel, "Intel Celeron - ���ö�������" );
				strcat( mCPUName, "Intel Celeron - ���ö�������" );
				break;
			case 7:			// Model = 7:  Pentium III/Xeon (���ö�������) �ͺ�
				strcpy( mCPUInfo.szModel, "Intel Pentium III/Pentium III Xeon - ���ö�������, 0.25 ΢��" );
				strcat( mCPUName, "Intel Pentium III/Pentium III Xeon (0.25 ΢��) ���ö�������" );
				break;
			case 8:			// Model = 8:  Pentium III/Xeon/Celeron (256 KB ���ö�������) �ͺ�
				strcpy( mCPUInfo.szModel, "Intel Pentium III/Celeron/Pentium III Xeon - ���ö�������, 0.18 ΢��" );
				// We want to know it exactly:
				switch (mCPUInfo.nBrandID)
				{
				case 1:			// Model = 8, Brand id = 1:  Celeron (���ö�������) �ͺ�
					strcat( mCPUName, "Intel Celeron (0.18 ΢��) ���ö�������" );
					break;
				case 2:			// Model = 8, Brand id = 2:  Pentium III (���ö�������) �ͺ�
					strcat( mCPUName, "Intel Pentium III (0.18 ΢��) ���ö�������" );
					break;
				case 3:			// Model = 8, Brand id = 3:  Pentium III Xeon (���ö�������) �ͺ�
					strcat( mCPUName, "Intel Pentium III Xeon (0.18 ΢��) ���ö�������" );
					break;
				default:		// ...?
					strcat( mCPUName, "Intel Pentium III core (unknown model, 0.18 ΢��) ���ö�������" );
					break;
				}
				break;
			case 0xA:		// Model = 0xA:  Pentium III/Xeon/Celeron (1 or 2 MB ���ö�������) �ͺ�
				strcpy( mCPUInfo.szModel, "Intel Pentium III/Celeron/Pentium III Xeon - ���ö�������, 0.18 ΢��" );
				// Exact detection:
				switch (mCPUInfo.nBrandID)
				{
				case 1:			// Model = 0xA, Brand id = 1:  Celeron (1 or 2 MB ���ö�������) �ͺ�
					strcat( mCPUName, "Intel Celeron (0.18 ΢��) ���ö�������" );
					break;
				case 2:			// Model = 0xA, Brand id = 2:  Pentium III (1 or 2 MB ���ö�������) �ͺ�
					strcat( mCPUName, "Intel Pentium III (0.18 ΢��) ���ö�������" );
					break;
				case 3:			// Model = 0xA, Brand id = 3:  Pentium III Xeon (1 or 2 MB ���ö�������) �ͺ�
					strcat( mCPUName, "Intel Pentium III Xeon (0.18 ΢��) ���ö�������" );
					break;
				default:
					strcat( mCPUName, "Intel Pentium III ���� (δ֪�ͺ�, 0.18 ΢��) ���ö�������" );
					break;
				}
				break;
			case 0xB:		// Model = 0xB: Pentium III/Xeon/Celeron (ͼ���ں���, ���ö�������) �ͺ�
				strcpy( mCPUInfo.szModel, "Intel Pentium III/Celeron/Pentium III Xeon - ���ö�������, 0.13 ΢��" );
				// Omniscient: ;-)
				switch (mCPUInfo.nBrandID)
				{
				case 3:			// Model = 0xB, Brand id = 3:  Celeron (ͼ���ں���) �ͺ�
					strcat( mCPUName, "Intel Celeron (ͼ���ں���, 0.13 ΢��) ���ö�������" );
					break;
				case 4:			// Model = 0xB, Brand id = 4:  Pentium III (ͼ���ں���) �ͺ�
					strcat( mCPUName, "Intel Pentium III (ͼ���ں���, 0.13 ΢��) ���ö�������" );
					break;
				case 7:			// Model = 0xB, Brand id = 7:  Celeron mobile (ͼ���ں���) �ͺ�
					strcat( mCPUName, "Intel Celeron mobile (ͼ���ں���, 0.13 ΢��) ���ö�������" );
					break;
				default:		// *bored*
					strcat( mCPUName, "Intel Pentium III ͼ���ں��� (δ֪�ͺ�, 0.13 ΢��) ���ö�������" );
					break;
				}
				break;
			default:
				strcpy( mCPUInfo.szModel, "δ֪ Intel Pentium Pro" );
				strcat( mCPUName, "Intel Pentium Pro (δ֪�ͺ�)" );
				break;
			}
			break;
		case 15:		//��չϵ��
			mCPUInfo.nExtendedModel = (eaxreg >> 16) & 0xFF;
			switch (mCPUInfo.nModel)
			{
			case 0:			// Model = 0:  Pentium 4 Willamette (A-Step) ����
				if ((mCPUInfo.nBrandID) == 8)	// Brand id = 8:  P4 Willamette
				{
					strcpy( mCPUInfo.szModel, "Intel Pentium 4 Willamette (A-Step)" );
					strcat( mCPUName, "Intel Pentium 4 Willamette ���� (A-Step)" );
				}
				else							// else Xeon
				{
					strcpy( mCPUInfo.szModel, "Intel Pentium 4 Willamette ���� Xeon (A-Step)" );
					strcat( mCPUName, "Intel Pentium 4 Willamette ���� Xeon (A-Step)" );
				}
				break;
			case 1:			// Model = 1:  Pentium 4 Willamette ����
				if ((mCPUInfo.nBrandID) == 8)	// Brand id = 8:  P4 Willamette
				{
					strcpy( mCPUInfo.szModel, "Intel Pentium 4 Willamette ����" );
					strcat( mCPUName, "Intel Pentium 4 Willamette ����" );
				}
				else							// else Xeon
				{
					strcpy( mCPUInfo.szModel, "Intel Pentium 4 Willamette ���� Xeon" );
					strcat( mCPUName, "Intel Pentium 4 Willamette ���� Xeon" );
				}
				break;
			case 2:			// Model = 2:  Pentium 4 Northwood ����
				if (((mCPUInfo.nBrandID) == 9) || ((mCPUInfo.nBrandID) == 0xA))		// P4 Willamette
				{
					strcpy( mCPUInfo.szModel, "Intel Pentium 4 Northwood ����" );
					strcat( mCPUName, "Intel Pentium 4 Northwood ����" );
				}
				else							// Xeon
				{
					strcpy( mCPUInfo.szModel, "Intel Pentium 4 Northwood ���� Xeon" );
					strcat( mCPUName, "Intel Pentium 4 Northwood ���� Xeon" );
				}
				break;
			default:
				strcpy( mCPUInfo.szModel, "δ֪ Intel Pentium 4" );
				strcat( mCPUName, "Intel Pentium 4 (δ֪�ͺ�)" );
				break;
			}
			break;
		default:
			strcpy( mCPUInfo.szModel, "δ֪ Intel model" );
			strcat( mCPUName, "Intel (δ֪�ͺ�)" );
			break;
		}


		if (mCPUInfo.MaxSupportedLevel >= 3)
		{
			unsigned long sig1, sig2, sig3;
			__asm
			{
				mov eax, 1;
				cpuid
				mov sig1, eax;
				mov eax, 3;
				cpuid
				mov sig2, ecx;
				mov sig3, edx;
			}

			sprintf( mCPUInfo.szProcessorSerial, "%04lX-%04lX-%04lX-%04lX-%04lX-%04lX",
				sig1 >> 16, sig1 & 0xFFFF, sig3 >> 16, sig3 & 0xFFFF, sig2 >> 16, sig2 & 0xFFFF );
		}
		else
		{
			strcpy( mCPUInfo.szProcessorSerial, "�޴��������к�" );
		}

		_GetStandardProcessorExtensions();

		_GetStandardProcessorConfiguration();
		_TranslateProcessorConfiguration();

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����δ֪��������Ϣ
	bool ProcessorInfo::_AnalyzeUnknownProcessor()
	{
		unsigned long eaxreg, ebxreg;

		//��� CPUID ָ������򷵻�
		if( !_CheckCPUIDPresence() )
			return false;

		//��ȡ���� CPUID ָ��
		__asm
		{
			mov eax, 1;
			cpuid
			mov eaxreg, eax;
			mov ebxreg, ebx;
		}

		//��ȡ�ͺţ�model����ϵ�У�family�����ΰ汾��stepping�������ͣ�type����
		mCPUInfo.nStepping = eaxreg & 0xF;
		mCPUInfo.nModel    = (eaxreg >> 4) & 0xF;
		mCPUInfo.nFamily   = (eaxreg >> 8) & 0xF;
		mCPUInfo.nType     = (eaxreg >> 12) & 0x3;

		mCPUInfo.nBrandID  = ebxreg & 0xF;

		_GetStandardProcessorExtensions();

		strcpy( mCPUName, "δ֪" );

		strcpy( mCPUInfo._Data.szTLB, "δ֪" );
		strcpy( mCPUInfo._Instruction.szTLB, "δ֪" );

		strcpy( mCPUInfo._Trace.szCache, "δ֪" );
		strcpy( mCPUInfo._L1.Data.szCache, "δ֪" );
		strcpy( mCPUInfo._L1.Instruction.szCache, "δ֪" );
		strcpy( mCPUInfo._L2.szCache, "δ֪" );
		strcpy( mCPUInfo._L3.szCache, "δ֪" );

		strcpy( mCPUInfo.szProcessorSerial, "δ֪/��֧��" );

		sprintf( mCPUInfo.szBrandID, "�̱��� %d", mCPUInfo.nBrandID );
		sprintf( mCPUInfo.szFamily, "ϵ�б�� %d", mCPUInfo.nFamily );
		sprintf( mCPUInfo.szModel, "�ͺű�� %d", mCPUInfo.nModel );

		//��� CPU ����
		switch (mCPUInfo.nType)
		{
		case 0:
			strcpy( mCPUInfo.szType, "ԭʼ OEM" );
			break;
		case 1:
			strcpy( mCPUInfo.szType, "��Ƶ" );
			break;
		case 2:
			strcpy( mCPUInfo.szType, "��Ƶ" );
			break;
		case 3:
			strcpy( mCPUInfo.szType, "����" );
			break;
		default:
			strcpy( mCPUInfo.szType, "δ֪" );
			break;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��� CPUID ָ���Ƿ����
	bool ProcessorInfo::_CheckCPUIDPresence()
	{
		unsigned long BitChanged;

		__asm
		{
			pushfd;
			pop eax;
			mov ebx, eax;
			xor eax, 0x00200000;
			push eax;
			popfd;
			pushfd;
			pop eax;
			xor eax,ebx;
			mov BitChanged, eax;
		}

		return ( (BitChanged) ? true : false );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���봦����λ������Ϣ
	void ProcessorInfo::_DecodeProcessorConfiguration( unsigned int cfg )
	{
		cfg &= 0xFF;

		switch(cfg)
		{
		case 0:			// cfg = 0:  δʹ��
			break;
		case 0x1:		// cfg = 0x1:  ���� TLB ,4 KB ҳ, 4 ·, 32 ���
			mCPUInfo._Instruction.bPresent = true;
			strcpy( mCPUInfo._Instruction.szPageSize, "4 KB" );
			mCPUInfo._Instruction.nAssociativeWays = 4;
			mCPUInfo._Instruction.nEntries = 32;
			break;
		case 0x2:		// cfg = 0x2:  ���� TLB ,4 MB ҳ, ��ȫ����, 2 ���
			mCPUInfo._Instruction.bPresent = true;
			strcpy( mCPUInfo._Instruction.szPageSize, "4 MB" );
			mCPUInfo._Instruction.nAssociativeWays = 4;
			mCPUInfo._Instruction.nEntries = 2;
			break;
		case 0x3:		// cfg = 0x3:  ���� TLB ,4 KB ҳ, 4 ·, 64 ���
			mCPUInfo._Data.bPresent = true;
			strcpy( mCPUInfo._Data.szPageSize, "4 KB" );
			mCPUInfo._Data.nAssociativeWays = 4;
			mCPUInfo._Data.nEntries = 64;
			break;
		case 0x4:		// cfg = 0x4:  ���� TLB ,4 MB ҳ, 4 ·, 8 ���
			mCPUInfo._Data.bPresent = true;
			strcpy( mCPUInfo._Data.szPageSize, "4 MB" );
			mCPUInfo._Data.nAssociativeWays = 4;
			mCPUInfo._Data.nEntries = 8;
			break;
		case 0x6:		// cfg = 0x6:  ����һ������, 8 KB, 4 ·, 32 �ֽ���·
			mCPUInfo._L1.Instruction.bPresent = true;
			strcpy( mCPUInfo._L1.Instruction.szSize, "8 KB" );
			mCPUInfo._L1.Instruction.nAssociativeWays = 4;
			mCPUInfo._L1.Instruction.nLineSize = 32;
			break;
		case 0x8:		// cfg = 0x8:  ����һ������, 16 KB, 4 ·, 32 �ֽ���·
			mCPUInfo._L1.Instruction.bPresent = true;
			strcpy( mCPUInfo._L1.Instruction.szSize, "16 KB" );
			mCPUInfo._L1.Instruction.nAssociativeWays = 4;
			mCPUInfo._L1.Instruction.nLineSize = 32;
			break;
		case 0xA:		// cfg = 0xA:  ����һ������, 8 KB, 2 ·, 32 �ֽ���·
			mCPUInfo._L1.Data.bPresent = true;
			strcpy( mCPUInfo._L1.Data.szSize, "8 KB" );
			mCPUInfo._L1.Data.nAssociativeWays = 2;
			mCPUInfo._L1.Data.nLineSize = 32;
			break;
		case 0xC:		// cfg = 0xC:  ����һ������, 16 KB, 4 ·, 32 �ֽ���·
			mCPUInfo._L1.Data.bPresent = true;
			strcpy( mCPUInfo._L1.Data.szSize, "16 KB" );
			mCPUInfo._L1.Data.nAssociativeWays = 4;
			mCPUInfo._L1.Data.nLineSize = 32;
			break;
		case 0x22:		// cfg = 0x22:  �����������������, 512 KB, 4 ·, 64 �ֽ���·, �ѷ���
			mCPUInfo._L3.bPresent = true;
			strcpy( mCPUInfo._L3.szSize, "512 KB" );
			mCPUInfo._L3.nAssociativeWays = 4;
			mCPUInfo._L3.nLineSize = 64;
			mCPUInfo._L3.bSectored = true;
			break;
		case 0x23:		// cfg = 0x23:  �����������������, 1024 KB, 8 ·, 64 �ֽ���·, �ѷ���
			mCPUInfo._L3.bPresent = true;
			strcpy( mCPUInfo._L3.szSize, "1024 KB" );
			mCPUInfo._L3.nAssociativeWays = 8;
			mCPUInfo._L3.nLineSize = 64;
			mCPUInfo._L3.bSectored = true;
			break;
		case 0x25:		// cfg = 0x25:  �����������������, 2048 KB, 8 ·, 64 �ֽ���·, �ѷ���
			mCPUInfo._L3.bPresent = true;
			strcpy( mCPUInfo._L3.szSize, "2048 KB" );
			mCPUInfo._L3.nAssociativeWays = 8;
			mCPUInfo._L3.nLineSize = 64;
			mCPUInfo._L3.bSectored = true;
			break;
		case 0x29:		// cfg = 0x29:  �����������������, 4096 KB, 8 ·, 64 �ֽ���·, �ѷ���
			mCPUInfo._L3.bPresent = true;
			strcpy( mCPUInfo._L3.szSize, "4096 KB" );
			mCPUInfo._L3.nAssociativeWays = 8;
			mCPUInfo._L3.nLineSize = 64;
			mCPUInfo._L3.bSectored = true;
			break;
		case 0x40:		// cfg = 0x40:  δ���ɶ�������(P6 ����)����������(P4 ����)
			break;
		case 0x41:		// cfg = 0x41:  ��������ݶ�������, 128 KB, 4 ·, 32 �ֽ���·
			mCPUInfo._L2.bPresent = true;
			strcpy( mCPUInfo._L2.szSize, "128 KB" );
			mCPUInfo._L2.nAssociativeWays = 4;
			mCPUInfo._L2.nLineSize = 32;
			break;
		case 0x42:		// cfg = 0x42:  ��������ݶ�������, 256 KB, 4 ·, 32 �ֽ���·
			mCPUInfo._L2.bPresent = true;
			strcpy( mCPUInfo._L2.szSize, "256 KB" );
			mCPUInfo._L2.nAssociativeWays = 4;
			mCPUInfo._L2.nLineSize = 32;
			break;
		case 0x43:		// cfg = 0x43:  ��������ݶ�������, 512 KB, 4 ·, 32 �ֽ���·
			mCPUInfo._L2.bPresent = true;
			strcpy( mCPUInfo._L2.szSize, "512 KB" );
			mCPUInfo._L2.nAssociativeWays = 4;
			mCPUInfo._L2.nLineSize = 32;
			break;
		case 0x44:		// cfg = 0x44:  ��������ݶ�������, 1024 KB, 4 ·, 32 �ֽ���·
			mCPUInfo._L2.bPresent = true;
			strcpy( mCPUInfo._L2.szSize, "1 MB" );
			mCPUInfo._L2.nAssociativeWays = 4;
			mCPUInfo._L2.nLineSize = 32;
			break;
		case 0x45:		// cfg = 0x45:  ��������ݶ�������, 2048 KB, 4 ·, 32 �ֽ���·
			mCPUInfo._L2.bPresent = true;
			strcpy( mCPUInfo._L2.szSize, "2 MB" );
			mCPUInfo._L2.nAssociativeWays = 4;
			mCPUInfo._L2.nLineSize = 32;
			break;
		case 0x50:		// cfg = 0x50:  ���� TLB ,4 KB / 4 MB / 2 MB ҳ, ��ȫ����, 64 ���
			mCPUInfo._Instruction.bPresent = true;
			strcpy( mCPUInfo._Instruction.szPageSize, "4 KB / 2 MB / 4 MB" );
			mCPUInfo._Instruction.nAssociativeWays = (unsigned int) -1;
			mCPUInfo._Instruction.nEntries = 64;
			break;
		case 0x51:		// cfg = 0x51:  ���� TLB ,4 KB / 4 MB / 2 MB ҳ, ��ȫ����, 128 ���
			mCPUInfo._Instruction.bPresent = true;
			strcpy( mCPUInfo._Instruction.szPageSize, "4 KB / 2 MB / 4 MB" );
			mCPUInfo._Instruction.nAssociativeWays = (unsigned int) -1;
			mCPUInfo._Instruction.nEntries = 128;
			break;
		case 0x52:		// cfg = 0x52:  ���� TLB ,4 KB / 4 MB / 2 MB ҳ, ��ȫ����, 256 ���
			mCPUInfo._Instruction.bPresent = true;
			strcpy( mCPUInfo._Instruction.szPageSize, "4 KB / 2 MB / 4 MB" );
			mCPUInfo._Instruction.nAssociativeWays = (unsigned int) -1;
			mCPUInfo._Instruction.nEntries = 256;
			break;
		case 0x5B:		// cfg = 0x5B:  ���� TLB ,4 KB / 4 MB ҳ, ��ȫ����, 64 ���
			mCPUInfo._Data.bPresent = true;
			strcpy( mCPUInfo._Data.szPageSize, "4 KB / 4 MB" );
			mCPUInfo._Data.nAssociativeWays = (unsigned int) -1;
			mCPUInfo._Data.nEntries = 64;
			break;
		case 0x5C:		// cfg = 0x5C:  ���� TLB ,4 KB / 4 MB ҳ, ��ȫ����, 128 ���
			mCPUInfo._Data.bPresent = true;
			strcpy( mCPUInfo._Data.szPageSize, "4 KB / 4 MB" );
			mCPUInfo._Data.nAssociativeWays = (unsigned int) -1;
			mCPUInfo._Data.nEntries = 128;
			break;
		case 0x5d:		// cfg = 0x5D:  ���� TLB ,4 KB / 4 MB ҳ, ��ȫ����, 256 ���
			mCPUInfo._Data.bPresent = true;
			strcpy( mCPUInfo._Data.szPageSize, "4 KB / 4 MB" );
			mCPUInfo._Data.nAssociativeWays = (unsigned int) -1;
			mCPUInfo._Data.nEntries = 256;
			break;
		case 0x66:		// cfg = 0x66:  ����һ������, 8 KB, 4 ·, 64 �ֽ���·, �ѷ���
			mCPUInfo._L1.Data.bPresent = true;
			strcpy( mCPUInfo._L1.Data.szSize, "8 KB" );
			mCPUInfo._L1.Data.nAssociativeWays = 4;
			mCPUInfo._L1.Data.nLineSize = 64;
			break;
		case 0x67:		// cfg = 0x67:  ����һ������, 16 KB, 4 ·, 64 �ֽ���·, �ѷ���
			mCPUInfo._L1.Data.bPresent = true;
			strcpy( mCPUInfo._L1.Data.szSize, "16 KB" );
			mCPUInfo._L1.Data.nAssociativeWays = 4;
			mCPUInfo._L1.Data.nLineSize = 64;
			break;
		case 0x68:		// cfg = 0x68:  ����һ������, 32 KB, 4 ·, 64 �ֽ���·, �ѷ���
			mCPUInfo._L1.Data.bPresent = true;
			strcpy( mCPUInfo._L1.Data.szSize, "32 KB" );
			mCPUInfo._L1.Data.nAssociativeWays = 4;
			mCPUInfo._L1.Data.nLineSize = 64;
			break;
		case 0x70:		// cfg = 0x70:  traceһ������, 12 K-micro-ops, 4 ·
			mCPUInfo._Trace.bPresent = true;
			strcpy( mCPUInfo._Trace.szSize, "12 K-micro-ops" );
			mCPUInfo._Trace.nAssociativeWays = 4;
			break;
		case 0x71:		// cfg = 0x71:  traceһ������, 16 K-micro-ops, 4 ·
			mCPUInfo._Trace.bPresent = true;
			strcpy( mCPUInfo._Trace.szSize, "16 K-micro-ops" );
			mCPUInfo._Trace.nAssociativeWays = 4;
			break;
		case 0x72:		// cfg = 0x72:  traceһ������, 32 K-micro-ops, 4 ·
			mCPUInfo._Trace.bPresent = true;
			strcpy( mCPUInfo._Trace.szSize, "32 K-micro-ops" );
			mCPUInfo._Trace.nAssociativeWays = 4;
			break;
		case 0x79:		// cfg = 0x79:  ��������ݶ�������, 128 KB, 8 ·, 64 �ֽ���·, �ѷ���
			mCPUInfo._L2.bPresent = true;
			strcpy( mCPUInfo._L2.szSize, "128 KB" );
			mCPUInfo._L2.nAssociativeWays = 8;
			mCPUInfo._L2.nLineSize = 64;
			mCPUInfo._L2.bSectored = true;
			break;
		case 0x7A:		// cfg = 0x7A:  ��������ݶ�������, 256 KB, 8 ·, 64 �ֽ���·, �ѷ���
			mCPUInfo._L2.bPresent = true;
			strcpy( mCPUInfo._L2.szSize, "256 KB" );
			mCPUInfo._L2.nAssociativeWays = 8;
			mCPUInfo._L2.nLineSize = 64;
			mCPUInfo._L2.bSectored = true;
			break;
		case 0x7B:		// cfg = 0x7B:  ��������ݶ�������, 512 KB, 8 ·, 64 �ֽ���·, �ѷ���
			mCPUInfo._L2.bPresent = true;
			strcpy( mCPUInfo._L2.szSize, "512 KB" );
			mCPUInfo._L2.nAssociativeWays = 8;
			mCPUInfo._L2.nLineSize = 64;
			mCPUInfo._L2.bSectored = true;
			break;
		case 0x7C:		// cfg = 0x7C:  ��������ݶ�������, 1024 KB, 8 ·, 64 �ֽ���·, �ѷ���
			mCPUInfo._L2.bPresent = true;
			strcpy( mCPUInfo._L2.szSize, "1 MB" );
			mCPUInfo._L2.nAssociativeWays = 8;
			mCPUInfo._L2.nLineSize = 64;
			mCPUInfo._L2.bSectored = true;
			break;
		case 0x81:		// cfg = 0x81:  ��������ݶ�������, 128 KB, 8 ·, 32 �ֽ���·
			mCPUInfo._L2.bPresent = true;
			strcpy( mCPUInfo._L2.szSize, "128 KB" );
			mCPUInfo._L2.nAssociativeWays = 8;
			mCPUInfo._L2.nLineSize = 32;
			break;
		case 0x82:		// cfg = 0x82:  ��������ݶ�������, 256 KB, 8 ·, 32 �ֽ���·
			mCPUInfo._L2.bPresent = true;
			strcpy( mCPUInfo._L2.szSize, "256 KB" );
			mCPUInfo._L2.nAssociativeWays = 8;
			mCPUInfo._L2.nLineSize = 32;
			break;
		case 0x83:		// cfg = 0x83:  ��������ݶ�������, 512 KB, 8 ·, 32 �ֽ���·
			mCPUInfo._L2.bPresent = true;
			strcpy( mCPUInfo._L2.szSize, "512 KB" );
			mCPUInfo._L2.nAssociativeWays = 8;
			mCPUInfo._L2.nLineSize = 32;
			break;
		case 0x84:		// cfg = 0x84:  ��������ݶ�������, 1024 KB, 8 ·, 32 �ֽ���·
			mCPUInfo._L2.bPresent = true;
			strcpy( mCPUInfo._L2.szSize, "1 MB" );
			mCPUInfo._L2.nAssociativeWays = 8;
			mCPUInfo._L2.nLineSize = 32;
			break;
		case 0x85:		// cfg = 0x85:  ��������ݶ�������, 2048 KB, 8 ·, 32 �ֽ���·
			mCPUInfo._L2.bPresent = true;
			strcpy( mCPUInfo._L2.szSize, "2 MB" );
			mCPUInfo._L2.nAssociativeWays = 8;
			mCPUInfo._L2.nLineSize = 32;
			break;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���봦����������Ϣ
	void ProcessorInfo::_TranslateProcessorConfiguration()
	{
		TranslateTLB( &mCPUInfo._Data );
		TranslateTLB( &mCPUInfo._Instruction );

		TranslateCache( &mCPUInfo._Trace );

		TranslateCache( &mCPUInfo._L1.Instruction );
		TranslateCache( &mCPUInfo._L1.Data );
		TranslateCache( &mCPUInfo._L2 );
		TranslateCache( &mCPUInfo._L3 );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��׼������������Ϣ
	void ProcessorInfo::_GetStandardProcessorConfiguration()
	{
		unsigned long eaxreg, ebxreg, ecxreg, edxreg;

		//��� CPUID ָ������򷵻�
		if( !_CheckCPUIDPresence() )
			return;

		if (mCPUInfo.MaxSupportedLevel >= 2)
		{
			unsigned long count, num = 255;
			for (count = 0; count < num; count++)
			{
				__asm
				{
					mov eax, 2;
					cpuid
					mov eaxreg, eax;
					mov ebxreg, ebx;
					mov ecxreg, ecx;
					mov edxreg, edx;
				}

				num = eaxreg & 0xFF;

				_DecodeProcessorConfiguration(eaxreg >> 8);
				_DecodeProcessorConfiguration(eaxreg >> 16);
				_DecodeProcessorConfiguration(eaxreg >> 24);

				if ((ebxreg & 0x80000000) == 0)
				{
					_DecodeProcessorConfiguration(ebxreg);
					_DecodeProcessorConfiguration(ebxreg >> 8);
					_DecodeProcessorConfiguration(ebxreg >> 16);
					_DecodeProcessorConfiguration(ebxreg >> 24);
				}
				if ((ecxreg & 0x80000000) == 0)
				{
					_DecodeProcessorConfiguration(ecxreg);
					_DecodeProcessorConfiguration(ecxreg >> 8);
					_DecodeProcessorConfiguration(ecxreg >> 16);
					_DecodeProcessorConfiguration(ecxreg >> 24);
				}
				if ((edxreg & 0x80000000) == 0)
				{
					_DecodeProcessorConfiguration(edxreg);
					_DecodeProcessorConfiguration(edxreg >> 8);
					_DecodeProcessorConfiguration(edxreg >> 16);
					_DecodeProcessorConfiguration(edxreg >> 24);
				}
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��׼��������չ��Ϣ
	void ProcessorInfo::_GetStandardProcessorExtensions()
	{
		unsigned long ebxreg, edxreg;

		//��� CPUID ָ������򷵻�
		if( !_CheckCPUIDPresence() )
			return;

		//���� CPUID ָ��
		__asm
		{
			mov eax, 1;
			cpuid
			mov ebxreg, ebx;
			mov edxreg, edx;
		}

		//����׼��������չ��Ϣλ
		mCPUInfo._Ext.FPU_FloatingPointUnit							= CheckBit(edxreg, 0);
		mCPUInfo._Ext.VME_Virtual8086ModeEnhancements				= CheckBit(edxreg, 1);
		mCPUInfo._Ext.DE_DebuggingExtensions						= CheckBit(edxreg, 2);
		mCPUInfo._Ext.PSE_PageSizeExtensions						= CheckBit(edxreg, 3);
		mCPUInfo._Ext.TSC_TimeStampCounter							= CheckBit(edxreg, 4);
		mCPUInfo._Ext.MSR_ModelSpecificRegisters					= CheckBit(edxreg, 5);
		mCPUInfo._Ext.PAE_PhysicalAddressExtension					= CheckBit(edxreg, 6);
		mCPUInfo._Ext.MCE_MachineCheckException						= CheckBit(edxreg, 7);
		mCPUInfo._Ext.CX8_COMPXCHG8B_Instruction						= CheckBit(edxreg, 8);
		mCPUInfo._Ext.APIC_AdvancedProgrammableInterruptController	= CheckBit(edxreg, 9);
		mCPUInfo._Ext.APIC_ID = (ebxreg >> 24) & 0xFF;
		mCPUInfo._Ext.SEP_FastSystemCall							= CheckBit(edxreg, 11);
		mCPUInfo._Ext.MTRR_MemoryTypeRangeRegisters					= CheckBit(edxreg, 12);
		mCPUInfo._Ext.PGE_PTE_GlobalFlag							= CheckBit(edxreg, 13);
		mCPUInfo._Ext.MCA_MachineCheckArchitecture					= CheckBit(edxreg, 14);
		mCPUInfo._Ext.CMOV_ConditionalMoveAndCompareInstructions		= CheckBit(edxreg, 15);
		mCPUInfo._Ext.FGPAT_PageAttributeTable						= CheckBit(edxreg, 16);
		mCPUInfo._Ext.PSE36_36bitPageSizeExtension					= CheckBit(edxreg, 17);
		mCPUInfo._Ext.PN_ProcessorSerialNumber						= CheckBit(edxreg, 18);
		mCPUInfo._Ext.CLFSH_CFLUSH_Instruction						= CheckBit(edxreg, 19);
		mCPUInfo._Ext.CLFLUSH_InstructionCacheLineSize = (ebxreg >> 8) & 0xFF;
		mCPUInfo._Ext.DS_DebugStore									= CheckBit(edxreg, 21);
		mCPUInfo._Ext.ACPI_ThermalMonitorAndClockControl			= CheckBit(edxreg, 22);
		mCPUInfo._Ext.MMX_MultimediaExtensions						= CheckBit(edxreg, 23);
		mCPUInfo._Ext.FXSR_FastStreamingSIMD_ExtensionsSaveRestore	= CheckBit(edxreg, 24);
		mCPUInfo._Ext.SSE_StreamingSIMD_Extensions					= CheckBit(edxreg, 25);
		mCPUInfo._Ext.SSE2_StreamingSIMD2_Extensions				= CheckBit(edxreg, 26);
		mCPUInfo._Ext.SS_SelfSnoop									= CheckBit(edxreg, 27);
		mCPUInfo._Ext.HT_HyperThreading								= CheckBit(edxreg, 28);
		mCPUInfo._Ext.HT_HyterThreadingSiblings = (ebxreg >> 16) & 0xFF;
		mCPUInfo._Ext.TM_ThermalMonitor								= CheckBit(edxreg, 29);
		mCPUInfo._Ext.IA64_Intel64BitArchitecture					= CheckBit(edxreg, 30);
	}
	//--------------------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------------------
	FKForceInline static char* TranslateAssociativeWays( unsigned int nWays, char* buf )
	{
		if( nWays == 0xFFFFFFFF )
		{
			strcpy( buf, "��ȫ����" );
		}
		else
		{
			if( nWays == 1 )
				strcpy( buf, "��·ֱ��ӳ��" );
			else if( nWays == 0 )
				strcpy( buf, "δ֪����·��" );
			else
				sprintf( buf, "%d ·����", nWays );
		}

		return buf;
	}
	//--------------------------------------------------------------------------------------------------------------
	FKForceInline static void TranslateTLB( ProcessorTLB* tlb )
	{
		char buf[64];

		//��⻺���Ƿ����
		if(tlb->bPresent)
		{
			sprintf( tlb->szTLB, "%s ҳ��С, %s, %d ���", tlb->szPageSize,
				TranslateAssociativeWays( tlb->nAssociativeWays, buf ), tlb->nEntries );
		}
		else
		{
			strcpy( tlb->szTLB, "��" );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	FKForceInline static void TranslateCache( ProcessorCache* cache )
	{
		char buf[64];

		//��⻺���Ƿ����
		if (cache->bPresent)
		{
			//�������������˵������
			sprintf( cache->szCache, "%s �����С, %s, %d �ֽ���·", cache->szSize,
				TranslateAssociativeWays( cache->nAssociativeWays, buf ), cache->nLineSize );
			if( cache->bSectored )
				strcat( cache->szCache, ", �ѷ���" );
		}
		else
		{
			strcpy( cache->szCache, "��" );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
