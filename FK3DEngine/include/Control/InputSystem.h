/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	InputSystem
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�������ϵͳ
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//����ƶ���Χ�ṹ
	struct MouseRect
	{
		int Left;
		int Right;
		int Top;
		int Bottom;
		int WheelMin;
		int WheelMax;

		FKForceInline MouseRect& operator = ( const MouseRect& other )
		{
			Left		= other.Left;
			Right		= other.Right;
			Top			= other.Top;
			Bottom		= other.Bottom;
			WheelMin	= other.WheelMin;
			WheelMax	= other.WheelMax;
			return *this;
		};
	};
	//--------------------------------------------------------------------------------------------------------------
	#define KEY_BUF_SIZE		256			//����״̬�����С
	//--------------------------------------------------------------------------------------------------------------
	//�������ϵͳ
	class InputSystem : public Singleton< InputSystem >
	{
	public:
		bool	mbEnableKeyboard;			//��־���������Ƿ���
		bool	mbEnableMouse;				//��־��������Ƿ���

		bool	mbKeyState[KEY_BUF_SIZE];	//���̰���״̬
		bool	mbKeyDown[KEY_BUF_SIZE];	//���̰����¼�
		bool	mbKeyUp[KEY_BUF_SIZE];		//���̷ż��¼�

		bool	mbMouseState[3];			//��갴��״̬
		bool	mbMouseDown[3];				//��갴���¼�
		bool	mbMouseUp[3];				//���ż��¼�
		bool	mbMouseDBClick[3];			//���˫���¼�

		DWORD	mMouseLastDownTime[3];		//����ϴεİ���ʱ�䣨���룩
		DWORD	mMouseDBClickTime[3];		//���˫���ж�ʱ�䣨���룩

		MouseRect	mMouseMoveRect;			//����ƶ�����
		LONG		mMouseSpeed;			//����ƶ��ٶ�

		//��굱ǰ����
		int		mMouseX;
		int		mMouseY;
		int		mMouseZ;

		//��������һ֡�ƶ�����
		int		mMouseRelX;
		int		mMouseRelY;
		int		mMouseRelZ;

	public:
		InputSystem();
		virtual ~InputSystem() = 0;

		//��ʼ������ϵͳ
		virtual void Initialize() = 0;

		//��ʼ�����������豸
		virtual void InitializeKeyboard( HWND hWnd, bool bExclusive = false ) = 0;

		//��ʼ����������豸
		virtual void InitializeMouse( HWND hWnd, bool bExclusive = false ) = 0;

		//�򿪼�������
		void FKFastcall EnableKeyboard( bool bEnable );

		//���������
		void FKFastcall EnableMouse( bool bEnable );

		//�������˫���ж����ʱ�䣨���룩
		void FKFastcall SetMouseDBClickTime( DWORD dwLeftTime, DWORD dwRightTime, DWORD dwMidTime );

		//��������ƶ��ٶ�
		void FKFastcall SetMouseSpeed( LONG nMoveSpeed = 100 );

		//�������λ��
		void FKFastcall SetMousePos( int x, int y, int z );

		//��������ƶ�����
		void FKFastcall SetMouseRect( MouseRect* pMouseRect );

		//��������ƶ�������������
		void FKFastcall FixPosByMouseRect( int* pX, int* pY, int* pZ );

		//���¼�������
		virtual void UpdateKeyboard() = 0;

		//�����������
		virtual void UpdateMouse() = 0;
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
