/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Skeleton
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
	Skeleton::Skeleton( UINT nNumKey, float fIntervalTime )
		: mNumKey			(nNumKey)
		, mIntervalTime		(fIntervalTime)
		, mNumBones			(0)
	{
		mBoneMatList.Initialize( 10, 10 );
	}
	//--------------------------------------------------------------------------------------------------------------
	Skeleton::~Skeleton()
	{
		DeleteAllBones();

		mBoneMatList.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ͷ
	void Skeleton::CreateBone( const Matrix4* pBoneKeyMatrix )
	{
		Matrix4Stack* pMatStack = new Matrix4Stack;
		*mBoneMatList.Push() = pMatStack;

		pMatStack->Initialize( mNumKey, 100 );
		memcpy( pMatStack->Begin(), pBoneKeyMatrix, sizeof(Matrix4) * mNumKey );

		++mNumBones;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ����ͷ
	void Skeleton::DeleteBone( UINT nBoneIndex )
	{
		if( nBoneIndex >= mNumBones )
			Except( Exception::ERR_INVALIDPARAMS, "ָ��Ҫɾ���Ĺ�ͷ�����ڡ�" );

		Matrix4Stack* pMatStack = *( mBoneMatList.Begin() + nBoneIndex );
		mBoneMatList.Erase( nBoneIndex );

		delete pMatStack;

		--mNumBones;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����й�ͷ
	void Skeleton::DeleteAllBones()
	{
		BoneMatList::Iterator it = mBoneMatList.Begin();
		BoneMatList::Iterator end = mBoneMatList.End();
		for(; it!=end; ++it )
			SafeDelete( *it );

		mBoneMatList.Clear();

		mNumBones = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����֡����
	void Skeleton::SetKeyNumber( UINT nNumKey )
	{
		mNumKey = nNumKey;

		BoneMatList::Iterator it = mBoneMatList.Begin();
		BoneMatList::Iterator end = mBoneMatList.End();
		for(; it!=end; ++it )
			(*it)->Resize( nNumKey );
	}
	//--------------------------------------------------------------------------------------------------------------
	//����ͣ��ʱ��
	void Skeleton::SetIntervalTime( float fIntervalTime )
	{
		mIntervalTime = fIntervalTime;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
