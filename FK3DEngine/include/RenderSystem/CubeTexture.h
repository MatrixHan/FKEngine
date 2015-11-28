/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	CubeTexture
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
	class FK_DLL CubeTexture : public BaseTexture
	{
	public:
		UINT		mEdgeLength;	//������߳�

	public:
		CubeTexture( UINT nEdgeLength, PixelFormat ePixelFormat, UINT nNumLevel, TextureUsage Type );
		virtual ~CubeTexture() = 0;

		//��ȡ����������߳�
		UINT GetEdgeLength();

		//���ָ����������Ϊĳ��ɫ
		void FillColor( CubeFace eFace, DWORD color = 0, RECT* pFillRect = NULL, UINT nLevel = 0 );

		//��������
		virtual void LockRect( CubeFace eFace, void** ppBuf, UINT* pPitch, RECT* pLockRect = NULL,
			UINT nLevel = 0, bool bDiscardLock = false ) = 0;

		//��������
		virtual void UnlockRect( CubeFace eFace, UINT nLevel = 0 ) = 0;
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< CubeTexture* >	CubeTextureList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
