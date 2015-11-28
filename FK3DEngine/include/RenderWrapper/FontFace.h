/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	FontFace
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once


//���� FreeType 2.1.9 ͷ�ļ�
#include <ft2build.h>
#include FT_FREETYPE_H


//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//������
	class FK_DLL FontFace
	{
	public:
		friend class TextSurface;

		//������Ϣ
		struct GlyphInfo
		{
			wchar_t		wChar;		//�����ַ�
			int			nWidth;		//���ο��
			int			nHeight;	//���θ߶�
			int			nLeft;		//������߾�
			int			nTop;		//�����ϱ߾�
			int			nHorAdvance;//�����־�
			int			nVerAdvance;//�����־�

			int			nTexIndex;	//��������λ������
		};

		//���λ�������
		struct GlyphDraw
		{
			int			nUVIndex;	//������������
			int			nGlyphIndex;//������Ϣ����
			int			nDrawOrder;	//���λ������
		};

		//��������ͼ����Ϣ
		struct GlyphTex
		{
			wchar_t		wChar;		//�����ַ�
			UV4			sUV;		//������������
		};

	public:
		FT_Render_Mode	mRenderMode;	//������Ⱦģʽ

		Texture*		mpFontTexture;	//��������

		int				mnMaxWidth;		//����ַ����
		int				mnMaxHeight;	//����ַ��߶�

		int				mFontAscender;	//�����ϱ߾�
		int				mLineSpace;		//�м��

	protected:
		FT_Face			mFontFace;		// FreeType ���������

		int				mGlyphDataLen;	//�������ݴ�С
		BYTEStack		mGlyphDataStack;//�������ݶ�ջ
		int				mNumGlyphData;	//������������

		UINT			mnTexSize;		//��������ߴ�
		float			mfTexSizeInv;	//��������ߴ絹��

		UINT			mHorGlyphNum;	//������������
		UINT			mVerGlyphNum;	//������������

		GlyphTex*		mpGlyphTex;		//��������ͼ�񻺴�
		int*			mpDrawTime;		//����������ƴ���

		UINT			mCurGlyphNum;	//��ǰ��������
		UINT			mMaxGlyphNum;	//���������������
		UINT			mOverwritePos;	//��д����λ��

	public:
		FontFace( LPCSTR szFontFile, UINT nSize, UINT nTexSize, UINT nGlyphWidth, UINT nGlyphHeight,
			UINT nFontIndex, FT_Render_Mode eRenderMode );
		~FontFace();

		//׼��ָ������
		GlyphInfo* FKFastcall PrepareGlyph( wchar_t wChar, GlyphDraw* pGlyphDraw );

		//����������������
		UV4* FKFastcall ProcGlyphTex( GlyphDraw* pGlyphDraw );

		//��������ͼ������
		void FKFastcall ResetGlyphData();

	protected:
		//���ַ�ͼ���Ƶ�������
		void FKFastcall _CopyGlyphToTex( GlyphDraw* pGlyphDraw );
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< FontFace* >	FontFaceList;
	//--------------------------------------------------------------------------------------------------------------
};

//==================================================================================================================
