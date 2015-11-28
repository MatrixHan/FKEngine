/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ZPos
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
namespace FK2DEngine
{
	enum ENUM_DefaultZPos
	{
		eDZP_None = 0,

		eDZP_BackGroudBegin		= 100,		// ���������²�
		eDZP_BackGroudEnd		= 200,		// ���������ϲ�

		eDZP_TerrainBegin		= 300,		// ���β����²�
		eDZP_TerrainEnd			= 400,		// ���β����ϲ�

		eDZP_TerrainBuildBegin	= 500,		// ���ν������²�
		eDZP_TerrainBeginEnd	= 600,		// ���ν������ϲ�

		eDZP_SpritBegin			= 700,		// ���ξ������²�
		eDZP_SpritEnd			= 800,		// ���ξ������ϲ�

		eDZP_SceneParticleBegin	= 900,		// �����������²�
		eDZP_SceneParticleEnd	= 1000,		// �����������ϲ�

		eDZP_UIBegin			= 1100,		// UI���²�
		eDZP_UIEnd				= 1200,		// UI���ϲ�

		eDZP_CursorBegin		= 1300,		// ������²�


		eDZP_Max = 0xffff,
	};
}