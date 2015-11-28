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

#pragma once

//--------------------------------------------------------------------
#include "ArchiveFactory.h"
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	//! �ļ�ϵͳ�ĵ�������
	class CFileSystemArchiveFactory : public CArchiveFactory
	{
	public:
		virtual ~CFileSystemArchiveFactory(){}
	public:
		const std::wstring& GetType() const;
		CArchive* CreateInstance( const std::wstring& p_szName );
		void DestroyInstance( CArchive* p_pPtr );
	};
	//--------------------------------------------------------------------
}