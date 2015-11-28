/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	OverlaySurface
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	ƽ��ͼ����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	// Z ˳����������
	enum ZOrderType
	{
		ZOT_Top,		//���ϲ㣨�����Ⱦ��
		ZOT_Bottom,		//���²㣨������Ⱦ��
		ZOT_Upon,		//ָ��ƽ��ͼ��֮�ϣ�����Ⱦ��
		ZOT_Below,		//ָ��ƽ��ͼ��֮�£�����Ⱦ��
	};

	//ƽ��ͼ�񶥵�ṹ
	struct OverlayVertex
	{
		float	x, y, z;	//����
		DWORD	color;		//��ɫ
		float	u, v;		//��������
	};

	//--------------------------------------------------------------------------------------------------------------
	//ƽ��ͼ���ࣨ����ʵ�ִ���ͼ��Ķ�������ƴ����ʾ������
	class FK_DLL OverlaySurface
	{
	public:
		friend class OverlayManager;

	public:
		bool				mbVisable;		//�Ƿ�ɼ�
		TextureFilterType	mFilterType;	//�����������

	protected:
		OverlayVertex*		mpVertexPtr;	//��������ָ��
		UINT				mNumVertex;		//��������
		UINT				mVertexOffset;	//��Ⱦ����ƫ����

	public:
		OverlaySurface( ZOrderType eZType, OverlaySurface* pZRefOverlay, TextureFilterType eFilterType );
		virtual ~OverlaySurface();

		//����ƽ��ͼ��ɼ�״̬
		void FKFastcall SetVisable( bool bVisable );

		//����ƽ��ͼ�� Z ˳��
		void FKFastcall SetZOrder( ZOrderType eZType, OverlaySurface* pZRefOverlay = NULL );

		//����ƽ��ͼ�������������
		void FKFastcall SetFilterType( TextureFilterType eFilterType );

	protected:
		//����ƽ��ͼ�񶥵�
		UINT FKFastcall _UpdateVertex( OverlayVertex* pVertexBuf, UINT nOffset );

		//����ƽ��ͼ�񶥵�
		virtual void FKFastcall _ProcessVertex() = 0;

		//��Ⱦƽ��ͼ��
		virtual void FKFastcall _RenderOverlay() = 0;
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< OverlaySurface* >	OverlayList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
