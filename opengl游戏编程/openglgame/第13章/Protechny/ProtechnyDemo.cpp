//=========================================================================
/**
*  @file      ProtechnyDemo.cpp
*
*  ��Ŀ������ ����ϵͳ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-12-02
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
#include "stdafx.h"
#include "ProtechnyDemo.h"						    


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	ProtechnyDemo * demo = new ProtechnyDemo(class_name);
	return reinterpret_cast<GLApplication *>(demo);
}


/** ���캯�� */
ProtechnyDemo::ProtechnyDemo(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	m_Fps = 0;
	m_RotAngle = 0.0;
		    
}


/** ��ʼ��OpenGL */
bool ProtechnyDemo::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);	                             


	glEnable(GL_TEXTURE_2D);             /**< ��������ӳ�� */   
	
	/** ���û�����ӻ�ð�͸��Ч�� */
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);    
	glEnable(GL_BLEND);				     /**< ���û�� */
	
	/** ��ʼ������ */
	if(!m_Font.InitFont())
		MessageBox(NULL,"��ʼ������ʧ��!","����",MB_OK);

	/** ����������� */
	if(!m_TextureGround.Load("Data/wall.bmp"))
		MessageBox(NULL,"������������ʧ��!","����",MB_OK);
	
	
	/** ��ʼ����Ȫʵ�� */	
	if(!m_Protechny.Init(5000))
	{
		MessageBox(NULL,"ѩ��ϵͳ��ʼ��ʧ��!","����",MB_OK);
		exit(-1);
	}
	
	return true;                                      
}

/** �û��Զ����ж�غ��� */
void ProtechnyDemo::Uninit()	
{
}

/** ������º��� */
void ProtechnyDemo::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}
	
}

/** ����֡�� */
void ProtechnyDemo::CaculateFrameRate()
{
	static float framesPerSecond    = 0.0f;	     /**< ������ʾ֡�� */	
    static float lastTime			= 0.0f;	     /**< ��¼�ϴ�ʱ�� */						
    float currentTime = GetTickCount() * 0.001f; /**< ��õ�ǰʱ�� */	 			

	framesPerSecond++;                           /**< ��ʾ֡������1 */
    /** ���ʱ������1.0�� */
	if( currentTime - lastTime > 1.0f )          
    {
		
	    lastTime = currentTime;                   /**< ���浱ǰʱ�� */
		m_Fps = framesPerSecond;                  /**< ��ǰ֡������m_Fps */
        framesPerSecond = 0;                      /**< ��֡������ */                    
    }

}

/** ���������Ϣ */
void  ProtechnyDemo::PrintText()
{
	char string[128];                               /**< ���ڱ�������ַ��� */
	glPushAttrib(GL_CURRENT_BIT);                   /**< ����������ɫ������Ϣ */
	glColor3f(0.0f,1.0f,1.0f);                      /**< ����������ɫ */

	/** ���֡�� */
    CaculateFrameRate();                               /**< ����֡�� */
    sprintf(string,"FPS:%d",(int)m_Fps);               /**< �ַ�����ֵ */
	m_Font.PrintText(string, -5.0f,3.5f);              /**< ����ַ��� */
	glPopAttrib();
		
}

/** ���Ƶ��� */
void ProtechnyDemo::DrawGround()
{
	glPushMatrix();
	glRotatef(m_RotAngle,0.0f,1.0f,0.0f);   

	/** ָ������ */
	glBindTexture(GL_TEXTURE_2D,m_TextureGround.ID);
	glColor4ub(255,255,255,255);
	glNormal3f(0.0f,1.0f,0.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f);glVertex3f(-2.5f,-1.0f,2.5f);
		glTexCoord2f(1.0f,0.0f);glVertex3f(-2.5f,-1.0f,-2.5f);
		glTexCoord2f(1.0f,1.0f);glVertex3f(2.5f,-1.0f,-2.5f);
		glTexCoord2f(0.0f,1.0f);glVertex3f(2.5f,-1.0f,2.5f);
	glEnd();
	
	glPopMatrix();
	
	/** ����ת���ĽǶ� */
	m_RotAngle += 0.005f;
}



/** ���ƺ��� */
void ProtechnyDemo::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-6.0f);

	/** ���Ƶ��� */
	DrawGround();
    
	/** ��Ⱦ��Ȫ */
	m_Protechny.Render();

	/** �����Ļ��Ϣ */ 
	PrintText();
		
	glFlush();	                 /**< ǿ��ִ�����е�OpenGL���� */
}
