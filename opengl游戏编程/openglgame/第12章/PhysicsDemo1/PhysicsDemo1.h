//=========================================================================
/**
*  @file      PhysicsDemo1.h
*
*  ��Ŀ������ �����˶���ʾ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-10-10
*
*  ����������������������¼����麯��
*																								
*	virtual bool Init();														
*		ִ�����еĳ�ʼ������������ɹ���������true							
*																			
*	virtual void Uninit();													
*		ִ�����е�ж�ع���										
*																			
*	virtual void Update(DWORD milliseconds);										
*		ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ
*																			
*	virtual void Draw();															
*		ִ�����еĻ��Ʋ���
*/
//=========================================================================

#ifndef __DEMO_H__
#define __DEMO_H__

#include "stdafx.h"
#include "GLFrame.h"												/**< ���������Ŀ���� */
#include "Input.h"

/** ��GL_Application������һ������ */
class CDemo : GLApplication								
{
public:
	bool	Init();								    /**< ��ʼ������ */
	void	Uninit();								/**< ж�ع��� */
	void	Update(DWORD milliseconds);				/**< ���²��� */
	void	Draw();									/**< ���Ʋ��� */


	void    DrawGrid();                             /**< ����������� */
	void    DrawSphere(float x,float y);            /**< ��ָ��λ�û������� */

private:
	friend class GLApplication;					    /**< ����Ϊ����һ����Ԫ�� */
	CDemo(const char * class_name);				    /**< ���캯�� */
   
	/** �û��Զ���ĳ������ */
	CInputSystem*  m_pInput;                         /**< ����ϵͳ */
	float x,y,vx;                                    /**< С���λ�ú�X�����ٶ� */
	      
};


#endif	// __DEMO_H__