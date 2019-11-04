
#include <windows.h>

#include "di.h"
/*/////////////////////////////////////////////////////////////////////


  �򥻪���


/*/////////////////////////////////////////////////////////////////////

LPDIRECTINPUT7			di_DI;        //�ŧi DirectInput �������
LPDIRECTINPUTDEVICE7	di_Key ; //�ŧi��J�˸m�������

DWORD					di_TimeBuffer ;

BYTE					di_KeyData[256] ; //�U�O���

DI_DEVICE_DATA di_DDD ;
/*/////////////////////////////////////////////////////////////////////

  �إ�

/*/////////////////////////////////////////////////////////////////////
BOOL diCreate( HINSTANCE hInst , HWND hWnd )
{
	di_DI = NULL ;
	di_Key = NULL ;
	memset( &di_DDD , 0 , sizeof( di_DDD ));

	//�إ� DirectInput ����
	if( DirectInputCreateEx(hInst, DIRECTINPUT_VERSION, 
        IID_IDirectInput7, (void**)&di_DI, NULL) != DI_OK )
		return false ;
	//�إ߿�J�˸m����
	if( di_DI->CreateDeviceEx(GUID_SysKeyboard, IID_IDirectInputDevice7,
        (void**)&di_Key, NULL) != DI_OK)
		return false ;
	//�]�w��Ʈ榡
	if( di_Key->SetDataFormat(&c_dfDIKeyboard) != DI_OK)
		return false ;
	//�]�w�{����ռh��
	if( di_Key->SetCooperativeLevel(hWnd, 
                   DISCL_BACKGROUND | DISCL_NONEXCLUSIVE) != DI_OK)
		return false ;
	//���ο�J�˸m
	if( di_Key->Acquire() != DI_OK)
		return false ;
	//���ثe�ɶ�
	di_TimeBuffer = timeGetTime();
	//����
	return true ;
}

/*/////////////////////////////////////////////////////////////////////

  ����

/*/////////////////////////////////////////////////////////////////////
void diRelease()
{
	if( di_Key )di_Key->Release();
	if( di_DI )di_DI->Release();
}

/*/////////////////////////////////////////////////////////////////////

  ���θ˸m

/*/////////////////////////////////////////////////////////////////////
void diRun()
{
	int i ;
	int news ;
	DWORD tNow ;
	const BYTE key[4] = { DIK_Z , DIK_X , DIK_C , DIK_V , };
	//�ɶ�
	do
	{
		tNow = timeGetTime();
		di_DDD._time = tNow - di_TimeBuffer ;
	}while( di_DDD._time < 15 );
	if( di_DDD._time > 40 )di_DDD._time = 40 ;
	di_TimeBuffer = tNow ;
	//���o��L���A
	if( di_Key )
    if( di_Key->GetDeviceState( 256 ,(LPVOID)&di_KeyData )== DI_OK )
	{
	//��V��
		if( di_KeyData[ DIK_DOWN] & 0x80 )
			news = 1 ;//�U
		else if( di_KeyData[ DIK_UP ] & 0x80 )
			news = 5 ;//�W
		else if( di_KeyData[ DIK_LEFT ] & 0x80 )
			news = 7 ;//��
		else if( di_KeyData[ DIK_RIGHT ] & 0x80 )
			news = 3 ;//�k
		else news = 0 ;
	//��V���ʤ�
		if( news == di_DDD.News4ing )
		{
			if( di_DDD.News4ing )
				di_DDD.News4 = 0 ;
			else 
			{
				di_DDD.News4 = news ;
				di_DDD.News4ing = news ; 
			}
		}else
		{
			di_DDD.News4 = news ;
			di_DDD.News4ing = news ;
		}
	//����
		for( i = 0 ; i < 4 ; i++ )
		{
			if( di_KeyData[ key[i]] & 0x80 )
			{
				if( di_DDD.Bning[i] )
					di_DDD.Bn[i] = false ;
				else
				{
					di_DDD.Bn[i] = true ;
					di_DDD.Bning[i] = true ;
				}
			}else
			{
				di_DDD.Bn[i] = false ;
				di_DDD.Bning[i] = false ;
			}
		}
	}
}