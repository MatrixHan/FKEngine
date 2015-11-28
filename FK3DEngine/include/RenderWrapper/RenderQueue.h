/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RenderQueue
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��Ⱦ������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "RenderObject.h"
#include "RenderSubGroup.h"
#include "RenderGroup.h"
#include "RenderInstance.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class Camera;
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ������
	class FK_DLL RenderQueue
	{
	public:
		RenderUnitStack			mRenderUnitStack;		//��Ⱦ��Ԫ��ջ
		RenderGroupStack		mRenderGroupStack;		//��Ⱦ���ջ
		RenderSubGroupStack		mRenderSubGroupStack;	//����Ⱦ���ջ

	public:
		RenderQueue();
		~RenderQueue();

		//�����Ⱦ����
		void ClearRenderQueue();

		//������Ⱦ����
		void SortRenderQueue( const Camera* pCamera );

		//��Ⱦ
		void Render( const Camera* pCamera );

		//�����Ⱦʵ��
		void FKFastcall AddRenderInstance( RenderInstance* pInstance );

		//�����Ⱦʵ���б�
		void FKFastcall AddRenderInstList( RenderInstList* pRenderInstList );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
