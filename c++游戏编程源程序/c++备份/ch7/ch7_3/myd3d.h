/*////////////////////////////////////////////////






  Direct Graphice





/*////////////////////////////////////////////////

#if !defined(__MYD3D_H___)
#define __MYD3D_H___


#include "d3d9.h"
#include "d3dx9tex.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

/*//////////////////////////////////////////////




  �`�γ��I���




/*//////////////////////////////////////////////

/*//////////////////////////////////////////////

  �w�W��A�w�ഫ

/*//////////////////////////////////////////////
const DWORD D3DFVF_TLVERTEX = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE |  D3DFVF_SPECULAR | D3DFVF_TEX1 );
typedef struct _D3DTLVERTEX 
{
	float x , y , z , rhw ;
	D3DCOLOR  diffuse , specular;
	float tu, tv;
}D3DTLVERTEX ;
/*//////////////////////////////////////////////

  �t��

/*//////////////////////////////////////////////
extern LPDIRECT3D9			d3d_3D ;
extern LPDIRECT3DDEVICE9	d3d_Device ;
//��l��
void d3dInit();
//����
void d3dRelease();
//�إ�
BOOL d3dCreate( HWND hWnd , int width , int height , BOOL IsWindow  );
//�վ�ù��l�ΰϤj�p
BOOL d3dSetDisplaySize( HWND hWnd , int width , int height );
//�إ�D3d �� Device 
BOOL d3dDeviceCreate( HWND hWnd , BOOL IsWindow );
//ø�ϭ��M��
void d3dClear( UINT color = 0 );

/*//////////////////////////////////////////////





  Direct Graphice Hdc Object
  class d3dHdc 





/*//////////////////////////////////////////////

class d3dHdc 
{
private :
	HDC m_hdc ;
	LPDIRECT3DSURFACE9 m_Surface ;

public :
	void Release();
	inline operator HDC(){ return m_hdc ;};
public :
	d3dHdc();
	~d3dHdc();
};

/*////////////////////////////////////////////////




  3D ����




/*////////////////////////////////////////////////
class d3dTexture
{
private :
	int					m_Width ;
	int					m_Height ;
	LPDIRECT3DTEXTURE9	m_Texture ;
public :
	void BltFast( int x , int y );
	void BltFast( int l , int t , int r , int b );
public :
	BOOL Create( LPCTSTR file );
	void Release();
	inline operator LPDIRECT3DTEXTURE9(){ return m_Texture ;};
public :
	d3dTexture();
	~d3dTexture();
};


#endif

