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

#pragma once

//==================================================================================================================

#include "../RenderWrapper/Material.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	//��ɫ����������
	enum ShaderParamType
	{
		SPT_FLOAT,	// float �Ͳ�������λ����Ϊ 4 float��
		SPT_INT,	// int   �Ͳ�������λ����Ϊ 4 int��
		SPT_BOOL,	// bool  �Ͳ�������λ����Ϊ 1 bool��		
	};

	//��ɫ�������ṹ
	struct ShaderParam
	{
		UINT				nRegIndex;	//�Ĵ������
		ShaderParamType		eParamType;	//��������
		UINT				nNumUnits;	//��λ����
		void*				pData;		//��������ָ��
	};

	typedef Stack< ShaderParam >	ShaderParamStack;

	//--------------------------------------------------------------------------------------------------------------
	class ShaderManager;
	//--------------------------------------------------------------------------------------------------------------
	//��ɫ������
	class FK_DLL BaseShader
	{
	public:
		friend class ShaderManager;

	protected:
		CgLanguageType		mShaderLangType;	//��ɫ����������

		UINT				mNumVaryingParam;	//�ɱ��������
		UINT				mNumUniformParam;	//ͳһ��������
		UINT				mNumConstantParam;	//������������

		ShaderParamStack	mShaderParams;		//��ɫ������

		DWORD*				mpShaderCode;		//��ɫ������
		DWORD				mShaderCodeLen;		//��ɫ�����볤��

		ShaderParam*		mpTransMatParam;	//����ת��������ɫ������

		ShaderParam*		mpDiffuseParam;		//����ɫ��ɫ������
		ShaderParam*		mpAmbientParam;		//����ɫ��ɫ������
		ShaderParam*		mpSpecularParam;	//�߹�ɫ��ɫ������
		ShaderParam*		mpEmissiveParam;	//����ɫ��ɫ������

	public:
		BaseShader();
		virtual ~BaseShader();

		//������ɫ���Զ������
		void SetShaderCustomParam( int nIndex, ShaderParamType eType, UINT nNumUnits, void* pData );

		//���ö���ת��������ɫ������
		void SetTransformMatrixParam( int nIndex );

		//��������ɫ��ɫ������
		void SetShdaerDiffuseParam( int nIndex );

		//���û���ɫ��ɫ������
		void SetShdaerAmbientParam( int nIndex );

		//���ø߹�ɫ��ɫ������
		void SetShdaerSpecularParam( int nIndex );

		//���÷���ɫ��ɫ������
		void SetShdaerEmissiveParam( int nIndex );

		//���ö���ת������
		void SetTransformMatrix( Camera* pCamera, Matrix4* pWorldMat );

		//���ò���
		void SetMaterial( Material* pMaterial );
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< BaseShader* >		BaseShaderList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
