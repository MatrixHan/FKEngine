/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	WaveDecoder
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	Wave �ļ�������
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

	// WAV �ļ�ͷ
	struct WaveHeader
	{
		char	szRIFF[4];		// "RIFF" ��־
		LONG	dwFileLen;		//�ļ�����
		char	szWAVE[4];		// "WAVE" ��־
		char	szFMT[4];		// "fmt " ��־��ע����ַ�����β��һ���ո�

		int		nReserved;		//�������ֽ�

		short	wFormatTag;		//��ʽ���
		WORD	wChannels;		//������
		DWORD	dwSamplePerSec;	//������
		DWORD	dwBytesPerSec;	//���ݴ�������
		WORD	wBlockAlign;	//���ݿ����ֵ
		WORD	wBitsPerSample;	//ÿ��������λ��

		char	szDATA[4];		// "data" ��־
		DWORD	dwDataLen;		//���ݶγ��ȣ���λ��λ��
	};

	#pragma pack ( pop )

	//--------------------------------------------------------------------------------------------------------------
	// Wave �ļ�������
	class FK_DLL WaveDecoder : public SoundDecoder
	{
	public:
		WaveDecoder();
		~WaveDecoder();

		//�������ļ�
		SoundFormat* OpenSoundFile( FileObject* pFile, LPCSTR szFileName );

		//�ر������ļ�
		void CloseSoundFile();

		//����������ȡλ�õ����
		void ResetReadPos();

		//��ȡ�������ݵ�ָ������
		void ReadSoundData( void* pBuf, DWORD dwLen );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
