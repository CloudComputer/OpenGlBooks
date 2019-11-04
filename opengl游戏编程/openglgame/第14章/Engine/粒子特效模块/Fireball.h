//========================================================
/**
*  @file      FireBall.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��ը����
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef _FIRE_BALL_H_
#define _FIRE_BALL_H_

#include "texture.h"
#include "billboard.h"

#define MAX_LENGTH 100.0f

/** ��ը���� */
class CFireball  
{
public:
	CFireball();
	~CFireball(){}

	void SetSpeed(float s){speed = s;}
	BOOL canReduceLife(){return canReduce;}
	void Change(vector3d& dest){end_pos = dest;}
	void SetColor(float _r,float _g,float _b){r=_r;g=_g;b=_b;}
	BOOL isRun(){return bRun;}
	void Render();
	void Set(vector3d start , vector3d end);
	BOOL Init(char *filename , float size);



private:
	CTexture texture;
	CBillBoard billboard;

	float m_iSize;
	vector3d start_pos,end_pos,vpos;
	float speed;
	BOOL bRun;
	vector3d orient;
	float r,g,b;
	BOOL canReduce;
	BOOL isArrive;
	int i;
};

#endif