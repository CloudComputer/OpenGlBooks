//========================================================
/**
*  @file      Monster.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��Ϸ�еĹ���
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "ActiveObj.h"
#include "terrain.h"
#include "fireball.h"
#include "info.h"
#include "sound.h"

extern CInfo ObjectInfo;


/**\brief
 * ��Ϸ�еĹ���
 */
class CMonster : public CActiveObj
{
public:
	CMonster(void);
	~CMonster(void){_DELETE(property);}


	/**\brief
	 * �����ٶ�
	 */
	void SetSpeed(float s);
	void Render_Pick(void);


	/**\brief
	 * ���ù��������
	 */
	void SetMonsterInfo(SActiveObjPro& info);
	void SetShadow(BOOL b){property->shadow=b;}

	/**\brief
	 * ��Ⱦ����
	 */
	virtual void OnRender(void){CActiveObj::OnRender();fireball.Render();}


	/**\brief
	 * ��Ⱦ������ݸ���
	 */
	virtual void EndRender(void);


	/**\brief
	 * ��ʼ��һ������
	 */
	BOOL Init(char* modelname,char* texturename,float scale,float h);


	/**\brief
	 * ��INI�ļ���ʼ��һ������
	 */
	BOOL LoadIni(char* filename,char* index);


private:
	//! ħ��
	CFireball fireball;

	int time_elapse;

	CSound sound;
};

#endif