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
	FontFace::FontFace( LPCSTR szFontFile, UINT nSize, UINT nTexSize, UINT nGlyphWidth, UINT nGlyphHeight,
		UINT nFontIndex, FT_Render_Mode eRenderMode )
		: mRenderMode		(eRenderMode)
		, mpFontTexture		(NULL)
		, mFontFace			(NULL)
		, mNumGlyphData		(0)
		, mCurGlyphNum		(0)
		, mOverwritePos		(0)
	{
		//��������С
		if( nSize == 0 )
			Except( Exception::ERR_INVALIDPARAMS, "�������������СΪ�㡣" );

		//��������
		mFontFace = FontManager::mpSingleton->_LoadFontFace( szFontFile, nFontIndex );

		//���������С
		FT_Error error = FT_Set_Pixel_Sizes( mFontFace, 0, nSize );
		if( error != 0 )
			Except( Exception::ERR_INTERNAL_ERROR, "���������Сʧ�ܡ�" );

		//����ô�С���γߴ�
		if( mFontFace->units_per_EM == 0 )
			Except( Exception::ERR_INVALIDPARAMS, "��֧�ֵ������ʽ��" );

		if( nGlyphWidth == 0 )
		{
			float BoxW = (float)( ( mFontFace->bbox.xMax - mFontFace->bbox.xMin ) * nSize ) / (float)mFontFace->units_per_EM;
			mnMaxWidth = CeilToInt( BoxW );
		}
		else
			mnMaxWidth = nGlyphWidth;

		if( nGlyphHeight == 0 )
		{
			float BoxH = (float)( ( mFontFace->bbox.yMax - mFontFace->bbox.yMin ) * nSize ) / (float)mFontFace->units_per_EM;
			mnMaxHeight	= CeilToInt( BoxH );
		}
		else
			mnMaxHeight = nGlyphHeight;

		mFontAscender = CeilToInt( (float)( mFontFace->ascender * nSize ) / (float)mFontFace->units_per_EM );
		mLineSpace = CeilToInt( (float)( mFontFace->height * nSize ) / (float)mFontFace->units_per_EM );

		//�����������
		if( 0 != FT_Select_Charmap( mFontFace, FT_ENCODING_UNICODE ) )
			Except( Exception::ERR_INTERNAL_ERROR, "�����������ʧ�ܡ�" );

		//����������������
		if( (int)nTexSize < mnMaxWidth || (int)nTexSize < mnMaxHeight )
			Except( Exception::ERR_INVALIDPARAMS, "ָ������������ߴ�С�����γߴ硣" );

		mnTexSize = nTexSize;
		mfTexSizeInv = 1.0f / (float)nTexSize;

		mHorGlyphNum = nTexSize / mnMaxWidth;
		mVerGlyphNum = nTexSize / mnMaxHeight;
		mMaxGlyphNum = mHorGlyphNum * mVerGlyphNum;

		//������������ͼ�񻺴�
		int nBufSize = mMaxGlyphNum * ( sizeof(GlyphTex) + sizeof(int) );
		mpGlyphTex = (GlyphTex*)malloc( nBufSize );
		memset( mpGlyphTex, 0, nBufSize );

		mpDrawTime = (int*)( mpGlyphTex + mMaxGlyphNum );

		//��ʼ���������ݻ���
		mGlyphDataLen = mnMaxWidth * mnMaxHeight * sizeof(DWORD) + sizeof(GlyphInfo);
		mGlyphDataStack.Initialize( 256 * mGlyphDataLen, 128 * mGlyphDataLen );

		//������������
		mpFontTexture = TextureManager::mpSingleton->CreateTexture( nTexSize, nTexSize, PF_A8R8G8B8, TU_DYNAMIC, 1 );
		mpFontTexture->FillColor();
	}
	//--------------------------------------------------------------------------------------------------------------
	FontFace::~FontFace()
	{
		//�ͷ�����
		if( mFontFace != NULL )
			FT_Done_Face( mFontFace );

		SafeFree( mpGlyphTex );

		TextureManager::mpSingleton->DeleteTexture( mpFontTexture );
	}
	//--------------------------------------------------------------------------------------------------------------
	//׼��ָ������
	FontFace::GlyphInfo* FKFastcall FontFace::PrepareGlyph( wchar_t wChar, GlyphDraw* pGlyphDraw )
	{
		pGlyphDraw->nUVIndex = -1;

		BYTE* pGlyphData = mGlyphDataStack.Begin();

		//����ָ�������Ƿ��Ѵ���
		for( int i=0; i<mNumGlyphData; ++i, pGlyphData+=mGlyphDataLen )
		{
			GlyphInfo* pGlyphInfo = (GlyphInfo*)pGlyphData;

			//���ָ�������Ѵ����򷵻���
			if( pGlyphInfo->wChar == wChar )
			{
				pGlyphDraw->nGlyphIndex = i;
				return pGlyphInfo;
			}
		}

		//���������δ�����򴴽���
		GlyphInfo* pGlyphInfo = (GlyphInfo*)mGlyphDataStack.Push( mGlyphDataLen );

		pGlyphInfo->wChar = wChar;
		pGlyphDraw->nGlyphIndex = mNumGlyphData;
		pGlyphInfo->nTexIndex = -1;

		++mNumGlyphData;

		DWORD* pImageBuf = (DWORD*)( pGlyphInfo + 1 );

		//���������
		if( 0 != FT_Load_Char( mFontFace, wChar, FT_LOAD_DEFAULT ) )
			Except( Exception::ERR_INTERNAL_ERROR, "ѡ���ַ�����ʧ�ܡ�" );

		FT_GlyphSlot pGlyph = mFontFace->glyph;
		FT_Bitmap* pBitmap = &pGlyph->bitmap;

		//��������β���������Ƕλͼ�������Ⱦ
		if( pGlyph->format != FT_GLYPH_FORMAT_BITMAP )
		{
			if( 0 != FT_Render_Glyph( pGlyph, mRenderMode ) )
				Except( Exception::ERR_INTERNAL_ERROR, "��Ⱦ����λ	ͼʧ�ܡ�" );
		}

		//�洢�����Ű�����
		pGlyphInfo->nLeft		= pGlyph->bitmap_left;
		pGlyphInfo->nTop		= pGlyph->bitmap_top;
		pGlyphInfo->nWidth		= mnMaxWidth;
		pGlyphInfo->nHeight		= mnMaxHeight;
		pGlyphInfo->nHorAdvance	= pGlyph->metrics.horiAdvance >> 6;
		pGlyphInfo->nVerAdvance = pGlyph->metrics.vertAdvance >> 6;

		//��������ͼ�񵽻���
		memset( pImageBuf, 0, sizeof(DWORD) * mnMaxWidth * mnMaxHeight );
		DWORD* pDstBuf = pImageBuf;
		DWORD* pDst = pDstBuf;

		//�������ģʽΪ��ɫ��һλ����һ���أ�
		if( pBitmap->pixel_mode == FT_PIXEL_MODE_MONO )
		{
			BYTE* pSrc = (BYTE*)pBitmap->buffer;
			BYTE* pSrcRow = pSrc;

			for( int y=0; y<pBitmap->rows; ++y )
			{
				BYTE nBitMask = 128;
				for( int x=0; x<pBitmap->width; ++x )
				{
					*pDst = ( *pSrc & nBitMask ) ? 0xFFFFFFFF : 0x0;
					++pDst;

					nBitMask >>= 1;
					if( nBitMask == 0 )
					{
						nBitMask = 128;
						++pSrc;
					}
				}

				pSrcRow += pBitmap->pitch;
				pSrc = pSrcRow;
				pDstBuf += pGlyphInfo->nWidth;
				pDst = pDstBuf;
			}
		}
		//�������ģʽΪ 256 λ�Ҷȣ�һ�ֽڴ���һ���أ�
		else
		{
			BYTE* pSrc = (BYTE*)pBitmap->buffer;
			BYTE* pSrcRow = pSrc;

			for( int y=0; y<pBitmap->rows; ++y )
			{
				for( int x=0; x<pBitmap->width; ++x )
				{
					DWORD dwGray = *pSrc;
					*pDst = dwGray | (dwGray<<8) | (dwGray<<16) | (dwGray<<24);

					++pDst;
					++pSrc;
				}

				pSrcRow += pBitmap->pitch;
				pSrc = pSrcRow;
				pDstBuf += pGlyphInfo->nWidth;
				pDst = pDstBuf;
			}
		}

		//����������Ϣ
		return pGlyphInfo;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������������
	UV4* FKFastcall FontFace::ProcGlyphTex( GlyphDraw* pGlyphDraw )
	{
		//��ȡ������Ϣ
		GlyphInfo* pGlyphInfo = (GlyphInfo*)( mGlyphDataStack.Begin() + pGlyphDraw->nGlyphIndex * mGlyphDataLen );

		GlyphTex* pGlyphTex;
		int nTexIndex = pGlyphInfo->nTexIndex;

		//���ָ����ԭ������������
		if( nTexIndex != -1 )
		{
			pGlyphTex = mpGlyphTex + nTexIndex;

			//���ԭ��λ���ַ����������������������
			if( pGlyphTex->wChar == pGlyphInfo->wChar )
			{
				//��������������ڱ�֡��Ⱦ��δʹ��
				int* pDrawTime = mpDrawTime + nTexIndex;
				if( *pDrawTime == 0 )
					*pDrawTime += 1;

				pGlyphDraw->nDrawOrder = *pDrawTime;

				//����ѽ������� UV ������ֱ�ӷ���
				if( pGlyphDraw->nUVIndex == nTexIndex )
					return NULL;

				//���򷵻�������������
				pGlyphDraw->nUVIndex = nTexIndex;
				return &pGlyphTex->sUV;
			}
		}

		//ָ���µ���������λ��

		//�������λ������
		if( mCurGlyphNum == mMaxGlyphNum )
		{
			nTexIndex = mOverwritePos;
			pGlyphTex = mpGlyphTex + nTexIndex;

			if( mpDrawTime[ nTexIndex ] > 0 )
			{
				++mOverwritePos;

				if( mOverwritePos == mMaxGlyphNum )
					mOverwritePos = 0;
			}
		}
		else
		{
			nTexIndex = mCurGlyphNum;
			pGlyphTex = mpGlyphTex + nTexIndex;

			++mCurGlyphNum;
		}

		pGlyphTex->wChar = pGlyphInfo->wChar;
		pGlyphInfo->nTexIndex = nTexIndex;
		pGlyphDraw->nUVIndex = nTexIndex;

		//���������������ϵ�λ��
		UV4* pUV = &pGlyphTex->sUV;
		pUV->u1 = (float)( ( nTexIndex % mHorGlyphNum ) * mnMaxWidth ) * mfTexSizeInv;
		pUV->v1 = (float)( ( nTexIndex / mHorGlyphNum ) * mnMaxHeight ) * mfTexSizeInv;
		pUV->u2 = pUV->u1 + (float)mnMaxWidth * mfTexSizeInv;
		pUV->v2 = pUV->v1 + (float)mnMaxHeight * mfTexSizeInv;

		//������׸������ַ�����ͼ���Ƶ�������
		int* pDrawTime = mpDrawTime + nTexIndex;
		if( *pDrawTime == 0 )
			_CopyGlyphToTex( pGlyphDraw );

		*pDrawTime += 1;
		pGlyphDraw->nDrawOrder = *pDrawTime;

		//��Ҫ���¶��� UV ����
		return &pGlyphTex->sUV;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ͼ������
	void FKFastcall FontFace::ResetGlyphData()
	{
		memset( mpDrawTime, 0, sizeof(int) * mMaxGlyphNum );

		mOverwritePos = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ַ�ͼ���Ƶ�������
	void FKFastcall FontFace::_CopyGlyphToTex( GlyphDraw* pGlyphDraw )
	{
		GlyphInfo* pGlyphInfo = (GlyphInfo*)( mGlyphDataStack.Begin() + pGlyphDraw->nGlyphIndex * mGlyphDataLen );

		//���û���κ�ͼ����ֱ�ӷ���
		if( pGlyphInfo->nWidth == 0 || pGlyphInfo->nHeight == 0 )
			return;

		DWORD* pImageBuf = (DWORD*)( pGlyphInfo + 1 );
		int nTexIndex = pGlyphDraw->nUVIndex;

		//��������ͼ����λ��
		RECT LockRect;
		LockRect.left = ( nTexIndex % mHorGlyphNum ) * mnMaxWidth;
		LockRect.top = nTexIndex / mHorGlyphNum * mnMaxHeight;
		LockRect.right = LockRect.left + pGlyphInfo->nWidth;
		LockRect.bottom = LockRect.top + pGlyphInfo->nHeight;

		//��������
		BYTE* pTexBuf;
		UINT nTexPitch;
		int nCopyLen = pGlyphInfo->nWidth * sizeof(DWORD);
		mpFontTexture->LockRect( (void**)&pTexBuf, &nTexPitch, &LockRect );

		for( int y=0; y<pGlyphInfo->nHeight; ++y )
		{
			memcpy( pTexBuf, pImageBuf, nCopyLen );
			pTexBuf += nTexPitch;
			pImageBuf += pGlyphInfo->nWidth;
		}

		//��������
		mpFontTexture->UnlockRect();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
