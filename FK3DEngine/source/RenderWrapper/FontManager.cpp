/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	FontManager
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
	FontManager::FontManager()
	{
		mFontFaceList.Initialize( 10, 5 );

		//��ʼ�� FreeType ��
		FT_Error error = FT_Init_FreeType( &mFreeTypeLib );
		if( error != 0 )
			Except( Exception::ERR_INTERNAL_ERROR, "��ʼ�� FreeType ʧ�ܡ�" );
	}
	//--------------------------------------------------------------------------------------------------------------
	FontManager::~FontManager()
	{
		//ɾ����������
		DeleteAllFont();

		//�ͷ� FreeType ��
		FT_Done_FreeType( mFreeTypeLib );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����������ļ�
	void FontManager::SetFontPack( FileObject* pFile )
	{
		mpFontPackFile = pFile;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ر��������ļ�
	void FontManager::DetachFontPack()
	{
		mpFontPackFile = NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����µ�����
	FontFace* FontManager::CreateFontFace( LPCSTR szFontFile, UINT nSize, UINT nTexSize, UINT nGlyphWidth,
		UINT nGlyphHeight, UINT nFontIndex, FT_Render_Mode eRenderMode )
	{
		FontFace* pFont = new FontFace( szFontFile, nSize, nTexSize, nGlyphWidth, nGlyphHeight, nFontIndex, eRenderMode );
		*mFontFaceList.Push() = pFont;
		return pFont;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ������
	void FontManager::DeleteFontFace( FontFace* pFont )
	{
		if( pFont == NULL )
			return;

		FontFaceList::Iterator it = mFontFaceList.Begin();
		FontFaceList::Iterator end = mFontFaceList.End();
		for(; it!=end; ++it )
		{
			if( *it == pFont )
			{
				mFontFaceList.Erase( it );
				delete pFont;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ����������
	void FontManager::DeleteAllFont()
	{
		FontFaceList::Iterator it = mFontFaceList.Begin();
		FontFaceList::Iterator end = mFontFaceList.End();
		for(; it!=end; ++it )
			SafeDelete( *it );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������Ⱦ����
	void FontManager::UpdateFont()
	{
		FontFaceList::Iterator it = mFontFaceList.Begin();
		FontFaceList::Iterator end = mFontFaceList.End();
		for(; it!=end; ++it )
		{
			FontFace* pFont = *it;
			pFont->ResetGlyphData();
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� FreeType ����
	FT_Face FontManager::_LoadFontFace( LPCSTR szFontFile, UINT nFaceIndex )
	{
		//��������
		FT_Face pFontFace = NULL;
		FT_Error error = FT_New_Face( mFreeTypeLib, szFontFile, nFaceIndex, &pFontFace );
		if( error != 0 )
		{
			if( error == FT_Err_Cannot_Open_Resource )
				Except( Exception::ERR_INVALIDPARAMS, (String)"�Ҳ���ָ���������ļ� '" + szFontFile + "'��" );
			else if( error == FT_Err_Unknown_File_Format )
				Except( Exception::ERR_INVALIDPARAMS, "�����ļ���ʽ�����޷��������塣" );
			else
				Except( Exception::ERR_INTERNAL_ERROR, "��������ʧ�ܡ�" );
		}

		return pFontFace;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
