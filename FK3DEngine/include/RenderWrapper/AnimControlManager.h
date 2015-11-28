/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	AnimControlManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	����������������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	//����������������
	class FK_DLL AnimControlManager : public Singleton< AnimControlManager >
	{
	public:
		UINT				mNumAnimControl;	//��������������
		AnimControlList		mAnimControlList;	//�����������б�

	public:
		AnimControlManager();
		~AnimControlManager();

		//�����¶���������
		AnimControl* CreateAnimControl();

		//ɾ��ԭ�ж���������
		void DeleteAnimControl( AnimControl* pAnimControl );

		//ɾ�����ж���������
		void DeleteAllAnimControl();

		//��ȡָ������������
		AnimControl* GetAnimControl( UINT nIndex );

		//���¶���֡ʱ��
		void UpdateFrameTime( float fFrameTime );
	};
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
