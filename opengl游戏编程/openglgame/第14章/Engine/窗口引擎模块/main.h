//========================================================
/**
*  @file      main.h
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


#ifndef __MAIN_H__
#define __MIAN_H__

#include "stdafx.h"
#include "gameapp.h"


/**\brief
 * ����������������
 */
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow);



/**\brief
 * ������Ϣ������
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);



#endif