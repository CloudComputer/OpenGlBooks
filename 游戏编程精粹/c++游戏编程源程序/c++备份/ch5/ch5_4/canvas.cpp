
#include "stdafx.h"
#include <stdio.h>
#include <math.h>

//�����ܼƫŧi
HINSTANCE hInst;
HBITMAP	chess[2];
HDC		hdc,mdc,bufdc;
HWND	hWnd;
DWORD	tPre,tNow;
int		board[10][10];
bool	ptab[10][10][192];
bool	ctab[10][10][192];
int		win[2][192];
int		num[2];
bool	turn,over;
int		winner;

//�禡�ŧi
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				MyPaint(HDC hdc);
void				InitGame();
void				ComTurn();

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
// �ѽL�����H�ΩI�s InitGame() �禡�}�l�ѧ�
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HBITMAP tile,bmp;
	int rowNum,colNum;
	int i,x,y;

	hInst = hInstance;
	hWnd = CreateWindow("canvas", "ø�ϵ���" , WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	MoveWindow(hWnd,10,10,480,520,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	hdc = GetDC(hWnd);
	mdc = CreateCompatibleDC(hdc);
	bufdc = CreateCompatibleDC(hdc);

	bmp = CreateCompatibleBitmap(hdc,450,450);
	SelectObject(mdc,bmp);

	tile = (HBITMAP)LoadImage(NULL,"tile.bmp",IMAGE_BITMAP,45,45,LR_LOADFROMFILE);
	chess[0] = (HBITMAP)LoadImage(NULL,"chess0.bmp",IMAGE_BITMAP,38,38,LR_LOADFROMFILE);
	chess[1] = (HBITMAP)LoadImage(NULL,"chess1.bmp",IMAGE_BITMAP,38,38,LR_LOADFROMFILE);

	for (i=0;i<100;i++)
	{
		rowNum = i / 10;
		colNum = i % 10;
		x = colNum * 45;
		y = rowNum * 45;
		
		SelectObject(bufdc,tile);
		BitBlt(mdc,x,y,45,45,bufdc,0,0,SRCCOPY);
	}

	InitGame();
	MyPaint(hdc);

	return TRUE;
}

//****�ѧ���l�禡***********************************
// 1.�]�w�ѽL��l���A����Ӫ��e
// 2.�M�w���U�l���@��
void InitGame()
{
	int i,j,k;
	int count=0;

	over = false;
	num[0] = num[1] = 0;

	//�]�w���a�P�q���b�U����ӲզX�����Ѥl��
	for(i=0;i<192;i++)
	{
		win[0][i] = 0;
		win[1][i] = 0;
	}

	//��l�ƴѽL���A
	for(i=0;i<10;i++)          
		for(j=0;j<10;j++)
			board[i][j] = 2;

	//�]�w������V����ӲզX
	for(i=0;i<10;i++)          
		for(j=0;j<6;j++)
		{
			for(k=0;k<5;k++)
			{
				ptab[i][j+k][count] = true;
				ctab[i][j+k][count] = true;
			}
			count++;
		}

	//�]�w������V����ӲզX
	for(i=0;i<10;i++)          
		for(j=0;j<6;j++)
		{
			for(k=0;k<5;k++)
			{
				ptab[j+k][i][count] = true;
				ctab[j+k][i][count] = true;
			}
			count++;
		}

	//�]�w���﨤�u��V����ӲզX
	for(i=0;i<6;i++)           
		for(j=0;j<6;j++)
		{
			for(k=0;k<5;k++)
			{
				ptab[j+k][i+k][count] = true;
				ctab[j+k][i+k][count] = true;
			}
			count++;
		}

	//�]�w�Ϲ﨤�u��V����ӲզX
	for(i=0;i<6;i++)           
		for(j=9;j>=4;j--)
		{
			for(k=0;k<5;k++)
			{
				ptab[j-k][i+k][count] = true;
				ctab[j-k][i+k][count] = true;
			}
			count++;
		}

	//�üƨM�w�Ѩ��@����U�Ѥl
	srand(GetTickCount());
	if(rand()%2 == 0)
		turn = true;
	else
		turn = false;
}

//****�q���U�l�禡***********************************
// 1.�p����Ӥ���
// 2.��̨ܳΦ�m�i��U�l�ʧ@
void ComTurn()
{
	int	grades[2][10][10];
	int m,n,i,max=0;
	int u,v;

	for(m=0;m<10;m++) 
		for(n=0;n<10;n++)
		{
			grades[0][m][n] = 0;
			grades[1][m][n] = 0;

			if(board[m][n] == 2)
			{
				for(i=0;i<192;i++)
				{
					//�p�⪱�a�b�ŴѮ�W����Ӥ���
					if(ptab[m][n][i] && win[0][i] != 7)
					{
						switch(win[0][i])
						{
							case 0:
								grades[0][m][n]+=1;
								break;
							case 1:
								grades[0][m][n]+=200;
								break;
							case 2:
								grades[0][m][n]+=400;
								break;
							case 3:
								grades[0][m][n]+=2000;
								break;
							case 4:
								grades[0][m][n]+=10000;
								break;
						}
					}

					//�p��q���b�ŴѮ�W����Ӥ���
					if(ctab[m][n][i] && win[1][i] != 7)
					{
						switch(win[1][i])
						{
							case 0:
								grades[1][m][n]+=1;
								break;
							case 1:
								grades[1][m][n]+=220;
								break;
							case 2:
								grades[1][m][n]+=420;
								break;
							case 3:
								grades[1][m][n]+=2100;
								break;
							case 4:
								grades[1][m][n]+=20000;
								break;
						}
					}
				}

				if(max == 0)
				{
					u = m;
					v = n;
				}

				if(grades[0][m][n] > max)
				{
					max = grades[0][m][n];
					u = m;
					v = n;
				}
				else if(grades[0][m][n] == max)
				{
					if(grades[1][m][n] > grades[1][u][v])
					{
						u = m;
						v = n;
					}
				}

				if(grades[1][m][n] > max)
				{
					max = grades[1][m][n];
					u = m;
					v = n;
				}
				else if(grades[1][m][n] == max)
				{
					if(grades[0][m][n] > grades[0][u][v])
					{
						u = m;
						v = n;
					}
				}
			}
		}

	board[u][v] = 1;      //�]�w���q�����Ѥl
	num[1]++;

	if(num[0] == 50 && num[1] == 50)
	{
		winner = 2;			//����
		over = true;
	}
	else
		for(i=0;i<192;i++)
		{
			if(ctab[u][v][i])
			{
				win[1][i]++;
				ptab[u][v][i] = false;
				win[0][i] = 7;

				if(win[1][i] == 5)
				{
					winner = 1;
					over = true;
				}
			}
		}
	turn = true;			//�����a�U
}

//****�ۭqø�Ϩ禡*********************************
// �����K�Ϥ���ܰT��
void MyPaint(HDC hdc)
{
	int m,n;
	char *str;

	if(over)
	{
		switch(winner)
		{
			case 0:
				str = "�zĹ�F ! ���U F1 �i���s�i��C��..";
				break;
			case 1:
				str = "�q��Ĺ�F ! ���U F1 �i���s�i��C��..";
				break;
			case 2:
				str = "�����ӭt ! ���U F1 �i���s�i��C��..";
				break;
		}
		TextOut(hdc,10,470,str,strlen(str));
	}
	else if(!turn)						//�q���U�l
	{
		str = "�q����Ҥ�...                                      ";
		TextOut(hdc,10,470,str,strlen(str));
		ComTurn();                 
	}
	else
	{
		str = "�ӱz�U�F...                                        ";
		TextOut(hdc,10,470,str,strlen(str));
	}

	for(m=0;m<10;m++)
		for(n=0;n<10;n++)
		{
			if(board[m][n] == 0)			//�K�W���a�Ѥl
			{
				SelectObject(bufdc,chess[0]);
				BitBlt(mdc,m*45+3,n*45+3,38,38,bufdc,0,0,SRCCOPY);
			}
			else if(board[m][n] == 1)      //�K�W�q���Ѥl
			{
				SelectObject(bufdc,chess[1]);
				BitBlt(mdc,m*45+3,n*45+3,38,38,bufdc,0,0,SRCCOPY);
			}
			else							//�K�W�Ů�
			{
				SelectObject(bufdc,chess[1]);
				BitBlt(mdc,m*45+3,n*45+3,38,38,bufdc,0,0,WHITENESS);
			}
		}

	BitBlt(hdc,10,10,450,450,mdc,0,0,SRCCOPY);

	tPre = GetTickCount();
}

//****�T���B�z�禡***********************************
// 1.�]�w���U F1 �䭫�s�}�l�C��
// 2.�B�z���a���U�ƹ�����U�Ѥl���ʧ@
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int x,y,m,n,i;

	switch (message)
	{
		case WM_KEYDOWN:				  //���U����T��
			switch (wParam) 
			{
				case VK_ESCAPE:           //���U Esc ��
					PostQuitMessage( 0 );
					break;
				case VK_F1:				  //���U F1 ��
					InitGame();
					break;
			}
		case WM_LBUTTONDOWN:			  //���U�ƹ�����T��
			if(!over)
				if(turn)
				{
					x = LOWORD(lParam);		//���o�ƹ� X �y��
					y = HIWORD(lParam);		//���o�ƹ� Y �y��
					
					if(x > 10 && x < 460 && y> 10 && y < 460)
					{
						m = (int)floor((x-10)/45);
						n = (int)floor((y-10)/45);

						if(board[m][n] == 2)
						{
							board[m][n] = 0;   //�]�w�����a���Ѥl
							num[0]++;
							
							if(num[0] == 50 && num[1] == 50)
							{
								winner = 2;	   //����
								over = true;
							}
							else
								for(i=0;i<192;i++)
								{
									if(ptab[m][n][i])
									{
										win[0][i]++;
										ctab[m][n][i] = false;
										win[1][i] = 7;

										if(win[0][i] == 5)
										{
											winner = 0;
											over = true;
										}
									}
								}
							turn = false;       //���q���U
						}
					}
				}
				break;
		case WM_DESTROY:					//���������T��
			DeleteDC(mdc);
			DeleteDC(bufdc);
			DeleteObject(chess[0]);
			DeleteObject(chess[1]);

			ReleaseDC(hWnd,hdc);

			PostQuitMessage(0);
			break;
		default:							//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}