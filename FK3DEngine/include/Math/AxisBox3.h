/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	AxisBox3
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
	class FK_DLL AxisBox3
	{
	public:
		union
		{
			struct
			{
				Vector3	mMaxVer;		//��Χ������
				Vector3	mMinVer;		//��Χ����С��
			};
			float m[6];
		};

		bool			mbEmpty;		//��־��Χ���Ƿ�Ϊ��

	public:
		AxisBox3();
		AxisBox3( const AxisBox3& refBox );
		AxisBox3( const Vector3& vMax, const Vector3& vMin );
		AxisBox3( const float pValue[6] );
		AxisBox3( float fMaxX, float fMaxY, float fMaxZ, float fMinX, float fMinY, float fMinZ );

		//��ֵ�����������
		AxisBox3& operator = ( const AxisBox3& refBox );

		//���ð�Χ�����㡢��С�㡣
		void SetMaxMin( const Vector3& vMax, const Vector3& vMin );
		void SetMaxMin( const float pValue[6] );
		void SetMaxMin( float fMaxX, float fMaxY, float fMaxZ, float fMinX, float fMinY, float fMinZ );

		//��ȡ��Χ�����㡢��С�㡣
		void GetMaxMin( Vector3* pvMax, Vector3* pvMin ) const;
		void GetMaxMin( float pValue[6] ) const;
		void GetMaxMin( float& fMaxX, float& fMaxY, float& fMaxZ, float& fMinX, float& fMinY, float& fMinZ ) const;

		//��ȡ��Χ�нǵ�
		void GetCorner( Vector3 pCorner[8] ) const;

		//��ȡ����ת�����Ľǵ�
		void GetCorner( Vector3 pCorner[8], const Matrix4& mat4 ) const;

		//����/��ȡ�Ƿ�Ϊ��
		void SetEmpty( const bool bEmpty );
		bool IsEmpty() const;

		//�ϲ��㼯
		void ContainVertex( const Vector3* pVertex, const UINT nNumVer );

		//�ϲ���Χ��
		void Combine( const AxisBox3& refBox );

		//��ȡ�ϲ���İ�Χ��
		void GetCombine( AxisBox3* pOutAxisBox3, const AxisBox3& refBox ) const;

		//ʹ�þ���ת����Χ��
		void Transform( const Matrix4& mat4, Vector3 pCorner[8] = NULL );

		//��ȡʹ�þ���ת����İ�Χ��
		void GetTransform( AxisBox3* pOutAxisBox3, const Matrix4& mat4, Vector3 pCorner[8] = NULL ) const;

		//���ָ����Χ���Ƿ���ð�Χ���ཻ
		bool IsIntersect( const AxisBox3& refBox ) const;
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
