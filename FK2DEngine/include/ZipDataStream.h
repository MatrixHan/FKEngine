/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ZipDataStream
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "DataStream.h"
#include "Archive.h"
//--------------------------------------------------------------------
typedef struct zzip_dir		ZZIP_DIR;
typedef struct zzip_file	ZZIP_FILE;
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	class CZipDataStream : public CDataStream
	{
	protected:
		ZZIP_FILE*				m_pZipFile;
	public:
		CZipDataStream( ZZIP_FILE* p_pZipFile, unsigned int p_unUncompressedSize );
		CZipDataStream( const std::wstring& p_szName, ZZIP_FILE* p_pZipFile, unsigned int p_unUncompressedSize );
		~CZipDataStream();
	public:
		unsigned int Read( void* p_pBuf, unsigned int p_unCount );
		void Skip( long p_lCount );
		void Seek( unsigned int p_unPos );
		unsigned int Tell() const;
		bool Eof() const;
		void Close();
	};
	//--------------------------------------------------------------------
}