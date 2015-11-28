/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	MaterialManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	���ʹ�����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//���ʹ�����
	class FK_DLL MaterialManager : public Singleton< MaterialManager >
	{
	protected:
		MaterialMap			mMaterialMap;		//��������������ϣ��
		MaterialList		mMaterialList;		//��������������ջ

	public:
		MaterialManager();
		~MaterialManager();

		//��ʼ�����ʹ�����
		void Initialize( UINT nNumMaterial );

		//�ͷŲ��ʹ�����
		void Release();

		//�����µĲ���
		Material* CreateMaterial( const char* szMaterialName );

		//�����������������
		Material* CreateMaterial( const char* szTexFileName, MaterialType eType );

		//���ݲ������ݴ����µĲ���
		Material* CreateMaterial( const MaterialData* pMaterialData );

		//ɾ��ԭ�в���
		void DeleteMaterial( Material* pMaterial );

		//ɾ�����в���
		void DeleteAllMaterial();

		//�������ƻ�ȡ����
		FKInline Material* GetMaterial( const char* szMaterialName );

		//��ȡ��������
		FKInline UINT GetMaterialNum();

		//���ݲ�������ѡ�����ʵ��������ʽ
		PixelFormat GetBestTextureFormat( MaterialType eMatType, PixelFormat eOrgPixelFormat );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
