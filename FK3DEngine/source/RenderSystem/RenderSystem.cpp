/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RenderSystem
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderSystem/RenderSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	bool		RenderSystem::mbSoftVerProc			= false;		//�Ƿ�����ʹ��������㴦��ʽ
	DWORD		RenderSystem::mdwDepthMode			= D3DZB_TRUE;	//ʹ����Ȼ���ģʽ
	DWORD		RenderSystem::mdwMaxBlendNum		= 0;			//Ӳ��֧�ֶ�����������������
	DWORD		RenderSystem::mdwMaxBlendIndex		= 0;			//Ӳ��֧�ֶ�������������������

	UINT		RenderSystem::mnAdpter				= 0;			//���������
	UINT		RenderSystem::mRenderWidth			= 0;			//��Ⱦ������
	UINT		RenderSystem::mRenderHeight			= 0;			//��Ⱦ������

	PixelFormat	RenderSystem::mDisplayFormat		= PF_UNKNOWN;	//��ʾ��ʽ
	UINT		RenderSystem::mDisplayColorDepth	= 0;			//��ʾ��ʽɫ���ֽ���
	UINT		RenderSystem::mDisplayAlphaBits		= 0;			//��ʾ��ʽ Alpha ֵλ��

	DWORD		RenderSystem::mMaxTextureNum		= 0;			//�����������
	DWORD		RenderSystem::mMaxStreamNum			= 0;			//��󶥵�������

	UINT		RenderSystem::mNumTriangle			= 0;			//��һ֡��Ⱦ��������

	//--------------------------------------------------------------------------------------------------------------
	RenderSystem::RenderSystem( const RenderSystemType eType )
		: mbRun				(false)
		, mpRenderWindow	(NULL)
		, mpConfig			(NULL)
		, mpViewport		(NULL)
		, mSystemType		(eType)
		, mbUseSwapSrcRect	(false)
		, mbUseSwapDestRect	(false)
		, mhSwapDestWindow	(NULL)
	{
		mViewportList.Initialize( 3, 10 );
		mFreeLightIndex.Initialize( 8, 8 );

		memset( mppLastTexture, 0, sizeof(Texture*) * 8 );
		memset( mppLastVB, 0, sizeof(VertexBuffer) * 8 );

		mpLastIB = NULL;
		mpLastVD = NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	RenderSystem::~RenderSystem()
	{
		DeleteAllViewport();
		mViewportList.Clear();
		mFreeLightIndex.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ӿ�
	Viewport* RenderSystem::CreateViewport( DWORD dwLeft, DWORD dwTop, DWORD dwWidth, DWORD dwHeight,
		float fMinZ, float fMaxZ )
	{
		//���Ϊ����ģʽ������Ⱦ���ֵ��Χ�Ƿ��� 0.0f - 1.0f ֮�䡣
#ifdef _DEBUG
		if( fMinZ > 1.0f || fMinZ < 0.0f || fMaxZ > 1.0f || fMaxZ < 0.0f || fMinZ > fMaxZ )
		{
			Except( Exception::ERR_INVALIDPARAMS, "�ӿ���Ⱦ���ֵ��Χ������ 0.0f �� 1.0f ֮�䡣" );
			return NULL;
		}
#endif

		Viewport* pViewport = new Viewport( dwLeft, dwTop, dwWidth, dwHeight, fMinZ, fMaxZ );
		*mViewportList.Push() = pViewport;

		return pViewport;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ���ӿ�
	void RenderSystem::DeleteViewport( Viewport* pViewport )
	{
		if( pViewport == NULL )
			return;

		ViewportList::Iterator it = mViewportList.Begin();
		ViewportList::Iterator end = mViewportList.End();
		for(; it!=end; ++it )
		{
			if( *it == pViewport )
			{
				mViewportList.Erase( it );
				delete pViewport;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�������ӿ�
	void RenderSystem::DeleteAllViewport()
	{
		ViewportList::Iterator it = mViewportList.Begin();
		ViewportList::Iterator end = mViewportList.End();
		for(; it!=end; ++it )
		{
			if( *it != NULL )
				delete *it;
		}

		mViewportList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����ӿ�����
	UINT RenderSystem::GetNumViewport()
	{
		return mViewportList.Size();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ǰ�����ӿ�
	Viewport* RenderSystem::GetActiveViewport()
	{
		return mpViewport;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������Ⱦҳ�潻������
	void RenderSystem::SetSwapParam( RECT* pSrcRect, RECT* pDestRect, HWND hDestWindow )
	{
		if( !mpConfig->bWindowed )
			Except( Exception::ERR_INVALIDPARAMS, "�Ǵ�����Ⱦģʽ������������Ⱦҳ�潻��������" );

		if( pSrcRect != NULL )
		{
			mbUseSwapSrcRect = true;
			memcpy( &mSwapSrcRect, pSrcRect, sizeof(RECT) );
		}
		else
		{
			mbUseSwapSrcRect = false;
		}

		if( pDestRect != NULL )
		{
			mbUseSwapDestRect = true;
			memcpy( &mSwapDestRect, pDestRect, sizeof(RECT) );
		}
		else
		{
			mbUseSwapDestRect = false;
		}

		mhSwapDestWindow = hDestWindow;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
