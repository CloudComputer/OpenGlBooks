// canvasFrame.cpp : implementation file
//
#define DIRECTINPUT_VERSION 0x0700
#include "stdafx.h"
#include "canvasr.h"
#include "canvasFrame.h"
#include "dinput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct bullet          
{
   int   x;           
   int   y;
   BOOL exist;
};

/////////////////////////////////////////////////////////////////////////////
// canvasFrame

IMPLEMENT_DYNCREATE(canvasFrame, CFrameWnd)

LPDIRECTINPUT7  pDI;        //�ŧi DirectInput �������
LPDIRECTINPUTDEVICE7  pDMO; //�ŧi��J�˸m�������
HRESULT result;             //�ŧi HRESULT ���A�ܼ�
DIMOUSESTATE2 MState;       //�ƹ����A���c  
int x,y,xlast,ylast;
bullet b[200];
int bcount=0;
int i;

canvasFrame::canvasFrame()
{
	int cx,cy;
	Create(NULL,"ø�ϵ���");
	CClientDC dc(this);
	int width = dc.GetDeviceCaps(HORZRES);
	int height = dc.GetDeviceCaps(VERTRES);
	GetWindowRect( &rect );
	width = ( width - ( rect.right - rect.left ))/2 ;
	height = (height - (rect.bottom - rect.top ))/2 ;
	MoveWindow( width , height , (rect.right - rect.left ) , (rect.bottom - rect.top ) ,true);
	GetClientRect(&rect);
	ClientToScreen(&rect);    //�ഫ�y��
	::ClipCursor(&rect);      //�]�w�ƹ����ʽd��
	mdc = new CDC;
	mdc1 = new CDC;
	mdc->CreateCompatibleDC(&dc);
	mdc1->CreateCompatibleDC(&dc);
	bitmap = new CBitmap;
	bitmap->m_hObject = (HBITMAP)::LoadImage(NULL,"ship.bmp",IMAGE_BITMAP,100,74,LR_LOADFROMFILE); //���J����
	mdc->SelectObject(bitmap);
	bitmap->m_hObject = (HBITMAP)::LoadImage(NULL,"bullet1.bmp",IMAGE_BITMAP,32,15,LR_LOADFROMFILE); //���J����
	mdc1->SelectObject(bitmap);
	x = ((rect.right-rect.left) - 100)/2;    
	y = ((rect.bottom-rect.top) - 100)/2;   
	cx = x + 81/2;
	cy = y + 81/2;
	CPoint *p = new CPoint(cx,cy);
	ClientToScreen(p);               //�ഫ�y��
	::ShowCursor(false);             //�����ƹ����
	::SetCursorPos(p->x,p->y);       //�]�w�ƹ���m
	ScreenToClient(&rect);           //�ഫ�y��
	delete p;
}

canvasFrame::~canvasFrame()
{
	delete bitmap;
	delete mdc;
	delete mdc1;
	pDMO->Release();
	pDI->Release();
	::ClipCursor(NULL);
}

BEGIN_MESSAGE_MAP(canvasFrame, CFrameWnd)
	//{{AFX_MSG_MAP(canvasFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// canvasFrame message handlers

int canvasFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	HINSTANCE hinst = AfxGetInstanceHandle();  //���o���ε{���� handle
	result = DirectInputCreateEx(hinst, DIRECTINPUT_VERSION, 
        IID_IDirectInput7, (void**)&pDI, NULL); //�إ� DirectInput ����
	if(result != DI_OK)
		MessageBox("�إ� DirectInput ���󥢱�!");
	result = pDI->CreateDeviceEx(GUID_SysMouse, IID_IDirectInputDevice7,
        (void**)&pDMO, NULL); //�إ߿�J�˸m����
	if(result != DI_OK)
		MessageBox("�إ߷ƹ���J�˸m����!");
	result = pDMO->SetDataFormat(&c_dfDIMouse2);
	if(result != DI_OK)
		MessageBox("�]�w��Ʈ榡����!");
	result = pDMO->SetCooperativeLevel(m_hWnd, 
                   DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);  //�]�w��ռh��
	if(result != DI_OK)
		MessageBox("�]�w�{����ռh�ť���!");
	result = pDMO->Acquire();   //���ο�J�˸m
	if(result != DI_OK)
		MessageBox("���ο�J�˸m����!");
	SetTimer(500,1,NULL);
	// TODO: Add your specialized creation code here
	return 0;
}

void canvasFrame::OnTimer(UINT nIDEvent)
{
	CFrameWnd::OnTimer(nIDEvent);
	CClientDC dc(this);    
	result = pDMO->GetDeviceState(sizeof(MState),(LPVOID)&MState); //���o�ƹ����A
	if(result != DI_OK )
		MessageBox("���o�ƹ����A����!");
	x += MState.lX;      //�]�w�����ϥܪ� x �y��
	y += MState.lY;      //�]�w�����ϥܪ� y �y��
	if(x<rect.left)      //�O�_�w�ܥ����
		x = rect.left;
	if(x>rect.right-100) //�O�_�w�ܥk���
		x = rect.right-100;
	if(y<rect.top)       //�O�_�w�ܤW���
		y = rect.top;
	if(y>rect.bottom-74) //�O�_�w�ܤU���
		y = rect.bottom-74;
	dc.BitBlt(xlast,ylast,100,74,mdc,0,0,WHITENESS); //�л\�W�����K��
	xlast = x;
	ylast = y;
	if(MState.rgbButtons[0] & 0x80)  //�P�_�O�_���U�ƹ�����
	{
		for(i=0;i<200;i++)
		{
			if(b[i].exist == false)  //�[�J�@���s�l�u
			{
				b[i].x = x;
				b[i].y = y+30;
				b[i].exist = true;
				bcount++;
				break;
			}
		}
	}
	if(bcount != 0)
		for(i=0;i<200;i++)          //�K�W�Ҧ��l�u
		{
			dc.BitBlt(b[i].x,b[i].y,32,15,mdc1,0,0,SRCCOPY);
			b[i].x -=17;
			if(b[i].x<-30)
			{
				b[i].exist = false;
				bcount--;
			}
		}
	dc.BitBlt(x,y,100,74,mdc,0,0,SRCCOPY); //�K�W����
}

void canvasFrame::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
	if( nChar== VK_ESCAPE )      //�P�_�O�_���U Esc ��
		PostMessage(WM_CLOSE );  //�ǰeWM_CLOSE�T��
}
