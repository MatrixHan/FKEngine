/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	AnimControlManager
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
	AnimControlManager::AnimControlManager()
		: mNumAnimControl		(0)
	{
		mAnimControlList.Initialize( 20, 20 );
	}
	//--------------------------------------------------------------------------------------------------------------
	AnimControlManager::~AnimControlManager()
	{
		DeleteAllAnimControl();

		mAnimControlList.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����¶���������
	AnimControl* AnimControlManager::CreateAnimControl()
	{
		AnimControl* pAnimControl = new AnimControl();
		*mAnimControlList.Push() = pAnimControl;
		++mNumAnimControl;
		return pAnimControl;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ԭ�ж���������
	void AnimControlManager::DeleteAnimControl( AnimControl* pAnimControl )
	{
		if( pAnimControl == NULL )
			return;

		AnimControlList::Iterator it = mAnimControlList.Begin();
		AnimControlList::Iterator end = mAnimControlList.End();
		for(; it!=end; ++it )
		{
			if( *it == pAnimControl )
			{
				mAnimControlList.Erase( it );
				delete pAnimControl;
				--mNumAnimControl;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����ж���������
	void AnimControlManager::DeleteAllAnimControl()
	{
		AnimControlList::Iterator it = mAnimControlList.Begin();
		AnimControlList::Iterator end = mAnimControlList.End();
		for(; it!=end; ++it )
			SafeDelete( *it );

		mAnimControlList.Clear();
		mNumAnimControl = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡָ������������
	AnimControl* AnimControlManager::GetAnimControl( UINT nIndex )
	{
		if( nIndex >= mNumAnimControl )
			Except( Exception::ERR_INVALIDPARAMS, "ָ��Ҫɾ���Ķ��������������ڡ�" );

		return *( mAnimControlList.Begin() + nIndex );
	}
	//--------------------------------------------------------------------------------------------------------------
	//���¶���֡ʱ��
	void AnimControlManager::UpdateFrameTime( float fFrameTime )
	{
		AnimControlList::Iterator it = mAnimControlList.Begin();
		AnimControlList::Iterator end = mAnimControlList.End();

		for(; it!=end; ++it )
		{
			AnimControl* pAnimControl = *it;
			if( pAnimControl->mbCanPlay )
				pAnimControl->UpdateKeyTime( fFrameTime );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
