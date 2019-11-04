//========================================================
/**
*  @file      AVIPlayer.cpp
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  AVI������
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
#include "aviplayer.h"


AVIPlayer::AVIPlayer(void)
{
	m_hWnd=NULL;
	m_hmmWnd=NULL;
}


AVIPlayer::~AVIPlayer(void)
{
	Stop();
	m_hWnd=NULL;
}


BOOL AVIPlayer::Init(HWND _hWnd)
{
	if(_hWnd)
	{
		m_hWnd=_hWnd;
		return TRUE;
	}
	else 
		return FALSE;
}