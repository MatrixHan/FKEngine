/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ShaderManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderSystem/RenderSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	ShaderManager::ShaderManager()
		: mpShaderPack		(NULL)
	{
		mVSList.Initialize( 10, 10 );
		mPSList.Initialize( 10, 10 );
	}
	//--------------------------------------------------------------------------------------------------------------
	ShaderManager::~ShaderManager()
	{
		DeleteAllVertexShader();
		DeleteAllPixelShader();

		mVSList.Release();
		mPSList.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ɫ���������ļ�
	void ShaderManager::SetProgramPackFile( FileObject* pPackFile )
	{
		mpShaderPack = pPackFile;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ָ�����ļ���������ɫ��
	void ShaderManager::CreateShaderFromFile( LPCSTR szFileName )
	{
		//��ȡ�ļ�����
		mpShaderPack->Open( szFileName, OT_Read );
		DWORD dwFileLen = mpShaderPack->GetLength();

		BYTE* pFileData = (BYTE*)malloc( dwFileLen );
		if( pFileData == NULL )
			Except( Exception::ERR_NOT_ENOUGH_MEM, "�ڼ��� SCG �ļ�ʱ�޷��������ݻ���ʧ�ܡ�" );

		mpShaderPack->Read( pFileData, dwFileLen );
		mpShaderPack->Close();
		BYTE* pDataPtr = pFileData;


		//��֤�ļ�ͷ
		if( 0 != memcmp( pDataPtr, szScgFileHeader, sizeof(szScgFileHeader) ) )
		{
			free( pFileData );
			Except( Exception::ERR_INTERNAL_ERROR, (String)"�Ƿ��� SCG ��ɫ�������ļ� '" + szFileName + "'��" );
		}
		pDataPtr += sizeof(szScgFileHeader);

		//��ȡ��ɫ������
		UINT nNumShaders = *(UINT*)pDataPtr;
		pDataPtr += sizeof(UINT);


		//ѭ������������ɫ��
		for( UINT i=0; i<nNumShaders; ++i )
		{
			//��ȡ��ɫ����Ϣͷ
			CgShaderData* pShaderData = (CgShaderData*)pDataPtr;
			pDataPtr += sizeof(CgShaderData);

			//��ȡͳһ�����Ĵ�������ֵ����
			DWORD* pUniformParamIndex = (DWORD*)pDataPtr;
			size_t nUniformParamIndexLen = sizeof(DWORD) * pShaderData->nNumUniformParam;
			pDataPtr += nUniformParamIndexLen;

			//��ȡ��ɫ������
			DWORD* pShaderCode = (DWORD*)pDataPtr;
			pDataPtr += pShaderData->nShaderCodeLen;


			BaseShader* pShader = NULL;

			//������ɫ�������ж��Ƕ�����ɫ������������ɫ��
			bool bIsVS;
			switch ( pShaderData->eShaderLangType )
			{
			case DX_VS_11:		case DX_VS_20:		case DX_VS_2X:
			case OGL_VP_20:		case OGL_VP_30:		case OGL_ARB_VP1:
				{
					pShader = static_cast< BaseShader* >( CreateVertexShader() );
					bIsVS = true;
					break;
				}
			case DX_PS_11:		case DX_PS_12:		case DX_PS_13:		case DX_PS_20:
			case DX_PS_2X:		case OGL_FP_20:		case OGL_FP_30:		case OGL_ARB_FP1:
				{
					pShader = static_cast< BaseShader* >( CreatePixelShader() );
					bIsVS = false;
					break;
				}
			default:
				{
					free( pFileData );
					Except( Exception::ERR_INTERNAL_ERROR, "�������ɫ�����͡�" );
				}
			}


			//������ɫ������
			pShader->mNumVaryingParam	= pShaderData->nNumVaryingParam;
			pShader->mNumUniformParam	= pShaderData->nNumUniformParam;
			pShader->mNumConstantParam	= pShaderData->nNumConstantParam;

			//�洢��ɫ��ͳһ�����Ĵ�������ֵ
			for( UINT i=0; i<pShader->mNumUniformParam; ++i )
			{
				ShaderParam* pParam = pShader->mShaderParams.Push();
				pParam->nRegIndex = (UINT)*pUniformParamIndex++;
			}

			//�洢��ɫ������
			pShader->mShaderCodeLen = pShaderData->nShaderCodeLen;
			pShader->mpShaderCode = (DWORD*)malloc( pShader->mShaderCodeLen );
			if( pShader->mpShaderCode == NULL )
			{
				free( pFileData );
				Except( Exception::ERR_INTERNAL_ERROR, "������ɫ�����뻺��ʧ�ܡ�" );
			}

			memcpy( pShader->mpShaderCode, pShaderCode, pShader->mShaderCodeLen );


			//������ɫ��
			if( bIsVS )
			{
				VertexShader* pVS = static_cast< VertexShader* >( pShader );
				pVS->BuildVertexShader();
			}
			else
			{
				PixelShader* pPS = static_cast< PixelShader* >( pShader );
				pPS->BuildPixelShader();
			}
		}


		free( pFileData );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡָ����ŵĶ�����ɫ��
	VertexShader* ShaderManager::GetVertexShader( UINT nIndex )
	{
		if( nIndex >= mVSList.Size() )
			Except( Exception::ERR_INVALIDPARAMS, "ָ����ŵĶ�����ɫ�������ڡ�" );

		return *( mVSList.Begin() + nIndex );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡָ����ŵ�������ɫ��
	PixelShader* ShaderManager::GetPixelShader( UINT nIndex )
	{
		if( nIndex >= mPSList.Size() )
			Except( Exception::ERR_INVALIDPARAMS, "ָ����ŵ�������ɫ�������ڡ�" );

		return *( mPSList.Begin() + nIndex );
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ָ���Ķ�����ɫ��
	void ShaderManager::DeleteVertexShader( VertexShader* pVertexShader )
	{
		if( pVertexShader == NULL )
			return;

		VertexShaderList::Iterator it = mVSList.Begin();
		VertexShaderList::Iterator end = mVSList.End();
		for(; it!=end; ++it )
		{
			if( *it == pVertexShader )
			{
				mVSList.Erase( it );
				delete pVertexShader;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ָ����������ɫ��
	void ShaderManager::DeletePixelShader( PixelShader* pPixelShader )
	{
		if( pPixelShader == NULL )
			return;

		PixelShaderList::Iterator it = mPSList.Begin();
		PixelShaderList::Iterator end = mPSList.End();
		for(; it!=end; ++it )
		{
			if( *it == pPixelShader )
			{
				mPSList.Erase( it );
				delete pPixelShader;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����еĶ�����ɫ��
	void ShaderManager::DeleteAllVertexShader()
	{
		VertexShaderList::Iterator it = mVSList.Begin();
		VertexShaderList::Iterator end = mVSList.End();
		for(; it!=end; ++it )
		{
			SafeDelete( *it );
		}

		mVSList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����е�������ɫ��
	void ShaderManager::DeleteAllPixelShader()
	{
		PixelShaderList::Iterator it = mPSList.Begin();
		PixelShaderList::Iterator end = mPSList.End();
		for(; it!=end; ++it )
		{
			SafeDelete( *it );
		}

		mPSList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
