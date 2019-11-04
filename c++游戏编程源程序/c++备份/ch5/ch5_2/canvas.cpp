
#include "stdafx.h"
#include <stdio.h>

//�w�q���c
struct chr
{
	int		nHp;
	int		fHp;
	int		lv;
	int		w;
	int		kind;
};

//�����ܼƫŧi
HINSTANCE hInst;
HBITMAP	bg,sheep,girl,skill,slash,magic,recover,game;
HDC		hdc,mdc,bufdc;
HWND	hWnd;
DWORD	tPre,tNow;
int		pNum,f,txtNum;
bool	attack,over;
chr		player,monster;
char	text[5][100];

//�禡�ŧi
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				MyPaint(HDC hdc);
void				MsgInsert(char*);
void				CheckDie(int hp,bool player);

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
// ��l���a�ΩǪ����U�����A
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

	bg = (HBITMAP)LoadImage(NULL,"bg.bmp",IMAGE_BITMAP,640,480,LR_LOADFROMFILE);
	sheep = (HBITMAP)LoadImage(NULL,"sheep.bmp",IMAGE_BITMAP,133,220,LR_LOADFROMFILE);
	girl = (HBITMAP)LoadImage(NULL,"girl.bmp",IMAGE_BITMAP,480,148,LR_LOADFROMFILE);
	skill = (HBITMAP)LoadImage(NULL,"skill.bmp",IMAGE_BITMAP,74,60,LR_LOADFROMFILE);
	slash = (HBITMAP)LoadImage(NULL,"slash.bmp",IMAGE_BITMAP,196,162,LR_LOADFROMFILE);
	magic = (HBITMAP)LoadImage(NULL,"magic.bmp",IMAGE_BITMAP,200,100,LR_LOADFROMFILE);
	recover = (HBITMAP)LoadImage(NULL,"recover.bmp",IMAGE_BITMAP,300,150,LR_LOADFROMFILE);
	game = (HBITMAP)LoadImage(NULL,"over.bmp",IMAGE_BITMAP,289,74,LR_LOADFROMFILE);

	player.nHp = player.fHp = 50;	//�]�w���a����ͩR�ȤΤW��
	player.lv = 2;					//�]�w���a���ⵥ��
	player.w  = 4;					//�]�w�����ˮ`�[�v��

	monster.nHp = monster.fHp = 100;	//�]�w�Ǫ�����ͩR�ȤΤW��
	monster.lv = 1;						//�]�w�Ǫ����ⵥ��
	monster.w = 1;						//�]�w�����ˮ`�[�v��

	txtNum = 0;		//��ܰT���ƥ�

	MyPaint(hdc);

	return TRUE;
}

//****�ۭqø�Ϩ禡*********************************
// 1.�e���K�ϻP��԰T�����
// 2.�Ǫ��欰�P�_�ΦU���ƭȳB�z�P�p��
void MyPaint(HDC hdc)
{
	char str[100];
	int i,damage;

	//�K�W�I����
	SelectObject(bufdc,bg);
	BitBlt(mdc,0,0,640,480,bufdc,0,0,SRCCOPY);

	//��ܹ�԰T��
	for(i=0;i<txtNum;i++)
		TextOut(mdc,0,360+i*18,text[i],strlen(text[i]));

	//�K�W�Ǫ���
	if(monster.nHp>0)
	{
		SelectObject(bufdc,sheep);
		BitBlt(mdc,70,180,133,110,bufdc,0,110,SRCAND);
		BitBlt(mdc,70,180,133,110,bufdc,0,0,SRCPAINT);
		sprintf(str,"%d / %d",monster.nHp,monster.fHp);
		TextOut(mdc,100,320,str,strlen(str));
	}

	//�K�W���a��
	if(player.nHp>0)
	{
		SelectObject(bufdc,girl);
		BitBlt(mdc,500,200,60,74,bufdc,pNum*60,74,SRCAND);
		BitBlt(mdc,500,200,60,74,bufdc,pNum*60,0,SRCPAINT);
		sprintf(str,"%d / %d",player.nHp,player.fHp);
		TextOut(mdc,510,320,str,strlen(str));
	}

	if(over)				//�K�W�C�������ϥ�
	{
		SelectObject(bufdc,game);
		BitBlt(mdc,200,200,289,37,bufdc,0,37,SRCAND);
		BitBlt(mdc,200,200,289,37,bufdc,0,0,SRCPAINT);
	}
	else if(!attack)		//�K�W�������O�ϥ�
	{
		SelectObject(bufdc,skill);
		BitBlt(mdc,500,350,74,30,bufdc,0,30,SRCAND);
		BitBlt(mdc,500,350,74,30,bufdc,0,0,SRCPAINT);
	}	
	else
	{
		f++;

		//��5~10�ӵe������ܪ��a�����ϥ�
		if(f>=5 && f<=10)
		{
			SelectObject(bufdc,slash);
			BitBlt(mdc,100,160,98,162,bufdc,98,0,SRCAND);
			BitBlt(mdc,100,160,98,162,bufdc,0,0,SRCPAINT);

			//��10�ӵe���ɭp��Ǫ����ˮ`�{�ץH�Υ[�J��ܰT��
			if(f == 10)
			{
				damage = rand()%10 + player.lv*player.w;
				monster.nHp -= (int)damage;
					
				sprintf(str,"���a����...���a��Ǫ��y���F %d ���ˮ`�C",damage);
				MsgInsert(str);

				CheckDie(monster.nHp,false);
			}
		}

		srand(tPre);

		//��15�ӵe���ɧP�_�Ǫ��i��󶵰ʧ@
		if(f == 15)
		{
			if(monster.nHp > 20)				//�ͩR�Ȥj��20
			{
				if(rand()%10 != 1)
					monster.kind = 0;
				else
					monster.kind = 1;
			}
			else								//�ͩR�Ȥp��20
			{
				switch(rand()%5)
				{
					case 0:						//���q����
						monster.kind = 0;
						break;
					case 1:						//�I������]�k
						monster.kind = 1;
						break;
					case 2:						//�Ϻɥ��O����
						monster.kind = 2;
						break;
					case 3:						//�ɦ�
						monster.kind = 3;
						break;
					case 4:						//�k�]
						monster.kind = 4;
						break;
				}
			}
		}

		//��26~30�ӵe������ܩǪ��欰�ϥ�
		if(f>=26  && f<=30)
		{
			switch(monster.kind)
			{
				case 0:							//���q����
					SelectObject(bufdc,slash);
					BitBlt(mdc,480,150,98,162,bufdc,98,0,SRCAND);
					BitBlt(mdc,480,150,98,162,bufdc,0,0,SRCPAINT);

					//��30�ӵe���ɭp�⪱�a���ˮ`�{�ץH�Υ[�J��ܰT��
					if(f == 30)
					{
						damage = rand()%10 + monster.lv*monster.w;
						player.nHp -= (int)damage;
						
						sprintf(str,"�Ǫ�����...�Ǫ��缾�a�y���F %d ���ˮ`�C",damage);
						MsgInsert(str);

						CheckDie(player.nHp,true);
					}
					break;
				case 1:							//�I������]�k
					SelectObject(bufdc,magic);
					BitBlt(mdc,480,190,100,100,bufdc,100,0,SRCAND);
					BitBlt(mdc,480,190,100,100,bufdc,0,0,SRCPAINT);

					//��30�ӵe���ɭp�⪱�a���ˮ`�{�ץH�Υ[�J��ܰT��
					if(f == 30)
					{
						damage = rand()%10 + 3*monster.w;
						player.nHp -= (int)damage;	
						
						sprintf(str,"�Ǫ��]�k����...�Ǫ��缾�a�y���F %d ���ˮ`�C",damage);
						MsgInsert(str);

						CheckDie(player.nHp,true);
					}
					break;
				case 2:							//�Ϻɥ��O����
					SelectObject(bufdc,slash);
					BitBlt(mdc,480,150,98,162,bufdc,98,0,SRCAND);
					BitBlt(mdc,480,150,98,162,bufdc,0,0,SRCPAINT);

					//��30�ӵe���ɭp�⪱�a���ˮ`�{�ץH�Υ[�J��ܰT��
					if(f == 30)
					{
						damage = rand()%10 + monster.lv*monster.w*5;
						player.nHp -= (int)damage;
						
						sprintf(str,"�Ǫ����O����...�Ǫ��缾�a�y���F %d ���ˮ`�C",damage);
						MsgInsert(str);

						CheckDie(player.nHp,true);
					}
					break;
				case 3:							//�ɦ�
					SelectObject(bufdc,recover);
					BitBlt(mdc,60,160,150,150,bufdc,150,0,SRCAND);
					BitBlt(mdc,60,160,150,150,bufdc,0,0,SRCPAINT);

					//��30�ӵe���ɩǪ��^�_�ͩR�ȥH�Υ[�J��ܰT��
					if(f == 30)
					{
						monster.nHp += 30;
						
						sprintf(str,"�Ǫ��]�k�ɦ�...�^�_�F 30 �ͩR�ȡC",damage);
						MsgInsert(str);
					}
					break;
				case 4:
					//��30�ӵe���ɧP�_�Ǫ��O�_�k�]���\
					if(f == 30)
					{
						if(rand()%3 == 1)	//�k�]���\���v��1/3
						{
							over = true;
							monster.nHp = 0;

							sprintf(str,"�Ǫ��k�]...�k�]���\�C");
							MsgInsert(str);
						}
						else
						{
							sprintf(str,"�Ǫ��k�]...�k�]���ѡC");
							MsgInsert(str);
						}
					}
					break;
			}
		}

		if(f == 30)			//�^�X����
		{
			attack = false;
			f = 0;
		}
	}

	BitBlt(hdc,0,0,640,480,mdc,0,0,SRCCOPY);

	tPre = GetTickCount();

	pNum++;
	if(pNum == 8)
		pNum = 0;
}

//****��԰T���s�W�禡*********************************
void MsgInsert(char* str)
{
	if(txtNum < 5)
	{
		sprintf(text[txtNum],str);
		txtNum++;
	}
	else
	{
		for(int i=0;i<txtNum;i++)
			sprintf(text[i],text[i+1]);

		sprintf(text[4],str);
	}
}

//****���a�Ǫ��ͩR�ȧP�_�禡*************************
void CheckDie(int hp,bool player)
{
	char str[100];

	if(hp <= 0)
	{
		over = true;
		if(player)
		{
			sprintf(str,"�A�Q�Ǫ����ѤF...");
			MsgInsert(str);
		}
		else
		{
			sprintf(str,"�Ǫ����...");
			MsgInsert(str);
		}
	}
}

//****�T���B�z�禡***********************************
// �P�_���a�O�_�U�F�������O
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int x,y;

	switch (message)
	{
		case WM_KEYDOWN:				//������U�T��
			if(wParam==VK_ESCAPE)		//���U Esc ��
				PostQuitMessage(0);
			break;
		case WM_LBUTTONDOWN:			//���U�ƹ�����T��
			if(!attack)
			{
				x = LOWORD(lParam);		//���o�ƹ� X �y��
				y = HIWORD(lParam);		//���o�ƹ� Y �y��
			
				if(x >= 500 && x <= 574 && y >= 350 && y <= 380)
					attack = true;
			}
			break;
		case WM_DESTROY:				//���������T��
			DeleteDC(mdc);
			DeleteDC(bufdc);
			DeleteObject(bg);
			DeleteObject(sheep);
			DeleteObject(girl);
			DeleteObject(skill);
			DeleteObject(slash);
			DeleteObject(magic);
			DeleteObject(recover);
			DeleteObject(game);

			ReleaseDC(hWnd,hdc);

			PostQuitMessage(0);
			break;
		default:						//�䥦�T��
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

