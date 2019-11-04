//========================================================
/**
*  @file      Animate.cpp
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  2Dƽ�涯����
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
#include "Animate.h"
#include "timer.h"


CAnimate::CAnimate():FrameNum(1),color(SColor(1.0,1.0,1.0,1.0)),
		m_fDeltaTime(0.f),bBlend(TRUE),DeltaTime(0.5f),n(0)
{
}


/**\brief
 * ��������
 *
 *\param	filename	�����ļ���
 *\param	nFrameNum	��֡��
 *\param	_bBlend		�Ƿ�͸������
 *\return	BOOL		�Ƿ�ɹ���������
 */
BOOL CAnimate::LoadTexture(char* filename,int nFrameNum,BOOL _bBlend)
{
	FrameNum=nFrameNum;
	texture.InitTexture(filename,_bBlend);

	return TRUE;
}


/**\brief
 * ͨ��INI�ļ���ʼ��
 */
BOOL CAnimate::LoadIni(char* filename,char* index)
{
	CIniFile Ini(filename);

	rect.x=Ini.ReadInt(index,"x");
	rect.y=Ini.ReadInt(index,"y");
	rect.width=Ini.ReadInt(index,"width");
	rect.height=Ini.ReadInt(index,"height");

	color.r	=PERSENT(Ini.ReadInt(index,"r"));
	color.g	=PERSENT(Ini.ReadInt(index,"g"));
	color.b	=PERSENT(Ini.ReadInt(index,"b"));
	color.a	=PERSENT(Ini.ReadInt(index,"a"));

	DeltaTime	=PERSENT(Ini.ReadInt(index,"DeltaTime"));
	char* file	=Ini.ReadText(index,"TexFile");

	FrameNum=Ini.ReadInt(index,"FrameNum");

	this->LoadTexture(file,FrameNum,bBlend);

	return TRUE;
}



/**\brief
 * ��Ⱦ����
 */
void CAnimate::draw()
{
	glEnable(GL_TEXTURE_2D);
	texture.Bind(0);

	if(bBlend==TRUE)
	{
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER , 0.0f);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	}

	glBegin(GL_TRIANGLE_FAN);
	glColor4f(color.r,color.g,color.b,color.a);
		glTexCoord2f( (1.0f/(float)FrameNum)*(float)(n+0),1);
		glVertex2i(rect.x,rect.y+rect.height);

		glTexCoord2f( (1.0f/(float)FrameNum)*(float)(n+0),0);
		glVertex2i(rect.x,rect.y);

		glTexCoord2f( (1.0f/(float)FrameNum)*(float)(n+1),0);
		glVertex2i(rect.x+rect.width,rect.y);

		glTexCoord2f( (1.0f/(float)FrameNum)*(float)(n+1),1);
		glVertex2i(rect.x+rect.width,rect.y+rect.height);
	glEnd();

	m_fDeltaTime-=CTimer::GetSysTimer()->m_fTime;
	if(m_fDeltaTime<=0.0f) { ++n;m_fDeltaTime=DeltaTime;}
	if(n>=FrameNum)n=0;

	if(bBlend==TRUE)
	{
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
	}
	glDisable(GL_TEXTURE_2D);
}
