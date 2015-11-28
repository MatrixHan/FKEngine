/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	VertexBuffer
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
	//���㻺����
	class FK_DLL VertexBuffer
	{
	public:
		UINT	mnBufLen;		//���㻺���С
		UINT	mVerSize;		//ÿ������Ĵ�С
		bool	mbDynamic;		//�Ƿ�Ϊ��̬���㻺��
		bool	mbSoftProc;		//�Ƿ�Ϊ������㴦��

	public:
		VertexBuffer();
		virtual ~VertexBuffer() = 0;

		//�������㻺��
		virtual void CreateVertexBuffer( UINT nVerSize, UINT nVerNum, bool bDynamic = false, bool bSoftProc = false ) = 0;

		//�ͷŶ��㻺��
		virtual void ReleaseVertexBuffer() = 0;

		//�������㻺��
		virtual void* Lock( UINT nOffsetVer, UINT nLockVer, bool bNoOverwrite = false ) = 0;

		//�������㻺��
		virtual void Unlock() = 0;

		//д�����ݵ����㻺��
		void WriteData( UINT nOffsetVer, void* pData, UINT nVerNum, bool bNoOverwrite = false );
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< VertexBuffer* >	VertexBufferList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
