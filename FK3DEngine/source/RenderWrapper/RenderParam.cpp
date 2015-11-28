/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RenderParam
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
	//���ݲ���������Ⱦ
	void FKFastcall RenderParam::RenderByParam() const
	{
		//�жϻ�������
		switch (eDrawType)
		{
		case RenderParam::DT_Basic:
			{
				RenderSystem::mpSingleton->_RenderVertex( sBasicParam.ePrimType, sBasicParam.nVerOffset,
					sBasicParam.nMinIndex, sBasicParam.nVerCount, sBasicParam.nIndexOffset, sBasicParam.nPrimCount );
				return;
			}
		case RenderParam::DT_TPatch:
			{
				return;
			}
		case RenderParam::DT_RPatch:
			{
				return;
			}
		default:
			Except( Exception::ERR_INTERNAL_ERROR, "�������Ⱦ�����������͡�" );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�Ƿ���Ҫ���н�����Ⱦ
	bool FKFastcall RenderParam::NeedRender() const
	{
		//�жϻ�������
		switch (eDrawType)
		{
		case RenderParam::DT_Basic:		return ( sBasicParam.nPrimCount != 0 );
		case RenderParam::DT_TPatch:	return ( sTPatchParam.nPrimCount != 0 );
		case RenderParam::DT_RPatch:	return ( sRPatchParam.nPrimCount != 0 );
		default:
			Except( Exception::ERR_INTERNAL_ERROR, "�������Ⱦ�����������͡�" );
		}

		return false;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
