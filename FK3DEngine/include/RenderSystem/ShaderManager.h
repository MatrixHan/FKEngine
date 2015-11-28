/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ShaderManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��ɫ��������
	class FK_DLL ShaderManager : public Singleton< ShaderManager >
	{
	protected:
		FileObject*			mpShaderPack;	// ��ɫ���������ļ�

		VertexShaderList	mVSList;		//������ɫ���б�
		PixelShaderList		mPSList;		//������ɫ���б�

	public:
		ShaderManager();
		virtual ~ShaderManager();

		//������ɫ���������ļ�
		void SetProgramPackFile( FileObject* pPackFile );

		//��ָ�����ļ���������ɫ��
		void CreateShaderFromFile( LPCSTR szFileName );

		//����������ɫ��
		virtual VertexShader* CreateVertexShader() = 0;

		//����������ɫ��
		virtual PixelShader* CreatePixelShader() = 0;

		//��ȡָ����ŵĶ�����ɫ��
		VertexShader* GetVertexShader( UINT nIndex );

		//��ȡָ����ŵ�������ɫ��
		PixelShader* GetPixelShader( UINT nIndex );

		//ɾ��ָ���Ķ�����ɫ��
		void DeleteVertexShader( VertexShader* pVertexShader );

		//ɾ��ָ����������ɫ��
		void DeletePixelShader( PixelShader* pPixelShader );

		//ɾ�����еĶ�����ɫ��
		void DeleteAllVertexShader();

		//ɾ�����е�������ɫ��
		void DeleteAllPixelShader();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
