
#ifndef GL_FRAME_H
#define GL_FRAME_H

#include <windows.h>								

///���̻�����
typedef struct {									
	BOOL keyDown [256];							
} Keys;											

//Ӧ�ó���ṹ
typedef struct {								
	HINSTANCE		hInstance;						
	const char*		className;						
} Application;									

//���ڵĳ�ʼ�����Խṹ 
typedef struct {									
	Application*		application;				
	char*				title;	                    //����					
	int					width;						//���
	int					height;						//�߶�
	int					bitsPerPixel;				//bpp
	BOOL				isFullScreen;				//�Ƿ�ȫ��
} GL_WindowInit;									

///���ڽṹ
typedef struct {									
	Keys*				keys;						// ���̽ṹ
	HWND				hWnd;						// ���ھ��
	HDC					hDC;						// �豸������
	HGLRC				hRC;						// ��Ⱦ������
	GL_WindowInit		init;						// ��ʼ���ṹ��
	BOOL				isVisible;					// �Ƿ�ɼ�
	DWORD				lastTickCount;				// ʱ��
} GL_Window;										

static int ScreenW=800;											  
static int ScreenH=600;											    // Window Structure


void TerminateApplication (GL_Window* window);		// ��������

void ToggleFullscreen (GL_Window* window);			// �л�ģʽ

BOOL Initialize (GL_Window* window, Keys* keys);	// ��ʼ��

void Deinitialize (void);							// ж�ع���

void Update (DWORD milliseconds);					// ���²���

void Draw (void);									// ��Ⱦ����

#endif												