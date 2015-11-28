/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ImageDecoder
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/CommonBase/CommonBaseInsideHead.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	ImageDecoder::ImageDecoder()
		: mFnParseHeader	(NULL)
		, mFnDecode			(NULL)
		, mFnEndDecode		(NULL)
		, mbIsLoadImage		(false)
		, mpImageFile		(NULL)
		, mpImageData		(NULL)
		, mbPreLoadInMem	(false)
		, mWidth			(0)
		, mHeight			(0)
		, mPixelFormat		(PF_UNKNOWN)
		, mpDDSInfo			(NULL)
		, mpExtData			(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	ImageDecoder::~ImageDecoder()
	{
		if( mbIsLoadImage )
			UnloadImage();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ļ�����ͼ��
	void ImageDecoder::LoadImageFromFile( FileObject* pImageFile, const char* szFileName, const bool bPreLoadInMem )
	{
		mpImageFile = pImageFile;
		mbPreLoadInMem = bPreLoadInMem;

		//���ļ�
		pImageFile->Open( szFileName, OT_Read );

		//���ָ��Ԥ�Ƚ�ͼ�����������ڴ�
		if( mbPreLoadInMem )
		{
			DWORD dwFileLen = pImageFile->GetLength();
			mImageData.Allocate( dwFileLen );
			pImageFile->Read( mImageData.GetPointer(), dwFileLen );
			mpImageData = &mImageData;
		}

		//�����ļ���չ���ж��ļ�����
		static char szExtName[32] = { NULL };
		UINT nExtPos = Misc::GetLastCharIndex( (char*)szFileName, '.' ) + 1;
		memcpy( szExtName, szFileName + nExtPos, 32 );
		strlwr( szExtName );

		UINT nExtHash = Misc::HashString( szExtName );

		//������ָ��ָ����Ӧ�Ľ��뺯��
		switch (nExtHash)
		{
			//BMP ͼ��
		case BmpExtNameID:
			{
				mFnParseHeader	= BmpParseHeader;
				mFnEndDecode	= BmpEndDecode;
				mFnDecode		= BmpDecode;
				break;
			}
			//TGA ͼ��
		case TgaExtNameID:
			{
				mFnParseHeader	= TgaParseHeader;
				mFnEndDecode	= TgaEndDecode;
				mFnDecode		= TgaDecode;
				break;
			}
			//JPG ͼ��
		case JpgExtNameID:
			{
				mFnParseHeader	= JpgParseHeader;
				mFnEndDecode	= JpgEndDecode;
				mFnDecode		= JpgDecode;
				break;
			}
			//DDS ͼ��
		case DDSExtNameID:
			{
				mFnParseHeader	= DDSParseHeader;
				mFnEndDecode	= DDSEndDecode;
				mFnDecode		= DDSDecode;
				break;
			}
		default:
			Except( Exception::ERR_INTERNAL_ERROR, (String)"�޷�����ͼ���ļ� '" + szFileName +
				"' ����չ��ʶ��ͼ�����͡�");
		}

		mbIsLoadImage = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ڴ�����ͼ��
	void ImageDecoder::LoadImageFromMem( DataChunk* pImageData, ImageType eType )
	{
		mpImageData = pImageData;
		mbPreLoadInMem = true;

		//�����ļ����ͽ�����ָ��ָ����Ӧ�Ľ��뺯��
		switch (eType)
		{
			//BMP ͼ��
		case eBMP:
			{
				mFnParseHeader	= BmpParseHeader;
				mFnEndDecode	= BmpEndDecode;
				mFnDecode		= BmpDecode;
				break;
			}
			//TGA ͼ��
		case eTGA:
			{
				mFnParseHeader	= TgaParseHeader;
				mFnEndDecode	= TgaEndDecode;
				mFnDecode		= TgaDecode;
				break;
			}
			//JPG ͼ��
		case eJPG:
			{
				mFnParseHeader	= JpgParseHeader;
				mFnEndDecode	= JpgEndDecode;
				mFnDecode		= JpgDecode;
				break;
			}
			//DDS ͼ��
		case eDDS:
			{
				mFnParseHeader	= DDSParseHeader;
				mFnEndDecode	= DDSEndDecode;
				mFnDecode		= DDSDecode;
				break;
			}
		default:
			Except( Exception::ERR_INVALIDPARAMS, "�����ͼ�����͡�");
		}

		mbIsLoadImage = true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ж��ͼ���ļ�
	bool ImageDecoder::UnloadImage()
	{
		bool bResult = true;

		mFnEndDecode( this );

		//�ر��ļ�
		if( mpImageFile != NULL )
			bResult = mpImageFile->Close();

		mFnParseHeader	= NULL;
		mFnDecode		= NULL;
		mpImageFile		= NULL;
		mpImageData		= NULL;
		mbPreLoadInMem	= false;
		mWidth			= 0;
		mHeight			= 0;
		mPixelFormat	= PF_UNKNOWN;

		//���ͼ������
		mImageData.Free();

		mbIsLoadImage = false;

		return bResult;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡͼ����ߡ�
	void ImageDecoder::GetDimension( UINT& nWidth, UINT& nHeight )
	{
		nWidth = mWidth;
		nHeight = mHeight;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡͼ���ʽ
	PixelFormat ImageDecoder::GetFormat()
	{
		return mPixelFormat;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ͼ��ͷ
	void ImageDecoder::ParseHeader()
	{
		mFnParseHeader( this );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ͼ������
	void ImageDecoder::Decode( BYTE* pDstBuf, RECT* srcRect, RECT* dstRect, int pitch, PixelFormat ePixelFormat )
	{
		mFnDecode( this, pDstBuf, srcRect, dstRect, pitch, ePixelFormat );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
