//=========================================================================
/**
*  @file      SnowDemo.h
*
*  ��Ŀ������ ����ϵͳ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-02
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

#ifndef __SNOWDEMO_H__
#define __SNOWDEMO_H__

#include "stdafx.h"
#include "GLFrame.h"												/**< ���������Ŀ���� */
#include "Font.h"
#include "Snow.h"

/** ��GL_Application������һ������ */
class SnowDemo : GLApplication								
{
public:
	bool	Init();							/**< ִ�����еĳ�ʼ������ */
	void	Uninit();						/**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);		/**< ִ�����еĸ��²��� */
	void	Draw();							/**< ִ�����еĻ��Ʋ��� */
	
	void    CaculateFrameRate();            /**< ����֡�� */
	void    PrintText();                    /**< ���������Ϣ */
	void    DrawGround();                   /**< ���Ƶ��� */
		
	
private:
	friend class GLApplication;				/**< ����Ϊ����һ����Ԫ�� */
	SnowDemo(const char * class_name);	    /**< ���캯�� */

	/** �û��Զ���ĳ������ */ 
	CSnow       m_Snow;                      /**< ѩ��ʵ�� */
	GLFont      m_Font;                      /**< ������ */
	CBMPLoader  m_TextureGround;             /**< �������� */
	float       m_Fps;                       /**< ֡�� */
	float       m_RotAngle;                  /**< �������ת�Ƕ� */
	
};


#endif	// __SNOWDEMO_H__