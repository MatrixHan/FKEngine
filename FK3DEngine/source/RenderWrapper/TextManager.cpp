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
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderWrapper/RenderWrapperInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	TextManager::TextManager()
	{
		mTextSurfaceList.Initialize( 32, 16 );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƽ������
	TextSurface* TextManager::CreateTextSurface( ZOrderType eZType, OverlaySurface* pZRefOverlay, FontFace* pFont,
		LPCWSTR szText, int nX, int nY, int nLineWidth, int nMaxChars, DWORD dwColor, TextureFilterType eFilterType )
	{
		////�Զ����㻻�п��
		if( nLineWidth == 0 )
			nLineWidth = OverlayManager::mpSingleton->mRenderWidth - nX - 10;

		TextSurface* pTextSurface = new TextSurface( eZType, pZRefOverlay, pFont, szText,
			nX, nY, nLineWidth, nMaxChars, dwColor, eFilterType );
		
		*mTextSurfaceList.Push() = pTextSurface ;

		return pTextSurface;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ƽ������
	void TextManager::DeleteTextSurface( TextSurface* pTextSurface )
	{
		if( pTextSurface == NULL )
			return;

		Stack<TextSurface*>::Iterator it = mTextSurfaceList.Begin();
		Stack<TextSurface*>::Iterator end = mTextSurfaceList.End();
		for(; it!=end; ++it )
		{
			if( *it == pTextSurface )
			{
				mTextSurfaceList.Erase( it );
				delete pTextSurface;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ������ƽ������
	void TextManager::DeleteAllTextSurface()
	{
		Stack<TextSurface*>::Iterator it = mTextSurfaceList.Begin();
		Stack<TextSurface*>::Iterator end = mTextSurfaceList.End();
		for(; it!=end; ++it )
		{
			if( *it != NULL )
				delete *it;
		}

		mTextSurfaceList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
