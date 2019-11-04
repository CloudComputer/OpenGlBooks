//=========================================================================
/**
*  @file      SoundDemo.cpp
*
*  ��Ŀ������ DirectSound������ʾ
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

#include "DirectSoundDemo.h"											/**< ����ͷ�ļ� */

/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	CSoundDemo * demo = new CSoundDemo(class_name);
	return reinterpret_cast<GLApplication *>(demo);
}


/** ���캯�� */
CSoundDemo::CSoundDemo(const char * class_name) : GLApplication(class_name)
{ 
}

/** ��ʼ��OpenGL */
bool CSoundDemo::Init()									
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

	/** ������Ƶϵͳ���������� */
	m_pSoundManager = new CSoundManager();
	m_pSound1 = new CSound();
	m_pSound2 = new CSound();

	/** ����ϵͳ��ʼ�� */
	m_pInput->Init(this->m_Window.GetHwnd(),(HINSTANCE)GetModuleHandle(NULL),
		           true,IS_USEKEYBOARD);


    /** ��Ƶϵͳ��ʼ�� */
	m_pSoundManager->Init(this->m_Window.GetHwnd());
	
	/** ��������������ʽ */
	m_pSoundManager->SetPrimaryBuffer();

	/** �������������� */
	m_pSound1->LoadWaveFile("airplane.wav");
	m_pSound1->Play(true);

	m_pSound2->LoadWaveFile("explorer.wav");
	m_pSound2->Play(true);

	/** ��ʼ������ */
	if(!m_hFont.InitFont())
	{
		MessageBox(NULL,"��ʼ������ʧ��!","����",MB_OK);
		return false;
	}
	
	return true;	/**< �ɹ����� */										
}

/** �û��Զ����ж�غ��� */
void CSoundDemo::Uninit()									
{
	/** �û��Զ����ж�ع��� */
	if(m_pInput)
	{
		delete m_pInput;
		m_pInput = NULL;
	}
	if(m_pSound1)
	   delete m_pSound1;
		if(m_pSound2)
	   delete m_pSound2;

	if(m_pSoundManager)
		delete m_pSoundManager;

}

/** ������º��� */
void CSoundDemo::Update(DWORD milliseconds)						
{
	/** ����ϵͳ���� */
	m_pInput->Update();

	/** ��ESC��ʱ�˳� */
	if(m_pInput->GetKeyboard()->KeyDown(DIK_ESCAPE))
	{
		TerminateApplication();
	} 

	/** ���¡�A����ֹͣ�ɻ��������� */
	if(m_pInput->GetKeyboard()->KeyDown(DIK_A))
	{
		m_pSound1->Stop();
	} 

	/** ���¡�S����ֹͣ��ը�������� */
	if(m_pInput->GetKeyboard()->KeyDown(DIK_S))
	{
		m_pSound2->Stop();
	} 
	     
}

/** ���ƺ��� */
void CSoundDemo::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();	
	glTranslatef(0.0f,0.0f,-10.0f);

	/** �����ʾ��Ϣ */
	m_hFont.PrintText("���¡�A�����رշɻ�����",-2.5,1.0);
	m_hFont.PrintText("���¡�S�����رձ�ը����",-2.5,0.0);
	m_hFont.PrintText("���¡�ESC�����˳�",-2.5,-1.0);
	
	glFlush();

}
