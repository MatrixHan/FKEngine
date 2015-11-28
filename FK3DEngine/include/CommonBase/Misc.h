/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Misc
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	���渨�����ܳ���
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "Stack.h"
#include <windows.h>
#include "BaseTypeDefine.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//����������
	class FK_DLL Misc
	{
	protected:
		static CHARStack	mFormatBuf;		//�ַ�����ʽ������
		static WCHARStack	mUnicodeBuf;	// Unicode �ַ�������

	public:
		//��ʽ���ַ���
		static char* FormatString( int* pLen, const char* szStr, ... );

		//��ʾ��Ϣ
		static int ShowMsg( const char* szStr, const char* szCaption, int nFlag, ... );

		//��ʾ������Ϣ
		static void ShowErrMsg( const char* szStr, ... );

		//��ʾ WIN32 ϵͳ������Ϣ
		static void ShowWin32ErrMsg();

		//���ص�һ��ָ���ַ����ַ����е�λ�ã��Ҳ����򷵻� -1��
		static int GetFirstCharIndex( char* pStr, char cSymbol );

		//�������һ��ָ���ַ����ַ����е�λ�ã��Ҳ����򷵻� -1��
		static int GetLastCharIndex( char* pStr, char cSymbol );

		//�ж��ַ����Ƿ�Ϊ��ȷ��ȫ���ַ���β
		static bool IsSBCTerminater( char* pStr, size_t nStrLen );

		//�����ֽ��ַ���ת��Ϊ Unicode �ַ���
		static wchar_t* AnsiToUnicode( char* pStr );

		//��ȡ�ַ�����ϣֵ��������ַ������ȣ�
		static unsigned int HashString( const char* pString, size_t* pStrLenOutput = NULL );

		//���� MD5 ��Կ
		static void GetMD5Key( BYTE pMD5Key[16], const char* pString );

		//���� CRC32 У��ֵ
		static DWORD GetCRC32( BYTE* pData, DWORD dwLen );

		//�������ظ�ʽ��ȡɫ���ֽ���
		static unsigned int GetColorDepth( PixelFormat ePixelFormat );

		//�������ظ�ʽ��ȡ Alpha ֵλ��
		static unsigned int GetColorAlphaBits( PixelFormat ePixelFormat );

		//�����������
		static void ResetRandomSeed();

		//����ָ����Χ�ڵ����������
		static int GetIntRandom( const int nMin, const int nMax );

		//����ָ����Χ�ڵĸ��������
		static float GetFloatRandom( const float fMin, const float fMax );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
