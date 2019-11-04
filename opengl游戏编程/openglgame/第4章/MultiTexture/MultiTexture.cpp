//=========================================================================
/**
*  @file      MultiTexture.cpp
*
*  ��Ŀ������ ����ӳ��
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
#include "MultiTexture.h"						    


/** ���������� */
PFNGLMULTITEXCOORD2FARBPROC     glMultiTexCoord2fARB = NULL;
PFNGLACTIVETEXTUREARBPROC       glActiveTextureARB = NULL;


/** ����һ�������ʵ�� */
GLApplication * GLApplication::Create(const char * class_name)
{
	MultiTexture * test = new MultiTexture(class_name);
	return reinterpret_cast<GLApplication *>(test);
}


/** ���캯�� */
MultiTexture::MultiTexture(const char * class_name) : GLApplication(class_name)
{
  /// ��ʼ���û��Զ���ĳ������
	multitexturing = true;
	sp = false;
}

/** ����Ƿ�֧����չ */
bool MultiTexture::isExtensionSupported(const char* string)
{
	char *extension;			/**< ָ����չ�ַ�����ָ�� */
	char *end;				    /**< ���һ���ַ�ָ�� */
	int idx;

	extension = (char*)glGetString(GL_EXTENSIONS);
	if (extension == NULL)
		return false;	
	
	/** �õ����һ���ַ� */
	end = extension + strlen(extension);	

	/** ѭ�������ַ���string */
	while (extension < end)
	{
		/** �ҵ��ո�ǰ��һ���ַ��� */
		idx = strcspn(extension, " ");
		
		/** ����Ƿ��ҵ��ַ���string */
		if ( (strlen(string) == idx) && (strncmp(string, extension, idx) == 0))
		{
			return true;
		}
		
		/** ��ǰ������string,������һ���ַ��� */
		extension += (idx + 1);
	}
	/** û���ҵ�,�򷵻�false */
	return false;   
}

/** ��ʼ�� */
bool MultiTexture::initMultiTexture()
{
	/** ����Ƿ�֧����չ */
	if (isExtensionSupported("GL_ARB_multitexture"))
	{
				
		/** ��ú���ָ���ַ */
		glActiveTextureARB = (PFNGLACTIVETEXTUREARBPROC) wglGetProcAddress("glActiveTextureARB");
		glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC) wglGetProcAddress("glMultiTexCoord2fARB");
		
		return true;
	}
	else 
		return false;
}

/** ������������  */
bool MultiTexture::loadTexture()
{
	/// �ļ��� 
	char* fileName[4] ={ "wall.bmp","lightmap.bmp","bitmap.bmp","fog.bmp"};
		
	/// �����ķ�λͼ 
	for(int i=0; i<4; i++)
	{
		if(!m_texture[i].Load(fileName[i]))
		{
			MessageBox(NULL,"����λͼ�ļ�ʧ��!","����",MB_OK);
			exit(-1);
		}		 
		
	}
	return true;

}

/** ��ʼ��OpenGL */
bool MultiTexture::Init()									
{
/** �û��Զ���ĳ�ʼ������ */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);						
	glClearDepth(1.0f);											
	glDepthFunc(GL_LEQUAL);										
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);			
	ResizeDraw(true);	                             /**< �ı�OpenGL���ڴ�С��ֱ�ӵ�������ĺ��� */
	

	/** ��ʼ�� */
	if(!initMultiTexture())
	{
		MessageBox(NULL,"��֧�ֶ�������!","����",MB_OK);
		exit(-1);
	}

	/** �������� */
	if(!loadTexture())
	{
		MessageBox(NULL,"�����������!","����",MB_OK);
		exit(-1);
	}
			
		return true;                                        /**< �ɹ����� */
}

/** �û��Զ����ж�غ��� */
void MultiTexture::Uninit()									
{
	for(int i=0; i<4; i++)
	{
		m_texture[i].FreeImage();
		glDeleteTextures(1,&m_texture[i].ID);
	}
}

/** ������º��� */
void MultiTexture::Update(DWORD milliseconds)						
{
	if (m_Keys.IsPressed(VK_ESCAPE) == true)					/**< ��ESC�˳� */
	{
		TerminateApplication();									
	}

/** �û��Զ���ĸ��¹��� */

	/** �����¿ո��ʱ,������رն������� */
	if(m_Keys.IsPressed(VK_SPACE) && !sp)
	{
		sp = true;
		multitexturing = !multitexturing;
	}
	if(!m_Keys.IsPressed(VK_SPACE))
		sp = false;
	
	    
}


/** ���ƺ��� */
void MultiTexture::Draw()											
{
/** �û��Զ���Ļ��ƹ��� */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			
	glLoadIdentity();
	
	glTranslatef(0.0f,0.0f,-10.0f);

	/** ��������0,�������� */
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D,  m_texture[0].ID);

	/** ��������1,�������� */
	glActiveTextureARB(GL_TEXTURE1_ARB);

	/** ���������������,�����ø����� */
	if (multitexturing) 
		glEnable(GL_TEXTURE_2D); 
	else 
		glDisable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,  m_texture[1].ID);

	/** ����һ���ķ���ǽ�� */
	glPushMatrix();
		glTranslatef(-2.5, 0, 0);
		glScalef(2.0f,2.0f,2.0f);
		glBegin(GL_QUADS);

			/** ���ϵ� */
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 1.0f);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f, 1.0f);
			glVertex3f(-1, 1, 0);

			/** ���µ� */
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 0.0f);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f, 0.0f);
			glVertex3f(-1, -1, 0);

			/** ���µ� */
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0f, 0.0f);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1.0f, 0.0f);
			glVertex3f(1, -1, 0);

			/** ���ϵ� */
			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0f, 1.0f);
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1.0f, 1.0f);
			glVertex3f(1, 1, 0);

		glEnd();    /**< ���ƽ��� */											
	glPopMatrix();

	
	/** ��������0,�������� */
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,  m_texture[2].ID);

	/** ��������1,�������� */
	glActiveTextureARB(GL_TEXTURE1_ARB);
	
	/** ���������������,�����ø����� */
	if (multitexturing) 
		glEnable(GL_TEXTURE_2D); 
	else 
		glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,  m_texture[3].ID);

	static float wrap = 0;      /**< ����������� */     

	glTranslatef(2.5, 0, 0);
	glScalef(2.0f,2.0f,2.0f);
	glBegin(GL_QUADS);

		/** ���ϵ� */
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 1.0f);
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f - wrap, 1.0f);
		glVertex3f(-1, 1, 0);

		/** ���µ� */
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0.0f, 0.0f);
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0.0f - wrap, 0.0f);
		glVertex3f(-1, -1, 0);

		/** ���µ� */
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0f, 0.0f);
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1.0f - wrap, 0.0f);
		glVertex3f(1, -1, 0);

		/** ���ϵ� */
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1.0f, 1.0f);
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1.0f - wrap, 1.0f);
		glVertex3f(1, 1, 0);
	glEnd();											

	wrap += 0.001f;                   /**< ���� */

			
	glFlush();	                     /**< ǿ��ִ�����е�OpenGL���� */
}
