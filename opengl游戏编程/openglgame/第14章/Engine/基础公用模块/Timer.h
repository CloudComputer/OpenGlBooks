//========================================================
/**
*  @file      Timer.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  �߷ֱ��ʼ�ʱ��,����������Ϸ��ʱ��ϵͳ  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================


/**
=========================ʹ�÷���=========================

#include "Timer.h"

CTimer*	timer;		// �߷ֱ��ʼ�ʱ��

timer = new CTimer;
timer->Init();	// ��ʱ����ʼ��

timer->GetElapsedSeconds();

delete timer;

=========================================================*/


#ifndef _TIMER_H_
#define _TIMER_H_

#include "StdAfx.h"


/**\brief
 * �߷ֱ��ʼ�ʱ����
 */
class CTimer
{
public:
	CTimer();
	~CTimer();

	//! ������ʱ�䣬��λ����
	float	m_fTime;

	//! ֡��
	float	m_fFPS;


	/**\brief
	 * ��ʱ���ĳ�ʼ��
	 *
	 * ���ϵͳ�и߷ֱ��ʼ�ʱ����������tickƵ�ʣ�����TRUE��
	 * ����������FALSE,����ʹ�øü�ʱ����
	 */
	BOOL Init();


	/**\brief
	 * ��þ�����ʱ��
	 */
	float GetElapsedSeconds();


	/**\brief
	 * ��ȡ֡��
	 */
	float GetFPS(unsigned long elapsedFrames=1);


	/**\beief
	 * ����֡��
	 */
	float LockFPS(unsigned char targetFPS);


	/**\brief
	 * ˢ�¼�ʱ��
	 */
	void Update(){m_fTime=GetElapsedSeconds();m_fFPS=GetFPS();}


	/**\brief
	 * ȡ�õ�ǰ��ʱ����ָ��
	 */
	static CTimer* GetSysTimer(){return m_pTimer;}


private:
	LARGE_INTEGER   m_startTime;
	LARGE_INTEGER   m_ticksPerSecond;

	static CTimer*	m_pTimer;
};

#endif