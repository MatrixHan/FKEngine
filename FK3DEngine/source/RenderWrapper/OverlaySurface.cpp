/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	OverlaySurface
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
	OverlaySurface::OverlaySurface( ZOrderType eZType, OverlaySurface* pZRefOverlay, TextureFilterType eFilterType )
		: mbVisable		(true)
		, mNumVertex	(0)
		, mVertexOffset	(0)
		, mFilterType	(eFilterType)
		, mpVertexPtr	(NULL)
	{
		//����ƽ��ͼ�����
		OverlayManager::mpSingleton->_AddOverlayToList( this, eZType, pZRefOverlay );
	}
	//--------------------------------------------------------------------------------------------------------------
	OverlaySurface::~OverlaySurface()
	{
		//��ƽ��ͼ������б���ɾ��
		OverlayManager::mpSingleton->_DelOverlayFromList( this );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƽ��ͼ��ɼ�״̬
	void FKFastcall OverlaySurface::SetVisable( bool bVisable )
	{
		if( mbVisable && !bVisable )
		{
			//���ٶ������
			OverlayManager::mpSingleton->mNumRenderVer -= mNumVertex;
		}
		else if( !mbVisable && bVisable )
		{
			//���Ӷ������
			OverlayManager::mpSingleton->mNumRenderVer += mNumVertex;
		}

		mbVisable = bVisable;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƽ��ͼ�� Z ˳��
	void FKFastcall OverlaySurface::SetZOrder( ZOrderType eZType, OverlaySurface* pZRefOverlay )
	{
		OverlayManager::mpSingleton->_SetOverlayZOrder( this, eZType, pZRefOverlay );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƽ��ͼ�������������
	void FKFastcall OverlaySurface::SetFilterType( TextureFilterType eFilterType )
	{
		mFilterType = eFilterType;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ƽ��ͼ�񶥵�
	UINT FKFastcall OverlaySurface::_UpdateVertex( OverlayVertex* pVertexBuf, UINT nOffset )
	{
		if( mNumVertex == 0 )
			return 0;

		memcpy( pVertexBuf, mpVertexPtr, sizeof(OverlayVertex) * mNumVertex );

		mVertexOffset = nOffset;

		return mNumVertex;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
