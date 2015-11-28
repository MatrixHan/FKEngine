/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	SkySphere
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
	class FK_DLL SkySphere : public SkyEntity
	{
	protected:
		UINT				mRing;				//����
		UINT				mSegment;			//����
		UINT				mNumVertex;			//��������
		UINT				mNumIndex;			//��������
		UINT				mNumFace;			//����������

		Matrix4				mSkyWorldMatrix;	//�������Ⱦ�������

		Texture*			mpTexture;			//���������

		VertexDeclaration*	mpVD;				//��������
		VertexBuffer*		mpPositionVB;		//�������껺��
		VertexBuffer*		mpTexcoordVB;		//�������껺��
		IndexBuffer*		mpIB;				//��������

		float				mRotaValue;			//�����ٶ�
		float				mRotaDegree;		//����ֵ
		Vector3				mRotaAxis;			//������

	public:
		SkySphere( UINT nNumRing, UINT nNumSegment );
		virtual ~SkySphere();

		//�������������
		void SetSphereTexture( Texture* pTexture );

		//���ñ����ת
		void SetSurfaceRotation( float fRotaVale, const Vector3& vAxis );

		//���������
		void _UpdateSky( float fTimeSinceLastFrame );

		//��Ⱦ�����
		void _RenderSky();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
