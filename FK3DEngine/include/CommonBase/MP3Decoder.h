/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	MP3Decoder
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	MPEG ������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	#pragma pack ( push )
	#pragma pack ( 1 )

	// ID3v1 ��Ϣ�ṹ
	struct ID3v1Data
	{
		char	szTAG[3];		// "TAG" ��־
		char	szTitle[30];	//��������
		char	szArtist[30];	//����������
		char	szAlbum[30];	//ר������
		char	szYear[4];		//�������
		char	szComment[30];	//ע���ַ���
		BYTE	bGenre;			//��������
	};

	// ID3v2 ��Ϣͷ�ṹ
	struct ID3v2Header
	{
		char	szID3[3];		// "ID3" ��־
		BYTE	bMajorVer;		//���汾��
		BYTE	bSubVer;		//�ΰ汾��
		BYTE	bFlag;			//ѡ���־
		BYTE	szSize[4];		// ID3v2 �м����ݳ��ȣ�ȥ����ͷ��ע���ȣ���ȫͬ������ֵ��
	};

	#pragma pack ( pop )

	//--------------------------------------------------------------------------------------------------------------
	// MPEG ������
	class FK_DLL MP3Decoder : public SoundDecoder
	{
	public:
		//�ļ������С 256 KB
		static const DWORD	mdwFileCacheLen = 0x40000;

	public:
		ID3v1Data		mID3v1Data;			// ID3v1 ����

		DWORD			mdwID3v1Len;		// ID3v1 ���ݳ���
		DWORD			mdwID3v2Len;		// ID3v2 ���ݳ���

		DWORD			mdwFramePCMSize;	//֡��ѹ���ݳ���
		DWORD			mdwNumFrames;		//֡����
		DWORD			mdwPlayTime;		//�ܲ���ʱ�䣨�룩

		MPEGFrameInfo	mFrameInfo;			// MPEG ֡��Ϣ

	protected:
		DWORD			mdwPrefectchLen;	//����Ԥ���ļ����ݳ���
		DWORD			mdwReadDataLen;		//��Ԥ���ļ����ݳ���

		OVERLAPPED		mOverlapped;		//�ļ��첽��ȡ�ṹ
		DWORD			mSoundDataEnd;		//�ļ��������ݽ�βλ��

		char*			mpFramePCMBuffer;	//֡�����������ݻ���
		DWORD			mdwFramePCMLen;		//֡�ѽ����������ݳ���

		char*			mpFileReadPtr;		//�ļ����ݶ�ȡ����
		char*			mpFileWorkPtr;		//�ļ����ݽ��뻺��

		DWORD			mdwFrameOffset;		//����֡�������ļ������е�ƫ����

	public:
		MP3Decoder();
		~MP3Decoder();

		//�������ļ�
		SoundFormat* OpenSoundFile( FileObject* pFile, LPCSTR szFileName );

		//�ر������ļ�
		void CloseSoundFile();

		//����������ȡλ�õ����
		void ResetReadPos();

		//��ȡ�������ݵ�ָ������
		void ReadSoundData( void* pBuf, DWORD dwLen );

	protected:
		//�����ļ�����֡
		void _CheckAllFrames();

		//����֡��Ϣͷ
		bool _DecodeFrameHeader( BYTE szFrameHeader[4], MPEGFrameInfo* pFrameInfo );

		//��ʼԤ���ļ�����
		void FKFastcall _BeginPrefectch();

		//����Ԥ���ļ�����
		void FKFastcall _EndPrefectch();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
