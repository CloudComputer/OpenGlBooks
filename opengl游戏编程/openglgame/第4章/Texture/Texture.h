//=========================================================================
/**
*  @file      Texture.h
*
*  ��Ŀ������ ����ӳ��
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-12-02	
*  �޸����ڣ� 2007-07-10
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

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "stdafx.h"
#include "GLFrame.h"												/**< ���������Ŀ���� */
#include "CBMPLoader.h"
#include "TGALoader.h" 


/** ��GL_Application������һ������ */
class Texture : GLApplication								
{
public:
	bool	Init();							/**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();						/**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);		/**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();							/**< ִ�����еĻ��Ʋ��� */
	
	
	bool    LoadTexture();                  /**< �������� */
	void    SetLight();                     /**< ���ù�Դ */
	void    DrawSphere();                   /**< �������� */
	void    DrawBox();                      /**< ����ľ�� */
private:
	friend class GLApplication;				/**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	Texture(const char * class_name);	    /**< ���캯�� */

	/** �û��Զ���ĳ������ */ 
	CBMPLoader texture1;                     /**< λͼ������ */
	CTGALoader texture2;                     /**< TGA�ļ������� */
	float  rot;					             /**< ������ת���� */	
				
};


#endif	// __TEXTURE_H__