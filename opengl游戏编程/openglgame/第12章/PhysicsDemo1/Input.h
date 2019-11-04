//======================================================================
/**
*  @file      Input.h
*
*  ��Ŀ������ �����˶���ʾ
*   
*  �ļ�����:  ����ϵͳ��CInputSystem
*             ����,��CKeyboard��CMouse��CJoystick�ֱ�����������̡����
*			  ����Ϸ�ֱ���CInputSystem�������豸�Ĺ����ࡣ
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-24	
*  �޸����ڣ� 2007-07-24
*/																			
//======================================================================

#ifndef __INPUT_H__
#define __INPUT_H__

#include "stdafx.h"
#include "Vector.h"

#define IS_USEKEYBOARD  1
#define IS_USEMOUSE     2
#define IS_USEJOYSTICK  4

#define DINPUT_BUFFERSIZE  16

/** ������ */
class CKeyboard
{
public:
	/** ���캯������������ */
	CKeyboard(LPDIRECTINPUT8 pDI, HWND hwnd);
	~CKeyboard();

	/** �ж�ĳ�����Ƿ񱻰��� */
	bool KeyDown(char key);
	
	/** �ж�ĳ�����Ƿ��ͷ� */
	bool KeyUp(char key);
	
	/** �Լ����������� */
	void Clear();

	/** ���¼������� */
	bool Update();	

	/** ȡ�������� */
	bool Acquire();

	/** ֹͣȡ���� */
	bool Unacquire();

private:
	/** �����豸 */
	LPDIRECTINPUTDEVICE8  m_pDIDev;

	/** ���������� */
	char    m_keys[256];
};



/** ����� */
class CMouse
{
public:
	/** ���캯������������ */
	CMouse(LPDIRECTINPUT8 pDI,HWND hwnd,bool isExclusive);
	~CMouse();

	/** �������Ƿ��� */
	bool	IsLButtonPressed();

	/** ����Ҽ��Ƿ��� */
	bool	IsRButtonPressed();

	/** ����м��Ƿ��� */
	bool	IsMButtonPressed();

			
	/** ��ù��λ�� */
	Point2	GetMousePos();

	/** ���������� */
	bool	Update();

	/** ȡ������� */
	bool	Acquire();
		
	/** ֹͣȡ���� */
	bool	Unacquire();

	/** ���ڿ� */
	int		m_iWidth;

	/** ���ڸ� */
	int		m_iHeight;


private:
	/** ����豸 */
	LPDIRECTINPUTDEVICE8	m_pDIDev;

	/** �������������� */
	DIDEVICEOBJECTDATA      m_diData[DINPUT_BUFFERSIZE];
	
	/** ���λ�� */
	Point2					m_iMousePos;
};

//////////////
/** ����ϵͳ�� */
class CInputSystem
{
public:
	/** ���캯������������ */
	CInputSystem():bClick(false),bFirstMDownL(false) {  m_pInput = this; }
	~CInputSystem(){  ShutDown();      }  

	/** ��ʼ�������豸 */
	bool Init(HWND hwnd,HINSTANCE appInstance,
		      bool isExclusive,DWORD flags=0);

	/** �ͷ������豸��Դ */
	bool ShutDown();

	/** ȡ�����豸������ */
	void  AcquireAll();

	/** ͣ��ȡ�����豸������ */
	void  UnacquireAll();

	/** ���������豸�Ĳ��� */
	void	Update();

	/** ��ù���3D���� */
	Vector3  GetMousePosition();	

	/** �Ƿ񵥻������ */
	bool	Clicked(){  return  bClick;}

	/** ����Ƿ��ǵ�һ�ΰ��� */
	bool	FirstMouseDownL(){return bFirstMDownL;}
	
	/** ��ü��� */
	CKeyboard*  GetKeyboard(){  return  m_pKeyboard; }

	/** ������ */
	CMouse*       GetMouse() {  return  m_pMouse; }
	
	/** �õ���ǰ�Ĵ��ھ�� */
	static HWND GetSysHWnd() {  return  m_hWnd; }
	
	/** �õ���ǰ�������豸 */
	static CInputSystem* GetSysInput(){  return  m_pInput; }

private:
	/** ����ϵͳ */
	static CInputSystem*  m_pInput;

	/** ���ھ�� */
	static HWND  m_hWnd;

	/** ���� */
	CKeyboard*    m_pKeyboard;

	/** ��� */
	CMouse*   m_pMouse;

	/** �����豸 */
	LPDIRECTINPUT8 m_pDI;

	/** ���������º�̧��ʱΪTRUE */
	bool    bClick;

	/** ��갴�»��и�ʱ��Σ��ǲ��Ǹտ�ʼ���� */
	bool  bFirstMDownL;

};

////////////////////////////////////////////////////////////////////////
/**  CKeybord��inline������ʵ�� */ 

/** key���Ƿ��� */
inline bool CKeyboard::KeyDown(char key)
{
	return (m_keys[key] & 0x80) ? true : false;
}

/** key���Ƿ��� */
inline bool CKeyboard::KeyUp(char key)
{
	return (m_keys[key] & 0x80) ? false : true;
}

/** �Լ����������� */
inline void CKeyboard::Clear()
{
	ZeroMemory(m_keys,256*sizeof(char));
}

/** ȡ�������� */
inline bool CKeyboard::Acquire()
{
	Clear();
	return (!FAILED(m_pDIDev->Acquire()));
}

/** ֹͣȡ���� */
inline bool CKeyboard::Unacquire()
{
	Clear();
	return (!FAILED(m_pDIDev->Unacquire()));
}

////////////////////////////////////////////////////////////////
/**  CMoust��inline������ʵ�� */ 

/** ��ù��λ�� */
inline Point2 CMouse::GetMousePos()
{
	return m_iMousePos;
}

/** ȡ������� */
inline bool CMouse::Acquire()
{
	return (!FAILED(m_pDIDev->Acquire()));
}

/** ֹͣȡ���� */
inline bool CMouse::Unacquire()
{
	return (!FAILED(m_pDIDev->Unacquire()));
}

////////////////////////////
/** CInputSystem���inline���� */

/** ȡ�����豸������ */
inline void CInputSystem::AcquireAll()
{
	if (m_pKeyboard)	m_pKeyboard->Acquire();
	if (m_pMouse)		m_pMouse->Acquire();
	
}

/** ֹͣȡ���� */
inline void CInputSystem::UnacquireAll()
{
	if (m_pKeyboard)	m_pKeyboard->Unacquire();
	if (m_pMouse)		m_pMouse->Unacquire();
	
}


#endif //__INPUT_H__
