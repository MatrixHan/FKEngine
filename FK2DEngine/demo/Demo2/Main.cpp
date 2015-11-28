/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Main
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../interface/FKEngineInclude.h"
#include "../../../depend/boost/scoped_ptr.hpp"

//--------------------------------------------------------------------
#ifdef _DEBUG
#pragma comment(lib, "FK2DEngine_D.lib")
#else
#pragma comment(lib, "FK2DEngine.lib")

#endif
//--------------------------------------------------------------------
class CGameWindow : public FK2DEngine::CFKWindow
{
	static const unsigned long		SELECTION_COLOR = 0x66000000;
private:
	boost::scoped_ptr< FK2DEngine::CImage >			m_pBackgroundImage;
	boost::scoped_ptr< FK2DEngine::CImage >			m_pNameTitleImage;
	FK2DEngine::CImage*								m_pBodyImage;
	boost::scoped_ptr< FK2DEngine::CImage >			m_pSmallHeadImage;
	boost::scoped_ptr< FK2DEngine::CSong >			m_pSong;
	FK2DEngine::CBitmap								m_pBitmap;
	FK2DEngine::CBuffer*							m_pSongBuffer;
	FK2DEngine::CReader*							m_pReader;
	FK2DEngine::CFont								m_NameFont;
	FK2DEngine::CFont								m_NameFontBack;
	FK2DEngine::CFont								m_Font;
	FK2DEngine::CFont								m_FontBack;
public:
	CGameWindow()
		: CFKWindow( 1024, 768, false )
		, m_NameFont( Graphics(), L"����", 28, FK2DEngine::EFF_None )
		, m_NameFontBack( Graphics(), L"����", 28, FK2DEngine::EFF_None )
		, m_Font( Graphics(), L"Arial", 25, 0 )
		, m_FontBack( Graphics(), L"Arial", 25, 0 )
	{
 		SetCaption( L"FreeKnightEngine : AVG��ϷDemo" );

		// ��ʾͼƬ
		std::wstring szFileName = FK2DEngine::ShareResourcePrefix() + L"avgRc/background.png";
		m_pBackgroundImage.reset( new FK2DEngine::CImage( Graphics(), szFileName, false ) );

		szFileName = FK2DEngine::ShareResourcePrefix() + L"avgRc/nametitle.PNG";
		m_pNameTitleImage.reset( new FK2DEngine::CImage( Graphics(), szFileName, false ) );

		szFileName = FK2DEngine::ShareResourcePrefix() + L"avgRc/Body.bmp";
		m_pBodyImage = new FK2DEngine::CImage( Graphics(), szFileName, false );

		szFileName = FK2DEngine::ShareResourcePrefix() + L"avgRc/SmallHead.png";
		m_pSmallHeadImage.reset( new FK2DEngine::CImage( Graphics(), szFileName, false ) );

		// �������
		szFileName = FK2DEngine::ShareResourcePrefix() + L"avgRc/Attack.cur";
		SetNewCursor( szFileName );
		
		// �����־
		SSLogManager::Instance()->LogMessage( std::wstring( L"-------- LogBegin --------" ) );

		// �����ļ������ļ�
		CArchiveFactory* pSystemArchiveFactory = new CFileSystemArchiveFactory();
		SSArchiveManager::Instance()->AddArchiveFactory( pSystemArchiveFactory );
		CFileSystemArchive *pFileSystem = static_cast< CFileSystemArchive *>( SSArchiveManager::Instance()->Load( FK2DEngine::ShareResourcePrefix() + L"rc", L"FileSystem"));
		StringVectorPtr pStrVectorFileSystem = pFileSystem->List(true);

		// ��ȡZip�ļ�
		CArchiveFactory* pZipArchiveFactory = new CZipArchiveFactory();
		SSArchiveManager::Instance()->AddArchiveFactory( pZipArchiveFactory );
		CZipArchive* pZipArchive = static_cast< CZipArchive* >( SSArchiveManager::Instance()->Load( FK2DEngine::ShareResourcePrefix() + L"rc/Media/����Zip.zip", L"Zip"));
		StringVectorPtr pStrVectorZip = pZipArchive->List( true );
#ifdef USE_TEST_ZIP
		DataStreamPtr pDataStream = pZipArchive->Open( L"�صФ���.MP3" );
		unsigned int unSize = pDataStream.GetPointer()->Size();
		char* pBuf = new char[ unSize ];
		pDataStream.GetPointer()->Read( static_cast< void* >( pBuf ), unSize );
#else
		// ��ȡZip�ļ�����2
		DataStreamPtr pDataStream = pFileSystem->OpenZipFile( L"/Media/����Zip.zip", L"eternal.MP3", "123456" );
		unsigned int unSize = pDataStream.GetPointer()->Size();
		char* pBuf = new char[ unSize ];
		pDataStream.GetPointer()->Read( static_cast< void* >( pBuf ), unSize );
#endif
		m_pSongBuffer = new FK2DEngine::CBuffer( pBuf, unSize );
		m_pReader = new CReader( *m_pSongBuffer, unSize );
		m_pReader->SetPosition( 0 );
		m_pSong.reset( new FK2DEngine::CSong( *m_pReader ));
		m_pSong->Play( true );

		// ���ö�̬���
		//szFileName = FK2DEngine::ShareResourcePrefix() + L"avgRc\\AnimCursor.png";
		//m_pBitmap = LoadImageFile( szFileName );
		//SSAnimationCursorManager::Instance()->AddCursor( m_pBitmap, L"Ĭ�����", 32, 32 );
		//SSAnimationCursorManager::Instance()->SetAnimCursor( L"Ĭ�����" );
		//SSAnimationCursorManager::Instance()->Enable( true );
	}
public:
	void FKDraw()
	{
		m_pBackgroundImage->FKDraw( 0, 0, 0 );
		m_pNameTitleImage->FKDraw( 50, 580, 4 );
		m_pSmallHeadImage->FKDraw( 50, 380, 2 );
		m_NameFont.FKDraw( L"������ʿ��־", 65, 587, 6, 1, 1, FK2DEngine::CColor( 0xffafff30 ) );
		m_NameFontBack.FKDraw( L"������ʿ��־", 66, 588, 5, 1, 1, FK2DEngine::CColor( 0xff6fff50 ) );
		m_pBodyImage->FKDraw( 550, 150, 1, 1.0, 1.0, 0xffffffff, FK2DEngine::EAM_Mutiply );
		m_Font.FKDraw( L"����һ��AVG��ϷDemo�����ڲ������湦��..", 85, 625, 6, 1, 1, FK2DEngine::CColor::WHITE );
		m_FontBack.FKDraw( L"����һ��AVG��ϷDemo�����ڲ������湦��..", 86, 626, 5, 1, 1, FK2DEngine::CColor::GRAY );
		
		Graphics().DrawQuad(
			75,		600,			SELECTION_COLOR,
			75,		730,			SELECTION_COLOR,
			950,		600,		SELECTION_COLOR,
			950,		730,		SELECTION_COLOR,  3
			);
	}

	void KeyDown( FK2DEngine::CKey p_Key )
	{
		if( p_Key == FK2DEngine::EKB_Escape )
		{
			Close();
		}
		else if( p_Key == FK2DEngine::MS_WheelUp )
		{
			m_pSong->ChangeVolume( m_pSong->Volume() - 0.05 );
		}
		else if( p_Key == FK2DEngine::MS_WheelDown )
		{
			m_pSong->ChangeVolume( m_pSong->Volume() + 0.05 );
		}
		else if( p_Key == FK2DEngine::EKB_Space )
		{
 			if( m_pSong->Playing() )
			{
				m_pSong->Pause();
			}
			else if( m_pSong->Paused() )
			{
				m_pSong->Play( true );
			}
		}
		else if( p_Key == FK2DEngine::EKB_PrintScreen )
		{
			PrintScreen( FK2DEngine::ShareResourcePrefix() + L"Screen\\" + ToString( GetTime() ) + L".bmp" );
		}
	}
};
//--------------------------------------------------------------------
int main( int p_nArgc, char* p_Argv[] )
{
	CGameWindow window;
	window.Show();
}
//--------------------------------------------------------------------
