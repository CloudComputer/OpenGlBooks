
#include "stdafx.h"
#include <stdio.h>

//�����ܼƫŧi
HINSTANCE hInst;
HBITMAP bg,ball;
HDC		hdc,mdc,bufdc;
HWND	hWnd;
DWORD	tPre,tNow,tCheck;
RECT	rect;
int		x=0,y=100,vx=8,vy=0;
int		gy=1,fx=-1,fy=-4;

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
			if(tNow-tPre >= 50)
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
	HBITMAP bmp;
	hInst = hInstance;

	hWnd = CreateWindow("canvas", "ø�ϵ���" , WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	MoveWindow(hWnd,10,10,750,400,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);
	bufdc = CreateCompatibleDC(hdc);
	bmp = CreateCompatibleBitmap(hdc,750,400);

	SelectObject(mdc,bmp);

	bg = (HBITMAP)LoadImage(NULL,"bg.bmp",IMAGE_BITMAP,750,400,LR_LOADFROMFILE);
	ball = (HBITMAP)LoadImage(NULL,"ball.bmp",IMAGE_BITMAP,52,26,LR_LOADFROMFILE);
	
	GetClientRect(hWnd,&rect);

	MyPaint(hdc);

	return TRUE;
}

//****�ۭqø�Ϩ禡*********************************
// 1.�����K��
// 2.�ھڤp�y���B�ʪ��A�p��t�׻P�K�Ϯy��
void MyPaint(HDC hdc)
{
	SelectObject(bufdc,bg);
	BitBlt(mdc,0,0,750,400,bufdc,0,0,SRCCOPY);

	SelectObject(bufdc,ball);
	BitBlt(mdc,x,y,26,26,bufdc,26,0,SRCAND);
	BitBlt(mdc,x,y,26,26,bufdc,0,0,SRCPAINT);

	BitBlt(hdc,0,0,750,400,mdc,0,0,SRCCOPY);

	x += vx;			//�p�� X �b��V�K�Ϯy��

	vy = vy + gy;		//�p�� Y �b��V�t�פ��q
	y += vy;			//�p�� Y �b��V�K�Ϯy��

	if(y >= rect.bottom-26)			//�p�y���a
	{
		y = rect.bottom - 26;

		//���� X �b��V�t�פ��q
		vx += fx;					
		if(vx < 0)
			vx = 0;

		//���� Y �b��V�t�פ��q
		vy += fy;
		if(vy < 0)
			vy = 0;

		vy = -vy;
	}

	tPre = GetTickCount();     //�O������ø�Ϯɶ�
}

//****�T���B�z�禡***********************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:					//������U�T��
			if(wParam==VK_ESCAPE)			//���U Esc ��
				PostQuitMessage(0);
			break;
		case WM_DESTROY:					//���������T��
			DeleteDC(mdc);
			DeleteDC(bufdc);
			DeleteObject(bg);
			DeleteObject(ball);
			ReleaseDC(hWnd,hdc);
			PostQuitMessage(0);
			break;
		default:							//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

