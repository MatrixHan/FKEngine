/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	PackObject
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	����ļ�������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//����ļ������� �������ࣩ
	class FK_DLL PackObject : public FileObject
	{
	protected:
		BaseFile		mPackFile;		//����ļ�����

	public:
		//��������ļ�
		virtual void CreatePack( LPCSTR szPackName, LPCSTR szBasePath, StringArray* pFileNames, int nSubLevel ) = 0;

		//�򿪴���ļ�
		virtual void OpenPack( LPCSTR szPackName ) = 0;

		//�ڴ���ļ��������ļ�
		virtual void AddToPack( StringArray* pFileNames, int nSubLevel ) = 0;

		//�Ӵ���ļ���ɾ���ļ�
		virtual void DelFromPack( StringArray* pFileNames ) = 0;

		//��ȡ�����ļ��б�
		virtual void GetFileListInPack( FileSelectList* pFileList ) = 0;

		//�رմ���ļ�
		virtual bool ClosePack() = 0;
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
