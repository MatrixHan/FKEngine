/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Graphics
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "InsidePreInclude.h"
#include "Color.h"
#include "GraphicsBase.h"
#include "../../depend/boost/array.hpp"
#include "../../depend/boost/function.hpp"
#include "../../depend/boost/scoped_ptr.hpp"
#include <memory>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//! ������Ļ��ǰ�ֱ��ʿ�ȣ����أ�
	unsigned int	ScreenWidth();
	unsigned int	ScreenHeigth();

	//! �������ߴ�
	unsigned int const MAX_TEXTURE_SIZE		= 1026;//1024; Ϊ��֧��1024��С��ͼ

	typedef boost::array< double, 16 >		Transform;

	Transform Translate( double p_dX, double p_dY );
	Transform Rotate( double p_dAngle, double p_dAroundX = 0, double p_dAroundY = 0 );
	Transform Scale( double p_dFactor );
	Transform Scale( double p_dFactorX, double p_dFactorY, double p_dFromX = 0.0, double p_dFromY = 0.0 );

	class CGraphics
	{
	private:
		struct							SImpl;
		boost::scoped_ptr< SImpl >		m_pImpl;
	public:
		CGraphics( unsigned int p_unPhysicalWidth, unsigned int p_unPhysicalHeight, bool p_bFullScreen );
		~CGraphics();
	public:
		void	SetResolution( unsigned int p_unVirtualWidth, unsigned int p_unVirtualHeight );
	
		unsigned int	Width() const;
		unsigned int	Height() const;
		bool			FullScreen() const;

		//! ����D3D�� BeginScene �� EndScene��������Ⱦ���������������������Ⱦ��
		bool	Begin( CColor p_ClearColor = CColor::BLACK );
		void	End();

		//! ������ z ����
		void	Flush();

		//! ���������Ⱦ�������������һ��ȫ�µ���Ⱦ����
		void	BeginGL();
		//! ������Ⱦ״̬
		void	EndGL();

		//! �����������һ���ɾ���FL�������ڽ��ж� z ��������������BeginGL/EndGL֮�䣩
		void	ScheduleGL( const boost::function< void() >& p_Functor, ZPos p_Z );
	
		//! ��������βü�
		void	BeginClipping( double p_dX, double p_dY, double p_dWidth, double p_dHeight );
		//! �رղü�
		void	EndClipping();

		//! ��¼
		void	BeginRecording();
		std::auto_ptr< FK2DEngine::CImageData >	EndRecording();

		//! ���һ��ת����¼��ת����¼ջ��
		void	PushTransform( const Transform& p_Transform );
		void	PopTransform();

		//! ��һ������Ƶ�����һ���������
		void	DrawLine( double p_dX1, double p_dY1, CColor p_Color1,
			double p_dX2, double p_dY2, CColor p_Color2,
			ZPos p_Z, ENUM_AlphaMode p_eMode = EAM_Default );

		void	DrawTriangle( double p_dX1, double p_dY1, CColor p_Color1,
			double p_dX2, double p_dY2, CColor p_Color2,
			double p_dX3, double p_dY3, CColor p_Color3,
			ZPos p_Z, ENUM_AlphaMode p_eMode = EAM_Default );

		void	DrawQuad( double p_dX1, double p_dY1, CColor p_Color1,
			double p_dX2, double p_dY2, CColor p_Color2,
			double p_dX3, double p_dY3, CColor p_Color3,
			double p_dX4, double p_dY4, CColor p_Color4,
			ZPos p_Z, ENUM_AlphaMode p_eMode = EAM_Default );

		//! ��һ��ͼƬ�ж�ȡ����ͼƬ���л���
		std::auto_ptr< CImageData > CreateImage( const CBitmap& p_Src,
			unsigned int p_unSrcX, unsigned int p_unSrcY, unsigned int p_unSrcWidth,
			unsigned int p_unSrcHeight, unsigned int p_unBorderFlags );
	};
}