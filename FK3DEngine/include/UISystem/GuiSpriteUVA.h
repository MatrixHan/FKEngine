/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiSpriteUVA
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	���������û��������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "GuiBase.h"
#include "../RenderWrapper/OverlaySurface.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class SpriteSet;
	class Sprite;
	struct UVAnimation;
	//--------------------------------------------------------------------------------------------------------------
	//���������û��������
	class FK_DLL GuiSpriteUVA : public GuiBase
	{
	public:
		SpriteSet*	mpSpriteSet;	//��ťͼ���鼯
		Sprite*		mpSprite;		//��ťͼ����

	public:
		GuiSpriteUVA( ZOrderType eZType, OverlaySurface* pZRefOverlay, GuiDialog* pDialog,
			GuiLoca* pLoca, GuiClient* pClient, SpriteSet* pSpriteSet, UVAnimation* pUVA );
		virtual ~GuiSpriteUVA();

	public:
		//��ʾ/���ؿؼ�
		void FKFastcall Show( bool bShow );

		//����λ��
		void FKFastcall SetPos( long nX, long nY );

		//���� Z ˳��
		void FKFastcall SetZOrder( ZOrderType eZType, OverlaySurface* pZRefOverlay );

		//��ȡ Z ˳��
		OverlaySurface* FKFastcall GetZOrder( ZOrderType eZType );

		//����ָ�� UV ������
		void FKFastcall PlaySegment( int nPlaySegment, int nNextSegment, bool bReverse = false );

	public:
		//���û������������Ϣ
		LONG_PTR SendMsg( LONG_PTR nGM, LONG_PTR nGMA = 0, LONG_PTR nGMB = 0 );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

