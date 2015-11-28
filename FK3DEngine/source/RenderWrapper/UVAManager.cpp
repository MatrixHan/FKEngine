/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	UVAManager
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
	UVAManager::UVAManager()
		: mpPackFile	(NULL)
	{
		mUVAnimationList.Initialize( 20, 20 );
	}
	//--------------------------------------------------------------------------------------------------------------
	UVAManager::~UVAManager()
	{
		DeleteAllUVAnimation();
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� UVA ����ļ�
	void UVAManager::SetUVAPackFile( FileObject* pPackFile )
	{
		mpPackFile = pPackFile;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���� UV �������ݶ���
	UVAnimation* UVAManager::CreateUVAnimation( LPCSTR szFileName )
	{
		//�� UVA �ļ�
		mpPackFile->Open( szFileName );

		//��ȡ UVA �ļ�ͷ��Ϣ
		UVAHeader sHeader;
		mpPackFile->Read( &sHeader, sizeof(UVAHeader) );

		if( sHeader.nVersion != 0x0100 )
			Except( Exception::ERR_INTERNAL_ERROR, (String)"ָ������� UVA �ļ� '" + szFileName + "' �汾����ȷ��" );

		//�����ڴ�
		DWORD nDateLen = sizeof(UVASegment) * sHeader.nSegment + sizeof(UVAFrame) * sHeader.nFrames + sizeof(UVAnimation);
		BYTE* pMemBuf = (BYTE*)malloc( nDateLen );

		//���� UV �������ݶ���
		UVAnimation* pUVAnimation = (UVAnimation*)pMemBuf;

		*mUVAnimationList.Push() = pUVAnimation;

		//��ȡ���������ݺ�֡����
		pUVAnimation->nSegment = sHeader.nSegment;
		pUVAnimation->nFrames = sHeader.nFrames;
		pUVAnimation->pSegments = (UVASegment*)( pUVAnimation + 1 );
		pUVAnimation->pFrames = (UVAFrame*)( pUVAnimation->pSegments + pUVAnimation->nSegment );

		mpPackFile->Read( pUVAnimation->pSegments, nDateLen - sizeof(UVAnimation) );

		//�ر��ļ�
		mpPackFile->Close();

		return pUVAnimation;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�� UV �������ݶ���
	void UVAManager::DeleteUVAnimation( UVAnimation* pUVAnimation )
	{
		if( pUVAnimation == NULL )
			return;

		UVAnimationList::Iterator it = mUVAnimationList.Begin();
		UVAnimationList::Iterator end = mUVAnimationList.End();
		for(; it!=end; ++it )
		{
			if( *it == pUVAnimation )
			{
				UVAnimation* pUVA = *it;
				free( pUVA );

				mUVAnimationList.Erase( it );
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ������ UV �������ݶ���
	void UVAManager::DeleteAllUVAnimation()
	{
		UVAnimationList::Iterator it = mUVAnimationList.Begin();
		UVAnimationList::Iterator end = mUVAnimationList.End();
		for(; it!=end; ++it )
		{
			if( *it != NULL )
			{
				UVAnimation* pUVA = *it;
				free( pUVA );
			}
		}

		mUVAnimationList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
