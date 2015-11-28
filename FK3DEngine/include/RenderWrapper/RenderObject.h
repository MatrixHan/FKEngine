/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RenderObject
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��Ⱦ������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class VertexDeclaration;
	class VertexBuffer;
	class IndexBuffer;
	class Material;
	class RenderParam;
	class AnimControl;
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ������
	class FK_DLL RenderObject
	{
	public:
		friend class RenderInstance;

	public:
		UINT				mNumVertexBuffer;	//ʹ�ö��㻺������
		VertexBuffer**		mppVertexBuffer;	//���㻺��ָ������
		IndexBuffer*		mpIndexBuffer;		//��������ָ��
		VertexDeclaration*	mpVertexDeclaration;//��������ָ��

		Material**			mppMaterial;		//��������
		UINT				mNumMaterial;		//��������

		RenderParam*		mpRenderParam;		//��Ⱦ��������
		UINT				mNumRenderParam;	//��Ⱦ��������

		AxisBox3			mBoundBox;			//��Ⱦ�����Χ��

	public:
		RenderObject();
		virtual ~RenderObject();

		//���䶥����ָ�뻺��
		void AllocStreamBuf( UINT nNumber = 1 );

		//�ͷŶ�����ָ�뻺��
		void FreeStreamBuf();

		//�������ָ�뻺��
		void AllocMaterialBuf( UINT nNumber = 1 );

		//�ͷŲ���ָ�뻺��
		void FreeMaterialBuf();

		//�������в���ʹ�ü���
		void AddMaterialRef();

		//�������в���ʹ�ü���
		void DelMaterialRef();

		//������Ⱦ��������
		void AllocRenderParamBuf( UINT nNumParam = 1 );

		//�ͷ���Ⱦ��������
		void FreeRenderParamBuf();

	protected:
		//��Ⱦ����
		virtual void _RenderObj( const RenderParam* pParam, const Matrix4* pNodeMatrix ) = 0;

		//��Ⱦ��������
		virtual void _RenderAnimObj( const RenderParam* pParam, const AnimControl* pAnimControl, const Matrix4* pNodeMatrix ) = 0;
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< RenderObject* >	RenderObjList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
