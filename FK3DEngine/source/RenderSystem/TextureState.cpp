/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	TextureState
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
	TextureState::TextureState()
		: mpTexture			(NULL)				//����
		, mFilterMag		(TFT_LINEAR)		//�Ŵ������������
		, mFilterMin		(TFT_LINEAR)		//��С�����������
		, mFilterMip		(TFT_LINEAR)		//�༶�����������
		, mAddressU			(TAT_WRAP)			//���� U ����Ѱַ����
		, mAddressV			(TAT_WRAP)			//���� V ����Ѱַ����
		, mAddressW			(TAT_WRAP)			//���� W ����Ѱַ����
		, mColorOp			(TO_MODULATE)		//������ɫ��������
		, mColorArg1		(TA_TEXTURE)		//������ɫ�������� 2
		, mColorArg2		(TA_CURRENT)		//������ɫ�������� 2
		, mAlphaOp			(TO_SELECTARG1)		//���� Alpha ��������
		, mAlphaArg1		(TA_TEXTURE)		//���� Alpha �������� 1
		, mAlphaArg2		(TA_CURRENT)		//���� Alpha �������� 2
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	TextureState::~TextureState()
	{
		if( mpTexture != NULL )
			TextureManager::mpSingleton->DeleteTexture( mpTexture );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void TextureState::SetTexture( Texture* pTexture )
	{
		mpTexture = pTexture;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ����
	Texture* TextureState::GetTexture()
	{
		return mpTexture;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������������
	void TextureState::SetTextureFilter( SamplerType eSamplerType, TextureFilterType eFilterType )
	{
		switch (eSamplerType)
		{
		case ST_MAGFILTER:		mFilterMag = eFilterType;		return;
		case ST_MINFILTER:		mFilterMin = eFilterType;		return;
		case ST_MIPFILTER:		mFilterMip = eFilterType;		return;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "ȡ�����ʹ����޷������������������Ⱦ״̬��" );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�����������
	TextureFilterType TextureState::GetTextureFilter( SamplerType eSamplerType )
	{
		switch (eSamplerType)
		{
		case ST_MAGFILTER:		return mFilterMag;
		case ST_MINFILTER:		return mFilterMin;
		case ST_MIPFILTER:		return mFilterMip;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "ȡ�����ʹ����޷���ȡ�������������Ⱦ״̬��" );
		}

		return (TextureFilterType)0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������Ѱַ����
	void TextureState::SetTextureAddress( SamplerType eSamplerType, TextureAddressType eAddressType )
	{
		switch (eSamplerType)
		{
		case ST_MAGFILTER:		mAddressU = eAddressType;		return;
		case ST_MINFILTER:		mAddressV = eAddressType;		return;
		case ST_MIPFILTER:		mAddressW = eAddressType;		return;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "ȡ�����ʹ����޷���������Ѱַ������Ⱦ״̬��" );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ����Ѱַ����
	TextureAddressType TextureState::GetTextureAddress( SamplerType eSamplerType )
	{
		switch (eSamplerType)
		{
		case ST_MAGFILTER:		return mAddressU;
		case ST_MINFILTER:		return mAddressV;
		case ST_MIPFILTER:		return mAddressW;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "ȡ�����ʹ����޷���ȡ����Ѱַ������Ⱦ״̬��" );
		}

		return (TextureAddressType)0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������������״̬
	void TextureState::SetTextureOperation( TextureStateType eStateType, TextureOperation eOperationType )
	{
		switch (eStateType)
		{
		case TST_COLOROP:		mColorOp = eOperationType;		return;
		case TST_ALPHAOP:		mAlphaOp = eOperationType;		return;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "����״̬���ʹ����޷����������������״̬��" );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�����������״̬
	TextureOperation TextureState::GetTextureOperation( TextureStateType eStateType )
	{
		switch (eStateType)
		{
		case TST_COLOROP:		return mColorOp;
		case TST_ALPHAOP:		return mAlphaOp;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "����״̬���ʹ����޷���ȡ�����������״̬��" );
		}

		return (TextureOperation)0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������������״̬
	void TextureState::SetTextureArgument( TextureStateType eStateType, TextureArgument eArgumentType )
	{
		switch (eStateType)
		{
		case TST_COLORARG1:		mColorArg1 = eArgumentType;		return;
		case TST_COLORARG2:		mColorArg2 = eArgumentType;		return;
		case TST_ALPHAARG1:		mAlphaArg1 = eArgumentType;		return;
		case TST_ALPHAARG2:		mAlphaArg2 = eArgumentType;		return;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "����״̬���ʹ����޷����������������״̬��" );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�����������״̬
	TextureArgument TextureState::GetTextureArgument( TextureStateType eStateType )
	{
		switch (eStateType)
		{
		case TST_COLORARG1:		return mColorArg1;
		case TST_COLORARG2:		return mColorArg2;
		case TST_ALPHAARG1:		return mAlphaArg1;
		case TST_ALPHAARG2:		return mAlphaArg2;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "����״̬���ʹ����޷���ȡ�����������״̬��" );
		}

		return (TextureArgument)0;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
