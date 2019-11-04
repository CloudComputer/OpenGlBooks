//========================================================
/**
*  @file      Timer.cpp
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

#include "stdafx.h"
#include "Timer.h"

CTimer* CTimer::m_pTimer=NULL;

CTimer::CTimer(){m_pTimer=this;}
CTimer::~CTimer(){}

/**\brief
 * ��ʱ���ĳ�ʼ��
 *
 * ���ϵͳ�и߷ֱ��ʼ�ʱ����������tickƵ�ʣ�����TRUE��
 * ����������FALSE,����ʹ�øü�ʱ����
 */
BOOL CTimer::Init()
{
	if (!QueryPerformanceFrequency(&m_ticksPerSecond))
	{
		return FALSE;// ϵͳ��֧�ָ߷ֱ��ʼ�ʱ��
	}

	else
	{
		QueryPerformanceCounter(&m_startTime);
		return TRUE;
	}
}



/**\brief
 * ��þ�����ʱ��
 */
float CTimer::GetElapsedSeconds()
{
	static LARGE_INTEGER s_lastTime = m_startTime;
	LARGE_INTEGER currentTime;

	QueryPerformanceCounter(&currentTime);

	float seconds=(float)(currentTime.QuadPart-s_lastTime.QuadPart)/(float)m_ticksPerSecond.QuadPart;

	// ��ʱ����λ
	s_lastTime = currentTime;

	return seconds;
}


/**\brief
 * ��ȡ֡��
 */
float CTimer::GetFPS(unsigned long elapsedFrames)
{
	static LARGE_INTEGER s_lastTime = m_startTime;
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	float fps = (float)elapsedFrames * (float)m_ticksPerSecond.QuadPart / ((float)currentTime.QuadPart - (float)s_lastTime.QuadPart);
	// ���ö�ʱ��
	s_lastTime = currentTime;
	return fps;
} 


/**\beief
 * ����֡��
 */
float CTimer::LockFPS(unsigned char targetFPS)
{
	if (targetFPS == 0)targetFPS = 1;

	static LARGE_INTEGER s_lastTime = m_startTime;
	LARGE_INTEGER currentTime;
	float   fps;
	// ��ʱ�Ա�֤�̶���֡��
	do
	{
		QueryPerformanceCounter(&currentTime);
		fps=(float)m_ticksPerSecond.QuadPart/((float)(currentTime.QuadPart-s_lastTime.QuadPart));
	}
	while (fps > (float)targetFPS);
	// ���ö�ʱ��
	s_lastTime = m_startTime;

	return fps;
}
