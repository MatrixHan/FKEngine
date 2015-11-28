/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BitmapGDIPlus
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "../include/Graphics.h"
#include "../include/Bitmap.h"
#include "../include/IO.h"
#include "../include/Platform.h"
#include "../include/StringConversion.h"
#include "../include/WinUtility.h"
#include "../../depend/boost/cstdint.hpp"
#include "../../depend/boost/algorithm/string.hpp"
#include <map>
#include <ObjIdl.h>
#include <GdiPlus.h>
#include <Windows.h>
//--------------------------------------------------------------------
namespace
{
	bool							g_bInitialized = false;
	ULONG_PTR						g_pToken;
	Gdiplus::GdiplusStartupInput	g_GDIInput;

	void ReshuffleBitmap( FK2DEngine::CBitmap& p_Bitmap )
	{
		boost::uint32_t* p = reinterpret_cast< boost::uint32_t* >( p_Bitmap.Data() );
		for( int i = p_Bitmap.Width() * p_Bitmap.Height(); i > 0; --i, ++p )
		{
			*p = (*p & 0xff00ff00 ) | ((*p << 16) & 0x00ff0000 ) | ((*p >> 16) & 0x000000ff );
		}
	}
	
	void Check( Gdiplus::Status p_Status, const char* p_szAction )
	{
		if( p_Status != Gdiplus::Ok )
		{
			std::string szErrorInfo;
			szErrorInfo.clear();

			switch( p_Status )
			{
			case Gdiplus::InvalidParameter:
				szErrorInfo = "��Ч����";
				break;
			}
			MessageBoxA( NULL, ( std::string( "GDI����ʱ�������� " ) + p_szAction + std::string( "\n����ԭ��") + szErrorInfo ).c_str(), NULL, NULL );
			throw std::runtime_error( std::string( "GDI����ʱ��������" ) + p_szAction );
		}
	}

	void CloseGDIPlus()
	{
		Gdiplus::GdiplusShutdown( g_pToken );
	}

	void RequireGDIPlus()
	{
		if( g_bInitialized )
		{
			return;
		}
		g_bInitialized = true;
		Check( Gdiplus::GdiplusStartup(&g_pToken, &g_GDIInput, NULL ), "��ʼ��GDI" );
		atexit( CloseGDIPlus );
	}

	FK2DEngine::CBitmap GdiPlusToFkEngine( Gdiplus::Bitmap& p_Bitmap )
	{
		FK2DEngine::CBitmap	Result;
		Result.Resize( p_Bitmap.GetWidth(), p_Bitmap.GetHeight() );

		GUID				guid;
		Check( p_Bitmap.GetRawFormat(&guid), "��ȡ��ʽGUID" );

		Gdiplus::BitmapData		Target;
		Target.Width		= Result.Width();
		Target.Height		= Result.Height();
		Target.PixelFormat	= PixelFormat32bppARGB;
		Target.Stride		= Result.Width() * 4;
		Target.Scan0		= Result.Data();

		Gdiplus::Rect			Rect( 0, 0, p_Bitmap.GetWidth(), p_Bitmap.GetHeight() );

		Check( p_Bitmap.LockBits( &Rect, Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeUserInputBuf,
			PixelFormat32bppARGB, &Target ), "�����ֽ�" );
		Check( p_Bitmap.UnlockBits(&Target), "�����ֽ�" );

		ReshuffleBitmap( Result );

		if( guid == Gdiplus::ImageFormatBMP )
		{
			ApplyColorKey( Result, FK2DEngine::CColor::FUCHSIA );
		}

		return Result;
	}

	boost::shared_ptr< IStream > ReadToIStream( FK2DEngine::CReader p_Reader )
	{
		unsigned int unRemaining = p_Reader.Resource().Size() - p_Reader.Position();
		HGLOBAL hBuffer = ::GlobalAlloc( GMEM_MOVEABLE, unRemaining );
		FK2DEngine::Win::Check( hBuffer );
		void* pBufferPtr = ::GlobalLock( hBuffer );
		if( !pBufferPtr )
		{
			::GlobalFree( hBuffer );
			FK2DEngine::Win::ThrowLastError();
		}

		p_Reader.Read( pBufferPtr, p_Reader.Resource().Size() - p_Reader.Position() );

		IStream* pStream = NULL;
		if( ::CreateStreamOnHGlobal( hBuffer, TRUE, &pStream ) != S_OK )
		{
			::GlobalFree( hBuffer );
			throw std::runtime_error( "����IStreamʧ��" );
		}

		return FK2DEngine::Win::ShareComPtr( pStream );
	}

	CLSID& EncoderFromMimeType( const std::wstring& p_szMimeType )
	{
		static std::map< std::wstring, CLSID >			s_Cache;
		if( s_Cache.count( p_szMimeType ) )
		{
			return s_Cache[p_szMimeType];
		}

		UINT unNum = 0;
		UINT unSize = 0;

		Check( Gdiplus::GetImageEncodersSize( &unNum, &unSize ), "�������" );

		unsigned int unVecSize = ( unSize + sizeof( Gdiplus::ImageCodecInfo ) - 1 ) / sizeof( Gdiplus::ImageCodecInfo );

		std::vector< Gdiplus::ImageCodecInfo >		Codecs( unVecSize );

		Check( Gdiplus::GetImageEncoders( unNum, unSize, &Codecs[0] ), "ö�ٱ���" );

		for( unsigned int i = 0; i < unNum; ++i )
		{
			if( Codecs[i].MimeType == p_szMimeType )
			{
				return s_Cache[p_szMimeType] = Codecs[i].Clsid;
			}
		}

		throw std::runtime_error( "û�к��ʵı��뷽ʽ�ṩ�� " + FK2DEngine::WstringToUTF8( p_szMimeType ) );
	}

	CLSID EncoderFromHint( const std::wstring& p_szFormatHint )
	{
		std::wstring::size_type	Index = p_szFormatHint.rfind( '.' );
		std::wstring szMimeType = L"image/";
		if( Index == std::wstring::npos )
		{
			szMimeType += p_szFormatHint;
		}
		else
		{
			szMimeType += p_szFormatHint.substr( Index + 1 );
		}

		boost::to_lower( szMimeType );

		if( szMimeType == L"image/jpg" )
		{
			szMimeType = L"image/jpeg";
		}
		else if( szMimeType == L"image/tif" )
		{
			szMimeType = L"image/tiff";
		}

		return EncoderFromMimeType( szMimeType );
	}
}	
//--------------------------------------------------------------------
FK2DEngine::CBitmap FK2DEngine::LoadImageFile( const std::wstring& p_szFileName )
{
	RequireGDIPlus();

	Gdiplus::Bitmap Bitmap( p_szFileName.c_str() );
	Check( Bitmap.GetLastStatus(), ("��ȡ" + WstringToUTF8( p_szFileName ) ).c_str() );
	return GdiPlusToFkEngine( Bitmap );
}
//--------------------------------------------------------------------
FK2DEngine::CBitmap FK2DEngine::LoadImageFile( CReader p_Input )
{
	RequireGDIPlus();

	boost::shared_ptr< IStream >	pStream = ReadToIStream( p_Input );
	Gdiplus::Bitmap Bitmap( pStream.get() );
	Check( Bitmap.GetLastStatus(), "���ڴ��ж�ȡһ��λͼ" );
	return GdiPlusToFkEngine( Bitmap );
}
//--------------------------------------------------------------------
void FK2DEngine::SaveImageFile( const CBitmap& p_Bitmap, const std::wstring& p_szFileName )
{
	CBitmap input = p_Bitmap;
	if( boost::iends_with( p_szFileName, "bmp" ) )
	{
		UnApplyColorKey( input, CColor::FUCHSIA );
	}

	ReshuffleBitmap( input );

	Gdiplus::Bitmap Output( input.Width(), input.Height(), input.Width() * 4,
		PixelFormat32bppARGB, (BYTE*)input.Data() );
	Check( Output.GetLastStatus(), "���ڴ��д���һ��λͼ" );

	Check( Output.Save( p_szFileName.c_str(), &EncoderFromHint( p_szFileName )),
		( "д��" + WstringToUTF8( p_szFileName )).c_str() );
}
//--------------------------------------------------------------------
void FK2DEngine::SaveImageFile( const CBitmap& p_Bitmap, FK2DEngine::CWriter p_Writer,
							 const std::wstring& p_szFormatHint /*= L"png"*/ )
{
	CBitmap input = p_Bitmap;
	if( boost::iends_with( p_szFormatHint, "bmp" ) )
	{
		UnApplyColorKey( input, CColor::FUCHSIA );
	}

	ReshuffleBitmap( input );

	Gdiplus::Bitmap Output( input.Width(), input.Height(), input.Width() * 4,
		PixelFormat32bppARGB, (BYTE*)input.Data() );
	Check( Output.GetLastStatus(), "���ڴ��д���һ��λͼ" );

	IStream* pStream = NULL;
	if( CreateStreamOnHGlobal( 0, TRUE, &pStream ) != S_OK )
	{
		throw std::runtime_error( "�޷�����׼����д���IStream" );
	}

	boost::shared_ptr< IStream >	pStreamGuard( FK2DEngine::Win::ShareComPtr( pStream ) );
	Check( Output.Save( pStream, &EncoderFromHint( p_szFormatHint ) ), "����һ��λͼ���ڴ���" );

	HGLOBAL Buffer;
	GetHGlobalFromStream( pStream, &Buffer );
	void* pBufferPtr = GlobalLock( Buffer );
	if( !pBufferPtr )
	{
		Win::ThrowLastError();
	}
	
	p_Writer.Write( pBufferPtr, GlobalSize(Buffer) );
	GlobalUnlock( Buffer );
}
//--------------------------------------------------------------------