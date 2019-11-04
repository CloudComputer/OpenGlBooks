
#include "stdafx.h"
#include <stdio.h>

//�����ܼƫŧi
HINSTANCE hInst;
HBITMAP bg,ship,bird;
HDC		hdc,mdc,bufdc;
HWND	hWnd;
DWORD	tPre,tNow;
int		x,y,nowX,nowY;
int		w=0;
POINT	p[3];

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
	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
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
// 1.�]�w�����Τp������l��m
// 2.�]�w�ƹ���Ц�m������
// 3.����ƹ���в��ʰϰ�
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HBITMAP bmp;
	POINT pt,lt,rb;
	RECT	rect;

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

	bg = (HBITMAP)LoadImage(NULL,"bg.bmp",IMAGE_BITMAP,648,480,LR_LOADFROMFILE);
	ship = (HBITMAP)LoadImage(NULL,"ship.bmp",IMAGE_BITMAP,100,148,LR_LOADFROMFILE);
	bird = (HBITMAP)LoadImage(NULL,"bird.bmp",IMAGE_BITMAP,122,122,LR_LOADFROMFILE);

	x = 300;
	y = 300;
	nowX = 300;
	nowY = 300;

	//�]�w�ƹ���Ц�m
	pt.x = 300;
	pt.y = 300;
	ClientToScreen(hWnd,&pt);
	SetCursorPos(pt.x,pt.y);
	
	ShowCursor(false);		//���÷ƹ����

	//����ƹ���в��ʰϰ�
	GetClientRect(hWnd,&rect);
	lt.x = rect.left;
	lt.y = rect.top;
	rb.x = rect.right;
	rb.y = rect.bottom;
	ClientToScreen(hWnd,&lt);
	ClientToScreen(hWnd,&rb);
	rect.left = lt.x;
	rect.top = lt.y;
	rect.right = rb.x;
	rect.bottom = rb.y;
	ClipCursor(&rect);

	p[0].x = 30;
	p[0].y = 100;

	p[1].x = 250;
	p[1].y = 250;

	p[2].x = 500;
	p[2].y = 400;

	MyPaint(hdc);

	return TRUE;
}

//****�ۭqø�Ϩ禡*********************************
// 1.�]�w�����y�Шöi��K��
// 2.�]�w�p���y�Шöi��K��
void MyPaint(HDC hdc)
{
	int i;

	//�K�W�I����
	SelectObject(bufdc,bg);
	BitBlt(mdc,0,0,w,480,bufdc,640-w,0,SRCCOPY);
	BitBlt(mdc,w,0,640-w,480,bufdc,0,0,SRCCOPY);

	//�K�W������
	if(nowX < x)
	{
		nowX += 10;
		if(nowX > x)
			nowX = x;
	}
	else
	{
		nowX -=10;
		if(nowX < x)
			nowX = x;
	}

	if(nowY < y)
	{
		nowY += 10;
		if(nowY > y)
			nowY = y;
	}
	else
	{
		nowY -= 10;
		if(nowY < y)
			nowY = y;
	}
	SelectObject(bufdc,ship);
	BitBlt(mdc,nowX,nowY,100,74,bufdc,0,74,SRCAND);
	BitBlt(mdc,nowX,nowY,100,74,bufdc,0,0,SRCPAINT);

	//�K�W�p����
	SelectObject(bufdc,bird);
	for(i=0;i<3;i++)
	{
		if(rand()%3 != 1)		//�]�w2/3���v�i��l�v
		{
			if(p[i].y > nowY-16)
				p[i].y -= 5;
			else
				p[i].y += 5;
	
			if(p[i].x > nowX-25)
				p[i].x -= 5;
			else
				p[i].x += 5;
		}
		
		if(p[i].x > nowX-25)    //�P�_�p�����ʤ�V
		{
			BitBlt(mdc,p[i].x,p[i].y,61,61,bufdc,61,61,SRCAND);
			BitBlt(mdc,p[i].x,p[i].y,61,61,bufdc,0,61,SRCPAINT);
		}
		else
		{
			BitBlt(mdc,p[i].x,p[i].y,61,61,bufdc,61,0,SRCAND);
			BitBlt(mdc,p[i].x,p[i].y,61,61,bufdc,0,0,SRCPAINT);
		}
	}

	BitBlt(hdc,0,0,640,480,mdc,0,0,SRCCOPY);

	tPre = GetTickCount();

	w += 10;
	if(w==640)
		w = 0;
}

//****�T���B�z�禡***********************************
// 1.�B�zWM_MOUSEMOVE�T���]�w�����K�Ϯy��
// 2.����������ɫ�_�ƹ����ʰϰ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:				//������U�T��
			if(wParam==VK_ESCAPE)		//���U Esc ��
				PostQuitMessage(0);
			break;
		case WM_MOUSEMOVE:
			x = LOWORD(lParam);			//���o�ƹ� X �y��
			if(x > 530)
				x = 530;
			else if(x < 0)
				x = 0;

			y = HIWORD(lParam);			//���o�ƹ� Y �y��
			if(y > 380)
				y = 380;
			else if(y < 0)
				y = 0;
				
			break;
		case WM_DESTROY:				//���������T��
			ClipCursor(NULL);			//��_�ƹ����ʰϰ�

			DeleteDC(mdc);
			DeleteDC(bufdc);
			DeleteObject(bg);
			DeleteObject(ship);
			DeleteObject(bird);
			ReleaseDC(hWnd,hdc);

			PostQuitMessage(0);
			break;
		default:						//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

