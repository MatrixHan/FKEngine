/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	CommandLine
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
	CommandLine::CommandLine()
	{
		//��ȡ�������ַ���ָ��
		char* pCommandLine = GetCommandLineA();

		//��ȡ��������·���ַ���
		if( *pCommandLine == '\0' || *pCommandLine != '"' )
			return;
		++pCommandLine;

		char* pAppPath = pCommandLine;
		UINT nPathLen = 0;
		while( *pCommandLine != '"' )
		{
			++pCommandLine;
			++nPathLen;
		}

		mAppPath.SetString( pAppPath, nPathLen );

		pCommandLine += 2;

		//��ȡ��������ַ���
		while( *pCommandLine != '\0' )
		{
			char* pArgString = pCommandLine;

			UINT nArgLen = 0;
			while( *pCommandLine != ' ' )
			{
				++pCommandLine;
				++nArgLen;
			}

			if( nArgLen != 0 )
				mArgStrings.Push( pArgString, nArgLen );

			++pCommandLine;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
