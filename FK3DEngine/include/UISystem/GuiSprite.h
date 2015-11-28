/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiSprite
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�����û��������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "../RenderWrapper/OverlaySurface.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class SpriteSet;
	class Sprite;
	//--------------------------------------------------------------------------------------------------------------
	//��ť����
	class FK_DLL GuiSprite : public GuiBase
	{
	public:
		SpriteSet*	mpSpriteSet;	//��ťͼ���鼯
		Sprite*		mpSprite;		//��ťͼ����

	public:
		GuiSprite( GuiDialog* pDialog, GuiLoca* pLoca, GuiClient* pClient, SpriteSet* pSpriteSet );
		virtual ~GuiSprite();

	public:
		//����/�رտؼ�
		void FKFastcall Enable( bool bEnable );

		//��ʾ/���ؿؼ�
		void FKFastcall Show( bool bShow );

		//����λ��
		void FKFastcall SetPos( long nX, long nY );

		//���� Z ˳��
		void FKFastcall SetZOrder( ZOrderType eZType, OverlaySurface* pZRefOverlay );

		//��ȡ Z ˳��
		OverlaySurface* FKFastcall GetZOrder( ZOrderType eZType );

	public:
		//���û������������Ϣ
		LONG_PTR SendMsg( LONG_PTR nGM, LONG_PTR nGMA = 0, LONG_PTR nGMB = 0 );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

