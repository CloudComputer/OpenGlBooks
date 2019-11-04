
#include "stdafx.h"
#include <stdio.h>

//�����ܼƫŧi
HINSTANCE hInst;
HBITMAP bg,girl;
HDC		mdc;

//�`�Ʃw�q
const int xstart = 50;
const int ystart = 20;

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
// �b�z���B�z�A�B�z��N�b�z���Ϧs�^ girl
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	HDC hdc;

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

	BITMAP bm1,bm2;
	unsigned char *px1,*px2;

	//�B�z�I����
	bg = (HBITMAP)LoadImage(NULL,"bg.bmp",IMAGE_BITMAP,600,450,LR_LOADFROMFILE); 
	GetObject(bg,sizeof(BITMAP),&bm1);

	if(bm1.bmBitsPixel != 32 && bm1.bmBitsPixel != 24) 
	{
		MessageBox(NULL,"���{���u��b 32 bit �� 24 bit ��ܼҦ�������","ĵ�i",0);
		return FALSE;
	}

	px1 = new unsigned char [bm1.bmHeight * bm1.bmWidthBytes];
	GetBitmapBits(bg,bm1.bmHeight * bm1.bmWidthBytes,px1);

	//�B�z�e����
	girl = (HBITMAP)LoadImage(NULL,"girl.bmp",IMAGE_BITMAP,298,329,LR_LOADFROMFILE); 
	GetObject(girl,sizeof(BITMAP),&bm2);
	px2 = new unsigned char [bm2.bmHeight * bm2.bmWidthBytes];
	GetBitmapBits(girl,bm2.bmHeight * bm2.bmWidthBytes,px2);

	int xend,yend;
	int x,y,i;				//�j����ܼ�
	int rgb_b;
	int PxBytes = bm1.bmBitsPixel / 8 ;

	xend = xstart + 298;
	yend = ystart + 329;

	//�B�z�I���Ϲ����C��
	for(y=ystart;y<yend;y++) 	
	{
		for(x=xstart;x<xend;x++) 
		{
			rgb_b = y * bm1.bmWidthBytes + x * PxBytes ;

			px1[rgb_b] = px1[rgb_b] * 0.7;		
			px1[rgb_b+1] = px1[rgb_b+1] * 0.7;	
			px1[rgb_b+2] = px1[rgb_b+2] * 0.7;	
		}
	}

	//�B�z�e���Ϲ����C��
	for(y=0;y<(bm2.bmHeight); y++) 	
	{
		for(x=0;x<bm2.bmWidth; x++) 
		{
			rgb_b = y * bm2.bmWidthBytes + x * PxBytes ;
			i = (ystart+y) * bm1.bmWidthBytes + (xstart+x) * PxBytes;

			px2[rgb_b]   = px2[rgb_b]  *0.3 + px1[i];	
			px2[rgb_b+1] = px2[rgb_b+1] *0.3 + px1[i+1];	
			px2[rgb_b+2] = px2[rgb_b+2] *0.3 + px1[i+2];	
		}
	}

	SetBitmapBits(girl,bm2.bmHeight*bm2.bmWidthBytes,px2);

	MyPaint(hdc);

	ReleaseDC(hWnd,hdc);
	delete [] px1;
	delete [] px2;

	return TRUE;
}

//****�ۭqø�Ϩ禡*********************************
void MyPaint(HDC hdc)
{
	//�K�W�I����
	SelectObject(mdc,bg);
	BitBlt(hdc,0,0,600,450,mdc,0,0,SRCCOPY);

	//�K�W�B�z�᪺�b�z����
	SelectObject(mdc,girl);
	BitBlt(hdc,xstart,ystart,298,329,mdc,0,0,SRCCOPY);
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
			DeleteObject(bg);
			DeleteObject(girl);
			PostQuitMessage(0);
			break;
		default:							//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

