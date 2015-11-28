/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	TextSurface
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	ƽ��������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//ƽ��������
	class FK_DLL TextSurface : public OverlaySurface
	{
	public:
		friend class TextManager;

	public:
		FontFace*		mpFont;			//��������
		wchar_t*		mpText;			//���������ַ���
		int				mNumChars;		//�����ַ�����
		int				mMaxChars;		//����ַ�����
		int				mX;				//������ʾ X ����
		int				mY;				//������ʾ Y ���꣨���ֻ��ߣ�
		int				mLineWidth;		//�����п�
		DWORD			mTextColor;		//������ɫ

	protected:
		FontFace::GlyphDraw*	mpGlyphDraw;	//�������λ�������
		OverlayVertex*			mpVertexData;	//���ֶ�������

		UINT					mNumDrawGroup;	//������Ⱦ��������
		UINT					mpDrawGroup[8];	//������Ⱦ��������

	public:
		TextSurface( ZOrderType eZType, OverlaySurface* pZRefOverlay, FontFace* pFont, LPCWSTR szText, int nX, int nY,
			int nLineWidth, int nMaxChars = 0, DWORD dwColor = 0xFFFFFFFF, TextureFilterType eFilterType = TFT_POINT );
		~TextSurface();
	

		//��������ַ�����
		void SetMaxChars( int nMaxChars );

		//������������
		void SetText( LPCWSTR szText );

		//��������λ��
		void SetTextPos( int nX, int nY );

		//����������ɫ
		void SetTextColor( DWORD dwColor );

	protected:
		//������������
		void FKFastcall _UpdateText();

		//����ƽ��ͼ�񶥵�
		void FKFastcall _ProcessVertex();

		//��Ⱦƽ��ͼ��
		void FKFastcall _RenderOverlay();
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< TextSurface* >	TextSurfaceList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
