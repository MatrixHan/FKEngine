/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	AnimationCursor
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "Bitmap.h"
#include "Image.h"
#include <vector>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	//! ��̬�����
	class CAnimationCursor
	{
	public:
		CAnimationCursor();
		~CAnimationCursor();
	public:
		//! ��ʼ��
		//@params [IN] p_nSingleWidth	����ͼƬ�Ŀ��
		void Init( CBitmap& p_pBitmap, const std::wstring& p_szName,
			int p_nSingleWidth, int p_nSingleHeight );
		
		//! ����
		//@params [IN] p_bUpdate �Ƿ����һ֡
		void FKDraw( bool p_bUpdate = false );

		//! ��ȡ�������
		std::wstring GetName() const;
	private:
		CBitmap*				m_pBitmap;		// �����ͼƬ
		std::vector< CImage >	m_vecAnim;		// ����鶯��
		std::wstring			m_szName;		// ���������
		int						m_nCurFrame;	// ��ǰ֡��
		int						m_nMaxFrame;	// ���֡��
	};
	//--------------------------------------------------------------------
}