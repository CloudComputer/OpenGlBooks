/**  
*
*
*   @file   stdafx.h
*
*
*/

#ifndef _STDAFX_H_
#define _STDAFX_H_

#define WIN32_LEAN_AND_MEAN	

/** Ϊ����WM_MOUSEWHEEL��Ϣ���ӵ� */
#define _WIN32_WINNT 0x0400
#define _WIN32_WINDOWS 0x0400


/** ����ͳ�е�ͷ�ļ� */
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

/** ����OpenGLͷ�ļ� */
#include <gl\gl.h>				 
#include <gl\glu.h>
#include <gl\glaux.h>
#include <gl\glext.h>

/** �����Զ���ͷ�ļ� */
#include "general.h"
#include "structdef.h"


/** Ҫ�õ������ӿ� */
#pragma comment(lib, "opengl32.lib")		
#pragma comment(lib, "glu32.lib")							
#pragma comment(lib, "glaux.lib")	
#pragma comment(lib,"dxguid.lib"	)
#pragma comment(lib,"dinput8.lib"	)
#pragma comment(lib,"dsound.lib"	)
#pragma comment(lib,"winmm.lib"		)
//#pragma comment(lib,"zlibstat.lib"	)
//#pragma comment(lib, "ws2_32.lib"	)

/** ��ֹ��������������ת���ľ��� */
#pragma warning(disable: 4311)                                 
#pragma warning(disable: 4312)
#pragma warning(disable: 4244)
#pragma warning(disable: 4018)
#pragma warning(disable: 4267)


#endif