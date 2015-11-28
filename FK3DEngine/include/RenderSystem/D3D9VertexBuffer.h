/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9VertexBuffer
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	D3D9 ���㻺����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//D3D9 ���㻺����
	class FK_DLL D3D9VertexBuffer : public VertexBuffer
	{
	public:
		IDirect3DVertexBuffer9*		mpD3D9VertexBuffer;

	public:
		D3D9VertexBuffer();
		~D3D9VertexBuffer();

		//�������㻺��
		void CreateVertexBuffer( UINT nVerSize, UINT nVerNum, bool bDynamic = false, bool bSoftProc = false );

		//�ͷŶ��㻺��
		void ReleaseVertexBuffer();

		//�������㻺��
		void* Lock( UINT nOffsetVer, UINT nLockVer, bool bNoOverwrite = false );

		//�������㻺��
		void Unlock();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
