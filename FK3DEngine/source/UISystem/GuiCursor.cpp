/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiCursor
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/UISystem/UISystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	GuiCursor::GuiCursor( GuiLoca* pLoca, int nTargetX, int nTargetY, SpriteSet* pSpriteSet, UVAnimation* pUVA )
		: GuiSpriteUVA		( ZOT_Top, NULL, NULL, pLoca, NULL, pSpriteSet, pUVA )
		, mTargetX			(nTargetX)
		, mTargetY			(nTargetY)
		, mfStatChageTime	(6.0f)
		, mfIdleTime		(0.0f)
		, mbIdleStatus		(false)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʾ/���ؿؼ�
	void FKFastcall GuiCursor::Show( bool bShow )
	{
		mpSprite->SetVisable( bShow );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����λ��
	void FKFastcall GuiCursor::SetPos( long nX, long nY )
	{
		//�ı侫����ʾλ��
		mpSprite->SetLocation( nX - mTargetX, nY - mTargetY );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ù��״̬�л���ʱ
	void FKFastcall GuiCursor::SetStatChageTime( float fSecond )
	{
		mfStatChageTime = fSecond;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¹������ʱ��
	void FKFastcall GuiCursor::UpdateIdleTime( float fSecond )
	{
		//����Ѿ�Ϊ�ȴ�״̬��ֱ�ӷ���
		if( mbIdleStatus )
			return;

		mfIdleTime += fSecond;

		//���������״̬�л���ʱ
		if( mfIdleTime >= mfStatChageTime )
		{
			//��ʼ���ŵȴ�״̬�л�����
			mpSprite->mpUVASprite->PlaySegment( mnChangeSegment, mnIdleSegment );

			mbIdleStatus = true;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¹��Ϊ�״̬
	void FKFastcall GuiCursor::UpdateActivate()
	{
		mfIdleTime = 0.0f;

		//�����겻�ǵȴ�״̬��ֱ�ӷ���
		if( !mbIdleStatus )
			return;

		mbIdleStatus = false;

		//�����ǰ���ڲ��ŵȴ�״̬�л�����
		if( mpSprite->mpUVASprite->mnCurSegment == mnChangeSegment )
		{
			//��ʼ���򲥷ŵȴ�״̬�л�����
			mpSprite->mpUVASprite->SetReversePlay();

			//�趨����֮�󲥷Ż״̬����
			mpSprite->mpUVASprite->SetNextSegment( mnActiveSegment );
		}
		else
		{
			//��ʼ���򲥷ŵȴ�״̬�л�����
			mpSprite->mpUVASprite->PlaySegment( mnChangeSegment, mnActiveSegment, true );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

