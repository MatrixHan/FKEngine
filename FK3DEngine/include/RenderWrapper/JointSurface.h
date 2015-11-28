/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	JointSurface
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	ƴ��ͼ����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//ƴ��ͼ���ࣨ����ʵ�ִ���ͼ��Ķ�������ƴ����ʾ������
	class FK_DLL JointSurface : public OverlaySurface
	{
	public:
		float				mfWidth;		//��Ⱦ���
		float				mfHeight;		//��Ⱦ�߶�

		UINT				mPicWidth;		//ͼ��ʵ�ʿ��
		UINT				mPicHeight;		//ͼ��ʵ�ʸ߶�

		UINT				mNumTextures;	//����ƴ�ӵ���������
		TextureList			mTextureList;	//����ƴ�ӵ�����ָ��

		bool				mbDynamic;		//�Ƿ�Ϊ��Ҫ��̬���µ�ƴ��ͼ��
		OverlayVertex*		mpVertexData;	//ƴ��ͼ�񶥵�����

	protected:
		UINT				mNumCols;		//������������
		UINT				mNumRows;		//������������
		UINT				mPerWidth;		//ÿ������Ŀ��
		UINT				mPerHeight;		//ÿ������ĸ߶�
		UINT				mRemWidth;		//���һ�������ʹ�ÿ��
		UINT				mRemHeight;		//���һ�������ʹ�ø߶�
		UINT				mActWidth;		//���һ�������ʵ�ʿ��
		UINT				mActHeight;		//���һ�������ʵ�ʸ߶�

	public:
		JointSurface( ZOrderType eZType, OverlaySurface* pZRefOverlay, TextureFilterType eFilterType );
		~JointSurface();

		//����ƴ��ͼ��
		void CreateJointSurface( float fLeft, float fTop, float fWidth, float fHeight, UINT nTexWidth, UINT nTexHeight,
			PixelFormat ePixelFormat, bool bDynamic = false, DWORD color = 0xFFFFFFFF );

		//��ͼ���ļ�������ƴ��ͼ������ߴ�ΪͼƬ�ߴ磩
		void LoadJointSurfaceFromFile( float fLeft, float fTop, float fWidth, float fHeight, FileObject* pFile,
			const char* szName, PixelFormat ePixelFormat, bool bDynamic = false, DWORD color = 0xFFFFFFFF );

		//����ƴ��ͼ��λ��
		void FKFastcall SetLocation( float fLeft, float fTop );

		//����ƴ��ͼ����ɫ
		void FKFastcall SetColor( DWORD color );

		//��ȡ��ƴ��ͼ�������
		Texture* GetTexture( UINT nNumTexture = 0 );

	protected:
		//����ƽ��ͼ�񶥵�
		void FKFastcall _ProcessVertex();

		//��Ⱦƽ��ͼ��
		void FKFastcall _RenderOverlay();
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< JointSurface* >	JointList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
