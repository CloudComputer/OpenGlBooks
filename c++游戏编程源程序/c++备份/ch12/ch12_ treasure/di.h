/*/////////////////////////////////////////////////////////////////////






  Direct Input 





/*/////////////////////////////////////////////////////////////////////
#if !defined(__DI_INCLUDE__)
#define __DI_INCLUDE__

#define DIRECTINPUT_VERSION 0x0700

#include <dinput.h>
#pragma comment(lib,"dinput.lib")

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")



/*/////////////////////////////////////////////////////////////////////

  �ϥΪ̾ާ@

/*/////////////////////////////////////////////////////////////////////
typedef struct _DI_DEVICE_DATA
{
	DWORD		_time ;//�g�L�ɶ�
	int			News4  ;//�I�@�U��V
	int			News4ing  ;//�����V
	BYTE		Bn[4]	 ;//���@�U����
	BYTE		Bning[4] ;//�������
}DI_DEVICE_DATA ;
extern DI_DEVICE_DATA di_DDD ;
/*/////////////////////////////////////////////////////////////////////


  �򥻵{��


/*/////////////////////////////////////////////////////////////////////
BOOL diCreate( HINSTANCE hInst , HWND hWnd );
void diRelease();

//��L���ާ@(Keyboard��di_DDD)
void diRun();

#endif