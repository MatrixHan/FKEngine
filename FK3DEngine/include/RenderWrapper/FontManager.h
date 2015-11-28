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
*	�ļ�˵����	���������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//���������
	class FK_DLL FontManager : public Singleton< FontManager >
	{
	public:
		friend class FontFace;

	protected:
		FT_Library		mFreeTypeLib;		// FreeType ��

		FileObject*		mpFontPackFile;		//�������ļ�ָ��
		FontFaceList	mFontFaceList;		//�����б�

	public:
		FontManager();
		~FontManager();

		//�����������ļ�
		void SetFontPack( FileObject* pFile );

		//�ر��������ļ�
		void DetachFontPack();

		//�����µ�����
		FontFace* CreateFontFace( LPCSTR szFontFile, UINT nSize, UINT nTexSize = 512, UINT nGlyphWidth = 0,
			UINT nGlyphHeight = 0, UINT nFontIndex = 0, FT_Render_Mode eRenderMode = FT_RENDER_MODE_NORMAL );

		//ɾ������
		void DeleteFontFace( FontFace* pFont );

		//ɾ����������
		void DeleteAllFont();
		
		//����������Ⱦ����
		void UpdateFont();

	protected:
		//���� FreeType ����
		FT_Face _LoadFontFace( LPCSTR szFontFile, UINT nFaceIndex );
	};
	//--------------------------------------------------------------------------------------------------------------
};

//==================================================================================================================
