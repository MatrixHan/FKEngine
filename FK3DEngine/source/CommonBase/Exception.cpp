/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Exception
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

	//���һ���쳣
	Exception Exception::mLastException;

	//--------------------------------------------------------------------------------------------------------------
	Exception::Exception()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//�쳣���캯��
	//
	// eLevel��	�쳣����
	// sDesc��	�쳣����
	// sFunc��	�׳��쳣����
	// sFile��	�׳��쳣�ļ�
	// nLine��	�׳��쳣�к�
	Exception::Exception( ExceptionType eType, const String& sDesc, LPCSTR szFunc, LPCSTR szFile, UINT nLine )
		: mType		(eType)
		, mDesc		(sDesc)
		, mFunc		(szFunc)
		, mFile		(szFile)
		, mLine		(nLine)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�쳣������Ϣ
	String Exception::GetDescription()
	{
		char* pszDescription[] =
		{
			"δ֪�Ĵ�������",			//ERR_UNKNOWN
			"�ڴ治��",					//ERR_NOT_ENOUGH_MEM
			"�޷���ָ���ļ�",			//ERR_CANNOT_OPEN_FILE
			"�޷���ȡ�ļ�����",			//ERR_CANNOT_READ_FILE
			"�޷�д���ļ�����",			//ERR_CANNOT_WRITE_FILE
			"�Ƿ��Ĵ������",			//ERR_INVALIDPARAMS
			"���ƹ���",					//ERR_NAME_TOO_LONG
			"��Ⱦϵͳ API ����",		//ERR_RENDER_API_ERROR
			"����ϵͳ API ����",		//ERR_SOUND_API_ERROR
			"Windows ����ϵͳ API ����",//ERR_WINAPI_ERROR
			"�����ظ�����Ŀ",			//ERR_DUPLICATE_ITEM
			"�Ҳ���ָ����Ŀ",			//ERR_ITEM_NOT_FOUND
			"�������ڲ�����",			//ERR_INTERNAL_ERROR
			"���������ж�",				//ERR_RT_ASSERTION_FAILED
		};

		//��ʽ��������Ϣ
		String FullDesc = Misc::FormatString( NULL,	"�����쳣��ֹ��\n"
													"\n�쳣������ %s"
													"\n�������ͣ� %s"
													"\n�����ļ��� %s"
													"\n�������� %s"
													"\n�����кţ� %d",
													mDesc.GetCharPtr(),
													pszDescription[ mType ],
													mFile.GetCharPtr(),
													mFunc.GetCharPtr(),
													mLine );

		return FullDesc;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����쳣����
	void Exception::SetException( ExceptionType eType, const String& sDesc, LPCSTR szFunc, LPCSTR szFile, UINT nLine )
	{
		mLastException.mType = eType;
		mLastException.mDesc = sDesc;
		mLastException.mFunc = szFunc;
		mLastException.mFile = szFile;
		mLastException.mLine = nLine;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
