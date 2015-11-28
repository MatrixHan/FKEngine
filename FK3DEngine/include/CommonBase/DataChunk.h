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
*	�ļ�˵����	���ݿ���
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//���ݿ���
	class FK_DLL DataChunk
	{
	protected:
		BYTE*		mpData;			//���ݻ���ָ��
		BYTE*		mpPos;			//��ǰ��ȡλ��ָ��
		size_t		mActualLen;		//ʵ���ڴ�ռ��С
		size_t		mProtectedLen;	//��󱣻���д����
		size_t		mRemainLen;		//��ǰ��ȡλ�õ���β���ݳ���

	public:
		DataChunk();
		DataChunk( DataChunk& refDataChunk );
		DataChunk( size_t nSize );
		virtual ~DataChunk();

		//�������ݿ��ڴ�
		void Allocate( size_t nSize );

		//�ͷ����ݿ��ڴ�
		void Free();

		//д�����ݵ����ݿ�
		void Write( const void* pBuf, size_t nLen );

		//�����ݿ��������
		void Read( void* pBuf, size_t nLen );

		//��ȡ��ǰ��дָ�루�������ܵ�������
		BYTE* GetPointer();

		//���õ�ǰ��дָ��λ�ã�����������󱣻���д��Χ��
		void SetPosition( long Offset, BasePos eBasePos = BP_Begin );

		//��ȡ��ǰ��дָ��λ��
		size_t GetPosition();

		//�������ݿ���󱣻���д���ȣ�����������ǰ�����ڴ��С��
		void SetProtectedLen( size_t NewLen );

		//��ȡ������д����
		size_t GetProtectedLen();

		//���·������ݿ��ڴ棨�����ڲ���дָ�����λ�ò����ñ�����Χ��
		BYTE* Reallocate( size_t nSize );

		//��ֵ������
		DataChunk& operator = ( const DataChunk& refDataChunk );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
