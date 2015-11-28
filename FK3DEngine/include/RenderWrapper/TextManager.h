/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	TextManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	���ֹ�����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

#include <list>

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//���ֹ�����
	class FK_DLL TextManager : public Singleton< TextManager >
	{
	public:
		Stack<TextSurface*> mTextSurfaceList;//ƽ�������б�
	public:
		TextManager();

		//����ƽ������
		TextSurface* CreateTextSurface( ZOrderType eZType, OverlaySurface* pZRefOverlay, FontFace* pFont,
			LPCWSTR szText, int nX, int nY, int nLineWidth = 0, int nMaxChars = 0, DWORD dwColor = 0xFFFFFFFF,
			TextureFilterType eFilterType = TFT_POINT );

		//ɾ��ƽ������
		void DeleteTextSurface( TextSurface* pTextSurface );

		//ɾ������ƽ������
		void DeleteAllTextSurface();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
