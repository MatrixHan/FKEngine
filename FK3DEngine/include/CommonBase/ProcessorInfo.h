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
*	�ļ�˵����	��������Ϣ��
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	struct ProcessorExtensions
	{
		bool			FPU_FloatingPointUnit;							//���㴦��Ԫ
		bool			VME_Virtual8086ModeEnhancements;				//���� 8086 ģʽ��ǿ
		bool			DE_DebuggingExtensions;							//��չ����ָ��
		bool			PSE_PageSizeExtensions;							//ҳ��С��չ
		bool			TSC_TimeStampCounter;							//ʱ�������
		bool			MSR_ModelSpecificRegisters;						//ģ��ϸ�ڼĴ���
		bool			PAE_PhysicalAddressExtension;					//�����ַ��չ
		bool			MCA_MachineCheckArchitecture;					//�������ܹ�
		bool			MCE_MachineCheckException;						//��������쳣
		bool			CX8_COMPXCHG8B_Instruction;						//COMPXCHG8B ָ��
		bool			APIC_AdvancedProgrammableInterruptController;	//�߼��ɱ���жϿ�����
		unsigned int	APIC_ID;										//�߼��ɱ���жϿ��������
		bool			SEP_FastSystemCall;								//����ϵͳ������
		bool			MTRR_MemoryTypeRangeRegisters;					//�ڴ����ͷ�Χ�Ĵ���
		bool			PGE_PTE_GlobalFlag;								//PTE ȫ�ֱ�־
		bool			CMOV_ConditionalMoveAndCompareInstructions;		//�������ݴ��ͺͱȽ�ָ�
		bool			FGPAT_PageAttributeTable;						//ҳ���Ա�
		bool			PSE36_36bitPageSizeExtension;					//36 λҳ��С��չ
		bool			PN_ProcessorSerialNumber;						//���������к�
		bool			CLFSH_CFLUSH_Instruction;						//CLFLUSH ָ��֧��
		unsigned int	CLFLUSH_InstructionCacheLineSize;				//CLFLUSH ָ����С
		bool			DS_DebugStore;									//���Դ洢��
		bool			ACPI_ThermalMonitorAndClockControl;				//�¶�̽��/ʱ�ӿ���
		bool			EMMX_MultimediaExtensions;						//��չ��ý��ָ�
		bool			MMX_MultimediaExtensions;						//��ý��ָ�
		bool			FXSR_FastStreamingSIMD_ExtensionsSaveRestore;	//���� SIMD ָ��洢/�ָ�
		bool			SSE_StreamingSIMD_Extensions;					//��������ָ���������չָ�
		bool			SSE2_StreamingSIMD2_Extensions;					//��������ָ���������չָ� 2
		bool			SS_SelfSnoop;									//��̽��
		bool			HT_HyperThreading;								//���߳�
		unsigned int	HT_HyterThreadingSiblings;						//���߳�
		bool			TM_ThermalMonitor;								//�¶�̽��
		bool			IA64_Intel64BitArchitecture;					//Intel 64 λ�ܹ�
		bool			_3DNOW_InstructionExtensions;					//3DNow! ָ�
		bool			_E3DNOW_InstructionExtensions;					//��ǿ 3DNow! ָ�
		bool			AA64_AMD64BitArchitecture;						//AMD 64 λ�ܹ�
	};
	//--------------------------------------------------------------------------------------------------------------
	struct ProcessorCache
	{
		bool			bPresent;						//�Ƿ����
		char			szSize[32];						//��С˵��
		unsigned int	nAssociativeWays;				//����·��
		unsigned int	nLineSize;						//��·��С
		bool			bSectored;						//�Ƿ��ѷ���
		char			szCache[128];					//����˵��
	};
	//--------------------------------------------------------------------------------------------------------------
	struct ProcessorL1Cache
	{
		ProcessorCache	Instruction;					//ָ���
		ProcessorCache	Data;							//���ݻ���
	};
	//--------------------------------------------------------------------------------------------------------------
	struct ProcessorTLB
	{
		bool			bPresent;						//�Ƿ����
		char			szPageSize[32];					//ҳ��С˵��
		unsigned int	nAssociativeWays;				//����·��
		unsigned int	nEntries;						//�����
		char			szTLB[128];						//����˵��
	};
	//--------------------------------------------------------------------------------------------------------------
	struct CPUInfo
	{
		char				szVendor[16];				//����˵��
		unsigned int		nFamily;					//ϵ��
		unsigned int		nExtendedFamily;			//��չϵ��
		char				szFamily[64];				//ϵ��˵��
		unsigned int		nModel;						//�ͺ�
		unsigned int		nExtendedModel;				//��չ�ͺ�
		char				szModel[128];				//�ͺ�˵��
		unsigned int		nStepping;					//�ΰ汾
		unsigned int		nType;						//����
		char				szType[64];					//����˵��
		unsigned int		nBrandID;					//�̱���
		char				szBrandID[64];				//�̱���˵��
		char				szProcessorSerial[64];		//���������к�
		unsigned long		MaxSupportedLevel;			//���֧�ֵȼ�
		unsigned long		MaxSupportedExtendedLevel;	//��չ���֧�ֵȼ�

		ProcessorExtensions	_Ext;
		ProcessorL1Cache	_L1;
		ProcessorCache		_L2;
		ProcessorCache		_L3;
		ProcessorCache		_Trace;
		ProcessorTLB		_Instruction;
		ProcessorTLB		_Data;
	};
	//--------------------------------------------------------------------------------------------------------------
	//��������Ϣ��
	class FK_DLL ProcessorInfo
	{
	public:
		static __int64		mqwFrequency;	// CPU Ƶ��
		static char			mCPUName[128];	// CPU ����
		static CPUInfo		mCPUInfo;		// CPU ��Ϣ

	public:
		//��ȡ CPU Ƶ��
		static __int64 GetCPUFrequency( unsigned int nMeasureTime );

		//��ȡ CPU ��Ϣ
		static const CPUInfo* GetCPUInfo();

		//��ȡ CPU ˵����Ϣ�ַ���
		static String GetCPUInfoText();

		//�� CPU ˵����Ϣд��ָ���ı��ļ�
		static bool WriteCPUInfoTextFile( const char* szFileName );

	protected:
		//���� AMD ��������Ϣ
		static bool _AnalyzeAMDProcessor();

		//���� Intel ��������Ϣ
		static bool _AnalyzeIntelProcessor();

		//����δ֪��������Ϣ
		static bool _AnalyzeUnknownProcessor();

		//��� CPUID ָ���Ƿ����
		static bool _CheckCPUIDPresence();

		//���봦����λ������Ϣ
		static void _DecodeProcessorConfiguration( unsigned int cfg );

		//���봦����������Ϣ
		static void _TranslateProcessorConfiguration();

		//��ȡ��׼������������Ϣ
		static void _GetStandardProcessorConfiguration();

		//��ȡ��׼��������չ��Ϣ
		static void _GetStandardProcessorExtensions();		
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
