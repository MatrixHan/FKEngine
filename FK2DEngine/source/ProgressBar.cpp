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

#include "../include/ProgressBar.h"

//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	void CProgressBar::Create( IGUIControl* p_pParent, int p_nLeft, int p_nTop,
		CBitmap& p_BarBmp, CBitmap& p_BackgroudBmp, CBitmap& p_HeadBmp,
		CBitmap& p_MidBmp, CBitmap& p_TailBmp )
	{

	}
	//--------------------------------------------------------------------
	void CProgressBar::SetRange( unsigned int p_unBegin, unsigned int p_unEnd )
	{

	}
	//--------------------------------------------------------------------
	void CProgressBar::SetPos( unsigned int p_unPos )
	{

	}
	//--------------------------------------------------------------------
	unsigned int CProgressBar::GetMax() const
	{
		return m_unMax;
	}
	//--------------------------------------------------------------------
	unsigned int CProgressBar::GetMin() const
	{
		return m_unMin;
	}
	//--------------------------------------------------------------------
	unsigned int CProgressBar::GetPos() const
	{
		return m_unPos;
	}
	//--------------------------------------------------------------------
}