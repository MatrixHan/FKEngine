/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	AnimControl
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
	AnimControl::AnimControl()
		: mbCanPlay				(true)
		, mNumKey				(0)
		, mIntervalTime			(0.1f)
		, mCurKey				(0)
		, mCurIntervalTime		(0.0f)
		, mAnimSpeed			(1.0f)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ö�����Ϣ
	void AnimControl::SetAnimationInfo( UINT nNumKey, float fIntervalTime )
	{
		if( nNumKey == 0 || fIntervalTime == 0.0f )
			Except( Exception::ERR_INVALIDPARAMS, "����Ķ���֡����֡ͣ��ʱ�䡣" );

		mNumKey = nNumKey;
		mIntervalTime = fIntervalTime;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ö����ܷ񲥷�
	void AnimControl::SetPlayable( bool bCanPlay )
	{
		mbCanPlay = bCanPlay;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ö��������ٶ�
	void AnimControl::SetPlaySpeed( float fSpeed )
	{
		mAnimSpeed = fSpeed;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���õ�ǰ����ʱ��
	void AnimControl::SetCurTime( float fAnimTime )
	{
		mCurIntervalTime = fAnimTime;
		int nPassedKey = FloorToInt( mCurIntervalTime / mIntervalTime );
		mCurIntervalTime -= mIntervalTime * (float)nPassedKey;

		mCurKey += (UINT)nPassedKey;		
		mCurKey %= mNumKey;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¶���֡ʱ��
	void FKFastcall AnimControl::UpdateKeyTime( float fKeyTime )
	{
		mCurIntervalTime += fKeyTime * mAnimSpeed;
		int nPassedKey = FloorToInt( mCurIntervalTime / mIntervalTime );
		mCurIntervalTime -= mIntervalTime * (float)nPassedKey;

		mCurKey += (UINT)nPassedKey;
		mCurKey %= mNumKey;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
