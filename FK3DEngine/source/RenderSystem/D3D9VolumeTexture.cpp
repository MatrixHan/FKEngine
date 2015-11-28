/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9VolumeTexture
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
	D3D9VolumeTexture::D3D9VolumeTexture( UINT nWidth, UINT nHeight, UINT nDepth,
		PixelFormat ePixelFormat, UINT nNumLevel, TextureUsage Type )
		: VolumeTexture		( nWidth, nHeight, nDepth, ePixelFormat, nNumLevel, Type )
	{
		mBaseTexture.mpBaseTexture = reinterpret_cast< BaseTexture* >( this );

		HRESULT result = E_FAIL;

		//����������;��ȡ�����ڴ����ʽ�� D3D ������;��ʶ
		DWORD dwUsage = _GetPoolModeAndUsage();

		//��������
		result = D3D9RenderSystem::mpD3D9Device->CreateVolumeTexture( mWidth, mHeight, mDepth, mNumLevel,
			dwUsage, D3D9TypeGet::GetPixelFormat( mPixelFormat ),
			D3D9TypeGet::GetPoolMode( mPoolMode ), (IDirect3DVolumeTexture9**)&mpD3D9Texture, NULL );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"ʹ�� Direct3D 9 �豸������ά�������"
			"\nD3D9 ��������" + DXGetErrorDescription9(result) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void D3D9VolumeTexture::LockBox( LockBox3* pLocked, Box3* pLockBox, UINT nLevel, bool bDiscardLock )
	{
		//ѡ����������
		DWORD flag = bDiscardLock ? D3DLOCK_DISCARD : D3DLOCK_NOSYSLOCK;

		//��������
		HRESULT result = reinterpret_cast< IDirect3DVolumeTexture9* >( mpD3D9Texture )->LockBox(
			nLevel, (D3DLOCKED_BOX*)pLocked, (D3DBOX*)pLockBox, flag );

		if( FAILED( result ) )
			Except( Exception::ERR_INVALIDPARAMS, (String)"���� Direct3D 9 ��ά�������\nD3D9 ����������" +
			DXGetErrorDescription9(result) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void D3D9VolumeTexture::UnlockBox( UINT nLevel )
	{
		HRESULT result = reinterpret_cast< IDirect3DVolumeTexture9* >( mpD3D9Texture )->UnlockBox( nLevel );

		if( FAILED( result ) )
			Except( Exception::ERR_INVALIDPARAMS, (String)"���� Direct3D 9 ��ά�������\nD3D9 ����������" +
			DXGetErrorDescription9(result) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Զ����ɶ༶����ӳ��
	void D3D9VolumeTexture::GenerateMipSubLevels( TextureFilterType eFilterType )
	{
		_GenerateMipSubLevels( eFilterType );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
