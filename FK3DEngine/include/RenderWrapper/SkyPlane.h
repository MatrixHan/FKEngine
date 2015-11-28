/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SkyPlane
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//�����
	class FK_DLL SkyPlane : public SkyEntity
	{
	protected:
		Texture*			mpBackgroundTexture;	//����������
		Texture*			mpSurfaceTexture;		//�������

		VertexDeclaration*	mpVD;					//��������
		VertexBuffer*		mpPositionVB;			//�������껺��
		VertexBuffer*		mpTexcoordVB;			//�������껺��

		float				mCloudUFactor;			//������� U ����仯ϵ��
		float				mCloudVFactor;			//������� V ����仯ϵ��
		float				mCloudU;				//������� U ֵ
		float				mCloudV;				//������� V ֵ

		float				mpUV[16];				//������������

	public:
		SkyPlane();
		virtual ~SkyPlane();

		//�����������
		void SetSkyTexture( Texture* pBackground, Texture* pSurface );

		//�����ƶ�����
		void SetMoveDirection( float fMoveFront, float fMoveRight );

		//���������
		void _UpdateSky( float fTimeSinceLastFrame );

		//��Ⱦ�����
		void _RenderSky();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
