/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	PRTDataChunk
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�������ݿ���
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//�������ݿ���
	class FK_DLL PRTDataChunk : public DataChunk
	{
	protected:
		BYTE		mpPassword[32];		//��������

	public:
		PRTDataChunk();
		PRTDataChunk( PRTDataChunk& refDataChunk );
		PRTDataChunk( size_t nSize );
		~PRTDataChunk();

		//���ö�д�������루���������ַ�����
		void SetPassword( const char* szPassword );

		//���ö�д��������
		void SetPassword( const BYTE pPassword[16] );

		//�����д��������
		void ClearPassword();

		//д�����ݵ��������ݿ�
		void Code( const void* pBuf, size_t nLen );

		//�ӱ������ݿ��������
		void Decode( void* pBuf, size_t nLen );

		//��ֵ������
		PRTDataChunk& operator = ( const PRTDataChunk& refDataChunk );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
