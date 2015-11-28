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
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/CommonBase/CommonBaseInsideHead.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	PRTDataChunk::PRTDataChunk()
		: DataChunk()
	{
		ClearPassword();
	}
	//--------------------------------------------------------------------------------------------------------------
	PRTDataChunk::PRTDataChunk( PRTDataChunk& refDataChunk )
	{
		*this = refDataChunk;
	}
	//--------------------------------------------------------------------------------------------------------------
	PRTDataChunk::PRTDataChunk( size_t nSize )
		: DataChunk( nSize )
	{
		ClearPassword();
	}
	//--------------------------------------------------------------------------------------------------------------
	PRTDataChunk::~PRTDataChunk()
	{
		ClearPassword();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ö�д��������
	void PRTDataChunk::SetPassword( const char* szPassword )
	{
		//ʹ�� MD5 �㷨���ַ���תΪ 128 λ��Կ
		Misc::GetMD5Key( mpPassword, szPassword );

		//����Ϊ 256 λ˫�����ظ���Կ
		memcpy( mpPassword + 16, mpPassword, 16 );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ö�д��������
	void PRTDataChunk::SetPassword( const BYTE pPassword[16] )
	{
		memcpy( mpPassword, pPassword, 16 );
		memcpy( mpPassword + 16, pPassword, 16 );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����д��������
	void PRTDataChunk::ClearPassword()
	{
		memset( mpPassword, 0, sizeof(mpPassword) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//д�����ݵ��������ݿ�
	void PRTDataChunk::Code( const void* pBuf, size_t nLen )
	{
		//���д�����ݳ��ȴ���ʣ��ռ䳤���򱨴�
		if( nLen > mRemainLen )
			Except( Exception::ERR_INVALIDPARAMS, "д�����ݳ��ȴ��ڱ������ݿ�ʣ��ռ䳤�ȣ�д��Ƿ���" );

		//��ȡ��ǰ��ȡλ�õĵ�һ�����봦���ֽ�λ��
		BYTE* pPassword = mpPassword + ( (int)( mpPos - mpData ) % 16 );

		//�����ݸ��Ƶ�������
		memcpy( mpPos, pBuf, nLen );

		//��������
		BYTE* pData = mpPos;
		UINT nRound = (UINT)nLen >> 4;
		UINT nRem = (UINT)nLen % 16;

		//���� 16 �ֽڶ�������
		for( UINT i=0; i<nRound; ++i )
		{
			*(UINT*)pData += *(UINT*)(pPassword);
			pData += 4;
			*(UINT*)pData += *(UINT*)(pPassword+4);
			pData += 4;
			*(UINT*)pData += *(UINT*)(pPassword+8);
			pData += 4;
			*(UINT*)pData += *(UINT*)(pPassword+12);
			pData += 4;
		}

		//����ʣ��δ�������ݴ���
		for( UINT i=0; i<nRem; ++i, ++pData )
		{
			*pData += pPassword[i];
			++pData;
		}

		mpPos += nLen;
		mRemainLen -= nLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ӱ������ݿ��������
	void PRTDataChunk::Decode( void* pBuf, size_t nLen )
	{
		//�����ȡ���ݳ��ȴ���ʣ��ռ䳤���򱨴�
		if( nLen > mRemainLen )
			Except( Exception::ERR_INVALIDPARAMS, "��ȡ���ݳ��ȴ��ڱ������ݿ�ʣ��ռ䳤�ȣ���ȡ�Ƿ���" );

		//��ȡ��ǰ��ȡλ�õĵ�һ�����봦���ֽ�λ��
		BYTE* pPassword = mpPassword + ( (int)( mpPos - mpData ) % 16 );

		//�����ݸ��Ƶ�������
		memcpy( pBuf, mpPos, nLen );

		//��������
        BYTE* pData = (BYTE*)pBuf;	
		UINT nRound = (UINT)nLen >> 4;
		UINT nRem = (UINT)nLen % 16;

		//���� 16 �ֽڶ�������
		for( UINT i=0; i<nRound; ++i )
		{
			*(UINT*)pData -= *(UINT*)(pPassword);
			pData += 4;
			*(UINT*)pData -= *(UINT*)(pPassword+4);
			pData += 4;
			*(UINT*)pData -= *(UINT*)(pPassword+8);
			pData += 4;
			*(UINT*)pData -= *(UINT*)(pPassword+12);
			pData += 4;
		}

		//����ʣ��δ�������ݴ���
		for( UINT i=0; i<nRem; ++i, ++pData )
		{
			*pData -= pPassword[i];
			++pData;
		}

		mpPos += nLen;
		mRemainLen -= nLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ֵ������
	PRTDataChunk& PRTDataChunk::operator = ( const PRTDataChunk& refDataChunk )
	{
		//���û��ำֵ������
		DataChunk::operator =( refDataChunk );

		//��������
		memcpy( mpPassword, refDataChunk.mpPassword, sizeof(mpPassword) );

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
