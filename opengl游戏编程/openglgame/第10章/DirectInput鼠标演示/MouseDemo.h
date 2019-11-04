//=========================================================================
/**
*  @file      MouseDemo.h
*
*  ��Ŀ������ DirectInput�����ʾ
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

#ifndef __MOUSEDEMO_H__
#define __MOUSEDEMO_H__

#include "stdafx.h"
#include "GLFrame.h"												
#include "Input.h"

/** ��GL_Application������һ������ */
class CMouseDemo : GLApplication								
{
public:
	bool	Init();										/**< ��ʼ������ */
	void	Uninit();									/**< ж�ع��� */
	void	Update(DWORD milliseconds);					/**< ���²��� */
	void	Draw();										/**< ���Ʋ��� */

private:
	friend class GLApplication;							/**< ����Ϊ����һ����Ԫ�� */
	CMouseDemo(const char * class_name);				/**< ���캯�� */
									
    CInputSystem*  m_pInput;                            /**< ����ϵͳ */

};


#endif	// __MOUSEDEMO_H__