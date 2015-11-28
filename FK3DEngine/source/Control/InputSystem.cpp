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
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/Control/ControlInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	InputSystem::InputSystem()
		: mbEnableKeyboard		(true)
		, mbEnableMouse			(true)
		, mMouseSpeed			(100)
	{
		memset( mbKeyState, 0, sizeof(bool)*( KEY_BUF_SIZE*3 + 3*4 ) );

		mMouseLastDownTime[0] = 0;
		mMouseLastDownTime[1] = 0;
		mMouseLastDownTime[2] = 0;
		mMouseDBClickTime[0] = 200;
		mMouseDBClickTime[1] = 200;
		mMouseDBClickTime[2] = 200;

		mMouseX = mMouseY = mMouseZ = 0;
		mMouseRelX = mMouseRelY = mMouseRelZ = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	InputSystem::~InputSystem()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//�򿪼�������
	void FKFastcall InputSystem::EnableKeyboard( bool bEnable )
	{
		mbEnableKeyboard = bEnable;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������
	void FKFastcall InputSystem::EnableMouse( bool bEnable )
	{
		mbEnableMouse = bEnable;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������˫���ж����ʱ�䣨���룩
	void FKFastcall InputSystem::SetMouseDBClickTime( DWORD dwLeftTime, DWORD dwRightTime, DWORD dwMidTime )
	{
		mMouseDBClickTime[0] = dwLeftTime;
		mMouseDBClickTime[1] = dwRightTime;
		mMouseDBClickTime[2] = dwMidTime;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ƶ��ٶ�
	void FKFastcall InputSystem::SetMouseSpeed( LONG nMoveSpeed )
	{
		mMouseSpeed = nMoveSpeed;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������λ��
	void FKFastcall InputSystem::SetMousePos( int x, int y, int z )
	{
		FixPosByMouseRect( &x, &y, &z );

		mMouseX = x;
		mMouseY = y;
		mMouseZ = z;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ƶ�����
	void FKFastcall InputSystem::SetMouseRect( MouseRect* pMouseRect )
	{
		mMouseMoveRect = *pMouseRect;

		FixPosByMouseRect( &mMouseX, &mMouseY, &mMouseZ );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ƶ�������������
	void FKFastcall InputSystem::FixPosByMouseRect( int* pX, int* pY, int* pZ )
	{
		if( *pX > mMouseMoveRect.Right )
			*pX = mMouseMoveRect.Right;
		else if( *pX < mMouseMoveRect.Left )
			*pX = mMouseMoveRect.Left;

		if( *pY > mMouseMoveRect.Bottom )
			*pY = mMouseMoveRect.Bottom;
		else if( *pY < mMouseMoveRect.Top )
			*pY = mMouseMoveRect.Top;

		if( *pZ > mMouseMoveRect.WheelMax )
			*pZ = mMouseMoveRect.WheelMax;
		else if( *pZ < mMouseMoveRect.WheelMin )
			*pZ = mMouseMoveRect.WheelMin;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
