/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	MissileEmitter
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�������ӷ�����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��������
	class FK_DLL MissileParticle : public Particle
	{
	public:
		//�������Ӵ�������
		struct Param
		{
			Material*	pMaterial;		//���Ӳ���
			float		fLife;			//��������
			int			nBeginAlpha;	//��ʼ͸����
			int			nEndAlpha;		//����͸����
			float		fBeginSize;		//��ʼ�ߴ�
			float		fEndSize;		//�����ߴ�
		};

	public:
		Material*		mpMaterial;		//���Ӳ���
		float			mfLife;			//��������
		float			mfSize;			//���ӳߴ�
		int				mnAlpha;		//����͸����
		float			mfSizeFactor;	//���ӳߴ�仯ϵ��
		float			mfAlphaFactor;	//����͸���ȱ仯ϵ��

	public:
		MissileParticle( const Param* pParam );
		~MissileParticle();

		//���Ӵ�������
		static Particle* Creator( const void* pParam );
	};
	//--------------------------------------------------------------------------------------------------------------
	//�������ӷ�����
	class FK_DLL MissileEmitter : public SpriteEmitter
	{
	public:
		//�������ӷ�������������
		struct Param
		{
			Particle*	pParticle;
			float		fEmitRate;
		};

		//��������ʵ������
		struct Data
		{
			Vector3		vPosition;		//����λ��
			float		fLifeTime;		//��������ʱ��
			float		fSize;			//���ӳߴ磨ֱ����
			int			nAlpha;			//����͸����
		};
		typedef Stack< Data >	DataStack;

	protected:
		DataStack		mParticleData;	//����ʵ������
		BYTEStack		mVertexData;	//���Ӷ�������

		float			mfEmitRate;		//���ӷ�������
		float			mfInterval;		//������ʱ��

	public:
		MissileEmitter( const Param* pParam );

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
