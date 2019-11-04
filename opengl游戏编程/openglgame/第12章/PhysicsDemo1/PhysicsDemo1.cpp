//=========================================================================
/**
*  @file      PhysicsDemo1.cpp
*
*  ��Ŀ������ �����˶���ʾ
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

#include "PhysicsDemo1.h"											/**< ����ͷ�ļ� */

/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	CDemo * demo = new CDemo(class_name);
	return reinterpret_cast<GLApplication *>(demo);
}


/** ���캯�� */
CDemo::CDemo(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	x = -5.0;
	y = 0.5;
	vx = 0.01;

												
}

/** ��ʼ��OpenGL */
bool CDemo::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);											/**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */


	/** �����Դ������ֵ */
	GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; 	/**< ��������� */
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };		/**< �������� */
	GLfloat LightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f };	/**< �������� */
	GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };	/**< ��Դλ�� */


    /** ���ù�Դ������ֵ */
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		/**< ���û����� */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		/**< ��������� */
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);	/**< ��������� */
	
	
	/** ���ù�Դ������ */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1); 	
	
	/** ��ʼ������ϵͳ */
	m_pInput = new CInputSystem();
	m_pInput->Init(this->m_Window.GetHwnd(),(HINSTANCE)GetModuleHandle(NULL),
		           true,IS_USEKEYBOARD|IS_USEMOUSE);
	
	return true;											/**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void CDemo::Uninit()									
{
/** �û��Զ����ж�ع��� */
 if(m_pInput)
 {
	 delete m_pInput;
	 m_pInput = NULL;
 }
}

/** ������º��� */
void CDemo::Update(DWORD milliseconds)						
{

/** �û��Զ���ĸ��¹��� */
	m_pInput->Update();
	if(m_pInput->GetKeyboard()->KeyDown(DIK_ESCAPE))
	{
		TerminateApplication();
	} 
    
	/** ����С���λ�� */
    x += vx;
	if(x > 5.0 || x<-5.0)
		vx = -vx;
     
}


/** ����������� */
void CDemo::DrawGrid()
{
    /** ��ó�����һЩ״̬  */
	GLboolean  lp,tp;
	glGetBooleanv(GL_LIGHTING,&lp);  
	glGetBooleanv(GL_TEXTURE_2D,&tp);
	
	/** �ر�����͹��� */
	glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
	
	/** ���ƹ��� */
	glPushAttrib(GL_CURRENT_BIT);   /**< ���浱ǰ���� */
    glPushMatrix();                 /**< ѹ���ջ */
	glTranslatef(0.0f,0.0f,0.0f);  
	glColor3f(0.0f, 0.0f, 1.0f);    /**< ������ɫ */

	/** ��X,Zƽ���ϻ������� */
	for(float i = -50; i <= 50; i += 1)
	{
		/** ������ */
		glBegin(GL_LINES);

		    /** X�᷽�� */
			glVertex3f(-50, 0, i);
			glVertex3f(50, 0, i);

			/** Z�᷽�� */
			glVertex3f(i, 0, -50);
			glVertex3f(i, 0, 50);

		glEnd();
	}
	glPopMatrix();
	glPopAttrib();
	/** �ָ�����״̬ */
	if(tp)
	  glEnable(GL_TEXTURE_2D);
	if(lp)
      glEnable(GL_LIGHTING);
}

/** �������� */
void CDemo::DrawSphere(float x,float y)
{
	/** ���ò������� */
	GLfloat mat_ambient[] = { 0.9f, 0.5f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.9f, 0.5f, 0.8f, 1.0f };
	GLfloat mat_shininess[] = { 100.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
	/** �����������״̬ */
	GLboolean tp;
	glGetBooleanv(GL_TEXTURE_2D,&tp);
    glDisable(GL_TEXTURE_2D);                   /**< �ر����� */
    /** ���ƹ��� */
	glPushMatrix();
    glTranslatef(x,y,-5.0f);
    GLUquadricObj * sphere = gluNewQuadric();
    gluQuadricOrientation(sphere, GLU_OUTSIDE);
	gluQuadricNormals(sphere,GLU_SMOOTH);
	gluSphere(sphere,0.25,20,20);
	gluDeleteQuadric(sphere);
    glPopMatrix();
    
	/** �ָ�״̬ */
	if(tp)
	   glEnable(GL_TEXTURE_2D);
	
}

/** ���ƺ��� */
void CDemo::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();	

	/** �����ӵ� */
	gluLookAt(0.0f,1.5f, 5.0f, 
		      0.0f, 1.5f, 0.0f,
			  0.0f, 1.0f, 0.0f);
	
	/** ����������� */
	DrawGrid();

	/** ����С�� */
    DrawSphere(x,y);


		

}
