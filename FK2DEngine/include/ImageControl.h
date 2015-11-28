/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ImageControl
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
#include <vector>
#include "Image.h"
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	//! ͼƬ�ؼ�
	//@remarks �������ʾһ����̬ͼƬ
	class CImageControl : public IGUIControl
	{
	public:
		CImageControl();
	public:
		void Create( IGUIControl* p_pParent, int p_nLeft, int p_nTop,
			CBitmap& p_Bitmap );
		virtual void FKDraw() const;
		//! �ÿؼ����ɽ��ܽ���
		virtual bool CanHaveFocus() const
		{
			return false;
		}
	public:
		void SetImage( CBitmap& p_Bitmap );
	private:
		CBitmap*					m_pBitmap;		// ͼƬָ��
		std::vector< CImage >		m_vecImages;	// ͼ���б�
	};
	//--------------------------------------------------------------------
}