//========================================================
/**
*  @file      GLEngine.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��Ϸ������----��Ϸ�����е����ϲ����֯������
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================


#ifndef _GL_ENGINE_H_
#define _GL_ENGINE_H_

#include "input.h"
#include "font.h"
#include "camera.h"
#include "timer.h"
#include "sound.h"
#include "music.h"
#include "StaticObjMgr.h"
#include "role.h"
#include "monstersMgr.h"
#include "SceneMgr.h"
#include "GUIMgr.h"
#include "Message.h"


/*! ������*/
class GLEngine
{
public:
	GLEngine(void);
	~GLEngine(void);

	BOOL Init(void);				//!< ��ʼ��������opengl����ĳ�ʼ��

	void SetProjection(int iFOVAngle,int iHeight);//!< ���þ���

	void Prepare(void);				//!< ��Ⱦǰ��׼������

	void Render(void);				//!< 3D��Ⱦ

	void SwapBuffer(void){::SwapBuffers(m_hDC);}//!< ����������

	void Close(void);				//!< �ر�����

private:
	BOOL InitObject(void);			//!< ��Ϸ�е�ʵ������ĳ�ʼ��

	BOOL SetDCPixelFormat(void);	//!< ����opengl���ظ�ʽ


	HDC			m_hDC;		//!< �豸���

	HGLRC		m_hRC;		//!< ��Ⱦ���

	HZFont*		m_pFont;	//!< ����

	CInput*		m_pInput;	//!< ����ϵͳ

	CTimer*		m_pTimer;	//!< ��ʱ��

	CCamera		camera;		//!< �����

	CMusic		m_cMusic;	//!< ��������

	SceneMgr	m_cSceneMgr;//!< ��������

	GUIMgr		m_cGUIMgr;	//!< �������

	Message		m_cMessage;	//!< ��Ϣ����
};


#endif 