//=========================================================================
/**
*  @file      BitmapFont.h
*
*  ��Ŀ������ OpenGL����
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

#ifndef __BITMAPFONT_H__
#define __BITMAPFONT_H__

#include "stdafx.h"
#include "GLFrame.h"			/**< ���������Ŀ���� */
#include "GLFont.h"             /**< �������嶨���� */


/** ��GL_Application������һ������ */
class BitmapFont : GLApplication								
{
public:
	bool	Init();							/**< ִ�����еĳ�ʼ������������ɹ���������true */
	void	Uninit();						/**< ִ�����е�ж�ع��� */
	void	Update(DWORD milliseconds);		/**< ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ */
	void	Draw();							/**< ִ�����еĻ��Ʋ��� */

private:
	friend class GLApplication;				/**< ����Ϊ����һ����Ԫ�࣬�����������������ʵ����������GL_Application * GL_Application::Create(const char * class_name) */
	BitmapFont(const char * class_name);	/**< ���캯�� */

	/** �û��Զ���ĳ������ */ 
	GLFont font;                /**< ����һ������ʵ�� */
	float	cnt1;				/**< �����ƶ�������1 */
    float	cnt2;				/**< �����ƶ�������2 */
				
};


#endif	// __BITMAPFONT_H__