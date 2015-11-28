/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	MemPool
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	�ڴ��ģ����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//�ڴ�أ�����ɱ�֤�ڴ�ĵ�ַ�̶��������ܱ�֤�ڴ����Է��䡣��
	template <typename T> class FK_DLL MemPool
	{
	public:
		//�ڴ����Ϣ�ṹ
		struct PoolInfo
		{
			T*				pPool;		//�ڴ�ؿռ�
			bool*			pbIsUsed;	//Ԫ�ؿռ�ռ�ñ�־
			unsigned int	nNumEmpty;	//���ڴ���п���Ԫ������
		};

	public:
		//----------------------------------------------------------------------------------------------------------
		//�ڴ�ػ���Ԫ�ص�����
		class BaseIterator
		{
		public:
			friend class MemPool;

		protected:
			MemPool*		pMemPool;	//�������������ڴ��
			PoolInfo*		pPoolInfo;	//�õ����������ڴ��
			unsigned int	nPoolNum;	//�õ����������ڴ�ر��
			unsigned int	nDataNum;	//���������ݱ��

		public:
			T*				pData;		//����������

		public:
			//��ֵ������
			FKInline BaseIterator& operator = ( const BaseIterator& rBaseIterator );

			//��ȱȽϲ�����
			FKInline const bool operator == ( const BaseIterator& rBaseIterator );

			//����ȱȽϲ�����
			FKInline const bool operator != ( const BaseIterator& rBaseIterator );
		};
		//----------------------------------------------------------------------------------------------------------
		//�ڴ��Ԫ���ڴ���������˵����������ʳ�������Ԫ�أ����۸�Ԫ���Ƿ�Ϊ�ա���
		class Iterator : public BaseIterator
		{
		public:
			//����ƶ����������ȼ��㣩
			Iterator& operator ++ ();

			//����ƶ�������������㣩
			Iterator operator ++ (int);

			//��ǰ�ƶ����������ȼ��㣩
			Iterator& operator -- ();

			//��ǰ�ƶ�������������㣩
			Iterator operator -- (int);
		};
		//----------------------------------------------------------------------------------------------------------
		//�ڴ�ؿ���Ԫ�ص��������˵��������������ʳ������в�Ϊ�յ�Ԫ�ء���
		class DataIterator : public BaseIterator
		{
		public:
			//����ƶ����������ȼ��㣩
			DataIterator& operator ++ ();

			//����ƶ�������������㣩
			DataIterator operator ++ (int);

			//��ǰ�ƶ����������ȼ��㣩
			DataIterator& operator -- ();

			//��ǰ�ƶ�������������㣩
			DataIterator operator -- (int);
		};
		//----------------------------------------------------------------------------------------------------------

	protected:
		PoolInfo*		m_pPoolInfo;		//�ڴ����Ϣ����
		unsigned int	m_nNumPool;			//��ǰ�ڴ������
		unsigned int	m_nPoolDataLen;		//�ڴ�������ڴ����Ĵ�С

		PoolInfo*		m_pCurPool;			//��ǰ�ɱ�ʹ�õ�Ԫ�����ڵ��ڴ��ָ��
		unsigned int	m_pCurNum;			//��ǰ�ɱ�ʹ�õ�Ԫ��λ��

		PoolInfo*		m_pNextPool;		//��һ���ɱ�ʹ�õ�Ԫ�����ڵ��ڴ��ָ��
		unsigned int	m_pNextNum;			//��һ���ɱ�ʹ�õ�Ԫ��λ��

		unsigned int	m_nPoolSize;		//�����ڴ������Ԫ������

		unsigned int	m_nNumData;			//��ǰԪ������
		unsigned int	m_nMaxNumData;		//���Ԫ������

		BaseIterator	m_TmpIterator;		//������ʱ����Ԫ�ص�����

	public:
		MemPool();
		~MemPool();

		//��ʼ���ڴ�أ�NumPerPool Ϊ�����ڴ�ص�Ԫ������PoolNum Ϊ��ʼ�ڴ����������
		void Initialize( unsigned int NumPerPool, unsigned int PoolNum );

		//�ͷ��ڴ��
		void Release();

		//����ڴ��������Ԫ��
		void Clear();

		//������Ԫ��
		T* Add();

		//ɾ����Ԫ��
		void Erase( T* pData );

		//����ָ��λ�õ�Ԫ���ڴ������
		Iterator& GetIterator( unsigned int nPos = 0 );

		//����ָ��λ�õĿ���Ԫ�ص�����
		DataIterator& GetDataIterator( unsigned int nPos = 0 );

		//���س�ǰ����Ԫ�ص�����
		BaseIterator& Front();

		//���س�β����Ԫ�ص�����
		BaseIterator& End();

	protected:
		//����һ���µ��ڴ��
		void AllocNewPool();
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
