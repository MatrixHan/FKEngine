/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SkyBox
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��պ�
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��պ���������
	struct SkyBoxTexture
	{
		Texture*	pTopTexture;		//��������
		Texture*	pFrontTexture;		//ǰ������
		Texture*	pBackTexture;		//��������
		Texture*	pLeftTexture;		//��������
		Texture*	pRightTexture;		//��������
	};
	//--------------------------------------------------------------------------------------------------------------
	//��պ�
	class FK_DLL SkyBox : public SkyEntity
	{
	public:
		Texture*			mpTopTexture;		//��������
		Texture*			mpFrontTexture;		//ǰ������
		Texture*			mpBackTexture;		//��������
		Texture*			mpLeftTexture;		//��������
		Texture*			mpRightTexture;		//��������

	protected:
		VertexDeclaration*	mpVD;				//��������
		VertexBuffer*		mpPositionVB;		//�������껺��
		VertexBuffer*		mpTexcoordVB;		//�������껺��

	public:
		SkyBox();
		~SkyBox();

		//������պ�����
		void SetSkyBoxTexture( SkyBoxTexture* pSkyBoxTexture );

		//���������
		void _UpdateSky( float fTimeSinceLastFrame );

		//��Ⱦ�����
		void _RenderSky();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
