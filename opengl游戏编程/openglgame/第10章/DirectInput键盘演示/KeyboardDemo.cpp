//=========================================================================
/**
*  @file      KeyboardDemo.cpp
*
*  ��Ŀ������ DirectInput������ʾ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-10-10
*
*  ����������������������¼����麯��
*																								
*	virtual bool Init();														
*		ִ�����еĳ�ʼ������������ɹ���������true							
*																			
*	virtual void Uninit();													
*		ִ�����е�ж�ع���										
*																			
*	virtual void Update(DWORD milliseconds);										
*		ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ
*																			
*	virtual void Draw();															
*		ִ�����еĻ��Ʋ���
*/
//=========================================================================

#include "KeyboardDemo.h"											/**< ����ͷ�ļ� */

/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	CKeyboardDemo * demo = new CKeyboardDemo(class_name);
	return reinterpret_cast<GLApplication *>(demo);
}


/** ���캯�� */
CKeyboardDemo::CKeyboardDemo(const char * class_name) : GLApplication(class_name)
{ 
}

/** ��ʼ��OpenGL */
bool CKeyboardDemo::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);											

	/** ��������ϵͳ */
	m_pInput = new CInputSystem();

	/** ����ϵͳ��ʼ�� */
	m_pInput->Init(this->m_Window.GetHwnd(),(HINSTANCE)GetModuleHandle(NULL),
		           true,IS_USEKEYBOARD);

	/** ��ʼ������ */
	if(!m_hFont.InitFont())
		MessageBox(NULL,"��ʼ������ʧ�ܣ�","����",MB_OK);

	return true;	/**< �ɹ����� */										
}

/** �û��Զ����ж�غ��� */
void CKeyboardDemo::Uninit()									
{
	/** �û��Զ����ж�ع��� */
	if(m_pInput)
	{
		delete m_pInput;
		m_pInput = NULL;
	}
}

/** ������º��� */
void CKeyboardDemo::Update(DWORD milliseconds)						
{
	/** ����ϵͳ���� */
	m_pInput->Update();

	/** ��ESC��ʱ�˳� */
	if(m_pInput->GetKeyboard()->KeyDown(DIK_ESCAPE))
	{
		TerminateApplication();
	}   	
	     
}

/** ���ƺ��� */
void CKeyboardDemo::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();	
	glTranslatef(0.0f,0.0f,-10.0f);
	

	/** �������������� */
	char string[50] = {"��û�а����κμ�"};
   
	/** ���A�����£� */
	if(m_pInput->GetKeyboard()->KeyDown(DIK_A))
		sprintf(string,"�������� %s ��","A");
	
	/** ���F1�����£� */   
	if(m_pInput->GetKeyboard()->KeyDown(DIK_F1))
       sprintf(string,"�������� %s ��","F1");
	
	/** ���Ctrl��A��ͬʱ���£�*/
	if(m_pInput->GetKeyboard()->KeyDown(DIK_A) && 
	      m_pInput->GetKeyboard()->KeyDown(DIK_LCONTROL))
       sprintf(string,"�������� %s ��","CTRL + A");
	
	/** �����ʾ��Ϣ */
	glColor3f(1.0f,0.0f,1.0f);
	m_hFont.PrintText(string,-2.0,0.0);

	glFlush();

}
