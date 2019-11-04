//�ޥμ��Y��
#include "stdafx.h"
#include <stack>
using namespace std;

//�`�Ʃw�q
const int rows = 8,cols = 8;

//�����ܼƫŧi
HINSTANCE hInst;
HBITMAP ball;
HDC		hdc,mdc,bufdc;
HWND	hWnd;
DWORD	tPre,tNow;
char	*str;
int		nowPos,prePos;
bool	find;
stack<int> path;

int mapIndex[rows*cols] = { 0,2,0,0,0,0,0,0,   //��1�C
							0,1,0,1,1,1,1,0,   //��2�C
							0,1,0,1,0,1,1,0,   //��3�C
							0,1,0,0,0,1,1,0,   //��4�C
							0,1,1,1,1,1,1,0,   //��5�C
							0,1,0,0,0,0,1,0,   //��6�C
							0,0,1,1,1,1,1,0,   //��7�C
							0,0,0,0,0,0,3,0 }; //��8�C
int record[rows*cols];

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
// 1.�g�c�����K��
// 2.�]�w�p�y��g�c�J�f�B
// 3.�� mapIndex �]�w record �}�C����l���e
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

	MoveWindow(hWnd,10,10,430,450,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);
	bufdc = CreateCompatibleDC(hdc);

	bmp = CreateCompatibleBitmap(hdc,cols*50,rows*50);
	SelectObject(mdc,bmp);

	HBITMAP tile;
	int rowNum,colNum;
	int i,x,y;

	tile = (HBITMAP)LoadImage(NULL,"tile.bmp",IMAGE_BITMAP,50,50,LR_LOADFROMFILE);
	ball = (HBITMAP)LoadImage(NULL,"ball.bmp",IMAGE_BITMAP,50,50,LR_LOADFROMFILE);

	//�� mapIndex �}�C�����w�q�i��g�c����
	for (i=0;i<rows*cols;i++)
	{
		record[i] = mapIndex[i];

		rowNum = i / cols;			//�D�C�s��
		colNum = i % cols;			//�D��s��
		x = colNum * 50;			//�D�K�� X �y��
		y = rowNum * 50;			//�D�K�� Y �y��
		
		SelectObject(bufdc,tile);

		if(!mapIndex[i])
			BitBlt(mdc,x,y,50,50,bufdc,0,0,SRCCOPY);
		else
		{
			if(mapIndex[i] == 2)	//���g�c�X�f
			{
				nowPos = i;
				path.push(i);
				record[i] = 0;
			}
			BitBlt(mdc,x,y,50,50,bufdc,0,0,WHITENESS);
		}
	}
	prePos = cols * rows + 1;

	MyPaint(hdc);

	return TRUE;
}

//****�ۭqø�Ϩ禡*********************************
// �j�M�i����|�Τp�y���ʶK��
void MyPaint(HDC hdc)
{
	int rowNum,colNum;
	int x,y;
	int up,down,left,right;

	//�M���W���K��
	rowNum = prePos / cols;
	colNum = prePos % cols;
	x = colNum * 50;
	y = rowNum * 50;

	SelectObject(bufdc,ball);
	BitBlt(mdc,x,y,50,50,bufdc,0,0,	WHITENESS);

	//�p�y�K��
	rowNum = nowPos / cols;
	colNum = nowPos % cols;
	x = colNum * 50;
	y = rowNum * 50;

	SelectObject(bufdc,ball);
	BitBlt(mdc,x,y,50,50,bufdc,0,0,	SRCCOPY);

	if(!find)
	{
		str = "��M�X�f��...";

		up    = nowPos - cols;
		down  = nowPos + cols;
		left  = nowPos - 1;
		right = nowPos + 1;

		if(up>=0 && record[up])						//���W��
		{
			path.push(up);
			record[up] = 0;
			prePos = nowPos;
			nowPos = up;

			if(mapIndex[nowPos] == 3)				//���X�f
				find = true;
		}
		else if(down<=cols*rows-1 && record[down])  //���U��
		{
			path.push(down);
			record[down] = 0;
			prePos = nowPos;
			nowPos = down;

			if(mapIndex[nowPos] == 3)
				find = true;
		}
		else if(left>=rowNum*cols && record[left])  //������
		{
			path.push(left);
			record[left] = 0;
			prePos = nowPos;
			nowPos = left;

			if(mapIndex[nowPos] == 3)
				find = true;
		}
		else if(right<=(rowNum+1)*cols-1 && record[right])  //���k��
		{
			path.push(right);
			record[right] = 0;
			prePos = nowPos;
			nowPos = right;

			if(mapIndex[nowPos] == 3)
				find = true;
		}
		else						//�L�i���ʤ��
		{
			if(path.size() <= 1)	//�^��J�f
				str = "�g�c�L�X�f...";
			else
			{
				path.pop();
				prePos = nowPos;
				nowPos = path.top();
			}
		}
	}
	else
	{
		str = "���X�f�F!";
	}

	TextOut(mdc,0,0,str,strlen(str));
	BitBlt(hdc,10,10,cols*50,rows*50,mdc,0,0,SRCCOPY);

	tPre = GetTickCount();
}

//****�T���B�z�禡***********************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:				//������U�T��
			if(wParam==VK_ESCAPE)		//���U Esc ��
				PostQuitMessage(0);
			break;
		case WM_DESTROY:					//���������T��
			DeleteDC(mdc);
			DeleteDC(bufdc);
			DeleteObject(ball);

			ReleaseDC(hWnd,hdc);

			PostQuitMessage(0);
			break;
		default:							//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

