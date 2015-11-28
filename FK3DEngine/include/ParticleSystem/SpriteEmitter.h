/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SpriteEmitter
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
	//�������ӷ�����
	class FK_DLL SpriteEmitter : public Emitter
	{
	public:
		friend class ParticleSystem;

		//�������Ӷ�������
		struct Vertex
		{
			float		x, y, z, w;		//��������
			DWORD		dwColor;		//������ɫ
			float		fU;				//�������� U
			float		fV;				//�������� V
		};
		typedef	Stack< Vertex >		VertexStack;

	protected:
		Vertex*				mpVertexData;		//�������Ӷ�������
		WORD*				mpIndexData;		//����������������
		UINT				mNumRenderParticle;	//��Ⱦ������������

	public:
		SpriteEmitter( Particle* pParticle );
		virtual ~SpriteEmitter() = 0;

	protected:
		//���¾������ӷ���
		virtual UINT _UpdateSprite( const Camera* pCamera ) = 0;

		//���ݾ���������Ļ�ռ�����������򶥵�����
		void _ReorderVertexData();

		//���¾������ӷ�������������
		void _UpdateVertexData( Vertex* pVerBuf, WORD* pIndexBuf, UINT nVertexOffset, UINT nIndexOffset );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
