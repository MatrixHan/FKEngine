/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Text
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "InsidePreInclude.h"
#include "Color.h"
#include "GraphicsBase.h"
#include <string>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//! ���ص�ǰƽ̨�µ�Ĭ����������
	std::wstring DefaultFontName();

	//! ����һ��������ռ�����ؿ��
	unsigned int TextWidth( const std::wstring& p_Text, const std::wstring& p_FontName,
		unsigned int p_unFontWight, unsigned int p_unFontFlags = 0 );

	//! ��һ�� Bitmap �ϻ���һ������
	void FKDrawText( CBitmap& p_Bitmap, const std::wstring& p_Text,
		int p_nX, int p_nY, CColor p_Color, const std::wstring& p_FontName,
		unsigned int p_unFontHeight, unsigned int p_unFontFlags = 0 );

	//! ����һ�� Bitmap �����������һ������
	CBitmap CreateText( const std::wstring& p_Text, const std::wstring& p_FontName,
		unsigned int p_unFontHeight, unsigned int p_unFontFlags = 0 );

	CBitmap CreateText( const std::wstring& p_Text, const std::wstring& p_FontName,
		unsigned int p_unFontHeight, int p_nLineSpacing, unsigned int p_unMaxWidth,
		ENUM_TextAlign p_eAlign, unsigned int p_unFontFlags = 0 );

	void RegisterEntity( const std::wstring& p_Name, const CBitmap& p_Replacement );
}