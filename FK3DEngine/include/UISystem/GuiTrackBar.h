/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiTrackBar
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	����������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//����������
	class FK_DLL GuiTrackBar : public GuiBase
	{
	public:
		//����������
		struct Param
		{
			SpriteSet*		pSpriteSet;		//���鼯ָ��
			int				nRange;			//����ֵ��Χ
			int				nValue;			//��ǰ����ֵ

			int				nX;				// X ����
			int				nY;				// Y ����

			int				nBkgY;			//���� Y ����
			int				nBkgWidth;		//�������
			int				nBkgHeight;		//�����߶�

			int				nProgLeft;		//������ƫ�� X ����
			int				nProgTop;		//������ƫ�� Y ����
			int				nProgWidth;		//���������
			int				nProgHeight;	//�������߶�

			int				nSliderY;		//���� Y ����
			int				nSliderMinX;	//������С X ����
			int				nSliderMaxX;	//������� X ����
			int				nSliderWidth;	//������
			int				nSliderHeight;	//����߶�

			FnFrameEvent	fnEvent;		//�����¼�
		};

	public:
		float			mDragWidth;			//��������ƶ���Χ
		int				mRange;				//����ֵ��Χ
		int				mValue;				//��ǰ����ֵ
		float			mPercent;			//����ֵ�ٷֱ�

	protected:
		SpriteSet*		mpSpriteSet;		//���������鼯ָ��

		UV4				mProgressUV;		//������ UV
		UV4				mNormalUV;			//��ͨ���� UV
		UV4				mHighLightUV;		//�߹⻬�� UV

		Sprite*			mpBackground;		//��������
		Sprite*			mpProgress;			//����������
		Sprite*			mpSlider;			//���龫��

		int				mBkgY;				//���� Y ����
		int				mProgWidth;			//���������
		int				mProgHeight;		//�������߶�
		int				mSliderX;			//���� X ����
		int				mSliderY;			//���� Y ����
		int				mSliderMinX;		//������С X ����
		int				mSliderMaxX;		//������� X ����
		int				mSliderWidth;		//������
		int				mSliderHeight;		//����߶�

		GuiClient		mProgressClient;	//�������ͻ���
		GuiClient		mSliderClient;		//����ͻ���

		bool			mbDragSlider;		//�Ƿ������϶�����
		bool			mbSliderFocus;		//�����Ƿ��ý���

		FnFrameEvent	mFnEvent;			//�������¼�����ָ��

	public:
		GuiTrackBar( ZOrderType eZType, OverlaySurface* pZRefOverlay, GuiDialog* pDialog, Param* pParam );
		~GuiTrackBar();

		//����/�رտؼ�
		void FKFastcall Enable( bool bEnable );

		//��ʾ/���ؿؼ�
		void FKFastcall Show( bool bShow );

		//����λ��
		void FKFastcall SetPos( long nX, long nY );

		//�ƶ�λ��
		void FKFastcall MovePos( long nX, long nY );

		//���� Z ˳��
		void FKFastcall SetZOrder( ZOrderType eZType, OverlaySurface* pZRefOverlay );

		//��ȡ Z ˳��
		OverlaySurface* FKFastcall GetZOrder( ZOrderType eZType );

		//���/ʧȥ����
		void FKFastcall Focus( bool bHasFocus );

		//����ƶ�
		void FKFastcall MouseMove( InputSystem* pInputSystem );

		//�������
		void FKFastcall LDown( InputSystem* pInputSystem );

		//����ͷ�
		void FKFastcall LUp( InputSystem* pInputSystem );

	public:
		//���û������������Ϣ
		LONG_PTR SendMsg( LONG_PTR nGM, LONG_PTR nGMA = 0, LONG_PTR nGMB = 0 );

		//���û������¼�����
		void FKFastcall SetEvent( FnFrameEvent fnEvent );

		//���û���ֵ
		void FKFastcall SetValue( int nValue );

	protected:
		//����������֡�¼�
		void FKFastcall _ActiveEvent();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

