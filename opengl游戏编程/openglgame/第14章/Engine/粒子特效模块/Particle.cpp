//========================================================
/**
*  @file      Particle.cpp
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ����ϵͳ��
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
#include "Particle.h"
#include "time.h"


CParticle::CParticle()
{
	pList_particle = NULL;	
}

CParticle::~CParticle()
{
	if(pList_particle != NULL)
	{
		delete [] pList_particle;
		pList_particle = NULL;
	}
}


/**\brief
 * ����ϵͳ�ĳ�ʼ��
 *
 *\param	_num	������
 */
BOOL CParticle::Init(int _num)
{
	m_iMaxNum = _num;
	pList_particle = new PARTICLE[m_iMaxNum];
	if(pList_particle == NULL)
		return FALSE;
	return TRUE;
}


/**\brief
 * ���ӵ���Ⱦ
 */
void CParticle::Render()
{	
}