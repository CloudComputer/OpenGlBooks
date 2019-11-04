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

//�ŧi DirectDraw �ܼ�
LPDIRECTDRAW7              DD;  
LPDIRECTDRAWSURFACE7       DDSur; 
LPDIRECTDRAWSURFACE7       DDBuf; 
LPDIRECTDRAWSURFACE7	   DDPla[20];
DDSCAPS2				   DDcaps;
DDSURFACEDESC2             DDde;
HRESULT					   result;
DDCOLORKEY                 key;

//�ŧi DirectSound �ܼ�
LPDIRECTSOUND			   DS;          
LPDIRECTSOUNDBUFFER        DSPri;  
LPDIRECTSOUNDBUFFER        DSBuf[3];  
WAVEFORMATEX			   DSfmt;         
WAVEFORMATEX			   wfmt;        
DSBUFFERDESC			   DSde;        
MMCKINFO				   ckRiff;       
MMCKINFO				   ckInfo;     
MMRESULT				   mmresult;    
HMMIO					   hmmio;              
DWORD					   wsize;                 
LPVOID					   pAudio;
DWORD					   bytesAudio;

//�ŧi DirectInput �ܼ�
LPDIRECTINPUT7			   DI;       
LPDIRECTINPUTDEVICE7	   DIms;
DIMOUSESTATE2			   DImstate;    

//�ŧi�䥦�ܼ�
HDC hdc,dhdc;
HBITMAP bitmap;
int a,i,j,t,num;
int x=1,y=190;
int bg[8][640][480];
int px[16];
int py[16];
BOOL collide,over,win;
char str[10];

canvasFrame::canvasFrame()
{
	Create(NULL,"ø�ϵ���",WS_POPUP); 
	hdc = ::CreateCompatibleDC(NULL);
	::ShowCursor(false);
	CreateDDPla(640,480,"load.bmp",19);
	DDBuf->BltFast( 0 , 0 , DDPla[19], CRect(0,0,640,480) , DDBLTFAST_WAIT);
	DDSur->Flip( NULL , DDFLIP_WAIT );
	for(i=0;i<=7;i++)              //���J�e���ϻP�I����
	{
		sprintf(str,"bgbmp%d.bmp",i);
		CreateDDPla(640,480,str,i);
		sprintf(str,"mbgbmp%d.bmp",i);
		CreateDDPla(640,480,str,i+8);
	}
	CreateDDPla(34,34,"ball.bmp",16);   //���J�p�y��
	CreateDDPla(638,180,"win.bmp",17);  //���J�L����
	CreateDDPla(638,180,"lose.bmp",18); //���J���ѹ�
	ColorKey(16);
	ColorKey(17);
	ColorKey(18);
	for(a=0;a<=7;a++)
	{
		DDPla[a+8]->GetDC( &hdc );
		for(i=0;i<640;i++)
			for(j=0;j<480;j++)
				bg[a][i][j] = ::GetPixel(hdc,i,j);
		DDPla[a+8]->ReleaseDC(hdc);
	}
	CreateDSBuf("s0.wav",0);  //���J�I������
	CreateDSBuf("s1.wav",1);  //���J�I������
	CreateDSBuf("s2.wav",2);  //���J�L������
	DSBuf[0]->Play(0,0,1);
}

canvasFrame::~canvasFrame()
{
	delete bitmap;
	delete hdc;
	delete dhdc;
	DD->Release();
	DDSur->Release();
	for(i=0;i<=19;i++)
		DDPla[i]->Release();
	DI->Release();
	DIms->Release();
	DS->Release();
	DSPri->Release();
	for(i=0;i<1;i++)
		DSBuf[i]->Release();
}


BEGIN_MESSAGE_MAP(canvasFrame, CFrameWnd)
	//{{AFX_MSG_MAP(canvasFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// canvasFrame message handlers

int canvasFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	InitDD();
	InitDS();
	InitDI();
	SetTimer(1,0,NULL);
	return 0;
}

void canvasFrame::CreateDDPla(int width,int height,char* filename,int num)
{
//�]�w����Ȧs�Ϥj�p
	DDde.dwWidth = width;
	DDde.dwHeight = height; 
//�إ߹���Ȧs��
	result = DD->CreateSurface(&DDde, &DDPla[num], NULL); 
	if(result !=DD_OK)
	{
  		MessageBox("�إ߹���Ȧs�ϥ���!");
		return;
	}
//���J�I�}��
	bitmap = (HBITMAP)::LoadImage(NULL,filename,IMAGE_BITMAP,width,height,LR_LOADFROMFILE); 
	if(bitmap==NULL)
	{
		MessageBox("�L�k���J�I�}��!");
		return;
	}
//�ƻs�I�}�Ϩ�ø�Ϥ�
	::SelectObject(hdc,bitmap);
	DDPla[num]->GetDC( &dhdc );
	::BitBlt( dhdc , 0 , 0 ,width,height, hdc , 0 , 0 , SRCCOPY );
	DDPla[num]->ReleaseDC(dhdc);
}

void canvasFrame::ColorKey(int num)
{
	key.dwColorSpaceHighValue = 0;
	key.dwColorSpaceLowValue = 0;
	DDPla[num]->SetColorKey(DDCKEY_SRCBLT,&key);
}


void canvasFrame::OnTimer(UINT nIDEvent) 
{
	if(!over)
		Playing();    //�C�����b�i�椤
	else
		Over();       //�L���εo�͸I��
	DDSur->Flip( NULL , DDFLIP_WAIT );
	CFrameWnd::OnTimer(nIDEvent);
}
void canvasFrame::Over()
{
	t++;
	if(t%10 == 0)
	{
		num++;
		if(num == 8)
			num =0;
		t=0;
	}
	DDBuf->BltFast( 0 , 0 , DDPla[num], CRect(0,0,640,480) , DDBLTFAST_WAIT);
	DDBuf->BltFast(x,y,DDPla[16],CRect(0,0,34,34),DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY);
	if(win)
		DDBuf->BltFast(0,150,DDPla[17],CRect(0,0,638,180),DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY);
	if(collide)
		DDBuf->BltFast(0,150,DDPla[18],CRect(0,0,638,180),DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY);
}

void canvasFrame::Playing()
{
	t++;
	if(t%5 == 0)
	{
		num++;
		if(num == 8)
			num = 0;
		t=0;
	}
	DDBuf->BltFast( 0 , 0 , DDPla[num], CRect(0,0,640,480) , DDBLTFAST_WAIT);
	result = DIms->GetDeviceState(sizeof(DImstate),(LPVOID)&DImstate); 
	if(result != DI_OK )
	{
		MessageBox("���o�ƹ����A����!");
		return;
	}
	x += DImstate.lX;     
	y += DImstate.lY;      
	if(x<=1)
		x=1;
	if(x>=605)
		x=605;
	if(y<=20)
		y=20;
	if(y>=430)
		y=430;
	px[0] = x+16;
	px[1] = x;
	px[2] = x+33;
	px[3] = x+16;
	px[4] = x+5;
	px[5] = x+28;
	px[6] = x+27;
	px[7] = x+5;
	px[8] = x+2;
	px[9] = x+9;
	px[10] = x+31;
	px[11] = x+23;
	px[12] = x+24;
	px[13] = x+30;
	px[14] = x+9;
	px[15] = x+1;
	py[0] = y+0;
	py[1] = y+16;
	py[2] = y+16;
	py[3] = y+33;
	py[4] = y+5;
	py[5] = y+5;
	py[6] = y+29;
	py[7] = y+28;
	py[8] = y+24;
	py[9] = y+31;
	py[10] = y+23;
	py[11] = y+31;
	py[12] = y+2;
	py[13] = y+8;
	py[14] = y+2;
	py[15] = y+10;
	DDBuf->BltFast(x,y,DDPla[16],CRect(0,0,34,34),DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY);
	for(i=0;i<=15;i++)
		if(bg[num][px[i]][py[i]] ==0)   //�o�͸I��
		{
			DDBuf->BltFast(0,150,DDPla[18],CRect(0,0,638,180),DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY);
			over = true;
			DSBuf[1]->Play(0,0,0);
			collide = true;
			break;
		}
	if(px[2] > 630)						//�L��
	{
		DDBuf->BltFast(0,150,DDPla[17],CRect(0,0,638,180),DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY);
		DSBuf[0]->Stop();
		win = true;
		over = true;
		DSBuf[2]->Play(0,0,1);
	}
}

void canvasFrame::CreateDSBuf(char* filename,int num)
{	
//�}�һP�ˬd�ɮ׮榡
	hmmio = mmioOpen(filename, NULL, MMIO_ALLOCBUF|MMIO_READ );
	if(hmmio == NULL)      
	{
		MessageBox("�ɮפ��s�b!");
		return;
	}
	ckRiff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmresult = mmioDescend(hmmio,&ckRiff,NULL,MMIO_FINDRIFF);
	if(mmresult != MMSYSERR_NOERROR)
	{
		MessageBox("�ɮ׮榡���~!");
		return;
	}
	ckInfo.ckid = mmioFOURCC('f','m','t',' '); 
	mmresult = mmioDescend(hmmio,&ckInfo,&ckRiff,MMIO_FINDCHUNK);
	if(mmresult != MMSYSERR_NOERROR)
	{
		MessageBox("�ɮ׮榡���~!");
		return;
	}
//Ū���ɮ׮榡
	mmresult = mmioRead(hmmio,(HPSTR)&wfmt,sizeof(wfmt));
	if(mmresult == -1)
	{
		MessageBox("Ū���榡����!");
		return;
	}
	mmresult = mmioAscend(hmmio,&ckInfo,0);     
	ckInfo.ckid = mmioFOURCC('d','a','t','a'); 
	mmresult = mmioDescend(hmmio,&ckInfo,&ckRiff,MMIO_FINDCHUNK);
	if(mmresult != MMSYSERR_NOERROR)
	{
		MessageBox("�ɮ׮榡���~!");
		return;
	}
	wsize = ckInfo.cksize; 
//�]�w���w�İϯS��
	memset( &DSde,0,sizeof(DSde));     
    DSde.dwSize  = sizeof(DSde);      
    DSde.dwFlags = 	 DSBCAPS_STATIC |DSBCAPS_CTRLPAN |DSBCAPS_CTRLVOLUME| DSBCAPS_GLOBALFOCUS;
    DSde.dwBufferBytes = wsize;         
    DSde.lpwfxFormat   = &wfmt;  
//�إߦ��w�İ�
    result = DS->CreateSoundBuffer( &DSde, &DSBuf[num], NULL );
	if(result != DS_OK)
	{
		MessageBox("�إߦ��w�İϥ���!");
		return;
	}
//��w���w�İϨø��J����
	result = DSBuf[num]->Lock(0,wsize,&pAudio,&bytesAudio,NULL,NULL,NULL);
	if(result != DS_OK)
	{
		MessageBox("��w�w�İϥ���!");
		return;
	}
	mmresult = mmioRead(hmmio,(HPSTR)pAudio,bytesAudio);
	if(mmresult == -1)
	{
		MessageBox("Ū�����ɸ�ƥ���!");
		return;
	}
	result = DSBuf[num]->Unlock(pAudio,bytesAudio,NULL,NULL);
	if(result != DS_OK)
	{
		MessageBox("�Ѱ���w�w�İϥ���!");
		return;
	}
	mmioClose(hmmio,0);
}

void canvasFrame::InitDD()
{
//�إ� DirectDraw ����
	result = DirectDrawCreateEx(NULL, (VOID**)&DD, IID_IDirectDraw7, NULL);
    if (result != DD_OK)
	{
		MessageBox("�إ�DirectDraw���󥢱�!");
		return;
	}
//�]�w��ռh��
	result = DD->SetCooperativeLevel(m_hWnd,DDSCL_EXCLUSIVE |
			         DDSCL_FULLSCREEN|DDSCL_ALLOWREBOOT );
	if(result !=DD_OK)
	{
		MessageBox("�]�w�{����ռh�ť���!");
		return;
	}
//�]�w��ܼҦ�
	result = DD->SetDisplayMode(640,480,16,0,DDSDM_STANDARDVGAMODE); 
	if(result !=DD_OK)
	{
		MessageBox("�]�w�ù���ܼҦ�����!");
		return;
	}
//�إߥDø�ϭ�
	memset(&DDde,0,sizeof(DDde));       
	DDde.dwSize = sizeof(DDde);           
	DDde.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	DDde.dwBackBufferCount = 1;        
	DDde.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP;
	result = DD->CreateSurface(&DDde,&DDSur,NULL);
	if(result !=DD_OK)
	{
	 	MessageBox("�إߥDø�ϭ�����!");
		return;
	}
//�s����w�İ�
	DDcaps.dwCaps = DDSCAPS_BACKBUFFER;  
	result = DDSur->GetAttachedSurface(&DDcaps,&DDBuf); 
	if(result !=DD_OK)
	{
		MessageBox("�s����w�İϥ���!");
		return;
	}
//�ŧi����Ȧs�Ϫ��@�P�S��
	memset(&DDde,0,sizeof(DDde));        
	DDde.dwSize = sizeof(DDde);
	DDde.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH; 
	DDde.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN ;
}

void canvasFrame::InitDS()
{
//�إ� DirectSound ����
    result = DirectSoundCreate( NULL, &DS, NULL ); 
	if(result != DS_OK)
	{
		MessageBox("�إ� DirectSound ���󥢱�!");
		return;
	}
//�]�w��ռh��
    result = DS->SetCooperativeLevel( m_hWnd, DSSCL_PRIORITY );
	if(result != DS_OK)
	{
		MessageBox("�]�w��ռh�ť���!");
		return;
	}
//�إߥD�w�İ�
    memset( &DSde,0, sizeof(DSde) );          
    DSde.dwSize        = sizeof(DSde);       
    DSde.dwFlags       = DSBCAPS_PRIMARYBUFFER;
    DSde.dwBufferBytes = 0;
    DSde.lpwfxFormat   = NULL;
    result = DS->CreateSoundBuffer( &DSde, &DSPri, NULL );
	if(result != DS_OK)
	{
		MessageBox("�إߥD�w�İϥ���!");
		return;
	}
//�]�w�n������榡
    memset( &DSfmt,0, sizeof(DSfmt) );
    DSfmt.wFormatTag      = WAVE_FORMAT_PCM;
    DSfmt.nChannels       = 2;               
    DSfmt.nSamplesPerSec  = 44100;           
    DSfmt.wBitsPerSample  = 16;          
    DSfmt.nBlockAlign     = DSfmt.wBitsPerSample / 8 * DSfmt.nChannels;
    DSfmt.nAvgBytesPerSec = DSfmt.nSamplesPerSec * DSfmt.nBlockAlign;
    result = DSPri->SetFormat(&DSfmt);     
	if(result != DS_OK)
	{
		MessageBox("�]�w����榡����!");
		return;
	}
}

void canvasFrame::InitDI()
{
//�إ� DirectInput ����
	HINSTANCE hinst = AfxGetInstanceHandle(); 
	result = DirectInputCreateEx(hinst, DIRECTINPUT_VERSION,IID_IDirectInput7, (void**)&DI, NULL); 
	if(result != DI_OK)
	{
		MessageBox("�إ� DirectInput ���󥢱�!");
		return;
	}
//�إ߿�J�˸m����
	result = DI->CreateDeviceEx(GUID_SysMouse, IID_IDirectInputDevice7,(void**)&DIms, NULL); 
	if(result != DI_OK)
	{
		MessageBox("�إ߷ƹ���J�˸m����!");
		return;
	}
//�]�w��Ʈ榡
	result = DIms->SetDataFormat(&c_dfDIMouse2);
	if(result != DI_OK)
	{
		MessageBox("�]�w��Ʈ榡����!");
		return;
	}
//�]�w��ռh��
	result = DIms->SetCooperativeLevel(m_hWnd,DISCL_BACKGROUND | DISCL_NONEXCLUSIVE); 
	if(result != DI_OK)
	{
		MessageBox("�]�w�{����ռh�ť���!");
		return;
	}
//���ο�J�˸m
	result = DIms->Acquire();
	if(result != DI_OK)
	{
		MessageBox("���ο�J�˸m����!");
		return;
	}
}


void canvasFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

	if( nChar== VK_ESCAPE )      //���U Esc ��
		PostMessage(WM_CLOSE );  //�����{��
	if( nChar == VK_F1)          //���U F1 ��
	{
		over = false;
		if(win)
		{
			win = false;
			DSBuf[2]->Stop();
			DSBuf[0]->Play(0,0,1);
		}
		else
			collide = false;
		x = 1;
		y = 190;
	}
	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
