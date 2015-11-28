/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	VertexDeclaration
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/RenderSystem/RenderSystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	VertexDeclaration::VertexDeclaration()
		: mNumElement	(0)
	{
		mVertexElements.Initialize( 8, 8 );
	}
	//--------------------------------------------------------------------------------------------------------------
	VertexDeclaration::~VertexDeclaration()
	{
		mVertexElements.Release();
	}
	//--------------------------------------------------------------------------------------------------------------
	//��Ӷ���Ԫ��
	void VertexDeclaration::AddElement( WORD nStream, WORD nOffset, VertexElementType eType,
		VertexElementMethod eMethod, VertexElementUsage eUsage, BYTE nUsageIndex )
	{
		//���Ϊ����ģʽ
#ifdef _DEBUG
		if( mNumElement > 0 )
		{
			//��ⶥ����������ƫ�����Ƿ��ǰ��մ�С�����˳�����е�
			VertexElement* pBackElement = mVertexElements.Back();

			if( pBackElement->nStream > nStream )
				Except( Exception::ERR_INVALIDPARAMS, "����Ԫ�ض���������ֵû�а��մ�С�����˳�����С�" );

			if( pBackElement->nStream == nStream )
			{
				if( pBackElement->nOffset > nOffset )
					Except( Exception::ERR_INVALIDPARAMS, "ͬ�������ж���Ԫ������ƫ����û�а��մ�С�����˳�����С�" );
			}
		}
#endif

		//��Ӷ���Ԫ��
		VertexElement* pElement = mVertexElements.Push();
		pElement->nStream		= nStream;
		pElement->nOffset		= nOffset;
		pElement->Type			= eType;
		pElement->Method		= eMethod;
		pElement->Usage			= eUsage;
		pElement->UsageIndex	= nUsageIndex;

		++mNumElement;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ��ָ��λ�õĶ���Ԫ��
	void VertexDeclaration::DelElement( UINT nIndex )
	{
		mVertexElements.Erase( nIndex );

		--mNumElement;
	}
	//--------------------------------------------------------------------------------------------------------------
	//ɾ�����ж���Ԫ��
	void VertexDeclaration::DelAllElement()
	{
		mVertexElements.Clear();

		mNumElement = 0;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡָ��λ�õĶ���Ԫ��
	VertexElement* VertexDeclaration::GetElement( UINT nIndex )
	{
		if( nIndex >= mNumElement )
			return NULL;

		return mVertexElements.Begin() + nIndex;
	}
	//--------------------------------------------------------------------------------------------------------------
	//��ȡ����Ԫ������
	UINT VertexDeclaration::GetElementNum()
	{
		return mNumElement;
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
