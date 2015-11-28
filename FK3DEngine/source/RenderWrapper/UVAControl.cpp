/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	UVAControl
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
	UVAControl::UVAControl()
		: mpUVAnimation	(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	UVAControl::UVAControl( UVAnimation* pUVAnimation )
		: mpUVAnimation	(pUVAnimation)
		, mnCurSegment	(0)
		, mnCurFrame	(pUVAnimation->pSegments->Begin)
		, mfFrameTime	(0)
		, mbReverse		(false)
		, mnNextSegment	(0)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� UV ��������
	void UVAControl::SetUVAnimation( UVAnimation* pUVAnimation )
	{
		mpUVAnimation	= pUVAnimation;
		mnCurSegment	= 0;
		mnCurFrame		= pUVAnimation->pSegments->Begin;
		mfFrameTime		= 0;
		mbReverse		= false;
		mnNextSegment	= 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ָ��������
	void FKFastcall UVAControl::PlaySegment( int nPlaySegment, int nNextSegment, bool bReverse )
	{
		if( nPlaySegment >= mpUVAnimation->nSegment )
			Except( Exception::ERR_INVALIDPARAMS, "ָ�����ŵ� UVA ��������Ч��" );
		if( nNextSegment >= mpUVAnimation->nSegment )
			Except( Exception::ERR_INVALIDPARAMS, "ָ����һ�����ŵ� UVA ��������Ч��" );

		UVASegment* pSegment = mpUVAnimation->pSegments + nPlaySegment;

		mnCurSegment = nPlaySegment;
		mnCurFrame = bReverse ? pSegment->End : pSegment->Begin;

		mnNextSegment = nNextSegment;
		mbReverse = bReverse;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������һ�����Ŷ�����
	void FKFastcall UVAControl::SetNextSegment( int nNextSegment )
	{
		if( nNextSegment >= mpUVAnimation->nSegment )
			Except( Exception::ERR_INVALIDPARAMS, "ָ����һ�����ŵ� UVA ��������Ч��" );

		mnNextSegment = nNextSegment;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����Ϊ���򲥷�
	void FKFastcall UVAControl::SetReversePlay( bool bReverse )
	{
		mbReverse = bReverse;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¶���֡ʱ��
	UVAFrame* FKFastcall UVAControl::UpdateFrameTime( float fFrameTime )
	{
		int nPrevFrame = mnCurFrame;
		UVASegment* pCurSegment = mpUVAnimation->pSegments + mnCurSegment;
		UVAFrame* pCurFrame = mpUVAnimation->pFrames + nPrevFrame;

		//�ۼ�֡��ʱ
		mfFrameTime += fFrameTime;

		//����Ѿ����ڵ�ǰ֡��ʱ
		while( mfFrameTime >= pCurFrame->fFrameTime )
		{
			mfFrameTime -= pCurFrame->fFrameTime;

			//���Ϊ���򲥷�
			if( !mbReverse ) 
			{
				//�����δ����öζ�����β
				if( mnCurFrame < pCurSegment->End )
				{
					//���ŵ���һ֡
					++mnCurFrame;
				}
				//����Ѿ�����öζ�����β
				else
				{
					//��ʼ������һ��������
					mnCurSegment = mnNextSegment;
					pCurSegment = mpUVAnimation->pSegments + mnCurSegment;
					mnCurFrame = pCurSegment->Begin;
				}
			}
			//���Ϊ���򲥷�
			else
			{
				//�����δ����öζ�����ʼ
				if( mnCurFrame > pCurSegment->Begin )
				{
					//���ŵ���һ֡
					--mnCurFrame;
				}
				//����Ѿ�����öζ�����ʼ
				else
				{
					//��ʼ������һ��������
					mnCurSegment = mnNextSegment;
					pCurSegment = mpUVAnimation->pSegments + mnCurSegment;
					mnCurFrame = pCurSegment->End;

					mbReverse = false;
				}
			}

			pCurFrame = mpUVAnimation->pFrames + mnCurFrame;
		}

		//����ı��˲��Ŷ���֡
		if( nPrevFrame != mnCurFrame )
			return pCurFrame;

		return NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ǰ����֡ UV ����
	const UV4* FKFastcall UVAControl::GetCurrentUV()
	{
		UVAFrame* pCurFrame = mpUVAnimation->pFrames + mnCurFrame;
		return (const UV4*)&pCurFrame->sUV4;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
