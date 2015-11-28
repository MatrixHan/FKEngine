/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Viewport
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

#include "../RenderWrapper/Camera.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//�ӿ���
	class FK_DLL Viewport
	{
	public:
		DWORD		mLeft;				//�ӿ���߾�
		DWORD		mTop;				//�ӿ��ϱ߾�
		DWORD		mWidth;				//�ӿڿ�
		DWORD		mHeight;			//�ӿڸ�
		float		mMinZ;				//��С��Ⱦ���ֵ
		float		mMaxZ;				//�����Ⱦ���ֵ
		float		mAspect;			//�ӿں��ݱ�

		Matrix4		mViewportMat;		//�ӿھ���

		Camera*		mpCamera;			//�ӿڵ������

		ARGB		mdwClearColor;		//�ӿ������ɫ
		bool		mbClearPerFrame;	//�Ƿ�����Ⱦÿһ֡ǰ���ԭ��ͼ��

	public:
		Viewport();
		Viewport( DWORD dwLeft, DWORD dwTop, DWORD dwWidth, DWORD dwHeight, float fMinZ, float fMaxZ );

		//�����ӿ������
		void SetCamera( Camera* pCamera, bool bAutoSetProj = true );

		//�����ӿڷ�Χ
		void SetViewportRect( DWORD dwLeft, DWORD dwTop, DWORD dwWidth, DWORD dwHeight, float fMinZ, float fMaxZ );

		//���������ɫ
		void SetClearColor( const ColorValue& refColor );

		//�����Ƿ�����Ⱦÿһ֡ǰ���ԭ��ͼ��
		void EnableClear( bool bEnable = true );

		//��ȡ��Ļ����������ռ��ͶӰ����
		bool GetWorldRayFromScreenPoint( LONG nX, LONG nY, Ray3* pRay3 );

	protected:
		//�����ӿ�
		void FKFastcall _UpdateViewport();
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Viewport* >		ViewportList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
