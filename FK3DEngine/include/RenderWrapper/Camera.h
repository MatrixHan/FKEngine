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
*	�ļ�˵����	�������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

#include "ViewFrustum.h"


//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//�������
	class FK_DLL Camera
	{
	public:
		float		mFOVy;					//�۲��ӽ�
		float		mAspect;				//�۲���ݱ�
		float		mViewNear;				//���ü���
		float		mViewFar;				//Զ�ü���

		Vector3		mViewPos;				//�۲��
		float		mViewPitch;				//�۲츩����
		float		mViewYaw;				//�۲�ƫת��
		float		mViewRoll;				//�۲���б��

		Matrix4		mRotaMatrix;			//�۲���ת����
		Matrix4		mViewMatrix;			//�۲����
		Matrix4		mProjMatrix;			//ͶӰ����
		Matrix4		mViewProjMatrix;		//�۲�ͶӰ�ϲ�����

		ViewFrustum	mViewFrustum;			//����

		bool		mbNeedUpdateViewPos;	//�Ƿ���Ҫ���¹۲�λ�ƾ���
		bool		mbNeedUpdateViewRot;	//�Ƿ���Ҫ���¹۲���ת����
		bool		mbNeedUpdateView;		//�Ƿ���Ҫ���¹۲����
		bool		mbNeedUpdateProj;		//�Ƿ���Ҫ����ͶӰ����
		bool		mbNeedUpdateFrum;		//�Ƿ���Ҫ��������

	public:
		Camera();

		//���ù۲�״̬
		void SetView( const Vector3& vPos, float fPitch, float fYaw, float fRoll );

		//���ù۲�λ��
		void SetViewPos( const Vector3& vPos );

		//ƽ�ƹ۲�λ��
		void Translate( const Vector3& vTrans );

		//ƽ�ƹ۲�λ��
		void Translate( float fX, float fY, float fZ );

		//��ת�۲췽��
		void Rotate( float fPitch, float fYaw, float fRoll );

		//���ø�����
		void SetPitch( float fDegree );

		//����ƫת��
		void SetYaw( float fDegree );

		//������б��
		void SetRoll( float fDegree );

		//����ͶӰ״̬
		void SetProjection( float fFOVy, float fAspect, float fNear, float fFar );

		//���ù۲��ӽ�
		void SetVisualAngle( float fFOVy );

		//���ù۲���ݱ�
		void SetAspect( float fAspect );

		//���ý��ü���
		void SetViewNear( float fNear );

		//����Զ�ü���
		void SetViewFar( float fFar );

		//��ȡ�۲����
		Matrix4& GetViewMatrix();

		//��ȡͶӰ����
		Matrix4& GetProjMatrix();

		//��ȡ�۲�ͶӰ����
		Matrix4& GetViewProjMatrix();

		//���¹۲�λ�ƾ���
		void _UpdateViewPosMatrix();

		//���¹۲���ת����
		void _UpdateViewRotaMatrix();

		//���������
		void _UpdateCamera();

		//���¹۲����
		void _UpdateViewMatrix();

		//����ͶӰ����
		void _UpdateProjMatrix();

		//��������
		void _UpdateViewFrustum();
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Camera* >	CameraList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
