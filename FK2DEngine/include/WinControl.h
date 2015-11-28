/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	WinControl
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
#include "Image.h"
#include <vector>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	//! ����ؼ���
	//@remarks	���ؼ�����Ϊһ���ؼ��������ڵģ��ö���������ӿؼ�������
	//			���ؼ�����Ч�ԺͿɼ��ԡ�
	//			ͬʱ�������ӿؼ��ܸ��ؼ�����ϵӰ�죬�����ӿؼ����븸�ؼ�
	//			��֤λ�õ�ͬ����
	class CWinControl : public IGUIControl
	{
	public:
		CWinControl();
		virtual ~CWinControl();
	public:
		virtual void FKDraw() const;

		//! ���ñ���ͼƬ
		void SetBG( CBitmap& p_bBackground );

		//! ���ؼ����ɽ��ܽ���
		virtual bool CanHaveFocus() const
		{
			return false;
		}
	protected:
		CBitmap*				m_pBackGround;		// ����ͼƬָ��
		std::vector< CImage >	m_vecImage;			// ����ͼƬ
	};
	//--------------------------------------------------------------------
}