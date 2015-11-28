/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	Texture
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "InsidePreInclude.h"
#include "Bitmap.h"
#include "GraphicsCommon.h"
#include "TexChunk.h"
#include "BlockAllocator.h"
#include "../../depend/boost/cstdint.hpp"
#include "../../depend/boost/shared_ptr.hpp"
#include <vector>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	class CTexture
	{
	private:
		CBlockAllocator		m_Allocator;
		GLuint				m_Name;
		unsigned int		m_unNum;
	public:
		CTexture( unsigned int p_unSize );
		~CTexture();
	public:
		unsigned int Size() const;
		GLuint TexName() const;
		std::auto_ptr< CTexChunk >	TryAlloc( CGraphics& pGraphics, Transforms& p_Transforms,
			DrawOpQueueStack& p_Queues, boost::shared_ptr< CTexture > p_Ptr,
			const CBitmap& p_Bitmap, unsigned int p_unPadding );
		void Free( unsigned int p_unX, unsigned int p_unY );
		FK2DEngine::CBitmap ToBitmap( unsigned int p_unX, unsigned int p_unY,
			unsigned int p_unWidth, unsigned int p_unHeight )const;
	};
}