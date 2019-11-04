/*////////////////////////////////////////////////






  Direct Graphice





/*////////////////////////////////////////////////
#include "windows.h"
#include "myd3d.h"

/*//////////////////////////////////////////////

  �t��

/*//////////////////////////////////////////////

LPDIRECT3D9			d3d_3D ;
LPDIRECT3DDEVICE9	d3d_Device ;

/*//////////////////////////////////////////////

  ��l��

/*//////////////////////////////////////////////
void d3dInit()
{
	d3d_3D = NULL ;
	d3d_Device = NULL ;
}

/*//////////////////////////////////////////////

  ����

/*//////////////////////////////////////////////
void d3dRelease()
{
	if( d3d_3D ) d3d_3D->Release();
	if( d3d_Device ) d3d_Device->Release();
}

/*//////////////////////////////////////////////

  �إ�
  1.�վ�ù��l�ΰϤj�p
  2.�إ�D3d �� Device 
  3.ø�ϭ��M��

/*//////////////////////////////////////////////
BOOL d3dCreate( HWND hWnd , int width , int height , BOOL IsWindow )
{
	//�վ�ù��l�ΰϤj�p
	if( !d3dSetDisplaySize( hWnd , width , height ))
		return false ;
	//�إ�D3D �˸m
	if( !d3dDeviceCreate( hWnd , IsWindow ))
		return false ;
	//ø�ϭ��M��
	d3dClear();
	//����
	return true ;
}


/*//////////////////////////////////////////////

  �վ�ù��j�p

/*//////////////////////////////////////////////
BOOL d3dSetDisplaySize( HWND hWnd , int width , int height )
{
	//�վ�ù��j�p
	RECT rect ;
	HDC hdc ;
	//���o�l�ΰϦ�m
	hdc = GetDC( hWnd );
	rect.left = (GetDeviceCaps( hdc , HORZRES ) - width )/2;
	rect.top = (GetDeviceCaps( hdc , VERTRES ) - height )/2;
	ReleaseDC( hWnd , hdc );
	rect.right = rect.left + width ;
	rect.bottom = rect.top + height ;
	//�վ�l�ΰ�
	AdjustWindowRectEx( &rect , GetWindowLong( hWnd , GWL_STYLE ) , (GetMenu( hWnd)!=NULL) , 
		GetWindowLong( hWnd , GWL_EXSTYLE) );
	//���ʩl�ΰ�
	MoveWindow( hWnd , rect.left , rect.top , rect.right - rect.left , rect.bottom - rect.top , true );
	return true ;
}
/*//////////////////////////////////////////////

  �إ�D3d �� Device 

/*//////////////////////////////////////////////
BOOL d3dDeviceCreate( HWND hWnd , BOOL IsWindow  )
{
	//�إ�d3d�D�n�˸m
	d3d_3D =  Direct3DCreate9( D3D_SDK_VERSION );
	if( !d3d_3D )
		return false ;
	//���o�ثe�ୱ��ܼҦ�
	D3DDISPLAYMODE d3ddm ;
	if( d3d_3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT , &d3ddm ) != D3D_OK )
		return false ;
	//�إ�ø�ϸ˸m
	D3DPRESENT_PARAMETERS d3dpp ;
	memset( &d3dpp , 0 , sizeof( d3dpp ));
	d3dpp.Windowed = IsWindow ;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD ;
	d3dpp.BackBufferFormat = d3ddm.Format ;
	d3dpp.hDeviceWindow = hWnd ;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER ;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.EnableAutoDepthStencil = TRUE;

	if( d3d_3D->CreateDevice( D3DADAPTER_DEFAULT , 
		D3DDEVTYPE_HAL , hWnd , D3DCREATE_SOFTWARE_VERTEXPROCESSING , 
		&d3dpp , &d3d_Device ) != D3D_OK )
		return false ;
	return true ;
}
/*//////////////////////////////////////////////

  ø�ϭ��M��

/*//////////////////////////////////////////////
void d3dClear( UINT color )
{
	d3d_Device->Clear( 0 , 0 , D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER , color , 1.0f , 0 );
}
/*//////////////////////////////////////////////





  Direct Graphice Hdc Object
  class d3dHdc 





/*//////////////////////////////////////////////
d3dHdc::d3dHdc()
{
	m_hdc = 0 ;
	m_Surface = 0 ;
	//���o�˸m
	if( !d3d_Device )
		return ;
	if( d3d_Device->GetBackBuffer( 0 , 0 , D3DBACKBUFFER_TYPE_MONO , &m_Surface ) != D3D_OK )
		return ;

	m_Surface->GetDC( &m_hdc );

}

d3dHdc::~d3dHdc()
{
	Release();
}

void d3dHdc::Release()
{
	if( m_Surface )
	{
		if( m_hdc )
			m_Surface->ReleaseDC( m_hdc );
		m_Surface->Release();

		m_hdc = NULL ;
		m_Surface = NULL ;
	}

}
