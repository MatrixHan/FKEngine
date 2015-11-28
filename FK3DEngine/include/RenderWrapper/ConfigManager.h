/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ConfigManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	������Ϣ������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//������Ϣ������
	class FK_DLL ConfigManager : public Singleton< ConfigManager >
	{
	public:
		static ConfigData	mDefConfigData;		//Ĭ��������Ϣ

	protected:
		ConfigDataStack		mConfigDataStack;	//������Ϣ��ջ
		UINT				mCurConfigIndex;	//��ǰ������Ϣ����

	public:
		ConfigManager();
		~ConfigManager();

		//��ָ���������ļ�����������������Ϣ
		void LoadConfigFileData( DataChunk* pConfigFileData );

		//����һ��������Ϣ
		void AddConfig( ConfigData* pConfigData );

		//ɾ��һ��������Ϣ
		void DelConfig( UINT nIndex );

		//ɾ������������Ϣ
		void DelAllConfig();

		//��ȡĬ��������Ϣ
		void GetDefaultConfig( ConfigData* pConfigData );

		//��ȡָ����������Ϣ
		ConfigData* GetConfig( UINT nIndex );

		//���õ�ǰ������Ϣ
		void SetCurrenConfig( UINT nIndex );

		//��ȡ��ǰ������Ϣ
		ConfigData* GetCurrenConfig();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
