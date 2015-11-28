/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	MaterialManager
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
	MaterialManager::MaterialManager()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	MaterialManager::~MaterialManager()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ�����ʹ�����
	void MaterialManager::Initialize( UINT nNumMaterial )
	{
		mMaterialMap.Initialize( nNumMaterial );
		mMaterialList.Initialize( nNumMaterial, 100 );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷŲ��ʹ�����
	void MaterialManager::Release()
	{
		DeleteAllMaterial();

		mMaterialMap.Release();
		mMaterialList.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����µĲ���
	Material* MaterialManager::CreateMaterial( const char* szMaterialName )
	{
		//�����²���
		Material* pMaterial = new Material;
		pMaterial->SetName( szMaterialName );

		//�����ʼ����б�
		if( !mMaterialMap.Add( pMaterial, szMaterialName ) )
		{
			SafeDelete( pMaterial );
			Except( Exception::ERR_INVALIDPARAMS, (String)"ָ������Ϊ '" + szMaterialName +
				"' �Ĳ����Ѿ����ڡ�" );
		}

		*mMaterialList.Push() = pMaterial;

		return pMaterial;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����������������
	Material* MaterialManager::CreateMaterial( const char* szTexFileName, MaterialType eType )
	{
		//�����²���
		Material* pMaterial = new Material;
		
		switch (eType)
		{
		case Opacity:			pMaterial->mRenderState.SetOpacity();		break;
		case Transparent:		pMaterial->mRenderState.SetTransparent();	break;
		case AlphaMask:			pMaterial->mRenderState.SetAlphaMask();		break;
		}

		//���Ʋ�������
		pMaterial->mAmbient		= ColorValue::White;
		pMaterial->mDiffuse		= ColorValue::White;
		pMaterial->mSpecular	= ColorValue::Black;
		pMaterial->mEmissive	= ColorValue::Black;
		pMaterial->mPower		= 0.0f;

		if( szTexFileName != NULL )
		{
			//���������������ò�����
			size_t nLen = strlen( szTexFileName );
			memcpy( pMaterial->mName, szTexFileName, nLen );
			pMaterial->mName[nLen] = '\0';

			//���ݵ�ǰ����ʾ��ɫ��ʽ�Ͳ�������ѡ�����ʵ��������ʽ
			PixelFormat eTexFormat;
			if( eType == Opacity )
				eTexFormat = ( RenderSystem::mDisplayColorDepth > 2 ) ? RenderSystem::mDisplayFormat : PF_R5G6B5;
			else
				eTexFormat = PF_A8R8G8B8;

			//������������
			Texture* pTexture = TextureManager::mpSingleton->LoadFromFile( szTexFileName, 0, eTexFormat );
			TextureState* pTextureState = pMaterial->CreateTextureState();
			pTextureState->SetTexture( pTexture );
		}

		//�����ʼ����б�
		if( !mMaterialMap.Add( pMaterial, pMaterial->mName ) )
		{
			SafeDelete( pMaterial );
			Except( Exception::ERR_INVALIDPARAMS, (String)"ָ������Ϊ '" + pMaterial->mName +
				"' �Ĳ����Ѿ����ڡ�" );
		}

		*mMaterialList.Push() = pMaterial;

		return pMaterial;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ݲ������ݴ����µĲ���
	Material* MaterialManager::CreateMaterial( const MaterialData* pMaterialData )
	{
		//�����²���
		Material* pMaterial = new Material;

		switch (pMaterialData->eType)
		{
		case Opacity:			pMaterial->mRenderState.SetOpacity();		break;
		case Transparent:		pMaterial->mRenderState.SetTransparent();	break;
		case AlphaMask:			pMaterial->mRenderState.SetAlphaMask();		break;
		}

		//���Ʋ�������
		pMaterial->mAmbient		= pMaterialData->Ambient;
		pMaterial->mDiffuse		= pMaterialData->Diffuse;
		pMaterial->mSpecular	= pMaterialData->Specular;
		pMaterial->mEmissive	= pMaterialData->Emissive;
		pMaterial->mPower		= pMaterialData->Power;

		memcpy( pMaterial->mName, pMaterialData->szMaterialName, 32 );

		//������������
		if( pMaterialData->bHaveTexture )
		{
			//���ݵ�ǰ����ʾ��ɫ��ʽ�Ͳ�������ѡ�����ʵ��������ʽ
			PixelFormat eTexFormat;
			if( pMaterialData->eType == Opacity )
				eTexFormat = ( RenderSystem::mDisplayColorDepth > 2 ) ? RenderSystem::mDisplayFormat : PF_R5G6B5;
			else
				eTexFormat = PF_A8R8G8B8;

			//������������
			Texture* pTexture = TextureManager::mpSingleton->LoadFromFile( pMaterialData->szTexFileName, 0, eTexFormat );
			TextureState* pTextureState = pMaterial->CreateTextureState();
			pTextureState->SetTexture( pTexture );
		}

		//�����ʼ����б�
		if( !mMaterialMap.Add( pMaterial, pMaterialData->szMaterialName ) )
		{
			SafeDelete( pMaterial );
			Except( Exception::ERR_INVALIDPARAMS, (String)"ָ������Ϊ '" + pMaterialData->szMaterialName +
				"' �Ĳ����Ѿ����ڡ�" );
		}

		*mMaterialList.Push() = pMaterial;

		return pMaterial;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ԭ�в���
	void MaterialManager::DeleteMaterial( Material* pMaterial )
	{
		if( pMaterial == NULL )
			return;

		//���б���ɾ������
		mMaterialMap.Del( pMaterial->mName );

		MaterialList::Iterator it = mMaterialList.Begin();
		MaterialList::Iterator end = mMaterialList.End();
		for(; it!=end; ++it )
		{
			if( *it == pMaterial )
			{
				mMaterialList.Erase( it );
				delete pMaterial;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����в���
	void MaterialManager::DeleteAllMaterial()
	{
		MaterialList::Iterator it = mMaterialList.Begin();
		MaterialList::Iterator end = mMaterialList.End();
		for(; it!=end; ++it )
			SafeDelete( *it );

		mMaterialList.Clear();
		mMaterialMap.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������ƻ�ȡ����
	FKInline Material* MaterialManager::GetMaterial( const char* szMaterialName )
	{
		return *mMaterialMap.Find( szMaterialName );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��������
	FKInline UINT MaterialManager::GetMaterialNum()
	{
		return mMaterialList.Size();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ݲ�������ѡ�����ʵ��������ʽ
	PixelFormat MaterialManager::GetBestTextureFormat( MaterialType eMatType, PixelFormat eOrgPixelFormat )
	{
		//��ȡ��ɫ��ʽ�ֽ���
		UINT nColorDepth = Misc::GetColorDepth( eOrgPixelFormat );

		switch (eMatType)
		{
		case Opacity:
			return ( nColorDepth > 2 ) ? eOrgPixelFormat : PF_R5G6B5;
		case AlphaMask:
		case Transparent:
			return PF_A8R8G8B8;
		default:
			Except( Exception::ERR_INVALIDPARAMS, "�ڸ��ݲ�������ѡ�������ʽʱ�������˴���Ĳ������͡�" );
		}

		return PF_UNKNOWN;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
