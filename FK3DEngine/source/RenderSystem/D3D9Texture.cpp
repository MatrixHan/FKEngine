/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9Texture
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
	D3D9Texture::D3D9Texture( UINT nWidth, UINT nHeight, PixelFormat ePixelFormat, UINT nNumLevel, TextureUsage Type )
		: Texture			( nWidth, nHeight, ePixelFormat, nNumLevel, Type )
	{
		mBaseTexture.mpBaseTexture = reinterpret_cast< BaseTexture* >( this );

		HRESULT result = E_FAIL;

		//����������;��ȡ�����ڴ����ʽ�� D3D ������;��ʶ
		DWORD dwUsage = mBaseTexture._GetPoolModeAndUsage();

		//��������
		result = D3D9RenderSystem::mpD3D9Device->CreateTexture( mWidth, mHeight, mNumLevel,
			dwUsage, D3D9TypeGet::GetPixelFormat( mPixelFormat ),
			D3D9TypeGet::GetPoolMode( mPoolMode ), (IDirect3DTexture9**)&mBaseTexture.mpD3D9Texture, NULL );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"ʹ�� Direct3D 9 �豸�����������"
			"\nD3D9 ��������" + DXGetErrorDescription9(result) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void D3D9Texture::LockRect( void** ppBuf, UINT* pPitch, RECT* pLockRect, UINT nLevel, bool bDiscardLock )
	{
		//ѡ����������
		DWORD flag = bDiscardLock ? D3DLOCK_DISCARD : D3DLOCK_NOSYSLOCK;

		//��������
		D3DLOCKED_RECT d3dLockRect;
		HRESULT result = reinterpret_cast< IDirect3DTexture9* >( mBaseTexture.mpD3D9Texture )->LockRect(
			nLevel, &d3dLockRect, pLockRect, flag );

		if( FAILED( result ) )
			Except( Exception::ERR_INVALIDPARAMS, (String)"���� Direct3D 9 �������\nD3D9 ����������" +
			DXGetErrorDescription9(result) );

		*ppBuf = d3dLockRect.pBits;
		*pPitch = d3dLockRect.Pitch;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void D3D9Texture::UnlockRect( UINT nLevel )
	{
		HRESULT result = reinterpret_cast< IDirect3DTexture9* >( mBaseTexture.mpD3D9Texture )->UnlockRect( nLevel );

		if( FAILED( result ) )
			Except( Exception::ERR_INVALIDPARAMS, (String)"���� Direct3D 9 �������\nD3D9 ����������" +
			DXGetErrorDescription9(result) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Զ����ɶ༶����ӳ��
	void D3D9Texture::GenerateMipSubLevels( TextureFilterType eFilterType )
	{
		mBaseTexture._GenerateMipSubLevels( eFilterType );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
