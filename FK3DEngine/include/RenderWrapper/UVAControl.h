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
*	�ļ�˵����	UV ����������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	struct UVAnimation;
	//--------------------------------------------------------------------------------------------------------------
	// UV ����������
	class FK_DLL UVAControl
	{
	public:
		UVAnimation*	mpUVAnimation;	// UV ��������ָ��

		int				mnCurSegment;	//��ǰ���ŵĶ�����
		int				mnCurFrame;		//��ǰ���ŵĶ���֡

		float			mfFrameTime;	//��ǰ֡��ʱ

		bool			mbReverse;		//�Ƿ�ת����
		int				mnNextSegment;	//��һ�����ŵĶ�����

	public:
		UVAControl();
		UVAControl( UVAnimation* pUVAnimation );

		//���� UV ��������
		void SetUVAnimation( UVAnimation* pUVAnimation );

		//����ָ��������
		void FKFastcall PlaySegment( int nPlaySegment, int nNextSegment, bool bReverse = false );

		//������һ�����Ŷ�����
		void FKFastcall SetNextSegment( int nNextSegment );

		//����Ϊ���򲥷�
		void FKFastcall SetReversePlay( bool bReverse = true );

		//���¶���֡ʱ��
		UVAFrame* FKFastcall UpdateFrameTime( float fFrameTime );

		//��ȡ��ǰ����֡ UV ����
		const UV4* FKFastcall GetCurrentUV();
	};
	//--------------------------------------------------------------------------------------------------------------
};

//==================================================================================================================
