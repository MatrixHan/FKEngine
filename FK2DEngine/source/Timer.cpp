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

#include "../include/Timer.h"
#include "../include/Exception.h"
#include <assert.h>
#include <windows.h>

//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	// �־��ȼ�ʱ
	//--------------------------------------------------------------------
	CTimer::CTimer()
		: m_dwStartTime ( 0 )
		, m_dwElapse ( 0 )
		, m_dwPauseTime ( 0 )
		, m_eState ( eTS_Stop )
	{

	}
	//--------------------------------------------------------------------
	CTimer::~CTimer()
	{

	}
	//--------------------------------------------------------------------
	unsigned int CTimer::GetTime()
	{
		if( m_eState == eTS_Stop )
		{
			return 0;
		}

		return ::GetTickCount() - m_dwStartTime;
	}
	//--------------------------------------------------------------------
	unsigned int CTimer::GetElapseTime()
	{
		if( m_eState == eTS_Stop )
		{
			return 0;
		}
		else if( m_eState == eTS_Pause )
		{
			return m_dwPauseTime - m_dwStartTime - m_dwElapse;
		}
		else
		{
			return ::GetTickCount() - m_dwStartTime - m_dwElapse;
		}
	}
	//--------------------------------------------------------------------
	void CTimer::Play()
	{
		if( m_eState == eTS_Running )
		{
			return;
		}
		else if( m_eState == eTS_Pause )
		{
			m_dwElapse += ::GetTickCount() - m_dwPauseTime;
			m_eState = eTS_Running;
		}
		else if( m_eState == eTS_Stop )
		{
			m_dwStartTime = ::GetTickCount();
			m_dwElapse = 0;
			m_eState = eTS_Running;
		}
	}
	//--------------------------------------------------------------------
	void CTimer::Pause()
	{
		if( m_eState != eTS_Running )
		{
			return;
		}

		m_dwPauseTime = ::GetTickCount();
		m_eState = eTS_Pause;
	}
	//--------------------------------------------------------------------
	void CTimer::Stop()
	{
		m_eState = eTS_Stop;
	}
	//--------------------------------------------------------------------
	bool CTimer::IsPause() const
	{
		return m_eState == eTS_Pause ? true : false;
	}
	//--------------------------------------------------------------------
	bool CTimer::IsStop() const
	{
		return m_eState == eTS_Stop ? true : false;
	}
	//--------------------------------------------------------------------
	// �߾��ȼ�ʱ��
	//--------------------------------------------------------------------
	__int64 CPreciseTimer::m_n64Freq = 0;
	//--------------------------------------------------------------------
	CPreciseTimer::CPreciseTimer( int p_nPrecosion, bool p_nPlay )
		: m_n64TimeBegin( 0 )
		, m_n64TimeEnd( 0 )
		, m_eTimerState( eTS_Stop )
	{
		if( m_n64Freq == 0 )
		{
			LARGE_INTEGER tmp;

			if (QueryPerformanceFrequency(&tmp) == FALSE)
			{
				FK_EXCEPTION( CException::eEC_HardwareCannotSupport, L"�����޷�ʹ�ø߾��ȼ�ʱ��", L"CPreciseTimer::CPreciseTimer");
			}
			m_n64Freq = tmp.QuadPart;
		}

		FKAssert( p_nPrecosion > 0, "���������� С��0 �ļ�ʱ������" );

		m_nPrecision = p_nPrecosion;
		if( p_nPlay )
		{
			Play();
		}
	}
	//--------------------------------------------------------------------
	CPreciseTimer::~CPreciseTimer()
	{
		
	}
	//--------------------------------------------------------------------
	void CPreciseTimer::SetPrecosion( int p_nPrecosion )
	{
		FKAssert( p_nPrecosion > 0, "���������� С��0 �ļ�ʱ������" );
		m_nPrecision = p_nPrecosion;
	}
	//--------------------------------------------------------------------
	int CPreciseTimer::GetPrecosion() const
	{
		return m_nPrecision;
	}
	//--------------------------------------------------------------------
	unsigned int CPreciseTimer::GeTime()
	{
		if ( m_eTimerState != eTS_Running )
		{
			return DWORD((m_n64TimeEnd - m_n64TimeBegin) * m_nPrecision / m_n64Freq);
		}
		else
		{
			return DWORD((GetCurrentCount() - m_n64TimeBegin) * m_nPrecision / m_n64Freq);
		}
	}
	//--------------------------------------------------------------------
	void CPreciseTimer::Play()
	{
		if ( m_eTimerState == eTS_Stop )
		{
			m_n64TimeBegin = GetCurrentCount();
		}
		m_eTimerState = eTS_Running;		
	}
	//--------------------------------------------------------------------
	void CPreciseTimer::Stop()
	{
		m_n64TimeEnd = GetCurrentCount();
		m_eTimerState = eTS_Stop;
	}
	//--------------------------------------------------------------------
	void CPreciseTimer::Pause()
	{
		m_n64TimeEnd = GetCurrentCount();
		m_eTimerState = eTS_Pause;
	}
	//--------------------------------------------------------------------
	bool CPreciseTimer::IsPause() const
	{
		return m_eTimerState == eTS_Pause ? true : false; 
	}
	//--------------------------------------------------------------------
	bool CPreciseTimer::IsStop() const
	{
		return m_eTimerState == eTS_Stop ? true : false;
	}
	//--------------------------------------------------------------------
	__int64 CPreciseTimer::GetCurrentCount()
	{
		LARGE_INTEGER tmp;
		QueryPerformanceCounter(&tmp);
		return tmp.QuadPart;
	}
	//--------------------------------------------------------------------
}