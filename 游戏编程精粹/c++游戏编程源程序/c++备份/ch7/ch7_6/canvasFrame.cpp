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

canvasFrame::canvasFrame()
{
	RECT rect;
	Create(NULL,"D3D��l�]�w");
	CClientDC dc(this);
	int width = dc.GetDeviceCaps(HORZRES);
	int height = dc.GetDeviceCaps(VERTRES);
	GetWindowRect( &rect );
	width = ( width - ( rect.right - rect.left ))/2 ;
	height = (height - (rect.bottom - rect.top ))/2 ;
	MoveWindow( width , height , (rect.right - rect.left ) , (rect.bottom - rect.top ) ,true);

}

canvasFrame::~canvasFrame()
{
}


BEGIN_MESSAGE_MAP(canvasFrame, CFrameWnd)
	//{{AFX_MSG_MAP(canvasFrame)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// canvasFrame message handlers
d3dTexture a_Bk ;
d3dTexture a_Role ;



LRESULT canvasFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch( message )
	{
	case WM_CREATE :
		if( !d3dCreate( m_hWnd , 640 , 480 , true ))
			return PostMessage( WM_CLOSE );
		a_Bk.Create( "�I��.tga" );
		a_Role.Create( "����.tga" );
		return 0 ;
	case WM_DESTROY :
		d3dRelease();
		return 0 ;
	}
	return CFrameWnd::WindowProc(message, wParam, lParam);
}

void canvasFrame::OnPaint() 
{
	// TODO: Add your message handler code here
	Render();
	// Do not call CFrameWnd::OnPaint() for painting messages
	CPaintDC dc(this); // device context for painting
}

void canvasFrame::Render()
{
	//�M��
	d3dClear();
	//�}�lø�s
	d3d_Device->BeginScene();
		d3d_Device->SetRenderState( D3DRS_CULLMODE , D3DCULL_NONE );
		d3d_Device->SetRenderState( D3DRS_ZENABLE , D3DZB_FALSE );
		d3d_Device->SetRenderState( D3DRS_SHADEMODE , D3DSHADE_FLAT );
		d3d_Device->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
		a_Bk.BltFast( 0 , 0 );
		//�}�V��
		d3d_Device->SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
		d3d_Device->SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );
		d3d_Device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		//�]�w��m�P�V��ާ@�ӷ�
		d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAARG1 , D3DTA_TEXTURE );
		d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAARG2 , D3DTA_DIFFUSE );
		d3d_Device->SetTextureStageState( 0 , D3DTSS_COLORARG1 , D3DTA_TEXTURE );
		d3d_Device->SetTextureStageState( 0 , D3DTSS_COLORARG2 , D3DTA_DIFFUSE );
		//���I�V��Ȥ@�߬�0.5( 128 )
		//�ӷ�ALPHA�Ȩ�̬ۭ��A�C��ΰ�x1
		d3d_Device->SetTextureStageState( 0 , D3DTSS_COLOROP , D3DTOP_SELECTARG1 );
		d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAOP , D3DTOP_MODULATE );
		a_Role.BltFast( 0 , 0 , 200 , 200 , D3DCOLOR_ARGB( 128 , 255 , 255 , 255 ) );
		//�ӷ�ALPHA�Ȱ�x1,�C��ΰ�x2
		d3d_Device->SetTextureStageState( 0 , D3DTSS_COLOROP , D3DTOP_SELECTARG2 );
		d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAOP , D3DTOP_SELECTARG1 );
		a_Role.BltFast( 200 , 0 , 400 , 200 , D3DCOLOR_ARGB( 128 , 255 , 255 , 255 ) );
		//�ӷ�ALPHA�Ȱ�x1,�C��ΰ�x�ۭ��A���I�]����
		d3d_Device->SetTextureStageState( 0 , D3DTSS_COLOROP , D3DTOP_MODULATE );
		d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAOP , D3DTOP_SELECTARG1 );
		a_Role.BltFast( 000 , 200 , 200 , 400 , D3DCOLOR_ARGB( 128 , 255 , 0 , 0 ) );
		//�ӷ�ALPHA�Ȱ�x�ۭ�,�C��ΰ�x�ۭ��A���I�]����
		d3d_Device->SetTextureStageState( 0 , D3DTSS_COLOROP , D3DTOP_MODULATE );
		d3d_Device->SetTextureStageState( 0 , D3DTSS_ALPHAOP , D3DTOP_MODULATE );
		a_Role.BltFast( 200 , 200 , 400 , 400 , D3DCOLOR_ARGB( 128 , 0 , 255 , 255) );

	d3d_Device->EndScene();
	//����
	d3d_Device->Present( NULL , NULL , NULL , NULL );

}
