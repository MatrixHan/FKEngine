/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Emitter
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	���ӷ�����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================
#include "../RenderWrapper/RenderObject.h"
#include "../RenderWrapper/RenderInstance.h"
//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//���ӷ�����
	class FK_DLL Emitter : public RenderObject, public RenderInstance
	{
	public:
		friend class ParticleSystem;

		//���ӷ���������
		enum Type
		{
			PET_Sprite,		//�������ӷ�����
			PET_Mesh,		//�������ӷ�����
		};

		//���ӷ�������������
		typedef Emitter* (*FnCreator)( const void* pParam );

	public:
		Type			mType;			//���ӷ���������

		Particle*		mpParticle;		//����ָ��
		UINT			mNumParticle;	//��ǰ��������

	public:
		Emitter( Type eType, Particle* pParticle );
		virtual ~Emitter() = 0;

	protected:
		//���·�����
		virtual void _UpdateEmitter( const float fFrameTime ) = 0;

		//��Ⱦ����
		void _RenderObj( const RenderParam* pParam, const Matrix4* pNodeMatrix );

		//��Ⱦ��������
		void _RenderAnimObj( const RenderParam* pParam, const AnimControl* pAnimControl, const Matrix4* pNodeMatrix );
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< Emitter* >	EmitterList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
