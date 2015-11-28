/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	FactoryObject
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include <xstring>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//! ���󹤳���
	template< typename T >
	class TFactoryObject
	{
	public:
		virtual ~TFactoryObject()
		{

		}

		//! ���ع�������
		virtual const std::wstring& GetType() const = 0;

		//! ����һ������
		virtual T* CreateInstance( const std::wstring& p_szName ) = 0;

		//! ���ٱ�����������һ������
		virtual void DestroyInstance( T* p_pPtr ) = 0;
	};
}