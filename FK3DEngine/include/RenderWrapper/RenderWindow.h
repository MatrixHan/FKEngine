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
*	�ļ�˵����	��Ⱦ������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//������Ϣ
	struct WindowInfo
	{
		char*		sCaption;	//���ڱ���
		bool		bCenter;	//�Ƿ񴰿ھ���
		UINT		nLeft;		//��߾�
		UINT		nTop;		//�ϱ߾�
		UINT		nWidth;		//���
		UINT		nHeight;	//�߶�
		DWORD		dwStyle;	//���ڷ��

		WNDPROC		fnWndProc;	//������Ϣ������
		HCURSOR		hCursor;	//�������ָ����
		HICON		hIcon;		//����ͼ����
	};
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ������
	class FK_DLL RenderWindow
	{
	public:
		HWND			mhWnd;			//���ھ��
		HINSTANCE		mhInst;			//����ʵ�����
		WNDCLASSEX		mWndClass;		//��������

		String			mWndCaption;	//���ڱ���
		UINT			mnLeft;			//��߾�
		UINT			mnTop;			//�ϱ߾�
		UINT			mnWidth;		//���
		UINT			mnHeight;		//�߶�
		DWORD			mdwStyle;		//���ڷ��

		UINT			mnClientWidth;	//�ͻ������
		UINT			mnClientHeight;	//�ͻ����߶�

		HCURSOR			mhCursor;		//���ָ����

		MSG				mMsg;			//������Ϣ
		bool			mbDestroy;		//�����Ƿ�����
		bool			mbActive;		//�����Ƿ񱻼���
		bool			mbInner;		//�Ƿ�Ϊ�ڲ�����
		bool			mbShowCursor;	//�Ƿ���ʾ���ָ��

	public:
		RenderWindow();
		~RenderWindow();

		//�ڲ�������Ϣ�������������ڴ���Ĵ�����Ϣ�����е��ã�
		LRESULT WinProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

		//������Ⱦ����
		void Create( const WindowInfo* pWndInfo );

		//ʹ���Ѵ��ڴ��ڴ�����Ⱦ����
		void CreateByExist( HWND hWnd );

		//��ʾ/������Ϸ����
		void ShowGameWindow( bool bShow = true );

		//��ʾ/������Ϸ�������ָ��
		void ShowCursor( bool bShow = true );

	protected:
		//��ȡ����λ��
		void _GetWindowRect();

		//��ȡ�ͻ����ߴ�
		void _GetWindowClient();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
