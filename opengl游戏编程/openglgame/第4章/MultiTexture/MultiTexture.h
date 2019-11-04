//=========================================================================
/**
*  @file      MultiTexture.h
*
*  ��Ŀ������ ����ӳ��
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-11
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

#ifndef __MULTITEXTURE_H__
#define __MULTITEXTURE_H__

#include "stdafx.h"
#include "CBMPLoader.h"
#include "GLFrame.h"	



/** ��GL_Application������һ������ */
class MultiTexture : GLApplication								
{
public:
	bool	Init();							   /**< ִ�����еĳ�ʼ������ */
	void	Uninit();						   /**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);		   /**< ִ�����еĸ��²��� */
	void	Draw();							   /**< ִ�����еĻ��Ʋ��� */

	bool    isExtensionSupported(const char *string);  /**< ����Ƿ�֧����չ */
	bool    initMultiTexture();                        /**< ��ʼ�� */
	bool    loadTexture();                             /**< װ������ */

private:
	friend class GLApplication;				   
	MultiTexture(const char * class_name);	           /**< ���캯�� */

	/** �û��Զ���ĳ������ */ 
	CBMPLoader   m_texture[4];            /**< ����4������ */
	bool         multitexturing;          /**< ��־�Ƿ�ʹ�ö������� */
	bool         sp;                      /**< �жϿո���Ƿ��ͷ� */
			
};

#endif	// __MULTITEXTURE_H__