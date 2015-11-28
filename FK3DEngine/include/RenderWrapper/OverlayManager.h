/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	OverlayManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	ƽ��ͼ�������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

#include "UVASprite.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//ƽ��ͼ����Ⱦ���ݽṹ
	struct OverlayRenderOp
	{
		UINT				Offset;		//��Ⱦ����ƫ����
		UINT				NumPrim;	//��ȾͼԪ����
		PrimitiveType		DrawType;	//��ȾͼԪ����
		TextureFilterType	FilterType;	//�����������
		Texture*			pTexture;	//��Ⱦ����ָ��
	};
	//--------------------------------------------------------------------------------------------------------------
	//ƽ��ͼ�������
	class FK_DLL OverlayManager : public Singleton< OverlayManager >
	{
	public:
		FileObject*			mpOverlayPack;	//ƽ��ͼ�����ļ�ָ��
		ImageDecoder		mImgDecoder;	//ͼ�������
		UINT				mNumRenderVer;	//ÿ֡��Ⱦ�Ķ�������

		UINT				mRenderWidth;	//ƽ��ͼ����Ⱦ����
		UINT				mRenderHeight;	//ƽ��ͼ����Ⱦ��߶�

		RenderState			mRenderState;	//ƽ��ͼ����Ⱦ״̬

	protected:
		OverlayList			mOverlayList;	//ƽ��ͼ���б�

		JointList			mJointList;		//ƴ��ͼ���б�
		SpriteList			mSpriteList;	//�����б�

		SpriteSetList		mSpriteSetList;	//���鼯�б�
		UVASpriteList		mUVASprite;		//���� UV �����������б�

		Matrix4				mWorldMatrix;	//ƽ��ͼ����Ⱦ�������
		Matrix4				mProjMatrix;	//ƽ��ͼ����ȾͶӰ����
		Matrix4				mViewMatrix;	//ƽ��ͼ����Ⱦ�۲����

		VertexBuffer*		mpVertexBuf;	//���㻺��
		VertexDeclaration*	mpVertexDecl;	//��������
		UINT				mMaxNumVer;		//���㻺����󶥵�����
		UINT				mOffsetVer;		//��ǰ֡ƫ�ƶ�����

	public:
		OverlayManager();
		~OverlayManager();

		//����������ļ�
		void SetOverlayPack( FileObject* pFile );

		//��ʼ��ƽ��ͼ�������
		void Initialize( UINT nMaxNumVer = 25000 );

		//���¶�������
		void _UpdateVertexData();

		//��Ⱦ����ƽ��ͼ��
		void _RenderAllOverlays();

		//������Ⱦ��ߴ�
		void SetRenderPlaneSize( UINT nWidth, UINT nHeight );

		//����ƽ��ͼ�񶯻�֡��ʱ
		void _UpdateFrameTime( float fFrameTime );

		//������ƴ��ͼ��
		JointSurface* CreateJointSurface( float fLeft, float fTop, float fWidth, float fHeight,
			ZOrderType eZType, OverlaySurface* pZRefOverlay, UINT nTexWidth, UINT nTexHeight, PixelFormat ePixelFormat,
			TextureFilterType eFilter = TFT_POINT, bool bDynamic = false, DWORD dwColor = 0xFFFFFFFF );

		//�����վ��鼯
		SpriteSet* CreateSpriteSet( UINT nTexWidth, UINT nTexHeight, PixelFormat ePixelFormat,
			UINT InitSpriteNum, UINT AddSpriteNum, TextureFilterType eFilter = TFT_LINEAR );

		//��ͼ���ļ�������ƴ��ͼ��
		JointSurface* LoadJointSurfaceFromFile( float fLeft, float fTop, float fWidth, float fHeight,
			ZOrderType eZType, OverlaySurface* pZRefOverlay, const char* szName, PixelFormat ePixelFormat,
			TextureFilterType eFilter = TFT_POINT, bool bDynamic = false, DWORD dwColor = 0xFFFFFFFF );

		//��ͼ���ļ������뾫�鼯
		SpriteSet* LoadSpriteSetFromFile( const char* szName, PixelFormat ePixelFormat,
			UINT InitSpriteNum, UINT AddSpriteNum, TextureFilterType eFilter = TFT_POINT );

		//ɾ��ƴ��ͼ��
		void DeleteJointSurface( JointSurface* pJointSurface );

		//ɾ�����鼯
		void DeleteSpriteSet( SpriteSet* pSpriteSet );

		//ɾ������ƴ��ͼ��
		void DeleteAllJointSurfaces();

		//ɾ�����о��鼯
		void DeleteAllSpriteSets();

		//��ȡ���ƽ��ͼ��ָ��
		OverlaySurface* FKFastcall GetTopmostOverlay();

		//��ƽ��ͼ����뵽�����б���
		void FKFastcall _AddOverlayToList( OverlaySurface* pOverlay, ZOrderType eZType, OverlaySurface* pZRefOverlay );

		//��ƽ��ͼ��ӹ����б���ɾ��
		void FKFastcall _DelOverlayFromList( OverlaySurface* pOverlay );

		//����ƽ��ͼ�� Z ˳��
		void FKFastcall _SetOverlayZOrder( OverlaySurface* pOverlay, ZOrderType eZType, OverlaySurface* pZRefOverlay );

		//������ UV �������������뵽�����б���
		void FKFastcall _AddUVASpriteToList( UVASprite* pUVASprite );

		//������ UV �����������ӹ����б���ɾ��
		void FKFastcall _DelUVASpriteFromList( UVASprite* pUVASprite );
	};
	//--------------------------------------------------------------------------------------------------------------
};

//==================================================================================================================
