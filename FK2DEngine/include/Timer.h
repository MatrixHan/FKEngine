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

#pragma once

//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	//! ��ʱ����ӿ�
	class ITimer
	{
	public:
		virtual unsigned int GetTime() = 0;
		virtual void Play() = 0;
		virtual void Pause() = 0;
		virtual void Stop() = 0;
		virtual bool IsStop() const = 0;
		virtual bool IsPause() const = 0;
	};
	//--------------------------------------------------------------------
	//! ��ʱ��
	class CTimer : public ITimer
	{
	public:
		CTimer();
		~CTimer();
	public:
		//! ��ȡ��Play����ǰ���ŵ�ʱ�䣨��λ�����룩
		//! note: ��������ͣʱ���ŵ�ʱ�䡣�ʱ��50������
		unsigned int GetTime();

		//! ��ȡ���ŵ�ʱ�䣨��λ�����룩
		//! note: ������ͣʱ���ŵ�ʱ�䡣�ʱ��50������
		unsigned int GetElapseTime();

		//! ��ʼ��ʱ �� ������ʱ
		void		Play();

		//! ��ͣ��ʱ
		void		Pause();

		//! ֹͣ��ʱ
		void		Stop();

		//! �Ƿ���ͣ��ʱ״̬
		bool		IsPause() const;

		//! �Ƿ�ֹͣ��ʱ״̬
		bool		IsStop() const;
	private:
		//! ʱ��״̬
		enum ENUM_TimerState
		{
			eTS_Running,					// ��ʱ��
			eTS_Pause,						// ��ͣ��ʱ
			eTS_Stop,						// ֹͣ��ʱ
		};
		unsigned int		m_dwStartTime;	// ��ʼʱ��
		unsigned int		m_dwElapse;		// ���ŵ�ʱ��
		unsigned int		m_dwPauseTime;	// ��ͣʱ��
		ENUM_TimerState		m_eState;		// ʱ��״̬
	};
	//--------------------------------------------------------------------
	//! �߾��ȼ�ʱ��
	class CPreciseTimer : public ITimer
	{
	public:
		CPreciseTimer( int p_nPrecosion = 10000, bool p_nPlay = false );
		~CPreciseTimer();
	public:
		//! ���ü�ʱ������
		//@params [IN] p_nPrecosion ��ֵΪ1000ʱ��GeTime()���ص�λΪ����
		void SetPrecosion( int p_nPrecosion = 10000 );

		//! ��ȡ��ʱ����
		int GetPrecosion() const;

		//! ��ȡ��ǰ��ʱ������
		unsigned int GeTime();

		//! ��ʼ��ʱ
		void Play();

		//! ֹͣ��ʱ
		void Stop();

		//! ��ͣ��ʱ
		void Pause();

		//! �Ƿ���ͣ��ʱ
		bool IsPause() const;

		//! �Ƿ�ֹͣ��ʱ
		bool IsStop() const;

	private:
		//! ��ȡϵͳ��ʱ����ֵ
		__int64 GetCurrentCount();
	private:
		//! ʱ��״̬
		enum ENUM_TimerState
		{
			eTS_Running,					// ��ʱ��
			eTS_Pause,						// ��ͣ��ʱ
			eTS_Stop,						// ֹͣ��ʱ
		};
		static __int64	m_n64Freq;		// ��ʱ��Ƶ��
		__int64			m_n64TimeBegin;	// ��ʼʱ��
		__int64			m_n64TimeEnd;	// ֹͣʱ��
		int				m_nPrecision;	// ��ʱ������
		ENUM_TimerState	m_eTimerState;	// ��ʱ��״̬
	};
	//--------------------------------------------------------------------
}