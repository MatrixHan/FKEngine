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
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderWrapper/RenderWrapperInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	Material::Material()
		: mDiffuse			( ColorValue::White )
		, mAmbient			( ColorValue::White )
		, mSpecular			( ColorValue::Black )
		, mEmissive			( ColorValue::Black )
		, mPower			(10.0f)
		, mRefCount			(0)
	{
		memset( mName, 0, sizeof(char) * 32 );
		memset( mppTextureState, 0, sizeof(TextureState*) * 8 );
	}
	//--------------------------------------------------------------------------------------------------------------
	Material::~Material()
	{
		DeleteAllTextureState();
	}
	//--------------------------------------------------------------------------------------------------------------
	//����/���ٲ������ü���
	void Material::AddRef()
	{
		++mRefCount;
	}
	//--------------------------------------------------------------------------------------------------------------
	bool Material::DelRef()
	{
		--mRefCount;

		//�������Ϊ�����Զ�ɾ���ò���
		if( mRefCount == 0 )
		{
			MaterialManager::mpSingleton->DeleteMaterial( this );
			return true;
		}

		return false;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����/��ȡ��������
	void Material::SetName( const char* pName )
	{
		size_t nStrLen = strlen( pName );
		if( nStrLen >= 32 )
			Except( Exception::ERR_NAME_TOO_LONG, "ָ���Ĳ������ƹ�����" );

		memcpy( mName, pName, nStrLen + 1 );
	}
	//--------------------------------------------------------------------------------------------------------------
	const char* Material::GetName()
	{
		return mName;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����/��ȡ����ɫ
	void Material::SetDiffuseColor( const ColorValue& Diffuse )
	{
		mDiffuse = Diffuse;
	}
	//--------------------------------------------------------------------------------------------------------------
	ColorValue& Material::GetDiffuseColor()
	{
		return mDiffuse;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����/��ȡ����ɫ
	void Material::SetAmbientColor( const ColorValue& Ambient )
	{
		mAmbient = Ambient;
	}
	//--------------------------------------------------------------------------------------------------------------
	ColorValue& Material::GetAmbientColor()
	{
		return mAmbient;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����/��ȡ�߹�ɫ
	void Material::SetSpecularColor( const ColorValue& Specular )
	{
		mSpecular = Specular;
	}
	//--------------------------------------------------------------------------------------------------------------
	ColorValue& Material::GetSpecularColor()
	{
		return mSpecular;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����/��ȡ����ɫ
	void Material::SetEmissiveColor( const ColorValue& Emissive )
	{
		mEmissive = Emissive;
	}
	//--------------------------------------------------------------------------------------------------------------
	ColorValue& Material::GetEmissiveColor()
	{
		return mEmissive;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����/��ȡ�߹�����ֵ
	void Material::SetPower( const float Power )
	{
		mPower = Power;
	}
	//--------------------------------------------------------------------------------------------------------------
	float Material::GetPower()
	{
		return mPower;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������״̬
	TextureState* Material::CreateTextureState( UINT nStage )
	{
		if( mppTextureState[nStage] != NULL )
			Except( Exception::ERR_INVALIDPARAMS, "ָ��������״̬�Ѿ����ڣ��޷��ظ�������" );

		if( nStage >= RenderSystem::mpSingleton->mMaxTextureNum )
			Except( Exception::ERR_INTERNAL_ERROR, "�޷�����֧�ֵ�����״̬����ޣ���������״̬ʧ�ܡ�" );

		mppTextureState[nStage] = new TextureState;

		return mppTextureState[nStage];
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ������״̬
	void Material::DeleteTextureState( UINT nStage )
	{
		SafeDelete( mppTextureState[nStage] );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ����������״̬
	void Material::DeleteAllTextureState()
	{
		for( UINT i=0; i<8; ++i )
			SafeDelete( mppTextureState[i] );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ����״̬
	TextureState* Material::GetTextureState( UINT nState )
	{
		return mppTextureState[nState];
	}
	//--------------------------------------------------------------------------------------------------------------
	//Ӧ����������״̬
	void Material::ApplyTextureState()
	{
		for( UINT i=0; i<RenderSystem::mpSingleton->mMaxTextureNum; ++i )
		{
			if( mppTextureState[i] != NULL )
			{
				RenderSystem::mpSingleton->_SetTextureState( mppTextureState[i], i );
				RenderSystem::mpSingleton->_SetTexture( mppTextureState[i]->mpTexture, i );
			}
			else
			{
				RenderSystem::mpSingleton->_DisableTextureState( i );
				RenderSystem::mpSingleton->_SetTexture( NULL, i );
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
