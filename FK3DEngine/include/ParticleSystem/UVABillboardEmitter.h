/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	UVABillboardEmitter
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	UV ������������ӷ�����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "../RenderWrapper/UVAControl.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	struct UVAnimation;
	//--------------------------------------------------------------------------------------------------------------
	// UV �������������
	class FK_DLL UVABillboardParticle : public Particle
	{
	public:
		// UV ������������Ӵ�������
		struct Param
		{
			Material*	pMaterial;		//���Ӳ���
			char*		pUVAFileName;	// UVA �ļ���
			float		fSizeX;			//���ӳߴ� X
			float		fSizeY;			//���ӳߴ� Y
		};

	public:
		Material*		mpMaterial;		//���Ӳ���
		float			mfSizeX;		//���ӳߴ� X
		float			mfSizeY;		//���ӳߴ� Y

		UVAnimation*	mpUVAnimation;	// UV ��������

	public:
		UVABillboardParticle( const Param* pParam );
		~UVABillboardParticle();

		//���Ӵ�������
		static Particle* Creator( const void* pParam );
	};
	//--------------------------------------------------------------------------------------------------------------
	// UV ������������ӷ�����
	class FK_DLL UVABillboardEmitter : public SpriteEmitter
	{
	public:
		//��������ӷ�������������
		struct Param
		{
			Particle*		pParticle;
			Vector3*		pPosition;
			UINT			nNumBillboard;
		};

	public:
		UVAControl		mUVAControl;	// UV ����������

	protected:
		Vector3*		mpParticleData;	//����ʵ������

	public:
		UVABillboardEmitter( const Param* pParam );
		~UVABillboardEmitter();

		//���ӷ�������������
		static Emitter* Creator( const void* pParam );

	protected:
		//���·�����
		void _UpdateEmitter( const float fFrameTime );

		//���¾������ӷ���
		UINT _UpdateSprite( const Camera* pCamera );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
