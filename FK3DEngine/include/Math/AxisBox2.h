/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	AxisBox2
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��ά������Χ����
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//��ά������Χ����
	class FK_DLL AxisBox2
	{
	public:
		union
		{
			struct
			{
				Vector2	mMaxVer;		//��Χ������
				Vector2	mMinVer;		//��Χ����С��
			};
			float m[4];
		};

		bool			mbEmpty;		//��־��Χ���Ƿ�Ϊ��

	public:
		AxisBox2();
		AxisBox2( const AxisBox2& refBox );
		AxisBox2( const Vector2& vMax, const Vector2& vMin );
		AxisBox2( const float pValue[4] );
		AxisBox2( float fMaxX, float fMaxY, float fMinX, float fMinY );

		//��ֵ�����������
		AxisBox2& operator = ( const AxisBox2& refBox );

		//���ð�Χ�����㡢��С�㡣
		void SetMaxMin( const Vector2& vMax, const Vector2& vMin );
		void SetMaxMin( const float pValue[4] );
		void SetMaxMin( float fMaxX, float fMaxY, float fMinX, float fMinY );

		//��ȡ��Χ�����㡢��С�㡣
		void GetMaxMin( Vector2* pvMax, Vector2* pvMin ) const;
		void GetMaxMin( float pValue[4] ) const;
		void GetMaxMin( float& fMaxX, float& fMaxY, float& fMinX, float& fMinY ) const;

		//��ȡ��Χ�нǵ�
		void GetCorner( Vector2 pCorner[4] ) const;

		//����/��ȡ�Ƿ�Ϊ��
		void SetEmpty( const bool bEmpty );
		bool IsEmpty() const;

		//�ϲ��㼯
		void ContainVertex( const Vector2* pVertex, const UINT nNumVer );

		//�ϲ���Χ��
		void Combine( const AxisBox2& refBox );

		//��ȡ�ϲ���İ�Χ��
		void GetCombine( AxisBox2* pOutAxisBox2, const AxisBox2& refBox ) const;

		//���ָ����Χ���Ƿ���ð�Χ���ཻ
		bool IsIntersect( const AxisBox2& refBox ) const;
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
