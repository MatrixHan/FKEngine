/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ArrowEmitter
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/ParticleSystem/ParticleSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//ArrowEmitter::ArrowEmitter( Param* pParam )
	//	: Emitter	( &pParam->sBaseParam )
	//	, mfIntervalTime	(0.0f)
	//{
	//	memcpy( &mfGenerateTime, &pParam->fGenerateTime, sizeof(float)*5 );

	//	mParticleDatas.Initialize( pParam->sBaseParam.nMaxParticleNum, 100 );
	//}
	////--------------------------------------------------------------------------------------------------------------
	//ArrowEmitter::~ArrowEmitter()
	//{
	//	mParticleDatas.Release();
	//}
	////--------------------------------------------------------------------------------------------------------------
	////���·�����
	//UINT ArrowEmitter::_UpdateEmitter( float fFrameTime, Vector3* pFaceDir, Vector3* pGravity )
	//{
	//	//������������
	//	mCurParticleNum = 0;

	//	////����֡��ʱ
	//	//mfIntervalTime += fFrameTime;

	//	////���֡��ʱ������������ʱ��
	//	//while( mfIntervalTime >= mfGenerateTime )
	//	//{
	//	//	mfIntervalTime -= mfGenerateTime;

	//	//	//�����µ�����
	//	//	ParticleData* pParticleData = mParticleDatas.Push();

	//	//	pParticleData->fSize = mpParticle->mSize;
	//	//	pParticleData->fLife = mpParticle->mLife;

	//	//	memset( &pParticleData->vPosition, 0, sizeof(Vector3)*2 );

	//	//	//�������ӵ����ɢ���ٶ�
	//	//	pParticleData->fEmissionX = Misc::GetFloatRandomValue( mfMaxEmission, mfMinEmission );
	//	//	pParticleData->fEmissionZ = Misc::GetFloatRandomValue( mfMaxEmission, mfMinEmission );

	//	//	//���ô����ٶ�
	//	//	pParticleData->fFlowSpeed = mfFlowSpeed;
	//	//}

	//	////������������
	//	//int nNumDead = 0;
	//	//ParticleVertex* pVertexPtr = mpVertexData;
	//	//WORD* pIndexPtr = mpIndexData;

	//	//ParticleDatas::Iterator it = mParticleDatas.Begin();
	//	//ParticleDatas::Iterator end = mParticleDatas.End();
	//	//for(; it!=end; ++it )
	//	//{
	//	//	ParticleData* pParticle = *it;

	//	//	//���㵱ǰ��������
	//	//	pParticle->fLife -= mpParticle->mFade * fFrameTime;

	//	//	//�������������
	//	//	if( pParticle->fLife <= 0 )
	//	//	{
	//	//		++nNumDead;
	//	//		continue;
	//	//	}

	//	//	//�������Ӵ�С
	//	//	pParticle->fSize += mpParticle->mSizeFactor * fFrameTime;

	//	//	//�������Ӵ������ٶ�
	//	//	pParticle->fFlowSpeed *= mfFlowFactor;

	//	//	//���������������ٶ�
	//	//	pParticle->vGravity += *pGravity;

	//	//	//������������
	//	//	pParticle->vPosition += pParticle->vGravity;
	//	//	pParticle->vPosition.x += pParticle->fEmissionX;
	//	//	pParticle->vPosition.z += pParticle->fEmissionZ;
	//	//	pParticle->vPosition.y += pParticle->fFlowSpeed;

	//	//	//�����δ�����������������
	//	//	if( mCurParticleNum < mMaxParticleNum )
	//	//	{
	//	//		++mCurParticleNum;

	//	//		//�������Ӷ�������
	//	//		float fSize = pParticle->fSize;

	//	//		//����
	//	//		//pVertexPtr->vPosition.x = pParticle->vPosition.x * 
	//	//}

	//	////ɾ����������
	//	//mParticleDatas.PopFront( nNumDead );

	//	return mCurParticleNum;
	//}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
