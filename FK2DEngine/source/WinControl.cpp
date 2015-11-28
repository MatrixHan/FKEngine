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

#include "../Include/WinControl.h"
#include "../Include/UIManager.h"
#include "../Include/Image.h"
#include "../Include/ImageData.h"
#include <vector>

//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	CWinControl::CWinControl()
		: m_pBackGround( NULL )
	{
		m_nLeft = 0;
		m_nTop = 0;
		m_pParent = NULL;
		m_vecImage.clear();
	}
	//--------------------------------------------------------------------
	CWinControl::~CWinControl()
	{

	}
	//--------------------------------------------------------------------
	void CWinControl::FKDraw() const
	{
		if( !m_bVisible || m_pBackGround == NULL )
		{
			return;
		}

		m_vecImage[0].FKDraw( m_nLeft, m_nTop, GetZPos() );
	}
	//--------------------------------------------------------------------
	void CWinControl::SetBG( CBitmap& p_bBackground )
	{
		m_pBackGround = &p_bBackground;
		m_vecImage.push_back( CImage( SSGUIManager::Instance()->GetGraphics().CreateImage( 
			*m_pBackGround, 0, 0, m_pBackGround->Width(), m_pBackGround->Height(), EBF_Smooth ) ) );
	}
	//--------------------------------------------------------------------
}