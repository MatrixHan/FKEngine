/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Form
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "WinControl.h"
#include "Bitmap.h"
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	class CForm : public CWinControl
	{
	public:
		CForm();
		virtual ~CForm(){}
	public:
		void Create( IGUIControl* p_pParent, int p_nLeft, int p_nTop,
			int p_nWidth, int p_nHeight );
		void Create( IGUIControl* p_pParent, int p_nLeft, int p_nTop,
			CBitmap& p_Bitmap );
	public:
		//! �����Ⱦ���
		//@remarks �Ⱦ�������갴�¿��϶�����
		void SetHotRect( RECT& p_RC );

		//! ��д�¼�������
		virtual void MouseMove( POINT p_Point );
		virtual void MouseDown( POINT p_Point, ENUM_MouseButton p_eMB );
		virtual void MouseUp( POINT p_Point, ENUM_MouseButton p_eMB );
	private:
		RECT						m_HotRC;		// �Ⱦ���
		POINT						m_OffsetPT;		// ��갴��ʱ�Ⱦ����е�ƫ��
		bool						m_bHolding;		// ����Ƿ������д���
		bool						m_bMoveable;	// �����Ƿ�����ƶ�
	};
	//--------------------------------------------------------------------
}