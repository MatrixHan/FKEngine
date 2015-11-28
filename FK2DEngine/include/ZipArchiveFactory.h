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

#pragma once

//--------------------------------------------------------------------
#include "ZipArchive.h"
#include "ArchiveFactory.h"
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	//! Zip�ĵ�������
	class CZipArchiveFactory : public CArchiveFactory
	{
	public:
		virtual ~CZipArchiveFactory() {}
	public:
		const std::wstring& GetType() const;
		CArchive* CreateInstance( const std::wstring& p_szName );
		void DestroyInstance( CArchive* p_pPtr );
	};
	//--------------------------------------------------------------------
}