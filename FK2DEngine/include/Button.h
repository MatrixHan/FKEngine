/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Button
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "../Include/PicButton.h"
#include "../Include/Bitmap.h"
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	class IGUIControl;
	//--------------------------------------------------------------------
	class CButton : public CPicButton
	{
	public:
		void Create( IGUIControl* p_pParent, int p_nLeft, int p_nTop, 
			CBitmap& p_Bitmap, const std::wstring& p_szCaption );

		virtual void FKDraw() const;

		void SetCaption( const std::wstring& p_szCaption );
	private:
		POINT				m_TextPos;		// ����λ��
	};
	//--------------------------------------------------------------------
}