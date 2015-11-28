/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9TextureManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderSystem/RenderSystemInsideHeader.h"
#include "../../../Depend/dx9/d3dx9.h"
#include "../../../Depend/dx9/dxerr9.h"
#include "../../include/CommonBase/MemoryMarco.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	D3D9TextureManager::D3D9TextureManager()
	{
		//����Ĭ������ߴ磨���Ӳ���Ƿ�֧�ָóߴ�����
		SetMaxTextureSize( mMaxWidth, mMaxHeight );


		//��ȡӲ��֧���������ߴ�
		mHardMaxWidth = (UINT)D3D9RenderSystem::mD3D9CurCaps.MaxTextureWidth;
		mHardMaxHeight = (UINT)D3D9RenderSystem::mD3D9CurCaps.MaxTextureHeight;

		mMaxWidth = mHardMaxWidth;
		mMaxHeight = mHardMaxHeight;

		mHardMaxVolumeExtent = (UINT)D3D9RenderSystem::mD3D9CurCaps.MaxVolumeExtent;
		mMaxVolumeExtent = mHardMaxVolumeExtent;


		//�ж�Ӳ���Ƿ�֧�ַǱ߳��������
		mbHardCanNotSquare = ( D3D9RenderSystem::mD3D9CurCaps.TextureCaps & D3DPTEXTURECAPS_SQUAREONLY ) == 0;
		mbCanNotSquare = mbHardCanNotSquare;

		//�ж�Ӳ���Ƿ�֧�ַ� 2 �� n ���ݳߴ�Ķ�ά����
		mbHardCanNotPow2 = ( D3D9RenderSystem::mD3D9CurCaps.TextureCaps & D3DPTEXTURECAPS_POW2 ) != 0;
		mbCanNotPow2 = mbHardCanNotPow2;

		//�ж�Ӳ���Ƿ�֧�ַ� 2 �� n ���ݳߴ����������
		mbHardCanNotPow2Cube = ( D3D9RenderSystem::mD3D9CurCaps.TextureCaps & D3DPTEXTURECAPS_CUBEMAP_POW2 ) == 0;
		mbCanNotPow2Cube = mbHardCanNotPow2Cube;

		//�ж�Ӳ���Ƿ�֧�ַ� 2 �� n ���ݳߴ����ά����
		mbHardCanNotPow2Volume = ( D3D9RenderSystem::mD3D9CurCaps.TextureCaps & D3DPTEXTURECAPS_VOLUMEMAP_POW2 ) == 0;
		mbCanNotPow2Volume = mbHardCanNotPow2Volume;


		//��ȡӲ��֧������ѹ����ʽ
		for( UINT i=0; i<5; ++i )
		{
			HRESULT result = D3D9RenderSystem::mpD3D9->CheckDeviceFormat( D3D9RenderSystem::mnAdpter,
				D3D9RenderSystem::mDeviceType, D3D9RenderSystem::mD3Dpp.BackBufferFormat, 0, D3DRTYPE_TEXTURE,
				D3D9TypeGet::GetPixelFormat( (PixelFormat)( PF_DXT1 + i ) ) );

			mbTexCompFormats[i] = ( result == S_OK );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ά����
	Texture* D3D9TextureManager::CreateTexture( UINT nWidth, UINT nHeight, PixelFormat ePixelFormat,
		TextureUsage Type, int nNumLevels )
	{
		//���Ϊѹ�������ʽ
		if( ePixelFormat & PF_COMPRESS_MASK )
		{
			//���ָ������ѹ����ʽ�Ƿ����
			if( !CheckCompressFormat( ePixelFormat ) )
				Except( Exception::ERR_INTERNAL_ERROR, "Ӳ����֧��ָ��������ѹ����ʽ���޷���������" );

			if( !IsPow2( nWidth ) || !IsPow2( nHeight ) )
				Except( Exception::ERR_INTERNAL_ERROR, "�޷������� 2 ���ݳߴ��ѹ������" );
		}

		//��ȡ��ѵ�����ߴ�
		UINT texWidth = 0;
		UINT texHeight = 0;
		GetBestSize( nWidth, nHeight, texWidth, texHeight );

		nNumLevels = (UINT)( ( nNumLevels == -1 ) ? mDefTexLevels : nNumLevels );

		Texture* pTex = new D3D9Texture( texWidth, texHeight, ePixelFormat, nNumLevels, Type );

		*mTextureList.Push() = pTex;
		++mNumTextures;

		return pTex;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������������
	CubeTexture* D3D9TextureManager::CreateCubeTexture( UINT nEdgeLength, PixelFormat ePixelFormat,
		TextureUsage Type, int nNumLevels )
	{
		//���Ϊѹ�������ʽ
		if( ePixelFormat & PF_COMPRESS_MASK )
		{
			//���ָ������ѹ����ʽ�Ƿ����
			if( !CheckCompressFormat( ePixelFormat ) )
				Except( Exception::ERR_INTERNAL_ERROR, "Ӳ����֧��ָ��������ѹ����ʽ���޷���������" );

			if( !IsPow2( nEdgeLength ) )
				Except( Exception::ERR_INTERNAL_ERROR, "�޷������� 2 ���ݳߴ��ѹ������" );
		}

		//��ȡ��ѵ�����ߴ�
		UINT texEdgeLen = GetBestSizeCube( nEdgeLength );

		nNumLevels = (UINT)( ( nNumLevels == -1 ) ? mDefTexLevels : nNumLevels );

		CubeTexture* pTex = new D3D9CubeTexture( texEdgeLen, ePixelFormat, nNumLevels, Type );

		*mTextureList.Push() = pTex;
		++mNumTextures;

		return pTex;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ά����
	VolumeTexture* D3D9TextureManager::CreateVolumeTexture( UINT nWidth, UINT nHeight, UINT nDepth,
		PixelFormat ePixelFormat, TextureUsage Type, int nNumLevels )
	{
		//���Ϊѹ�������ʽ
		if( ePixelFormat & PF_COMPRESS_MASK )
		{
			//���ָ������ѹ����ʽ�Ƿ����
			if( !CheckCompressFormat( ePixelFormat ) )
				Except( Exception::ERR_INTERNAL_ERROR, "Ӳ����֧��ָ��������ѹ����ʽ���޷���������" );

			if( !IsPow2( nWidth ) || !IsPow2( nHeight ) || !IsPow2( nDepth ) )
				Except( Exception::ERR_INTERNAL_ERROR, "�޷������� 2 ���ݳߴ��ѹ������" );
		}

		//��ȡ��ѵ�����ߴ�
		UINT texWidth = 0;
		UINT texHeight = 0;
		UINT texDepth = 0;
		GetBestSizeVolume( nWidth, nHeight, nDepth, texWidth, texHeight, texDepth );

		nNumLevels = (UINT)( ( nNumLevels == -1 ) ? mDefTexLevels : nNumLevels );

		VolumeTexture* pTex = new D3D9VolumeTexture( texWidth, texHeight, texDepth, ePixelFormat, nNumLevels, Type );

		*mTextureList.Push() = pTex;
		++mNumTextures;

		return pTex;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ߴ������ֵ
	void D3D9TextureManager::SetMaxTextureSize( UINT nWidth, UINT nHeight )
	{
		UINT nMaxTexWidth = (UINT)D3D9RenderSystem::mD3D9CurCaps.MaxTextureWidth;
		UINT nMaxTexHeight = (UINT)D3D9RenderSystem::mD3D9CurCaps.MaxTextureHeight;

		mMaxWidth	= FK_MIN( nMaxTexWidth, nWidth );
		mMaxHeight	= FK_MIN( nMaxTexHeight, nHeight );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
