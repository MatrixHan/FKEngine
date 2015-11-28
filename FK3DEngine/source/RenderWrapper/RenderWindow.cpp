/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RenderWindow
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
	RenderWindow::RenderWindow()
		: mhWnd				(NULL)
		, mnLeft			(0)
		, mnTop				(0)
		, mnWidth			(0)
		, mnHeight			(0)
		, mdwStyle			(0)
		, mnClientWidth		(0)
		, mnClientHeight	(0)
		, mhCursor			(NULL)
		, mbDestroy			(false)
		, mbActive			(false)
		, mbInner			(false)
		, mbShowCursor		(true)
	{
		memset( &mMsg, 0, sizeof(MSG) );
	}
	//--------------------------------------------------------------------------------------------------------------
	RenderWindow::~RenderWindow()
	{
		//���Ϊ�ڲ���������
		if( mbInner )
		{
			//�ݻٴ���
			DestroyWindow( mhWnd );

			//ע��������
			UnregisterClass( "MyGame", mWndClass.hInstance );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ڲ�������Ϣ�������������ڴ���Ĵ�����Ϣ�����е��ã�
	LRESULT RenderWindow::WinProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
	{
		switch( msg )
		{
			//��ֹ��������ָ�뱻�������
		case WM_SETCURSOR:
			{
				if( mbShowCursor )
					SetCursor( mhCursor );
				else
					SetCursor( NULL );

				return 0;
			}

			//�����򼤻�״̬�ı�ʱͬʱ�ı��������״̬
		case WM_ACTIVATEAPP:
			{
				if( LOWORD( wParam ) == WA_INACTIVE )
				{
					mbActive = false;
				}
				else
				{
					mbActive = true;
				}

				break;
			}

			//��ֹ��������Ļ��������ʾ���ڵ�ģʽ����
		case WM_SYSCOMMAND:
			{
				switch (wParam)
				{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
				}
				break;
			}

			//ˢ�´��ڴ�Сʱ
		case WM_PAINT:
			{
				ValidateRect( mhWnd, NULL );
				return 0;
			}

			//�ı䴰�ڴ�Сʱ
		case WM_SIZE:
			{
				_GetWindowRect();
				_GetWindowClient();
				ValidateRect( mhWnd, NULL );
				return 0;
			}

			//�ƶ�����ʱ
		case WM_MOVE:
			{
				_GetWindowRect();
				ValidateRect( mhWnd, NULL );
				return 0;
			}

			//���ڱ�����
		case WM_DESTROY:
			{
				mbDestroy = true;
				mbActive = false;
				break;
			}
		}

		return DefWindowProc( hWnd, msg, wParam, lParam );
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ⱦ����
	void RenderWindow::Create( const WindowInfo* pWndInfo )
	{
		//�����Ϣ������ָ��
		if( pWndInfo->fnWndProc == NULL )
			Except( Exception::ERR_INVALIDPARAMS, "��Ϸ������Ϣ������Ϊ�գ��޷��������ڡ�" );

		//�洢������Ϣ
		mWndCaption	= pWndInfo->sCaption;
		mnLeft		= pWndInfo->nLeft;
		mnTop		= pWndInfo->nTop;
		mnWidth		= pWndInfo->nWidth;
		mnHeight	= pWndInfo->nHeight;
		mdwStyle	= pWndInfo->dwStyle;

		mhCursor	= pWndInfo->hCursor;
		
		//������ô��ھ������Զ����㴰�ڱ߾�
		if( pWndInfo->bCenter )
		{
			mnLeft = ( GetSystemMetrics(SM_CXSCREEN) - mnWidth ) / 2;
			mnTop = ( GetSystemMetrics(SM_CYSCREEN) - mnHeight ) / 2;
		}

		//��ȡ��ǰ���̾��
		mhInst = (HINSTANCE)GetModuleHandle( NULL );

		//���ò�ע�ᴰ������
		mWndClass.cbSize		= sizeof(WNDCLASSEX);
		mWndClass.style			= CS_HREDRAW | CS_VREDRAW;
		mWndClass.lpfnWndProc	= pWndInfo->fnWndProc;
		mWndClass.cbClsExtra	= 0;
		mWndClass.cbWndExtra	= 0;
		mWndClass.hInstance		= mhInst;
		mWndClass.hIcon			= pWndInfo->hIcon;
		mWndClass.hCursor		= mhCursor;
		mWndClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
		mWndClass.lpszMenuName	= NULL;
		mWndClass.lpszClassName	= pWndInfo->sCaption;
		mWndClass.hIconSm		= NULL;

		RegisterClassEx( &mWndClass );

		//�������򴰿�
		mhWnd = CreateWindow(
			pWndInfo->sCaption,
			pWndInfo->sCaption,
			mdwStyle,
			mnLeft,
			mnTop,
			mnWidth,
			mnHeight,
			NULL, NULL, mhInst, NULL );
		if( mhWnd == NULL )
			Except( Exception::ERR_WINAPI_ERROR, "������Ϸ����ʧ�ܡ�" );

		//��ȡ���ڿͻ����ߴ�
		_GetWindowClient();

		//�����ش���
		ShowWindow( mhWnd, SW_HIDE );
		UpdateWindow( mhWnd );

		mbInner = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ʹ���Ѵ��ڴ��ڴ�����Ⱦ����
	void RenderWindow::CreateByExist( HWND hWnd )
	{
		//��ȡ������Ϣ
		mhWnd = hWnd;

		//��ȡ����ʵ��
		mhInst = (HINSTANCE)GetModuleHandle( NULL );

		//��ȡ���ڷ��
		mdwStyle = (DWORD)GetWindowLong( mhWnd, GWL_STYLE ) | (DWORD)GetWindowLong( mhWnd, GWL_EXSTYLE );

		//��ȡ�������꼰�ͻ����ߴ�
		_GetWindowRect();
		_GetWindowClient();

		//��ȡ���ڱ���
		char szCaption[512];
		if( 0 == GetWindowText( hWnd, szCaption, 512 ) )
			Except( Exception::ERR_WINAPI_ERROR, "��ȡ�ⲿ������Ϸ���ڵı������" );
		else
			mWndCaption = szCaption;

		mbInner = false;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʾ/������Ϸ����
	void RenderWindow::ShowGameWindow( bool bShow )
	{
		ShowWindow( mhWnd, SW_NORMAL );
		UpdateWindow( mhWnd );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʾ/������Ϸ�������ָ��
	void RenderWindow::ShowCursor( bool bShow )
	{
		if( bShow )
			SetCursor( mhCursor );
		else
			SetCursor( NULL );

		mbShowCursor = bShow;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ����λ��
	void RenderWindow::_GetWindowRect()
	{
		RECT rc;
		GetWindowRect( mhWnd, &rc );

		mnLeft		= rc.left;
		mnTop		= rc.top;
		mnWidth		= rc.right - rc.left;
		mnHeight	= rc.bottom - rc.top;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ͻ����ߴ�
	void RenderWindow::_GetWindowClient()
	{
		RECT rc;
		GetClientRect( mhWnd, &rc );

		mnClientWidth	= rc.right - rc.left;
		mnClientHeight	= rc.bottom - rc.top;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
