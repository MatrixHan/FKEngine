/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ArchiveManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../include/Archive.h"
#include "../include/ArchiveFactory.h"
#include "../include/ArchiveManager.h"
#include "../include/Exception.h"
#include "../include/LogManager.h"
#include <vector>

//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	CArchiveManager::CArchiveManager()
	{
		
	}
	//--------------------------------------------------------------------
	CArchiveManager::~CArchiveManager()
	{
		// �ͷ���Դ
		ArchiveMap::iterator Ite = m_Archives.begin();
		ArchiveMap::const_iterator IteEnd = m_Archives.end();

		for( ; Ite != IteEnd; ++Ite )
		{
			CArchive* pArch = Ite->second;

			// �ͷ��ĵ�
			pArch->Unload();

			// �ҵ���Ӧ�ĵ�����
			ArchiveFactoryMap::iterator IteFind = m_ArchFactories.find( pArch->GetType() );
			if( IteFind == m_ArchFactories.end() )
			{
				// �����ĵ�û���ҵ�
				FK_EXCEPTION( CException::eEC_ItemCannotFind,
					L"û���ҵ��ɴ���: " + IteFind->second->GetType() + L" ���ĵ�����",
					L"CArchiveManager::~CArchiveManager" );
			}

			IteFind->second->DestroyInstance( pArch );
		}

		// ����ĵ�ӳ���
		m_Archives.clear();
	}
	//--------------------------------------------------------------------
	CArchive* CArchiveManager::Load( const std::wstring& p_Filename, const std::wstring& p_ArchiveType )
	{
		ArchiveMap::iterator i = m_Archives.find( p_Filename );
		CArchive* pArch = 0;

		if( i == m_Archives.end() )
		{
			// �����ĵ�����
			ArchiveFactoryMap::iterator Ite = m_ArchFactories.find( p_ArchiveType );
			if( Ite == m_ArchFactories.end() )
			{
				FK_EXCEPTION( CException::eEC_ItemCannotFind, 
					L"û���ҵ����Դ���" + p_ArchiveType + L"���ĵ�����",
					L"CArchiveManager::Load" );
			}
			pArch = Ite->second->CreateInstance( p_Filename );
			pArch->Load();
			m_Archives[ p_Filename ] = pArch;
		}
		else
		{
			pArch = i->second;
		}

		return pArch;
	}
	//--------------------------------------------------------------------
	void CArchiveManager::Unload( CArchive* p_pArch )
	{
		Unload( p_pArch->GetName() );
	}
	//--------------------------------------------------------------------
	void CArchiveManager::Unload( const std::wstring& p_szFileName )
	{
		ArchiveMap::iterator i = m_Archives.find( p_szFileName );

		if( i != m_Archives.end() )
		{
			i->second->Unload();

			// �����ĵ�����
			ArchiveFactoryMap::iterator Ite = m_ArchFactories.find( i->second->GetType() );
			if( Ite == m_ArchFactories.end() )
			{
				FK_EXCEPTION( CException::eEC_ItemCannotFind, 
					L"û���ҵ����Դ���" + i->second->GetType() + L"���ĵ�����",
					L"CArchiveManager::Load" );
			}
			Ite->second->DestroyInstance( i->second );
			m_Archives.erase( i );
		}
	}
	//--------------------------------------------------------------------
	void CArchiveManager::AddArchiveFactory( CArchiveFactory* p_pFactory )
	{
		m_ArchFactories.insert( ArchiveFactoryMap::value_type( p_pFactory->GetType(), p_pFactory ) );
		SSLogManager::Instance()->LogMessage( L"���ڴ���" + p_pFactory->GetType() + L"���͵��ĵ������ѳɹ�ע���." );
	}
	//--------------------------------------------------------------------
	CArchiveManager::ArchiveMap& CArchiveManager::GetArchiveMap()
	{
		return m_Archives;
	}
	//--------------------------------------------------------------------
}	