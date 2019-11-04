
#include "stdafx.h"
#include <stdio.h>

//�����ܼƫŧi
HINSTANCE hInst;
HBITMAP girl[7];
HDC		mdc,hdc;
int		num;

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

	//�T���j��
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
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
// 1.�q�ɮ׸��J�I�}��
// 2.�إ߭p�ɾ�
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
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
		sprintf(filename,"girl%d.bmp",i);
		girl[i] = (HBITMAP)LoadImage(NULL,filename,IMAGE_BITMAP,640,480,LR_LOADFROMFILE);
	}
	
	num = 0;
	SetTimer(hWnd,1,500,NULL);

	MyPaint(hdc);

	return TRUE;
}

//****�ۭqø�Ϩ禡*********************************
// �̹ϸ����Ƕi������K��
void MyPaint(HDC hdc)
{
	if(num == 7)
		num = 0;

	SelectObject(mdc,girl[num]);
	BitBlt(hdc,0,0,600,450,mdc,0,0,SRCCOPY);

	num++;
}

//****�T���B�z�禡***********************************
// 1.�[�J�B�zWM_TIMER�T��
// 2.����������ɧR���p�ɾ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i;

	switch (message)
	{
		case WM_TIMER:						//�ɶ��T��
			MyPaint(hdc);
			break;
		case WM_DESTROY:					//���������T��
			DeleteDC(mdc);
			ReleaseDC(hWnd,hdc);
			for(i=0;i<7;i++)
				DeleteObject(girl[i]);

			KillTimer(hWnd,1);

			PostQuitMessage(0);
			break;
		default:							//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}