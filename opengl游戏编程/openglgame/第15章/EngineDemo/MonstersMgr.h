//========================================================
/**
*  @file      MonstersMgr.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ���������
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef _MONSTERS_MGR_H_
#define _MONSTERS_MGR_H_

#include "monster.h"
#include "mathlib.h"
#include "Info.h"


/**\brief
 * ������������
 */
class CMonstersMgr
{
public:
	CMonstersMgr();
	~CMonstersMgr();


	/**\brief
	 * �õ�ĳ�������״̬
	 */
	OBJ_STATE GetMonsterState(int id){return m_pMonster[id].GetObjectState();}


	/**\brief
	 * �õ�ĳ�������λ��
	 */
	vector3d GetMonsterPos(int id){return m_pMonster[id].GetPos();}


	/**\brief
	 * �����Ƿ���ʾ��Ӱ
	 */
	void SetShadow(BOOL b);


	/**\brief
	 * ��ѡ��ģʽ����Ⱦ����
	 */
	void Render_Pick(int id){m_pMonster[id].Render_Pick();}


	/**\brief
	 * ȡ�ù��������
	 */
	unsigned int GetMonsterNum(){return m_nNumMonsters;}


	/**\brief
	 * ȡ�õ�ǰ�����������ָ��
	 */
	static CMonstersMgr* GetSysMonstersMgr(){return m_pMonstersMgr;}


	/**\brief
	 * ��Ⱦ����
	 */
	void Render();


	/**\brief
	 * ��ʼ������
	 */
	BOOL LoadIni(char* filename,char* index);


private:
	//! ���������
	unsigned int m_nNumMonsters;

	//! ��Ź������ݵ�ָ��
	CMonster* m_pMonster;

	//! �����������ָ��
	static CMonstersMgr* m_pMonstersMgr;
};



////////////////////////////////////////////////////
//----------------inline����ʵ��--------------------
inline void CMonstersMgr::Render()
{
	for(unsigned int i=0;i<m_nNumMonsters;++i)m_pMonster[i].Render();
}


#endif