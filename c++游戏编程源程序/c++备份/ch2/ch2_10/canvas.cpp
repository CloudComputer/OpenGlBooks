
#include "stdafx.h"
#include <stdio.h>

//�����ܼƫŧi
HINSTANCE hInst;
HBITMAP fullmap;
HDC		mdc;

//�`�Ʃw�q
const int rows = 10,cols = 10;

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
// �ŧi�a�ϰ}�C�A�i��϶��K�ϡA�����a�ϫ���
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	HDC hdc,bufdc;

	hInst = hInstance;

	hWnd = CreateWindow("canvas", "ø�ϵ���" , WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	MoveWindow(hWnd,10,10,640,400,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	int mapIndex[rows*cols] = { 2,2,2,2,2,0,1,0,1,0,  //��1�C
								3,3,2,2,0,0,0,1,1,0,  //��2�C
								3,0,0,0,0,0,0,0,1,2,  //��3�C
								2,2,0,0,0,0,0,2,2,2,  //��4�C
								2,2,0,0,0,0,2,2,2,2,  //��5�C
								2,2,0,0,0,2,2,0,0,2,  //��6�C
								2,0,0,2,2,2,0,0,1,0,  //��7�C
								0,0,2,0,0,0,1,1,1,1,  //��8�C
								0,2,0,3,3,3,3,3,3,1,  //��9�C
								2,0,3,3,3,3,3,3,3,3 };//��10�C

	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);
	bufdc = CreateCompatibleDC(hdc);

	HBITMAP map[4];
	char filename[20] = "";
	int rowNum,colNum;
	int i,x,y;
	int xstart,ystart;
	
	xstart = 32 * (rows-1);
	ystart = 0;

	fullmap = (HBITMAP)LoadImage(NULL,"bg.bmp",IMAGE_BITMAP,640,480,LR_LOADFROMFILE); 
	SelectObject(mdc,fullmap);

	//���J�U�϶��I�}��
	for(i=0;i<4;i++)
	{
		sprintf(filename,"map%d.bmp",i);
		map[i] = (HBITMAP)LoadImage(NULL,filename,IMAGE_BITMAP,128,32,LR_LOADFROMFILE);
	}

	//�� mapIndex �}�C�����w�q���X�����϶��A�i��a�ϫ���
	for (i=0;i<rows*cols;i++)
	{
		SelectObject(bufdc,map[mapIndex[i]]);

		rowNum = i / cols;     //�D�C�s��
		colNum = i % cols;     //�D��s��
		x = xstart + colNum * 32 + rowNum * (-32);  //�D�K�� X �y��
		y = ystart + rowNum * 16 + colNum * 16;     //�D�K�� Y �y��
		
		BitBlt(mdc,x,y,64,32,bufdc,64,0,SRCAND);
		BitBlt(mdc,x,y,64,32,bufdc,0,0,SRCPAINT);
	}

	MyPaint(hdc);

	ReleaseDC(hWnd,hdc);
	DeleteDC(bufdc);

	return TRUE;
}

//****�ۭqø�Ϩ禡*********************************
void MyPaint(HDC hdc)
{
	//�K�W�����᪺�զX�a��
	SelectObject(mdc,fullmap);
	BitBlt(hdc,0,0,640,480,mdc,0,0,SRCCOPY);
}

//****�T���B�z�禡***********************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		case WM_PAINT:						//������ø�T��
			hdc = BeginPaint(hWnd, &ps);
			MyPaint(hdc);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:					//���������T��
			DeleteDC(mdc);
			DeleteObject(fullmap);
			PostQuitMessage(0);
			break;
		default:							//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

