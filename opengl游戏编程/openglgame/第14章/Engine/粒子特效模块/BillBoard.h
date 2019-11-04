//========================================================
/**
*  @file      BillBoard.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  �������
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef _BILL_BORAD_H_
#define _BILL_BORAD_H_

#include "mathlib.h"


/**\brief
 * �����������
 */
class CBillBoard  
{
public:
	CBillBoard():rotate(0.f),bRotate(TRUE){}
	~CBillBoard(){}

	void SetRotate(BOOL isRotate){bRotate = isRotate;}
	void Render(vector3d vpos,float m_iSize);
	void Update();


private:
	vector3d	right;
	vector3d	up;
	float		rotate;
	BOOL		bRotate;
};


#endif