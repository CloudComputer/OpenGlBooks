//=========================================================================
/**
*  @file      MouseDemo.cpp
*
*  ��Ŀ������ DirectInput�����ʾ
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

#include "MouseDemo.h"											/**< ����ͷ�ļ� */

/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	CMouseDemo * demo = new CMouseDemo(class_name);
	return reinterpret_cast<GLApplication *>(demo);
}


/** ���캯�� */
CMouseDemo::CMouseDemo(const char * class_name) : GLApplication(class_name)
{ 
}

/** ��ʼ��OpenGL */
bool CMouseDemo::Init()									
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
		           true,IS_USEKEYBOARD|IS_USEMOUSE);

	return true;	/**< �ɹ����� */										
}

/** �û��Զ����ж�غ��� */
void CMouseDemo::Uninit()									
{
	/** �û��Զ����ж�ع��� */
	if(m_pInput)
	{
		delete m_pInput;
		m_pInput = NULL;
	}
}

/** ������º��� */
void CMouseDemo::Update(DWORD milliseconds)						
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
void CMouseDemo::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();	
	glTranslatef(0.0f,0.0f,-10.0f);
	
	/** �������������� */
	char string[50];
    static bool flag = false;
	static bool lButtonDown = false;
	static bool rButtonDown = false;

	/** ���ñ��� */
	if(m_pInput->GetMouse()->IsLButtonPressed())
		lButtonDown = true;
	if(m_pInput->GetMouse()->IsRButtonPressed())
		rButtonDown = true;

	if(lButtonDown && m_pInput->GetMouse()->IsLButtonPressed()==false)
	{
		lButtonDown = false;
		flag = false;
	}
	
	if(rButtonDown && m_pInput->GetMouse()->IsRButtonPressed()==false)
	{
		rButtonDown = false;
		flag = false;
	}

	/** �������ʱ */
	if(lButtonDown && !flag)
	{	
		flag = true;
		sprintf(string,"�����������£�λ��Ϊ��%d,%d",
			m_pInput->GetMouse()->GetMousePos().x,
            m_pInput->GetMouse()->GetMousePos().y);
	    MessageBox(NULL,string,"��ʾ",MB_OK);

	}

	/** �Ҽ�����ʱ */
	if(rButtonDown && !flag)
	{	
		flag = true;
		sprintf(string,"����ҽ������£�λ��Ϊ��%d,%d",
			m_pInput->GetMouse()->GetMousePos().x,
            m_pInput->GetMouse()->GetMousePos().y);
	    MessageBox(NULL,string,"��ʾ",MB_OK);

	}

	glFlush();

}
