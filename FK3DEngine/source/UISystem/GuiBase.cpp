/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	GuiBase
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#include "../../include/UISystem/UISystemInsideHeader.h"

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	GuiClient::GuiClient()
		: mType		(NoClient)
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	GuiClient::GuiClient( const GuiClient& refClient )
	{
		//�жϿͻ�������
		switch (refClient.mType)
		{
		case Rect:
			{
				mType = Rect;
				memcpy( &mRect, &refClient.mRect, sizeof(GuiRect) );
				break;
			}
		case MaskMap:
			{
				mType = MaskMap;
				break;
			}
		default:
			Except( Exception::ERR_INTERNAL_ERROR, "������û��������ͻ�����Χ���͡�" );
		}
	}
	//--------------------------------------------------------------------------------------------------------------
	GuiClient::GuiClient( int nLeft, int nTop, int nRight, int nBottom )
		: mType			(Rect)
	{
		mRect.Left		= nLeft;
		mRect.Top		= nTop;
		mRect.Right		= nRight;
		mRect.Bottom	= nBottom;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���þ��οͻ�����Χ
	void FKFastcall GuiClient::SetClient( int nLeft, int nTop, int nRight, int nBottom )
	{
		mType = Rect;

		mRect.Left		= nLeft;
		mRect.Top		= nTop;
		mRect.Right		= nRight;
		mRect.Bottom	= nBottom;
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ָ�������Ƿ��ڿͻ�����
	bool FKFastcall GuiClient::IsOnClient( int x, int y )
	{
		//�жϿͻ�������
		switch (mType)
		{
		case Rect:
			{
				if( x > mRect.Left && x < mRect.Right &&
					y > mRect.Top && y < mRect.Bottom )
					return true;
				break;
			}
		case MaskMap:
			{
				if( x < 0 || x > mMaskMap.nWidth || y < 0 || y > mMaskMap.nHeight )
				{
					//����������Ӧ������ͼλ��
					UINT nBit = y *  mMaskMap.nWidth + x;
					UINT nByte = nBit >> 3;
					UINT nBitInByte = nBit % 8;

					//�жϸ��ֽڵĶ�Ӧλ�Ƿ�Ϊ��
					if( ( mMaskMap.pBitMask[ nByte ] << nBitInByte ) >> (8-nBitInByte) == 1 )
						return true;
				}
				break;
			}
		default:
			Except( Exception::ERR_INTERNAL_ERROR, "������û��������ͻ�����Χ���͡�" );
		}

		return false;
	}
	//--------------------------------------------------------------------------------------------------------------
	GuiBase::GuiBase( GuiLoca* pLoca, GuiClient* pClient, GuiDialog* pDialog )
		: mbEnable		(true)
		, mbVisable		(true)
		, mbFocus		(false)
		, mpDialog		(pDialog)
	{
		//�洢�ؼ�λ��
		if( pLoca != NULL )
			memcpy( &mLoca, pLoca, sizeof(GuiLoca) );
		else
			memset( &mLoca, 0, sizeof(GuiLoca) );

		//�洢�ͻ�����Χ
		if( pClient != NULL )
			memcpy( &mClient, pClient, sizeof(GuiClient) );
		else
			memset( &mClient, 0, sizeof(GuiClient) );
	}
	//--------------------------------------------------------------------------------------------------------------
	GuiBase::~GuiBase()
	{
	}
	//--------------------------------------------------------------------------------------------------------------
	//���ָ�������Ƿ��ڿͻ�����
	bool GuiBase::IsOnClient( int x, int y )
	{
		//���ݽ���λ�������������
		int nRelX = x - mLoca.X;
		int nRelY = y - mLoca.Y;

		//���ָ�������Ƿ��ڿؼ��û�����
		return mClient.IsOnClient( nRelX, nRelY );
	}
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================

