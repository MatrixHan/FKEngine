/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Material
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "RenderState.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class TextureState;
	//--------------------------------------------------------------------------------------------------------------
	//������
	class FK_DLL Material
	{
	public:
		char				mName[32];			//��������

		ColorValue			mDiffuse;			//����ɫ
		ColorValue			mAmbient;			//����ɫ
		ColorValue			mSpecular;			//�߹�ɫ
		ColorValue			mEmissive;			//����ɫ
		float				mPower;				//�߹�����ֵ

		RenderState			mRenderState;		//������Ⱦ״̬
		TextureState*		mppTextureState[8];	//��������״̬

		UINT				mRefCount;			//���ü���

	public:
		Material();
		~Material();

		//����/���ٲ������ü���
		void AddRef();
		bool DelRef();

		//����/��ȡ��������
		void SetName( const char* pName );
		const char* GetName();

		//����/��ȡ����ɫ
		void SetDiffuseColor( const ColorValue& Diffuse );
		ColorValue& GetDiffuseColor();

		//����/��ȡ����ɫ
		void SetAmbientColor( const ColorValue& Ambient );
		ColorValue& GetAmbientColor();

		//����/��ȡ�߹�ɫ
		void SetSpecularColor( const ColorValue& Specular );
		ColorValue& GetSpecularColor();

		//����/��ȡ����ɫ
		void SetEmissiveColor( const ColorValue& Emissive );
		ColorValue& GetEmissiveColor();

		//����/��ȡ�߹�����ֵ
		void SetPower( const float Power );
		float GetPower();

		//��������״̬
		TextureState* CreateTextureState( UINT nStage = 0 );

		//ɾ������״̬
		void DeleteTextureState( UINT nStage = 0 );

		//ɾ����������״̬
		void DeleteAllTextureState();

		//��ȡ����״̬
		TextureState* GetTextureState( UINT nState = 0 );

		//Ӧ����������״̬
		void ApplyTextureState();
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Material* >		MaterialList;
	typedef HashMap< Material* >	MaterialMap;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
