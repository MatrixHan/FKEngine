/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	FKSharedPtr
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//--------------------------------------------------------------------
#include <assert.h>
//--------------------------------------------------------------------
namespace FK2DEngine
{
	template< typename T  >
	class TSharedPtr
	{
	private:
		T*					m_pRep;				// ����ָ��
		unsigned int*		m_pUseCount;		// ���ü���
	public:
		TSharedPtr()
			: m_pRep( 0 )
			, m_pUseCount( 0 )
		{

		}

		explicit TSharedPtr( T* p_pRep )
			: m_pRep( p_pRep )
			, m_pUseCount( new unsigned int (1) )
		{

		}

		TSharedPtr( const TSharedPtr& p_Other )
			: m_pRep( 0 )
			, m_pUseCount( 0 )
		{
			m_pRep		= p_Other.m_pRep;
			m_pUseCount	= p_Other.m_pUseCount;

			if( m_pUseCount )
			{
				++(*m_pUseCount);
			}
		}

		TSharedPtr& operator = ( const TSharedPtr& p_Other )
		{
			if( m_pRep == p_Other.m_pRep )
			{
				return *this;
			}

			Release();

			m_pRep = p_Other.m_pRep;
			m_pUseCount = p_Other.m_pUseCount;

			if( m_pUseCount )
			{
				++(*m_pUseCount);
			}

			return *this;
		}

		virtual ~TSharedPtr()
		{
			Release();
		}

		inline T& operator * () const
		{
			assert( m_pRep );
			return *m_pRep;
		}

		inline T* operator -> () const
		{
			assert( m_pRep );
			return m_pRep;
		}

		inline T* Get() const
		{
			return m_pRep;
		}

		//! �󶨵�����ָ��
		void bind( T* p_pRep )
		{
			assert( !m_pRep && !m_pUseCount );
			m_pUseCount = new unsigned int (1);
			m_pRep = p_pRep;
		}

		inline bool Unique() const
		{
			return *m_pUseCount == 1;
		}

		inline unsigned int UseCount() const
		{
			return *m_pUseCount;
		}

		inline T* GetPointer() const
		{
			return m_pRep;
		}

		inline bool IsNull() const
		{
			return m_pRep == 0;
		}

		inline void SetNull()
		{
			if( m_pRep )
			{
				Release();
				m_pRep = 0;
				m_pUseCount = 0;
			}
		}

	protected:
		inline void Release()
		{
			bool bDestoryThis = false;

			if( m_pUseCount )
			{
				if( --( *m_pUseCount ) == 0 )
				{
					bDestoryThis = true;
				}
			}

			if( bDestoryThis )
			{
				Destroy();
			}
		}

		virtual void Destroy()
		{
			delete m_pRep;
			delete m_pUseCount;
		}
	};
}