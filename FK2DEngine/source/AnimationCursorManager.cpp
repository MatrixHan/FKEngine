/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	AnimationCursorManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../include/AnimationCursor.h"
#include "../include/AnimationCursorManager.h"
#include "../include/Exception.h"
#include "../include/LogManager.h"
#include "../Include/StringConversion.h"

//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	CAnimationCursorManager::CAnimationCursorManager()
		: m_bEnable ( false )
		, m_pCurCursor( NULL )
		, m_fDelta( 0 )
		, m_fTime( 0 )
		, m_nHotX( 0 )
		, m_nHotY( 0 )
		, m_pGraphics( NULL )
		, m_bNeedUpdate( false )
	{

	}
	//--------------------------------------------------------------------
	CAnimationCursorManager::~CAnimationCursorManager()
	{
	}
	//--------------------------------------------------------------------
	void CAnimationCursorManager::Init( CGraphics& p_Graphics, int p_nFPS, int p_nHotX, int p_nHotY )
	{
		FKAssert( p_nFPS >= 0 , "���ö������ˢ��FPS������" );
		m_pGraphics = &p_Graphics;
		m_fDelta = ( 1 / (float)p_nFPS ) * 1000;
	}
	//--------------------------------------------------------------------
	void CAnimationCursorManager::Enable( bool p_bEnable )
	{
		if( p_bEnable )
		{
			ShowCursor( FALSE );
		}
		else
		{
			ShowCursor( TRUE );
		}
		m_bEnable = p_bEnable;
	}
	//--------------------------------------------------------------------
	bool CAnimationCursorManager::Enabled()
	{
		return m_bEnable;
	}
	//--------------------------------------------------------------------
	bool CAnimationCursorManager::AddCursor( CBitmap& p_Bitmap, const std::wstring& p_szCursorName,
		int p_nSingleWidth, int p_nSingleHeight )
	{
		CursorMap::const_iterator Ite = m_CursorMap.find( p_szCursorName );
		if( Ite != m_CursorMap.end() )
		{
			SSLogManager::Instance()->LogMessage( L"�Ѿ�ע������Ϊ " + p_szCursorName + L" �Ķ�̬��꣬�����ظ�ע��" );
			return false;
		}
		CAnimationCursor AnimCursor;
		AnimCursor.Init( p_Bitmap, p_szCursorName, p_nSingleWidth, p_nSingleHeight );
		m_CursorMap.insert( make_pair( p_szCursorName, AnimCursor ) );
		return true;
	}
	//--------------------------------------------------------------------
	void CAnimationCursorManager::SetAnimCursor( const std::wstring& p_szCursorName )
	{
		CursorMap::const_iterator Ite = m_CursorMap.find( p_szCursorName );
		if( Ite != m_CursorMap.end() )
		{
			m_pCurCursor = (FK2DEngine::CAnimationCursor *)(&(Ite->second));
		}
	}
	//--------------------------------------------------------------------
	CGraphics& CAnimationCursorManager::GetGraphics()
	{
		FKAssert( (m_pGraphics != NULL), L"��ȡ��̬�����Ⱦָ��ʧ��" );
		return *m_pGraphics;
	}
	//--------------------------------------------------------------------
	void CAnimationCursorManager::Update( float p_fDetla )
	{
		if( !m_bEnable )
		{
			return;
		}
		m_fTime += p_fDetla;
		if( m_fTime > m_fDelta )
		{
			m_fTime -= m_fDelta;
			m_bNeedUpdate = true;
		}
	}
	//--------------------------------------------------------------------
	void CAnimationCursorManager::FKDraw()
	{
		if( !m_bEnable )
		{
			return;
		}
		if( m_pCurCursor != NULL ) 
		{
			m_pCurCursor->FKDraw( m_bNeedUpdate );
			if( m_bNeedUpdate )
			{
				m_bNeedUpdate = !m_bNeedUpdate;
			}
		}
	}
	//--------------------------------------------------------------------
}