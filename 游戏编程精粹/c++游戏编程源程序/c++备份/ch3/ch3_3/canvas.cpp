
#include "stdafx.h"

//�����ܼƫŧi
HINSTANCE hInst;
HBITMAP dra,bg;
HDC		hdc,mdc,bufdc;
HWND	hWnd;
DWORD	tPre,tNow;
int		num,x,y;

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
// ���J�I�}�Ϩó]�w�U�����l��
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	char filename[20] = "";
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

	dra = (HBITMAP)LoadImage(NULL,"dra.bmp",IMAGE_BITMAP,760,198,LR_LOADFROMFILE);
	bg = (HBITMAP)LoadImage(NULL,"bg.bmp",IMAGE_BITMAP,640,480,LR_LOADFROMFILE);

	num = 0;    //��ܹϸ�
	x = 640;	//�K�ϰ_�l X �y��
	y = 360;    //�K�ϰ_�l Y �y��

	MyPaint(hdc);

	return TRUE;
}

//****�ۭqø�Ϩ禡*********************************
// 1.���s�]�ʹϮ׳z��
// 2.��s�K�Ϯy��
void MyPaint(HDC hdc)
{
	if(num == 8)
		num = 0;

	//��mdc���K�W�I����
	SelectObject(bufdc,bg);
	BitBlt(mdc,0,0,640,480,bufdc,0,0,SRCCOPY);

	//��mdc�W�i��z�ųB�z
	SelectObject(bufdc,dra);
	BitBlt(mdc,x,y,95,99,bufdc,num*95,99,SRCAND);
	BitBlt(mdc,x,y,95,99,bufdc,num*95,0,SRCPAINT);

	//�N�̫�e����ܩ������
	BitBlt(hdc,0,0,640,480,mdc,0,0,SRCCOPY);

	tPre = GetTickCount();     //�O������ø�Ϯɶ�
	num++;

	x-=20;					   //�p��U���K�Ϯy��
	if(x<=-95)
		x = 640;
}

//****�T���B�z�禡***********************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:					//���������T��
			DeleteDC(mdc);
			DeleteDC(bufdc);
			DeleteObject(dra);
			DeleteObject(bg);
			ReleaseDC(hWnd,hdc);
			PostQuitMessage(0);
			break;
		default:							//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

