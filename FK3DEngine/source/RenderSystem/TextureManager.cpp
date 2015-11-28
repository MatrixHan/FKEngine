/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	TextureManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderSystem/RenderSystemInsideHeader.h"

//==================================================================================================================


namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	TextureManager::TextureManager()
		: mpTexPackFile				(NULL)
		, mNumTextures				(0)
		, mDefTexLevels				(1)
		, mbCanNotSquare			(false)
		, mbHardCanNotSquare		(false)
		, mbCanNotPow2				(false)
		, mbHardCanNotPow2			(false)
		, mbCanNotPow2Cube			(false)
		, mbHardCanNotPow2Cube		(false)
		, mbCanNotPow2Volume		(false)
		, mbHardCanNotPow2Volume	(false)
	{
		mTextureList.Initialize( 200, 100 );
	}
	//--------------------------------------------------------------------------------------------------------------
	TextureManager::~TextureManager()
	{
		//ɾ����������
		DeleteAllTextures();

		mTextureList.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����������ļ�
	void TextureManager::SetTexturePack( FileObject* pFile )
	{
		mpTexPackFile = pFile;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ǿ��ʹ�ñ߳��������
	void TextureManager::ForceSquare( bool bForceUse )
	{
		mbCanNotSquare = bForceUse ? false : mbHardCanNotSquare;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ǿ��ʹ��Ϊ 2 �� n ���ݳߴ�Ķ�ά����
	void  TextureManager::ForcePow2( bool bForceUse )
	{
		mbCanNotPow2 = bForceUse ? false : mbHardCanNotPow2;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ǿ��ʹ��Ϊ 2 �� n ���ݳߴ����������
	void TextureManager::ForcePow2Cube( bool bForceUse )
	{
		mbCanNotPow2Cube = bForceUse ? false : mbHardCanNotPow2Cube;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ǿ��ʹ��Ϊ 2 �� n ���ݳߴ����ά����
	void TextureManager::ForcePow2Volume( bool bForceUse )
	{
		mbCanNotPow2Volume = bForceUse ? false : mbHardCanNotPow2Volume;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ������
	void TextureManager::DeleteTexture( Texture* pTexture )
	{
		if( pTexture == NULL )
			return;

		BaseTextureList::Iterator it = mTextureList.Begin();
		BaseTextureList::Iterator end = mTextureList.End();
		for(; it!=end; ++it )
		{
			if( *it == pTexture )
			{
				mTextureList.Erase( it );
				delete pTexture;
				--mNumTextures;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ����������
	void TextureManager::DeleteAllTextures()
	{
		BaseTextureList::Iterator it = mTextureList.Begin();
		BaseTextureList::Iterator end = mTextureList.End();
		for(; it!=end; ++it )
		{
			if( *it != NULL )
				delete *it;
		}

		mNumTextures = 0;
		mTextureList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ǰ����������
	FKInline UINT TextureManager::GetNumTextures()
	{
		return mNumTextures;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��Ѷ�ά�������ߴ�
	void TextureManager::GetBestSize( UINT inWidth, UINT inHeight, UINT& outWidth, UINT& outHeight )
	{
		//���ͼ��ߴ�����������ߴ�
		if( inWidth > mMaxWidth || inHeight > mMaxHeight )
			Except( Exception::ERR_INVALIDPARAMS, "ָ��������ߴ糬���˵�ǰ���õ��������ߴ硣" );

		//��������ʵ��������ߴ�
		if( mbCanNotPow2 )
		{
			outWidth = inWidth;
			outHeight = inHeight;
		}
		else
		{
			outWidth = CeilToPow2( inWidth );
			outHeight = CeilToPow2( inHeight );
		}

		if( !mbCanNotSquare )
			outWidth = outHeight = max( outWidth, outHeight );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��������������ߴ�
	UINT TextureManager::GetBestSizeCube( UINT inEdgeLength )
	{
		return mbCanNotPow2Cube ? inEdgeLength : CeilToPow2( inEdgeLength );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�����ά�������ߴ�
	void TextureManager::GetBestSizeVolume( UINT inWidth, UINT inHeight, UINT inDepth,
		UINT& outWidth, UINT& outHeight, UINT& outDepth )
	{
		//���ͼ��ߴ�����������ߴ�
		if( inWidth > mMaxVolumeExtent || inHeight > mMaxVolumeExtent || inDepth > mMaxVolumeExtent )
			Except( Exception::ERR_INVALIDPARAMS, "ָ��������ߴ糬���˵�ǰ���õ��������ߴ硣" );

		//��������ʵ��������ߴ�
		if( mbCanNotPow2Volume )
		{
			outWidth = inWidth;
			outHeight = inHeight;
			outDepth = inDepth;
		}
		else
		{
			outWidth = CeilToPow2( inWidth );
			outHeight = CeilToPow2( inHeight );
			outDepth = CeilToPow2( inDepth );
		}

		if( !mbCanNotSquare )
			outWidth = outHeight = outDepth = max( max( outWidth, outHeight ), outDepth );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡӲ�����֧������ߴ�
	void TextureManager::GetHardMaxTexSize( UINT& nMaxWidth, UINT& nMaxHeight )
	{
		nMaxWidth = mHardMaxWidth;
		nMaxHeight = mHardMaxHeight;
	}
	//--------------------------------------------------------------------------------------------------------------
	UINT TextureManager::GetHardMaxTexSize()
	{
		return mHardMaxVolumeExtent;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����Ĭ��������������
	void TextureManager::SetDefTextureLevels( int nNumLevels )
	{
		mDefTexLevels = 1;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡĬ��������������
	int TextureManager::GetDefTextureLevels()
	{
		return mDefTexLevels;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ļ�����һ������
	Texture* TextureManager::LoadFromFile( const char* szFileName, int nNumLevels, PixelFormat ePixelFormat )
	{
		//����ͼƬ
		mImgDecoder.LoadImageFromFile( mpTexPackFile, szFileName );

		//����ͼ��ͷ
		mImgDecoder.ParseHeader();

		//���Ϊ����ѹ��ͼ���ʽ
		if( mImgDecoder.mPixelFormat & PF_COMPRESS_MASK )
		{
			ePixelFormat = mImgDecoder.mPixelFormat;

			//���ļ�����༶ӳ������
			if( nNumLevels != 1 )
			{
				if( mImgDecoder.mpDDSInfo->dwLevelCount == 1 )
					Except( Exception::ERR_INTERNAL_ERROR, (String)"DDS �ļ� " + szFileName + " û�а����༶�������ݣ�"
					"����޷�������Ӧ�Ķ༶ӳ������" );

				nNumLevels = mImgDecoder.mpDDSInfo->dwLevelCount;
			}
		}

		//��ȡͼ��ߴ�
		UINT nWidth = 0;
		UINT nHeight = 0;
		mImgDecoder.GetDimension( nWidth, nHeight );

		//��������
		Texture* pTexture = CreateTexture( nWidth, nHeight, ePixelFormat, TU_NORMAL, nNumLevels );

		//����ÿһ����������
		BYTE* pDst = NULL;
		UINT Pitch = 0;

		int nNumFillLevel = ( nNumLevels == 0 ) ? 1 : nNumLevels;

		for( int i=0; i<nNumFillLevel; ++i )
		{
			//�趨��������
			if( mImgDecoder.mpDDSInfo != NULL )
				mImgDecoder.mpDDSInfo->dwDecodeLevel = i;

			//��������
			pTexture->LockRect( (void**)&pDst, &Pitch, NULL, i );

			//���ͼ������
			mImgDecoder.Decode( pDst, NULL, NULL, Pitch, ePixelFormat );

			//��������
			pTexture->UnlockRect( i );
		}

		//ж��ͼƬ
		if( !mImgDecoder.UnloadImage() )
			Except( Exception::ERR_INTERNAL_ERROR, "�ر�����ͼ�����ݽ�����ʧ�ܡ�" );

		//�Զ����ɶ༶����ӳ��
		if( nNumLevels == 0 )
		{
			if( !IsPow2( nWidth ) || !IsPow2( nHeight ) )
				Except( Exception::ERR_INTERNAL_ERROR, (String)"��Ϊ���� " + szFileName + " �ĳߴ�Ϊ�� 2 ������ֵ��"
				"����޷��Զ��������Ķ༶����ӳ�䡣" );

			pTexture->GenerateMipSubLevels();
		}

		return pTexture;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ڴ��м���һ������
	Texture* TextureManager::LoadFromMem( BYTE* pMemPtr, int nNumLevels, PixelFormat ePixelFormat )
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ָ��ѹ����ʽ�����Ƿ����
	bool TextureManager::CheckCompressFormat( const PixelFormat ePixelFormat )
	{
		//���Ϊѹ�������ʽ
		if( ePixelFormat & PF_COMPRESS_MASK )
		{
			//���ָ������ѹ����ʽ�Ƿ����
			DWORD dwFmtIndex = (DWORD)ePixelFormat - PF_COMPRESS_MASK - 1;
			return mbTexCompFormats[ dwFmtIndex ];
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
