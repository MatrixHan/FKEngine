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

#pragma once

//--------------------------------------------------------------------
#include "Singleton.h"
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	//! �ĵ�������
	class CArchiveManager
	{
		typedef std::map< std::wstring, CArchiveFactory* >		ArchiveFactoryMap;
		typedef std::map< std::wstring, CArchive* >				ArchiveMap;
	protected:
		ArchiveFactoryMap			m_ArchFactories;	// ��Ч���ĵ�����
		ArchiveMap					m_Archives;			// ��ǰ�Ѽ��ص��ĵ�
	public:
		CArchiveManager();
		~CArchiveManager();
		//! ��ȡһ���ĵ�
		//@param [IN] p_ArchiveType �ĵ����� ����zip File
		CArchive* Load( const std::wstring& p_Filename, const std::wstring& p_ArchiveType );

		//! �ͷ��ĵ�
		void Unload( CArchive* p_pArch );

		//! �ͷ��ĵ�
		void Unload( const std::wstring& p_szFileName );

		//! ����ĵ�����
		void AddArchiveFactory( CArchiveFactory* p_pFactory );

		//! �õ��ĵ�ӳ���
		CArchiveManager::ArchiveMap& GetArchiveMap();
	private:
		DECLARE_SINGLETON_CLASS( CArchiveManager );
	};
}

typedef FK2DEngine::TSingleton< FK2DEngine::CArchiveManager >	SSArchiveManager;