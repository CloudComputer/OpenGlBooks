//========================================================
/**
*  @file      SkyBox.cpp
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  �����
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#include "stdafx.h"
#include "SkyBox.h"
#include <math.h>


CSkyBox::CSkyBox():yrot(0.f)
{
}

CSkyBox::~CSkyBox()
{
}


/**\brief
 * ��յĳ�ʼ��
 */
BOOL CSkyBox::Init()
{
	if(!texture.InitTexture("scene/cloud.bmp"))
		return FALSE;
	return TRUE;
}


/**\brief
 * ��Ⱦ���
 */
void CSkyBox::Render()
{
	CCamera::GetCameraPointer()->GetCameraPos(&m_sCameraPos);
	texture.Bind(0);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(m_sCameraPos.x,-40,m_sCameraPos.z-CCamera::GetCameraPointer()->GetDestToRole());
	glRotatef(yrot,0.f,1.f,0.f);
	glColor3f(1.f,1.f,1.f);
	glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.5,0.5);
		glVertex3f(0,300,0);
		glTexCoord2f(0,0);
		glVertex3f(-300,0, 300);

		glTexCoord2f(1,0);
		glVertex3f(-300,0,-300);

		glTexCoord2f(1,1);
		glVertex3f( 300,0,-300);

		glTexCoord2f(0,1);
		glVertex3f( 300,0, 300);

		glTexCoord2f(0,0);
		glVertex3f(-300,0, 300);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	yrot += 0.04f;
	if(yrot > 360.0f)yrot -= 360.0f;
}
