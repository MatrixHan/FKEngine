/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	TriMesh
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
	TriMesh::TriMesh()
		: mNumBone			(0)
		, mpBoneIndex		(NULL)
		, mpSkeleton		(NULL)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	TriMesh::~TriMesh()
	{
		SafeFree( mpBoneIndex );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����崴������
	Geometry* TriMesh::Creator()
	{
		return new TriMesh;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������� Z �ᷴ�����ƽ��
	void TriMesh::MakePlane3( float fXMin, float fXMax, float fYMin, float fYMax, float fZ,
		bool bHaveUV, bool bHaveNormal, Material* pMaterial )
	{
		const UINT nNumVertex = 4;
		const UINT nNumIndex = 4;

		//�������񶥵���
		BuildMeshStream( nNumVertex, nNumIndex, bHaveUV, bHaveNormal );

		//�����㻺��
		UINT nNumVertexBuffer = 0;

		Vector3* pPos = (Vector3*)mppVertexBuffer[nNumVertexBuffer]->Lock( 0, 0 );

		pPos->x = fXMin;		pPos->y = fYMin;		pPos->z = fZ;			++pPos;
		pPos->x = fXMin;		pPos->y = fYMax;		pPos->z = fZ;			++pPos;
		pPos->x = fXMax;		pPos->y = fYMax;		pPos->z = fZ;			++pPos;
		pPos->x = fXMax;		pPos->y = fYMin;		pPos->z = fZ;			++pPos;

		mppVertexBuffer[nNumVertexBuffer++]->Unlock();

		if( bHaveNormal )
		{
			Vector3* pNormal = (Vector3*)mppVertexBuffer[nNumVertexBuffer]->Lock( 0, 0 );

			pNormal->x = 0.0f;		pNormal->y = 0.0f;		pNormal->z = -1.0f;		++pNormal;
			pNormal->x = 0.0f;		pNormal->y = 0.0f;		pNormal->z = -1.0f;		++pNormal;
			pNormal->x = 0.0f;		pNormal->y = 0.0f;		pNormal->z = -1.0f;		++pNormal;
			pNormal->x = 0.0f;		pNormal->y = 0.0f;		pNormal->z = -1.0f;		++pNormal;

			mppVertexBuffer[nNumVertexBuffer++]->Unlock();
		}

		if( bHaveUV )
		{
			float* pUV = (float*)mppVertexBuffer[nNumVertexBuffer]->Lock( 0, 0 );
			
			*pUV++ = 0.0f;		*pUV++ = 1.0f;
			*pUV++ = 0.0f;		*pUV++ = 0.0f;
			*pUV++ = 1.0f;		*pUV++ = 0.0f;
			*pUV++ = 1.0f;		*pUV++ = 1.0f;

			mppVertexBuffer[nNumVertexBuffer++]->Unlock();
		}

		//������������
		WORD* pIndex = (WORD*)mpIndexBuffer->Lock( 0, 0 );
		*pIndex++ = 0;		*pIndex++ = 1;		*pIndex++ = 2;		*pIndex++ = 3;
		mpIndexBuffer->Unlock();


		//���ð�Χ��
		mBoundBox.SetMaxMin( fXMax, fYMax, fZ + 1.0f, fXMin, fYMin, fZ - 1.0f );

		//������Ⱦ����
		AllocRenderParamBuf();
		mpRenderParam->eDrawType	= RenderParam::DT_Basic;

		mpRenderParam->sBasicParam.ePrimType	= PT_TRIANGLE_FAN;
		mpRenderParam->sBasicParam.nVerOffset	= 0;
		mpRenderParam->sBasicParam.nMinIndex	= 0;
		mpRenderParam->sBasicParam.nIndexOffset	= 0;
		mpRenderParam->sBasicParam.nVerCount	= 4;
		mpRenderParam->sBasicParam.nPrimCount	= 2;

		//���ò���
		if( pMaterial != NULL )
		{
			AllocMaterialBuf();
			mppMaterial[0] = pMaterial;
			mpRenderParam->pMaterial = pMaterial;
			pMaterial->AddRef();
		}
		else
		{
			mpRenderParam->pMaterial = NULL;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������������
	void TriMesh::MakeBox( const Vector3& vCenter, float fSideLen, UINT nSegment,
		bool bHaveUV, bool bHaveNormal, Material* pMaterial )
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//������������
	void TriMesh::MakeSphere( const Vector3& vCenter, float fRadius, UINT nRing, UINT nSegment,
		bool bHaveUV, bool bHaveNormal, Material* pMaterial )
	{
		//���뾶
		if( fRadius <= 0.0f )
			Except( Exception::ERR_INVALIDPARAMS, "������������İ뾶��������㡣" );

		//�������嶥������
		UINT nNumVertex = ( nRing + 1 ) * ( nSegment + 1 );
		UINT nNumIndex = 2 * nRing * ( nSegment + 1 );

		//�������񶥵���
		BuildMeshStream( nNumVertex, nNumIndex, bHaveUV, bHaveNormal );

		//�����㻺��
		UINT nNumVertexBuffer = 0;

		Vector3* pPos = (Vector3*)mppVertexBuffer[nNumVertexBuffer++]->Lock( 0, 0 );

		Vector3* pNormal = NULL;
		if( bHaveNormal )
			pNormal = (Vector3*)mppVertexBuffer[nNumVertexBuffer++]->Lock( 0, 0 );

		float* pUV = NULL;
		if( bHaveUV )
			pUV = (float*)mppVertexBuffer[nNumVertexBuffer++]->Lock( 0, 0 );

		//������������
		WORD* pIndex = (WORD*)mpIndexBuffer->Lock( 0, 0 );


		//����Ƕ�
		float fRingAngle = FK_PI / (float)nRing;
		float fSegmentAngle = FK_PI * 2.0f / (float)nSegment;

		float r = 0.0f;
		float y = 0.0f;
		float x = 0.0f;
		float z = 0.0f;

		//���ɴ�ֱһ�������ѭ��
		WORD wIndex = 0;
		for( UINT ring=0; ring<nRing+1; ++ring )
		{
			SinCos( (float)ring * fRingAngle, &r, &y );

			//����ˮƽ��һ�ζ����ѭ��			
			for( UINT seg=0; seg<nSegment+1; ++seg )
			{
				SinCos( (float)seg * fSegmentAngle, &x, &z );

				pPos->x = x * r	* fRadius + vCenter.x;
				pPos->y = y		* fRadius + vCenter.y;
				pPos->z = z * r	* fRadius + vCenter.z;
				++pPos;

				if( bHaveNormal )
				{
					pNormal->x = x;
					pNormal->y = y;
					pNormal->z = z;
					pNormal->Normalize();
					++pNormal;
				}

				if( bHaveUV )
				{
					*pUV++ = 1.0f - (float)seg / (float)nSegment;
					*pUV++ = (float)ring / (float)nRing;
				}

				if( ring != nRing )
				{
					*pIndex++ = wIndex;
					*pIndex++ = wIndex + (WORD)( nSegment + 1 );
					++wIndex;
				}
			}
		}

		//������������
		mpIndexBuffer->Unlock();

		//�������㻺��
		for( UINT i=0; i<mNumVertexBuffer; ++i )
			mppVertexBuffer[i]->Unlock();

		//���ð�Χ��
		mBoundBox.SetMaxMin( fRadius, fRadius, fRadius, -fRadius, -fRadius, -fRadius );

		//������Ⱦ����
		AllocRenderParamBuf();
		mpRenderParam->eDrawType	= RenderParam::DT_Basic;

		mpRenderParam->sBasicParam.ePrimType	= PT_TRIANGLE_STRIP;
		mpRenderParam->sBasicParam.nVerOffset	= 0;
		mpRenderParam->sBasicParam.nMinIndex	= 0;
		mpRenderParam->sBasicParam.nIndexOffset	= 0;
		mpRenderParam->sBasicParam.nVerCount	= nNumVertex;
		mpRenderParam->sBasicParam.nPrimCount	= nNumIndex - 2;

		//���ò���
		if( pMaterial != NULL )
		{
			AllocMaterialBuf();
			mppMaterial[0] = pMaterial;
			mpRenderParam->pMaterial = pMaterial;
			pMaterial->AddRef();
		}
		else
		{
			mpRenderParam->pMaterial = NULL;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ù�����ͷ��������
	void TriMesh::SetBoneIndex( UINT* pBoneIndex, UINT nNumBone )
	{
		mNumBone = nNumBone;

		SafeFree( mpBoneIndex );

		//������������
		size_t BufLen = sizeof(UINT) * nNumBone;
		mpBoneIndex = (UINT*)malloc( BufLen );
		if( mpBoneIndex == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "����������Ƥ��ͷ�������ݻ���ʧ�ܡ�" );

		memcpy( mpBoneIndex, pBoneIndex, BufLen );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void TriMesh::SetSkeleton( Skeleton* pSkeleton )
	{
		//���ʹ����Ƥ��ͷ����������ָ�������Ĺ�ͷ����
		if( mNumBone > pSkeleton->mNumBones )
			Except( Exception::ERR_INVALIDPARAMS, "�������Ƥ��ͷ������ָ�������Ĺ�ͷ������ƥ�䣬�޷�������" );

		mpSkeleton = pSkeleton;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ����
	void TriMesh::_RenderObj( const RenderParam* pParam, const Matrix4* pNodeMatrix )
	{
		//�����������
		RenderSystem::mpSingleton->_SetWorldMatrix( pNodeMatrix );

		//�����Ҫ������㴦�������
		if( mbSoftVertexProc )
			RenderSystem::mpSingleton->_SetSoftwareVertexProcess( true );

		//������Ⱦ������Ⱦ
		pParam->RenderByParam();

		if( mbSoftVertexProc )
			RenderSystem::mpSingleton->_SetSoftwareVertexProcess( false );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ��������
	void TriMesh::_RenderAnimObj( const RenderParam* pParam, const AnimControl* pAnimControl, const Matrix4* pNodeMatrix )
	{
		//���ö�������

		//��Ⱦ������ʱ����
		static Matrix4 TmpRenderMat;

		//��ȡ������ͷ�����б�
		Matrix4Stack** ppMatStack = mpSkeleton->mBoneMatList.Begin();

		for( UINT i=0; i<mNumBone; ++i )
		{
			//��ȡ��ǰ֡��ǰ��ͷ�ľ���
			Matrix4* pBoneMat = ppMatStack[ mpBoneIndex[i] ]->Begin() + pAnimControl->mCurKey;

			//�����ͳ����ڵ������
			Mat4TransMat4( &TmpRenderMat, pBoneMat, pNodeMatrix );

			//���þ���
			RenderSystem::mpSingleton->_SetWorldMatrix( &TmpRenderMat, i );
		}


		//�����Ҫ������㴦�������
		if( mbSoftVertexProc )
			RenderSystem::mpSingleton->_SetSoftwareVertexProcess( true );

		//����Ƕ�������Ƥ����
		if( mNumBlendMatrix > 0 )
		{
			//��Ⱦ��Ƥ����
			RenderSystem::mpSingleton->_SetIndexVertexBlend( mNumBlendMatrix );
			pParam->RenderByParam();
			RenderSystem::mpSingleton->_SetIndexVertexBlend( 0 );
		}
		else
		{
			//������Ⱦ������Ⱦ
			pParam->RenderByParam();
		}

		if( mbSoftVertexProc )
			RenderSystem::mpSingleton->_SetSoftwareVertexProcess( false );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
