/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SkySphere
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
	SkySphere::SkySphere( UINT nNumRing, UINT nNumSegment )
		: mSkyWorldMatrix	(Matrix4::Identity)
		, mpTexture			(NULL)
		, mpVD				(NULL)
		, mpPositionVB		(NULL)
		, mpTexcoordVB		(NULL)
		, mpIB				(NULL)
		, mRotaValue		(0.0f)
		, mRotaDegree		(0.0f)
		, mRotaAxis			(Vector3::UnitX)
	{
		mRing		= nNumRing;							//����
		mSegment	= nNumSegment;						//����
		mNumVertex	= ( mRing + 1 ) * ( mSegment + 1 );	//��������
		mNumIndex	= 2 * mRing * ( mSegment + 1 );		//��������
		mNumFace	= mNumIndex - 2;					//����������


		BufferManager* pBufMgr = BufferManager::GetSingletonPtr();

		//������������
		mpVD = pBufMgr->AddVertexDeclaration();
		mpVD->AddElement( 0, 0, VET_FLOAT3, VEM_DEFAULT, VEU_POSITION, 0 );
		mpVD->AddElement( 1, 0, VET_FLOAT2, VEM_DEFAULT, VEU_TEXCOORD, 0 );
		mpVD->CreateVertexDeclaration();

		//�������㻺��
		mpPositionVB = pBufMgr->AddVertexBuffer();
		mpPositionVB->CreateVertexBuffer( sizeof(float)*3, mNumVertex * 2, false );

		mpTexcoordVB = pBufMgr->AddVertexBuffer();
		mpTexcoordVB->CreateVertexBuffer( sizeof(float)*2, mNumVertex * 2, false );

		mpIB = pBufMgr->AddIndexBuffer();
		mpIB->CreateIndexBuffer( mNumIndex * 2, IT_INDEX16 );

		//����ԭʼ��������
		size_t nPosDataLen = sizeof(float) * mNumVertex * 3;
		size_t nUVDataLen = sizeof(float) * mNumVertex * 2;
		size_t nIndexDataLen = sizeof(WORD) * mNumIndex;

		char* pDataBuf = (char*)malloc( nPosDataLen + nUVDataLen + nIndexDataLen );
		if( pDataBuf == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "���������ʱ���䶥���������ɻ���ʧ�ܡ�" );

		float* pPosData		= (float*)pDataBuf;
		float* pUVData		= (float*)( pDataBuf + nPosDataLen );
		WORD* pIndexData	= (WORD*)( pDataBuf + nPosDataLen + nUVDataLen );

		Vector3* pPos = (Vector3*)pPosData;
		float* pUV = pUVData;
		WORD* pIndex = pIndexData;

		//����Ƕ�
		const float fRing = (float)mRing;
		const float fSegment = (float)mSegment;
		const float fRingAngle = FK_PI / (float)fRing;
		const float fSegmentAngle = FK_PI * 2.0f / (float)fSegment;

		float r = 0.0f;
		float y = 0.0f;
		float x = 0.0f;
		float z = 0.0f;

		//���ɴ�ֱһ�������ѭ��
		WORD wIndex = ( mRing + 1 ) * ( mSegment + 1 );
		for( float ring=0; ring<fRing+1.0f; ++ring )
		{
			SinCos( ring * fRingAngle, &r, &y );

			//����ˮƽ��һ�ζ����ѭ��			
			for( float seg=0; seg<fSegment+1.0f; ++seg )
			{
				SinCos( seg * fSegmentAngle, &x, &z );

				pPos->x = x * r	* 60.0f;
				pPos->y = y * 60.0f;
				pPos->z = z * r	* 60.0f;
				++pPos;

				*pUV++ = 1.0f - seg / fSegment;
				*pUV++ = ring / fRing * 0.5f;

				if( ring != fRing )
				{
					--wIndex;
					*pIndex++ = wIndex - (WORD)mSegment - 1;
					*pIndex++ = wIndex;
				}
			}
		}

		//������д�뻺��
		char* pDstPos = (char*)mpPositionVB->Lock( 0, 0 );

		memcpy( pDstPos, pPosData, nPosDataLen );
		pDstPos += nPosDataLen;
		memcpy( pDstPos, pPosData, nPosDataLen );

		mpPositionVB->Unlock();
        
		char* pDstUV = (char*)mpTexcoordVB->Lock( 0, 0 );
		char* pDstIndex = (char*)mpIB->Lock( 0, 0 );
		
		memcpy( pDstUV, pUVData, nUVDataLen );
		memcpy( pDstIndex, pIndexData, nIndexDataLen );
		pDstUV += nUVDataLen;
		pDstIndex += nIndexDataLen;

		//���ɻ��������°�ߵĶ�������
		pUV = pUVData;
		for( UINT i=0; i<(mRing+1)*(mSegment+1); ++i )
		{
			++pUV;
			*pUV += 0.5f;
			++pUV;
		}

		pIndex = pIndexData;
		for( UINT i=0; i<mRing*(mSegment+1); ++i )
		{
			*pIndex += mNumIndex;	++pIndex;
			*pIndex += mNumIndex;	++pIndex;
		}

		memcpy( pDstUV, pUVData, nUVDataLen );
		memcpy( pDstIndex, pIndexData, nIndexDataLen );

		mpTexcoordVB->Unlock();
		mpIB->Unlock();

		//�ͷŶ����������ɻ���
		free( pDataBuf );
	}
	//--------------------------------------------------------------------------------------------------------------
	SkySphere::~SkySphere()
	{
		BufferManager* pBufMgr = BufferManager::GetSingletonPtr();

		//�ͷŶ������������㻺��
		pBufMgr->DelVertexDeclaration( mpVD );
		pBufMgr->DelVertexBuffer( mpPositionVB );
		pBufMgr->DelVertexBuffer( mpTexcoordVB );
		pBufMgr->DelIndexBuffer( mpIB );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�������������
	void SkySphere::SetSphereTexture( Texture* pTexture )
	{
		mpTexture = pTexture;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ñ����ת
	void SkySphere::SetSurfaceRotation( float fRotaVale, const Vector3& vAxis )
	{
		mRotaValue = fRotaVale;
		mRotaAxis = vAxis;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������
	void SkySphere::_UpdateSky( float fTimeSinceLastFrame )
	{
		mRotaDegree += mRotaValue * fTimeSinceLastFrame;

		if( mRotaDegree > 180.0f )
			mRotaDegree -= 360.0f;
		else if( mRotaDegree < -180.0f )
			mRotaDegree += 360.0f;

		mSkyWorldMatrix.SetRotationAxis( mRotaDegree, mRotaAxis );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ�����
	void SkySphere::_RenderSky()
	{
		//���ݵ�ǰ�������͹ۿ�����
		RenderSystem::mpSingleton->_GetViewMatrix( &mMatViewSave );
		RenderSystem::mpSingleton->_GetWorldMatrix( &mMatWorldSave );

		//������Ⱦ�����Ĺۿ�����ֻ�ı���ۿ�λ�ã�
		mMatView = mMatViewSave;
		mMatView._41 = 0.0f;	mMatView._42 = 0.0f;	mMatView._43 = 0.0f;

		RenderSystem::mpSingleton->_SetViewMatrix( &mMatView );

		//������Ⱦ�������������
		RenderSystem::mpSingleton->_SetWorldMatrix( &mMatWorld );

		//�������������״̬
		_SetTextureState();

		//��������岻͸����Ⱦ״̬
		RenderSystem::mpSingleton->_SetRenderState( &mRenderOpacity );

		//���ö���������Դ�Ͷ�������
		RenderSystem::mpSingleton->_SetVertexStream( mpPositionVB, 0 );
		RenderSystem::mpSingleton->_SetVertexStream( mpTexcoordVB, 1 );
		RenderSystem::mpSingleton->_SetIndexStream( mpIB );
		RenderSystem::mpSingleton->_SetVertexDeclaration( mpVD );

		//��������
		RenderSystem::mpSingleton->_SetTexture( mpTexture, 0 );

		//��Ⱦ������
		RenderSystem::mpSingleton->_RenderVertex( PT_TRIANGLE_STRIP, 0, 0, mNumVertex, 0, mNumFace );

		//���������͸����Ⱦ״̬
		RenderSystem::mpSingleton->_SetRenderState( &mRenderTransparent );

		//��Ⱦ���
		RenderSystem::mpSingleton->_SetWorldMatrix( &mSkyWorldMatrix );
		RenderSystem::mpSingleton->_RenderVertex( PT_TRIANGLE_STRIP, mNumVertex, 0, mNumVertex, 0, mNumFace );

		//�ָ�ԭ�����������͹ۿ�����
		RenderSystem::mpSingleton->_SetViewMatrix( &mMatViewSave );
		RenderSystem::mpSingleton->_SetWorldMatrix( &mMatWorldSave );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
