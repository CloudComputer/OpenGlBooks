
#include "stdafx.h"

//�����ܼƫŧi
HINSTANCE hInst;
HBITMAP map;
HDC		hdc,mdc;
HWND	hWnd;
DWORD	tPre,tNow;
int		x=0,y=0;

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
// �إߵ����θ��J�I����
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
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

	map = (HBITMAP)LoadImage(NULL,"map.bmp",IMAGE_BITMAP,1548,1129,LR_LOADFROMFILE);

	SelectObject(mdc,map);

	MyPaint(hdc);

	return TRUE;
}

//****�ۭqø�Ϩ禡*********************************
// �̭I���ϰŵ������W���I�y�жi��K��
void MyPaint(HDC hdc)
{
	BitBlt(hdc,0,0,640,480,mdc,x,y,SRCCOPY);
	tPre = GetTickCount();
}

//****�T���B�z�禡***********************************
// �̾ګ��U����V��ӧ��ܭI���ϰŵ������W���I�y��
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:			     //���U��L�T��
			switch (wParam) 
			{
				case VK_UP:				 //���U�W��
					y -= 20;
					if(y < 0)
						y = 0;
					break;
				case VK_DOWN:			 //���U�U��
					y += 20;
					if(y > 660)
						y = 660;
					break;
				case VK_LEFT:			 //���U����
					x -= 20;
					if(x < 0)
						x = 0;
					break;
				case VK_RIGHT:			 //���U�k��
					x += 20;
					if(x > 910)
						x = 910;
					break;
			}
			break;
		case WM_DESTROY:					//���������T��
			DeleteDC(mdc);
			DeleteObject(map);
			ReleaseDC(hWnd,hdc);
			PostQuitMessage(0);
			break;
		default:							//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

