//========================================================
/**
*  @file      Plant.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ������Ⱦ
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef __PLANT_H__
#define __PLANT_H__

#include "texture.h"
#include "terrain.h"
#include "Object.h"

/**\brief
 * ������Ⱦ��
 */
class Plant:public Object
{
public:
	Plant();
	~Plant();

	/**\brief
	 * ��������
	 */
	BOOL Load(char* body,char* branch);

	/**\brief
	 * �������Ĵ�ϸ
	 */
	void SetSize(float _size)	{m_szTree=_size;}

	/**\brief
	 * �������ĸ߶�
	 */
	void SetHeight(float h)		{m_height=h;}

	/**\brief
	 * ����֦Ҷ�Ŀ��
	 */
	void SetBranchWidth(float w){m_fBranchWidth=w;}

	/**\brief
	 * ��INI�ļ��������Ĳ���
	 */
	BOOL LoadIni(char* filename,char* index);

	/**\brief
	 * ֲ�����Ⱦ
	 */
	virtual void OnRender();


private:
	/**\brief
	 * ����һ����֦
	 */
	void RenderSingleBranch(float width , float height);

	/**\brief
	 * ������֦
	 */
	void RenderBranch();

	/**\brief
	 * ��������
	 */
	void RenderTreebody();

	/**\brief
	 * ��������ͷ��
	 */
	void RenderTop(float width ,float height);


	CTexture	treebody;		//!< ���ɵ�����
	CTexture	treebranch;		//!< ��֦������
	float		m_szTree;		//!< ��ϸ
	float		m_fBranchWidth;	//!< ֦Ҷ�Ŀ��
	float		m_height;		//!< �߶�
};

#endif
