/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	BitmapUtils
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
#include <windows.h>
//--------------------------------------------------------------------
FK2DEngine::CReader FK2DEngine::LoadFromPNG( CBitmap& p_Bitmap, CReader p_Reader )
{
	p_Bitmap = LoadImageFile( p_Reader );
	p_Reader.SetPosition( p_Reader.Resource().Size() );
	return p_Reader;
}
//--------------------------------------------------------------------
FK2DEngine::CReader FK2DEngine::LoadFromBMP( CBitmap& p_Bitmap, CReader p_Reader )
{
	return LoadFromPNG( p_Bitmap, p_Reader );
}
//--------------------------------------------------------------------
FK2DEngine::CWriter FK2DEngine::SaveToPNG( const CBitmap& p_Bitmap, CWriter p_Writer )
{
	SaveImageFile( p_Bitmap, p_Writer );
	return p_Writer.Resource().BackWrite();
}
//--------------------------------------------------------------------
#ifndef FK_IPHONE
FK2DEngine::CWriter FK2DEngine::SaveToBMP( const CBitmap& p_Bitmap, CWriter p_Writer )
{
	SaveImageFile( p_Bitmap, p_Writer, L"bmp" );
	return p_Writer.Resource().BackWrite();
}
#endif
//--------------------------------------------------------------------
void FK2DEngine::ApplyBorderFlags( CBitmap& p_DestBitmap, const CBitmap& p_SrcBitmap,
	unsigned int p_unSrcX, unsigned int p_unSrcY, unsigned int p_unSrcWidth,
	unsigned int p_unSrcHeight, unsigned int p_unBorderFlags )
{
	p_DestBitmap.Resize ( p_unSrcWidth + 2, p_unSrcHeight + 2 );

	if( p_unBorderFlags & EBF_TileableTop )
	{
		p_DestBitmap.Insert( p_SrcBitmap, 1, 0, p_unSrcX, p_unSrcY, p_unSrcWidth, 1 );
	}
	if( p_unBorderFlags & EBF_TileableBottom )
	{
		p_DestBitmap.Insert( p_SrcBitmap, 1, p_DestBitmap.Height() - 1 ,
			p_unSrcX, p_unSrcY + p_unSrcHeight - 1, p_unSrcWidth, 1 );
	}

	if( p_unBorderFlags & EBF_TileableLeft )
	{
		p_DestBitmap.Insert( p_SrcBitmap, 0, 1, p_unSrcX, p_unSrcY, 1, p_unSrcHeight );
	}
	if( p_unBorderFlags & EBF_TileableRight )
	{
		p_DestBitmap.Insert( p_SrcBitmap, p_DestBitmap.Width() - 1, 1, 
			p_unSrcX + p_unSrcWidth - 1, p_unSrcY, 1, p_unSrcHeight );
	}

	if(( p_unBorderFlags & EBF_TileableTop ) && ( p_unBorderFlags & EBF_TileableLeft ))
	{
		p_DestBitmap.SetPixel( 0, 0, p_SrcBitmap.GetPixel( p_unSrcX, p_unSrcY ) );
	}
	if(( p_unBorderFlags & EBF_TileableTop ) && ( p_unBorderFlags & EBF_TileableRight ))
	{
		p_DestBitmap.SetPixel( p_DestBitmap.Width() - 1, 0,
			p_SrcBitmap.GetPixel( p_unSrcX + p_unSrcWidth - 1, p_unSrcY ) );
	}
	if(( p_unBorderFlags & EBF_TileableTop ) && ( p_unBorderFlags & EBF_TileableLeft ))
	{
		p_DestBitmap.SetPixel( 0, p_DestBitmap.Height() - 1,
			p_SrcBitmap.GetPixel( p_unSrcX, p_unSrcY + p_unSrcHeight - 1 ) );
	}
	if(( p_unBorderFlags & EBF_TileableTop ) && ( p_unBorderFlags & EBF_TileableLeft ))
	{
		p_DestBitmap.SetPixel( p_DestBitmap.Width() - 1, p_DestBitmap.Height() - 1,
			p_SrcBitmap.GetPixel( p_unSrcX + p_unSrcWidth - 1, p_unSrcY + p_unSrcHeight - 1 ) );
	}

	p_DestBitmap.Insert( p_SrcBitmap, 1, 1, p_unSrcX, p_unSrcY, p_unSrcWidth, p_unSrcHeight );
}
//--------------------------------------------------------------------
//! ����һ��BMP�ļ�ͷ����   
static PBITMAPINFO CreateBitmapInfoStruct( HBITMAP p_hBmp )
{   
	BITMAP			bmp;    
	PBITMAPINFO		pbmi;    
	WORD			cClrBits;    

	// ��ȡBITMAP����ɫ��ʽ���߶ȣ����
	if (!GetObject(p_hBmp, sizeof(BITMAP), (LPSTR)&bmp))    
		return NULL;  
 
	// ������ɫ��ʽ������ռ���ֽ���
	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);    
	if (cClrBits == 1)    
		cClrBits = 1;    
	else if (cClrBits <= 4)    
		cClrBits = 4;    
	else if (cClrBits <= 8)    
		cClrBits = 8;    
	else if (cClrBits <= 16)    
		cClrBits = 16;    
	else if (cClrBits <= 24)    
		cClrBits = 24;    
	else cClrBits = 32;    

   
	// ����һ�� BITMAPINFO �ṹ�ڴ棨����BITMAPINFOHEADER�ṹ��һ��RGBQUAD�������飩
	if (cClrBits != 24)
	{
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR,    
		sizeof(BITMAPINFOHEADER) +    
		sizeof(RGBQUAD) * (1<< cClrBits));    
	}
	else
	{
		// 24λ���ظ�ʽû�� RGBQUAD ��������
		pbmi = (PBITMAPINFO) LocalAlloc(LPTR,    
		sizeof(BITMAPINFOHEADER));
	}
   
	// ��ʼ����� BITMAPINFO �ṹ
	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);    
	pbmi->bmiHeader.biWidth = bmp.bmWidth;    
	pbmi->bmiHeader.biHeight = bmp.bmHeight;    
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;    
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;    
	if (cClrBits < 24)    
		pbmi->bmiHeader.biClrUsed = (1<<cClrBits);    
	// ���BITMAPû��ѹ���������� BI_RGB ��ʽ
	pbmi->bmiHeader.biCompression = BI_RGB;    

	// ����֧��WindowsNT�����Կ��ʹ��DWORD������Windows 95/98/Me, ���Ӧ���� WORD������ʹ����RLEѹ����
	pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8   
		* pbmi->bmiHeader.biHeight;      
	pbmi->bmiHeader.biClrImportant = 0;    
	return pbmi;    
}
//--------------------------------------------------------------------
bool FK2DEngine::SaveHBITMAP2File( const std::wstring& p_pszFile, HBITMAP p_hBMP, HDC p_hDC )   
{   
	PBITMAPINFO pbi = CreateBitmapInfoStruct( p_hBMP );   

	HANDLE hf;					// �ļ����
	BITMAPFILEHEADER hdr;       // BITMAP �ļ�ͷ
	PBITMAPINFOHEADER pbih;     // BITMAP ��Ϣͷ
	LPBYTE lpBits;              // �ڴ�ָ��
	DWORD dwTotal;              // ���ֽ���
	DWORD cb;                   // �����ֽ���
	BYTE *hp;                   // �ֽ�ָ��
	DWORD dwTmp;    
	DWORD fileSizeInfo=0;

	pbih = (PBITMAPINFOHEADER) pbi;    
	lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);   

	if (!lpBits)    
		return false;  
  
	// ��DIB�м�����ɫ��
	if (!GetDIBits(p_hDC, p_hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi,    
		DIB_RGB_COLORS))    
	{   
		return false;    
	}   

	// ����BMP�ļ�
	fileSizeInfo = (DWORD) (sizeof(BITMAPFILEHEADER) +    
		pbih->biSize + pbih->biClrUsed    
		* sizeof(RGBQUAD) + pbih->biSizeImage); 
	if(fileSizeInfo==58)
		return false;
	hf = CreateFileW(p_pszFile.c_str(),    
		GENERIC_READ | GENERIC_WRITE,    
		(DWORD) 0,    
		NULL,    
		OPEN_ALWAYS,    
		FILE_ATTRIBUTE_NORMAL,    
		(HANDLE) NULL);    
	if (hf == INVALID_HANDLE_VALUE)    
		return FALSE;    
	hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
	// �ļ���С
	hdr.bfSize = fileSizeInfo;  

	hdr.bfReserved1 = 0;    
	hdr.bfReserved2 = 0;    

	// ������ɫ����ƫ��
	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +    
		pbih->biSize + pbih->biClrUsed    
		* sizeof (RGBQUAD);    
 
	// д�� BITMAPFILEHEADER ͷ
	if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER),    
		(LPDWORD) &dwTmp,  NULL))    
	{   
		return false;    
	}   
  
	// д�� BITMAPINFOHEADER ͷ �� RGBQUAD ����
	if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER)    
		+ pbih->biClrUsed * sizeof (RGBQUAD),    
		(LPDWORD) &dwTmp, ( NULL)))   
	{   
		return false;  
	}   

	// ������ɫ���ݵ�BMP�ļ���
	dwTotal = cb = pbih->biSizeImage;    
	hp = lpBits;    
	if (!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL))    
	{   
		return false;    
	}   

	// �ر�BMP�ļ�    
	if (!CloseHandle(hf))    
		return false;    

	// �ͷ��ڴ�
	GlobalFree((HGLOBAL)lpBits);   
	return true;   
}  
//--------------------------------------------------------------------