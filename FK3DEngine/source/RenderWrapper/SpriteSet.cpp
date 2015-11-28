/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SpriteSet
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
	//����һ���յľ��鼯
	SpriteSet::SpriteSet( UINT nTexWidth, UINT nTexHeight, PixelFormat ePixelFormat,
		UINT InitSpriteNum, UINT AddSpriteNum, TextureFilterType eFilter )
		: mFilterType	(eFilter)
	{
		//�����Դ���������ߴ�
		UINT TexWidth = 0;
		UINT TexHeight = 0;

		TextureManager* pTexMgr = TextureManager::GetSingletonPtr();
		pTexMgr->GetBestSize( nTexWidth, nTexHeight, TexWidth, TexHeight );

		//��������
		mpTexture = pTexMgr->CreateTexture( TexWidth, TexHeight, ePixelFormat, TU_DYNAMIC, 1 );

		//��ʼ�������б�����
		mSpriteList.Initialize( InitSpriteNum, AddSpriteNum );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����һ�����ļ�����ͼ��ľ��鼯
	SpriteSet::SpriteSet( FileObject* pFile, const char* szName, PixelFormat ePixelFormat,
		UINT InitSpriteNum, UINT AddSpriteNum, TextureFilterType eFilter )
		: mFilterType	(eFilter)
	{
		//��ȡͼ�������
		ImageDecoder* pImgDecoder = &OverlayManager::mpSingleton->mImgDecoder;

		//����ͼƬ
		pImgDecoder->LoadImageFromFile( pFile, szName );

		//��ȡͼ��ߴ�
		UINT Width = 0;
		UINT Height = 0;
		pImgDecoder->ParseHeader();
		pImgDecoder->GetDimension( Width, Height );

		//�����Դ���������ߴ�
		UINT TexWidth = 0;
		UINT TexHeight = 0;

		TextureManager::mpSingleton->GetBestSize( Width, Height, TexWidth, TexHeight );

		//���Ӳ���޷�����ͼƬ�ߴ�������򱨴��������������� UV ����Ĵ���
		//if( Width != TexWidth || Height != TexHeight )
		//	Except( Exception::ERR_INVALIDPARAMS, "�������鼯ʱ����Ӳ���޷�����Ҫ���ͼƬ�ߴ������" );

		//��������
		mpTexture = TextureManager::mpSingleton->CreateTexture( Width, Height, ePixelFormat );

		//��ͼ��������䵽������
		BYTE* pDst = NULL;
		UINT pitch = 0;
		mpTexture->LockRect( (void**)&pDst, &pitch );
		pImgDecoder->Decode( pDst, NULL, NULL, pitch, ePixelFormat );
		mpTexture->UnlockRect();

		//�ر�ͼƬ������
		if( !pImgDecoder->UnloadImage() )
			Except( Exception::ERR_INTERNAL_ERROR, "�رվ�������ͼ�����ݽ�����ʧ�ܡ�" );

		//��ʼ�������б�����
		mSpriteList.Initialize( InitSpriteNum, AddSpriteNum );
	}
	//--------------------------------------------------------------------------------------------------------------
	SpriteSet::~SpriteSet()
	{
		OverlayManager* pOverlayMgr = OverlayManager::GetSingletonPtr();

		//ɾ�����о���
		DeleteAllSprites();

		//�ͷŸ�����
		TextureManager::mpSingleton->DeleteTexture( mpTexture );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����һ�����ڸþ��鼯�ľ�̬����
	Sprite* SpriteSet::CreateSprite( float fLeft, float fTop, float fWidth, float fHeight,
		ZOrderType eZType, OverlaySurface* pZRefOverlay, UV4* pUV, DWORD color )
	{
		Sprite* pSprite = new Sprite( this, fLeft, fTop, fWidth, fHeight,
			eZType, pZRefOverlay, mFilterType, pUV, color );

		//�����������
		*mSpriteList.Push() = pSprite;

		return pSprite;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����һ�����ڸþ��鼯�Ķ�������
	Sprite* SpriteSet::CreateUVASprite( float fLeft, float fTop, float fWidth, float fHeight,
		ZOrderType eZType, OverlaySurface* pZRefOverlay, UVAnimation* pUVAnimation, DWORD color )
	{
		Sprite* pSprite = new Sprite( this, fLeft, fTop, fWidth, fHeight,
			eZType, pZRefOverlay, mFilterType, pUVAnimation, color );

		//�����������
		*mSpriteList.Push() = pSprite;

		return pSprite;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ָ������
	void SpriteSet::DeleteSprite( Sprite* pSprite )
	{
		if( pSprite == NULL )
			return;

		//�����Ӷ�����ɾ��
		SpriteList::Iterator it = mSpriteList.Begin();
		SpriteList::Iterator end = mSpriteList.End();
		for(; it!=end; ++it )
		{
			if( *it == pSprite )
			{
				mSpriteList.Erase( it );
				delete pSprite;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����о���
	void SpriteSet::DeleteAllSprites()
	{
		//�����Ӷ�����ɾ��
		SpriteList::Iterator it = mSpriteList.Begin();
		SpriteList::Iterator end = mSpriteList.End();
		for(; it!=end; ++it )
		{
			if( *it != NULL )
				delete *it;
		}

		mSpriteList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������о�����ʾ״̬
	void SpriteSet::SetAllVisable( bool bVisable )
	{
		SpriteList::Iterator it = mSpriteList.Begin();
		SpriteList::Iterator end = mSpriteList.End();
		for(; it!=end; ++it )
			(*it)->SetVisable( bVisable );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
