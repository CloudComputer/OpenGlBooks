//========================================================
/**
*  @file      main.cpp
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��������
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
#include "resource.h"
#include "main.h"

//////////////////////////////////////////////////////////
//-----------------������ȫ�ֱ����Ķ���-------------------
//! ������Ϣ�ṹ
SWindowInfo* g_sWindowInfo;

//! Ӧ�ó���
GameApp*	 g_cGameApp;



//////////////////////////////////////////////////////////
//-----------------������ȫ�ֺ�����ʵ��-------------------

/**\brief
 * ����������������
 */
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	g_cGameApp		= new GameApp();
	g_sWindowInfo	= new SWindowInfo;

	if(!g_sWindowInfo->LoadIni("ini\\init.ini","window"))
	{
		_ERROR("Window Info Init failed!");
		_DELETE(g_cGameApp);
		return 0;
	}

	if(!g_cGameApp->Init(*g_sWindowInfo))
	{
		_ERROR("App init failed!");
		_DELETE(g_cGameApp);
		return 0;
	}

	g_cGameApp->Run();

	_DELETE(g_cGameApp);
	_DELETE(g_sWindowInfo);

	return 0;
}



/**\brief
 * ������Ϣ������
 */
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	return g_cGameApp->MessageHandler(hWnd,message,wParam,lParam);
}

