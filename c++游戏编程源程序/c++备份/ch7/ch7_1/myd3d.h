/*////////////////////////////////////////////////






  Direct Graphice





/*////////////////////////////////////////////////

#if !defined(__MYD3D_H___)
#define __MYD3D_H___


#include "d3d9.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")


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

#endif

