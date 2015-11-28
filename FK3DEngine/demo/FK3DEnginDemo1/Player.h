/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Player
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

#include "../../include/CommonBase/CommonBaseInsideHead.h"
#include "../../include/Math/MathInsideHead.h"
#include "../../include/Control/ControlInsideHeader.h"
#include "../../include/PhysiceSystem/PhysicsSystemInsideHeader.h"
#include "../../include/RenderSystem/RenderSystemInsideHeader.h"
#include "../../include/SoundSystem/SoundSystemInsideHeader.h"
#include "../../include/UISystem/UISystemInsideHeader.h"
#include "../../include/ParticleSystem/ParticleSystemInsideHeader.h"
#include "../../include/Scene/SceneInsideHeader.h"
#include "../../include/RenderWrapper/RenderWrapperInsideHeader.h"
using namespace FK3DEngine;

//--------------------------------------------------------------------------------------------------------------
//�����
class Player
{
public:
	//��������ṹ
	struct Input
	{
		bool	bForward;		//ǰ��
		bool	bBackward;		//����
		bool	bShiftLeft;		//����
		bool	bShiftRight;	//����

		bool	bJump;			//��Ծ

		float	fViewPitch;		//�۲츩����
		float	fViewYaw;		//�۲�ƫת��

		float	fFrameTime;		//֡��ʱ
	};

	//���״̬
	enum Status
	{
		Walk,					//��ͨ����
		FreeLook,				//���ɹۿ�
	};

public:
	Vector3			mPlayerPos;		//�������
	float			mViewPitch;		//�۲츩����
	float			mViewYaw;		//�۲�ƫת��
	float			mViewRoll;		//�۲���б��

	Matrix4			mMatRotaFull;	//ȫ������ת����
	Matrix4			mMatRotaYaw;	//ˮƽ��ת����
	Vector3			mMoveDir;		//�ƶ�����
	Vector3			mVelocity;		//�ƶ��ٶ�
	Vector3			mMovement;		//�ƶ�ʸ��
	Vector3			mGroundNormal;	//���淨��

	float			mfGravity;		//����
	bool			mbIsLand;		//�Ƿ������

	float			mLandMoveFactor;//�ƶ�������
	float			mAirMoveFactor;	//�����ƶ�������
	float			mJumpFactor;	//��Ծ������
	float			mRotaFactor;	//��ת������
	float			mRollFactor;	//��б������
	float			mMaxRollValue;	//�����бֵ
	float			mWalkLimit;		//��������ٶ�ֵ
	float			mWalkFriction;	//����Ħ����
	float			mLookLimit;		//�ۿ�����ٶ�ֵ
	float			mLookFriction;	//�ۿ�Ħ����

	RigidCylinder*	mpPlayerRigid;	//�����ײ����

	TriMesh*		mpMesh;			//�������ģ��

	Skeleton*		mpAnim1;
	Skeleton*		mpAnim2;
	Skeleton*		mpAnim3;

	SceneNode*		mpSceneNode;	//��ҳ����ڵ�
	RenderInstance*	mpRenderInst;	//�����Ⱦʵ��
	AnimControl*	mpAnimControl;	//��Ҷ���������

public:
	Player();
	~Player();

	//�����������ģ�ͼ�����
	void LoadPlayerModel( LPCSTR szPlayerFileName );

	//�������λ��
	void SetPlayerPos( const Vector3& vPos );

	//�������״̬
	void UpdatePlayer( const Input& rInput, const Status eStatus = Walk );

	//������������
	void UpdateCamera( Camera* pCamera );

protected:
	//�����ƶ��ٶ�
	void _ClipVelocity( const Vector3& vMoveVec, const float fFriction, const float fSpeedLimit );

	//���������ײ���
	void _DoCollisionDetect();
};