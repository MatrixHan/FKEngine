/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	DataChunk
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
	DataChunk::DataChunk()
		: mpData		(NULL)
		, mpPos			(NULL)
		, mActualLen	(0)
		, mProtectedLen	(0)
		, mRemainLen	(0)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	DataChunk::DataChunk( DataChunk& refDataChunk )
	{
		*this = refDataChunk;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Զ������ڴ湹�캯��
	//
	//nSize��	�����ڴ��С
	DataChunk::DataChunk( size_t nSize )
		: mpData		(NULL)
		, mActualLen	(nSize)
		, mProtectedLen	(nSize)
		, mRemainLen	(nSize)
	{
		//���Ϊ DEBUG ģʽ�����Ƿ��ͷ����ڴ�
#ifdef _DEBUG
		if( mpData != NULL )
			Except( Exception::ERR_INTERNAL_ERROR, "�������ݿ飨DataChunk���ڴ�֮ǰû���ͷ���ǰ������ڴ档" );
#endif
		//�����ڴ�
		mpData = (BYTE*)malloc(nSize);
		if( mpData == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "���ݿ飨DataChunk���޷����䵽�㹻���ڴ档" );

		mpPos = mpData;
	}
	//--------------------------------------------------------------------------------------------------------------
	DataChunk::~DataChunk()
	{
		SafeFree( mpData );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������ݿ��ڴ�
	void DataChunk::Allocate( size_t nSize )
	{
		//���Ϊ DEBUG ģʽ�����Ƿ��ͷ����ڴ�
#ifdef _DEBUG
		if( mpData != NULL )
			Except( Exception::ERR_INTERNAL_ERROR, "�������ݿ飨DataChunk���ڴ�֮ǰû���ͷ���ǰ������ڴ档" );
#endif
		//�����ڴ�
		mpData = (BYTE*)malloc(nSize);
		if( mpData == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "���ݿ飨DataChunk���޷����䵽�㹻���ڴ档" );

		mpPos = mpData;
		mRemainLen = mProtectedLen = mActualLen = nSize;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷ����ݿ��ڴ�
	void DataChunk::Free()
	{
		SafeFree( mpData );
		mpPos = NULL;
		mProtectedLen = mActualLen = mRemainLen = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//д�����ݵ����ݿ�
	void DataChunk::Write( const void* pBuf, size_t nLen )
	{
		//���д�����ݳ��ȴ���ʣ��ռ䳤���򱨴�
		if( nLen > mRemainLen )
			Except( Exception::ERR_INVALIDPARAMS, "д�����ݳ��ȴ������ݿ�ʣ��ռ䳤�ȣ�д��Ƿ���" );

		memcpy( mpPos, pBuf, nLen );
		mpPos += nLen;
		mRemainLen -= nLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ݿ��������
	void DataChunk::Read( void* pBuf, size_t nLen )
	{
		//�����ȡ���ݳ��ȴ���ʣ��ռ䳤���򱨴�
		if( nLen > mRemainLen )
			Except( Exception::ERR_INVALIDPARAMS, "��ȡ���ݳ��ȴ������ݿ�ʣ��ռ䳤�ȣ���ȡ�Ƿ���" );

		memcpy( pBuf, mpPos, nLen );
		mpPos += nLen;
		mRemainLen -= nLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ǰ��дָ�루�������ܵ�������
	BYTE* DataChunk::GetPointer()
	{
		return mpPos;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���õ�ǰ��дָ��λ�ã�����������󱣻���д��Χ��
	void DataChunk::SetPosition( long Offset, BasePos eBasePos )
	{
		long TmpRemainLen = (long)mRemainLen;

		//�ж��ƶ�ƫ������׼����
		switch (eBasePos)
		{
			//��ʼλ��
		case BP_Begin:
			{
				TmpRemainLen = (long)mProtectedLen - Offset;
				break;
			}
			//��βλ��
		case BP_End:
			{
				TmpRemainLen = -Offset;
				break;
			}
			//��ǰ��дλ��
		case BP_Curpos:
			{
				TmpRemainLen -= Offset;
				break;
			}
		default:
			Except( Exception::ERR_INVALIDPARAMS, "�Ƿ������ݿ��дָ���ƶ���׼λ�����͡�" );
		}

		if( TmpRemainLen > (long)mProtectedLen || TmpRemainLen < 0 )
			Except( Exception::ERR_INVALIDPARAMS, "���������ݿ��дָ���ƶ���������д��Χ֮�⡣" );

		//�ƶ���дָ��λ��
		mRemainLen = (size_t)TmpRemainLen;
		mpPos = mpData + mProtectedLen - mRemainLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ǰ��дָ��λ��
	size_t DataChunk::GetPosition()
	{
		return mProtectedLen - mRemainLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������ݿ���󱣻���д���ȣ�����������ǰ�����ڴ��С��
	void DataChunk::SetProtectedLen( size_t NewLen )
	{
		if( NewLen > mActualLen )
			Except( Exception::ERR_INTERNAL_ERROR, "���������õ����ݿ���󱣻���д���ȴ���ʵ�ʷ�����ڴ��С��" );

		//������� ����/���� ��ʣ���д����
		long TmpRemainLen = (long)mRemainLen;
		TmpRemainLen += (long)NewLen - (long)mProtectedLen;

		//������ڱ������ȵļ�С��ɶ�дָ���ڱ�����Χ֮�������ƶ�����β
		mRemainLen = ( TmpRemainLen < 0 ) ? 0 : (size_t)TmpRemainLen;

		mProtectedLen = NewLen;
		mpPos = mpData + mProtectedLen - mRemainLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ������д����
	size_t DataChunk::GetProtectedLen()
	{
		return mProtectedLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���·������ݿ��ڴ棨�����ڲ���дָ�����λ�ò����ñ�����Χ��
	//
	//nSize��	�µ����ݿ��С
	//����ֵ��	�µ���Զ�дָ�루���λ����ԭָ����ͬ��
	BYTE* DataChunk::Reallocate( size_t nSize )
	{
		//�����ڴ�
		mpData = (BYTE*)realloc( mpData, nSize );
		if( mpData == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "���ݿ飨DataChunk���޷����·��䵽�㹻���ڴ档" );

		//���ñ�����ΧΪʵ���ڴ��С
		mActualLen = nSize;

		//������� ����/���� ��ʣ���д����
		long TmpRemainLen = (long)mRemainLen;
		TmpRemainLen += (long)mActualLen - (long)mProtectedLen;

		//������ڱ������ȵļ�С��ɶ�дָ���ڱ�����Χ֮�������ƶ�����β
		mRemainLen = ( TmpRemainLen < 0 ) ? 0 : (size_t)TmpRemainLen;

		//�����ڲ���дָ�����λ��
		mProtectedLen = mActualLen;
		mpPos = mpData + mProtectedLen - mRemainLen;

		return mpPos;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ֵ������
	DataChunk& DataChunk::operator = ( const DataChunk& refDataChunk )
	{
		SafeFree( mpData );

		mActualLen		= refDataChunk.mActualLen;
		mProtectedLen	= refDataChunk.mProtectedLen;
		mRemainLen		= refDataChunk.mRemainLen;

		mpData = (BYTE*)malloc( mActualLen );
		if( mpData == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "���ݿ飨DataChunk���޷����䵽�㹻���ڴ档" );

		memcpy( mpData, refDataChunk.mpData, mActualLen );

		mpPos = mpData + mProtectedLen - mRemainLen;

		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
