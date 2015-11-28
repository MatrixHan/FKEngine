/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Camera
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderWrapper/RenderWrapperInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	Camera::Camera()
		: mFOVy					(45.0f)
		, mAspect				(4.0f/3.0f)
		, mViewNear				(1.0f)
		, mViewFar				(10000.0f)
		, mViewPos				( Vector3( 0.0f, 0.0f, 0.0f ) )
		, mViewPitch			(0.0f)
		, mViewYaw				(0.0f)
		, mViewRoll				(0.0f)
		, mbNeedUpdateViewPos	(true)
		, mbNeedUpdateViewRot	(true)
		, mbNeedUpdateView		(true)
		, mbNeedUpdateProj		(true)
		, mbNeedUpdateFrum		(true)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ù۲�״̬
	void Camera::SetView( const Vector3& vPos, float fPitch, float fYaw, float fRoll )
	{
		mViewPos = vPos;
		mViewPitch = fPitch;
		mViewYaw = fYaw;
		mViewRoll = fRoll;
		mbNeedUpdateView = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ù۲�λ��
	void Camera::SetViewPos( const Vector3& vPos )
	{
		mViewPos = vPos;
		mbNeedUpdateView = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ƽ�ƹ۲�λ��
	void Camera::Translate( const Vector3& vTrans )
	{
		mViewPos += vTrans;
		mbNeedUpdateView = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ƽ�ƹ۲�λ��
	void Camera::Translate( float fX, float fY, float fZ )
	{
		mViewPos.x += fX;
		mViewPos.y += fY;
		mViewPos.z += fZ;
		mbNeedUpdateView = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ת�۲췽��
	void Camera::Rotate( float fPitch, float fYaw, float fRoll )
	{
		mViewPitch	+= fPitch;
		mViewYaw	+= fYaw;
		mViewRoll	+= fRoll;

		mbNeedUpdateView = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ø�����
	void Camera::SetPitch( float fDegree )
	{
		mViewPitch = fDegree;
		mbNeedUpdateView = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƫת��
	void Camera::SetYaw( float fDegree )
	{
		mViewYaw = fDegree;
		mbNeedUpdateView = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������б��
	void Camera::SetRoll( float fDegree )
	{
		mViewRoll = fDegree;
		mbNeedUpdateView = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ͶӰ״̬
	void Camera::SetProjection( float fFOVy, float fAspect, float fNear, float fFar )
	{
		mFOVy = fFOVy;
		mAspect = fAspect;
		mViewNear = fNear;
		mViewFar = fFar;

		mbNeedUpdateProj = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ù۲��ӽ�
	void Camera::SetVisualAngle( float fFOVy )
	{
		mFOVy = fFOVy;
		mbNeedUpdateProj = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ù۲���ݱ�
	void Camera::SetAspect( float fAspect )
	{
		mAspect = fAspect;
		mbNeedUpdateProj = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ý��ü���
	void Camera::SetViewNear( float fNear )
	{
		mViewNear = fNear;
		mbNeedUpdateProj = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����Զ�ü���
	void Camera::SetViewFar( float fFar )
	{
		mViewFar = fFar;
		mbNeedUpdateProj = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�۲����
	Matrix4& Camera::GetViewMatrix()
	{
		return mViewMatrix;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡͶӰ����
	Matrix4& Camera::GetProjMatrix()
	{
		return mProjMatrix;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�۲�ͶӰ����
	Matrix4& Camera::GetViewProjMatrix()
	{
		return mViewProjMatrix;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¹۲�λ�ƾ���
	void Camera::_UpdateViewPosMatrix()
	{
		//����λ��
		static Vector3 vViewFront;
		vViewFront.x = mViewPos.x;
		vViewFront.y = mViewPos.y;
		vViewFront.z = mViewPos.z + 1.0f;

		mViewMatrix.SetLookAtLH( mViewPos, vViewFront, Vector3::UnitY );

		mbNeedUpdateView = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¹۲���ת����
	void Camera::_UpdateViewRotaMatrix()
	{
		//������ת
		static Matrix4 MatA;
		static Matrix4 MatB;
		static Matrix4 MatC;

		//�� Y ����ת * �� X ����ת
		MatA.SetRotationY( mViewYaw );
		MatB.SetRotationX( mViewPitch );

		Mat4TransMat4( &MatC, &MatA, &MatB );

		//�� Z ����ת
		MatA.SetRotationZ( mViewRoll );

		Mat4TransMat4( &mRotaMatrix, &MatC, &MatA );

		mbNeedUpdateView = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������
	void Camera::_UpdateCamera()
	{
		if( mbNeedUpdateViewPos )
			_UpdateViewPosMatrix();

		if( mbNeedUpdateViewRot )
			_UpdateViewRotaMatrix();

		if( mbNeedUpdateView )
			_UpdateViewMatrix();

		if( mbNeedUpdateProj )
			_UpdateProjMatrix();

		if( mbNeedUpdateFrum )
			_UpdateViewFrustum();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¹۲����
	void Camera::_UpdateViewMatrix()
	{
		//����λ�ƺ���ת����
		mViewMatrix *= mRotaMatrix;

		mbNeedUpdateView = false;
		mbNeedUpdateFrum = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ͶӰ����
	void Camera::_UpdateProjMatrix()
	{
		mProjMatrix.SetPerspectiveFovLH( mFOVy, mAspect, mViewNear, mViewFar );

		mbNeedUpdateProj = false;
		mbNeedUpdateFrum = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void Camera::_UpdateViewFrustum()
	{
		//���¹۲�ͶӰ����
		Mat4TransMat4( &mViewProjMatrix, &mViewMatrix, &mProjMatrix );

		mViewFrustum.UpdateViewFrustum( mViewProjMatrix );

		mbNeedUpdateFrum = false;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
