
#include "stdafx.h"

//�����ܼƫŧi
HINSTANCE hInst;
HBITMAP dra,bg[3];
HDC		hdc,mdc,bufdc;
HWND	hWnd;
DWORD	tPre,tNow;
int		x0=0,x1=0,x2=0,num=0;

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
// ���J�I���Ϩëإߪ��I�}�Ͽ�Ψ�mdc��
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

	bg[0] = (HBITMAP)LoadImage(NULL,"bg0.bmp",IMAGE_BITMAP,640,480,LR_LOADFROMFILE);
	bg[1] = (HBITMAP)LoadImage(NULL,"bg1.bmp",IMAGE_BITMAP,640,600,LR_LOADFROMFILE);
	bg[2] = (HBITMAP)LoadImage(NULL,"bg2.bmp",IMAGE_BITMAP,640,600,LR_LOADFROMFILE);
	dra = (HBITMAP)LoadImage(NULL,"dra.bmp",IMAGE_BITMAP,760,198,LR_LOADFROMFILE);

	MyPaint(hdc);

	return TRUE;
}

//****�ۭqø�Ϩ禡*********************************
// 1.�̦U�I�����񶶧Ƕi��`���I���K��
// 2.�i��e�����s�Ϫ��z�ŶK��
// 3.���]�U�I���Ϥ��μe�׻P�]�ʮ��s�Ϲϸ�
void MyPaint(HDC hdc)
{
	//�K�W�ѪŹ�
	SelectObject(bufdc,bg[0]);
	BitBlt(mdc,0,0,x0,300,bufdc,640-x0,0,SRCCOPY);
	BitBlt(mdc,x0,0,640-x0,300,bufdc,0,0,SRCCOPY);

	//�K�W��a��
	BitBlt(mdc,0,300,x2,180,bufdc,640-x2,300,SRCCOPY);
	BitBlt(mdc,x2,300,640-x2,180,bufdc,0,300,SRCCOPY);

	//�K�W�s�r�Ϩóz��
	SelectObject(bufdc,bg[1]);
	BitBlt(mdc,0,0,x1,300,bufdc,640-x1,300,SRCAND);
	BitBlt(mdc,x1,0,640-x1,300,bufdc,0,300,SRCAND);
	BitBlt(mdc,0,0,x1,300,bufdc,640-x1,0,SRCPAINT);
	BitBlt(mdc,x1,0,640-x1,300,bufdc,0,0,SRCPAINT);

	//�K�W�ЫιϨóz��
	SelectObject(bufdc,bg[2]);
	BitBlt(mdc,0,250,x2,300,bufdc,640-x2,300,SRCAND);
	BitBlt(mdc,x2,250,640-x2,300,bufdc,0,300,SRCAND);
	BitBlt(mdc,0,250,x2,300,bufdc,640-x2,0,SRCPAINT);
	BitBlt(mdc,x2,250,640-x2,300,bufdc,0,0,SRCPAINT);

	//�K�W���s�Ϩóz��
	SelectObject(bufdc,dra);
	BitBlt(mdc,250,350,95,99,bufdc,num*95,99,SRCAND);
	BitBlt(mdc,250,350,95,99,bufdc,num*95,0,SRCPAINT);

	BitBlt(hdc,0,0,640,480,mdc,0,0,SRCCOPY);

	tPre = GetTickCount();

	x0 += 5;		//���]�ѪŭI�����μe��
	if(x0==640)
		x0 = 0;

	x1 += 8;		//���]�s�Z�I�����μe��
	if(x1==640)
		x1 = 0;

	x2 += 16;		//���]��a�ΩЫέI�����μe��
	if(x2==640)
		x2 = 0;

	num++;			//���]�]�ʹϸ�
	if(num == 8)
		num = 0;
}

//****�T���B�z�禡***********************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:					//���������T��
			DeleteDC(mdc);
			DeleteDC(bufdc);
			DeleteObject(bg[0]);
			DeleteObject(bg[1]);
			DeleteObject(bg[2]);
			DeleteObject(dra);
			ReleaseDC(hWnd,hdc);
			PostQuitMessage(0);
			break;
		default:							//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

