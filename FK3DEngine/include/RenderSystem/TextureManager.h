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

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//���������
	class FK_DLL TextureManager : public Singleton< TextureManager >
	{
	public:
		UINT				mMaxWidth;				//��ά���������
		UINT				mMaxHeight;				//��ά�������߶�
		UINT				mHardMaxWidth;			//Ӳ��֧�ֶ�ά���������
		UINT				mHardMaxHeight;			//Ӳ��֧�ֶ�ά�������߶�

		UINT				mMaxVolumeExtent;		//��ά�������ߴ�
		UINT				mHardMaxVolumeExtent;	//Ӳ��֧����ά�������ߴ�

		BaseTextureList		mTextureList;			//�����б�
		UINT				mNumTextures;			//��������
		int					mDefTexLevels;			//Ĭ��������������

		bool				mbCanNotSquare;			//�Ƿ�����ʹ�÷Ǳ߳��������
		bool				mbHardCanNotSquare;		//Ӳ���Ƿ�֧�ַǱ߳��������

		bool				mbCanNotPow2;			//�Ƿ�����ʹ�÷� 2 �� n ���ݳߴ��ά����
		bool				mbHardCanNotPow2;		//Ӳ���Ƿ�֧�ַ� 2 �� n ���ݳߴ��ά����

		bool				mbCanNotPow2Cube;		//�Ƿ�����ʹ�÷� 2 �� n ���ݳߴ���������
		bool				mbHardCanNotPow2Cube;	//Ӳ���Ƿ�֧�ַ� 2 �� n ���ݳߴ���������

		bool				mbCanNotPow2Volume;		//�Ƿ�����ʹ�÷� 2 �� n ���ݳߴ���ά����
		bool				mbHardCanNotPow2Volume;	//Ӳ���Ƿ�֧�ַ� 2 �� n ���ݳߴ���ά����

	protected:
		FileObject*			mpTexPackFile;			//�������ļ�ָ��
		ImageDecoder		mImgDecoder;			//����ͼ�������

		bool				mbTexCompFormats[5];	//��������ѹ����ʽ��DXT1-DXT5��

	public:
		TextureManager();
		virtual ~TextureManager();

		//�����������ļ�
		void SetTexturePack( FileObject* pFile );

		//ǿ��ʹ�ñ߳��������
		void ForceSquare( bool bForceUse = true );

		//ǿ��ʹ��Ϊ 2 �� n ���ݳߴ�Ķ�ά����
		void ForcePow2( bool bForceUse = true );

		//ǿ��ʹ��Ϊ 2 �� n ���ݳߴ����������
		void ForcePow2Cube( bool bForceUse = true );

		//ǿ��ʹ��Ϊ 2 �� n ���ݳߴ����ά����
		void ForcePow2Volume( bool bForceUse = true );

		//������ά����
		virtual Texture* CreateTexture( UINT nWidth, UINT nHeight, PixelFormat ePixelFormat,
			TextureUsage Type = TU_NORMAL, int nNumLevels = -1 ) = 0;

		//������������
		virtual CubeTexture* CreateCubeTexture( UINT nEdgeLength, PixelFormat ePixelFormat,
			TextureUsage Type = TU_NORMAL, int nNumLevels = -1 ) = 0;

		//������ά����
		virtual VolumeTexture* CreateVolumeTexture( UINT nWidth, UINT nHeight, UINT nDepth,
			PixelFormat ePixelFormat, TextureUsage Type = TU_NORMAL, int nNumLevels = -1 ) = 0;

		//ɾ������
		void DeleteTexture( Texture* pTexture );

		//ɾ����������
		void DeleteAllTextures();

		//��ȡ��ǰ����������
		FKInline UINT GetNumTextures();

		//��ȡ��Ѷ�ά�������ߴ�
		void GetBestSize( UINT inWidth, UINT inHeight, UINT& outWidth, UINT& outHeight );

		//��ȡ��������������ߴ�
		UINT GetBestSizeCube( UINT inEdgeLength );

		//��ȡ�����ά�������ߴ�
		void GetBestSizeVolume( UINT inWidth, UINT inHeight, UINT inDepth,
			UINT& outWidth, UINT& outHeight, UINT& outDepth );

		//��ȡӲ�����֧������ߴ�
		void GetHardMaxTexSize( UINT& nMaxWidth, UINT& nMaxHeight );
		UINT GetHardMaxTexSize();

		//��������ߴ������ֵ
		virtual void SetMaxTextureSize( UINT nWidth, UINT nHeight ) = 0;

		//����Ĭ��������������
		void SetDefTextureLevels( int nNumLevels = 0 );

		//��ȡĬ��������������
		int GetDefTextureLevels();

		//���ļ�����һ������
		Texture* LoadFromFile( const char* szFileName, int nNumLevels = 1, PixelFormat ePixelFormat = PF_A8R8G8B8 );

		//���ڴ��м���һ������
		Texture* LoadFromMem( BYTE* pMemPtr, int nNumLevels = 1, PixelFormat ePixelFormat = PF_A8R8G8B8 );

		//���ָ��ѹ����ʽ�����Ƿ����
		bool CheckCompressFormat( const PixelFormat ePixelFormat );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
