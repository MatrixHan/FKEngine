/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	FrameListener
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	֡������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	//֡�¼�������
	typedef void (*FnFrameEvent)( LONG_PTR pParam );

	//֡�¼�����
	struct FrameEvent
	{
		FnFrameEvent	fnEvent;	//֡�¼�������ָ��
		LONG_PTR		pParam;		//֡�¼���������
	};

	typedef Stack< FrameEvent >		FrameEventList;

	//֡��������
	struct FrameListenerData
	{
		float	fTimeSinceLastFrame;		//��һ֡����ǰ֡��ʱ��
	};

	//--------------------------------------------------------------------------------------------------------------
	//֡��������Ӧ�ó���̳д�����ʵ���Լ���֡��������
	class FK_DLL FrameListener
	{
	protected:
		FrameEventList		mFrameEventList;	//֡�¼��б�

	public:
		FrameListener();
		virtual ~FrameListener();

		//����֡�¼�
		void FKFastcall AddFrameEvent( FnFrameEvent fnEvent, LONG_PTR pParam = NULL );

		//����֡�¼�
		void ProcFrameEvent();

		//֡��ʼ�¼�
		virtual void FrameStart( FrameListenerData* pFrameData ) = 0;

		//֡����ʱ��
		virtual void FrameEnd( FrameListenerData* pFrameData ) = 0;
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
