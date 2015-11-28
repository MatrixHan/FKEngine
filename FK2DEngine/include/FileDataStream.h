/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	FileDataStream
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "DataStream.h"

//--------------------------------------------------------------------
namespace FK2DEngine
{
	class CFileDataStream : public CDataStream
	{
	protected:
		std::ifstream*			m_pStream;			// ԭʼ������
		char*					m_pNormalStream;	// ԭʼ�������������ڴ��ȡ�����޷�ʹ��ifstreamʱ���ñ�ָ�룩
		char*					m_pCurrent;			// ��ʹ�� char* �ڴ����ʱ����ֵ��Ч����¼�ļ���ǰָ��
		bool					m_bFreeOnClose;		// �Ƿ��ڹر���ʱɾ��������
	public:
		CFileDataStream( std::ifstream* p_pStream, bool p_bFreeOnClose = true );
		//! �ӱ�׼�������й��첢ָ��һ������
		//@param [IN] p_szName ָ����������
		CFileDataStream( const std::wstring& p_szName, std::ifstream* p_pS, bool p_bFreeOnClose );
		CFileDataStream( const std::wstring& p_szName, std::ifstream* p_pS,
			unsigned int p_unSize, bool p_bFreeOnClose );
		CFileDataStream( const std::wstring& p_szName, char* p_pBuf, 
			unsigned int p_unSize, bool p_bFreeOnClose );
		~CFileDataStream();
	public:
		unsigned int Read( void* p_pBuf, unsigned int p_unCount );
		unsigned int ReadLine( char* p_pBuf, unsigned int p_unMaxCount, const std::wstring& p_Delim = L"\n" );
		void Skip( long p_lCount );
		void Seek( unsigned int p_unPos );
		unsigned int Tell() const;
		bool Eof() const;
		void Close();
	};
}

