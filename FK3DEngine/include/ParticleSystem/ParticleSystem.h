/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ParticleSystem
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	����ϵͳ
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//����ϵͳ
	class FK_DLL ParticleSystem : public Singleton< ParticleSystem >
	{
	public:
		ParticleList		mParticleList;		//�����б�
		EmitterList			mEmitterList;		//���ӷ������б�

		VertexBuffer*		mpVertexBuffer;		//�������Ӷ��㻺��
		IndexBuffer*		mpIndexBuffer;		//����������������
		VertexDeclaration*	mpVertexDeclaration;//�������Ӷ�������

		UINT				mMaxNumSParticle;	//����������ɾ���������
		UINT				mOffsetSParticle;	//��ǰ֡ƫ�ƾ���������
		UINT				mRenderSParticle;	//��ǰ֡��Ⱦ����������

	public:
		ParticleSystem( UINT nMaxNumSpriteParticle );
		virtual ~ParticleSystem();

		//��������
		Particle* CreateParticle( Particle::FnCreator fnCreator, void* pParam = NULL );

		//ɾ������
		void DeleteParticle( Particle* pParticle );

		//ɾ����������
		void DeleteAllParticle();

		//�������ӷ�����
		Emitter* CreateEmitter( Emitter::FnCreator fnCreator, void* pParam = NULL );

		//ɾ�����ӷ�����
		void DeleteEmitter( Emitter* pEmitter );

		//ɾ���������ӷ�����
		void DeleteAllEmitter();

		//���·�����
		void _UpdateEmitter( float fFrameTime );

		//���¾������ӷ���
		void _UpdateSprite( const Camera* pCamera );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
