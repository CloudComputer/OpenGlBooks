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
struct bullet       //�ŧi�l�u���c
{
   int  x;          //X�y��
   int  y;          //Y�y��
   BOOL exist;      //�O�_�s�b
};           
/////////////////////////////////////////////////////////////////////////////
// canvasFrame

IMPLEMENT_DYNCREATE(canvasFrame, CFrameWnd)
LPDIRECTINPUT7       pDI;  //�ŧi DirectInput �������
LPDIRECTINPUTDEVICE7 pDJS; //�ŧi��J�˸m�������
HRESULT result;            //�ŧi HRESULT ���A�ܼ�
DIDEVCAPS JSCap;           //�ŧi�n��S�ʵ��c
DIJOYSTATE  JState;        //�ŧi�n�쪬�A���c 
int x,y,xlast,ylast;
bullet b[200];             //�ŧi�l�u�}�C
int bcount=0;              //�l�u��
int i;
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
	ClientToScreen(&rect);    //�ഫ�y��
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
	::ShowCursor(false);        //�����ƹ����
	ScreenToClient(&rect);		//�ഫ�y��
}

canvasFrame::~canvasFrame()
{
	delete bitmap;
	delete mdc;
	delete mdc1;
	pDJS->Release();
	pDI->Release();
}


BEGIN_MESSAGE_MAP(canvasFrame, CFrameWnd)
	//{{AFX_MSG_MAP(canvasFrame)
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// canvasFrame message handlers
BOOL CALLBACK Joysticks(LPCDIDEVICEINSTANCE lpddi,LPVOID pvRef)
{
    result = pDI->CreateDeviceEx( lpddi->guidInstance,IID_IDirectInputDevice7,
		                        (VOID**)&pDJS, NULL );
	if(result != DI_OK)
		return DIENUM_CONTINUE;
	else
		return DIENUM_STOP;
}

BOOL CALLBACK Objects(LPCDIDEVICEOBJECTINSTANCE lpddoi,LPVOID pvRef)
{
    DIPROPRANGE dr; 
    dr.diph.dwSize       = sizeof(DIPROPRANGE);
    dr.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dr.diph.dwHow        = DIPH_BYOFFSET;
    dr.diph.dwObj        = lpddoi->dwOfs; //���o�b������
    switch( lpddoi->dwOfs )
    {
        case DIJOFS_X:
                dr.lMin              = -100; 
				dr.lMax              = 100; 
				result = pDJS->SetProperty(DIPROP_RANGE,&dr.diph);
			    if(result != DI_OK)
       				MessageBox(NULL,"�]�w�b�d�򥢱�!","���~�T��",MB_OK);
	            break;
        case DIJOFS_Y:
                dr.lMin              = -50; 
				dr.lMax              = 50; 
				result = pDJS->SetProperty(DIPROP_RANGE,&dr.diph);
			    if(result != DI_OK)
       				MessageBox(NULL,"�]�w�b�d�򥢱�!","���~�T��",MB_OK);
	            break;
        case DIJOFS_Z:
	            //�]�w z ��V�b�d�򪺵{���X(��)
	            break;
        case DIJOFS_RX:
     			//�]�w x ����b�d�򪺵{���X(��)
                break;
        case DIJOFS_RY:
     			//�]�w y ����b�d�򪺵{���X(��)
                break;
        case DIJOFS_RZ:
     			//�]�w z ����b�d�򪺵{���X(��)
                break;
        case DIJOFS_SLIDER(0):
                //�]�w�ƶb 1 �d�򪺵{���X(��)
			    break;
        case DIJOFS_SLIDER(1):
                //�]�w�ƶb 2 �d�򪺵{���X(��)
				break;
    }
    return DIENUM_CONTINUE;
}
int canvasFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	HINSTANCE hinst = AfxGetInstanceHandle();
    result = DirectInputCreateEx(hinst, DIRECTINPUT_VERSION,IID_IDirectInput7, (LPVOID*)&pDI, NULL );
	if(result != DI_OK)
		MessageBox("�إ� DirectInput ���󥢱�!");
	result = pDI->EnumDevices(DIDEVTYPE_JOYSTICK, Joysticks,
                             NULL, DIEDFL_ATTACHEDONLY ); //�C�|�n��˸m
	if(result != DI_OK)
		MessageBox("�C�|�n�쥢��!");
	if(pDJS == NULL) //�P�_�O�_���n��
		MessageBox("�L�i�ϥΪ��n��˸m!");
    result = pDJS->SetDataFormat(&c_dfDIJoystick);
	if(result != DI_OK)
		MessageBox("�]�w��Ʈ榡����!");
    result = pDJS->SetCooperativeLevel(m_hWnd, DISCL_EXCLUSIVE|DISCL_BACKGROUND );
	if(result != DI_OK)
		MessageBox("�]�w��ռh�ť���!");
	JSCap.dwSize = sizeof(JSCap);
    result = pDJS->GetCapabilities(&JSCap);
	if(result != DI_OK)
		MessageBox("���o�n��S�ʥ���!");
    result = pDJS->EnumObjects(Objects, (VOID*)m_hWnd,DIDFT_AXIS);
	if(result != DI_OK)
		MessageBox("�C�|�n�줸�󥢱�!");
	result = pDJS->Acquire();
	if(result != DI_OK)
		MessageBox("���o�n��˸m����!");
	SetTimer(1,1,NULL);
	return 0;
}

void canvasFrame::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
	if( nChar== VK_ESCAPE )      //�P�_�O�_���U Esc ��
		PostMessage(WM_CLOSE );  //�ǰeWM_CLOSE�T��
	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
}

void canvasFrame::OnTimer(UINT nIDEvent) 
{
	CFrameWnd::OnTimer(nIDEvent);
	CClientDC dc(this);
	result = pDJS->Poll();   //�����n��
	if(result != DI_OK && result != DI_NOEFFECT)
		MessageBox("�����n�쥢��!");
    result = pDJS->GetDeviceState( sizeof(JState), &JState );
    if (result != DI_OK) 
		MessageBox("���o�n�쪬�A����!");   
	x += JState.lX;      //�]�w�����ϥܪ� X �y��
	y += JState.lY;      //�]�w�����ϥܪ� Y �y��
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
	if(JState.rgbButtons[0] & 0x80)  //�P�_�O�_���U�o�g�l�u�s
	{
		for(i=0;i<200;i++)
		{
			if(b[i].exist == false)
			{
				b[i].x = x;
				b[i].y = y+30;
				b[i].exist = true;
				bcount++;
				break;
			}
		}
	}
	if(JState.rgbButtons[1] & 0x80) //�O�_���U�����s
		PostMessage(WM_CLOSE );  //�ǰeWM_CLOSE�T��
	if(bcount != 0)
		for(i=0;i<200;i++)
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

	

