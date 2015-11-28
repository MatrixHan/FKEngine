/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RenderSubGroup
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
	//������Ⱦ��Ԫ
	FKInline void SwapRenderUnit( RenderUnit* pUnitA, RenderUnit* pUnitB )
	{
		static RenderUnit sTmpUnit;

		sTmpUnit.pRenderInstance	= pUnitA->pRenderInstance;
		sTmpUnit.pRenderParam		= pUnitA->pRenderParam;

		pUnitA->pRenderInstance		= pUnitB->pRenderInstance;
		pUnitA->pRenderParam		= pUnitB->pRenderParam;

		pUnitB->pRenderInstance		= sTmpUnit.pRenderInstance;
		pUnitB->pRenderParam		= sTmpUnit.pRenderParam;
	}
	//--------------------------------------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------------------------------
	//��������Ⱦ��
	void RenderSubGroup::SortRenderSubGroup( const Camera* pCamera )
	{
		//�����в�͸����Ⱦ��Ԫ������ǰ��
		RenderUnit* pTransFindStart = mpHeadRenderUnit;
		RenderUnit* pSolidFindStart = mpRearRenderUnit;

		for(;;)
		{
			//���ҵ�һ��͸����Ⱦ��Ԫ
			RenderUnit* pFirstTransUnit = _FindFirstTransUnit( pTransFindStart );
			if( pFirstTransUnit == NULL )
			{
				mpHeadSolidUnit = mpHeadRenderUnit;
				mpRearSolidUnit = mpRearRenderUnit;

				mpHeadTransUnit = NULL;
				mpRearTransUnit = NULL;

				break;
			}

			//�������һ����͸����Ⱦ��Ԫ
			RenderUnit* pLastSolidUnit = _FindLastSolidUnit( pSolidFindStart );
			if( pLastSolidUnit == NULL )
			{
				mpHeadSolidUnit = NULL;
				mpRearSolidUnit = NULL;

				mpHeadTransUnit = mpHeadRenderUnit;
				mpRearTransUnit = mpRearRenderUnit;

				break;
			}

			if( pLastSolidUnit > pFirstTransUnit )
			{
				mpHeadSolidUnit = mpHeadRenderUnit;
				mpRearSolidUnit = pLastSolidUnit;

				mpHeadTransUnit = pFirstTransUnit;
				mpRearTransUnit = mpRearRenderUnit;
			}

			SwapRenderUnit( pFirstTransUnit, pLastSolidUnit );

			pTransFindStart = pFirstTransUnit + 1;
			pSolidFindStart = pLastSolidUnit - 1;
		}

		_SortSolidRenderUnit();				//���²�͸����Ⱦ��Ԫ
		_SortTransRenderUnit( pCamera );	//����͸����Ⱦ��Ԫ
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ǰ͸����Ⱦ��Ԫ
	FKInline RenderUnit* RenderSubGroup::_FindFirstTransUnit( RenderUnit* pStartUnit )
	{
		for(; pStartUnit<=mpRearRenderUnit; ++pStartUnit )
		{
			if( pStartUnit->pRenderParam->pMaterial->mRenderState.IsTransparent() )
				return pStartUnit;
		}

		return NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ĩ��͸����Ⱦ��Ԫ
	FKInline RenderUnit* RenderSubGroup::_FindLastSolidUnit( RenderUnit* pStartUnit )
	{
		for(; pStartUnit>=mpHeadRenderUnit; --pStartUnit )
		{
			if( !pStartUnit->pRenderParam->pMaterial->mRenderState.IsTransparent() )
				return pStartUnit;
		}

		return NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����͸����Ⱦ��Ԫ
	FKInline void RenderSubGroup::_SortSolidRenderUnit()
	{
		if( mpHeadSolidUnit == NULL )
			return;

		//���ݲ���������Ⱦ��Ԫ��ѡ�����򷨣�
		RenderUnit* pUnit = mpHeadSolidUnit;
		UINT nNumUnit = (UINT)( mpRearSolidUnit - mpHeadSolidUnit ) + 1;

		for( UINT i=0; i<nNumUnit; ++i )
		{
			int nMinIndex = i;

			for( UINT j=i; j<nNumUnit; ++j )
				if( pUnit[nMinIndex].pRenderParam->pMaterial > pUnit[j].pRenderParam->pMaterial )
					nMinIndex = j;

			SwapRenderUnit( pUnit + i, pUnit + nMinIndex );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//����͸����Ⱦ��Ԫ
	FKInline void RenderSubGroup::_SortTransRenderUnit( const Camera* pCamera )
	{
		if( mpHeadTransUnit == NULL )
			return;

		RenderUnit* pUnit = mpHeadTransUnit;
		UINT nNumUnit = (UINT)( mpRearTransUnit - mpHeadTransUnit ) + 1;

		//���ݴ�Զ�����Ĺ۲����������Ⱦ��Ԫ��ѡ�����򷨣�
		for( UINT i=0; i<nNumUnit; ++i )
		{
			//����͸����Ⱦ��Ԫ�۲����
			pUnit[i].pRenderInstance->UpdateViewDepth( pCamera );

			int nMinIndex = i;

			for( UINT j=i; j<nNumUnit; ++j )
				if( pUnit[nMinIndex].pRenderInstance->mfViewDepth < pUnit[j].pRenderInstance->mfViewDepth )
					nMinIndex = j;

			SwapRenderUnit( pUnit + i, pUnit + nMinIndex );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
