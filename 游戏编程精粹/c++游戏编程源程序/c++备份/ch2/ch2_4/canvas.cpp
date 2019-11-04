#include "stdafx.h"

//�����ܼƫŧi
HINSTANCE hInst;
HPEN hPen;
HBRUSH hBru[4];
int sBru[4] = {HS_VERTICAL,HS_HORIZONTAL,HS_CROSS,HS_DIAGCROSS};

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
// �إߵe���P�e��
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	HDC hdc;
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

	hPen = CreatePen(PS_SOLID,3,RGB(255,0,0));
	for(i=0;i<=3;i++)
	{
		hBru[i] = CreateHatchBrush(sBru[i],RGB(0,0,255));
	}

	hdc = GetDC(hWnd);
	MyPaint(hdc);
	ReleaseDC(hWnd,hdc);

	return TRUE;
}

//****�ۭqø�Ϩ禡*********************************
void MyPaint(HDC hdc)
{
	SelectObject(hdc,hPen);

	SelectObject(hdc,hBru[0]);
	Ellipse(hdc,20,20,270,150);                 //�e����
	TextOut(hdc,120,160,"����",strlen("����"));

	SelectObject(hdc,hBru[1]);
	RoundRect(hdc,300,20,550,150,30,30);        //�e�ꨤ�x��
	TextOut(hdc,400,160,"�ꨤ�x��",strlen("�ꨤ�x��"));

	SelectObject(hdc,hBru[2]);
	Pie(hdc,20,210,270,340,50,50,300,300);      //�e����
	TextOut(hdc,120,350,"����",strlen("����"));

	SelectObject(hdc,hBru[3]);
	Chord(hdc,300,210,550,340,50,50,600,300);   //�e�}��
	TextOut(hdc,400,350,"�}��",strlen("�}��"));
}

//****�T���B�z�禡***********************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int i;

	switch (message) 
	{
		case WM_PAINT:						//������ø�T��
			hdc = BeginPaint(hWnd, &ps);
			MyPaint(hdc);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:					//���������T��
			DeleteObject(hPen);
			for(i=0;i<=3;i++)
				DeleteObject(hBru[i]);
			PostQuitMessage(0);
			break;
		default:							//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}