/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	FileObject
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�ļ�������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "../CommonBase/BaseTypeDefine.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	//�ļ�״̬
	const int FS_NotExist	= 0x0;		//�ļ�������
	const int FS_Exist		= 0x1;		//�ļ�����

	const int FS_Directory	= 0x2;		//���ļ�ΪĿ¼
	const int FS_ReadOnly	= 0x10;		//�ļ�Ϊֻ������
	const int FS_Hidden		= 0x20;		//�ļ�Ϊ��������
	const int FS_System		= 0x40;		//�ļ�Ϊϵͳ����
	const int FS_Archive	= 0x80;		//�ļ�Ϊ�浵����
	const int FS_Compressed	= 0x100;	//���ļ���ѹ���ļ�

	//--------------------------------------------------------------------------------------------------------------
	//�ļ�������
	enum OpenType
	{
		OT_Read,		//ֻ�����ȡ���ļ�������ڣ�
		OT_Write,		//ֻ����д�루����ԭ�ļ���
		OT_WriteAppend,	//ֻ����д�루���������ݣ�
		OT_ReadWirte,	//��ȡ��д�루�ļ�������ڣ�
	};
	//--------------------------------------------------------------------------------------------------------------
	//�ļ������� �������ࣩ
	class FK_DLL FileObject
	{
	public:
		char	mszCurDir[MAX_PATH];//��ǰĿ¼�ַ���
		UINT	mnCurDirLen;		//��ǰĿ¼�ַ�������

	public:
		FileObject();
		virtual ~FileObject() = 0;

		//�����ļ���ǰĿ¼
		void SetFileDirectory( LPCSTR szCurDir );

		//���ļ�
		virtual void Open( LPCSTR szFileName, OpenType eOpenTyp = OT_Read, bool bOverlapped = false ) = 0;

		//�ر��ļ�
		virtual bool Close() = 0;

		//��ȡ�ļ�����
		virtual DWORD GetLength() = 0;

		//�����ļ���дָ��λ��
		virtual void SetPosition( long Offset, BasePos eBasePos = BP_Begin ) = 0;
		
		//��ȡ�ļ���дָ��λ��
		virtual DWORD GetPosition() = 0;

		//��ȡ�ļ�����
		virtual void Read( void* pBuf, DWORD dwLen ) = 0;

		//д���ļ�����
		virtual void Write( const void* pBuf, DWORD dwLen ) = 0;

		//�첽��ȡ�ļ�����
		virtual bool AsynRead( void* pBuf, DWORD dwLen, LPOVERLAPPED pOverlapped ) = 0;

		//�첽д���ļ�����
		virtual bool AsynWrite( const void* pBuf, DWORD dwLen, LPOVERLAPPED pOverlapped ) = 0;

		//��ȡ�첽��д���
		virtual DWORD GetAsynResult( LPOVERLAPPED pOverlapped, bool bWait = true ) = 0;

	protected:
		//�ڲ����ļ�����
		void _InternalOpen( LPCSTR szFileName, OpenType eOpenType, bool bOverlapped, HANDLE* pHandle );

	public:
		//��ȡָ���ļ���״̬
		static int GetFileStatus( LPCSTR szFileName );

		//ɾ���ļ�
		static bool Delete( LPCSTR szFileName, bool bDeleteReadOnly = false );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
