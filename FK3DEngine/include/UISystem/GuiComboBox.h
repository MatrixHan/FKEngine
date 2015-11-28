/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiComboBox
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class TextSurface;
	class SpriteSet;
	class FontFace;
	class Sprite;
	//--------------------------------------------------------------------------------------------------------------
	//��Ͽ����
	class FK_DLL GuiComboBox : public GuiBase
	{
	public:
		//��Ͽ����
		struct Param
		{
			SpriteSet*		pSpriteSet;		//���鼯
			FontFace*		pFontFace;		//��������
			UINT			nItemNum;		//��ʼ�б�������

			int				nX;				// X ����
			int				nY;				// Y ����
			int				nWidth;			//���
			int				nChoosenHeight;	//ѡ����߶�
			int				nItemHeight;	//�б���߶�
			int				nBoarderHeight;	//�б��߿�߶�
			int				nTextLeft;		//����ƫ�� X ����
			int				nTextTop;		//����ƫ�� Y ����
			GuiClient		sChoosenClient;	//ѡ����ͻ���
		};

		//�б���ṹ
		struct Item
		{
			LONG_PTR		pData;			//�б�������

			Sprite*			pItemSprite;	//�б����
			TextSurface*	pItemText;		//�б�������
		};
		typedef Stack< Item >	ItemList;

	protected:
		SpriteSet*		mpSpriteSet;		//��Ͽ��鼯ָ��
		FontFace*		mpTextFont;			//�б�����������

		UV4				mTopBoarderUV;		//�ϱ߿� UV
		UV4				mBottomBoarderUV;	//�±߿� UV
		UV4				mNormalUV;			//��ͨѡ���� UV
		UV4				mHighLightUV;		//�߹�ѡ���� UV
		UV4				mItemUV;			//�б��� UV

		Sprite*			mpChoosenItem;		//ѡ�����
		TextSurface*	mpChoosenText;		//ѡ��������

		Sprite*			mpHighLightItem;	//�б���߹����־���
		Sprite*			mpBoarder;			//ѡ����߿���

		int				mX;					//��Ͽ� X ����
		int				mY;					//��Ͽ� Y ����
		int				mWidth;				//��Ͽ���
		int				mChoosenHeight;		//ѡ����߶�
		int				mItemHeight;		//�б���߶�
		int				mBoarderHeight;		//�б��߿�߶�
		int				mTextLeft;			//����ƫ�� X ����
		int				mTextTop;			//����ƫ�� Y ����

		GuiClient		mChoosenClient;		//ѡ����ͻ���
		bool			mbChoosenFocus;		//ѡ�����

		GuiClient		mListClient;		//�б�ͻ���
		bool			mbShowList;			//�Ƿ���ʾ�б�

		ItemList		mItemList;			//�б���
		int				mnFocusItem;		//�����б�������

	public:
		GuiComboBox( ZOrderType eZType, OverlaySurface* pZRefOverlay, GuiDialog* pDialog, Param* pParam );
		~GuiComboBox();

	public:
		//����/�رտؼ�
		void FKFastcall Enable( bool bEnable );

		//��ʾ/���ؿؼ�
		void FKFastcall Show( bool bShow );

		//����λ��
		void FKFastcall SetPos( long nX, long nY );

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

		//�����б���
		void FKFastcall AddItem( const wchar_t* szName, UINT nIndex, LONG_PTR pData = 0 );

		//ɾ���б���
		void FKFastcall DelItem( UINT nIndex );

		//ɾ�������б���
		void FKFastcall DelAllItem();

		//ѡ���б���
		void FKFastcall SelItem( UINT nIndex );

	public:
		//���û������������Ϣ
		LONG_PTR SendMsg( LONG_PTR nGM, LONG_PTR nGMA = 0, LONG_PTR nGMB = 0 );

	protected:
		//��ʾ�����б�
		void FKFastcall _ShowList();

		//���������б�
		void FKFastcall _HideList();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

