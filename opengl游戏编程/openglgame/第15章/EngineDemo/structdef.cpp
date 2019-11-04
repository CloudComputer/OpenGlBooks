//========================================================
/**
*  @file      structdef.cpp
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ���ýṹ����  
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
#include "structdef.h"
#include "IniFile.h"



/** ������SWindowInfo�ṹ��ʵ��  */

//! SWindowInfo�ṹ�ľ�̬������ʼ��
SWindowInfo*	SWindowInfo::m_pInfo=NULL;
BOOL			SWindowInfo::m_bFullScreen=FALSE;
int				SWindowInfo::m_iWidth=640;
int				SWindowInfo::m_iHeight=480;
int				SWindowInfo::m_iBits=32;
HINSTANCE		SWindowInfo::m_hInstance=NULL;
HWND			SWindowInfo::m_hWnd=NULL;
char*			SWindowInfo::m_strWinName=NULL;

/**\brief
 * ��INI�ļ����봰����Ϣ
 */
BOOL SWindowInfo::LoadIni(char* _filename,char* _index)
{
	CIniFile t_cIni(_filename);
	m_iWidth		=t_cIni.ReadInt(_index,"width");
	m_iHeight		=t_cIni.ReadInt(_index,"height");
	m_iBits			=t_cIni.ReadInt(_index,"bits");
	m_bFullScreen	=t_cIni.ReadInt(_index,"FullScreen");
	m_strWinName	=t_cIni.ReadText(_index,"WindowName");

	m_hInstance = GetModuleHandle(NULL);

	return TRUE;
}

