/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ObjectFileLoader
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
	ObjectFileLoader::ObjectFileLoader()
		: mpObjectPack		(NULL)
	{
		mLoadedMaterialList.Initialize( 10, 10 );
		mLoadedTriMeshList.Initialize( 20, 100 );
		mLoadedStreamMeshList.Initialize( 20, 100 );
		mLoadedSkeletonList.Initialize( 10, 10 );
		mLoadedParticleList.Initialize( 10, 10 );
		mLoadedEmitterList.Initialize( 10, 10 );
		mLoadedBoundMeshList.Initialize( 20, 50 );
	}
	//--------------------------------------------------------------------------------------------------------------
	ObjectFileLoader::~ObjectFileLoader()
	{
		if( mpObjectPack != NULL )
		{
			mpObjectPack->Close();
			mpObjectPack = NULL;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����������ļ�
	void ObjectFileLoader::SetObjectPackFile( FileObject* pPackFile )
	{
		mpObjectPack = pPackFile;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���������ļ�
	void ObjectFileLoader::LoadObjectFile( const char* szFileName )
	{
		//�����ϴεļ����б�
		mLoadedMaterialList.Clear();
		mLoadedTriMeshList.Clear();
		mLoadedStreamMeshList.Clear();
		mLoadedSkeletonList.Clear();
		mLoadedParticleList.Clear();
		mLoadedEmitterList.Clear();
		mLoadedBoundMeshList.Clear();

		FKTry
		{
			//���ļ�
			mpObjectPack->Open( szFileName, OT_Read );

			//��ȡ�ļ�����
			mFileLength = mpObjectPack->GetLength();

			//��ȡ�ļ�ͷ
			ObjectChunkID eChunkID = FK_CID_Invaild;

			if( !_ReadChunkID( eChunkID ) )
				Except( Exception::ERR_CANNOT_READ_FILE, "�޷���ȡ�ļ�ͷ�Ρ�" );

			if( eChunkID != FK_CID_Header )
				Except( Exception::ERR_INTERNAL_ERROR, "�Ƿ����ļ�ͷ�α�ʶ��" );

			_ReadChunkHeader();

			//ѭ����ȡ����ʣ���ļ���
			while( _ReadChunkID( eChunkID ) )
			{
				switch (eChunkID)
				{
				case FK_CID_Material:		_ReadChunkMaterial();		break;
				case FK_CID_TriMesh:		_ReadChunkTriMesh();		break;
				case FK_CID_StreamMesh:		_ReadChunkStreamMesh();		break;
				case FK_CID_Skeleton:		_ReadChunkSkeleton();		break;
				case FK_CID_Billboard:		_ReadChunkBillboard();		break;
				case FK_CID_BoundMesh:		_ReadChunkBoundMesh();		break;
				case FK_CID_End:			goto ChunkEnd;
				default:
					Except( Exception::ERR_INVALIDPARAMS, "�޷�ʶ����ļ��α�ʶ��" );
				}
			}

ChunkEnd:
			//�ر��ļ�
			mpObjectPack->Close();
		}
		FKCatch
		{
			mpObjectPack->Close();

			String sOrgDesc = sException.mDesc;
			sException.mDesc.Format( "����������ʿ3D��Ϸ���������ļ� '%s' ʧ�ܡ�\nʧ��ԭ�� %s",
				szFileName, sOrgDesc.GetCharPtr() );

			ExceptToUpLevel;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ļ��α�ʶ
	bool ObjectFileLoader::_ReadChunkID( ObjectChunkID& eChunkID )
	{
		//��������ļ���β�򷵻�
		DWORD dwCurPos = mpObjectPack->GetPosition();
		if( dwCurPos == mFileLength )
			return false;

		//��ȡ�ļ��α�ʶ
		mpObjectPack->Read( &eChunkID, sizeof(ObjectChunkID) );

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ļ�ͷ��
	void ObjectFileLoader::_ReadChunkHeader()
	{
		//��ȡ�ļ�ͷ�ַ���
		static char pFileHeader [sizeof(FK_OBJ_FILE_HEADER)] = { NULL };
		mpObjectPack->Read( pFileHeader, sizeof(FK_OBJ_FILE_HEADER) );
		if( 0 != memcmp( pFileHeader, FK_OBJ_FILE_HEADER, sizeof(FK_OBJ_FILE_HEADER) ) )
			Except( Exception::ERR_INTERNAL_ERROR, "�Ƿ����ļ�ͷ�ַ�����" );

		//��ȡ�ļ��汾��
		UINT nVersion = 0;
		mpObjectPack->Read( &nVersion, sizeof(UINT) );

		//����ļ��汾�űȵ�ǰ֧�ְ汾��Ҫ��
		if( nVersion > FK_OBJ_FILE_VERSION )
			Except( Exception::ERR_INTERNAL_ERROR, "�ļ��汾�Ÿ��ڵ�ǰ֧�ְ汾�š�" );

		//����ļ��汾�ŵ�����ͼ��ݰ汾��
		if( nVersion < FK_OBJ_FILE_MIN_COMPATIBLE_VERSION )
			Except( Exception::ERR_INTERNAL_ERROR, "�ļ��汾�ŵ�����ͼ��ݰ汾�š�" );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ���ʶ�
	void ObjectFileLoader::_ReadChunkMaterial()
	{
		//��ȡ��������
		static MaterialData sMaterialData;
		mpObjectPack->Read( &sMaterialData, sizeof(MaterialData) );

		//��������
		*mLoadedMaterialList.Push() = MaterialManager::mpSingleton->CreateMaterial( &sMaterialData );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�����������
	void ObjectFileLoader::_ReadChunkTriMesh()
	{
		//��������
		TriMesh* pTriMesh = (TriMesh*)GeometryManager::mpSingleton->CreateGeometry( TriMesh::Creator );


		//��ȡ������������Ϣ
		static TriMeshInfo sMeshInfo;

		mpObjectPack->Read( &sMeshInfo, sizeof(TriMeshInfo) );

		if( sMeshInfo.nNumBone > 0 )
		{
			//��ȡ��ͷ��������
			size_t nDataLen = sizeof(UINT) * sMeshInfo.nNumBone;
			UINT* pBoneIndexBuf = (UINT*)malloc( nDataLen );
			mpObjectPack->Read( pBoneIndexBuf, (DWORD)nDataLen );

			pTriMesh->SetBoneIndex( pBoneIndexBuf, sMeshInfo.nNumBone );

			free( pBoneIndexBuf );

			//�ж��Ƿ���Ҫʹ��������㴦��
			pTriMesh->mNumBlendMatrix	= sMeshInfo.nNumBonePerVer;
			pTriMesh->mMaxBlendIndex	= sMeshInfo.nNumBone - 1;

			DWORD dwHardMaxBlendIndex = sMeshInfo.bHaveNormal ?
				( RenderSystem::mdwMaxBlendIndex / 2 ) : RenderSystem::mdwMaxBlendIndex;

			pTriMesh->mbSoftVertexProc = ( dwHardMaxBlendIndex < pTriMesh->mMaxBlendIndex
				|| RenderSystem::mdwMaxBlendNum < pTriMesh->mNumBlendMatrix );
		}

		//�������񶥵�������
		pTriMesh->AllocStreamBuf( sMeshInfo.nNumVertexStream );
		pTriMesh->AllocMaterialBuf( sMeshInfo.nNumSubMesh );
		pTriMesh->AllocRenderParamBuf( sMeshInfo.nNumSubMesh );

		UINT nVertexStreamIndex = 0;
		UINT nSubMeshIndex = 0;


		//������������
		pTriMesh->mpVertexDeclaration = BufferManager::mpSingleton->AddVertexDeclaration();

		//ѭ����ȡ���������������
		ObjectChunkID eChunkID = FK_CID_Invaild;
		while( _ReadChunkID( eChunkID ) )
		{
			switch (eChunkID)
			{
			case FK_CID_BoundBox:
				{
					_ReadChunkBoundBox( pTriMesh );
					break;
				}
			case FK_CID_IndexStream:
				{
					_ReadChunkIndexStream( pTriMesh, pTriMesh->mbSoftVertexProc );
					break;
				}
			case FK_CID_VertexStream:
				{
					_ReadChunkVertexStream( pTriMesh, nVertexStreamIndex, pTriMesh->mbSoftVertexProc );
					++nVertexStreamIndex;
					break;
				}
			case FK_CID_VertexElement:
				{
					_ReadChunkVertexElement( pTriMesh );
					break;
				}
			case FK_CID_SubMesh:
				{
					_ReadChunkSubMesh( pTriMesh, nSubMeshIndex );
					++nSubMeshIndex;
					break;
				}
			case FK_CID_End:
				{
					goto ChunkEnd;
				}
			default:
				Except( Exception::ERR_INVALIDPARAMS, "�޷�ʶ�������������α�ʶ��" );
			}
		}

ChunkEnd:
		//���ض�������
		pTriMesh->mpVertexDeclaration->CreateVertexDeclaration();

		*mLoadedTriMeshList.Push() = pTriMesh;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�����������
	void ObjectFileLoader::_ReadChunkStreamMesh()
	{
		//��������
		StreamMesh* pStreamMesh = (StreamMesh*)GeometryManager::mpSingleton->CreateGeometry( StreamMesh::Creator );


		//��ȡ������������Ϣ
		static StreamMeshInfo sMeshInfo;

		mpObjectPack->Read( &sMeshInfo, sizeof(StreamMeshInfo) );

		pStreamMesh->mNumSegment		= sMeshInfo.nNumSegment;
		pStreamMesh->mNumVertex			= sMeshInfo.nNumVertex;
		pStreamMesh->mNumIndex			= sMeshInfo.nNumFace * 3;
		pStreamMesh->mNumIndexPerFrame	= sMeshInfo.nNumFacePerFrame * 3;
		pStreamMesh->mNumKey			= sMeshInfo.nNumFrames;
		pStreamMesh->mIntervalTime		= sMeshInfo.fIntervalTime;

		//�������񶥵�������
		pStreamMesh->AllocStreamBuf( sMeshInfo.nNumVertexStream );
		pStreamMesh->AllocMaterialBuf( sMeshInfo.nNumSubMesh );
		pStreamMesh->AllocRenderParamBuf( sMeshInfo.nNumSubMesh );

		UINT nVertexStreamIndex = 0;
		UINT nSubMeshIndex = 0;


		//��ȡ���������������
		pStreamMesh->AllocSegmentBuf();

		mpObjectPack->Read( pStreamMesh->mpSegmentsIndex, sizeof(UINT) * pStreamMesh->mNumKey );
		mpObjectPack->Read( pStreamMesh->mpSegments, sizeof(StreamMeshSegment) * pStreamMesh->mNumSegment );


		//������������
		pStreamMesh->mpVertexDeclaration = BufferManager::mpSingleton->AddVertexDeclaration();

		//ѭ����ȡ���������������
		ObjectChunkID eChunkID = FK_CID_Invaild;
		while( _ReadChunkID( eChunkID ) )
		{
			switch (eChunkID)
			{
			case FK_CID_BoundBox:
				{
					_ReadChunkBoundBox( pStreamMesh );
					break;
				}
			case FK_CID_IndexStream:
				{
					_ReadChunkIndexStream( pStreamMesh, pStreamMesh->mbSoftVertexProc );
					break;
				}
			case FK_CID_VertexStream:
				{
					_ReadChunkVertexStream( pStreamMesh, nVertexStreamIndex, pStreamMesh->mbSoftVertexProc );
					++nVertexStreamIndex;
					break;
				}
			case FK_CID_VertexElement:
				{
					_ReadChunkVertexElement( pStreamMesh );
					break;
				}
			case FK_CID_SubMesh:
				{
					_ReadChunkSubMesh( pStreamMesh, nSubMeshIndex );
					++nSubMeshIndex;
					break;
				}
			case FK_CID_End:
				{
					goto ChunkEnd;
				}
			default:
				Except( Exception::ERR_INVALIDPARAMS, "�޷�ʶ��Ķ���������α�ʶ��" );
			}
		}

ChunkEnd:
		//���ض�������
		pStreamMesh->mpVertexDeclaration->CreateVertexDeclaration();

		*mLoadedStreamMeshList.Push() = pStreamMesh;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��Χ�ж�
	void ObjectFileLoader::_ReadChunkBoundBox( RenderObject* pRenderObject )
	{
		//��ȡ��Χ���������С��
		static Vector3 pBoundVer[2];
		mpObjectPack->Read( pBoundVer, sizeof(Vector3) * 2 );

		//���ð�Χ��
		pRenderObject->mBoundBox.SetMaxMin( pBoundVer[0], pBoundVer[1] );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ���������ݶ�
	void ObjectFileLoader::_ReadChunkIndexStream( RenderObject* pRenderObject, bool bSoftProc )
	{
		//��ȡ��������Ϣ
		static IndexStreamInfo sIndexStreamInfo;
		mpObjectPack->Read( &sIndexStreamInfo, sizeof(IndexStreamInfo) );

		//����������
		IndexBuffer* pIndexBuffer = BufferManager::mpSingleton->AddIndexBuffer();
		pIndexBuffer->CreateIndexBuffer(
			sIndexStreamInfo.nNumIndex,
			sIndexStreamInfo.eIndexType,
			sIndexStreamInfo.bDynamic,
			bSoftProc );

		//������������
		void* pDstBuf = pIndexBuffer->Lock( 0, 0 );
		mpObjectPack->Read( pDstBuf, pIndexBuffer->mnBufLen );
		pIndexBuffer->Unlock();

		pRenderObject->mpIndexBuffer = pIndexBuffer;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ���������ݶ�
	void ObjectFileLoader::_ReadChunkVertexStream( RenderObject* pRenderObject, UINT nIndex, bool bSoftProc )
	{
		//��ȡ��������Ϣ
		static VertexStreamInfo sVertexStreamInfo;
		mpObjectPack->Read( &sVertexStreamInfo, sizeof(VertexStreamInfo) );

		//����������
		VertexBuffer* pVertexBuffer = BufferManager::mpSingleton->AddVertexBuffer();
		pVertexBuffer->CreateVertexBuffer(
			sVertexStreamInfo.nVerSize,
			sVertexStreamInfo.nNumVer,
			sVertexStreamInfo.bDynamic,
			bSoftProc );

		//���ض���������
		void* pDstBuf = pVertexBuffer->Lock( 0, 0 );
		mpObjectPack->Read( pDstBuf, pVertexBuffer->mnBufLen );
		pVertexBuffer->Unlock();

		pRenderObject->mppVertexBuffer[nIndex] = pVertexBuffer;
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������
	void ObjectFileLoader::_ReadChunkVertexElement( RenderObject* pRenderObject )
	{
		//��ȡ����Ԫ������
		static VertexElement sVertexElement;
		mpObjectPack->Read( &sVertexElement, sizeof(VertexElement) );

		//���붥��Ԫ������
		pRenderObject->mpVertexDeclaration->AddElement(
			sVertexElement.nStream,
			sVertexElement.nOffset,
			sVertexElement.Type,
			sVertexElement.Method,
			sVertexElement.Usage,
			sVertexElement.UsageIndex );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�������
	void ObjectFileLoader::_ReadChunkSubMesh( RenderObject* pRenderObject, UINT nIndex )
	{
		//��ȡ��������Ϣ
		static SubMeshInfo sSubMeshInfo;
		mpObjectPack->Read( &sSubMeshInfo, sizeof(SubMeshInfo) );

		//������������Ϣ������Ⱦ����
		UINT nMaterialIndex = (UINT)sSubMeshInfo.nMaterialIndex;
		if( nMaterialIndex >= mLoadedMaterialList.Size() )
			Except( Exception::ERR_INVALIDPARAMS, "������ָ��ʹ�õĲ�������ֵ����" );

		Material* pMaterial = mLoadedMaterialList[ nMaterialIndex ];
		pMaterial->AddRef();

		pRenderObject->mppMaterial[nIndex] = pMaterial;

		RenderParam* pRenderParam = pRenderObject->mpRenderParam + nIndex;

		pRenderParam->pMaterial	= pMaterial;
		pRenderParam->eDrawType	= RenderParam::DT_Basic;
		pRenderParam->nPriority	= RSGP_Default;

		pRenderParam->sBasicParam.ePrimType		= PT_TRIANGLE_LIST;
		pRenderParam->sBasicParam.nVerOffset	= 0;
		pRenderParam->sBasicParam.nMinIndex		= 0;
		pRenderParam->sBasicParam.nIndexOffset	= sSubMeshInfo.nIndexOffset;
		pRenderParam->sBasicParam.nVerCount		= sSubMeshInfo.nVerCount;
		pRenderParam->sBasicParam.nPrimCount	= sSubMeshInfo.nPrimCount;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ������
	void ObjectFileLoader::_ReadChunkSkeleton()
	{
		//��ȡ������Ϣ
		static SkeletonInfo sSkeletonInfo;

		mpObjectPack->Read( &sSkeletonInfo, sizeof(SkeletonInfo) );

		//��������
		Skeleton* pSkeleton = SkeletonManager::mpSingleton->CreateSkeleton(
			sSkeletonInfo.nNumKey, sSkeletonInfo.fIntervalTime );

		//�������й�ͷ
		DWORD dwSizePerBone = sizeof(Matrix4) * sSkeletonInfo.nNumKey;
		Matrix4* pMatrixBuf = (Matrix4*)malloc( dwSizePerBone );

		for( UINT i=0; i<sSkeletonInfo.nNumBone; ++i )
		{
			//��ȡ��ͷ��������
			mpObjectPack->Read( pMatrixBuf, dwSizePerBone );
			pSkeleton->CreateBone( pMatrixBuf );
		}

		free( pMatrixBuf );

		*mLoadedSkeletonList.Push() = pSkeleton;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ������
	void ObjectFileLoader::_ReadChunkBillboard()
	{
		//��ȡ�������Ϣ
		static BillboardInfo sBillboardInfo;
		mpObjectPack->Read( &sBillboardInfo, sizeof(BillboardInfo) );

		//��ȡ��������
		if( (UINT)sBillboardInfo.nMaterialIndex >= mLoadedMaterialList.Size() )
			Except( Exception::ERR_INVALIDPARAMS, "�����ʹ�ò�������ֵ����" );

		Material* pMaterial = mLoadedMaterialList[ sBillboardInfo.nMaterialIndex ];

		//��ȡ�������������
		DWORD dwPosSize = sizeof(Vector3) * sBillboardInfo.nNumBillboard;
		Vector3* pPositionBuf = (Vector3*)malloc( dwPosSize );
		mpObjectPack->Read( pPositionBuf, dwPosSize );


		Particle* pParticle = NULL;
		Emitter* pEmitter = NULL;

		//���Ϊ��̬�����
		if( sBillboardInfo.szUVAFileName[0] == '\0' )
		{
			BillboardParticle::Param sParamP;

			sParamP.pMaterial	= pMaterial;
			sParamP.fSizeX		= sBillboardInfo.fSizeX;
			sParamP.fSizeY		= sBillboardInfo.fSizeY;

			pParticle = ParticleSystem::mpSingleton->CreateParticle( BillboardParticle::Creator, &sParamP );

			BillboardEmitter::Param sParamE;

			sParamE.pParticle		= pParticle;
			sParamE.nNumBillboard	= sBillboardInfo.nNumBillboard;
			sParamE.pPosition		= pPositionBuf;

			pEmitter = ParticleSystem::mpSingleton->CreateEmitter( BillboardEmitter::Creator, &sParamE );
		}
		//���Ϊ UV ���������
		else
		{
			UVABillboardParticle::Param sParamP;

			sParamP.pMaterial		= pMaterial;
			sParamP.pUVAFileName	= sBillboardInfo.szUVAFileName;
			sParamP.fSizeX			= sBillboardInfo.fSizeX;
			sParamP.fSizeY			= sBillboardInfo.fSizeY;

			pParticle = ParticleSystem::mpSingleton->CreateParticle( UVABillboardParticle::Creator, &sParamP );

			UVABillboardEmitter::Param sParamE;

			sParamE.pParticle		= pParticle;
			sParamE.nNumBillboard	= sBillboardInfo.nNumBillboard;
			sParamE.pPosition		= pPositionBuf;

			pEmitter = ParticleSystem::mpSingleton->CreateEmitter( UVABillboardEmitter::Creator, &sParamE );
		}

		free( pPositionBuf );

		*mLoadedParticleList.Push() = pParticle;
		*mLoadedEmitterList.Push() = pEmitter;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��ײ�����
	void ObjectFileLoader::_ReadChunkBoundMesh()
	{
		//��ȡ��ײ����Ϣ
		static BoundInfo sBoundInfo;

		mpObjectPack->Read( &sBoundInfo, sizeof(BoundInfo) );

		//������ײ��������
		DWORD dwBoundFaceSize = sizeof(BoundFace) * sBoundInfo.nNumFace;
		DWORD dwBoundVertexSize = sizeof(Vector3) * sBoundInfo.nNumVertex;

		BoundFace* pBoundFace = (BoundFace*)malloc( dwBoundFaceSize + dwBoundVertexSize );
		Vector3* pBoundVertex = (Vector3*)( pBoundFace + sBoundInfo.nNumFace );

		mpObjectPack->Read( pBoundFace, dwBoundFaceSize );
		mpObjectPack->Read( pBoundVertex, dwBoundVertexSize );

		//������ײ����
		BoundMesh* pBoundMesh = (BoundMesh*)PhysicsSystem::mpSingleton->CreateBoundVolume( BoundMesh::Creator );
		pBoundMesh->LoadBoundMesh( &sBoundInfo, pBoundFace, pBoundVertex );

		free( pBoundFace );

		*mLoadedBoundMeshList.Push() = pBoundMesh;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
