/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	IndexBuffer
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//����������
	class FK_DLL IndexBuffer
	{
	public:
		UINT		mnBufLen;		//���������С
		IndexType	mIndexType;		//������������
		UINT		mIndexSize;		//��������ֵ���ݳ���
		bool		mbDynamic;		//�Ƿ�Ϊ��̬����������

	public:
		IndexBuffer();
		virtual ~IndexBuffer() = 0;

		//������������
		virtual void CreateIndexBuffer( UINT nIndexNum, IndexType eIndexType, bool bDynamic = false, bool bSoftProc = false ) = 0;

		//�ͷ���������
		virtual void ReleaseIndexBuffer() = 0;

		//������������
		virtual void* Lock( UINT nOffsetNum, UINT nLockNum, bool bNoOverwrite = false ) = 0;

		//������������
		virtual void Unlock() = 0;

		//д�����ݵ���������
		void WriteData( UINT nOffsetNum, void* pData, UINT nIndexNum, bool bNoOverwrite = false );
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< IndexBuffer* >	IndexBufferList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
