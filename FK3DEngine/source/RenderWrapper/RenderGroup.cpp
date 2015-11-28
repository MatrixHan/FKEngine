/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RenderGroup
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
	//������Ⱦ��
	void RenderGroup::SortRenderGroup( RenderSubGroupStack* pRenderSubGroupStack, const Camera* pCamera )
	{
		if( mpHeadRenderUnit == NULL )
			return;

		//��������Ⱦ�����ȼ�������Ⱦ��Ԫ��ѡ�����򷨣�
		RenderUnit* pUnit = mpHeadRenderUnit;
		UINT nNumUnit = (UINT)( mpRearRenderUnit - mpHeadRenderUnit ) + 1;

		for( UINT i=0; i<nNumUnit; ++i )
		{
			int nMinIndex = i;

			for( UINT j=i; j<nNumUnit; ++j )
				if( pUnit[nMinIndex].pRenderParam->nPriority > pUnit[j].pRenderParam->nPriority )
					nMinIndex = j;

			SwapRenderUnit( pUnit + i, pUnit + nMinIndex );
		}

		//��������Ⱦ��
		RenderSubGroup* pSubGroup = pRenderSubGroupStack->Push();

		pSubGroup->mnPriority = pUnit->pRenderParam->nPriority;
		pSubGroup->mpHeadRenderUnit = pUnit;
		pSubGroup->mpRearRenderUnit = pUnit;

		for( UINT i=1; i<nNumUnit; ++i )
		{
			if( pUnit[i].pRenderParam->nPriority == pSubGroup->mnPriority )
			{
				pSubGroup->mpRearRenderUnit += 1;
			}
			else
			{
				pSubGroup->SortRenderSubGroup( pCamera );

				pSubGroup = pRenderSubGroupStack->Push();

				pSubGroup->mnPriority = pUnit->pRenderParam->nPriority;
				pSubGroup->mpHeadRenderUnit = pUnit + i;
				pSubGroup->mpRearRenderUnit = pUnit + i;
			}
		}

		pSubGroup->SortRenderSubGroup( pCamera );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
