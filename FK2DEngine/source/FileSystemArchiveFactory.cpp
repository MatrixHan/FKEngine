/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	FileSystemArchiveFactory
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../Include/FileSystemArchive.h"
#include "../include/FileSystemArchiveFactory.h"

//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	const std::wstring& CFileSystemArchiveFactory::GetType() const
	{
		static std::wstring szName = L"FileSystem";
		return szName;
	}
	//--------------------------------------------------------------------
	CArchive* CFileSystemArchiveFactory::CreateInstance( const std::wstring& p_szName )
	{
		return new CFileSystemArchive( p_szName, L"FileSystem" );
	}
	//--------------------------------------------------------------------
	void CFileSystemArchiveFactory::DestroyInstance( CArchive* p_pPtr )
	{
		delete p_pPtr;
	}
	//--------------------------------------------------------------------
}