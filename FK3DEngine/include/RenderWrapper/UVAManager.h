/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	UVAManager
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------

	// UV ��������
	struct UVAnimation
	{
		int			nSegment;		//����������
		int			nFrames;		//������֡��
		UVASegment*	pSegments;		//����������ָ��
		UVAFrame*	pFrames;		//����֡����ָ��
	};
	typedef Stack< UVAnimation* >	UVAnimationList;

	//--------------------------------------------------------------------------------------------------------------
	// UV ����������
	class FK_DLL UVAManager : public Singleton< UVAManager >
	{
	protected:
		FileObject*			mpPackFile;			// UVA ����ļ�

		UVAnimationList		mUVAnimationList;	// UV ���������б�

	public:
		UVAManager();
		~UVAManager();

		//���� UVA ����ļ�
		void SetUVAPackFile( FileObject* pPackFile );

		//���� UV �������ݶ���
		UVAnimation* CreateUVAnimation( LPCSTR szFileName );

		//ɾ�� UV �������ݶ���
		void DeleteUVAnimation( UVAnimation* pUVAnimation );

		//ɾ������ UV �������ݶ���
		void DeleteAllUVAnimation();
	};
	//--------------------------------------------------------------------------------------------------------------
};

//==================================================================================================================
