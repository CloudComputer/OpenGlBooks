//======================================================================
/**
*  @file      GLFrame.h
*
*  ��Ŀ������ Ħ�����������˶�ģ��
*  �ļ�����:  �������� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-10-10
*	
*  ���������ļ̳�����������º�����ʵ��
*																			
*  GLApplication * GLApplication::Create(const char * class_name)		
*		������������һ��ʵ��		
*																			
*  bool Init();														
*		ִ�����еĳ�ʼ������������ɹ���������true							
*																			
*  void Uninit();													
*		ִ�����е�ж�ع���										
*																			
*  void Update(DWORD milliseconds);										
*		ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ
*																			
*  void Draw();															
*		ִ�����еĻ��Ʋ���
*/																			
//======================================================================
#ifndef	__GLFRAME_H__
#define	__GLFRAME_H__

#include "stdafx.h"
#include "GLWindow.h"											/**< ����GLWindow.hͷ�ļ� */

/** �����ĳ����࣬�̳�����������OpenGL���� */
class GLApplication											
{
public:
	/** ����һ��ȫ�ֵ�Create����������������뱻�̳���ʵ�� */
	static GLApplication * Create(const char * class_name);	/**< �������Լ������� */

	/** ���������� */
	virtual ~GLApplication() {};

protected:
	/** ����ĺ������뱻�̳���ʵ�֣���ɻ�����OpenGL��Ⱦ���� */
	virtual bool	Init() = 0;							/**< OpenGL�ĳ�ʼ�� */ 
	virtual void	Uninit() = 0;							/**< OpenGL��ж�� */
	virtual void	Update(DWORD milliseconds) = 0;				/**< ִ��OpenGL����ĸ��� */
	virtual void	Draw() = 0;									/**< ����OpenGL���� */

	/** ͨ�õĺ��� */
	void	ToggleFullscreen();									/**< �л� ȫ��/����ģʽ */
	void	TerminateApplication();								/**< �������� */
	void	ResizeDraw(bool enable) { m_ResizeDraw = enable; }	/**< �����ڴ��ڸı��С��ʱ�򣬿��Ի��� */

	/** ���캯�� */
	GLApplication(const char * class_name);	
	GLWindow	m_Window;										/**< Window�� */
private:
	/** �������ѭ�� */
	friend int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	int		Main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	/** ��Ϣ����ص����� */
	friend LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT	Message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	static const UINT WM_TOGGLEFULLSCREEN = (WM_USER + 1);		/**< �Զ�����Ϣ�����л�����ģʽ��ʱ���� */
	
	const char* m_ClassName;									/**< ������ */
	bool		m_IsProgramLooping;								/**< ����ѭ����ǣ����Ϊfalse�����˳����� */
	bool        m_CreateFullScreen;                             /**< ��Ϊtrue���򴴽�ȫ��ģʽ */
	bool		m_IsVisible;									/**< �����Ƿ�ɼ� */
	bool		m_ResizeDraw;									/**< �Ƿ��ڸı��Сʱ�������˻��ƺ��� */
	DWORD		m_LastTickCount;								/**< ��һ�μ�ʱ����ֵ */
};

#endif	// __GLFRAMEWORK_H__