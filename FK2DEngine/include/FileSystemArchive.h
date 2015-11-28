/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	FileSystemArchive
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "Archive.h"
#include "ArchiveFactory.h"
#include <queue>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	#define FK_MAX_PATH		256
	//--------------------------------------------------------------------
	//! �ļ�ϵͳ�ĵ�
	//@remarks ֧�ֶ�ȡ�ļ���
	class CFileSystemArchive : public CArchive
	{
		typedef std::deque< std::wstring >			DirectoryStack;
	protected:
		std::wstring			m_szBasePath;			// ����·��
		mutable DirectoryStack	m_DirectoryStack;		// Ŀ¼��ջ
		mutable char			m_szPath[FK_MAX_PATH];	// ·��
	public:
		CFileSystemArchive( const std::wstring& p_szName, const std::wstring& p_szType );
		~CFileSystemArchive();
	public:
		bool 				IsCaseSensitive() const;
		void 				Load();
		void 				Unload();
		DataStreamPtr		Open( const std::wstring& p_FileName ) const;
		//! ����Zip�ļ��������������֪
		//@params [IN] p_ZipFileName Zip�ļ�·����
		//@params [IN] p_FileName ��Ҫ�����ļ�����·��Ϊ���zip�ļ������·������
		//@params [IN] szPassword ע�⣬����ֻ�����ǵ��ֽ�
		DataStreamPtr		OpenZipFile( const std::wstring& p_ZipFileName, const std::wstring& p_FileName, const std::string& szPassword = "" ) const;
		StringVectorPtr		List( bool p_bRecursive = true );
		FileInfoListPtr		ListFileInfo( bool p_bRecursive = true );
		StringVectorPtr		Find( const std::wstring& p_Pattern, bool p_bRecursive = true );
		FileInfoListPtr		FindFileInfo( const std::wstring& p_Pattern, bool p_bRecursive = true );
		bool				Exists( const std::wstring& p_szFilename );
	protected:
		void	FindFiles( const std::wstring& p_szPattern, bool p_bRecursive, StringVector* p_pSimpleList,
			FileInfoList* p_pDetailList, const std::wstring& p_CurrentDir = L"" );
		void	ChangeDirectory( const std::wstring& p_szDir ) const;
		void	PushDirectory( const std::wstring& p_szDir ) const;
		void	PopDirectory() const;
	};
}