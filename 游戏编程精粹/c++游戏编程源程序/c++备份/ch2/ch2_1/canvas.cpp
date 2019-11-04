
#include "stdafx.h"

//�����ܼƫŧi
HINSTANCE hInst;
HPEN hPen[7];
HBRUSH hBru[7];
int sPen[7] = {PS_SOLID,PS_DASH,PS_DOT,PS_DASHDOT,PS_DASHDOTDOT,PS_NULL,PS_INSIDEFRAME};
int sBru[6] = {HS_VERTICAL,HS_HORIZONTAL,HS_CROSS,HS_DIAGCROSS,HS_FDIAGONAL,HS_BDIAGONAL};

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
// �إ� 7 �ؤ��P���e���εe�ꪫ��
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

	MoveWindow(hWnd,10,10,650,350,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	for(i=0;i<=6;i++)
	{
		hPen[i] = CreatePen(sPen[i],1,RGB(255,0,0));
		if(i==6)
			hBru[i] = CreateSolidBrush(RGB(0,255,0));
		else
			hBru[i] = CreateHatchBrush(sBru[i],RGB(0,255,0));
	}

	hdc = GetDC(hWnd);
	MyPaint(hdc);
	ReleaseDC(hWnd,hdc);

	return TRUE;
}

//****�ۭqø�Ϩ禡*********************************
// �H�U���e���εe��ø�s�u���P��R�x��
void MyPaint(HDC hdc)
{
	int i,x1,x2,y;
	
	//�H 7 �ؤ��P�e��ø�s�u��
	for(i=0;i<=6;i++)
	{
		y = (i+1) * 30;

		SelectObject(hdc,hPen[i]);
		MoveToEx(hdc,30,y,NULL);	 //���ʽu���_�I
		LineTo(hdc,100,y);			 //�e�u
	}
	
	x1 = 120;
	x2 = 180;

	//�H 7 �ؤ��P�e���R�x��
	for(i=0;i<=6;i++)
	{
		SelectObject(hdc,hBru[i]);
		Rectangle(hdc,x1,30,x2,y);	 //�e�ʳ��x��
		x1 += 70;
		x2 += 70;
	}
}
//****�T���B�z�禡***********************************
// 1.������ø�T���o�ͮɩI�sMyPaint()
// 2.���������T���o�ͮɧR��GDI����
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
			for(i=0;i<=6;i++)
			{
				DeleteObject(hPen[i]);		//�R���e��
				DeleteObject(hBru[i]);		//�R���e��
			}
			PostQuitMessage(0);
			break;
		default:							//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

