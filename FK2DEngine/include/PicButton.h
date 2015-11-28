/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	PicButton
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "UIControl.h"
#include "Image.h"
#include <vector>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	//! ͼƬ��ť��
	class CPicButton : public IGUIControl
	{
	public:
		//! ö�ٰ�ť״̬
		enum ENUM_ButtonState
		{
			eBS_Up,
			eBS_Hot,
			eBS_Down,
			eBS_Disabled,
			eBS_MAX,
		};

	public:
		CPicButton();
		virtual ~CPicButton(){}
	public:
		virtual void FKDraw() const = 0;

		//! ���ð�ťͼƬ
		//@note Ҫ��һ�����У��ֱ�ΪUp,Hot,Down,Disabledʱ��ͼƬ
		void SetGlygh( CBitmap& p_Bitmap );

		//! ���ð�ť����ʱͼƬ��ƫ��
		void SetDownOffset( int p_nX, int p_nY );

		//! ������
		virtual void MouseEnter();
		//! ����뿪
		virtual void MouseLeave();
		//! ��갴��
		virtual void MouseDown( POINT p_Point, ENUM_MouseButton p_eMB );
		//! ��굯��
		virtual void MouseUp( POINT p_Point, ENUM_MouseButton p_eMB );

	public:
		//! ���û����ṩ��OnClick�¼�����
		SNotifyEvent			OnClick;

	protected:
		CBitmap*			m_pBitmap;		// ��ťͼƬ
		std::vector<CImage>	m_vecImage;		// ͼƬ��Ԫ
		ENUM_ButtonState	m_eBS;			// ��ť״̬
		POINT				m_DownOffset;	// ��ť����ʱ��ͼƬƫ��
		bool				m_bHolding;		// ����Ƿ���а�ť
		bool				m_bHovering;	// ����Ƿ��ڰ�ť�Ϸ�
	};
	//--------------------------------------------------------------------
}