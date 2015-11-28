/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiButton
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ť����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "GuiSprite.h"
#include "../RenderWrapper/FrameListener.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��ť����
	class FK_DLL GuiButton : public GuiSprite
	{
	public:
		static const int mnNormalStatus		= 0;	//��ť��ͨ״̬����֡
		static const int mnFocusStatus		= 1;	//��ť����״̬����֡
		static const int mnPressStatus		= 2;	//��ť����״̬����֡

		//��ť����
		struct Param
		{
			SpriteSet*		pSpriteSet;		//���鼯

			GuiLoca			sLoca;			//��ťλ��
			GuiClient		sClient;		//��ť�ͻ���
			UV4*			pUV;			//��ť��������
			FnFrameEvent	fnEvent;		//��ť�¼�
		};

	protected:
		UV4*			mpUV;		//��ť����ָ֡��
		FnFrameEvent	mFnEvent;	//��ť�¼�����ָ��
		bool			mbPressed;	//�Ƿ��Ѱ��¹���ť

	public:
		GuiButton( ZOrderType eZType, OverlaySurface* pZRefOverlay, GuiDialog* pDialog, Param* pParam );

	public:
		//���/ʧȥ����
		void FKFastcall Focus( bool bHasFocus );

		//�������
		void FKFastcall LDown( InputSystem* pInputSystem );

		//����ͷ�
		void FKFastcall LUp( InputSystem* pInputSystem );

		//���ð�ť�¼�����
		void FKFastcall SetEvent( FnFrameEvent fnEvent );

	public:
		//���û������������Ϣ
		LONG_PTR SendMsg( LONG_PTR nGM, LONG_PTR nGMA = 0, LONG_PTR nGMB = 0 );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

