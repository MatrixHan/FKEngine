/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Timer
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
	//����һ���ӵ�ʱ���ڵ�ʱ��Ƶ�ʣ��𵴴���������
	__int64 Timer::m_sTimerFrequency = 0;

	//--------------------------------------------------------------------------------------------------------------
	Timer::Timer()
		: m_bIsPause	(false)
		, m_BeginTime	(0)
		, m_PauseTime	(0)
		, m_dwPrecision	(1000)
	{
		if( m_sTimerFrequency == 0 )
		{
			//���һ�����ڵ�ʱ��Ƶ�ʣ��𵴴�����
			LARGE_INTEGER LargeInt;
			if( QueryPerformanceFrequency( &LargeInt ) == TRUE )
			{
				m_sTimerFrequency = LargeInt.QuadPart;
			}
			else
			{
				Misc::ShowErrMsg( "Initialise timer failed." );
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	Timer::~Timer()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¿�ʼ��ʱ
	void FKFastcall Timer::Start()
	{
		//��õ�ǰʱ�䣨��ʱ��ʼʱ�䣩
		LARGE_INTEGER LargeInt;
		QueryPerformanceCounter( &LargeInt );
		m_BeginTime = LargeInt.QuadPart;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ʱʱ��
	//
	//����ֵ��	�Ӽ�ʱ��ʼ�����ô˺�����ʱ�䣨unsigned long ֵ��
	DWORD FKFastcall Timer::GetTime()
	{
		//��ʱ��ʼʱ���ȥ��ǰʱ��ó���ʱʱ��
		LARGE_INTEGER LargeInt;
		QueryPerformanceCounter( &LargeInt );
		return (DWORD)( ( LargeInt.QuadPart - m_BeginTime ) * m_dwPrecision / m_sTimerFrequency );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ʱʱ��
	//
	//��ʱ��λʱ��Ϊ�룬����ʼ��Ϊ΢�루�����֮һ�룩��
	//
	//����ֵ��	�Ӽ�ʱ��ʼ�����ô˺�����ʱ�䣨float ֵ��
	float FKFastcall Timer::GetTimeDouble()
	{
		LARGE_INTEGER LargeInt;
		QueryPerformanceCounter( &LargeInt );
		return (float)( ( LargeInt.QuadPart - m_BeginTime ) * 1000000 / m_sTimerFrequency ) / 1000000;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ͣ��ʱ
	void FKFastcall Timer::Pause()
	{
		LARGE_INTEGER LargeInt;

	#ifdef _DEBUG	//����ģʽʱ����ͣ��ʱ�ı�־����˫����ͣ
		if( !m_bIsPause )
		{
			//��ȡ��ͣʱ��ʱ��
			QueryPerformanceCounter( &LargeInt );
			m_PauseTime = LargeInt.QuadPart;
			m_bIsPause = true;
		}
		else
		{
			Misc::ShowErrMsg( "���ܶ�ͬһ����ʱ������������ͣ��ʱ��" );
		}
	#else
		//��ȡ��ͣʱ��ʱ��
		QueryPerformanceCounter( &LargeInt );
		m_PauseTime = LargeInt.QuadPart;
		m_bIsPause = true;
	#endif
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�Ƿ���ͣ�˼�ʱ
	bool FKFastcall Timer::IsPaused()
	{
		return m_bIsPause;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ͣ��ʱ
	void FKFastcall Timer::Resume()
	{
		LARGE_INTEGER LargeInt;

	#ifdef _DEBUG	//����ģʽʱ����ͣ��ʱ�ı�־����˫�س�����ͣ
		if( m_bIsPause )
		{
			//��ʱ��ʼʱ����ϴ���ͣ��������֮ͣ���ʱ��
			QueryPerformanceCounter( &LargeInt );
			m_BeginTime += LargeInt.QuadPart - m_PauseTime;
			m_bIsPause = false;
		}
		else
		{
			Misc::ShowErrMsg( "���ܶ�ͬһ����ʱ���������γ�����ͣ��ʱ��" );
		}
	#else
		//��ʱ��ʼʱ����ϴ���ͣ��������֮ͣ���ʱ��
		QueryPerformanceCounter( &LargeInt );
		m_BeginTime += LargeInt.QuadPart - m_PauseTime;
		m_bIsPause = false;
	#endif
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ʱ���ʽ
	//
	//dwPrecision��	ʱ���ʽֵ��Ĭ��ֵ1000�����ֵΪ 1000 �򷵻�ʱ��ֵ��λΪ���롣
	void __fastcall Timer::SetFormat( const DWORD dwPrecision )
	{
		m_dwPrecision = dwPrecision;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
