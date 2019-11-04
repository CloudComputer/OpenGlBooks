//========================================================
/**
*  @file      SceneMgr.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ����������
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================


#ifndef __SCENE_MGR_H__
#define __SCENE_MGR_H__

#include "iscene.h"
#include "aviscene.h"
//#include "titlescene.h"
//#include "selcharscene.h"
#include "openairscene.h"
#include "role.h"
#include "monstersMgr.h"
#include "staticObjMgr.h"
#include "timer.h"


/**\brief
 * ����������
 */
class SceneMgr
{
public:
	SceneMgr(void);
	~SceneMgr(void);


	/**\brief
	 * ��ʼ��
	 */
	BOOL Init();


	/**\brief
	 * ��INI���볡������
	 */
	BOOL LoadIni(char* _filename,char* _index);


	/**\brief
	 * ���õ�ǰ����
	 */
	void SetScene(GAME_SCENE _scene);


	/**\brief
	 * ��õ�ǰ���е������ೡ��
	 */
	GAME_SCENE GetScene(void){return m_eSceneType;}


	/**\brief
	 * ��������Ⱦ
	 */
	void Render(void);

	/**\brief
	 * ȡ�õ�ǰ������������ָ��
	 */
	static SceneMgr* GetSysSceneMgr(void){return m_psceneMgr;}

private:
	//! ��ǰ����ָ��
	IScene* m_pScene;

	//! ��ǰ�ĳ�������
	GAME_SCENE m_eSceneType;

	//! ������������ָ��
	static SceneMgr* m_psceneMgr;

	/////////////////////////////////////////////
	//! ����
	CTerrain Terrain;

	//! ��ѡ���ݻ�����
	GLuint selectBuff[512];

	//! ��̬ʵ��
	CStaticObjMgr m_cStaticObj;

	//! ����
	CMonstersMgr m_cMonsters;

	//! Ӣ��
	CRole role;

	/**\brief
	 * ��ʼ����ѡ����
	 */
	void StartPick(void);

	/**\brief
	 * ��������ѡ����
	 */
	void EndPick(void);

	/**\brief
	 * �������ж����ѡ
	 */
	void Pick(void);
	BOOL PickModel(int&type ,unsigned int &id);
};


#endif