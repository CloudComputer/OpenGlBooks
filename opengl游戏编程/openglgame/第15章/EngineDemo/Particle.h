//========================================================
/**
*  @file      Particle.h
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

#ifndef _PATICLE_H_
#define _PATICLE_H_

#include "mathlib.h"


/**\brief
 * ���ӵĽṹ
 */
struct PARTICLE
{
	//! ���ӵ�λ��
	vector3d  m_pos;

	//! ���ӵ��ٶ�
	vector3d  m_velocity;

	//! ���ӵ�������
	float   life;

	//! ���ӵĴ�С
	float   m_size;
	
	//! ���ٶ�
	vector3d   m_gravity;
	
	//! ��ɫ
	float   m_color[3];
};



/**\brief
 * ����ϵͳ��
 */
class CParticle  
{
public:
	CParticle();
	virtual ~CParticle();


	/**\brief
	 * ����ϵͳ�ĳ�ʼ��
	 *
	 *\param	_num	������
	 */
	virtual BOOL Init(int _num);
	
	
	/**\brief
	 * ���ӵ���Ⱦ
	 */
	virtual void Render() = 0;


protected:
	//! ��������
	int m_iMaxNum;

	//! ���ӵ�ָ��
	PARTICLE *pList_particle;
};


#endif