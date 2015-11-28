/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RenderState
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
	//��Ⱦ״̬��
	class FK_DLL RenderState
	{
	public:
		FillMode			mFillMode;				//���ģʽ
		ShadeMode			mShadeMode;				//��Ӱģʽ
		CullMode			mCullMode;				//��ѡ����

		bool				mbLighting;				//�Ƿ�������
		bool				mbSpecular;				//�Ƿ����߹�
		bool				mbFogEnable;			//�Ƿ�����

		FogMode				mFogMode;				//��ģʽ
		DWORD				mFogColor;				//����ɫ
		float				mFogStart;				//����ʼλ��
		float				mFogEnd;				//������λ��
		float				mFogDensity;			//��Ũ��

		bool				mbDepthTestEnable;		//�Ƿ�����Ȳ���
		bool				mbDepthWriteEnable;		//�Ƿ������д��

		bool				mbAlphaEnable;			//�Ƿ��� Alpha ���
		bool				mbAlphaTestEnable;		//�Ƿ��� Alpha ����

		CompareFunction		mDepthCompareFun;		//��ȱȽϺ���
		CompareFunction		mAlphaCompareFun;		// Alpha �ȽϺ���

		DWORD				mdwAlphaRefValue;		// Alpha ���Բ���ֵ

		BlendFactor			mSrcBlendFactor;		//��Դ��ɫ�������
		BlendFactor			mDestBlendFactor;		//Ŀ����ɫ�������
		BlendFactor			mSrcAlphaBlendFactor;	//��Դ Alpha ֵ�������
		BlendFactor			mDestAlphaBlendFactor;	//Ŀ�� Alpha ֵ�������

	public:
		RenderState();

		//����������
		RenderState& operator = ( const RenderState& refRenderState );
		FKInline bool operator == ( const RenderState& refRenderState ) const;
		FKInline bool operator != ( const RenderState& refRenderState ) const;

		//�ж��Ƿ�Ϊ͸����Ⱦ״̬
		bool FKFastcall IsTransparent() const;

		//����Ϊ��͸����Ⱦ״̬
		void FKFastcall SetOpacity();

		//����Ϊ��͸����Ⱦ״̬
		void FKFastcall SetTransparent( CompareFunction eCmpFun = CMP_GREATER, DWORD dwRefAlpha = 0x0 );

		//����Ϊ͸��������Ⱦ״̬
		void FKFastcall SetAlphaMask( CompareFunction eCmpFun = CMP_GREATEREQUAL, DWORD dwRefAlpha = 0xAA );

		//����Ϊ��������Ⱦ״̬
		void FKFastcall SetMultiLayers( CompareFunction eCmpFun = CMP_GREATER, DWORD dwRefAlpha = 0x0 );
	};
	//--------------------------------------------------------------------------------------------------------------
};

//==================================================================================================================
