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
	//�Ƿ�ɽ����ֽ��ַ���ת��Ϊ����
	bool NumConvert::CanMultiByteToInt( LPCSTR szStr, UINT nLen )
	{
		if( nLen == 0 )
			nLen = (UINT)strlen( szStr );

		//�����һ���ַ�Ϊ�������Թ�
		UINT nRemainNum = nLen;
		char* pStr = (char*)szStr;
		if( *pStr == '-' )
		{
			++pStr;
			--nRemainNum;
		}

		for( unsigned int i=0; i<nRemainNum; ++i )
		{
			BYTE Symbol = (BYTE)*pStr++;

			//�����ǰ�ַ������������޷�ת��
			if( Symbol < 48 && Symbol > 57 )
				return false;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Ƿ�ɽ����ֽ��ַ���ת��Ϊ������
	bool NumConvert::CanMultiByteToFloat( LPCSTR szStr, UINT nLen )
	{
		if( nLen == 0 )
			nLen = (UINT)strlen( szStr );

		//�����һ���ַ�Ϊ�������Թ�
		UINT nRemainNum = nLen;
		char* pStr = (char*)szStr;
		if( *pStr == '-' )
		{
			++pStr;
			--nRemainNum;
		}

		bool HaveDot = false;
		for( unsigned int i=0; i<nRemainNum; ++i )
		{
			BYTE Symbol = (BYTE)*pStr++;

			//������� '.' С����
			if( Symbol == 46 )
			{
				//����ǵ�һ������ '.' С����
				if( !HaveDot )
				{
					//���С���㲻�ڿ�ʼ���β
					if( i > 0 && i+1 < nRemainNum )
						HaveDot = true;
					else
						return false;
				}
				//����ڶ����������޷�ת��
				else
					return false;
			}
			//�����ǰ�ַ������������޷�ת��
			else if( Symbol < 48 && Symbol > 57 )
				return false;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Ƿ�ɽ� Unicode �ַ���ת��Ϊ����
	bool NumConvert::CanUnicodeToInt( LPCWSTR szStr, UINT nLen )
	{
		if( nLen == 0 )
			nLen = (UINT)wcslen( szStr );

		//�����һ���ַ�Ϊ�������Թ�
		UINT nRemainNum = nLen;
		wchar_t* pStr = (wchar_t*)szStr;
		if( *pStr == L'-' )
		{
			++pStr;
			--nRemainNum;
		}

		for( unsigned int i=0; i<nRemainNum; ++i )
		{
			WORD Symbol = (WORD)*pStr++;

			//�����ǰ�ַ������������޷�ת��
			if( Symbol < 48 && Symbol > 57 )
				return false;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Ƿ�ɽ� Unicode �ַ���ת��Ϊ������
	bool NumConvert::CanUnicodeToFloat( LPCWSTR szStr, UINT nLen )
	{
		if( nLen == 0 )
			nLen = (UINT)wcslen( szStr );

		//�����һ���ַ�Ϊ�������Թ�
		UINT nRemainNum = nLen;
		wchar_t* pStr = (wchar_t*)szStr;
		if( *pStr == '-' )
		{
			++pStr;
			--nRemainNum;
		}

		bool HaveDot = false;
		for( unsigned int i=0; i<nRemainNum; ++i )
		{
			WORD Symbol = (WORD)*pStr++;

			//������� '.' С����
			if( Symbol == 46 )
			{
				//����ǵ�һ������ '.' С����
				if( !HaveDot )
				{
					//���С���㲻�ڿ�ʼ���β
					if( i > 0 && i+1 < nRemainNum )
						HaveDot = true;
					else
						return false;
				}
				//����ڶ����������޷�ת��
				else
					return false;
			}
			//�����ǰ�ַ������������޷�ת��
			else if( Symbol < 48 && Symbol > 57 )
				return false;
		}

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ֽ��ַ���ת��Ϊ����
	int NumConvert::MultiByteToInt( LPCSTR szStr )
	{
		return atoi( szStr );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ֽ��ַ���ת��Ϊ������
	float NumConvert::MultiByteToFloat( LPCSTR szStr )
	{
		return (float)atof( szStr );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�� Unicode �ַ���ת��Ϊ����
	int NumConvert::UnicodeToInt( LPCWSTR szStr )
	{
		return _wtoi( szStr );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�� Unicode �ַ���ת��Ϊ������
	float NumConvert::UnicodeToFloat( LPCWSTR szStr )
	{
		return (float)_wtof( szStr );
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ת��Ϊ���ֽ��ַ���
	int NumConvert::IntToMultiByte( int nValue, char* pBuf )
	{
		int nNumChar = 0;

		//������ת��Ϊ�����ַ���
		char* pChar = pBuf;
		int nParseVal = ( nValue >= 0 ) ? nValue : -nValue;
		do
		{
			int nDigit = nParseVal % 10;
			nParseVal /= 10;

			*pChar = (char)( nDigit + '0' );
			++pChar;
			++nNumChar;
		}while( nParseVal > 0 );

		//���Ϊ����
		if( nValue < 0 )
		{
			*pChar = '-';
			++pChar;
			++nNumChar;
		}

		*pChar = '\0';
		--pChar;

		//��ת�ַ�˳��
		while( pBuf < pChar )
		{
			char TmpChar = *pBuf;
			*pBuf = *pChar;
			*pChar = TmpChar;
			--pChar;
			++pBuf;
		}

		return nNumChar;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ת��Ϊ Unicode �ַ���
	int NumConvert::IntToUnicode( int nValue, wchar_t* pBuf )
	{
		int nNumChar = 0;

		//������ת��Ϊ�����ַ���
		wchar_t* pChar = pBuf;
		int nParseVal = ( nValue >= 0 ) ? nValue : -nValue;
		do
		{
			int nDigit = nParseVal % 10;
			nParseVal /= 10;

			*pChar = (wchar_t)( nDigit + L'0' );
			++pChar;
			++nNumChar;
		}while( nParseVal > 0 );

		//���Ϊ����
		if( nValue < 0 )
		{
			*pChar = L'-';
			++pChar;
			++nNumChar;
		}

		*pChar = L'\0';
		--pChar;

		//��ת�ַ�˳��
		while( pBuf < pChar )
		{
			wchar_t TmpChar = *pBuf;
			*pBuf = *pChar;
			*pChar = TmpChar;
			--pChar;
			++pBuf;
		}

		return nNumChar;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ת��Ϊ���ֽ��ַ���
	int NumConvert::FloatToMultiByte( float fValue, char* pBuf, int nPrecision )
	{
		// 4 �ֽڸ������ɴ洢 8 λ����
		// 8 �ֽڸ������ɴ洢 16 λ����
		// 10 �ֽڸ������ɴ洢 19 λ����

		bool bSign = false;			//�Ƿ���ڸ���
		int nExponent;				// 10 ����ָ��

		unsigned char pBCDBuf[10] = { NULL };	//�����Ƹ�ʽ���ֻ���

		//�������ֵΪ��
		if( fValue == 0.0f )
		{
			char* pChar = pBuf;
			*pChar = '0';
			++pChar;

			if( nPrecision > 0 )
			{
				*pChar = '.';
				++pChar;

				for( int i=0; i<nPrecision; ++i )
				{
					*pChar = '0';
					++pChar;
				}
			}

			*pChar = '\0';

			return (int)( pChar - pBuf );
		}

		const float fOne = 1.0f;
		const float fTen = 10.0f;

		int CtrlwdHolder;			//ԭ������
		int CtrlwdSetter;			//�¿�����

		__asm
		{
			//���ֽڸ������洢�ṹ�� 1 λ���� 8 λָ�� 23 λβ��
			mov		eax, [fValue];
			shr		eax, 23;

			//�ж��Ƿ��з���
			test	eax, 0x100;
			je		NoSign;
			mov		BYTE PTR [bSign], 1;

NoSign:
			//��ȡ������������ָ��
			and		eax, 0xFF;
			sub		eax, 127;
			mov		[nExponent], eax;

			fclex;							//��������쳣
			fstcw	[CtrlwdHolder];			//���������
			mov		[CtrlwdSetter], 0x27F;	//���ÿ�����
			fldcw	CtrlwdSetter;

			//��������������ָ�� = log2( fValue ) ���� log2( fValue ) * log10( 2 ) = log10( fValue )

			fild	[nExponent];			//װ��������ָ��
			fldlg2;							// st0 = log10( 2 ), st1 = ָ��
			fmulp	st(1), st;				// st0 = log10( fValue )
			fistp	[nExponent];			// nExponent = log10( fValue ) �ó� 10 ����ָ��

			//��Ҫ���������� 8 ����Ч�����ƶ���С����ǰ����ʹ��ȫ���ַ�ת����Χ֮�ڡ�
			//��ˣ�������Ҫ��ԭ���������Ժ��ʵ�ʮ����ָ����

			xor		esi, esi;				//��ձ�־�Ĵ���
			mov		eax, 7;					//Ҫʹ 8 ����Ч������С����ǰ����ô��ָ��ӦΪ 7��
			sub		eax, [nExponent];		//��ȥʵ��ָ���ó�����ֵ
			mov		[nExponent], eax;		//�����������ָ��


			//��������ָ������ʵ�ʵ�����ϵ��
			jns		CalcPower;				//���ָ��С������ı����ķ���
			neg		eax;
			mov		esi, 1;					//��־ָ��С����

CalcPower:
			fld1;							//������ʱ���� z = 1	st0 = z
			fld		[fTen];					//������ʱ���� x = 10	st0 = x, st1 = z

CalcLoop:
			test	al, 1;					//���ָ��Ϊ����
			je		ChangeFactor;
			// z *= x
			fxch	st(1);					// st0 = z, st1 = x
			fmul	st, st(1);				// st0 = z * x, st1 = x;
			fxch	st(1);					// st0 = x, st1 = z * x;

ChangeFactor:
			shr		eax, 1;					//ָ������ 2
			test	eax, eax;				//���ָ��Ϊ�����˳�ѭ��
			je		ExitLoop;
			// x *= x
			fld		st(0);					// st0 = x, st1 = x, st1 = z
			fmulp	st(1), st;				// st0 = x * x, st1 = z

			jmp		CalcLoop;				//�ص�ѭ����ʼ

ExitLoop:
			test	esi, esi;				//���ָ��Ϊ����
			fstp	st(0);					// st0 = z �������յ�����ϵ����
			je		PositiveExp;
			fdivr	[fOne];					//�����ĵ��� st0 = 1.0f / z

PositiveExp:


			fld		[fValue];				//װ��Դ������ st0 = fValue, st1 = ����ϵ��
			fmulp	st(1), st;				//�仯ԭ��������λ st0 = �仯��ĸ�����

			//ת�� BCD ��ʽ����Ϊ�ַ���
			lea		esi, pBCDBuf;
			fbstp	[esi];					//�� st0 ����Ϊ�����Ʊ����ʮ�������֣�BCD��

			add		esi, 3;					// BCD ��ʽÿ�ֽڱ����������֣��ܹ����� 18 �����֣�����һ���ֽڱ�����š�
			mov		edi, pBuf;				//����ֻ��Ҫת��ǰ 4 ���ֽڵ� 8 �����֣�������ǽ�ָ��ָ��������ʼλ�á�

			//ѭ�� 4 �δ��� 8 ������
			mov		ecx, 4;

ProcTwoDigit:
			movzx	ax, BYTE PTR [esi];		//����λ�������� ax �Ĵ��� xxxx xxxx AAAA BBBB
			dec		esi;					//��ָ��ָ�����������ִ洢�ֽ�
			shl		ax, 4;					//xxxx AAAA BBBB xxxx
			shr		al, 4;					//xxxx AAAA xxxx BBBB
			rol		ax, 8;					//xxxx BBBB xxxx AAAA
			add		ax, 0x3030;				//BBBB + 48 AAAA + 48 ����ʱ��Ϊ���ֽ��ַ������ֱ��룩
			mov		[edi], ax;				//���ַ����ݸ��ƽ��ַ���
			add		edi, 2;					//�ƶ����ַ�ƫ����

			dec		ecx;					//�ݼ�������
			jnz		ProcTwoDigit;

			fldcw	[CtrlwdHolder];			//�ָ�������
			fwait;
		}

		//�����Ч���ֵ�һλΪ��
		if( *pBuf == '0' )
		{
			memcpy( pBuf, pBuf + 1, 7 );
			pBuf[7] = '0';
			++nExponent;
		}

		char* pEndPos = NULL;

		//���С��������Ч�������
		if( nExponent >= 8 )
		{
			//�����Ҫ��ʾС��
			if( nPrecision > 0 )
			{
				//����С�����ұ������λ����
				int nNumZeroPad = nExponent - 8;
				if( nNumZeroPad > nPrecision )
					nNumZeroPad = nPrecision;

				//���㱣����Ч��������
				int nRemainDigit = nPrecision - nNumZeroPad;

				//С����ʼλ��
				char* pDecPos = pBuf + 2;

				//�ƶ���Ч����
				memmove( pDecPos + nNumZeroPad, pBuf, nRemainDigit );

				//�����λ
				for( int i=0; i<nNumZeroPad; ++i )
					pDecPos[i] = '0';

				pBuf[0] = '0';
				pBuf[1] = '.';

				pEndPos = pDecPos + nPrecision;
			}
			//�������Ҫ��ʾС��
			else
			{
				*pBuf = '1';
				pEndPos = pBuf + 1;
			}
		}
		//���С��������Ч�����ұ�
		else if( nExponent <= 0 )
		{
			//����С������������λ����
			int nNumZeroPad = -nExponent;
			char* pPadPos = pBuf + 8;
			for( int i=0; i<nNumZeroPad; ++i )
				pPadPos[i] = '0';

			//�����Ҫ��ʾС��
			if( nPrecision > 0 )
			{
				pPadPos[ nNumZeroPad ] = '.';

				//С����ʼλ��
				char* pDecPos = pPadPos + nNumZeroPad + 1;
				for( int i=0; i<nPrecision; ++i )
					pDecPos[i] = '0';

				pEndPos = pDecPos + nPrecision;
			}
			//�������Ҫ��ʾС��
			else
			{
				pEndPos = pPadPos + nNumZeroPad;
			}
		}
		//���С��������Ч�����м�
		else
		{
			//�����Ҫ��ʾС��
			if( nPrecision > 0 )
			{
				//С�����ұ���Ч����λ��
				char* pDecDigit = pBuf + 8 - nExponent;

				//����С�����ұ߱�����Ч��������
				int nRemainDigit = nExponent;
				if( nRemainDigit > nPrecision )
				{
					nRemainDigit = nPrecision;
				}
				else
				{
					//����С�����ұ������λ����
					int nNumZeroPad = nPrecision - nRemainDigit;
					char* pPadPos = pDecDigit + 1 + nRemainDigit;

					//�����λ
					for( int i=0; i<nNumZeroPad; ++i )
						pPadPos[i] = '0';
				}

				//�ƶ�С�����ұ���Ч���ֵ���ȷλ��
				memmove( pDecDigit + 1, pDecDigit, nRemainDigit );

				*pDecDigit = '.';

				pEndPos = pDecDigit + nPrecision + 1;
			}
			//�������Ҫ��ʾС��
			else
			{
				pEndPos = pBuf + 8 - nExponent;
			}
		}

		*pEndPos = '\0';
		int nStrLen = (int)( pEndPos - pBuf ) + 1;

		//������ڸ���
		if( bSign )
		{
			//����Ƿ���ڲ�Ϊ�����Ч����
			char* pChar = pBuf;
			while( *pChar != '\0' )
			{
				if( *pChar != '0' && *pChar != '.' )
				{
					//���ַ�����ʼλ�����Ӹ���
					memmove( pBuf + 1, pBuf, nStrLen );
					pBuf[0] = '-';
					++nStrLen;
					return nStrLen;
				}

				++pChar;
			}
		}

		return nStrLen;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ת��Ϊ Unicode �ַ���
	int NumConvert::FloatToUnicode( float fValue, wchar_t* pBuf, int nPrecision )
	{		
		bool bSign = false;			//�Ƿ���ڸ���
		int nExponent;				// 10 ����ָ��

		unsigned char pBCDBuf[10] = { NULL };	//�����Ƹ�ʽ���ֻ���

		//�������ֵΪ��
		if( fValue == 0.0f )
		{
			wchar_t* pChar = pBuf;
			*pChar = L'0';
			++pChar;

			if( nPrecision > 0 )
			{
				*pChar = L'.';
				++pChar;

				for( int i=0; i<nPrecision; ++i )
				{
					*pChar = L'0';
					++pChar;
				}
			}

			*pChar = L'\0';

			return (int)( pChar - pBuf );
		}

		const float fOne = 1.0f;
		const float fTen = 10.0f;

		int CtrlwdHolder;			//ԭ������
		int CtrlwdSetter;			//�¿�����

		__asm
		{
			//���ֽڸ������洢�ṹ�� 1 λ���� 8 λָ�� 23 λβ��
			mov		eax, [fValue];
			shr		eax, 23;

			//�ж��Ƿ��з���
			test	eax, 0x100;
			je		NoSign;
			mov		BYTE PTR [bSign], 1;

NoSign:
			//��ȡ������������ָ��
			and		eax, 0xFF;
			sub		eax, 127;
			mov		[nExponent], eax;

			fclex;							//��������쳣
			fstcw	[CtrlwdHolder];			//���������
			mov		[CtrlwdSetter], 0x27F;	//���ÿ�����
			fldcw	CtrlwdSetter;

			//��������������ָ�� = log2( fValue ) ���� log2( fValue ) * log10( 2 ) = log10( fValue )

			fild	[nExponent];			//װ��������ָ��
			fldlg2;							// st0 = log10( 2 ), st1 = ָ��
			fmulp	st(1), st;				// st0 = log10( fValue )
			fistp	[nExponent];			// nExponent = log10( fValue ) �ó� 10 ����ָ��

			//��Ҫ���������� 8 ����Ч�����ƶ���С����ǰ����ʹ��ȫ���ַ�ת����Χ֮�ڡ�
			//��ˣ�������Ҫ��ԭ���������Ժ��ʵ�ʮ����ָ����

			xor		esi, esi;				//��ձ�־�Ĵ���
			mov		eax, 7;					//Ҫʹ 8 ����Ч������С����ǰ����ô��ָ��ӦΪ 7��
			sub		eax, [nExponent];		//��ȥʵ��ָ���ó�����ֵ
			mov		[nExponent], eax;		//�����������ָ��


			//��������ָ������ʵ�ʵ�����ϵ��
			jns		CalcPower;				//���ָ��С������ı����ķ���
			neg		eax;
			mov		esi, 1;					//��־ָ��С����

CalcPower:
			fld1;							//������ʱ���� z = 1	st0 = z
			fld		[fTen];					//������ʱ���� x = 10	st0 = x, st1 = z

CalcLoop:
			test	al, 1;					//���ָ��Ϊ����
			je		ChangeFactor;
			// z *= x
			fxch	st(1);					// st0 = z, st1 = x
			fmul	st, st(1);				// st0 = z * x, st1 = x;
			fxch	st(1);					// st0 = x, st1 = z * x;

ChangeFactor:
			shr		eax, 1;					//ָ������ 2
			test	eax, eax;				//���ָ��Ϊ�����˳�ѭ��
			je		ExitLoop;
			// x *= x
			fld		st(0);					// st0 = x, st1 = x, st1 = z
			fmulp	st(1), st;				// st0 = x * x, st1 = z

			jmp		CalcLoop;				//�ص�ѭ����ʼ

ExitLoop:
			test	esi, esi;				//���ָ��Ϊ����
			fstp	st(0);					// st0 = z �������յ�����ϵ����
			je		PositiveExp;
			fdivr	[fOne];					//�����ĵ��� st0 = 1.0f / z

PositiveExp:


			fld		[fValue];				//װ��Դ������ st0 = fValue, st1 = ����ϵ��
			fmulp	st(1), st;				//�仯ԭ��������λ st0 = �仯��ĸ�����

			//ת�� BCD ��ʽ����Ϊ�ַ���
			lea		esi, pBCDBuf;
			fbstp	[esi];					//�� st0 ����Ϊ�����Ʊ����ʮ�������֣�BCD��

			add		esi, 3;					// BCD ��ʽÿ�ֽڱ����������֣��ܹ����� 18 �����֣�����һ���ֽڱ�����š�
			mov		edi, pBuf;				//����ֻ��Ҫת��ǰ 4 ���ֽڵ� 8 �����֣�������ǽ�ָ��ָ��������ʼλ�á�

			//ѭ�� 4 �δ��� 8 ������
			mov		ecx, 4;

ProcTwoDigit:
			movzx	eax, BYTE PTR [esi];	//����λ�������� eax �Ĵ��� xxxx xxxx xxxx xxxx xxxx xxxx AAAA BBBB
			dec		esi;					//��ָ��ָ�����������ִ洢�ֽ�
			shl		eax, 12;				//xxxx xxxx xxxx AAAA BBBB xxxx xxxx xxxx
			shr		ax, 12;					//xxxx xxxx xxxx AAAA xxxx xxxx xxxx BBBB
			rol		eax, 16;				//xxxx xxxx xxxx BBBB xxxx xxxx xxxx AAAA
			add		eax, 0x300030;			//xxxx xxxx BBBB + 48 xxxx xxxx AAAA + 48 ����ʱ��Ϊ˫�ֽ��ַ������ֱ��룩
			mov		[edi], eax;				//���ַ����ݸ��ƽ��ַ���
			add		edi, 4;					//�ƶ����ַ�ƫ����

			dec		ecx;					//�ݼ�������
			jnz		ProcTwoDigit;

			fldcw	[CtrlwdHolder];			//�ָ�������
			fwait;
		}

		//�����Ч���ֵ�һλΪ��
		if( *pBuf == L'0' )
		{
			wmemcpy( pBuf, pBuf + 1, 7 );
			pBuf[7] = L'0';
			++nExponent;
		}

		wchar_t* pEndPos = NULL;

		//���С��������Ч�������
		if( nExponent >= 8 )
		{
			//�����Ҫ��ʾС��
			if( nPrecision > 0 )
			{
				//����С�����ұ������λ����
				int nNumZeroPad = nExponent - 8;
				if( nNumZeroPad > nPrecision )
					nNumZeroPad = nPrecision;

				//���㱣����Ч��������
				int nRemainDigit = nPrecision - nNumZeroPad;

				//С����ʼλ��
				wchar_t* pDecPos = pBuf + 2;

				//�ƶ���Ч����
				wmemmove( pDecPos + nNumZeroPad, pBuf, nRemainDigit );

				//�����λ
				for( int i=0; i<nNumZeroPad; ++i )
					pDecPos[i] = L'0';

				pBuf[0] = L'0';
				pBuf[1] = L'.';

				pEndPos = pDecPos + nPrecision;
			}
			//�������Ҫ��ʾС��
			else
			{
				*pBuf = L'1';
				pEndPos = pBuf + 1;
			}
		}
		//���С��������Ч�����ұ�
		else if( nExponent <= 0 )
		{
			//����С������������λ����
			int nNumZeroPad = -nExponent;
			wchar_t* pPadPos = pBuf + 8;
			for( int i=0; i<nNumZeroPad; ++i )
				pPadPos[i] = L'0';

			//�����Ҫ��ʾС��
			if( nPrecision > 0 )
			{
				pPadPos[ nNumZeroPad ] = L'.';

				//С����ʼλ��
				wchar_t* pDecPos = pPadPos + nNumZeroPad + 1;
				for( int i=0; i<nPrecision; ++i )
					pDecPos[i] = L'0';

				pEndPos = pDecPos + nPrecision;
			}
			//�������Ҫ��ʾС��
			else
			{
				pEndPos = pPadPos + nNumZeroPad;
			}
		}
		//���С��������Ч�����м�
		else
		{
			//�����Ҫ��ʾС��
			if( nPrecision > 0 )
			{
				//С�����ұ���Ч����λ��
				wchar_t* pDecDigit = pBuf + 8 - nExponent;

				//����С�����ұ߱�����Ч��������
				int nRemainDigit = nExponent;
				if( nRemainDigit > nPrecision )
				{
					nRemainDigit = nPrecision;
				}
				else
				{
					//����С�����ұ������λ����
					int nNumZeroPad = nPrecision - nRemainDigit;
					wchar_t* pPadPos = pDecDigit + 1 + nRemainDigit;

					//�����λ
					for( int i=0; i<nNumZeroPad; ++i )
						pPadPos[i] = L'0';
				}

				//�ƶ�С�����ұ���Ч���ֵ���ȷλ��
				wmemmove( pDecDigit + 1, pDecDigit, nRemainDigit );

				*pDecDigit = L'.';

				pEndPos = pDecDigit + nPrecision + 1;
			}
			//�������Ҫ��ʾС��
			else
			{
				pEndPos = pBuf + 8 - nExponent;
			}
		}

		*pEndPos = '\0';
		int nStrLen = (int)( pEndPos - pBuf ) + 1;

		//������ڸ���
		if( bSign )
		{
			//����Ƿ���ڲ�Ϊ�����Ч����
			wchar_t* pChar = pBuf;
			while( *pChar != L'\0' )
			{
				if( *pChar != L'0' && *pChar != L'.' )
				{
					//���ַ�����ʼλ�����Ӹ���
					wmemmove( pBuf + 1, pBuf, nStrLen );
					pBuf[0] = L'-';
					++nStrLen;
					return nStrLen;
				}

				++pChar;
			}
		}

		return nStrLen;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
