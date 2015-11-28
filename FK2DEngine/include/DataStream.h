/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	DataStream
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "FKSharedPtr.h"
#include "StringConversion.h"
#include <list>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	// ÿ�ζ�����Ĭ�ϴ�С
	#define FK_STREAM_TEMP_SIZE	512

	//! ��������ȡ��
	//@note ������̰߳�ȫ
	class CDataStream
	{
	protected:
		std::wstring			m_szName;	// ������
		unsigned int			m_unSize;	// �������ݳ���( ��������Ȳ��� )
	public:
		CDataStream()
			: m_unSize( 0 )
		{

		}

		CDataStream( const std::wstring& p_Name )
			: m_szName( p_Name )
			, m_unSize( 0 )
		{

		}

		virtual ~CDataStream()
		{

		}

		const std::wstring& GetName() const
		{
			return m_szName;
		}

		//! ���ش����ж�ȡ�����ݳ��ȣ�0 ����ȷ��
		unsigned int Size() const
		{
			return m_unSize;
		}

		//! ������������
		template< typename T >
		CDataStream& operator >> ( T& val );

		//! ��ȡ�ļ����������ļ�β����
		//@returns �ɹ���ȡ���ֽ���
		virtual unsigned int Read( void* p_pBufBegin, unsigned int p_unCount ) = 0;

		//! �����ж�ȡһ��
		//@note ʹ�ø÷�ʽ����������ʹ�ö����ƴ���
		virtual unsigned int ReadLine( char* p_pBuf, unsigned int p_unMaxCount, const std::wstring& p_Delim = L"\n" );

		//! �����ж�ȡһ�У�Ĭ��ɾ��ǰ��ո�
		virtual std::wstring GetLine( bool p_bTrimAfter = true );

		//! �õ�һ���ַ��������ַ�����������ȫ������
		virtual std::wstring GetAllString();

		//! ����һ��
		//@return �������ֽ���
		virtual unsigned int SkipLine( const std::wstring& p_Delim = L"\n" );
		
		//! �����ƶ��ֽ���������
		//@remark ��������Ϊ�������������Ϊ��ǰ��
		virtual void Skip( long p_lCount ) = 0;

		//! �ض�λ����λ��
		virtual void Seek( unsigned int p_unPos ) = 0;

		//! ���ص�ǰ���ݶ�ȡλ��
		virtual unsigned int Tell() const = 0;

		//! �ж��������Ƿ����
		virtual bool Eof() const = 0;

		//! �ر�������
		virtual void Close() = 0;
	};

	//! ������ֻ��ָ��
	typedef TSharedPtr< CDataStream >			DataStreamPtr;
	//! ��������
	typedef std::list< DataStreamPtr >			DataStreamList;
	//! ������������ָ��
	typedef TSharedPtr< DataStreamList >		DataStreamListPtr;
}