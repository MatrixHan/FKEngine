/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BaseShader
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
	BaseShader::BaseShader()
		: mShaderLangType		(Unknown)
		, mNumVaryingParam		(0)
		, mNumUniformParam		(0)
		, mNumConstantParam		(0)
		, mpShaderCode			(NULL)
		, mShaderCodeLen		(0)

		, mpTransMatParam		(NULL)
		, mpDiffuseParam		(NULL)
		, mpAmbientParam		(NULL)
		, mpSpecularParam		(NULL)
		, mpEmissiveParam		(NULL)
	{
		mShaderParams.Initialize( 3, 3 );
	}
	//--------------------------------------------------------------------------------------------------------------
	BaseShader::~BaseShader()
	{
		SafeFree( mpShaderCode );

		mShaderParams.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//������ɫ���Զ������
	void BaseShader::SetShaderCustomParam( int nIndex, ShaderParamType eType, UINT nNumUnits, void* pData )
	{
		if( nIndex < 0 || (UINT)nIndex >= mNumUniformParam )
			Except( Exception::ERR_INVALIDPARAMS, "ָ������ɫ�����������ڡ�" );

		ShaderParam* pParam = mShaderParams.Begin() + nIndex;

		//�洢��Դ��Ϣ
		pParam->eParamType	= eType;
		pParam->nNumUnits	= nNumUnits;
		pParam->pData		= pData;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ö���ת��������ɫ������
	void BaseShader::SetTransformMatrixParam( int nIndex )
	{
		if( nIndex < 0 )
		{
			mpTransMatParam = NULL;
			return;
		}
		else if( (UINT)nIndex >= mNumUniformParam )
		{
			Except( Exception::ERR_INVALIDPARAMS, "ָ������ɫ�����������ڡ�" );
		}

		mpTransMatParam = mShaderParams.Begin() + nIndex;

		mpTransMatParam->eParamType	= SPT_FLOAT;
		mpTransMatParam->nNumUnits	= 4;
		mpTransMatParam->pData		= NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������ɫ��ɫ������
	void BaseShader::SetShdaerDiffuseParam( int nIndex )
	{
		if( nIndex < 0 )
		{
			mpDiffuseParam = NULL;
			return;
		}
		else if( (UINT)nIndex >= mNumUniformParam )
		{
			Except( Exception::ERR_INVALIDPARAMS, "ָ������ɫ�����������ڡ�" );
		}

		mpDiffuseParam = mShaderParams.Begin() + nIndex;

		mpDiffuseParam->eParamType	= SPT_FLOAT;
		mpDiffuseParam->nNumUnits	= 1;
		mpDiffuseParam->pData		= NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���û���ɫ��ɫ������
	void BaseShader::SetShdaerAmbientParam( int nIndex )
	{
		if( nIndex < 0 )
		{
			mpAmbientParam = NULL;
			return;
		}
		else if( (UINT)nIndex >= mNumUniformParam )
		{
			Except( Exception::ERR_INVALIDPARAMS, "ָ������ɫ�����������ڡ�" );
		}

		mpAmbientParam = mShaderParams.Begin() + nIndex;

		mpAmbientParam->eParamType	= SPT_FLOAT;
		mpAmbientParam->nNumUnits	= 1;
		mpAmbientParam->pData		= NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ø߹�ɫ��ɫ������
	void BaseShader::SetShdaerSpecularParam( int nIndex )
	{
		if( nIndex < 0 )
		{
			mpSpecularParam = NULL;
			return;
		}
		else if( (UINT)nIndex >= mNumUniformParam )
		{
			Except( Exception::ERR_INVALIDPARAMS, "ָ������ɫ�����������ڡ�" );
		}

		mpSpecularParam = mShaderParams.Begin() + nIndex;

		mpSpecularParam->eParamType	= SPT_FLOAT;
		mpSpecularParam->nNumUnits	= 1;
		mpSpecularParam->pData		= NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���÷���ɫ��ɫ������
	void BaseShader::SetShdaerEmissiveParam( int nIndex )
	{
		if( nIndex < 0 )
		{
			mpEmissiveParam = NULL;
			return;
		}
		else if( (UINT)nIndex >= mNumUniformParam )
		{
			Except( Exception::ERR_INVALIDPARAMS, "ָ������ɫ�����������ڡ�" );
		}

		mpEmissiveParam = mShaderParams.Begin() + nIndex;

		mpEmissiveParam->eParamType	= SPT_FLOAT;
		mpEmissiveParam->nNumUnits	= 1;
		mpEmissiveParam->pData		= NULL;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ö���ת������
	void BaseShader::SetTransformMatrix( Camera* pCamera, Matrix4* pWorldMat )
	{
		if( mpTransMatParam == NULL )
			return;

		//����������Ĺ۲�ͶӰ���������������ת������
		static Matrix4 TransformMatrix;
		Mat4TransMat4( &TransformMatrix, pWorldMat, &pCamera->mViewProjMatrix );
		TransformMatrix.SetTranspose();

		mpTransMatParam->pData = (void*)&TransformMatrix;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ò���
	void BaseShader::SetMaterial( Material* pMaterial )
	{
		if( mpDiffuseParam != NULL )
			mpDiffuseParam->pData = (void*)&pMaterial->mDiffuse;

		if( mpAmbientParam != NULL )
			mpAmbientParam->pData = (void*)&pMaterial->mAmbient;

		if( mpSpecularParam != NULL )
			mpSpecularParam->pData = (void*)&pMaterial->mSpecular;

		if( mpEmissiveParam != NULL )
			mpEmissiveParam->pData = (void*)&pMaterial->mEmissive;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
