/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	D3D9CubeTexture
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
	D3D9CubeTexture::D3D9CubeTexture( UINT nEdgeLength, PixelFormat ePixelFormat, UINT nNumLevel, TextureUsage Type )
		: CubeTexture		( nEdgeLength, ePixelFormat, nNumLevel, Type )
	{
		mBaseTexture.mpBaseTexture = reinterpret_cast< BaseTexture* >( this );

		HRESULT result = E_FAIL;

		//����������;��ȡ�����ڴ����ʽ�� D3D ������;��ʶ
		DWORD dwUsage = _GetPoolModeAndUsage();

		//��������
		result = D3D9RenderSystem::mpD3D9Device->CreateCubeTexture( mEdgeLength, mNumLevel,
			dwUsage, D3D9TypeGet::GetPixelFormat( mPixelFormat ),
			D3D9TypeGet::GetPoolMode( mPoolMode ), (IDirect3DCubeTexture9**)&mpD3D9Texture, NULL );
		if( FAILED( result ) )
			Except( Exception::ERR_RENDER_API_ERROR, (String)"ʹ�� Direct3D 9 �豸���������������"
			"\nD3D9 ��������" + DXGetErrorDescription9(result) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void D3D9CubeTexture::LockRect( CubeFace eFace, void** ppBuf, UINT* pPitch, RECT* pLockRect, UINT nLevel, bool bDiscardLock )
	{
		//ѡ����������
		DWORD flag = bDiscardLock ? D3DLOCK_DISCARD : D3DLOCK_NOSYSLOCK;

		//��������
		D3DLOCKED_RECT d3dLockRect;
		HRESULT result = reinterpret_cast< IDirect3DCubeTexture9* >( mpD3D9Texture )->LockRect(
			(D3DCUBEMAP_FACES)eFace, nLevel, &d3dLockRect, pLockRect, flag );

		if( FAILED( result ) )
			Except( Exception::ERR_INVALIDPARAMS, (String)"���� Direct3D 9 �����������\nD3D9 ����������" +
			DXGetErrorDescription9(result) );

		*ppBuf = d3dLockRect.pBits;
		*pPitch = d3dLockRect.Pitch;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void D3D9CubeTexture::UnlockRect( CubeFace eFace, UINT nLevel )
	{
		HRESULT result = reinterpret_cast< IDirect3DCubeTexture9* >( mpD3D9Texture )->UnlockRect(
			(D3DCUBEMAP_FACES)eFace, nLevel );

		if( FAILED( result ) )
			Except( Exception::ERR_INVALIDPARAMS, (String)"���� Direct3D 9 �����������\nD3D9 ����������" +
			DXGetErrorDescription9(result) );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Զ����ɶ༶����ӳ��
	void D3D9CubeTexture::GenerateMipSubLevels( TextureFilterType eFilterType )
	{
		_GenerateMipSubLevels( eFilterType );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
