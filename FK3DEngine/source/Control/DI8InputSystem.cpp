/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	DI8InputSystem
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
	DI8InputSystem::DI8InputSystem()
		: mpDirectInput8	(NULL)
		, mpDI8Keyboard		(NULL)
		, mpDI8Mouse		(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	DI8InputSystem::~DI8InputSystem()
	{
		SafeRelease( mpDI8Keyboard );
		SafeRelease( mpDI8Mouse );
		SafeRelease( mpDirectInput8 );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ������ϵͳ
	void DI8InputSystem::Initialize()
	{
		//���� DirectInput8 ����
		HRESULT result = DirectInput8Create( (HINSTANCE)GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8,
			(void**)&mpDirectInput8, NULL );
		if( FAILED( result ) )
			Except( Exception::ERR_INTERNAL_ERROR, "���� DirectInput8 �������" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ�����������豸
	void DI8InputSystem::InitializeKeyboard( HWND hWnd, bool bExclusive )
	{
		//���������豸
		HRESULT result = mpDirectInput8->CreateDevice( GUID_SysKeyboard, &mpDI8Keyboard, NULL );
		if( FAILED( result ) )
			Except( Exception::ERR_INTERNAL_ERROR, (String)"���� DirectInput8 �����豸����"
			"\nDX ����������" + DXGetErrorDescription9( result ) );

		//���ü������ݸ�ʽ
		result = mpDI8Keyboard->SetDataFormat( &c_dfDIKeyboard );
		if( FAILED( result ) )
			Except( Exception::ERR_INTERNAL_ERROR, (String)"���� DirectInput8 �����豸���ݸ�ʽ����"
			"\nDX ����������" + DXGetErrorDescription9( result ) );

		//���ü���Э���ȼ�
		DWORD flag = bExclusive ? ( DISCL_FOREGROUND | DISCL_EXCLUSIVE ) : ( DISCL_BACKGROUND | DISCL_NONEXCLUSIVE );

		result = mpDI8Keyboard->SetCooperativeLevel( hWnd, flag );
		if( FAILED( result ) )
			Except( Exception::ERR_INTERNAL_ERROR, (String)"���� DirectInput8 �����豸Э���ȼ�����"
			"\nDX ����������" + DXGetErrorDescription9( result ) );

		//���û���ģʽ����
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj        = 0;
		dipdw.diph.dwHow        = DIPH_DEVICE;
		dipdw.dwData            = DI8_KEY_BUF_SIZE;

		result = mpDI8Keyboard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
		if( FAILED( result ) )
			Except( Exception::ERR_INTERNAL_ERROR, (String)"���� DirectInput8 �����豸���ݻ���ģʽ����"
			"\nDX ����������" + DXGetErrorDescription9( result ) );

		//��ȡ����
		mpDI8Keyboard->Acquire();

		mbEnableKeyboard = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ����������豸
	void DI8InputSystem::InitializeMouse( HWND hWnd, bool bExclusive )
	{
		HRESULT result = mpDirectInput8->CreateDevice( GUID_SysMouse, &mpDI8Mouse, NULL );
		if( FAILED( result ) )
			Except( Exception::ERR_INTERNAL_ERROR, (String)"���� DirectInput8 ����豸����"
			"\nDX ����������" + DXGetErrorDescription9( result ) );

		//�������ݸ�ʽ
		result = mpDI8Mouse->SetDataFormat( &c_dfDIMouse2 );
		if( FAILED( result ) )
			Except( Exception::ERR_INTERNAL_ERROR, (String)"���� DirectInput8 ����豸���ݸ�ʽ����"
			"\nDX ����������" + DXGetErrorDescription9( result ) );

		//���ü���Э���ȼ�
		DWORD flag = bExclusive ? ( DISCL_FOREGROUND | DISCL_EXCLUSIVE ) : ( DISCL_BACKGROUND | DISCL_NONEXCLUSIVE );

		result = mpDI8Mouse->SetCooperativeLevel( hWnd, flag );
		if( FAILED( result ) )
			Except( Exception::ERR_INTERNAL_ERROR, (String)"���� DirectInput8 ����豸Э���ȼ�����"
			"\nDX ����������" + DXGetErrorDescription9( result ) );

		//���û���ģʽ���
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj        = 0;
		dipdw.diph.dwHow        = DIPH_DEVICE;
		dipdw.dwData			= DI8_MOUSE_BUF_SIZE;

		result = mpDI8Mouse->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
		if( FAILED( result ) )
			Except( Exception::ERR_INTERNAL_ERROR, (String)"���� DirectInput8 ����豸���ݻ���ģʽ����"
			"\nDX ����������" + DXGetErrorDescription9( result ) );

		//��ȡ���
		mpDI8Mouse->Acquire();

		mbEnableMouse = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¼�������
	void DI8InputSystem::UpdateKeyboard()
	{
		if( !mbEnableKeyboard )
			return;

		static DIDEVICEOBJECTDATA didod[DI8_KEY_BUF_SIZE];
		DWORD dwElements = DI8_KEY_BUF_SIZE;

		//�����һ֡�¼�����
		memset( mbKeyDown, 0, sizeof(bool)*KEY_BUF_SIZE*2 );

Acquire:
		HRESULT result = mpDI8Keyboard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), didod, &dwElements, 0 );
		if( FAILED( result ) )
		{
			result = mpDI8Keyboard->Acquire();
			while( result == DIERR_INPUTLOST )
				result = mpDI8Keyboard->Acquire();

			if( SUCCEEDED( result ) )
				goto Acquire;

			Except( Exception::ERR_INTERNAL_ERROR, (String)"��ȡ DirectInput8 �����豸����"
				"\nDX ����������" + DXGetErrorDescription9( result ) );
		}

		//�������л�������
		for( DWORD i=0; i<dwElements; ++i )
		{
			//���̰������
			DWORD key = didod[i].dwOfs;

			//���������ĳ��
			if( didod[i].dwData & 0x80 )
			{
				mbKeyState[key] = true;
				mbKeyDown[key] = true;
				mbKeyUp[key] = false;
			}
			//����ſ���ĳ��
			else
			{
				mbKeyState[key] = false;
				mbKeyUp[key] = true;
				mbKeyDown[key] = false;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����������
	void DI8InputSystem::UpdateMouse()
	{
		if( !mbEnableKeyboard )
			return;

		static DIMOUSESTATE2 mouseState;
		static DIDEVICEOBJECTDATA didod[DI8_MOUSE_BUF_SIZE];
		DWORD dwElements = DI8_MOUSE_BUF_SIZE;
		DWORD dwTime = 0;
		bool bIsPressed = false;

		//�����һ֡�¼�����
		memset( mbMouseDown, 0, sizeof(bool)*9 );

		mMouseRelX = 0;
		mMouseRelY = 0;
		mMouseRelZ = 0;

Acquire:
		HRESULT result = mpDI8Mouse->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), didod, &dwElements, 0 );
		if( FAILED( result ) )
		{
			result = mpDI8Mouse->Acquire();
			while( result == DIERR_INPUTLOST )
				result = mpDI8Mouse->Acquire();

			if( SUCCEEDED( result ) )
				goto Acquire;

			Except( Exception::ERR_INTERNAL_ERROR, (String)"��ȡ DirectInput8 ����豸����"
				"\nDX ����������" + DXGetErrorDescription9( result ) );
		}

		//�������л�������
		for( DWORD i=0; i<dwElements; ++i )
		{
			//��Ϣ����ʱ��
			dwTime = didod[i].dwTimeStamp;

			//�Ƿ�Ϊ������Ϣ
			bIsPressed = ( didod[i].dwData & 0x80 ) ? true : false;

			switch( didod[i].dwOfs )
			{
				//�����Ϣ
			case DIMOFS_BUTTON0:
				mbMouseState[0] = bIsPressed;
				mbMouseDown[0] = bIsPressed;
				mbMouseUp[0] = !bIsPressed;

				//�������
				if( bIsPressed )
				{
					//�����ΰ�����ʱ�����ϴΰ�����ʱ����С��˫��ʱ��
					if( dwTime - mMouseLastDownTime[0] < mMouseDBClickTime[0] )
					{
						mbMouseDBClick[0] = true;
					}
					else
					{
						mMouseLastDownTime[0] = dwTime;
					}
				}
				break;

				//�Ҽ���Ϣ
			case DIMOFS_BUTTON1:
				mbMouseState[1] = bIsPressed;
				mbMouseDown[1] = bIsPressed;
				mbMouseUp[1] = !bIsPressed;

				//�������
				if( bIsPressed )
				{
					//�����ΰ�����ʱ�����ϴΰ�����ʱ����С��˫��ʱ��
					if( dwTime - mMouseLastDownTime[1] < mMouseDBClickTime[1] )
					{
						mbMouseDBClick[1] = true;
					}
					else
					{
						mMouseLastDownTime[1] = dwTime;
					}
				}
				break;

				//�м���Ϣ
			case DIMOFS_BUTTON2:
				mbMouseState[2] = bIsPressed;
				mbMouseDown[2] = bIsPressed;
				mbMouseUp[2] = !bIsPressed;

				//�������
				if( bIsPressed )
				{
					//�����ΰ�����ʱ�����ϴΰ�����ʱ����С��˫��ʱ��
					if( dwTime - mMouseLastDownTime[2] < mMouseDBClickTime[2] )
					{
						mbMouseDBClick[2] = true;
					}
					else
					{
						mMouseLastDownTime[2] = dwTime;
					}
				}
				break;

				//�����ƶ���Ϣ
			case DIMOFS_X:
				mMouseRelX += (int)( (long)didod[i].dwData * mMouseSpeed / 65 );
				break;
			case DIMOFS_Y:
				mMouseRelY += (int)( (long)didod[i].dwData * mMouseSpeed / 65 );
				break;
			case DIMOFS_Z:
				mMouseRelZ += (int)( (long)didod[i].dwData * mMouseSpeed / 65 );
				break;

			default:
				break;
			}
		}

		//�������λ��
		mMouseX += mMouseRelX;
		mMouseY += mMouseRelY;
		mMouseZ += mMouseRelZ;

		FixPosByMouseRect( &mMouseX, &mMouseY, &mMouseZ );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
