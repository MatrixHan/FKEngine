/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GeometryManager
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
	GeometryManager::GeometryManager()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	GeometryManager::~GeometryManager()
	{
		Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ʼ�������������
	void GeometryManager::Initialize( UINT nGeometryNum, UINT nAddNum )
	{
		mGeometryList.Initialize( nGeometryNum, nAddNum );
	}
	//--------------------------------------------------------------------------------------------------------------
	//�ͷż����������
	void GeometryManager::Release()
	{
		DeleteAllGeometry();
		mGeometryList.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//����������
	Geometry* GeometryManager::CreateGeometry( Geometry::FnCreator fnCreator )
	{
		//����������
		Geometry* pGeometry = fnCreator();
		*mGeometryList.Push() = pGeometry;
		return pGeometry;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ָ��������
	void GeometryManager::DeleteGeometry( Geometry* pGeometry )
	{
		GeometryList::Iterator it = mGeometryList.Begin();
		GeometryList::Iterator end = mGeometryList.End();
		for(; it!=end; ++it )
		{
			if( *it == pGeometry )
			{
				mGeometryList.Erase( it );
				delete pGeometry;
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����м�����
	void GeometryManager::DeleteAllGeometry()
	{
		GeometryList::Iterator it = mGeometryList.Begin();
		GeometryList::Iterator end = mGeometryList.End();
		for(; it!=end; ++it )
			SafeDelete( *it );

		mGeometryList.Clear();
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
