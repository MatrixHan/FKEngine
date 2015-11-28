/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	NumConvert
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	���渨�����ܳ���
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//����ת����
	class FK_DLL NumConvert
	{
	public:
		static const int	mMaxIntTextLen = 65;				//�������ת���ַ�������
		static const int	mMaxFloatTextLen = _CVTBUFSIZE;		//��󸡵���ת���ַ�������

	public:
		//�Ƿ�ɽ����ֽ��ַ���ת��Ϊ����
		static bool CanMultiByteToInt( LPCSTR szStr, UINT nLen = 0 );

		//�Ƿ�ɽ����ֽ��ַ���ת��Ϊ������
		static bool CanMultiByteToFloat( LPCSTR szStr, UINT nLen = 0 );

		//�Ƿ�ɽ� Unicode �ַ���ת��Ϊ����
		static bool CanUnicodeToInt( LPCWSTR szStr, UINT nLen = 0 );

		//�Ƿ�ɽ� Unicode �ַ���ת��Ϊ������
		static bool CanUnicodeToFloat( LPCWSTR szStr, UINT nLen = 0 );

		//�����ֽ��ַ���ת��Ϊ����
		static int MultiByteToInt( LPCSTR szStr );

		//�����ֽ��ַ���ת��Ϊ������
		static float MultiByteToFloat( LPCSTR szStr );

		//�� Unicode �ַ���ת��Ϊ����
		static int UnicodeToInt( LPCWSTR szStr );

		//�� Unicode �ַ���ת��Ϊ������
		static float UnicodeToFloat( LPCWSTR szStr );

		//������ת��Ϊ���ֽ��ַ���
		static int IntToMultiByte( int nValue, char* pBuf );

		//������ת��Ϊ Unicode �ַ���
		static int IntToUnicode( int nValue, wchar_t* pBuf );

		//��������ת��Ϊ���ֽ��ַ���
		static int FloatToMultiByte( float fValue, char* pBuf, int nPrecision = 2 );

		//��������ת��Ϊ Unicode �ַ���
		static int FloatToUnicode( float fValue, wchar_t* pBuf, int nPrecision = 2 );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
