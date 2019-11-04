// canvasFrame.cpp : implementation file
//

#include "stdafx.h"
#include "canvasr.h"
#include "canvasFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// canvasFrame
IMPLEMENT_DYNCREATE(canvasFrame, CFrameWnd)
int x=0,y=0,xlast,ylast,ox,oy;
float vx=21,vy=21;
float m,n;

canvasFrame::canvasFrame()
{
	Create(NULL,"ø�ϵ���");
	CClientDC dc(this);
	int width = dc.GetDeviceCaps(HORZRES);
	int height = dc.GetDeviceCaps(VERTRES);
	GetWindowRect( &rect );
	width = ( width - ( rect.right - rect.left ))/2 ;
	height = (height - (rect.bottom - rect.top ))/2 ;
	MoveWindow( width , height , (rect.right - rect.left ) , (rect.bottom - rect.top ) ,true);
	GetClientRect(&rect);
	mdc = new CDC;
	mdc->CreateCompatibleDC(&dc);
	ball = new CBitmap;
	ball->m_hObject = (HBITMAP)::LoadImage(NULL,"ball.bmp",IMAGE_BITMAP,39,39,LR_LOADFROMFILE); //���J�p�y��
	mdc->SelectObject(ball); //����I�}�Ϩ� mdc ��
}

canvasFrame::~canvasFrame()
{
	delete mdc;
	delete ball;
}


BEGIN_MESSAGE_MAP(canvasFrame, CFrameWnd)
	//{{AFX_MSG_MAP(canvasFrame)
	ON_WM_TIMER()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// canvasFrame message handlers

void canvasFrame::OnTimer(UINT nIDEvent)
{
	CFrameWnd::OnTimer(nIDEvent);
	CClientDC dc(this);
	dc.BitBlt(xlast,ylast,39,39,mdc,0,0,WHITENESS);
	dc.BitBlt(x,y,39,39,mdc,0,0,SRCCOPY);
	xlast = x;           //�W���K�� X �y��
	ylast = y;           //�W���K�� Y �y��
	x += (int)vx;
	y += (int)vy;
	ox = x+20;        //��� X �y��
	oy = y+20;        //��� Y �y��
	collide(rect.right,20,400,rect.bottom);	//�O�_�I�쥪��׭�
	collide(400,rect.bottom,0,200);     	//�O�_�I��k��׭�
	if(y < 0)             //�O�_�I��W�t
	{
		vy = -vy;
		y = 0;
	}
	if(x < 0)             //�O�_�I�쥪�t
	{
		vx = -vx;
		x = 0;
	}
	dc.MoveTo(rect.right,20);    //�e�u
	dc.LineTo(400,rect.bottom);
	dc.LineTo(0,200);
}

int canvasFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetTimer(1,50,NULL);
	return 0;
}

void canvasFrame::collide(int startX,int startY,int endX,int endY)
{
	float va,vb;        //�I����t��
	float lx,ly,fx,fy;
	lx = (float)endX-startX; //X �b�V�q
	ly = (float)endY-startY; //Y �b�V�q
	fx = (float)startY-endY; //X �b�k�V�q
	fy = (float)endX-startX; //Y �b�h�V�q
	m = (vx*(startY-oy)+vy*(ox-startX))/(lx*vy-ly*vx);
	n = (lx*(oy-startY)+ly*(startX-ox))/(vx*ly-vy*lx);
	if(m>=0 && m<=1 && n>=0 && n<=1)
	{
	    va = (float)(-2*(fx*vx+fy*vy)*fx/(pow(fx,2)+pow(fy,2))+vx);
        vb = (float)(-2*(fx*vx+fy*vy)*fy/(pow(fx,2)+pow(fy,2))+vy);
		vx = va;
		vy = vb;
	}
}

