/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BillboardEmitter
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��������ӷ�����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//���������
	class FK_DLL BillboardParticle : public Particle
	{
	public:
		//��������Ӵ�������
		struct Param
		{
			Material*	pMaterial;		//���Ӳ���
			float		fSizeX;			//���ӳߴ� X
			float		fSizeY;			//���ӳߴ� Y
		};

	public:
		Material*		mpMaterial;		//���Ӳ���
		float			mfSizeX;		//���ӳߴ� X
		float			mfSizeY;		//���ӳߴ� Y

	public:
		BillboardParticle( const Param* pParam );
		~BillboardParticle();

		//���Ӵ�������
		static Particle* Creator( const void* pParam );
	};
	//--------------------------------------------------------------------------------------------------------------
	//��������ӷ�����
	class FK_DLL BillboardEmitter : public SpriteEmitter
	{
	public:
		//��������ӷ�������������
		struct Param
		{
			Particle*		pParticle;
			Vector3*		pPosition;
			UINT			nNumBillboard;
		};

	protected:
		Vector3*		mpParticleData;	//����ʵ������

	public:
		BillboardEmitter( const Param* pParam );
		~BillboardEmitter();

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
