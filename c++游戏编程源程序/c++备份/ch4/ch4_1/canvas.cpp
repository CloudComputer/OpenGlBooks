
#include "stdafx.h"
#include <stdio.h>

//�����ܼƫŧi
HINSTANCE hInst;
HBITMAP girl[4],bg;
HDC		hdc,mdc,bufdc;
HWND	hWnd;
DWORD	tPre,tNow;
int		num,dir,x,y;

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
			if(tNow-tPre >= 40)
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
// ���J�I�}�Ϩó]�w�U��l��
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

	MoveWindow(hWnd,10,10,640,480,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);
	bufdc = CreateCompatibleDC(hdc);

	bmp = CreateCompatibleBitmap(hdc,640,480);
	SelectObject(mdc,bmp);

	x = 300;
	y = 250;
	dir = 0;
	num = 0;

	girl[0] = (HBITMAP)LoadImage(NULL,"girl0.bmp",IMAGE_BITMAP,440,148,LR_LOADFROMFILE);
	girl[1] = (HBITMAP)LoadImage(NULL,"girl1.bmp",IMAGE_BITMAP,424,154,LR_LOADFROMFILE);
	girl[2] = (HBITMAP)LoadImage(NULL,"girl2.bmp",IMAGE_BITMAP,480,148,LR_LOADFROMFILE);
	girl[3] = (HBITMAP)LoadImage(NULL,"girl3.bmp",IMAGE_BITMAP,480,148,LR_LOADFROMFILE);
	bg = (HBITMAP)LoadImage(NULL,"bg.bmp",IMAGE_BITMAP,640,480,LR_LOADFROMFILE);

	MyPaint(hdc);

	return TRUE;
}

//****�ۭqø�Ϩ禡*********************************
// �H���K�Ϯy�Эץ��ε����K��
void MyPaint(HDC hdc)
{
	int w,h;

	SelectObject(bufdc,bg);
	BitBlt(mdc,0,0,640,480,bufdc,0,0,SRCCOPY);

	SelectObject(bufdc,girl[dir]);
	switch(dir)
	{
		case 0:
			w = 55;
			h = 74;
			break;
		case 1:
			w = 53;
			h = 77;
			break;
		case 2:
			w = 60;
			h = 74;
			break;
		case 3:
			w = 60;
			h = 74;
			break;
	}
	BitBlt(mdc,x,y,w,h,bufdc,num*w,h,SRCAND);
	BitBlt(mdc,x,y,w,h,bufdc,num*w,0,SRCPAINT);
	
	BitBlt(hdc,0,0,640,480,mdc,0,0,SRCCOPY);

	tPre = GetTickCount();         //�O������ø�Ϯɶ�

	num++;
	if(num == 8)
		num = 0;

}

//****�T���B�z�禡***********************************
// 1.���UEsc�䵲���{��
// 2.���U��V�䭫�]�K�Ϯy��
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:			      //������U�T��
			switch (wParam) 
			{
				case VK_ESCAPE:           //���U Esc ��
					PostQuitMessage( 0 );
					break;
				case VK_UP:				  //���U�W��
					switch(dir)
					{
						case 0:	
							y -= 10;
							break;
						case 1:
							x -= 1;
							y -= 8;
							break;
						case 2:	
							x += 2;
							y -= 10;
							break;
						case 3:
							x += 2;
							y -= 10;
							break;
					}
					if(y < 0)
						y = 0;
					dir = 0;
					break;
				case VK_DOWN:			  //���U�U��
					switch(dir)
					{
						case 0:
							x += 1;
							y += 8;
							break;
						case 1:
							y += 10;
							break;
						case 2:
							x += 3;
							y += 6;
							break;
						case 3:
							x += 3;
							y += 6;
							break;
					}

					if(y > 375)
						y = 375;
					dir = 1;
					break;
				case VK_LEFT:			  //���U����
					switch(dir)
					{
						case 0:
							x -= 12;
							break;
						case 1:
							x -= 13;
							y += 4;
							break;
						case 2:
							x -= 10;
							break;
						case 3:
							x -= 10;
							break;
					}
					if(x < 0)
						x = 0;
					dir = 2;
					break;
				case VK_RIGHT:			   //���U�k��
					switch(dir)
					{
						case 0:
							x += 8;
							break;
						case 1:
							x += 7;
							y += 4;
							break;
						case 2:
							x += 10;
							break;
						case 3:
							x += 10;
							break;
					}
					if(x > 575)
						x = 575;
					dir = 3;
					break;
			}
			break;
		case WM_DESTROY:			    	//���������T��
			int i;

			DeleteDC(mdc);
			DeleteDC(bufdc);
			for(i=0;i<4;i++)
				DeleteObject(girl[i]);
			DeleteObject(bg);
			ReleaseDC(hWnd,hdc);

			PostQuitMessage(0);
			break;
		default:							//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

