/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	FKEngineInclude
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "../include/System.h"
#include "../include/Audio.h"
#include "../include/Bitmap.h"
#include "../include/Color.h"
#include "../include/Directories.h"
#include "../include/Font.h"
#include "../include/Graphics.h"
#include "../include/Image.h"
#include "../include/ImageData.h"
#include "../include/Input.h"
#include "../include/Inspection.h"
#include "../include/IO.h"
#include "../include/Math.h"
#include "../include/Platform.h"
#include "../include/Text.h"
#include "../include/TextInput.h"
#include "../include/Timing.h"
#include "../include/StringConversion.h"
#include "../include/FKWindow.h"
#include "../include/FKVersion.h"
#include "../include/Timer.h"
#include "../include/MsgListenerManager.h"
#include "../include/LogManager.h"
#include "../include/Exception.h"
#include "../include/FKSharedPtr.h"
#include "../include/ZPos.h"
#include "../include/Singleton.h"
#include "../include/Archive.h"
#include "../include/ArchiveFactory.h"
#include "../include/ArchiveManager.h"
#include "../include/DataStream.h"
#include "../include/ZipArchive.h"
#include "../include/ZipArchiveFactory.h"
#include "../include/ZipDataStream.h"
#include "../include/FileDataStream.h"
#include "../include/FileSystemArchive.h"
#include "../include/FileSystemArchiveFactory.h"
#include "../Include/UIInputManager.h"
#include "../Include/UIControl.h"
#include "../Include/UserMsgNotify.h"
#include "../Include/UIManager.h"
#include "../Include/WinControl.h"
#include "../Include/Panel.h"
#include "../Include/Form.h"
#include "../Include/PicButton.h"
#include "../Include/Button.h"
#include "../Include/CheckBox.h"
#include "../Include/RadioButton.h"
#include "../Include/Label.h"
#include "../Include/ImageControl.h"
#include "../include/ScrollBar.h"
#include "../include/Edit.h"
#include "../include/AnimationCursorManager.h"
#include "../include/IniFile.h"

//--------------------------------------------------------------------

//! �޸Ŀ���̨���ʹ�����ں���
#ifdef USE_FK_CONSOLE

#else
	#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif
//--------------------------------------------------------------------
//! ����Ϊ1����ջչ�����뽫�����뵽���У����쳣�׳�ʱ����ʾ���ö�ջ
#ifndef FK_STACK_UNWINDING
#define FK_STACK_UNWINDING 1
#endif
//--------------------------------------------------------------------
//! ����ģʽ
/*
0 - Debugģʽʹ�ñ�׼���ԣ�Releaseģʽû���κ�����
1 - Debugģʽʹ�ñ�׼���ԣ�Releaseģʽʹ���쳣����
2 - Debugģʽʹ���쳣���ƣ�Releaseģʽʹ���쳣����
*/
#ifndef FK_ASSERT_MODE
#define FK_ASSERT_MODE 1 
#endif
//--------------------------------------------------------------------

using namespace FK2DEngine;