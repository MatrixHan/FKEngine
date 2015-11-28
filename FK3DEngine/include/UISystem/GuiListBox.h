/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiListBox
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�б�����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//�б�����
	class FK_DLL GuiListBox : public GuiBase
	{
	public:
		//�б�����
		struct Param
		{
			SpriteSet*		pSpriteSet;		//���鼯
			FontFace*		pFontFace;		//��������
			UINT			nItemNum;		//��ʼ�б�������

			int				nX;				// X ����
			int				nY;				// Y ����
			int				nBkgWidth;		//�������
			int				nBkgHeight;		//�����߶�
		};

	protected:
		SpriteSet*		mpSpriteSet;		//�б���鼯ָ��
		FontFace*		mpTextFont;			//�б�����������

		int				mX;					// X ����
		int				mY;					// Y ����

	public:
		GuiListBox( GuiDialog* pDialog, Param* pParam );
		~GuiListBox();

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

	protected:

	public:
		//���û������������Ϣ
		LONG_PTR SendMsg( LONG_PTR nGM, LONG_PTR nGMA = 0, LONG_PTR nGMB = 0 );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

