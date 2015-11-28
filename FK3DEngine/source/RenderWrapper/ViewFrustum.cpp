/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	ViewFrustum
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderWrapper/RenderWrapperInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	ViewFrustum::ViewFrustum()
	{
		mOriVertex[0].x = -1.0f;	mOriVertex[0].y = -1.0f;	mOriVertex[0].z = 0.0f;		// xyz
		mOriVertex[1].x =  1.0f;	mOriVertex[1].y = -1.0f;	mOriVertex[1].z = 0.0f;		// Xyz
		mOriVertex[2].x = -1.0f;	mOriVertex[2].y =  1.0f;	mOriVertex[2].z = 0.0f;		// xYz
		mOriVertex[3].x =  1.0f;	mOriVertex[3].y =  1.0f;	mOriVertex[3].z = 0.0f;		// XYz
		mOriVertex[4].x = -1.0f;	mOriVertex[4].y = -1.0f;	mOriVertex[4].z = 1.0f;		// xyZ
		mOriVertex[5].x =  1.0f;	mOriVertex[5].y = -1.0f;	mOriVertex[5].z = 1.0f;		// XyZ
		mOriVertex[6].x = -1.0f;	mOriVertex[6].y =  1.0f;	mOriVertex[6].z = 1.0f;		// xYZ
		mOriVertex[7].x =  1.0f;	mOriVertex[7].y =  1.0f;	mOriVertex[7].z = 1.0f;		// XYZ
	}
	//--------------------------------------------------------------------------------------------------------------
	//��������
	void ViewFrustum::UpdateViewFrustum( const Matrix4& ViewProjMatrix )
	{
		//���۲������ͶӰ������˵ó���������ľ���
		static Matrix4 FrustumMat;
		Mat4Inverse( &FrustumMat, &ViewProjMatrix );

		//ת���˸���������굽����ռ�
		Mat4TransVec3( &mVertex3[0], &FrustumMat, (Vector3*)&mOriVertex[0] );
		Mat4TransVec3( &mVertex3[1], &FrustumMat, (Vector3*)&mOriVertex[1] );
		Mat4TransVec3( &mVertex3[2], &FrustumMat, (Vector3*)&mOriVertex[2] );
		Mat4TransVec3( &mVertex3[3], &FrustumMat, (Vector3*)&mOriVertex[3] );
		Mat4TransVec3( &mVertex3[4], &FrustumMat, (Vector3*)&mOriVertex[4] );
		Mat4TransVec3( &mVertex3[5], &FrustumMat, (Vector3*)&mOriVertex[5] );
		Mat4TransVec3( &mVertex3[6], &FrustumMat, (Vector3*)&mOriVertex[6] );
		Mat4TransVec3( &mVertex3[7], &FrustumMat, (Vector3*)&mOriVertex[7] );

		//���������������
		mPlane3[0].SetFromPoints( mVertex3[0], mVertex3[1], mVertex3[2] ); //����
		mPlane3[1].SetFromPoints( mVertex3[6], mVertex3[7], mVertex3[5] ); //Զ��
		mPlane3[2].SetFromPoints( mVertex3[2], mVertex3[6], mVertex3[4] ); //����
		mPlane3[3].SetFromPoints( mVertex3[7], mVertex3[3], mVertex3[5] ); //����
		mPlane3[4].SetFromPoints( mVertex3[2], mVertex3[3], mVertex3[6] ); //����
		mPlane3[5].SetFromPoints( mVertex3[1], mVertex3[0], mVertex3[4] ); //����
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ָ����Χ���Ƿ��������ཻ
	bool ViewFrustum::IsIntersect( const Vector3 pBoxVer[8] )
	{
		//���ô洢��Χ�еİ˸��ǵ��Ƿ���������������ڵı�����ÿ�����ÿһλ����õ���ĳ����Ĺ�ϵ��
		static BYTE bOutSide[8];
		memset( bOutSide, 0, sizeof(BYTE)*8 );

		//����Χ�еİ˸��ǵ��Ƿ����������������
		for( int nPoint=0; nPoint<8; ++nPoint )
		{
			for( int nPlane3=0; nPlane3<6; ++nPlane3 )
			{
				//����õ�������ĵ� i ��֮�⣬�򽫸õ�� bOutSide �еĵ� i λ��Ϊһ��
				if( mPlane3[nPlane3].mNormal.x * pBoxVer[nPoint].x +
					mPlane3[nPlane3].mNormal.y * pBoxVer[nPoint].y +
					mPlane3[nPlane3].mNormal.z * pBoxVer[nPoint].z +
					mPlane3[nPlane3].mDistance < 0 )
				{
					bOutSide[nPoint] |= ( 1 << nPlane3 );
				}
			}
			//���ĳ��� bOutSide ������λ��Ϊ 0����ô�õ�϶��������ڣ����Է����档
			if( bOutSide[nPoint] == 0 )
				return true;
		}

		//������е㶼�������ĳ�������򷵻ؼ�
		if( (	bOutSide[0] & bOutSide[1] & bOutSide[2] & bOutSide[3] &
				bOutSide[4] & bOutSide[5] & bOutSide[6] & bOutSide[7]	) != 0 )
		{
			return false;
		}

		//��������򷵻�����Ⱦ��
		//
		//	������ʵ�����Խ��и�����ϸ������� 12 �������Χ�е� 12 ����֮��ļ�⣬
		//	�����ǵ����������ϴ󣬶���������ļ����޷��жϳ�����ʵ���������������ֺ��٣�
		//	�����Ⱦ��ģ�Ͳ��Ǻܸ�������Щ�ò���ʧ���������ﲢû�н��������⡣
		//	�������ģ�͵���Ⱦ��ʱҪ�Ƚ�����������ö࣬����Կ��ǽ��������⣬
		//	����ķ����ʹ�����ο� DirectX 9.0 SDK Cull Sample ��

		return true;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
