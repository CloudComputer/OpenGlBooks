//========================================================
/**
*  @file      Snow.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ѩ����Ⱦ��
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef _SNOW_H_
#define _SNOW_H_

#include "Particle.h"
#include "texture.h"
#include "billboard.h"
#include "role.h"


/**\brief
 * ѩ����Ⱦ��
 */
class CSnow : public CParticle  
{
public:
	void Render();
	BOOL Init();
	CSnow(){}
	~CSnow(){}

private:
	void ResetPaticle(PARTICLE *particle);
	CTexture snow_texture;
	int m_width , m_height , m_depth;
	vector3d vCameraPos;
	CBillBoard billboard;
};

#endif