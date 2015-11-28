/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GraphicsBase
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "Platform.h"
#include <limits>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//! ���ֵ����ȸߵĽ��������ֵ�͵�ͼԪ
	typedef double ZPos;

	//! ����ͼԪ��Alpha��ɫ��Ϸ�ʽ
	enum ENUM_AlphaMode
	{
		EAM_Default,			// Ĭ������ͼԪ��ֵ��ϡ�255�ǲ�͸����
		EAM_Additive,			// ����ͼԪ�ӷ����
		EAM_Mutiply,			// ����ͼԪ�˷����( ȥ���׵� )
		EAM_SrcAlphaOne,
		EAM_OneSrcAlpha,
	};

	//! �����ʽ��ʶ
	enum ENUM_FontFlags
	{
		EFF_None			= 0,
		EFF_Bold			= 1,
		EFF_Italic			= 2,
		EFF_Underline		= 4,
		EFF_Combinations	= 8
	};

	//! ����ƫ�Ʒ�ʽ
	enum ENUM_TextAlign
	{
		ETA_Left,
		ETA_Right,
		ETA_Center,
		ETA_Justify
	};

	//! �ü���ʽ
	enum ENUM_BorderFlags
	{
		EBF_Smooth				= 0,
		EBF_TileableLeft		= 1,			// ����ü�
		EBF_TileableTop			= 2,			// ���ϲü�
		EBF_TileableRight		= 4,			// ���Ҳü�
		EBF_TileableBottom		= 8,			// ���²ü�
		EBF_Tileable = EBF_TileableLeft | EBF_TileableTop | EBF_TileableRight | EBF_TileableBottom,
	};


	#ifndef SWIG
		FK_DEPRECATED const double zImmediate = -std::numeric_limits< double >::infinity();
	#endif
}