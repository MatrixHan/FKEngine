/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	VertexDeclaration
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
	//����Ԫ������
	struct VertexElement
	{
		WORD				nStream;	//������������
		WORD				nOffset;	//�ö���Ԫ���ڶ��������е�ƫ����
		VertexElementType	Type;		//�������ͣ����ȣ�
		VertexElementMethod	Method;		//��դ������
		VertexElementUsage	Usage;		//������;
		BYTE				UsageIndex;	//��;����
	};
	typedef Stack< VertexElement >	VertexElementList;
	//--------------------------------------------------------------------------------------------------------------
	//����������
	class FK_DLL VertexDeclaration
	{
	protected:
		UINT				mNumElement;		//����Ԫ������
		VertexElementList	mVertexElements;	//����Ԫ���б�

	public:
		VertexDeclaration();
		virtual ~VertexDeclaration();

		//��Ӷ���Ԫ��
		void AddElement( WORD nStream, WORD nOffset, VertexElementType eType, VertexElementMethod eMethod,
			VertexElementUsage eUsage, BYTE nUsageIndex );

		//ɾ��ָ��λ�õĶ���Ԫ��
		void DelElement( UINT nIndex );

		//ɾ�����ж���Ԫ��
		void DelAllElement();

		//��ȡָ��λ�õĶ���Ԫ��
		VertexElement* GetElement( UINT nIndex );

		//��ȡ����Ԫ������
		UINT GetElementNum();

		//������������
		virtual void CreateVertexDeclaration() = 0;

		//ɾ����������
		virtual void ReleaseVertexDeclaration() = 0;
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< VertexDeclaration* >	VertexDeclarationList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
