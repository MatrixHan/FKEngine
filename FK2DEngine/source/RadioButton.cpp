/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RadioButton
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../Include/RadioButton.h"
#include "../Include/UIManager.h"

//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	CRadioButton::CRadioButton()
		: m_nGroup( 0 )
	{

	}
	//--------------------------------------------------------------------
	void CRadioButton::Create( IGUIControl* p_pParent, int p_nLeft, int p_nTop,
		CBitmap& p_Bitmap, const std::wstring& p_szCaption )
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

		SSGUIManager::Instance()->AddRadio( this );
	}
	//--------------------------------------------------------------------
	void CRadioButton::Check()
	{
		SSGUIManager::Instance()->CheckRadio( this );
		m_bChecked = true;
	}
	//--------------------------------------------------------------------
	void CRadioButton::SetGroup( int p_nGroup )
	{
		m_nGroup = p_nGroup;
	}
	//--------------------------------------------------------------------
	int CRadioButton::GetGroup() const
	{
		return m_nGroup;
	}
	//--------------------------------------------------------------------
	void CRadioButton::MouseUp( POINT p_Point, ENUM_MouseButton p_eMB )
	{
		if(( p_eMB == eMB_Left ) && ( m_eBS == eBS_Down ))
		{
			m_bChecked = true;
		}

		if( m_bChecked )
		{
			SSGUIManager::Instance()->CheckRadio( this );
		}

		CPicButton::MouseUp( p_Point, p_eMB );
	}
	//--------------------------------------------------------------------
}