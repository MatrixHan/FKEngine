/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	HashMap
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ϣ��ģ����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��ϣ��ģ����
	template <typename T> class FK_DLL HashMap
	{
	public:
		//��ϣ�ַ�����󳤶�
		static const int		mMaxHashStrLen = 32;

		//��ϣԪ�ؽṹ
		struct HashData
		{
			T				Data;						//�洢����

			char			szKeyName[mMaxHashStrLen];	//����
			unsigned short	nKeyNameLen;				//��������

			HashData*		pNext;						//��һ��Ԫ�ص�ָ��
			HashData*		pPrev;						//��һ��Ԫ�ص�ָ��

			unsigned int	nStackIndex;				//��Ԫ���ڶ�ջ�е�������
		};

	public:
		unsigned int			mnTableSize;	//��ϣԪ���������С
		HashData**				mpHashTable;	//��ϣԪ��������

		UINT					mNumData;		//��ϣԪ������
		Stack< HashData* >		mHashDataStack;	//��ϣԪ��ָ���ջ���������п�����ѭ��

	public:
		HashMap();
		~HashMap();

		//��ʼ����ϣ��nTableSize Ϊ��ϣ���С�������ӵ�Ԫ�س����˴���ֵ������ظ��ʼ��ߡ���
		void Initialize( unsigned int nTableSize );

		//��չ�ϣ��
		void Clear();

		//�ͷŹ�ϣ��
		void Release();

		//����Ԫ��
		bool Add( const T& refData, const char* szKeyName );

		//ɾ��Ԫ��
		void Del( const char* szKeyName );

		//Ѱ��Ԫ��
		T* Find( const char* szKeyName );

		//���ص�ǰԪ����
		FKInline unsigned int Size() const;
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
