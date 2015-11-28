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

#include "../../include/RenderSystem/RenderSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	RenderState::RenderState()
		: mFillMode				(FM_SOLID)				//���ģʽ
		, mShadeMode			(SM_GOURAUD)			//��Ӱģʽ
		, mCullMode				(CM_ANTICLOCKWISE)		//��ѡ����
		, mbLighting			(true)					//�Ƿ����ƹ�
		, mbSpecular			(false)					//�Ƿ����߹�
		, mbFogEnable			(false)					//�Ƿ�����
		, mFogMode				(FOG_LINEAR)			//��ģʽ
		, mFogColor				(0xFFFFFFFF)			//����ɫ
		, mFogStart				(1.0f)					//����ʼλ��
		, mFogEnd				(1000.0f)				//������λ��
		, mFogDensity			(1.0f)					//��Ũ��
		, mbDepthTestEnable		(true)					//�Ƿ�����Ȳ���
		, mbDepthWriteEnable	(true)					//�Ƿ������д��
		, mbAlphaEnable			(false)					//�Ƿ��� Alpha ���
		, mbAlphaTestEnable		(false)					//�Ƿ��� Alpha ����
		, mDepthCompareFun		(CMP_LESSEQUAL)			//��ȱȽϺ���
		, mAlphaCompareFun		(CMP_GREATER)			// Alpha �ȽϺ���
		, mdwAlphaRefValue		(0x0)					// Alpha ���Բ���ֵ
		, mSrcBlendFactor		(BF_ONE)				//��Դ��ɫ�������
		, mDestBlendFactor		(BF_ZERO)				//Ŀ����ɫ�������
		, mSrcAlphaBlendFactor	(BF_ONE)				//��Դ Alpha ֵ�������
		, mDestAlphaBlendFactor	(BF_ZERO)				//Ŀ�� Alpha ֵ�������
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������
	RenderState& RenderState::operator = ( const RenderState& refRenderState )
	{
		memcpy( this, &refRenderState, sizeof(RenderState) );
		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	FKInline bool RenderState::operator == ( const RenderState& refRenderState ) const
	{
		return ( 0 == memcmp( this, &refRenderState, sizeof(RenderState) ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	FKInline bool RenderState::operator != ( const RenderState& refRenderState ) const
	{
		return !( 0 == memcmp( this, &refRenderState, sizeof(RenderState) ) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ж��Ƿ�Ϊ͸����Ⱦ״̬
	bool FKFastcall RenderState::IsTransparent() const
	{
		return ( mDestBlendFactor != BF_ZERO && !mbDepthTestEnable && !mbDepthWriteEnable );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����Ϊ��͸����Ⱦ״̬
	void FKFastcall RenderState::SetOpacity()
	{
		mSrcBlendFactor		= BF_ONE;
		mDestBlendFactor	= BF_ZERO;

		mbDepthTestEnable	= true;
		mbDepthWriteEnable	= true;
		mbAlphaEnable		= false;
		mbAlphaTestEnable	= false;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����Ϊ��͸����Ⱦ״̬
	void FKFastcall RenderState::SetTransparent( CompareFunction eCmpFun, DWORD dwRefAlpha )
	{
		mSrcBlendFactor		= BF_SRCALPHA;
		mDestBlendFactor	= BF_INVSRCALPHA;

		mbDepthTestEnable	= false;
		mbDepthWriteEnable	= false;
		mbAlphaEnable		= true;
		mbAlphaTestEnable	= true;

		mAlphaCompareFun	= eCmpFun;
		mdwAlphaRefValue	= dwRefAlpha;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����Ϊ͸��������Ⱦ״̬
	void FKFastcall RenderState::SetAlphaMask( CompareFunction eCmpFun, DWORD dwRefAlpha )
	{
		mSrcBlendFactor		= BF_SRCALPHA;
		mDestBlendFactor	= BF_INVSRCALPHA;

		mbDepthTestEnable	= true;
		mbDepthWriteEnable	= true;
		mbAlphaEnable		= true;
		mbAlphaTestEnable	= true;

		mAlphaCompareFun	= eCmpFun;
		mdwAlphaRefValue	= dwRefAlpha;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����Ϊ��������Ⱦ״̬
	void FKFastcall RenderState::SetMultiLayers( CompareFunction eCmpFun, DWORD dwRefAlpha )
	{
		mSrcBlendFactor		= BF_SRCALPHA;
		mDestBlendFactor	= BF_INVSRCALPHA;

		mbAlphaEnable		= true;
		mbAlphaTestEnable	= true;

		mAlphaCompareFun	= eCmpFun;
		mdwAlphaRefValue	= dwRefAlpha;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
