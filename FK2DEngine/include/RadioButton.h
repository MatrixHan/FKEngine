/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RadioButton
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "CheckBox.h"
#include "Bitmap.h"
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	class IGUIControl;
	//--------------------------------------------------------------------
	//! ��ѡ��
	class CRadioButton : public CCheckBox
	{
	public:
		CRadioButton();
		virtual ~CRadioButton(){};
	public:
		void Create( IGUIControl* p_pParent, int p_nLeft, int p_nTop,
			CBitmap& p_Bitmap, const std::wstring& p_szCaption );

		void Check();
		void SetGroup( int p_nGroup );
		int GetGroup() const;
	public:
		virtual void MouseUp( POINT p_Point, ENUM_MouseButton p_eMB );
	private:
		int					m_nGroup;			// ��ť������
	};
	//--------------------------------------------------------------------
}