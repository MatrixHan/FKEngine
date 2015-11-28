/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Archive
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "DataStream.h"
#include "FKSharedPtr.h"
#include "StringConversion.h"
#include <map>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	class CArchive;
	//--------------------------------------------------------------------
	//! �ļ����ļ�����Ϣ
	struct SFileInfo
	{
		CArchive*		m_pArchive;				// �ĵ�ָ��
		std::wstring	m_szFileName;			// �ļ�ȫ��
		std::wstring	m_szPath;				// �ļ�·��
		std::wstring	m_szBaseName;			// �ļ���
		unsigned int	m_unCompressedSize;		// ѹ�����С
		unsigned int	m_unUnCompressedSize;	// ѹ��ǰ��С
	};
	//--------------------------------------------------------------------
	typedef std::vector< SFileInfo >			FileInfoList;
	typedef TSharedPtr< FileInfoList >			FileInfoListPtr;
	//--------------------------------------------------------------------
	//! �ĵ���
	//@remarks һ���ĵ�������һ���ļ��У�һ��ѹ���ļ�������Զ���ļ�
	class CArchive
	{
	protected:
		std::wstring				m_szName;	// �ĵ�����
		std::wstring				m_szType;	// �ĵ�����
	public:
		//! ���캯��
		//@remarks ���鲻Ҫֱ�ӵ��ã�ʹ��Factory��������
		CArchive( const std::wstring& p_szName, const std::wstring& p_szType )
			: m_szType( p_szType )
			, m_szName( p_szName )
		{

		}

		virtual ~CArchive()
		{

		}

	public:
		const std::wstring& GetName()
		{
			return m_szName;
		}
		
		const std::wstring& GetType()
		{
			return m_szType;
		}

		//! �Ƿ����д�Сд
		virtual bool IsCaseSensitive() const = 0;

		//! ��ȡ�ĵ�
		virtual void Load() = 0;

		//! �ͷ��ĵ�
		virtual void Unload() = 0;

		//! ��ȡһ���ĵ���һ������
		virtual DataStreamPtr Open( const std::wstring& p_szFileName ) const = 0;

		//! �ĵ��������ļ����б�
		//@param [IN] p_bRecursive �Ƿ�����ݹ����������ļ����µ��ļ�
		virtual StringVectorPtr List( bool p_bRecursive = true ) = 0;

		//! �ĵ��������ļ���ϸ��Ϣ���б�
		virtual FileInfoListPtr ListFileInfo( bool p_bRecursive = true ) = 0;

		//! ������ģʽ��ƥ��������ļ�
		//@param [IN] p_Pattern �ο���ģʽ��������ʹ��'*'��
		virtual StringVectorPtr Find( const std::wstring& p_Pattern, bool p_bRecursive = true ) = 0;

		//! ������ģʽ��ƥ��������ļ���ϸ��Ϣ
		virtual FileInfoListPtr FindFileInfo( const std::wstring& p_Pattern, bool p_bRecursive = true ) = 0;

		//! ����ļ��Ƿ����
		//@note ��Ҫָ������������ļ����֣����ܽ����ļ���
		virtual bool Exists( const std::wstring& p_szFilename ) = 0;
	};
	//--------------------------------------------------------------------
}