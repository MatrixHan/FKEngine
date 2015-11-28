/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiListBox
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/UISystem/UISystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	GuiListBox::GuiListBox( GuiDialog* pDialog, Param* pParam )
		: GuiBase		( NULL, NULL, pDialog )
		, mpSpriteSet	(pParam->pSpriteSet)
		, mpTextFont	(pParam->pFontFace)
		, mX			(pParam->nX)
		, mY			(pParam->nY)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	GuiListBox::~GuiListBox()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//����/�رտؼ�
	void FKFastcall GuiListBox::Enable( bool bEnable )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʾ/���ؿؼ�
	void FKFastcall GuiListBox::Show( bool bShow )
	{
		mbVisable = bShow;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����λ��
	void FKFastcall GuiListBox::SetPos( long nX, long nY )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� Z ˳��
	void FKFastcall GuiListBox::SetZOrder( ZOrderType eZType, OverlaySurface* pZRefOverlay )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ Z ˳��
	OverlaySurface* FKFastcall GuiListBox::GetZOrder( ZOrderType eZType )
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���/ʧȥ����
	void FKFastcall GuiListBox::Focus( bool bHasFocus )
	{
		mbFocus = bHasFocus;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƶ�
	void FKFastcall GuiListBox::MouseMove( InputSystem* pInputSystem )
	{
		//ת��Ϊ�ؼ�����ϵ
		int x = pInputSystem->mMouseX - mLoca.X;
		int y = pInputSystem->mMouseY - mLoca.Y;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������
	void FKFastcall GuiListBox::LDown( InputSystem* pInputSystem )
	{
		//ת��Ϊ�ؼ�����ϵ
		int nX = pInputSystem->mMouseX - mLoca.X;
		int nY = pInputSystem->mMouseY - mLoca.Y;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���û������������Ϣ
	LONG_PTR GuiListBox::SendMsg( LONG_PTR nGM, LONG_PTR nGMA, LONG_PTR nGMB )
	{
		switch (nGM)
		{
			case GM_Enable:
				Enable( ( nGMA == 1 ) ? true : false );
				return TRUE;
			case GM_Show:
				Show( ( nGMA == 1 ) ? true : false );
				return TRUE;
			case GM_Focus:
				Focus( ( nGMA == 1 ) ? true : false );
				return TRUE;
			case GM_MouseMove:
				MouseMove( (InputSystem*)nGMA );
				return TRUE;
			case GM_SetPos:
				SetPos( nGMA, nGMB );
				return TRUE;
			case GM_MovePos:
				SetPos( mLoca.X + nGMA, mLoca.Y + nGMB );
				return TRUE;
			case GM_SetZOrder:
				SetZOrder( (ZOrderType)nGMA, (OverlaySurface*)nGMB );
				return TRUE;
			case GM_GetZOrder:
				return (LONG_PTR)GetZOrder( (ZOrderType)nGMA );
			case GM_LDown:
				LDown( (InputSystem*)nGMA );
				return TRUE;
		}

		return FALSE;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

