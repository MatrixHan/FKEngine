/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	MpegInterface
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	MPEG ����ӿ�
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	const int	MPEG_MaxFrameSize	= 1792;
	const int	MPEG_SBLimit		= 32;
	const int	MPEG_SSLimit		= 18;
	const int	MPEG_ScaleBlock		= 12;

	extern const DWORD	MPEG_BitRateTable[3][3][16];	// MPEG ����������ӳ���
	extern const DWORD	MPEG_FrequencyTable[9];			// MPEG ����Ƶ��ӳ���

	//--------------------------------------------------------------------------------------------------------------

	// MPEG �汾
	const BYTE MPEG_Version1	= 0;
	const BYTE MPEG_Version2	= 1;
	const BYTE MPEG_Version25	= 2;

	// MPEG ����
	const BYTE MPEG_Layer1		= 0;
	const BYTE MPEG_Layer2		= 1;
	const BYTE MPEG_Layer3		= 2;

	// MPEG ֡��Ϣ
	struct MPEGFrameInfo
	{
		BYTE	bMpegVersion;	// MPEG �汾
		BYTE	bMpegLayer;		// MPEG ����

		bool	bCopyright;		//�Ƿ����а�Ȩ
		bool	bOriginal;		//�Ƿ�Ϊԭ��
		bool	bCRC;			//�Ƿ���� CRC У������
		bool	bPadding;		//�Ƿ���ڲ���λ

		DWORD	dwChannels;		//����������
		DWORD	dwFrequency;	//����Ƶ��
		DWORD	dwBitRate;		//����������

		BYTE	bJointMode;		// Joint Stereo ģʽ
		BYTE	bEmphasis;		// Emphasis ģʽ

		DWORD	dwFrameSize;	//֡���ݳ��ȣ����� 4 �ֽڵ�֡ͷ�� 2 �ֽڵ� CRC У�����ݣ�

		int		nFreqIndex;		//Ƶ������ֵ
		int		nBitRateIndex;	//����������ֵ
		int		nChannelMode;	//����ģʽ
		int		nJointStereo;	// Joint Stereo ģʽ��������
		int		nTableSelect;	//�ڶ�����������
		void*	pTableAlloc;	//�ڶ�������ָ��
	};

	//--------------------------------------------------------------------------------------------------------------

	//��ʼ�� MPEG ��Ƶ������
	void InitAudioDecoder();

	//���� MPEG ��Ƶ֡
	int DecodeAudioFrame( MPEGFrameInfo* pFrameInfo, char* pIn, char* pOut );

	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================