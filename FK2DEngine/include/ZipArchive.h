/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ZipArchive
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
//--------------------------------------------------------------------
typedef struct zzip_dir		ZZIP_DIR;
typedef struct zzip_file	ZZIP_FILE;
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	//! Zip�ĵ���
	class CZipArchive : public CArchive
	{
	protected:
		ZZIP_DIR*			m_pZipDir;					// Zip���ļ�
		FileInfoList		m_pFileList;
	public:
		CZipArchive( const std::wstring& p_Name, const std::wstring& p_Type );
		~CZipArchive();
	public:
		bool 				IsCaseSensitive() const;
		void 				Load();
		void 				Unload();
		DataStreamPtr		Open( const std::wstring& p_FileName ) const;
		StringVectorPtr		List( bool p_bRecursive = true );
		FileInfoListPtr		ListFileInfo( bool p_bRecursive = true );
		StringVectorPtr		Find( const std::wstring& p_Pattern, bool p_bRecursive = true );
		FileInfoListPtr		FindFileInfo( const std::wstring& p_Pattern, bool p_bRecursive = true );
		bool				Exists( const std::wstring& p_szFilename );

		void				CheckZipError( int p_nZipError, const std::wstring& p_szOperation )const;
	};
	//--------------------------------------------------------------------
}