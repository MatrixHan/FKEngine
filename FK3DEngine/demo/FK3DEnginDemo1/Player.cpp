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

#include "Player.h"

//--------------------------------------------------------------------------------------------------------------
Player::Player()
	: mPlayerPos		(Vector3::Zero)
	, mViewPitch		(0.0f)
	, mViewYaw			(0.0f)
	, mViewRoll			(0.0f)
	, mMoveDir			(Vector3::Zero)
	, mVelocity			(Vector3::Zero)
	, mMovement			(Vector3::Zero)
	, mGroundNormal		(Vector3::Zero)
	, mfGravity			(120.0f)
	, mbIsLand			(false)
	, mLandMoveFactor	(160.0f)
	, mAirMoveFactor	(20.0f)
	, mJumpFactor		(50.0f)
	, mRotaFactor		(30.0f)
	, mRollFactor		(10.0f)
	, mMaxRollValue		(2.0f)
	, mWalkLimit		(40.0f)
	, mWalkFriction		(80.0f)
	, mLookLimit		(30.0f)
	, mLookFriction		(120.0f)
	, mpPlayerRigid		(NULL)
{
	mpPlayerRigid = (RigidCylinder*)PhysicsSystem::mpSingleton->CreateRigidBody( RigidCylinder::Creator );
	mpPlayerRigid->SetRigidCylinder( 1.5f, 5.5f );
}
//--------------------------------------------------------------------------------------------------------------
Player::~Player()
{
}
//--------------------------------------------------------------------------------------------------------------
//�����������ģ�ͼ�����
void Player::LoadPlayerModel( LPCSTR szPlayerFileName )
{
	//ObjectFileLoader::mpSingleton->LoadObjectFile( "ElfMesh.scene" );
	//mpMesh = (TriMesh*)*ObjectFileLoader::mpSingleton->mLoadedGeometryList.Begin();

	//ObjectFileLoader::mpSingleton->LoadObjectFile( "ElfStand.scene" );
	//mpAnim1 = ObjectFileLoader::mpSingleton->mpLoadedSkeleton;

	//ObjectFileLoader::mpSingleton->LoadObjectFile( "ElfBeginRun.scene" );
	//mpAnim2 = ObjectFileLoader::mpSingleton->mpLoadedSkeleton;

	//ObjectFileLoader::mpSingleton->LoadObjectFile( "ElfRun.scene" );
	//mpAnim3 = ObjectFileLoader::mpSingleton->mpLoadedSkeleton;

	//mpSceneNode = (SceneNode*)g_pSceneMgr->GetSceneRootNode()->CreateChild();

	//mpMesh->InitializeInstanceList( 1, 1 );
	//mpMesh->SetSkeleton( mpAnim3 );
	//mpRenderInst = mpMesh->CreateInstance();

	//mpAnimControl = AnimControlManager::mpSingleton->CreateAnimControl();
	//mpAnimControl->SetAnimationInfo( mpAnim3->mNumKey, mpAnim3->mIntervalTime );
	//mpRenderInst->mpAnimControl = mpAnimControl;

	//mpSceneNode->AttachRenderInstance( mpRenderInst );
}
//--------------------------------------------------------------------------------------------------------------
//�������λ��
void Player::SetPlayerPos( const Vector3& vPos )
{
	mPlayerPos = vPos;
	mpPlayerRigid->SetMassCenter( vPos );
}
//--------------------------------------------------------------------------------------------------------------
//�������״̬
void Player::UpdatePlayer( const Input& rInput, const Status eStatus )
{
	//----------------------------------------------------------
	// ���ȸ��������������������ʾ�Ƕ�
	//
	// ��������ƶ�ʱ�ӽ�����ƫ��mViewYaw Ϊ���������𽥼�С��
	// ��������ƶ�ʱ�ӽ�����ƫ��mViewYaw Ϊ��������������
	// ��������ƶ�ʱ�ӽ�����ƫ��mViewPitch Ϊ���������𽥼�С��
	// ��������ƶ�ʱ�ӽ�����ƫ��mViewPitch Ϊ��������������
	//----------------------------------------------------------

	float fRotaAddYaw	= rInput.fViewYaw * mRotaFactor * rInput.fFrameTime;
	float fRotaAddPitch	= rInput.fViewPitch * mRotaFactor * rInput.fFrameTime;

	mViewPitch -= fRotaAddPitch;

	//�����������ʾ�Ƕȣ�Ҫ������ʾ�Ƿ�תȷ����θı�����ӽǡ�
	if( mViewPitch > 90.0f || mViewPitch < -90.0f )
		mViewYaw += fRotaAddYaw;
	else
		mViewYaw -= fRotaAddYaw;

	if( mViewYaw	< -180.0f )		mViewYaw	+= 360.0f;
	if( mViewPitch	< -180.0f )		mViewPitch	+= 360.0f;
	if( mViewYaw	> 180.0f )		mViewYaw	-= 360.0f;
	if( mViewPitch	> 180.0f )		mViewPitch	-= 360.0f;


	//���ݼ��������������ƶ�����
	mMoveDir.x = 0.0f;
	mMoveDir.y = 0.0f;
	mMoveDir.z = 0.0f;

	if( rInput.bForward )
		mMoveDir.z += 1.0f;
	if( rInput.bBackward )
		mMoveDir.z -= 1.0f;
	if( rInput.bShiftLeft )
		mMoveDir.x -= 1.0f;
	if( rInput.bShiftRight )
		mMoveDir.x += 1.0f;

	//�޲���ʱ�𽥻ָ���б��
	const float fRollFactor = mRollFactor * rInput.fFrameTime;
	if( mMoveDir.x == 0.0f )
	{
		if( fRollFactor > Abs( mViewRoll ) )
		{
			mViewRoll = 0.0f;
		}
		else
		{
			if( mViewRoll > 0.0f )
				mViewRoll -= fRollFactor;
			else if( mViewRoll < 0.0f )
				mViewRoll += fRollFactor;
		}
	}
	//������ʱ�ı���б��
	else if( mMoveDir.x > 0.0f )
	{
		mViewRoll += fRollFactor;
		if( mViewRoll > mMaxRollValue )
			mViewRoll = mMaxRollValue;
	}
	else
	{
		mViewRoll -= fRollFactor;
		if( mViewRoll < -mMaxRollValue )
			mViewRoll = -mMaxRollValue;
	}

	//��λ���ƶ�����
	mMoveDir.Normalize();


	//������ת����

	//�� Y ����ת * �� X ����ת
	static Matrix4 MatA;
	static Matrix4 MatB;

	//�� Y ����ת
	MatA.SetRotationY( mViewYaw );

	//��ȡˮƽ��ת����
	mMatRotaYaw = MatA.GetInverse();

	//������ X ����ת
	MatB.SetRotationX( mViewPitch );
	Mat4TransMat4( &mMatRotaFull, &MatA, &MatB );

	//����ȫ������ת���󣨹۲�ռ䵽����ռ�ת������
	mMatRotaFull.SetInverse();


	//��������ƶ�ʸ��
	static Vector3 vMoveVec;

	//�ж�����ƶ�״̬
	switch (eStatus)
	{
		//��ͨ����״̬
	case Walk:
		{
			//��ˮƽ��ת����ת���ƶ�����
			mMoveDir *= mMatRotaYaw;

			//������������ٶ�
			mVelocity.y -= mfGravity * rInput.fFrameTime;	// V ��t ʱ����ٶȣ� = a �����ٶȣ� * t ��ʱ�䣩

			//�����������
			if( mbIsLand )
			{
				//������ҿ����ƶ��ٶ�
				vMoveVec = mMoveDir * mLandMoveFactor * rInput.fFrameTime;

				//���ݵ��淨�������ƶ�����
				vMoveVec -= mGroundNormal * mGroundNormal.GetDot( vMoveVec );

				//����Ħ����
				const float fFriction = mWalkFriction * rInput.fFrameTime * mGroundNormal.y;

				//�����ƶ��ٶ�
				_ClipVelocity( vMoveVec, fFriction, mWalkLimit );

				//�����ҽ�����Ծ��������ϵ��ٶ�
				if( rInput.bJump )
					mVelocity.y += mJumpFactor;
			}
			//�������ڿ���
			else
			{
				//��������ڿ��п����Ժ�С���ٶȿ����ƶ����򣨱����������壩
				mVelocity += mMoveDir * mAirMoveFactor * rInput.fFrameTime;
			}

			//��������ƶ�����
			mMovement = mVelocity * rInput.fFrameTime * 0.5f;	// S ��t ʱ���ȱ����˶����룩 = V ��t ʱ����ٶȣ� * 0.5

			//���������ײ���
			mbIsLand = false;

			_DoCollisionDetect();
			break;
		}
		//���ɹۿ�״̬
	case FreeLook:
		{
			//����ת����ת���ƶ�����
			mMoveDir *= mMatRotaFull;

			//������ҿ����ƶ��ٶ�
			vMoveVec = mMoveDir * mLandMoveFactor * rInput.fFrameTime;

			//����Ħ����
			const float fFriction = mLookFriction * rInput.fFrameTime;

			//�����ƶ��ٶ�
			_ClipVelocity( vMoveVec, fFriction, mLookLimit );

			//��������ƶ�����
			mMovement = mVelocity * rInput.fFrameTime * 0.5f;

			//���������λ��
			mPlayerPos += mMovement;
			mpPlayerRigid->SetMassCenter( mPlayerPos );
			break;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------
//������������
void Player::UpdateCamera( Camera* pCamera )
{
	pCamera->SetView( mPlayerPos, mViewPitch, mViewYaw, mViewRoll );
	pCamera->mViewPos.y += 2.0f;
}
//--------------------------------------------------------------------------------------------------------------
//�����ƶ��ٶ�
void Player::_ClipVelocity( const Vector3& vMoveVec, const float fFriction, const float fSpeedLimit )
{
	//�����ƶ��ٶ�
	mVelocity += vMoveVec;

	//����Ħ����
	float fSpeed = mVelocity.GetLength();

	if( fSpeed > fFriction )
	{
		const float fOldSpeed = fSpeed;
		fSpeed -= fFriction;

		mVelocity *= fSpeed / fOldSpeed;
	}
	else
	{
		mVelocity = Vector3::Zero;
	}

	//��������ٶ�
	float fSpeedFactor = fSpeedLimit;
	if( fSpeed > fSpeedFactor )
	{
		fSpeedFactor /= fSpeed;
		mVelocity *= fSpeedFactor;
	}
}
//--------------------------------------------------------------------------------------------------------------
//���������ײ���
void Player::_DoCollisionDetect()
{
	//������Ҹ��������ƶ���
	mpPlayerRigid->SetMassCenter( mPlayerPos );
	mpPlayerRigid->SetLinearMove( mMovement );

	static CollisionInfo sCollisionInfo;
	PhysicsSystem::mpSingleton->DoCollisionDetect( mpPlayerRigid, &sCollisionInfo );

	//���δ������ײ
	if( !sCollisionInfo.bCollision )
	{
		mPlayerPos += mMovement;
		mpPlayerRigid->SetMassCenter( mPlayerPos );
		return;
	}

	//�����ƶ�Ŀ������
	Vector3 vTargetPos = mPlayerPos + mMovement;
	mPlayerPos = sCollisionInfo.vCollisionPos;

	//�ж���ײ������
	switch (sCollisionInfo.pCollisionVolume->mBoundType)
	{
		//��ͨ��ײ����
	case BoundInfo::General:
		{
			//���㻬������
			Vector3 vSlidePos = vTargetPos + sCollisionInfo.vFaceNormal *
				( sCollisionInfo.vCollisionPos - vTargetPos ).GetDot( sCollisionInfo.vFaceNormal );

			//���㻬��ʸ��
			mMovement = vSlidePos - sCollisionInfo.vCollisionPos;

			//�����ٶȷ���
			mVelocity -= sCollisionInfo.vFaceNormal * mVelocity.GetDot( sCollisionInfo.vFaceNormal );

			//����Ƿ�����أ���ײ�涸�ͳ̶ȣ�
			if( sCollisionInfo.vFaceNormal.y >= 0.6f )
			{
				mbIsLand = true;
				mGroundNormal = sCollisionInfo.vFaceNormal;
			}

			//��⻬����ײ
			_DoCollisionDetect();
			break;
		}
		//¥����ײ����
	case BoundInfo::Stair:
		{
			//�����ƶ��ٶ������������
			mPlayerPos.y += ( vTargetPos - sCollisionInfo.vCollisionPos ).GetLength();
			break;
		}
		//������ײ����
	case BoundInfo::Ladder:
		{
			break;
		}
	}
}