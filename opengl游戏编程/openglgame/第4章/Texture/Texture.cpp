//=========================================================================
/**
*  @file      Texture.cpp
*
*  ��Ŀ������ ����ӳ��
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

#include "Texture.h"						    


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	Texture * test = new Texture(class_name);
	return reinterpret_cast<GLApplication *>(test);
}


/** ���캯�� */
Texture::Texture(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	rot = 0.0;	
   
}

/** ������������ */
bool Texture::LoadTexture()
{
	/** ����λͼ�ļ� */
	if(!texture1.Load("image.bmp"))                          /**< ����λͼ�ļ� */
	{
		MessageBox(NULL,"װ��λͼ�ļ�ʧ�ܣ�","����",MB_OK);  /**< �������ʧ���򵯳��Ի��� */
		return false;
	}

	/** ����TGA�ļ� */
	if(!texture2.Load("sphere.tga"))                         /**< ����TGA�ļ� */
	{
		MessageBox(NULL,"װ��TGA�ļ�ʧ�ܣ�","����",MB_OK);  /**< �������ʧ���򵯳��Ի��� */
		return false;
	}
	
	/** ��������ӳ�� */
	glEnable(GL_TEXTURE_2D);

  	return true;
}

/** ���ù�Դ */
void Texture::SetLight()
{
    /** �����Դ������ֵ */
	GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f }; 	/**< ��������� */
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };		/**< �������� */
	GLfloat LightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f };	/**< �������� */
	GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };	/**< ��Դλ�� */

	/** ���ù�Դ������ֵ */
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		/**< ���û����� */
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		/**< ��������� */
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpecular);	/**< ��������� */
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	/**< ���ù�Դλ�� */
	
	/** ���ù�Դ */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1); 
}

/** ��ʼ��OpenGL */
bool Texture::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);									
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);	                             /**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */
	
		
	/** �������� */
	if(!LoadTexture())
		MessageBox(NULL,"��������ʧ��!","����",MB_OK);
	
	/** ���ù�Դ */
	SetLight();

	return true;                                        /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void Texture::Uninit()									
{
/** �û��Զ����ж�ع��� */
	texture1.FreeImage();              /** �ͷ�����ͼ��ռ�õ��ڴ� */
	glDeleteTextures(1, &texture1.ID); /**< ɾ��������� */

	texture2.FreeImage();              /** �ͷ�����ͼ��ռ�õ��ڴ� */
	glDeleteTextures(1, &texture2.ID); /**< ɾ��������� */

 }

/** ������º��� */
void Texture::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}


	if (m_Keys.IsPressed(VK_F1) == true)					/**< ��F1�ڴ��ں�ȫ�����л� */
	{
		ToggleFullscreen();									
	}
	
	rot += milliseconds/20.0;

		    
}


/** �������� */
void Texture::DrawSphere()
{
	glPushMatrix();
	glTranslatef(2.0f,0.0f,-10.0f);
	glRotatef(rot,0.0f,1.0f,1.0f);
	
	/** ָ������ */
	glBindTexture(GL_TEXTURE_2D,texture2.ID);
	
      GLUquadricObj * sphere = gluNewQuadric();
      gluQuadricOrientation(sphere, GLU_OUTSIDE);
	  gluQuadricNormals(sphere,GLU_SMOOTH);
	  gluQuadricTexture(sphere,GL_TRUE);
	  gluSphere(sphere,1.5,50,50);
	  gluDeleteQuadric(sphere);
	glPopMatrix();
	
}

/** ����ľ�� */
void Texture::DrawBox()
{
	/** ���ò������� */
	GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glPushMatrix();
	glTranslatef(-2.0f,0.0f,-10.0f);
	glRotatef(rot,1.0f,1.0f,0.0f);
	
	/** ѡ������ */
	glBindTexture(GL_TEXTURE_2D, texture1.ID);
	
	/** ��ʼ�����ı��� */
	glBegin(GL_QUADS);												
		
	    /// ǰ����
		glNormal3f( 0.0f, 0.0f, 1.0f);								/**< ָ������ָ��۲��� */
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	
		
		/// �����
		glNormal3f( 0.0f, 0.0f,-1.0f);								/**< ָ�����߱���۲��� */
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	
		
		/// ����
		glNormal3f( 0.0f, 1.0f, 0.0f);								/**< ָ���������� */
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	
		
		/// ����
		glNormal3f( 0.0f,-1.0f, 0.0f);								/**< ָ�����߳��� */
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	
		
		/// �Ҳ���
		glNormal3f( 1.0f, 0.0f, 0.0f);								/**< ָ�����߳��� */
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	
		
		/// �����
		glNormal3f(-1.0f, 0.0f, 0.0f);								/**< ָ�����߳��� */
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	
	glEnd();

	glPopMatrix();
}

/** ���ƺ��� */
void Texture::Draw()											
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();	
	
	/** ���ƹ��� */
    DrawSphere();
	DrawBox();
	
	/** ǿ��ִ�����е�OpenGL���� */	
	glFlush();							    
}
