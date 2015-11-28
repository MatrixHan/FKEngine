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
*	�ļ�˵����	ͼ�������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	class FileObject;
	class ImageDecoder;
	struct DDSDecodeInfo;

	//����ͼ��ͷ����
	typedef void ( *FnImageParseHeader )( ImageDecoder* pThis );

	//���ͼ����뺯��
	typedef void ( *FnImageEndDecode )( ImageDecoder* pThis );

	//����ͼ�����ݺ���
	typedef void ( *FnImageDecode )( ImageDecoder* pThis, BYTE* pDstBuf, RECT* srcRect, RECT* dstRect,
		int pitch, PixelFormat ePixelFormat );

	//--------------------------------------------------------------------------------------------------------------
	//ͼ�������
	class FK_DLL ImageDecoder
	{
	public:
		FnImageParseHeader		mFnParseHeader;	//����ͼ��ͷ����
		FnImageEndDecode		mFnEndDecode;	//���ͼ����뺯��
		FnImageDecode			mFnDecode;		//����ͼ�����ݺ���

		FileObject*				mpImageFile;	//ͼ���ļ�
		DataChunk				mImageData;		//������ͼ�����ݻ���
		DataChunk*				mpImageData;	//ͼ������ȡ���ݻ���

		bool					mbIsLoadImage;	//�Ƿ������ͼ��
		bool					mbPreLoadInMem;	//�Ƿ�Ԥ�Ƚ��ļ������ڴ�

		UINT					mWidth;			//ͼ���
		UINT					mHeight;		//ͼ���
		PixelFormat				mPixelFormat;	//ͼ���ʽ

		DDSDecodeInfo*			mpDDSInfo;		// DDS ������Ϣ����
		void*					mpExtData;		//�����������ָ��

	public:
		ImageDecoder();
		~ImageDecoder();

		//���ļ�����ͼ��
		void LoadImageFromFile( FileObject* pImageFile, const char* szFileName, const bool bPreLoadInMem = true );

		//���ڴ�����ͼ��
		void LoadImageFromMem( DataChunk* pImageData, ImageType eType );

		//ж��ͼ��
		bool UnloadImage();

		//��ȡͼ����ߡ�
		void GetDimension( UINT& nWidth, UINT& nHeight );

		//��ȡͼ���ʽ
		PixelFormat GetFormat();

		//����ͼ��ͷ
		void ParseHeader();

		//����ͼ������
		void Decode( BYTE* pDstBuf, RECT* srcRect, RECT* dstRect, int pitch, PixelFormat ePixelFormat );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
