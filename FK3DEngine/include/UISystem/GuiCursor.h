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
*	�ļ�˵����	������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "GuiSpriteUVA.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	struct UVAnimation;
	//--------------------------------------------------------------------------------------------------------------
	//������
	class FK_DLL GuiCursor : public GuiSpriteUVA
	{
	public:
		static const int mnActiveSegment	= 0;	//���״̬������
		static const int mnChangeSegment	= 1;	//���״̬������״̬�ı䶯����
		static const int mnIdleSegment		= 2;	//�������״̬������

	public:
		int			mTargetX;			//���Ŀ�� X
		int			mTargetY;			//���Ŀ�� Y

		float		mfStatChageTime;	//���״̬�л���ʱ
		float		mfIdleTime;			//�������ʱ��

		bool		mbIdleStatus;		//����Ƿ�Ϊ�ȴ�״̬

	public:
		GuiCursor( GuiLoca* pLoca, int nTargetX, int nTargetY, SpriteSet* pSpriteSet, UVAnimation* pUVA );

	public:
		//��ʾ/���ؿؼ�
		void FKFastcall Show( bool bShow );

		//����λ��
		void FKFastcall SetPos( long nX, long nY );

		//���ù��״̬�л���ʱ
		void FKFastcall SetStatChageTime( float fSecond = 6.0f );

		//���¹������ʱ��
		void FKFastcall UpdateIdleTime( float fSecond );

		//���¹��Ϊ�״̬
		void FKFastcall UpdateActivate();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

