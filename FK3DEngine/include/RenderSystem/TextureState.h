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

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class Texture;
	//--------------------------------------------------------------------------------------------------------------
	//����״̬��
	class FK_DLL TextureState
	{
	public:
		Texture*				mpTexture;		//����

		TextureFilterType		mFilterMag;		//�Ŵ������������
		TextureFilterType		mFilterMin;		//��С�����������
		TextureFilterType		mFilterMip;		//�༶�����������

		TextureAddressType		mAddressU;		//���� U ����Ѱַ����
		TextureAddressType		mAddressV;		//���� V ����Ѱַ����
		TextureAddressType		mAddressW;		//���� W ����Ѱַ����

		TextureOperation		mColorOp;		//������ɫ��������
		TextureArgument			mColorArg1;		//������ɫ�������� 1
		TextureArgument			mColorArg2;		//������ɫ�������� 2

		TextureOperation		mAlphaOp;		//���� Alpha ��������
		TextureArgument			mAlphaArg1;		//���� Alpha �������� 1
		TextureArgument			mAlphaArg2;		//���� Alpha �������� 2

	public:
		TextureState();
		~TextureState();

		//����/��ȡ����
		void SetTexture( Texture* pTexture );
		Texture* GetTexture();

		//����/��ȡ�����������
		void SetTextureFilter( SamplerType eSamplerType, TextureFilterType eFilterType );
		TextureFilterType GetTextureFilter( SamplerType eSamplerType );

		//����/��ȡ����Ѱַ����
		void SetTextureAddress( SamplerType eSamplerType, TextureAddressType eAddressType );
		TextureAddressType GetTextureAddress( SamplerType eSamplerType );

		//����/��ȡ�����������״̬
		void SetTextureOperation( TextureStateType eStateType, TextureOperation eOperationType );
		TextureOperation GetTextureOperation( TextureStateType eStateType );

		//����/��ȡ�����������״̬
		void SetTextureArgument( TextureStateType eStateType, TextureArgument eArgumentType );
		TextureArgument GetTextureArgument( TextureStateType eStateType );
	};
	//--------------------------------------------------------------------------------------------------------------
};

//==================================================================================================================
