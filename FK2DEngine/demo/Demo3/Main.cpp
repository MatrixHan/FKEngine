/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Main
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../interface/FKEngineInclude.h"

//--------------------------------------------------------------------
#ifdef NDEBUG
#pragma comment(lib, "FK2DEngine.lib")
#else
#pragma comment(lib, "FK2DEngine_D.lib")
#endif
//--------------------------------------------------------------------
#include "../../../depend/boost/scoped_ptr.hpp"
#include "../../../depend/boost/shared_ptr.hpp"
#include "../../../depend/boost/lexical_cast.hpp"
#include <cmath>
#include <cstdlib>
#include <list>
#include <vector>
//--------------------------------------------------------------------
class CGameWindow : public FK2DEngine::CFKWindow
{
private:
	FK2DEngine::CBitmap							m_UIButtonImage;
	FK2DEngine::CBitmap							m_UICheckBoxImage;
	FK2DEngine::CBitmap							m_UIPanelImage;
	FK2DEngine::CBitmap							m_UIImageCtrlImage;
	FK2DEngine::CBitmap							m_UIScrollImage;
	FK2DEngine::CBitmap							m_UIScrollBackImage;
	FK2DEngine::CBitmap							m_UIEditImage;
	FK2DEngine::CCheckBox						m_CheckBox;
	FK2DEngine::CFont							m_Font;
	FK2DEngine::CButton							m_Button;
	FK2DEngine::CRadioButton					m_Radio1;
	FK2DEngine::CRadioButton					m_Radio2;
	FK2DEngine::CRadioButton					m_Radio3;
	FK2DEngine::CRadioButton					m_Radio4;
	FK2DEngine::CPanel							m_Panel;
	FK2DEngine::CForm							m_Form;
	FK2DEngine::CLable							m_pLable;
	FK2DEngine::CImageControl					m_pImageCtrl;
	FK2DEngine::CEdit							m_pEdit;
	FK2DEngine::CImageControl					m_pEditBack;
	FK2DEngine::CScrollBar						m_pScrollBar;
	FK2DEngine::CColor*							m_pColor;
public:
	CGameWindow()
		: CFKWindow( 250,400,false )
		, m_Font( Graphics(), FK2DEngine::DefaultFontName(), 20 )
	{
		SetCaption( L"������ʿ��־���棺DEMO3 UI����" );
		SetBackgroudColor( FK2DEngine::CColor::BLUE );

		std::wstring szFileName = L"";

		szFileName = FK2DEngine::ShareResourcePrefix() + L"rc\\media\\Panel.bmp";
		m_UIPanelImage = LoadImageFile( szFileName );
		m_Panel.Create( SSGUIManager::Instance()->GetRootCtrl(), 
			( GetScreenWidth() - m_UIPanelImage.Width() ) / 2 , 40, m_UIPanelImage );

		szFileName = FK2DEngine::ShareResourcePrefix() + L"rc\\media\\PicButton.bmp";
		m_UIButtonImage = LoadImageFile( szFileName );
		m_pColor = (new CColor( CColor::GREEN ));
		m_Button.SetFontColor( *m_pColor );
		m_Button.Create( SSGUIManager::Instance()->GetRootCtrl(), 
			( GetScreenWidth() - m_UIButtonImage.Width() / 4 ) / 2 , 60, m_UIButtonImage, L"���԰�ť" );

		m_pLable.Create( SSGUIManager::Instance()->GetRootCtrl(), 
			40, 13, L"�� Lable�ؼ�" );

		szFileName = FK2DEngine::ShareResourcePrefix() + L"rc\\media\\Checkbox.bmp";
		m_UICheckBoxImage = LoadImageFile( szFileName );
		m_CheckBox.SetFont( m_Font );
		m_CheckBox.Create( SSGUIManager::Instance()->GetRootCtrl(), 
			( GetScreenWidth() - m_UICheckBoxImage.Width() / 6 - m_Font.TextWidth(L"���Ը�ѡ��") - 10 ) / 2, 110, m_UICheckBoxImage, L"���Ը�ѡ��" );


		m_Form.Create( SSGUIManager::Instance()->GetRootCtrl(), ( GetScreenWidth() - m_UIPanelImage.Width() ) / 2, 165 , m_UIPanelImage );
		RECT rc;
		rc.left = 0;
		rc.top = 0;
		rc.right = m_UIPanelImage.Width();
		rc.bottom = m_UIPanelImage.Height();
		m_Form.SetHotRect( rc );
		m_Form.SetZPos( FK2DEngine::eDZP_UIBegin + 2 );
		// ������Ӧ��Ϣ����
		SSGUIManager::Instance()->AddCtrl( &m_Form );

		m_Radio1.SetFont( m_Font );
		m_Radio2.SetFont( m_Font );
		m_Radio1.SetGroup( 1 );
		m_Radio2.SetGroup( 1 );
		m_Radio1.Create( (FK2DEngine::IGUIControl *)(&m_Form), 5, 5, m_UICheckBoxImage, L"��ѡ����1" );
		m_Radio2.Create( (FK2DEngine::IGUIControl *)(&m_Form), 5, 33, m_UICheckBoxImage, L"��ѡ����1" );

		m_Radio3.SetFont( m_Font );
		m_Radio4.SetFont( m_Font );
		m_Radio3.Create( (FK2DEngine::IGUIControl *)(&m_Form), 5, 61, m_UICheckBoxImage, L"��ѡ����2" );
		m_Radio3.SetGroup( 2 );
		m_Radio3.SetFontColor( *m_pColor );
		m_Radio4.Create( (FK2DEngine::IGUIControl *)(&m_Form), 5, 89, m_UICheckBoxImage, L"��ѡ����2" );
		m_Radio4.SetGroup( 2 );
		m_Radio4.SetFontColor( *m_pColor );

		szFileName = FK2DEngine::ShareResourcePrefix() + L"rc\\media\\slot.bmp";
		m_UIScrollBackImage = LoadImageFile( szFileName );
		m_pImageCtrl.Create( SSGUIManager::Instance()->GetRootCtrl(), 10, 310, m_UIScrollBackImage );
		szFileName = FK2DEngine::ShareResourcePrefix() + L"rc\\media\\slider.bmp";
		m_UIScrollImage = LoadImageFile( szFileName );
		m_pScrollBar.Create( SSGUIManager::Instance()->GetRootCtrl(), 17, 310, ESBT_Horizontal, m_UIScrollImage, m_UIScrollImage.Width() );

		szFileName = FK2DEngine::ShareResourcePrefix() + L"rc\\media\\edit.bmp";
		m_UIEditImage = LoadImageFile( szFileName );
		m_pEditBack.Create( SSGUIManager::Instance()->GetRootCtrl(), 10, 340, m_UIEditImage );
		m_pEdit.Create( SSGUIManager::Instance()->GetRootCtrl(), 35, 348, 200 );
		m_pEdit.SetFocus();
/*
		ON_KEYPRESS( &m_CheckBox, CCheckBox1Press );
*/

		szFileName = FK2DEngine::ShareResourcePrefix() + L"avgRc\\Attack.cur";
		SetNewCursor( szFileName );
	}

	void Update( float p_fDelta )
	{
	}

	void FKDraw()
	{

	}

	void KeyDown( FK2DEngine::CKey p_Key )
	{
		if( p_Key == FK2DEngine::EKB_Escape )
		{
			Close();
		}
	}

	bool OnClose()
	{
		if( MessageBox( NULL, L"ȷ���˳���", L"��ʾ", MB_OKCANCEL | MB_ICONINFORMATION ) == IDOK )
		{
			return true;
		}
		return false;
	}
};
//--------------------------------------------------------------------
int main( int p_nArgc, char* p_Argv[] )
{
	try
	{
		CGameWindow window;
		window.Show();
	}
	catch( ... )
	{
		throw;
	}
}
//--------------------------------------------------------------------