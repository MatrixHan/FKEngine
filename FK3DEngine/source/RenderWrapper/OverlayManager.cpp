/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	OverlayManager
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
	OverlayManager::OverlayManager()
		: mRenderWidth		(800)
		, mRenderHeight		(600)
		, mNumRenderVer		(0)
		, mpOverlayPack		(NULL)
		, mpVertexBuf		(NULL)
		, mpVertexDecl		(NULL)
		, mMaxNumVer		(0)
		, mOffsetVer		(0)
	{
		mOverlayList.Initialize( 80, 32 );
		mJointList.Initialize( 10, 10 );
		mSpriteList.Initialize( 60, 20 );
		mSpriteSetList.Initialize( 10, 10 );
		mUVASprite.Initialize( 20, 20 );

		//��ʼ��ƽ��ͼ����Ⱦ����
		mWorldMatrix.SetIdentity();
		mProjMatrix.SetOrthoOffCenterLH( 0.0f, 800.0f, 0.0f, 600.0f, 0.0f, 10.0f );
		mViewMatrix.SetLookAtLH( Vector3( 0.0f, 0.0f, -1.0f ), Vector3::Zero, Vector3( 0.0f, 1.0f, 0.0f ) );

		//��ʼ��ƽ��ͼ����Ⱦ״̬
		mRenderState.mbLighting		= false;
		mRenderState.mbFogEnable	= false;

		mRenderState.SetTransparent();
	}
	//--------------------------------------------------------------------------------------------------------------
	OverlayManager::~OverlayManager()
	{
		//�ͷŶ��㻺�漰��������
		BufferManager::mpSingleton->DelVertexBuffer( mpVertexBuf );
		BufferManager::mpSingleton->DelVertexDeclaration( mpVertexDecl );

		DeleteAllJointSurfaces();
		DeleteAllSpriteSets();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ��ƽ��ͼ�������
	void OverlayManager::Initialize( UINT nMaxNumVer )
	{
		//���㶥�㻺�洴����С
		mMaxNumVer = nMaxNumVer;

		//�������㻺��
		mpVertexBuf = BufferManager::mpSingleton->AddVertexBuffer();
		mpVertexDecl = BufferManager::mpSingleton->AddVertexDeclaration();

		mpVertexBuf->CreateVertexBuffer( sizeof(OverlayVertex), mMaxNumVer, true );

		mpVertexDecl->AddElement( 0, 0, VET_FLOAT3, VEM_DEFAULT, VEU_POSITION, 0 );
		mpVertexDecl->AddElement( 0, 12, VET_ARGBCOLOR, VEM_DEFAULT, VEU_COLOR, 0 );
		mpVertexDecl->AddElement( 0, 16, VET_FLOAT2, VEM_DEFAULT, VEU_TEXCOORD, 0 );

		mpVertexDecl->CreateVertexDeclaration();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¶�������
	void OverlayManager::_UpdateVertexData()
	{
		if( mNumRenderVer == 0 )
			return;

		//�����Ⱦ���������Ƿ񳬹��������
		if( mNumRenderVer > mMaxNumVer )
			Except( Exception::ERR_INTERNAL_ERROR, (String)"Direct3D 9 ƽ��ͼ����Ⱦ�������������˶��㻺���С������ʧ�ܡ�" +
			Misc::FormatString( NULL, "\n��ǰ������Ⱦ������%d    �����Ⱦ����������%d", mNumRenderVer, mMaxNumVer ) );

		//���������������򷵻���ʼλ����������������һ֡ʹ�� D3DLOCK_DISCARD ������
		bool bNoOverwrite = true;

		if( mOffsetVer + mNumRenderVer > mMaxNumVer )
		{
			mOffsetVer = 0;
			bNoOverwrite = false;
		}

		//��������ƽ��ͼ��Ķ�������
		OverlayList::Iterator it = mOverlayList.Begin();
		OverlayList::Iterator end = mOverlayList.End();

		//�������㻺��
		OverlayVertex* pVertexDst = (OverlayVertex*)mpVertexBuf->Lock( mOffsetVer, mNumRenderVer, bNoOverwrite );
		UINT nVerOffset = mOffsetVer;

		for(; it!=end; ++it )
		{
			OverlaySurface* pOverlay = *it;

			//�����ƽ��ͼ��ɼ�
			if( pOverlay->mbVisable )
			{
				//����ƽ��ͼ�񶥵�����
				pOverlay->_ProcessVertex();

				//����ƽ��ͼ�񶥵�����
				UINT nNumVertex = pOverlay->_UpdateVertex( pVertexDst, nVerOffset );
				pVertexDst += nNumVertex;
				nVerOffset += nNumVertex;
			}
		}

		//�������㻺��
		mpVertexBuf->Unlock();
		
		mOffsetVer += mNumRenderVer;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ����ƽ��ͼ��
	void OverlayManager::_RenderAllOverlays()
	{
		//���ö���������������
		RenderSystem::mpSingleton->_SetVertexStream( mpVertexBuf, 0 );
		RenderSystem::mpSingleton->_SetVertexDeclaration( mpVertexDecl );

		//������Ⱦ����
		RenderSystem::mpSingleton->_SetWorldMatrix( &mWorldMatrix );
		RenderSystem::mpSingleton->_SetProjMatrix( &mProjMatrix );
		RenderSystem::mpSingleton->_SetViewMatrix( &mViewMatrix );

		//��������Ѱַ�Ա�����ֽӷ�
		RenderSystem::mpSingleton->_SetTextureAddress( ST_ADDRESSU, TAT_MIRROR, 0 );
		RenderSystem::mpSingleton->_SetTextureAddress( ST_ADDRESSV, TAT_MIRROR, 0 );

		//����ƽ��ͼ����Ⱦ״̬
		RenderSystem::mpSingleton->_SetRenderState( &mRenderState );

		//���� Z ˳����Ⱦ����ƽ��ͼ��
		OverlayList::Iterator it = mOverlayList.Begin();
		OverlayList::Iterator end = mOverlayList.End();

		for(; it!=end; ++it )
		{
			OverlaySurface* pOverlay = *it;

			//�����ƽ��ͼ��ɼ�
			if( pOverlay->mbVisable )
				pOverlay->_RenderOverlay();
		}

		//����������Ⱦ����
		FontManager::mpSingleton->UpdateFont();
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������ļ�
	void OverlayManager::SetOverlayPack( FileObject* pFile )
	{
		mpOverlayPack = pFile;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ⱦ��ߴ�
	void OverlayManager::SetRenderPlaneSize( UINT nWidth, UINT nHeight )
	{
		mRenderWidth = nWidth;
		mRenderHeight = nHeight;
		mProjMatrix.SetOrthoOffCenterLH( 0.0f, (float)nWidth, 0.0f, (float)nHeight, 0.0f, 10.0f );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƽ��ͼ�񶯻�֡��ʱ
	void OverlayManager::_UpdateFrameTime( float fFrameTime )
	{
		UVASpriteList::Iterator it = mUVASprite.Begin();
		UVASpriteList::Iterator end = mUVASprite.End();
		for(; it!=end; ++it )
			(*it)->UpdateFrameTime( fFrameTime );
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ƴ��ͼ��
	JointSurface* OverlayManager::CreateJointSurface( float fLeft, float fTop, float fWidth, float fHeight,
		ZOrderType eZType, OverlaySurface* pZRefOverlay, UINT nTexWidth, UINT nTexHeight, PixelFormat ePixelFormat,
		TextureFilterType eFilter, bool bDynamic, DWORD dwColor )
	{
		//����ƴ��ͼ��
		JointSurface* pJointSurface = new JointSurface( eZType, pZRefOverlay, eFilter );
		*mJointList.Push() = pJointSurface;

		pJointSurface->CreateJointSurface( fLeft, fTop, fWidth, fHeight, nTexWidth, nTexHeight, ePixelFormat,
			bDynamic, dwColor );

		return pJointSurface;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����վ��鼯
	SpriteSet* OverlayManager::CreateSpriteSet( UINT nTexWidth, UINT nTexHeight, PixelFormat ePixelFormat,
		UINT InitSpriteNum, UINT AddSpriteNum, TextureFilterType eFilter )
	{
		SpriteSet* pSpriteSet = new SpriteSet( nTexWidth, nTexHeight, ePixelFormat,
			InitSpriteNum, AddSpriteNum, eFilter );
		*mSpriteSetList.Push() = pSpriteSet;

		return pSpriteSet;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ͼ���ļ�������ƴ��ͼ��
	JointSurface* OverlayManager::LoadJointSurfaceFromFile( float fLeft, float fTop, float fWidth, float fHeight,
		ZOrderType eZType, OverlaySurface* pZRefOverlay, const char* szName, PixelFormat ePixelFormat,
		TextureFilterType eFilter, bool bDynamic, DWORD dwColor )
	{
		//����ƽ��ͼ��
		JointSurface* pJointSurface = new JointSurface( eZType, pZRefOverlay, eFilter );
		*mJointList.Push() = pJointSurface;

		pJointSurface->LoadJointSurfaceFromFile( fLeft, fTop, fWidth, fHeight, mpOverlayPack, szName,
			ePixelFormat, bDynamic, dwColor );

		return pJointSurface;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ͼ���ļ������뾫�鼯
	SpriteSet* OverlayManager::LoadSpriteSetFromFile( const char* szName, PixelFormat ePixelFormat,
		UINT InitSpriteNum, UINT AddSpriteNum, TextureFilterType eFilter )
	{
		SpriteSet* pSpriteSet = new SpriteSet( mpOverlayPack, szName, ePixelFormat,
			InitSpriteNum, AddSpriteNum, eFilter );
		*mSpriteSetList.Push() = pSpriteSet;

		return pSpriteSet;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ƴ��ͼ��
	void OverlayManager::DeleteJointSurface( JointSurface* pJointSurface )
	{
		if( pJointSurface == NULL )
			return;

		JointList::Iterator it = mJointList.Begin();
		JointList::Iterator end = mJointList.End();
		for(; it!=end; ++it )
		{
			if( *it == pJointSurface )
			{
				mJointList.Erase( it );
				delete *it;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����鼯
	void OverlayManager::DeleteSpriteSet( SpriteSet* pSpriteSet )
	{
		if( pSpriteSet == NULL )
			return;

		SpriteSetList::Iterator it = mSpriteSetList.Begin();
		SpriteSetList::Iterator end = mSpriteSetList.End();
		for(; it!=end; ++it )
		{
			if( *it == pSpriteSet )
			{
				mSpriteSetList.Erase(it);
				delete pSpriteSet;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ������ƴ��ͼ��
	void OverlayManager::DeleteAllJointSurfaces()
	{
		JointList::Iterator it = mJointList.Begin();
		JointList::Iterator end = mJointList.End();
		for(; it!=end; ++it )
		{
			if( *it != NULL )
				delete *it;
		}

		mJointList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����о��鼯
	void OverlayManager::DeleteAllSpriteSets()
	{
		SpriteSetList::Iterator it = mSpriteSetList.Begin();
		SpriteSetList::Iterator end = mSpriteSetList.End();
		for(; it!=end; ++it )
		{
			if( *it != NULL )
				delete *it;
		}

		mSpriteSetList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ���ƽ��ͼ��ָ��
	OverlaySurface* FKFastcall OverlayManager::GetTopmostOverlay()
	{
		if( mOverlayList.Size() == 0 )
			return NULL;

		return *mOverlayList.Back();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ƽ��ͼ����뵽�����б���
	void FKFastcall OverlayManager::_AddOverlayToList( OverlaySurface* pOverlay,
		ZOrderType eZType, OverlaySurface* pZRefOverlay )
	{
		switch (eZType)
		{
			//���ϲ㣨�����Ⱦ��
		case ZOT_Top:
			{
				*mOverlayList.Push() = pOverlay;
				return;
			}
			//���²㣨������Ⱦ��
		case ZOT_Bottom:
			{
				*mOverlayList.Insert( (unsigned int)0 ) = pOverlay;
				return;
			}
			//ָ��ƽ��ͼ��֮�ϣ�����Ⱦ��
		case ZOT_Upon:
			{
				//���ָ����׼ƽ��ͼ�������һ��ƽ��ͼ��
				OverlayList::Iterator back = mOverlayList.Back();
				if( pZRefOverlay == *back )
				{
					*mOverlayList.Push() = pOverlay;
					return;
				}
				else
				{
					OverlayList::Iterator beg = mOverlayList.Begin();
					OverlayList::Iterator it = --back;
					for(; it>=beg; --it )
					{
						if( *it == pZRefOverlay )
						{
							*mOverlayList.Insert( ++it ) = pOverlay;
							return;
						}
					}
				}
				break;
			}
			//ָ��ƽ��ͼ��֮�£�����Ⱦ��
		case ZOT_Below:
			{
				OverlayList::Iterator it = mOverlayList.Begin();
				OverlayList::Iterator end = mOverlayList.End();
				for(; it!=end; ++it )
				{
					if( *it == pZRefOverlay )
					{
						*mOverlayList.Insert( it ) = pOverlay;
						return;
					}
				}
				break;
			}
		}

		//Except( Exception::ERR_INVALIDPARAMS, "ָ����ƽ��ͼ�� Z ˳������޷���������б�" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ƽ��ͼ��ӹ����б���ɾ��
	void FKFastcall OverlayManager::_DelOverlayFromList( OverlaySurface* pOverlay )
	{
		OverlayList::Iterator it = mOverlayList.Begin();
		OverlayList::Iterator end = mOverlayList.End();
		for(; it!=end; ++it )
		{
			if( *it == pOverlay )
			{
				//���ٶ������
				if( pOverlay->mbVisable )
					mNumRenderVer -= pOverlay->mNumVertex;

				mOverlayList.Erase( it );
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƽ��ͼ�� Z ˳��
	void FKFastcall OverlayManager::_SetOverlayZOrder( OverlaySurface* pOverlay,
		ZOrderType eZType, OverlaySurface* pZRefOverlay )
	{
		//����ƽ��ͼ����б���ɾ��
		OverlayList::Iterator it = mOverlayList.Begin();
		OverlayList::Iterator end = mOverlayList.End();
		for(; it!=end; ++it )
		{
			if( *it == pOverlay )
			{
				mOverlayList.Erase( it );

				//���䰴���µ� Z ˳������б�
				_AddOverlayToList( pOverlay, eZType, pZRefOverlay );
				return;
			}
		}

		//Except( Exception::ERR_INVALIDPARAMS, "ָ����ƽ��ͼ�񲻴��ڣ��޷������� Z ˳��" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�� UV �������������뵽�����б���
	void FKFastcall OverlayManager::_AddUVASpriteToList( UVASprite* pUVASprite )
	{
		if( pUVASprite == NULL )
			return;

		*mUVASprite.Push() = pUVASprite;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�� UV �����������ӹ����б���ɾ��
	void FKFastcall OverlayManager::_DelUVASpriteFromList( UVASprite* pUVASprite )
	{
		if( pUVASprite == NULL )
			return;

		UVASpriteList::Iterator it = mUVASprite.Begin();
		UVASpriteList::Iterator end = mUVASprite.End();
		for(; it!=end; ++it )
		{
			if( *it == pUVASprite )
			{
				mUVASprite.Erase( it );
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
