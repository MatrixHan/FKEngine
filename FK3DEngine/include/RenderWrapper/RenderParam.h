/********************************************************************
*
*	���ļ���FKMMORPG��һ���֡����ļ���Ȩ����FreeKnightDuzhi(������)���С�
*	E-mail: duzhi5368@163.com
*	QQ: 	281862942
* 	
*	-----------------------------------------------------------------
*
*	�ļ�����	RenderParam
*	���ߣ�		FreeKnightDuzhi[ ������ ]
*	�ļ�˵����	��Ⱦ������
*
*	�޸���:		
*	�޸�����:
*********************************************************************/

#pragma once

//==================================================================================================================

namespace FK3DEngine
{
	//--------------------------------------------------------------------------------------------------------------
	class Material;
	class RenderObject;
	class AnimControl;
	//--------------------------------------------------------------------------------------------------------------
	//��Ⱦ������
	class FK_DLL RenderParam
	{
	public:
		//��������
		enum DrawType
		{
			DT_Basic,	//����ͼԪ
			DT_TPatch,	//�����β�ֵ��Ƭ
			DT_RPatch,	//���β�ֵ��Ƭ
		};

		//����ͼԪ���Ʋ���
		struct BasicParam
		{
			PrimitiveType	ePrimType;		//����ͼԪ����
			DWORD			nVerOffset;		//��������ƫ����
			DWORD			nMinIndex;		//ʹ����С����ֵ
			DWORD			nIndexOffset;	//��������ƫ����
			DWORD			nVerCount;		//���ƶ�������
			DWORD			nPrimCount;		//����ͼԪ����
		};

		//�����β�ֵ��Ƭ���Ʋ���
		struct TPatchParam
		{
			DWORD			nPrimCount;		//����ͼԪ����
		};

		//���β�ֵ��Ƭ���Ʋ���
		struct RPatchParam
		{
			DWORD			nPrimCount;		//����ͼԪ����
		};

	public:
		DrawType			eDrawType;		//���Ʒ�ʽ
		Material*			pMaterial;		//��Ⱦ����
		UINT				nPriority;		//����Ⱦ�����ȼ�

		union
		{
			BasicParam	sBasicParam;		//����ͼԪ���Ʋ���
			TPatchParam	sTPatchParam;		//�����β�ֵ��Ƭ���Ʋ���
			RPatchParam	sRPatchParam;		//���β�ֵ��Ƭ���Ʋ���
		};

	public:
		//���ݲ���������Ⱦ
		void FKFastcall RenderByParam() const;

		//�Ƿ���Ҫ���н�����Ⱦ
		bool FKFastcall NeedRender() const;
	};
	//--------------------------------------------------------------------------------------------------------------
	typedef Stack< RenderParam* >	RenderParamList;
	//--------------------------------------------------------------------------------------------------------------
}

//==================================================================================================================
