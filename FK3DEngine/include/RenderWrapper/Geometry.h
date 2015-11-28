/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Geometry
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��������
	class FK_DLL Geometry : public RenderObject
	{
	public:
		//�����崴������
		typedef Geometry* (*FnCreator)();

	public:
		RenderInstList		mRenderInstList;	//��Ⱦʵ���б�

		bool				mbSoftVertexProc;	//�Ƿ�Ϊ������㴦��
		UINT				mNumBlendMatrix;	//�����Ͼ�������
		UINT				mMaxBlendIndex;		//ʹ������������ֵ

	public:
		Geometry();
		virtual ~Geometry();

		//����������
		void BuildMeshStream( UINT nVerNum, UINT nIndexNum, bool bHaveUV = false,
			bool bHaveNormal = false, bool bHaveColor = false, UINT nNumBlendMatrix = 0, UINT nMaxBlendIndex = 0 );

		//ɾ��������
		void DestroyMeshStream();

		//��ʼ����Ⱦʵ���б�
		void InitializeInstanceList( UINT nInitNum, UINT nAddNum );

		//�ͷ���Ⱦʵ���б�
		void ReleaseInstanceList();

		//������Ⱦʵ��
		RenderInstance* CreateInstance();

		//ɾ��ָ����Ⱦʵ��
		void DeleteInstance( RenderInstance* pInstance );

		//ɾ��������Ⱦʵ��
		void DeleteAllInstance();
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Geometry* >		GeometryList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
