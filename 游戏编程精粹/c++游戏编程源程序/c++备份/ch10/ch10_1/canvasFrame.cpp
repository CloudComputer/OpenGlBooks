// canvasFrame.cpp : implementation file
//
#define DIRECTINPUT_VERSION 0x0700
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

LPDIRECTINPUT7  pDI;        //�ŧi DirectInput �������
LPDIRECTINPUTDEVICE7  pDKB; //�ŧi��J�˸m�������
HRESULT         result;     //�ŧi HRESULT ���A�ܼ�
char buffer[256];           //�]�w�w�İ�
int x,y;                    //�ŧi�K�Ϯy��
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
	ball->m_hObject = (HBITMAP)::LoadImage(NULL,"ball.bmp",IMAGE_BITMAP,81,81,LR_LOADFROMFILE); //���J����
	mdc->SelectObject(ball);
	x = ((rect.right-rect.left) - 81)/2;    //�]�w�p�y�_�I X �y��
	y = ((rect.bottom-rect.top) - 81)/2;    //�]�w�p�y�_�I Y �y��
}

canvasFrame::~canvasFrame()
{
	delete ball;
	delete mdc;
	pDKB->Release();
	pDI->Release();
}


BEGIN_MESSAGE_MAP(canvasFrame, CFrameWnd)
	//{{AFX_MSG_MAP(canvasFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
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
	result = pDI->CreateDeviceEx(GUID_SysKeyboard, IID_IDirectInputDevice7,
        (void**)&pDKB, NULL); //�إ߿�J�˸m����
	if(result != DI_OK)
		MessageBox("�إ���L��J�˸m����!");
	result = pDKB->SetDataFormat(&c_dfDIKeyboard);
	if(result != DI_OK)
		MessageBox("�]�w��Ʈ榡����!");
	result = pDKB->SetCooperativeLevel(m_hWnd, 
                   DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);  //�]�w��ռh��
	if(result != DI_OK)
		MessageBox("�]�w�{����ռh�ť���!");
	result = pDKB->Acquire();   //���ο�J�˸m
	if(result != DI_OK)
		MessageBox("���ο�J�˸m����!");
	SetTimer(1,0,NULL);
	// TODO: Add your specialized creation code here
	return 0;
}

void canvasFrame::OnTimer(UINT nIDEvent) 
{
	CFrameWnd::OnTimer(nIDEvent);
	CClientDC dc(this);                   
	dc.BitBlt(x,y,81,81,mdc,0,0,SRCCOPY); 
    result = pDKB->GetDeviceState(sizeof(buffer),(LPVOID)&buffer);  //���o��L���A
    if(result != DI_OK)
		MessageBox("���o��L���A����!");
	if(buffer[DIK_RIGHT] & 0x80)    //�P�_�k��O�_�Q���U
		if(x+80 > rect.right)       //�P�_�O�_�I��k��t
			x = rect.right - 60;
		else
			x+=20;
	if(buffer[DIK_LEFT] & 0x80)     //�P�_����O�_�Q���U
		if(x-20 < -21)              //�P�_�O�_�I�쥪��t
			x = -21;
		else
			x-=20;
	if(buffer[DIK_UP] & 0x80)       //�P�_�W��O�_�Q���U
		if(y-20 < -21)              //�P�_�O�_�I��W��t
			y = -21;
		else
			y-=20;
	if(buffer[DIK_DOWN] & 0x80)     //�P�_�U��O�_�Q���U
		if(y+80 > rect.bottom)      //�P�_�O�_�I��U��t
			y = rect.bottom-60;
		else
			y+=20;
	if(buffer[DIK_ESCAPE] & 0x80)   //�P�_Esc��O�_�Q���U
	{
		KillTimer(1);               //�R���p�ɾ�
		PostMessage(WM_CLOSE);      //�����{��
	}
}
