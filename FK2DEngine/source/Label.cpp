/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Label
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../Include/Label.h"

//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	void CLable::Create( IGUIControl* p_pParent, int p_nLeft, int p_nTop,const std::wstring& p_szCaption )
	{
		IGUIControl::Create();

		SetParent( p_pParent );
		SetLeft( p_nLeft );
		SetTop( p_nTop );
		SetCaption( p_szCaption );
		if( m_pColor == NULL )
		{
			SetFontColor( *(new CColor( CColor::WHITE )) );
		}
	}
	//--------------------------------------------------------------------
	void CLable::FKDraw() const
	{
		if( !m_bVisible || m_pFont == NULL )
		{
			return ;
		}

		POINT pt = { 0, 0 };
		ClientToScreen( pt );
		m_pFont->FKDraw( m_szCaption, pt.x, pt.y, GetZPos(),
			1.0, 1.0, *m_pColor );
	}
	//--------------------------------------------------------------------
}