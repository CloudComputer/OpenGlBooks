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

LPDIRECTDRAW7              pDD7;  //�ŧiDirectDraw����
LPDIRECTDRAWSURFACE7       pPSur; //�ŧi�Dø�ϭ�
LPDIRECTDRAWSURFACE7       pBBuf; //�ŧi��w�İ�
LPDIRECTDRAWSURFACE7	   pOPla[8];
DDSCAPS2  caps;                   //�ŧiDDSCAPS���c
DDSURFACEDESC2             desc;  //�ŧi�y�z���c
HRESULT result;                   //�ŧiHRESULT���A�ܼ�
DDCOLORKEY key;					  //�ŧi�C����
int i;
LPDIRECTSOUND pDS;          //�ŧi DirectSound �������
LPDIRECTSOUNDBUFFER pPBuf;  //�ŧi�D�w�İϫ���
LPDIRECTSOUNDBUFFER pSBuf[2];  //�ŧi���w�İ�
WAVEFORMATEX pwfmt;         //�ŧi�n�����c
WAVEFORMATEX swfmt;         //�ŧi�n�����c
DSBUFFERDESC dsdesc;          //�ŧi�y�z���c
MMCKINFO      ckRiff;       //RIFF �϶�����T  
MMCKINFO      ckInfo;       //�l�϶�����T
MMRESULT	  mmresult;     //�Ǧ^���G
HMMIO hmmio;                //�}�Ҫ��h�C���ɮ�
DWORD size;                 //��ڸ�Ƥj�p
LPVOID pAudio;
DWORD bytesAudio;
canvasFrame::canvasFrame()
{
	hdc = ::CreateCompatibleDC(NULL);
	Create(NULL,"ø�ϵ���",WS_POPUP);
	pSBuf[0] = createbuffer("bground.wav"); //���J�I������
	pSBuf[1] = createbuffer("foot.wav"); //���J�}�B�n
	pSBuf[0]->Play(0,0,1); //����I������
}

void canvasFrame::ColorKey(int i)
{
	key.dwColorSpaceHighValue = 0x001f;
	key.dwColorSpaceLowValue = 0x001f;
	pOPla[i]->SetColorKey(DDCKEY_SRCBLT,&key);
	return;
}
canvasFrame::~canvasFrame()
{
	delete hdc;
	delete hdc1;
	delete bitmap;
	pDD7->Release();
	pPSur->Release();
	for(i=0;i<8;i++)
		pOPla[i]->Release();
	pDS->Release();
	pPBuf->Release();
	for(i=0;i<1;i++)
		pSBuf[i]->Release();
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

int canvasFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
    result = DirectDrawCreateEx(NULL, (VOID**)&pDD7, IID_IDirectDraw7, NULL);
	//�إ�DirectDraw����
    if (result != DD_OK)
		MessageBox("�إ�DirectDraw���󥢱�!");
	result = pDD7->SetCooperativeLevel(m_hWnd,DDSCL_EXCLUSIVE |
			         DDSCL_FULLSCREEN|DDSCL_ALLOWREBOOT );
	//�]�w��ռh��
	if(result !=DD_OK)
		MessageBox("�]�w�{����ռh�ť���!");
	result = pDD7->SetDisplayMode(640,480,16,0,DDSDM_STANDARDVGAMODE);  //�]�w�ù���ܼҦ�
	//�]�w��ܼҦ�
	if(result !=DD_OK)
		MessageBox("�]�w�ù���ܼҦ�����!");
	memset(&desc,0,sizeof(desc));       
	desc.dwSize = sizeof(desc);           
	desc.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	desc.dwBackBufferCount = 1;        
	desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP;
	result = pDD7->CreateSurface(&desc,&pPSur,NULL);
	//�إߥDø�ϭ�
	if(result !=DD_OK)
	 	MessageBox("�إߥDø�ϭ�����!");
	caps.dwCaps = DDSCAPS_BACKBUFFER;  
	result = pPSur->GetAttachedSurface(&caps,&pBBuf); 
	//�s����w�İ�
	if(result !=DD_OK)
		MessageBox("�s����w�İϥ���!");
	memset(&desc,0,sizeof(desc));        
	desc.dwSize = sizeof(desc);
	desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH; 
	desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN ;
	desc.dwWidth = 640; 
	desc.dwHeight = 480; 
	char file[10];
	char num[5];
	for(i=0;i<=7;i++)
	{
		result = pDD7->CreateSurface(&desc, &pOPla[i], NULL); 
		//�إ߹���Ȧs��
		if(result !=DD_OK)
  			MessageBox("�إ߹���Ȧs�ϥ���!");
		ColorKey(i);  //�]�w�C����
		sprintf( file , "b%d.bmp" , i ); //���o�����ɦW�r��
		bitmap = (HBITMAP)::LoadImage(NULL,file,IMAGE_BITMAP,640,480,LR_LOADFROMFILE); 
		if(bitmap==NULL)
			MessageBox("�L�k���J�I�}��!");
		::SelectObject(hdc,bitmap);       //�]�whdc�����I�}�Ϭ�bitmap
		pOPla[i]->GetDC( &hdc1 );            //���o����Ȧs�Ϫ�DC
		::BitBlt( hdc1 , 0 , 0 , 640 , 480 , hdc , 0 , 0 , SRCCOPY );
   		sprintf( num , "�� %d �i��" , i );  //�]�w�T���r��
		::TextOut(hdc1, 0, 0, num, lstrlen(num));  //ø�s�T���r��
		pOPla[i]->ReleaseDC( hdc1 );      //����DC
	}
	SetTimer(1,300,NULL);  //�]�w�p�ɾ�
	i=0;                   //���] i ��
    result = DirectSoundCreate( NULL, &pDS, NULL ); //�إ� DirectSound ����
	if(result != DS_OK)
		MessageBox("�إ� DirectSound ���󥢱�!");
    result = pDS->SetCooperativeLevel( m_hWnd, DSSCL_PRIORITY );
	if(result != DS_OK)
		MessageBox("�]�w��ռh�ť���!");
    memset( &dsdesc,0, sizeof(dsdesc) );          //�M�ŵ��c���e
    dsdesc.dwSize        = sizeof(dsdesc);        //�t�m�y�z���c�j�p
    dsdesc.dwFlags       = DSBCAPS_PRIMARYBUFFER;
    dsdesc.dwBufferBytes = 0;
    dsdesc.lpwfxFormat   = NULL;
    result = pDS->CreateSoundBuffer( &dsdesc, &pPBuf, NULL );
	if(result != DS_OK)
		MessageBox("�إߥD�w�İϥ���!");
    memset( &pwfmt,0, sizeof(pwfmt) );
    pwfmt.wFormatTag      = WAVE_FORMAT_PCM;
    pwfmt.nChannels       = 2;               //�����n�D
    pwfmt.nSamplesPerSec  = 44100;           //�����W�v
    pwfmt.wBitsPerSample  = 16;              //�줸
    pwfmt.nBlockAlign     = pwfmt.wBitsPerSample / 8 * pwfmt.nChannels;
    pwfmt.nAvgBytesPerSec = pwfmt.nSamplesPerSec * pwfmt.nBlockAlign;
    result = pPBuf->SetFormat(&pwfmt);       //�]�w����榡
	if(result != DS_OK)
		MessageBox("�]�w����榡����!");
	return 0;
}

void canvasFrame::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
	if( nChar== VK_ESCAPE )      //�P�_�O�_���U Esc ��
		PostMessage(WM_CLOSE );  //�ǰeWM_CLOSE�T��
}

void canvasFrame::OnTimer(UINT nIDEvent) 
{
	CFrameWnd::OnTimer(nIDEvent);
	if(i==7)
		i=0;
	if(i==1 || i==4)  //�P�_�ϸ�
		pSBuf[1]->Play(0,0,0);  //����}�B�n
	pBBuf->BltFast( 0 , 0 , pOPla[7], CRect(0,0,640,480) , DDBLTFAST_WAIT);  //�K�W�I����
	pBBuf->BltFast( 0 , 0 , pOPla[i], CRect(0,0,640,480) , DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY );
	//�K�W�H����
	pPSur->Flip( NULL , DDFLIP_WAIT ); //½��
	i++;
}

LPDIRECTSOUNDBUFFER canvasFrame::createbuffer(char* filename)
{	
	LPDIRECTSOUNDBUFFER buf;
	hmmio = mmioOpen(filename, NULL, MMIO_ALLOCBUF|MMIO_READ );
	//�}���ɮ�
	if(hmmio == NULL)                           //�P�_�O�_����
		MessageBox("�ɮפ��s�b!");
	ckRiff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	//�]�w�ɮ�����
	mmresult = mmioDescend(hmmio,&ckRiff,NULL,MMIO_FINDRIFF);
	//�j�M���A
	if(mmresult != MMSYSERR_NOERROR)
		MessageBox("�ɮ׮榡���~!");
	ckInfo.ckid = mmioFOURCC('f','m','t',' ');  //�]�w�϶�����
	mmresult = mmioDescend(hmmio,&ckInfo,&ckRiff,MMIO_FINDCHUNK);
	//�j�M�϶�
	if(mmresult != MMSYSERR_NOERROR)
		MessageBox("�ɮ׮榡���~!");
	if(mmioRead(hmmio,(HPSTR)&swfmt,sizeof(swfmt)) == -1) //Ū���ɮ׮榡
		MessageBox("Ū���榡����!");
	mmresult = mmioAscend(hmmio,&ckInfo,0);     //���X�l�϶�
	ckInfo.ckid = mmioFOURCC('d','a','t','a');  //�]�w�϶�����
	mmresult = mmioDescend(hmmio,&ckInfo,&ckRiff,MMIO_FINDCHUNK);
	//�j�M�϶�
	if(mmresult != MMSYSERR_NOERROR)
		MessageBox("�ɮ׮榡���~!");
	size = ckInfo.cksize;                       //���o��ڸ�Ƥj�p
	memset( &dsdesc,0,sizeof(dsdesc));        //�M�ŵ��c���e
    dsdesc.dwSize  = sizeof(dsdesc);          //�t�m���c�j�p
    dsdesc.dwFlags = 	 DSBCAPS_STATIC |DSBCAPS_CTRLPAN |DSBCAPS_CTRLVOLUME| DSBCAPS_GLOBALFOCUS;
    dsdesc.dwBufferBytes = size;            //�]�w�w�İϤj�p
    dsdesc.lpwfxFormat   = &swfmt;          //�]�w�w�İϮ榡
    result = pDS->CreateSoundBuffer( &dsdesc, &buf, NULL );
	if(result != DS_OK)
		MessageBox("�إߦ��w�İϥ���!");

	result = buf->Lock(0,size,&pAudio,&bytesAudio,NULL,NULL,NULL);
	//��w�w�İ�
	if(result != DS_OK)
		MessageBox("��w�w�İϥ���!");
	mmresult = mmioRead(hmmio,(HPSTR)pAudio,bytesAudio);
	//Ū�����ɸ��
	if(mmresult == -1)
		MessageBox("Ū�����ɸ�ƥ���!");
	result = buf->Unlock(pAudio,bytesAudio,NULL,NULL);
	//�Ѱ���w�w�İ�
	if(result != DS_OK)
		MessageBox("�Ѱ���w�w�İϥ���!");
	mmioClose(hmmio,0);
	return buf;
}

