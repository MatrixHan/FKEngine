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
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/Math/MathInsideHead.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	AxisBox2::AxisBox2()
		: mbEmpty	(true)
	{
		m[0] = 0.0f;		m[1] = 0.0f;
		m[2] = 0.0f;		m[3] = 0.0f;
	}
	//--------------------------------------------------------------------------------------------------------------
	AxisBox2::AxisBox2( const AxisBox2& refBox )
		: mbEmpty	(refBox.mbEmpty)
	{
		m[0] = refBox.m[0];		m[1] = refBox.m[1];
		m[2] = refBox.m[2];		m[3] = refBox.m[3];
	}
	//--------------------------------------------------------------------------------------------------------------
	AxisBox2::AxisBox2( const Vector2& vMax, const Vector2& vMin )
		: mbEmpty	(false)
		, mMaxVer	(vMax)
		, mMinVer	(vMin)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	AxisBox2::AxisBox2( const float pValue[4] )
		: mbEmpty	(false)
	{
		m[0] = pValue[0];		m[1] = pValue[1];
		m[2] = pValue[2];		m[3] = pValue[3];
	}
	//--------------------------------------------------------------------------------------------------------------
	AxisBox2::AxisBox2( float fMaxX, float fMaxY, float fMinX, float fMinY )
		: mbEmpty	(false)
	{
		m[0] = fMaxX;		m[1] = fMaxY;
		m[2] = fMinX;		m[3] = fMinY;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ֵ�����������
	AxisBox2& AxisBox2::operator = ( const AxisBox2& refBox )
	{
		memcpy( this, &refBox, sizeof(AxisBox2) );
		return *this;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ð�Χ�����㡢��С�㡣
	void AxisBox2::SetMaxMin( const Vector2& vMax, const Vector2& vMin )
	{
		mMaxVer = vMax;
		mMinVer = vMin;

		mbEmpty = false;
	}
	//--------------------------------------------------------------------------------------------------------------
	void AxisBox2::SetMaxMin( const float pValue[4] )
	{
		m[0] = pValue[0];		m[1] = pValue[1];
		m[2] = pValue[2];		m[3] = pValue[3];

		mbEmpty = false;
	}
	//--------------------------------------------------------------------------------------------------------------
	void AxisBox2::SetMaxMin( float fMaxX, float fMaxY, float fMinX, float fMinY )
	{
		m[0] = fMaxX;		m[1] = fMaxY;
		m[2] = fMinX;		m[3] = fMinY;

		mbEmpty = false;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��Χ�����㡢��С�㡣
	void AxisBox2::GetMaxMin( Vector2* pvMax, Vector2* pvMin ) const
	{
		*pvMax = mMaxVer;
		*pvMin = mMinVer;
	}
	//--------------------------------------------------------------------------------------------------------------
	void AxisBox2::GetMaxMin( float pValue[4] ) const
	{
		pValue[0] = m[0];	pValue[1] = m[1];
		pValue[2] = m[2];	pValue[3] = m[3];
	}
	//--------------------------------------------------------------------------------------------------------------
	void AxisBox2::GetMaxMin( float& fMaxX, float& fMaxY, float& fMinX, float& fMinY ) const
	{
		fMaxX = m[0];		fMaxY = m[1];
		fMinX = m[2];		fMinY = m[3];
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ��Χ�нǵ�
	void AxisBox2::GetCorner( Vector2 pCorner[4] ) const
	{
		pCorner[0].x = mMinVer.x;		pCorner[0].y = mMaxVer.y;	//����
		pCorner[1].x = mMaxVer.x;		pCorner[1].y = mMaxVer.y;	//����
		pCorner[2].x = mMinVer.x;		pCorner[2].y = mMinVer.y;	//����
		pCorner[3].x = mMaxVer.x;		pCorner[3].y = mMinVer.y;	//����
	}
	//--------------------------------------------------------------------------------------------------------------
	//�����Ƿ�Ϊ��
	void AxisBox2::SetEmpty( const bool bEmpty )
	{
		mbEmpty = bEmpty;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�Ƿ�Ϊ��
	bool AxisBox2::IsEmpty() const
	{
		return mbEmpty;
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ϲ��㼯
	void AxisBox2::ContainVertex( const Vector2* pVertex, const UINT nNumVer )
	{
		if( nNumVer == 0 )
			return;

		mbEmpty = false;

		//���¼������ֵ����Сֵ
		for( UINT i=0; i<nNumVer; ++i )
		{
			const Vector2* pVerPtr = pVertex + i;

			if( pVerPtr->x < mMinVer.x )
				mMinVer.x = pVerPtr->x;
			else if( pVerPtr->x > mMaxVer.x )
				mMaxVer.x = pVerPtr->x;

			if( pVerPtr->y < mMinVer.y )
				mMinVer.y = pVerPtr->y;
			else if( pVerPtr->y > mMaxVer.y )
				mMaxVer.y = pVerPtr->y;

			++pVerPtr;
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ϲ���Χ��
	void AxisBox2::Combine( const AxisBox2& refBox )
	{
		GetCombine( this, refBox );
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ�ϲ���İ�Χ��
	void AxisBox2::GetCombine( AxisBox2* pOutAxisBox2, const AxisBox2& refBox ) const
	{
		if( refBox.mbEmpty )
		{
			*pOutAxisBox2 = *this;
			return;
		}
		else if( mbEmpty && refBox.mbEmpty )
		{
			pOutAxisBox2->mbEmpty = true;
			return;
		}
		else if( mbEmpty && !refBox.mbEmpty )
		{
			*pOutAxisBox2 = refBox;
			return;
		}

		if( mMinVer.x > refBox.mMinVer.x )
			pOutAxisBox2->mMinVer.x = refBox.mMinVer.x;
		if( mMinVer.y > refBox.mMinVer.y )
			pOutAxisBox2->mMinVer.y = refBox.mMinVer.y;

		if( mMaxVer.x < refBox.mMaxVer.x )
			pOutAxisBox2->mMaxVer.x = refBox.mMaxVer.x;
		if( mMaxVer.y < refBox.mMaxVer.y )
			pOutAxisBox2->mMaxVer.y = refBox.mMaxVer.y;

		pOutAxisBox2->mbEmpty = false;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ָ����Χ���Ƿ���ð�Χ���ཻ
	bool AxisBox2::IsIntersect( const AxisBox2& refBox ) const
	{
		if( mbEmpty || refBox.mbEmpty )
			return false;

		if( mMaxVer.x < refBox.mMinVer.x || refBox.mMaxVer.x < mMinVer.x )
			return false;

		if( mMaxVer.y < refBox.mMinVer.y || refBox.mMaxVer.y < mMinVer.y )
			return false;

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
