//=========================================================================
/**
*  @file      BitmapFont.cpp
*
*  ��Ŀ������ OpenGL����
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-12-02	
*  �޸����ڣ� 2007-05-26
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

#include "BitmapFont.h"						    


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	BitmapFont * test = new BitmapFont(class_name);
	return reinterpret_cast<GLApplication *>(test);
}


/** ���캯�� */
BitmapFont::BitmapFont(const char * class_name) : GLApplication(class_name)
{
  
	/// ��ʼ���û��Զ���ĳ������
	cnt1 = 0.0;
	cnt2 = 0.0;	
   
}


/** ��ʼ��OpenGL */
bool BitmapFont::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);	                             /**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */
			
	/** ��ʼ������ */
	if(!font.InitFont(wglGetCurrentDC(),"Arial",60)) 
	   return false;

	return true;                                        /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void BitmapFont::Uninit()									
{
}

/** ������º��� */
void BitmapFont::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}


    cnt1 += milliseconds/1500.0;  /**< ���¼�����ֵ */
	cnt2 += milliseconds/1000.0;  /**< ���¼�����ֵ */
		    
}


/** ���ƺ��� */
void BitmapFont::Draw()											
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	 /**< ������� */		
	glLoadIdentity();	
	
    /** �����ַ����� */
	glTranslatef(0.0f, 0.0f, -10.0f);                              /**< ������Ļ */
	glColor3f(cos(cnt1),sin(cnt2),1.0f - 0.5f * cos(cnt1 + cnt2)); /**< ָ����ɫ */
    
	/** ���÷�������ַ��� */
	font.PrintText("Hello,OpenGL!",-3.5f + 2.0 * cos(cnt1), 3.5f * sin(cnt2)); 
	
	
	/** ǿ��ִ�����е�OpenGL���� */	
	glFlush();							    
}
