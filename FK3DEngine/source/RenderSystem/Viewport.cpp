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

#include "../../include/RenderSystem/RenderSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	Viewport::Viewport()
		: mLeft				(0)
		, mTop				(0)
		, mWidth			(800)
		, mHeight			(600)
		, mAspect			(800.0f/600.0f)
		, mMinZ				(0.0f)
		, mMaxZ				(1.0f)
		, mViewportMat		(Matrix4::Identity)
		, mpCamera			(NULL)
		, mdwClearColor		(0)
		, mbClearPerFrame	(false)
	{
		_UpdateViewport();
	}
	//--------------------------------------------------------------------------------------------------------------
	Viewport::Viewport( DWORD dwLeft, DWORD dwTop, DWORD dwWidth, DWORD dwHeight, float fMinZ, float fMaxZ )
		: mLeft				(dwLeft)
		, mTop				(dwTop)
		, mWidth			(dwWidth)
		, mHeight			(dwHeight)
		, mMinZ				(fMinZ)
		, mMaxZ				(fMaxZ)
		, mViewportMat		(Matrix4::Identity)
		, mpCamera			(NULL)
		, mdwClearColor		(0)
		, mbClearPerFrame	(false)
	{
		mAspect = (float)dwWidth / (float)dwHeight;

		_UpdateViewport();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ӿ������
	void Viewport::SetCamera( Camera* pCamera, bool bAutoSetProj )
	{
		//�洢�����ָ��
		mpCamera = pCamera;

		//���������ͶӰ����
		if( bAutoSetProj )
		{
			pCamera->mAspect = mAspect;
			pCamera->mbNeedUpdateProj;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ӿڷ�Χ
	void Viewport::SetViewportRect( DWORD dwLeft, DWORD dwTop, DWORD dwWidth, DWORD dwHeight, float fMinZ, float fMaxZ )
	{
		mLeft	= dwLeft;
		mTop	= dwTop;
		mWidth	= dwWidth;
		mHeight	= dwHeight;
		mMinZ	= fMinZ;
		mMaxZ	= fMaxZ;

		mAspect = (float)dwWidth / (float)dwHeight;

		_UpdateViewport();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������ɫ
	void Viewport::SetClearColor( const ColorValue& refColor )
	{
		mdwClearColor = refColor.GetARGB();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����Ƿ�����Ⱦÿһ֡ǰ���ԭ��ͼ��
	void Viewport::EnableClear( bool bEnable )
	{
		mbClearPerFrame = bEnable;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��Ļ����������ռ��ͶӰ����
	bool Viewport::GetWorldRayFromScreenPoint( LONG nX, LONG nY, Ray3* pRay3 )
	{
		if( nX < (LONG)mLeft || nY < (LONG)mTop )
			return false;
		
		nX -= mLeft;
		nY -= mTop;

		if( nX > (LONG)mWidth || nY > (LONG)mHeight )
			return false;

		//����Ļ����ת��Ϊ������Ϊԭ��ĵ�λ�����꣨ͶӰת����
		float fTanFOV2 = Tan( FK_PI * 0.125 );		// Tan( FK_DegreeToRadian( 45.0f / 2.0f )
		float fX = fTanFOV2 * ( (float)nX / ( (float)mWidth * 0.5f ) - 1.0f ) * mAspect;
		float fY = fTanFOV2 * ( 1.0f - (float)nY / ( (float)mHeight * 0.5f ) );

		//������ͶӰת��������ֵת��������ռ�����
		static Matrix4 MatInvView;
		static Vector3 VectorEnd;

		MatInvView = mpCamera->mViewMatrix.GetInverse();

		pRay3->mOrigin.x = fX * mpCamera->mViewNear;
		pRay3->mOrigin.y = fY * mpCamera->mViewNear;
		pRay3->mOrigin.z = mpCamera->mViewNear;

		VectorEnd.x = fX * mpCamera->mViewFar;
		VectorEnd.y = fY * mpCamera->mViewFar;
		VectorEnd.z = mpCamera->mViewFar;

		pRay3->mOrigin *= MatInvView;
		VectorEnd *= MatInvView;

		pRay3->mDirection = VectorEnd - pRay3->mOrigin;
		pRay3->mDirection.Normalize();

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ӿ�
	void FKFastcall Viewport::_UpdateViewport()
	{
		//�����ӿ�������۲���ݱ�
		if( mpCamera != NULL )
			mpCamera->SetAspect( mAspect );

		//�����ӿھ���
		float fHalfWidth = (float)mWidth / 2.0f;
		float fHalfHeight = (float)mHeight / 2.0f;

		mViewportMat._11 = fHalfWidth;
		mViewportMat._22 = -fHalfHeight;
		mViewportMat._33 = mMaxZ - mMinZ;
		mViewportMat._41 = (float)mLeft + fHalfWidth;
		mViewportMat._42 = (float)mTop + fHalfHeight;
		mViewportMat._43 = mMinZ;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
