/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Edit
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "Color.h"
#include "UIControl.h"
#include "Font.h"
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	//! ������ͣ���ֱ/ˮƽ��
	enum ENUM_CaretStyle
	{
		ECS_Vertical,
		ECS_Horizontal,
	};
	//--------------------------------------------------------------------
	//! �ı��༭��
	//@remarks ��ʱ��֧�ּ��а������
	class CEdit : public IGUIControl
	{
	public:
		CEdit();
		virtual ~CEdit(){}
	public:
		void Create( IGUIControl* p_pParent, int p_nLeft, int p_nTop, int p_nWidth );
		virtual void FKDraw() const;
		virtual void Update( float p_fDelta );

	public:
		void SetParent( IGUIControl* p_pParent );
		void SetFont( CFont& p_Font );
		void SetText( const std::wstring& p_Text );
		std::wstring GetText() const;
		//! ���ù����ɫ
		void SetCaretColor( CColor p_Color );
		//! ���ù������
		void SetCaretType( ENUM_CaretStyle p_eStyle );

	public:
		//! ��д���¼�������
		//! ��갴��
		virtual void MouseDown( POINT p_Point, ENUM_MouseButton p_eMB );
		//! ���̰���
		virtual void KeyDown( unsigned long p_ulKey, SShiftState p_State );
		//! �ַ�������
		virtual void KeyPress( char p_cKey );

	private:
		//! �ƶ����
		void MoveCaret( int p_nOffset );

	private:
		std::wstring			m_szText;		// �ı�����
		float					m_fTime;		// ��ʱ��
		int						m_nCaretPos;	// ���λ��
		int						m_nCharWidth;	// �ַ����
		bool					m_bShowCaret;	// �Ƿ���ʾ���
		CColor					m_CaretColor;	// �����ɫ
		ENUM_CaretStyle			m_eCaretStyle;	// �������
	};
}