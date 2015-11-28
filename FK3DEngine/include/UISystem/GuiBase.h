/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiBase
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�����û��������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//------------------------------------------------------------------------------------------------------------------
// �û�������Ϣ�б�

// GM_ Ϊ����Ϣǰ׺		// GMA_ Ϊ������Ϣ A ǰ׺		// GMB_ Ϊ������Ϣ B ǰ׺

//������Ϣ
#define GM_Base					0

#define GM_Unknown				GM_Base+0
#define GM_Enable				GM_Base+1		//����/�رտؼ�					GMA=1 ����		GMA=0 �ر�
#define GM_Show					GM_Base+2		//��ʾ/���ؿؼ�					GMA=1 ��ʾ		GMA=0 ����
#define GM_Focus				GM_Base+3		//���/ʧȥ����					GMA=1 ���		GMB=0 ʧȥ
#define GM_MouseMove			GM_Base+4		//����ƶ�						GMA ����ϵͳָ��
#define GM_SetPos				GM_Base+5		//����λ��						GMA X����		GMB Y����
#define GM_MovePos				GM_Base+6		//�ƶ�λ��						GMA X�������	GMB Y�������
#define GM_SetSize				GM_Base+7		//���óߴ�						GMA ���		GMB �߶�
#define GM_SetZOrder			GM_Base+8		//���� Z ˳��					GMA Z ˳������	GMB ��׼ƽ��ͼ��
#define GM_GetZOrder			GM_Base+9		//��ȡ Z ˳���׼ƽ��ͼ��		GMA Z ˳������

//������Ϣ
#define GM_Input				20

#define GM_LDBClick				GM_Input+0		//���˫��						GMA X����		GMB Y����
#define GM_RDBClick				GM_Input+1		//�Ҽ�˫��						GMA X����		GMB Y����
#define GM_LDown				GM_Input+2		//�������						GMA X����		GMB Y����
#define GM_RDown				GM_Input+3		//�Ҽ�����						GMA X����		GMB Y����
#define GM_LUp					GM_Input+4		//����ͷ�						GMA X����		GMB Y����
#define GM_RUp					GM_Input+5		//�Ҽ��ͷ�						GMA X����		GMB Y����

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//λ�������ṹ����Ը������Ͻǵ�λ�ã�
	struct GuiLoca
	{
		LONG	X;
		LONG	Y;
		UINT	Width;
		UINT	Height;
	};
	//--------------------------------------------------------------------------------------------------------------
	//���������ṹ
	struct GuiRect
	{
		int Left;
		int Top;
		int Right;
		int Bottom;		
	};
	//--------------------------------------------------------------------------------------------------------------
	//�ͻ�������ͼ
	struct GuiMaskMap
	{
		int		nWidth;
		int		nHeight;
		UINT	nBytes;
		BYTE*	pBitMask;
	};
	//--------------------------------------------------------------------------------------------------------------
	//�ͻ�����Χ
	class FK_DLL GuiClient
	{
	public:
		//�ͻ�������
		enum Type
		{
			NoClient,	//�޿ͻ���
			Rect,		//������
			MaskMap		//����ͼ
		};

		Type			mType;

		//�ͻ�����Χ
		union
		{
			GuiRect		mRect;
			GuiMaskMap	mMaskMap;
		};

	public:
		GuiClient();
		GuiClient( const GuiClient& refClient );
		GuiClient( int nLeft, int nTop, int nRight, int nBottom );

		//���þ��οͻ�����Χ
		void FKFastcall SetClient( int nLeft, int nTop, int nRight, int nBottom );

		//���ָ�������Ƿ��ڿͻ�����
		bool FKFastcall IsOnClient( int x, int y );
	};
	//--------------------------------------------------------------------------------------------------------------
	class GuiDialog;
	//--------------------------------------------------------------------------------------------------------------
	//�����û��������
	class FK_DLL GuiBase
	{
	public:
		bool			mbEnable;		//��ʶ�Ƿ���
		bool			mbVisable;		//��ʶ�Ƿ����
		bool			mbFocus;		//��ʶ�Ƿ��ý���

		GuiDialog*		mpDialog;		//�����û�����Ի���

		GuiLoca			mLoca;			//����λ��
		GuiClient		mClient;		//�ͻ�����Χ

	public:
		GuiBase( GuiLoca* pLoca, GuiClient* pClient, GuiDialog* pDialog = NULL );
		virtual ~GuiBase() = 0;

		//���ָ�������Ƿ��ڿͻ�����
		bool FKFastcall IsOnClient( int x, int y );

	public:
		//���û������������Ϣ
		virtual LONG_PTR SendMsg( LONG_PTR nGM, LONG_PTR nGMA = 0, LONG_PTR nGMB = 0 ) = 0;
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< GuiBase* >	GuiList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

