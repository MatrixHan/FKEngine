/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Button
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../Include/Button.h"
#include "../Include/UIControl.h"
#include "../Include/PicButton.h"
#include "../Include/Exception.h"

//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	void CButton::Create( IGUIControl* p_pParent, int p_nLeft, int p_nTop, 
		CBitmap& p_Bitmap,const std::wstring& p_szCaption )
	{
		IGUIControl::Create();
		SetParent( p_pParent );
		SetLeft( p_nLeft );
		SetTop( p_nTop );
		SetGlygh( p_Bitmap );
		SetCaption( p_szCaption );
		if( m_pColor == NULL )
		{
			SetFontColor( *(new CColor( CColor::WHITE )) );
		}
	}
	//--------------------------------------------------------------------
	void CButton::FKDraw() const
	{
		CPicButton::FKDraw();

		POINT pt = { 0, 0 };
		if( m_eBS == eBS_Down )
		{
			pt.x += m_DownOffset.x;
			pt.y += m_DownOffset.y;
		}
		ClientToScreen( pt );

		if( m_pFont != NULL )
		{
			m_pFont->FKDraw( m_szCaption, pt.x + m_TextPos.x, pt.y + m_TextPos.y, GetZPos(),
				1.0, 1.0, *m_pColor );
		}
	}
	//--------------------------------------------------------------------
	void CButton::SetCaption( const std::wstring& p_szCaption )
	{
		FKAssert( m_pFont != NULL , "Button����������Ϊ��" );

		IGUIControl::SetCaption( p_szCaption );

		// ������ʾ
		int nLen = (int)m_szCaption.length();
		m_TextPos.x = ( m_nWidth - static_cast<int>(m_pFont->TextWidth( p_szCaption) ) ) / 2;
		m_TextPos.y = ( m_nHeight - static_cast<int>(m_pFont->Height()) ) / 2 ;
	}
	//--------------------------------------------------------------------
}