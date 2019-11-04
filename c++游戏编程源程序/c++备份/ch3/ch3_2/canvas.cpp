
#include "stdafx.h"
#include <stdio.h>

//�����ܼƫŧi
HINSTANCE hInst;
HBITMAP man[7];
HDC		hdc,mdc;
HWND	hWnd;
DWORD	tPre,tNow,tCheck;
int		num,frame,fps;

//�禡�ŧi
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				MyPaint(HDC hdc);

//****�D�{��**************************************
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;

	MyRegisterClass(hInstance);

	//�����l�ƨ禡
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	//�C���j��
    while( msg.message!=WM_QUIT )
    {
        if( PeekMessage( &msg, NULL, 0,0 ,PM_REMOVE) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
		else
		{
			tNow = GetTickCount();
			if(tNow-tPre >= 100)
				MyPaint(hdc);
		}
    }

	return msg.wParam;
}

//****�w�q�ε��U�������O�禡*************************
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "canvas";
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

//****��l�禡*************************************
// �q�ɮ׸��J�I�}��
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	char filename[20] = "";
	int i;

	hInst = hInstance;

	hWnd = CreateWindow("canvas", "ø�ϵ���" , WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	MoveWindow(hWnd,10,10,600,450,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);

	//���J�U�H���I�}��
	for(i=0;i<7;i++)
	{
		sprintf(filename,"man%d.bmp",i);
		man[i] = (HBITMAP)LoadImage(NULL,filename,IMAGE_BITMAP,640,480,LR_LOADFROMFILE);
	}
	
	num = 0;
	frame = 0;

	MyPaint(hdc);

	return TRUE;
}

//****�ۭqø�Ϩ禡*********************************
// 1.�p��P��ܨC��e����s����
// 2.�̹ϸ����Ƕi������K��
void MyPaint(HDC hdc)
{
	char str[40] = "";

	if(num == 7)
		num = 0;
	frame++;			       //�e����s���ƥ[1
	if(tNow - tCheck >= 1000)
	{
		fps = frame;
		frame = 0;
		tCheck = tNow;
	}

	SelectObject(mdc,man[num]);
	sprintf(str,"�C������� %d  �ӵe��  ",fps);
	TextOut(mdc,0,0,str,strlen(str));
	BitBlt(hdc,0,0,600,450,mdc,0,0,SRCCOPY);

	tPre = GetTickCount();     //�O������ø�Ϯɶ�
	num++;
}

//****�T���B�z�禡***********************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i;

	switch (message)
	{
		case WM_DESTROY:					//���������T��
			DeleteDC(mdc);
			for(i=0;i<7;i++)
				DeleteObject(man[i]);
			ReleaseDC(hWnd,hdc);
			PostQuitMessage(0);
			break;
		default:							//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

