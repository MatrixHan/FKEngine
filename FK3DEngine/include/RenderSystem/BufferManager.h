/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BufferManager
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
	//���������
	class FK_DLL BufferManager : public Singleton< BufferManager >
	{
	protected:
		VertexBufferList		mVBList;	//���㻺���б�
		IndexBufferList			mIBList;	//���������б�
		VertexDeclarationList	mVDList;	//���������б�

	public:
		BufferManager();
		virtual ~BufferManager();

		//��ʼ�����������
		void Initialize();

		//�ͷŻ��������
		void Release();

		//�������㻺��
		virtual VertexBuffer* AddVertexBuffer() = 0;

		//������������
		virtual IndexBuffer* AddIndexBuffer() = 0;

		//������������
		virtual VertexDeclaration* AddVertexDeclaration() = 0;

		//ɾ�����㻺��
		void DelVertexBuffer( VertexBuffer* pVB );

		//ɾ����������
		void DelIndexBuffer( IndexBuffer* pIB );

		//ɾ����������
		void DelVertexDeclaration( VertexDeclaration* pVD );

		//ɾ�����ж��㻺��
		void DelAllVertexBuffer();

		//ɾ��������������
		void DelAllIndexBuffer();

		//ɾ�����ж�������
		void DelAllVertexDeclaration();

		//��ȡ���㻺������
		UINT GetNumVertexBuffer();

		//��ȡ������������
		UINT GetNumIndexBuffer();

		//��ȡ������������
		UINT GetNumVertexDeclaration();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
