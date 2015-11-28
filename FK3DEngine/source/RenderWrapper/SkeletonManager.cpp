/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SkeletonManager
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
	SkeletonManager::SkeletonManager()
		: mNumSkeleton		(0)
	{
		mSkeletonList.Initialize( 20, 20 );
	}
	//--------------------------------------------------------------------------------------------------------------
	SkeletonManager::~SkeletonManager()
	{
		DeleteAllSkeleton();

		mSkeletonList.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����¹���
	Skeleton* SkeletonManager::CreateSkeleton( UINT nNumKey, float fIntervalTime )
	{
		Skeleton* pSkeleton = new Skeleton( nNumKey, fIntervalTime );
		*mSkeletonList.Push() = pSkeleton;
		++mNumSkeleton;
		return pSkeleton;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ԭ�й���
	void SkeletonManager::DeleteSkeleton( Skeleton* pSkeleton )
	{
		if( pSkeleton == NULL )
			return;

		SkeletonList::Iterator it = mSkeletonList.Begin();
		SkeletonList::Iterator end = mSkeletonList.End();
		for(; it!=end; ++it )
		{
			if( *it == pSkeleton )
			{
				mSkeletonList.Erase( it );
				delete pSkeleton;
				--mNumSkeleton;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����й���
	void SkeletonManager::DeleteAllSkeleton()
	{
		SkeletonList::Iterator it = mSkeletonList.Begin();
		SkeletonList::Iterator end = mSkeletonList.End();
		for(; it!=end; ++it )
			SafeDelete( *it );

		mSkeletonList.Clear();
		mNumSkeleton = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡָ������
	Skeleton* SkeletonManager::GetSkeleton( UINT nIndex )
	{
		if( nIndex >= mNumSkeleton )
			Except( Exception::ERR_INVALIDPARAMS, "ָ��Ҫɾ���Ĺ��������ڡ�" );

		return *( mSkeletonList.Begin() + nIndex );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
