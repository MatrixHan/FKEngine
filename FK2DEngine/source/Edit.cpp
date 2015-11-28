/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Edit
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../include/Edit.h"
#include "../include/UIManager.h"

//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	CEdit::CEdit()
		: m_szText( L"" )
		, m_fTime( 0.0f )
		, m_nCaretPos( 0 )
		, m_bShowCaret( true )
		, m_nCharWidth( 0 )
		, m_eCaretStyle( ECS_Vertical )
	{

	}
	//--------------------------------------------------------------------
	void CEdit::Create( IGUIControl* p_pParent, int p_nLeft, int p_nTop, int p_nWidth )
	{
		IGUIControl::Create();

		SetParent( p_pParent );
		SetLeft( p_nLeft );
		SetTop( p_nTop );
		SetWidth( p_nWidth );

		if( m_pColor == NULL )
		{
			SetFontColor( *(new CColor( CColor::WHITE )) );
			m_CaretColor = *m_pColor;
		}
	}
	//--------------------------------------------------------------------
	void CEdit::FKDraw() const
	{
		POINT pt = { 0, 0 };
		ClientToScreen( pt );

		if( m_szText != L"" )
		{
			if( m_bEnabled )
			{
				m_pFont->FKDraw( m_szText, pt.x, pt.y, GetZPos(), 1.0, 1.0, *m_pColor );
			}
			else
			{
				m_pFont->FKDraw( m_szText, pt.x, pt.y, GetZPos(), 1.0, 1.0, CColor( 0xA0, 0xA0, 0xA0 ) );
			}
		}

		if( m_bFocused && m_bShowCaret && m_bEnabled )
		{
			pt.x += m_nCharWidth * m_nCaretPos;
			
			if( m_eCaretStyle == ECS_Vertical )
			{
				SSGUIManager::Instance()->GetGraphics().DrawLine(
					pt.x, pt.y, m_CaretColor, pt.x, pt.y + m_nHeight, m_CaretColor, GetZPos() );
			}
			else
			{
				pt.y += m_nHeight;
				SSGUIManager::Instance()->GetGraphics().DrawLine(
					pt.x, pt.y, m_CaretColor, pt.x + m_nCharWidth, pt.y, m_CaretColor, GetZPos() );
			}
		}
	}
	//--------------------------------------------------------------------
	void CEdit::Update( float p_fDelta )
	{
		// 500msˢ��һ�ι������
		m_fTime += p_fDelta;
		if( m_fTime >= 500 )
		{
			m_fTime -= 500;
			m_bShowCaret = !m_bShowCaret;
		}
	}
	//--------------------------------------------------------------------
	void CEdit::SetParent( IGUIControl* p_pParent )
	{
		IGUIControl::SetParent( p_pParent );

		if( m_pColor != NULL )
		{
			m_CaretColor = *m_pColor;
		}

		if( m_pFont != NULL )
		{
			m_nHeight = m_pFont->Height();
			m_nCharWidth = static_cast<int>( m_pFont->TextWidth( L"��" ) );	// ������
		}
	}
	//--------------------------------------------------------------------
	void CEdit::SetFont( CFont& p_Font )
	{
		IGUIControl::SetFont( p_Font );

		if( m_pFont != NULL )
		{
			m_nHeight = m_pFont->Height();
			m_nCharWidth = static_cast<int>( m_pFont->TextWidth( L"��" ) );	// ������	
		}
	}
	//--------------------------------------------------------------------
	void CEdit::SetText( const std::wstring& p_Text )
	{
		m_szText = p_Text;
	}
	//--------------------------------------------------------------------
	std::wstring CEdit::GetText() const
	{
		return m_szText;
	}
	//--------------------------------------------------------------------
	void CEdit::SetCaretColor( CColor p_Color )
	{
		m_CaretColor = p_Color;
	}
	//--------------------------------------------------------------------
	void CEdit::SetCaretType( ENUM_CaretStyle p_eStyle )
	{
		m_eCaretStyle = p_eStyle;
	}
	//--------------------------------------------------------------------
	void CEdit::MouseDown( POINT p_Point, ENUM_MouseButton p_eMB )
	{
		if( p_eMB != eMB_Left )
		{
			return;
		}

		ScreenToClient( p_Point );

		m_nCaretPos = ( p_Point.x + m_nCharWidth / 2 ) / m_nCharWidth;

		if( m_nCaretPos > static_cast< int >( m_szText.size() ) )
		{
			m_nCaretPos = static_cast< int >( m_szText.size() );
		}

		m_fTime = 0;
		m_bShowCaret = true;

		IGUIControl::MouseDown( p_Point , p_eMB );
	}
	//--------------------------------------------------------------------
	void CEdit::KeyDown( unsigned long p_ulKey, SShiftState p_State )
	{
		if( p_ulKey == VK_RIGHT )
		{
			MoveCaret( 1 );
			if( m_nCaretPos > static_cast< int >( m_szText.size() ) )
			{
				m_nCaretPos = static_cast< int >( m_szText.size() );
			}
		}
		else if( p_ulKey == VK_LEFT )
		{
			MoveCaret( -1 );
			if( m_nCaretPos < 0 )
			{
				m_nCaretPos = 0;
			}
		}
		else if( ( p_ulKey == VK_DELETE ) && ( m_nCaretPos < static_cast< int >( m_szText.size() ) ) )
		{
			std::wstring former = m_szText.substr( 0, m_nCaretPos );
			std::wstring latter = m_szText.substr( m_nCaretPos + 1, m_szText.size() - m_nCaretPos );
			m_szText = former + latter;
		}
		else if(( p_ulKey == VK_BACK ) && ( m_nCaretPos > 0 ))
		{
			std::wstring former = m_szText.substr( 0, m_nCaretPos - 1 );
			std::wstring latter = m_szText.substr( m_nCaretPos, m_szText.size() - m_nCaretPos );
			m_szText = former + latter;
			MoveCaret( -1 );
		}

		IGUIControl::KeyDown( p_ulKey, p_State );
	}
	//--------------------------------------------------------------------
	void CEdit::KeyPress( char p_cKey )
	{
		if( p_cKey < 33 || (( int )m_szText.size() + 1 ) * m_nCharWidth > m_nWidth )
		{
			return;
		}

		std::wstring former = m_szText.substr( 0, m_nCaretPos );
		std::wstring latter = m_szText.substr( m_nCaretPos, m_szText.size() );
		std::wstring szKey;
		szKey.insert( szKey.begin(), p_cKey );
		m_szText = former + szKey + latter;
		MoveCaret( 1 );

		IGUIControl::KeyPress( p_cKey );
	}
	//--------------------------------------------------------------------
	void CEdit::MoveCaret( int p_nOffset )
	{
		// ��ǰλ�ü���ƫ��ֵ
		m_nCaretPos += p_nOffset;

		// ����λ��ʹ֮�Ϸ�
		if( m_nCaretPos > static_cast<int>( m_szText.size() ) )
		{
			m_nCaretPos = static_cast<int>( m_szText.size() );
		}
		else if( m_nCaretPos < 0 )
		{
			m_nCaretPos = 0;
		}

		// ����Ϊ��ʾ״̬
		m_bShowCaret = true;
		m_fTime = 0;
	}
	//--------------------------------------------------------------------
}