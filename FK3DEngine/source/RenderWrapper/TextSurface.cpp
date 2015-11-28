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
	TextSurface::TextSurface( ZOrderType eZType, OverlaySurface* pZRefOverlay, FontFace* pFont, LPCWSTR szText,
		int nX, int nY, int nLineWidth, int nMaxChars, DWORD dwColor, TextureFilterType eFilterType )
		:OverlaySurface	( eZType, pZRefOverlay, eFilterType )
		 ,mpFont			(pFont)
		, mpText			(NULL)
		, mNumChars			(0)
		, mX				(nX)
		, mY				(nY)
		, mLineWidth		(nLineWidth)
		, mTextColor		(dwColor)
	{
		if( nX + mpFont->mnMaxWidth > nLineWidth )
			Except( Exception::ERR_INVALIDPARAMS, "ָ��ƽ�������п�ȹ�С��" );

		//�����ַ�������
		int nNumChars = 0;
		wchar_t* pChar = (wchar_t*)szText;
		while( *pChar != 0 )
		{
			++pChar;
			++nNumChars;
		}

		//���δָ������ַ�������ʹ�õ�ǰ�ַ����ַ�����
		if( nMaxChars == 0 )
			mMaxChars = nNumChars;
		else if( nMaxChars < nNumChars )
			Except( Exception::ERR_INVALIDPARAMS, "ָ��������ַ�����С�ڵ�ǰ�����ַ�������" );
		else
			mMaxChars = nMaxChars;

		mNumChars = nNumChars;

		//�����ڴ�
		size_t nStrLen = sizeof(wchar_t) * ( mMaxChars + 1 );
		size_t nDrawLen = sizeof(FontFace::GlyphDraw) * mMaxChars;

		BYTE* pMem = (BYTE*)malloc( nStrLen + nDrawLen + sizeof(OverlayVertex)*6*mMaxChars );

		//�����ַ���
		mpText = (wchar_t*)pMem;
		memcpy( mpText, szText, sizeof(wchar_t) * ( mNumChars + 1 ) );

		//�����������ݻ���
		mpGlyphDraw = (FontFace::GlyphDraw*)( pMem + nStrLen );
		memset( mpGlyphDraw, 0, nDrawLen );

		//���䶥�����ݻ���
		mpVertexData = (OverlayVertex*)( pMem + nStrLen + nDrawLen );
		mpVertexPtr = mpVertexData;
		mNumVertex = 0;

		//������������
		_UpdateText();
	}
	//--------------------------------------------------------------------------------------------------------------
	TextSurface::~TextSurface()
	{
		SafeFree( mpText );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ַ�����
	void TextSurface::SetMaxChars( int nMaxChars )
	{
		free( mpText );

		//�����ڴ�
		size_t nStrLen = sizeof(wchar_t) * ( nMaxChars + 1 );
		size_t nDrawLen = sizeof(FontFace::GlyphDraw) * nMaxChars;

		BYTE* pMem = (BYTE*)malloc( nStrLen + nDrawLen + sizeof(OverlayVertex)*6*nMaxChars );

		//�������ַ�������
		mMaxChars = nMaxChars;
		mNumChars = 0;

		mpText = (wchar_t*)pMem;
		memset( mpText, 0, nStrLen + nDrawLen );

		//�����������ݻ���
		mpGlyphDraw = (FontFace::GlyphDraw*)( pMem + nStrLen );

		//���䶥�����ݻ���
		mpVertexData = (OverlayVertex*)( pMem + nStrLen + nDrawLen );
		mpVertexPtr = mpVertexData;

		//������������
		_UpdateText();
	}
	//--------------------------------------------------------------------------------------------------------------
	//������������
	void TextSurface::SetText( LPCWSTR szText )
	{
		//�����ַ�������
		int mNumChars = 0;
		wchar_t* pChar = (wchar_t*)szText;
		while( *pChar != 0 )
		{
			++pChar;
			++mNumChars;
		}

		if( mMaxChars < mNumChars )
			Except( Exception::ERR_INVALIDPARAMS, "ָ���������ַ���������������ַ�������" );

		//�����ַ���
		memcpy( mpText, szText, sizeof(wchar_t) * ( mNumChars + 1 ) );

		//�����������ݻ���
		memset( mpGlyphDraw, 0, sizeof(FontFace::GlyphDraw) * mMaxChars );

		//������������
		_UpdateText();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ı�����λ��
	void TextSurface::SetTextPos( int nX, int nY )
	{
		//��������λ�ò�ֵ
		float fOffsetX = (float)( nX - mX );
		float fOffsetY = (float)( nY - mY );

		//�����������ζ���λ��
		wchar_t* pChar = mpText;
		OverlayVertex* pVertex = mpVertexData;

		while( *pChar != 0 )
		{
			++pChar;

			pVertex->x += fOffsetX;	pVertex->y += fOffsetY;	++pVertex;
			pVertex->x += fOffsetX;	pVertex->y += fOffsetY;	++pVertex;
			pVertex->x += fOffsetX;	pVertex->y += fOffsetY;	++pVertex;
			pVertex->x += fOffsetX;	pVertex->y += fOffsetY;	++pVertex;
			pVertex->x += fOffsetX;	pVertex->y += fOffsetY;	++pVertex;
			pVertex->x += fOffsetX;	pVertex->y += fOffsetY;	++pVertex;
		}

		mX = nX;
		mY = nY;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������ɫ
	void TextSurface::SetTextColor( DWORD dwColor )
	{
		//�����������ζ�����ɫ
		wchar_t* pChar = mpText;
		OverlayVertex* pVertex = mpVertexData;

		while( *pChar != 0 )
		{
			++pChar;

			pVertex->color = dwColor;	++pVertex;
			pVertex->color = dwColor;	++pVertex;
			pVertex->color = dwColor;	++pVertex;
			pVertex->color = dwColor;	++pVertex;
			pVertex->color = dwColor;	++pVertex;
			pVertex->color = dwColor;	++pVertex;
		}

		mTextColor = dwColor;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������������
	void FKFastcall TextSurface::_UpdateText()
	{
		//��ȥ�������
		if( mbVisable )
			OverlayManager::mpSingleton->mNumRenderVer -= mNumVertex;

		//��ǰ������ʾ��׼��
		int nPenX = mX;
		int nPenY = mY + mpFont->mFontAscender;

		//�����������ζ�������
		wchar_t* pChar = mpText;
		FontFace::GlyphDraw* pGlyphDraw = mpGlyphDraw;
		OverlayVertex* pVertex = mpVertexData;
		mNumChars = 0;
		mNumVertex = 0;

		while( *pChar != 0 )
		{
			//��ȡ������Ϣ
			FontFace::GlyphInfo* pGlyphInfo = mpFont->PrepareGlyph( *pChar, pGlyphDraw );

			//��������п�����Զ�����
			if( nPenX + pGlyphInfo->nWidth - mX > mLineWidth )
			{
				nPenX = mX;
				nPenY += mpFont->mLineSpace;
			}

			//����������ʾ����
			float fX1 = (float)( nPenX + pGlyphInfo->nLeft );
			float fY1 = (float)( nPenY - pGlyphInfo->nTop );
			float fX2 = fX1 + (float)pGlyphInfo->nWidth;
			float fY2 = fY1 + (float)pGlyphInfo->nHeight;

			nPenX += pGlyphInfo->nHorAdvance;

			//�������ζ�������
			pVertex->x = fX1;	pVertex->y = fY2;	pVertex->z = 1.0f;		//����
			pVertex->color = mTextColor;	++pVertex;

			pVertex->x = fX1;	pVertex->y = fY1;	pVertex->z = 1.0f;		//����
			pVertex->color = mTextColor;	++pVertex;

			pVertex->x = fX2;	pVertex->y = fY2;	pVertex->z = 1.0f;		//����
			pVertex->color = mTextColor;	++pVertex;

			pVertex->x = fX2;	pVertex->y = fY1;	pVertex->z = 1.0f;		//����
			pVertex->color = mTextColor;	++pVertex;

			pVertex->x = fX2;	pVertex->y = fY2;	pVertex->z = 1.0f;		//����
			pVertex->color = mTextColor;	++pVertex;

			pVertex->x = fX1;	pVertex->y = fY1;	pVertex->z = 1.0f;		//����
			pVertex->color = mTextColor;	++pVertex;

			++mNumChars;
			mNumVertex += 6;

			++pGlyphDraw;
			++pChar;
		}

		//�����µĶ������
		if( mbVisable )
			OverlayManager::mpSingleton->mNumRenderVer += mNumVertex;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƽ��ͼ�񶥵�
	void FKFastcall TextSurface::_ProcessVertex()
	{
		//�������ֶ���������������
		FontFace::GlyphDraw* pGlyphDraw = mpGlyphDraw;
		OverlayVertex* pVertex = mpVertexData;

		for( int i=0; i<mNumChars; ++i, ++pGlyphDraw )
		{
			//������������
			UV4* pUV = mpFont->ProcGlyphTex( pGlyphDraw );
			if( pUV != NULL )
			{
				pVertex->u = pUV->u1;	pVertex->v = pUV->v2;	++pVertex;
				pVertex->u = pUV->u1;	pVertex->v = pUV->v1;	++pVertex;
				pVertex->u = pUV->u2;	pVertex->v = pUV->v2;	++pVertex;
				pVertex->u = pUV->u2;	pVertex->v = pUV->v1;	++pVertex;
				pVertex->u = pUV->u2;	pVertex->v = pUV->v2;	++pVertex;
				pVertex->u = pUV->u1;	pVertex->v = pUV->v1;	++pVertex;
			}
		}

		//�������εĻ���˳���������ж�������
		static FontFace::GlyphDraw sTmpGlphyDraw;
		static OverlayVertex pTmpVertex[6];

		for( int i=0; i<mNumChars-1; i++ )
		{
			for( int j=i+1; j<mNumChars; j++ )
			{
				FontFace::GlyphDraw* pGlyphDrawA = mpGlyphDraw + i;
				FontFace::GlyphDraw* pGlyphDrawB = mpGlyphDraw + j;

				if( pGlyphDrawA->nDrawOrder > pGlyphDrawB->nDrawOrder )
				{
					OverlayVertex* pVertexPtrA = mpVertexData + i * 6;
					OverlayVertex* pVertexPtrB = mpVertexData + j * 6;

					memcpy( &sTmpGlphyDraw, pGlyphDrawA, sizeof(FontFace::GlyphDraw) );
					memcpy( pTmpVertex, pVertexPtrA, sizeof(OverlayVertex) * 6 );

					memcpy( pGlyphDrawA, pGlyphDrawB, sizeof(FontFace::GlyphDraw) );
					memcpy( pVertexPtrA, pVertexPtrB, sizeof(OverlayVertex) * 6 );

					memcpy( pGlyphDrawB, &sTmpGlphyDraw, sizeof(FontFace::GlyphDraw) );
					memcpy( pVertexPtrB, pTmpVertex, sizeof(OverlayVertex) * 6 );
				}
			}
		}

		//��ͬһ��Ⱦ˳������η���
		mNumDrawGroup = 0;

		pGlyphDraw = mpGlyphDraw;
		int nLastDrawOrder = pGlyphDraw->nDrawOrder;
		UINT nNumGlyphInGroup = 0;

		for( int i=0; i<mNumChars; ++i, ++pGlyphDraw, ++nNumGlyphInGroup )
		{
			if( pGlyphDraw->nDrawOrder != nLastDrawOrder )
			{
				if( mNumDrawGroup == 8 )
					goto ErrorNumDrawGroup;

				mpDrawGroup[ mNumDrawGroup ] = nNumGlyphInGroup;
				nLastDrawOrder = pGlyphDraw->nDrawOrder;
				nNumGlyphInGroup = 0;
				++mNumDrawGroup;
			}
		}

		mpDrawGroup[ mNumDrawGroup ] = nNumGlyphInGroup;
		++mNumDrawGroup;

		if( mNumDrawGroup == 8 )
			goto ErrorNumDrawGroup;

		return;

ErrorNumDrawGroup:
		Except( Exception::ERR_INTERNAL_ERROR, "����ƽ��������Ⱦ���鳬�������������" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦƽ��ͼ��
	void FKFastcall TextSurface::_RenderOverlay()
	{
		//���������������
		RenderSystem::mpSingleton->_SetTextureFilter( ST_MAGFILTER, mFilterType, 0 );
		RenderSystem::mpSingleton->_SetTextureFilter( ST_MINFILTER, mFilterType, 0 );

		//��������
		RenderSystem::mpSingleton->_SetTexture( mpFont->mpFontTexture, 0 );

		//������������
		UINT nVertexOffset = mVertexOffset;
		FontFace::GlyphDraw* pGlyphDraw = mpGlyphDraw;

		//ѭ����Ⱦ����������Ⱦ����
		for( UINT i=0; i<mNumDrawGroup; ++i )
		{
			UINT nNumGlyphInGroup = mpDrawGroup[i];

			//��������Ⱦ��������������
			for( UINT j=0; j<nNumGlyphInGroup; ++j, ++pGlyphDraw )
			{
				//��������׸������ַ�����ͼ���Ƶ�������
				if( pGlyphDraw->nDrawOrder > 1 )
					mpFont->_CopyGlyphToTex( pGlyphDraw );
			}

			//��Ⱦ�÷�������������
			RenderSystem::mpSingleton->_RenderVertex( PT_TRIANGLE_LIST, nVertexOffset, nNumGlyphInGroup << 1 );
			nVertexOffset += nNumGlyphInGroup * 6;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
