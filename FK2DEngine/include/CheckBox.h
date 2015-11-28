/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	CheckBox
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "PicButton.h"
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	//! ��ѡ��
	class CCheckBox : public CPicButton
	{
	public:
		CCheckBox();
		virtual ~CCheckBox(){}
	public:
		void Create( IGUIControl* p_pParent, int p_nLeft, int p_nTop,
			CBitmap& p_Bitmap, const std::wstring& p_szCaption );

		virtual void FKDraw() const;

		//! ����ͼƬ
		//@note Ҫ��һ������ͼƬ��ǰ���к� CPicButton һ�£�������Ϊѡ�мǺţ�������Ϊδѡ��״̬
		void SetGlygh( CBitmap& p_Bitmap );

		void Check();
		void UnCheck();
		bool IsChecked();
	public:
		//! ��д����¼�����
		virtual void MouseUp( POINT p_Point, ENUM_MouseButton p_eMB );
	protected:
		bool			m_bChecked;		// �Ƿ�ѡ��
	};
	//--------------------------------------------------------------------
}