/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RootControl
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "UIControl.h"
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	//! ��UI����
	//@remarks ȫ��Ψһ�����пؼ���Ϊ�ÿؼ��Ĺҽ��ӿؼ�
	class CRootControl : public IGUIControl
	{
	public:
		CRootControl()
		{
			m_bVisible = false;
			m_nLeft = 0;
			m_nTop = 0;
			m_nHeight = 0;
			m_nWidth = 0;
		}
		~CRootControl()
		{

		};
	public:
		//! ���ؼ������ܽ���
		virtual bool CanHaveFocus() const
		{
			return false;
		}
		//! ���ؼ��������
		virtual void FKDraw() const
		{
			return;
		}
	};
}