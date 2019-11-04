
#include "stdafx.h"
#include <stdio.h>

//�w�q���c
struct dragon
{
	int x,y;
	int dir;
};

//�`�Ʃw�q�P�����ܼƫŧi
const int draNum = 10;

HINSTANCE hInst;
HBITMAP draPic[4],bg;
HDC		hdc,mdc,bufdc;
HWND	hWnd;
DWORD	tPre,tNow;
int		picNum;
dragon  dra[draNum];


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
// ���J�I�}�Ϩó]�w�U��l��
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HBITMAP bmp;
	hInst = hInstance;
	int i;

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

	draPic[0] = (HBITMAP)LoadImage(NULL,"dra0.bmp",IMAGE_BITMAP,528,188,LR_LOADFROMFILE);
	draPic[1] = (HBITMAP)LoadImage(NULL,"dra1.bmp",IMAGE_BITMAP,544,164,LR_LOADFROMFILE);
	draPic[2] = (HBITMAP)LoadImage(NULL,"dra2.bmp",IMAGE_BITMAP,760,198,LR_LOADFROMFILE);
	draPic[3] = (HBITMAP)LoadImage(NULL,"dra3.bmp",IMAGE_BITMAP,760,198,LR_LOADFROMFILE);
	bg = (HBITMAP)LoadImage(NULL,"bg.bmp",IMAGE_BITMAP,640,480,LR_LOADFROMFILE);

	for(i=0;i<draNum;i++)
	{
		dra[i].dir = 3;    //�_�l��V
		dra[i].x = 200;	   //�K�ϰ_�l X �y��
		dra[i].y = 200;    //�K�ϰ_�l Y �y��
	}

	MyPaint(hdc);

	return TRUE;
}

//��w�ƧǪk
void BubSort(int n)
{
	int i,j;
	bool f;
	dragon tmp;

	for(i=0;i<n-1;i++)
	{
		f = false;
		for(j=0;j<n-i-1;j++)
		{
			if(dra[j+1].y < dra[j].y)
			{
				tmp = dra[j+1];
				dra[j+1] = dra[j];
				dra[j] = tmp;
				f = true;
			}
		}
		if(!f)
			break;
	}
}

//****�ۭqø�Ϩ禡*********************************
// 1.��������]�ʪ����s�i��ƧǶK��
// 2.���s�K�Ϯy�Эץ�
void MyPaint(HDC hdc)
{
	int w,h,i;

	if(picNum == 8)
		picNum = 0;

	//��mdc�����K�W�I����
	SelectObject(bufdc,bg);
	BitBlt(mdc,0,0,640,480,bufdc,0,0,SRCCOPY);

	BubSort(draNum);

	for(i=0;i<draNum;i++)
	{
		SelectObject(bufdc,draPic[dra[i].dir]);
		switch(dra[i].dir)
		{
			case 0:
				w = 66;
				h = 94;
				break;
			case 1:
				w = 68;
				h = 82;
				break;
			case 2:
				w = 95;
				h = 99;
				break;
			case 3:
				w = 95;
				h = 99;
				break;
		}
		BitBlt(mdc,dra[i].x,dra[i].y,w,h,bufdc,picNum*w,h,SRCAND);
		BitBlt(mdc,dra[i].x,dra[i].y,w,h,bufdc,picNum*w,0,SRCPAINT);
	}

	//�N�̫�e����ܩ������
	BitBlt(hdc,0,0,640,480,mdc,0,0,SRCCOPY);

	tPre = GetTickCount();         //�O������ø�Ϯɶ�
	picNum++;

	for(i=0;i<draNum;i++)
	{
		switch(rand()%4)          //�H���M�w�U�����ʤ�V
		{
			case 0:					     //�W
				switch(dra[i].dir)
				{
					case 0:	
						dra[i].y -= 20;
						break;
					case 1:
						dra[i].x += 2;
						dra[i].y -= 31;
						break;
					case 2:	
						dra[i].x += 14;
						dra[i].y -= 20;
						break;
					case 3:
						dra[i].x += 14;
						dra[i].y -= 20;
						break;
				}
				if(dra[i].y < 0)
					dra[i].y = 0;
				dra[i].dir = 0;
				break;
			case 1:				     	//�U
				switch(dra[i].dir)
				{
					case 0:
						dra[i].x -= 2;
						dra[i].y += 31;
						break;
					case 1:
						dra[i].y += 20;
						break;
					case 2:
						dra[i].x += 15;
						dra[i].y += 29;
						break;
					case 3:
						dra[i].x += 15;
						dra[i].y += 29;
						break;
				}

				if(dra[i].y > 370)
					dra[i].y = 370;
				dra[i].dir = 1;
				break;
			case 2:				    	//��
				switch(dra[i].dir)
				{
					case 0:
						dra[i].x -= 34;
						break;
					case 1:
						dra[i].x -= 34;
						dra[i].y -= 9;
						break;
					case 2:
						dra[i].x -= 20;
						break;
					case 3:
						dra[i].x -= 20;
						break;
				}
				if(dra[i].x < 0)
					dra[i].x = 0;
				dra[i].dir = 2;
				break;
			case 3:				    	//�k
				switch(dra[i].dir)
				{
					case 0:
						dra[i].x += 6;
						break;
					case 1:
						dra[i].x += 6;
						dra[i].y -= 10;
						break;
					case 2:
						dra[i].x += 20;
						break;
					case 3:
						dra[i].x += 20;
						break;
				}
				if(dra[i].x > 535)
					dra[i].x = 535;
				dra[i].dir = 3;
				break;
		}
	}
}

//****�T���B�z�禡***********************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		int i;

		case WM_DESTROY:					//���������T��
			DeleteDC(mdc);
			DeleteDC(bufdc);
			for(i=0;i<4;i++)
				DeleteObject(draPic[i]);
			DeleteObject(bg);
			ReleaseDC(hWnd,hdc);
			PostQuitMessage(0);
			break;
		default:							//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

