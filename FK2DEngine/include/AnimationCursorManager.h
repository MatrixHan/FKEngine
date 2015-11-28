/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	AnimationCursorManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include "AnimationCursor.h"
#include "Singleton.h"
#include <map>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	//--------------------------------------------------------------------
	typedef std::map< std::wstring, CAnimationCursor > CursorMap;
	//--------------------------------------------------------------------
	//! ��̬��������
	class CAnimationCursorManager
	{
	public:
		CAnimationCursorManager();
		~CAnimationCursorManager();
	public:
		//! ��ʼ��
		//@remarks [IN] p_nFPS	ÿ����ʾ֡��
		//@remarks [IN] p_nHotX	���Ľ���Xƫ��
		//@remarks [IN]	P_nHotY ���Ľ���Yƫ��
		void Init( CGraphics& p_Graphics, int p_nFPS = 30, int p_nHotX = 0, int p_nHotY = 0 );
		//! ����/�رչ�������
		void Enable( bool p_bEnable = true );
		//! �Ƿ�����������
		bool Enabled();
		//! ����һ����̬���
		bool AddCursor( CBitmap& p_Bitmap, const std::wstring& p_szCursorName,
			int p_nSingleWidth, int p_nSingleHeight );
		//! ���õ�ǰ��ʾ�Ķ�̬���
		void SetAnimCursor( const std::wstring& p_szCursorName );
		//! ������Ⱦ��
		CGraphics& GetGraphics();

		//! �߼�֡����
		void Update( float p_fDetla );
		//! ��ʾ֡����
		void FKDraw();
	private:
		bool					m_bEnable;			// �Ƿ���ö�̬���
		CAnimationCursor*		m_pCurCursor;		// ��ǰʹ�õĶ�̬���
		CursorMap				m_CursorMap;		// ��̬�����
		float					m_fDelta;			// ͼƬ���¼��
		float					m_fTime;			// ��ǰ�ѹ�ʱ��
		int						m_nHotX;			// ����xƫ��
		int						m_nHotY;			// ����yƫ��
		CGraphics*				m_pGraphics;		// ��Ⱦ��ָ��
		bool					m_bNeedUpdate;		// �Ƿ���Ҫ���¹��֡
	private:
		DECLARE_SINGLETON_CLASS( CAnimationCursorManager );
	};
	//--------------------------------------------------------------------
}

typedef FK2DEngine::TSingleton< FK2DEngine::CAnimationCursorManager >	SSAnimationCursorManager;