/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Bitmap
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "Color.h"
#include "InsidePreInclude.h"
#include "GraphicsBase.h"
#include "Platform.h"
#include "../../depend/boost/scoped_ptr.hpp"
#include <string>
#include <vector>
#include <Windows.h>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	class CBitmap
	{
	private:
		unsigned int				m_unWidth;
		unsigned int				m_unHeight;
		std::vector< CColor >		m_vecPixels;
	public:
		CBitmap() 
			: m_unWidth( 0 )
			, m_unHeight( 0 )
		{

		}

		CBitmap( unsigned int p_unWidth, unsigned int p_unHeight, CColor p_Color = CColor::NONE )
			: m_unWidth( p_unWidth )
			, m_unHeight( p_unHeight )
			, m_vecPixels( p_unHeight * p_unWidth, p_Color )
		{

		}

		unsigned int Width() const
		{
			return m_unWidth;
		}

		unsigned int Height() const
		{
			return m_unHeight;
		}

		CColor GetPixel( unsigned int p_unX, unsigned int p_unY ) const
		{
			return m_vecPixels[ p_unY * m_unWidth + p_unX ];
		}

		void SetPixel( unsigned int p_unX, unsigned int p_unY, CColor p_Color )
		{
			m_vecPixels[ p_unY * m_unWidth + p_unX ] = p_Color;
		}

		void Swap( CBitmap& p_Other );
		void Resize( unsigned int p_unWidth, unsigned int p_unHeight, CColor p_Color = CColor::NONE );
		//! ��ָ��λ�����һ��ͼƬ����ͼƬ���������򱻲ü�
		void Insert( const CBitmap& p_Source, int p_nX, int p_nY );
		void Insert( const CBitmap& p_Source, int p_nX, int p_nY, unsigned int p_unSrcX,
			unsigned int p_unSrcY, unsigned int p_unSrcWidth, unsigned int p_unSrcHeight ); 

		const CColor* Data() const
		{
			return &m_vecPixels[0];
		}
		CColor* Data()
		{
			return &m_vecPixels[0];
		}

		FK_DEPRECATED void Fill( CColor p_Color );
		FK_DEPRECATED void Replace( CColor p_OldColor, CColor p_NewColor );
	};


	//! ��ȡͼƬ�ļ�
	CBitmap LoadImageFile( const std::wstring& p_szFileName );
	CBitmap LoadImageFile( CReader p_Input );

	//! ����ͼƬ�ļ�
	void SaveImageFile( const CBitmap& p_Bitmap, const std::wstring& p_szFileName );
	void SaveImageFile( const CBitmap& p_Bitmap, FK2DEngine::CWriter p_Writer, const std::wstring& p_szFormatHint = L"png" );
	bool SaveHBITMAP2File( const std::wstring& pszFile, HBITMAP p_hBMP, HDC p_hDC );

	//! ������ɫ���� key ֵ�����ص� alpha ֵΪ 0
	void ApplyColorKey( CBitmap& p_Bitmap, CColor p_Key );
	//! �������� alpha ֵΪ 0 �����ص�Ϊ BackGround ָ������ɫ
	void UnApplyColorKey( CBitmap& p_Bitmap, CColor p_BackGround );

	void ApplyBorderFlags( CBitmap& p_DestBitmap, const CBitmap& p_SrcBitmap,
		unsigned int p_unSrcX, unsigned int p_unSrcY, unsigned int p_unSrcWidth,
		unsigned int p_unSrcHeight, unsigned int p_unBorderFlags );

	FK_DEPRECATED CReader LoadFromBMP( CBitmap& p_Bitmap, CReader p_Reader );
	FK_DEPRECATED CWriter SaveToBMP( const CBitmap& p_Bitmap, CWriter p_Writer );
	FK_DEPRECATED CReader LoadFromPNG( CBitmap& p_Bitmap, CReader p_Reader );
	FK_DEPRECATED CWriter SaveToPNG( const CBitmap& p_Bitmap, CWriter p_Writer );
}