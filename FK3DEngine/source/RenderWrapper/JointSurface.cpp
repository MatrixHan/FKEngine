/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	JointSurface
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
	JointSurface::JointSurface( ZOrderType eZType, OverlaySurface* pZRefOverlay, TextureFilterType eFilterType )
		: OverlaySurface	( eZType, pZRefOverlay, eFilterType )
		, mfWidth			(0.0f)
		, mfHeight			(0.0f)
		, mPicWidth			(0)
		, mPicHeight		(0)
		, mNumTextures		(0)
		, mNumCols			(0)
		, mNumRows			(0)
		, mPerWidth			(0)
		, mPerHeight		(0)
		, mRemWidth			(0)
		, mRemHeight		(0)
		, mActWidth			(0)
		, mActHeight		(0)
		, mpVertexData		(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	JointSurface::~JointSurface()
	{
		//�ͷŶ�������
		SafeFree( mpVertexData );

		//ɾ����ƴ��ͼ����ʹ��������б�
		mNumTextures = 0;

		TextureList::Iterator it = mTextureList.Begin();
		TextureList::Iterator end = mTextureList.End();
		for(; it!=end; ++it )
			TextureManager::mpSingleton->DeleteTexture( *it );

		mTextureList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƴ��ͼ��
	void JointSurface::CreateJointSurface( float fLeft, float fTop, float fWidth, float fHeight,
		UINT nTexWidth, UINT nTexHeight, PixelFormat ePixelFormat, bool bDynamic, DWORD color )
	{
		//�洢��Ⱦ�ߴ�
		mfWidth = fWidth;
		mfHeight = fHeight;

		//�洢����ߴ�
		mPicWidth = nTexWidth;
		mPicHeight = nTexHeight;

		//��ȡ�������ߴ�
		mPerWidth = TextureManager::mpSingleton->mMaxWidth;
		mPerHeight = TextureManager::mpSingleton->mMaxHeight;

		//�����Ƿ���Ҫ��̬��������
		TextureUsage TexUsage;
		TexUsage = bDynamic ? TU_DYNAMIC : TU_NORMAL;

		//������Ҫ��������������ߴ�
		Div( mPicWidth, mPerWidth, mNumCols, mRemWidth );

		//�������һ��������
		if( mRemWidth == 0 )
			mRemWidth = mPerWidth;
		else
			++mNumCols;

		Div( mPicHeight, mPerHeight, mNumRows, mRemHeight );

		//�������һ������߶�
		if( mRemHeight == 0 )
			mRemHeight = mPerHeight;
		else
			++mNumRows;

		mNumTextures = mNumCols * mNumRows;

		//������һ�������ʵ�ʿ�Ⱥ͸߶�
		TextureManager::mpSingleton->GetBestSize( mRemWidth, mRemHeight, mActWidth, mActHeight );

		//���䶥�������ڴ�
		mNumVertex = mNumTextures * 4;
		mpVertexData = (OverlayVertex*)malloc( sizeof(OverlayVertex)*mNumVertex );
		OverlayVertex* pVer = mpVertexData;

		//��ʼ�������б�ռ�
		mTextureList.Initialize( mNumRows * mNumCols, 2 );

		//�����������㶥������
		Texture* pTex = NULL;

		UINT nCurTexWidth, nCurTexHeight;
		float u2, v2;

		float fWidthScal = 1.0f / (float)mPicWidth * fWidth;
		float fHeightScal = 1.0f / (float)mPicHeight * fHeight;

		float fPosTop		= 0.0f;
		float fPosBottom	= 0.0f;
		float fPosLeft		= 0.0f;
		float fPosRight		= 0.0f;

		//��ѭ��
		for( UINT r=0; r<mNumRows; ++r )
		{
			//�������꼰 UV
			if( r == mNumRows - 1 )
			{
				v2 = mRemHeight / mActHeight;
				nCurTexHeight = mRemHeight;
			}
			else
			{
				v2 = 1.0;
				nCurTexHeight = mPerHeight;
			}
			float fPosHeight = nCurTexHeight * fHeightScal;
			fPosBottom += fPosHeight;

			//��ѭ��
			for( UINT c=0; c<mNumCols; ++c )
			{
				//�������꼰 UV
				if( c == mNumCols - 1 )
				{
					u2 = mRemWidth / mActWidth;
					nCurTexWidth = mRemWidth;
				}
				else
				{
					u2 = 1.0;
					nCurTexWidth = mPerWidth;
				}
				float fPosWidth = nCurTexWidth * fWidthScal;
				fPosRight += fPosWidth;

				//��������
				pTex = TextureManager::mpSingleton->CreateTexture(
					nCurTexWidth, nCurTexHeight, ePixelFormat, TexUsage, 1 );
				*mTextureList.Push() = pTex;

				//���㶥������

				//����
				pVer->x = fPosLeft + fLeft;		pVer->y = fPosBottom + fTop;	pVer->z = 1.0f;
				pVer->u = 0.0;	pVer->v = v2;	pVer->color = color;			++pVer;

				//����
				pVer->x = fPosLeft + fLeft;		pVer->y = fPosTop + fTop;		pVer->z = 1.0f;
				pVer->u = 0.0;	pVer->v = 0.0;	pVer->color = color;			++pVer;

				//����
				pVer->x = fPosRight + fLeft;	pVer->y = fPosTop + fTop;		pVer->z = 1.0f;
				pVer->u = u2;	pVer->v = 0.0;	pVer->color = color;			++pVer;

				//����
				pVer->x = fPosRight + fLeft;	pVer->y = fPosBottom + fTop;	pVer->z = 1.0f;
				pVer->u = u2;	pVer->v = v2;	pVer->color = color;			++pVer;

				fPosLeft += fPosWidth;
			}

			fPosLeft = fPosRight = 0;
			fPosTop += fPosHeight;
		}

		//���Ӷ������
		OverlayManager::mpSingleton->mNumRenderVer += mNumVertex;

		mpVertexPtr = mpVertexData;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ͼ���ļ�������ƴ��ͼ������ߴ�ΪͼƬ�ߴ磩
	void JointSurface::LoadJointSurfaceFromFile( float fLeft, float fTop, float fWidth, float fHeight, FileObject* pFile,
		const char* szName, PixelFormat ePixelFormat, bool bDynamic, DWORD color )
	{
		//�洢��Ⱦ�ߴ�
		mfWidth = fWidth;
		mfHeight = fHeight;

		//��ȡͼ�������
		ImageDecoder* pImgDecoder = &OverlayManager::mpSingleton->mImgDecoder;

		//����ͼƬ
		pImgDecoder->LoadImageFromFile( pFile, szName );

		//����ͼ��ͷ
		pImgDecoder->ParseHeader();

		//��ȡͼ��ߴ�
		pImgDecoder->GetDimension( mPicWidth, mPicHeight );

		//��ȡ�������ߴ�
		mPerWidth = TextureManager::mpSingleton->mMaxWidth;
		mPerHeight = TextureManager::mpSingleton->mMaxHeight;

		//�����Ƿ���Ҫ��̬��������
		TextureUsage TexUsage;
		TexUsage = bDynamic ? TU_DYNAMIC : TU_NORMAL;

		//������Ҫ��������������ߴ�
		Div( mPicWidth, mPerWidth, mNumCols, mRemWidth );

		//�������һ��������
		if( mRemWidth == 0 )
			mRemWidth = mPerWidth;
		else
			++mNumCols;

		Div( mPicHeight, mPerHeight, mNumRows, mRemHeight );

		//�������һ������߶�
		if( mRemHeight == 0 )
			mRemHeight = mPerHeight;
		else
			++mNumRows;

		mNumTextures = mNumCols * mNumRows;

		//������һ�������ʵ�ʿ�Ⱥ͸߶�
		TextureManager::mpSingleton->GetBestSize( mRemWidth, mRemHeight, mActWidth, mActHeight );

		//���䶥�������ڴ�
		mNumVertex = mNumTextures * 4;
		mpVertexData = (OverlayVertex*)malloc( sizeof(OverlayVertex)* mNumVertex );
		OverlayVertex* pVer = mpVertexData;

		//��ʼ�������б�ռ�
		mTextureList.Initialize( mNumRows * mNumCols, 2 );

		//�����������㶥������
		Texture* pTex = NULL;
		BYTE* pDst = NULL;
		UINT pitch = 0;

		UINT nTexWidth, nTexHeight;
		float u2, v2;

		float fWidthScal = 1.0f / (float)mPicWidth * fWidth;
		float fHeightScal = 1.0f / (float)mPicHeight * fHeight;

		float fPosTop		= 0.0f;
		float fPosBottom	= 0.0f;
		float fPosLeft		= 0.0f;
		float fPosRight		= 0.0f;

		RECT FillRect = { 0, 0, 0, 0 };

		//��ѭ��
		for( UINT r=0; r<mNumRows; ++r )
		{
			//�������꼰 UV
			if( r == mNumRows - 1 )
			{
				v2 = mRemHeight / mActHeight;
				nTexHeight = mRemHeight;
			}
			else
			{
				v2 = 1.0;
				nTexHeight = mPerHeight;
			}
			float fPosHeight = nTexHeight * fHeightScal;
			fPosBottom += fPosHeight;
			FillRect.bottom += nTexHeight;

			//��ѭ��
			for( UINT c=0; c<mNumCols; ++c )
			{
				//�������꼰 UV
				if( c == mNumCols - 1 )
				{
					u2 = mRemWidth / mActWidth;
					nTexWidth = mRemWidth;
				}
				else
				{
					u2 = 1.0;
					nTexWidth = mPerWidth;
				}
				float fPosWidth = nTexWidth * fWidthScal;
				fPosRight += fPosWidth;
				FillRect.right += nTexWidth;

				//��������
				pTex = TextureManager::mpSingleton->CreateTexture( nTexWidth, nTexHeight, ePixelFormat, TexUsage, 1 );
				*mTextureList.Push() = pTex;

				//��ͼ��������䵽������
				pTex->LockRect( (void**)&pDst, &pitch );
				pImgDecoder->Decode( pDst, &FillRect, NULL, pitch, ePixelFormat );
				pTex->UnlockRect();

				//���㶥������

				//����
				pVer->x = fPosLeft + fLeft;		pVer->y = fPosBottom + fTop;	pVer->z = 1.0f;
				pVer->u = 0.0;	pVer->v = v2;	pVer->color = color;			++pVer;

				//����
				pVer->x = fPosLeft + fLeft;		pVer->y = fPosTop + fTop;		pVer->z = 1.0f;
				pVer->u = 0.0;	pVer->v = 0.0;	pVer->color = color;			++pVer;

				//����
				pVer->x = fPosRight + fLeft;	pVer->y = fPosTop + fTop;		pVer->z = 1.0f;
				pVer->u = u2;	pVer->v = 0.0;	pVer->color = color;			++pVer;

				//����
				pVer->x = fPosRight + fLeft;	pVer->y = fPosBottom + fTop;	pVer->z = 1.0f;
				pVer->u = u2;	pVer->v = v2;	pVer->color = color;			++pVer;

				fPosLeft += fPosWidth;
				FillRect.left += nTexWidth;
			}

			fPosLeft = fPosRight = 0;
			fPosTop += fPosHeight;

			FillRect.left = FillRect.right = 0;
			FillRect.top += nTexHeight;
		}

		//�ر�ͼƬ������
		if( !pImgDecoder->UnloadImage() )
			Except( Exception::ERR_INTERNAL_ERROR, "�ر�ƴ��ͼ���ͼ���������������ʧ�ܡ�" );

		//���Ӷ������
		OverlayManager::mpSingleton->mNumRenderVer += mNumVertex;

		mpVertexPtr = mpVertexData;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƴ��ͼ��λ��
	void FKFastcall JointSurface::SetLocation( float fLeft, float fTop )
	{
		OverlayVertex* pVer = mpVertexData;

		//�޸Ķ�������
		float fWidthScal = 1.0f / (float)mPicWidth * mfWidth;
		float fHeightScal = 1.0f / (float)mPicHeight * mfHeight;

		float fPosTop		= fTop;
		float fPosBottom	= fTop;
		float fPosLeft		= fLeft;
		float fPosRight		= fLeft;

		//��ѭ��
		for( UINT r=0; r<mNumRows; ++r )
		{
			//��������
			float fHeight = ( ( r == mNumRows - 1 ) ? mRemHeight : mPerHeight ) * fHeightScal;
			fPosBottom += fHeight;

			//��ѭ��
			for( UINT c=0; c<mNumCols; ++c )
			{
				//��������
				float fWidth = ( ( c == mNumCols - 1 ) ? mRemWidth : mPerWidth ) * fWidthScal;
				fPosRight += fWidth;

				//���㶥������
				pVer->x = fPosLeft;		pVer->y = fPosBottom;	++pVer;	//����
				pVer->x = fPosLeft;		pVer->y = fPosTop;		++pVer;	//����
				pVer->x = fPosRight;	pVer->y = fPosTop;		++pVer;	//����
				pVer->x = fPosRight;	pVer->y = fPosBottom;	++pVer;	//����

				fPosLeft += fWidth;
			}

			fPosLeft = fPosRight = fLeft;
			fPosTop += fHeight;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƴ��ͼ����ɫ
	void FKFastcall JointSurface::SetColor( DWORD color )
	{
		OverlayVertex* pVer = mpVertexData;

		//��ѭ��
		for( UINT r=0; r<mNumRows; ++r )
		{
			//��ѭ��
			for( UINT c=0; c<mNumCols; ++c )
			{
				//���㶥������
				pVer->color = color;	++pVer;	//����
				pVer->color = color;	++pVer;	//����
				pVer->color = color;	++pVer;	//����
				pVer->color = color;	++pVer;	//����
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ƴ��ͼ��������
	Texture* JointSurface::GetTexture( UINT nNumTexture )
	{
#ifdef _DEBUG
		if( nNumTexture >= (UINT)mTextureList.Size() )
			return NULL;
#endif
		return mTextureList[nNumTexture];
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƽ��ͼ�񶥵�
	void FKFastcall JointSurface::_ProcessVertex()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦƽ��ͼ��
	void FKFastcall JointSurface::_RenderOverlay()
	{
		//���������������
		RenderSystem::mpSingleton->_SetTextureFilter( ST_MAGFILTER, mFilterType, 0 );
		RenderSystem::mpSingleton->_SetTextureFilter( ST_MINFILTER, mFilterType, 0 );

		//ѭ����Ⱦÿ������
		TextureList::Iterator TexIterator = mTextureList.Begin();
		UINT nOffset = mVertexOffset;

		for( UINT i=0; i<mNumTextures; ++i, ++TexIterator, nOffset += 4 )
		{
			//��������
			RenderSystem::mpSingleton->_SetTexture( *TexIterator, 0 );

			//����ͼԪ
			RenderSystem::mpSingleton->_RenderVertex( PT_TRIANGLE_FAN, nOffset, 2 );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
