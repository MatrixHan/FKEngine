/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiCheckBox
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ѡ�����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "../RenderWrapper/FrameListener.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��ѡ�����
	class FK_DLL GuiCheckBox : public GuiSprite
	{
	public:
		//��ѡ�����
		struct Param
		{
			SpriteSet*		pSpriteSet;		//���鼯

			GuiLoca			sLoca;			//��ѡ��λ��
			GuiClient		sClient;		//��ѡ��ͻ���

			FnFrameEvent	fnEvent;		//��ѡ���¼�
		};

	public:
		bool		mbChecked;			//�Ƿ�Ϊ��ѡ״̬

	protected:
		UV4				mNormalUV;			//��ͨ��������
		UV4				mCheckedUV;			//��ѡ��������
		UV4				mNormalLightUV;		//��ͨ�߹���������
		UV4				mCheckedLightUV;	//��ѡ�߹���������

		FnFrameEvent	mFnEvent;			//��ѡ���¼�����ָ��

	public:
		GuiCheckBox( ZOrderType eZType, OverlaySurface* pZRefOverlay, GuiDialog* pDialog, Param* pParam );

	public:
		//���/ʧȥ����
		void FKFastcall Focus( bool bHasFocus );

		//�������
		void FKFastcall LDown( InputSystem* pInputSystem );

		//���ø�ѡ���¼�����
		void FKFastcall SetEvent( FnFrameEvent fnEvent );

	public:
		//���û������������Ϣ
		LONG_PTR SendMsg( LONG_PTR nGM, LONG_PTR nGMA = 0, LONG_PTR nGMB = 0 );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

