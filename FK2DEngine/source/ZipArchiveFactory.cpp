/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ZipArchiveFactory
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../Include/Archive.h"
#include "../include/ZipArchive.h"
#include "../include/ZipArchiveFactory.h"

//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	const std::wstring& CZipArchiveFactory::GetType() const
	{
		static std::wstring szName = L"Zip";
		return szName;
	}
	//--------------------------------------------------------------------
	CArchive* CZipArchiveFactory::CreateInstance( const std::wstring& p_szName )
	{
		 return new CZipArchive( p_szName, L"Zip" );
	}
	//--------------------------------------------------------------------
	void CZipArchiveFactory::DestroyInstance( CArchive* p_pPtr )
	{
		delete p_pPtr;
	}
	//--------------------------------------------------------------------
}