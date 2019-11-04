//========================================================
/**
*  @file      PlantMgr.cpp
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


#include "stdafx.h"
#include "PlantMgr.h"
#include "inifile.h"


BOOL CTreeMgr::LoadIni(char* filename,char* index)
{
	CIniFile Ini(filename);
	unsigned int t_num=Ini.ReadInt(index,"TreeNum");
	//��ʼ��ֲ��
	char* strFile;
	char* strIndex;
	for(unsigned int i=0; i<t_num; ++i)
	{
		strFile = Ini.ReadText(index, i);
		strIndex = Ini.ReadData(index,i);
		tree.LoadIni(strFile, strIndex);
		m_pTrees.push_back(tree);
		_FREE(strFile);
		_FREE(strIndex);
	}

	return TRUE;
}


void CTreeMgr::Render()
{
	glDisable(GL_CULL_FACE);
	for(unsigned int i=0;i<m_pTrees.size();++i)
	{
		m_pTrees[i].Render();
	}
	glEnable(GL_CULL_FACE);
}

