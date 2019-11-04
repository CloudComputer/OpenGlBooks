//========================================================
/**
*  @file      GameApp.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  Ӧ�ó�����,��ɳ���ĳ�ʼ����
*             ���ڵĴ���������������
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================


#ifndef __GAME_APP_H__
#define __GAME_APP_H__

#include "GLEngine.h"
#include "Ime.h"
#include "IniFile.h"


/*! Ӧ�ó����� */
class GameApp  
{
public:
	GameApp(void);
	~GameApp(void);

	BOOL	Init(SWindowInfo _sWinInfo);	//!< ��ʼ�����򣬴��ڡ������

	/**\brief
	 * ��������
	 *
	 *\param	_sWinInfo	������Ϣ
	 *\return	BOOL		�����Ƿ�ɹ�
	 */
	BOOL	CreateGLWindow(SWindowInfo _sWinInfo);

	/**\brief
	 * ������Ϣ������
	 */
	LRESULT WINAPI MessageHandler(HWND hWnd,UINT message,WPARAM  wParam, LPARAM lParam);

	void Run(void);				//!< �������ѭ��


private:
	SWindowInfo	m_sWinInfo;		//!< ������Ϣ

	MSG			msg;			//!< ��Ϣ
	
	BOOL		m_bActive;		//!< �����Ƿ��ڻ״̬

	GLEngine	m_cEngine;		//!< ��Ϸ������ʵ��

	void KillGLWindow(void);	//!< ���ٴ���
};


#endif