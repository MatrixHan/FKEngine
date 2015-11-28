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
*	�ļ�˵����	�쳣��
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

//�쳣�����
#define FKTry							try
#define FKCatch							catch( Exception& sException )
#define FKCatchElse						catch( ... )

#define ShowExceptionMsg				MessageBox( GetActiveWindow(), sException.GetDescription().GetCharPtr(), \
										"����", MB_OK | MB_ICONERROR | MB_TASKMODAL )
#define ShowUnknownExceptionMsg			MessageBox( GetActiveWindow(), "����δ֪�ĳ������", \
										"����", MB_OK | MB_ICONERROR | MB_TASKMODAL )
#define ShowLastException				MessageBox( GetActiveWindow(), Exception::mLastException.GetDescription(). \
										GetCharPtr(), "����", MB_OK | MB_ICONERROR | MB_TASKMODAL )

#define Except( Type, Desc )			throw( Exception( Type, Desc, __FUNCTION__, __FILE__, __LINE__ ) )
#define ExceptToUpLevel					throw sException

#define SetLastException( Type, Desc )	Exception::mLastException.SetException( Type, Desc, \
										__FUNCTION__, __FILE__, __LINE__ )
#define GetLastException				Exception::mLastException

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//�쳣��
	class FK_DLL Exception
	{
	public:
		//�쳣����
		enum ExceptionType
		{
			ERR_UNKNOWN,
			ERR_NOT_ENOUGH_MEM,
			ERR_CANNOT_OPEN_FILE,
			ERR_CANNOT_READ_FILE,
			ERR_CANNOT_WRITE_FILE,
			ERR_INVALIDPARAMS,
			ERR_NAME_TOO_LONG,
			ERR_RENDER_API_ERROR,
			ERR_SOUND_API_ERROR,
			ERR_WINAPI_ERROR,
			ERR_DUPLICATE_ITEM,
			ERR_ITEM_NOT_FOUND,
			ERR_INTERNAL_ERROR,
			ERR_RT_ASSERTION_FAILED,
		};

		//���һ���쳣
		static Exception	mLastException;

	public:
		ExceptionType	mType;	//��������
		String			mDesc;	//��������
		String			mFunc;	//������
		String			mFile;	//�����ļ���
		UINT			mLine;	//�����к�

	public:
		Exception();
		Exception( ExceptionType eType, const String& sDesc, LPCSTR szFunc, LPCSTR szFile, UINT nLine );

		//��ȡ�쳣������Ϣ
		String GetDescription();

		//�����쳣����
		void SetException( ExceptionType eType, const String& sDesc, LPCSTR szFunc, LPCSTR szFile, UINT nLine );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
