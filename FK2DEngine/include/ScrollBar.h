/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ScrollBar
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "UIControl.h"
#include "Bitmap.h"
#include "UIManager.h"
#include "Image.h"
#include <vector>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	//! ����������
	enum ENUM_ScrollBarType
	{
		ESBT_Horizontal,		// ˮƽ
		ESBT_Vertical,			// ��ֱ
	};
	//--------------------------------------------------------------------
	//! ������
	class CScrollBar : public IGUIControl
	{
	public:
		CScrollBar();
		virtual ~CScrollBar(){}
	public:
		void Create(  IGUIControl* p_pParent, int p_nLeft, int p_nTop,
			ENUM_ScrollBarType p_eType, CBitmap& p_Bitmap, int p_nLength );
		virtual void FKDraw() const;

	public:
		//! ���û���ͼƬ
		void SetSlider( CBitmap& p_SliderBitmap );
		//! ���ù���������
		void SetLength( int p_nLength );
		//! ��ȡ����λ��
		int GetPosition() const;
		//! ���û���λ��
		void SetPosition( int p_nPos );
		//! ���ù���������
		void SetType( ENUM_ScrollBarType p_eType );
		//! ���û���λ�÷�Χ
		void SetRange( int p_nMin, int p_nMax );

	public:
		//! ��д���¼�������
		virtual void MouseMove( POINT p_Point );
		virtual void MouseDown( POINT p_Point, ENUM_MouseButton p_eMB );
		virtual void MouseUp( POINT p_Point, ENUM_MouseButton p_eMB );

	public:
		//! ���û��ṩ�Ķ����¼�����
		SNotifyEvent OnChange;
		SNotifyEvent OnScroll;

	private:
		ENUM_ScrollBarType				m_eType;		// ����������
		CBitmap*						m_pSlider;		// ����ͼƬָ��
		int								m_nOffset;		// ����ڻ����ϵ�ƫ��
		int								m_nSliderPos;	// ����λ��
		int								m_nMin;			// ����λ����Сֵ
		int								m_nMax;			// ����λ�����ֵ
		bool							m_bHolding;		// ����Ƿ���л���
		std::vector< CImage >			m_vecImages;	// ���ͼƬ��
	};
	//--------------------------------------------------------------------
}