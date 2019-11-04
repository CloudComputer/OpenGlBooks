//========================================================
/**
*  @file      PlantMgr.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��ľ������
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef _TREE_MANAGE_H_
#define _TREE_MANAGE_H_

#define TREE_NUM   10

#include "Plant.h"
#include "terrain.h"
#include <vector>

using namespace std;
class CTreeMgr
{
public:
	CTreeMgr(){}
	~CTreeMgr(){}
	int GetTreeNum(){return m_pTrees.size();}
	void Render_Pick(int id){m_pTrees[id].Render();}
	void Render();
	BOOL LoadIni(char* filename,char* index);


private:
	Plant tree;
	vector<Plant> m_pTrees;
};

#endif