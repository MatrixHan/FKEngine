/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ProgressBar
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
	//! ��������
	class CProgressBar : public CWinControl
	{
	public:
		void Create( IGUIControl* p_pParent, int p_nLeft, int p_nTop,
			CBitmap& p_BarBmp, CBitmap& p_BackgroudBmp, CBitmap& p_HeadBmp,
			CBitmap& p_MidBmp, CBitmap& p_TailBmp );
		void SetRange( unsigned int p_unBegin, unsigned int p_unEnd );
		void SetPos( unsigned int p_unPos );
		unsigned int GetMax() const;
		unsigned int GetMin() const;
		unsigned int GetPos() const;
	protected:
		unsigned int	m_unPos;			// ��ǰλ��
		unsigned int	m_unMin;			// ��Сλ��
		unsigned int	m_unMax;			// ���λ��
		CBitmap*		m_BarBmp;
		CBitmap*		m_BackgroudBmp;
		CBitmap*		m_HeadBmp;
		CBitmap*		m_MidBmp;
		CBitmap*		m_TailBmp;
	};
	//--------------------------------------------------------------------
}