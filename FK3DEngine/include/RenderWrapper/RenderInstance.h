/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RenderInstance
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��Ⱦʵ����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class RenderObject;
	class AnimControl;
	class RenderParam;
	class Camera;
	//--------------------------------------------------------------------------------------------------------------

	//Ԥ������Ⱦ�����ȼ�
	const UINT RGP_Background		= 0;		//������������Ⱦ�飩
	const UINT RGP_SkiesEarly		= 10;		//��ǰ��Ⱦ�����
	const UINT RGP_GeometyEarly		= 25;		//��ǰ��Ⱦ������
	const UINT RGP_GeometyDefault	= 50;		//�����壨Ĭ����Ⱦ�飩
	const UINT RGP_GeometyLate		= 75;		//�Ӻ���Ⱦ������
	const UINT RGP_SkiesLate		= 90;		//�Ӻ���Ⱦ�����
	const UINT RGP_Overlays			= 100;		//ƽ��ͼ�������Ⱦ�飩

	const UINT RSGP_Default			= 50;		//Ĭ������Ⱦ�����ȼ�

	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦʵ����
	class FK_DLL RenderInstance
	{
	public:
		RenderObject*		mpRenderObject;		//��Ⱦ����ָ��

		SceneNode*			mpSceneNode;		//�ҽӳ����ڵ�
		AnimControl*		mpAnimControl;		//����������

		UINT				mnGroupPriority;	//��Ⱦ�����ȼ�

		bool				mbVisable;			//ʵ���Ƿ�ɼ�
		bool				mbCullable;			//ʵ���Ƿ�ɱ���ѡ

		float				mfViewDepth;		//�۲����

	public:
		RenderInstance( UINT nGroupPriority = RGP_GeometyDefault );
		RenderInstance( RenderObject* pRenderObj, UINT nGroupPriority = RGP_GeometyDefault );
		virtual ~RenderInstance();

		//��Ⱦ��ʵ��
		void FKFastcall Render( RenderParam* pParam );

		//���¹۲����
		void FKFastcall UpdateViewDepth( const Camera* pCamera );
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< RenderInstance* >	RenderInstList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
