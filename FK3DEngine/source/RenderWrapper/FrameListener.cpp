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
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderWrapper/RenderWrapperInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	FrameListener::FrameListener()
	{
		mFrameEventList.Initialize( 20, 20 );
	}
	//--------------------------------------------------------------------------------------------------------------
	FrameListener::~FrameListener()
	{
		mFrameEventList.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//����֡�¼�
	void FKFastcall FrameListener::AddFrameEvent( FnFrameEvent fnEvent, LONG_PTR pParam )
	{
		FrameEvent* pEvent = mFrameEventList.Push();
		pEvent->fnEvent = fnEvent;
		pEvent->pParam = pParam;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����֡�¼�
	void FrameListener::ProcFrameEvent()
	{
		FrameEventList::Iterator it = mFrameEventList.Begin();
		FrameEventList::Iterator end = mFrameEventList.End();
		for(; it!=end; ++it )
		{
			FrameEvent* pEvent = it;
			pEvent->fnEvent( pEvent->pParam );
		}

		mFrameEventList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
