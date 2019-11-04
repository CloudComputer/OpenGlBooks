//========================================================
/**
*  @file      ProgressBar.cpp
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��������
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
#include "ProgressBar.h"


CProgressBar::CProgressBar():pos(0.0f),border(3)
{
	BarColor=SColor(0.0f,0.0f,1.0f,0.0f);
	m_sRect=SRect(0,0,100,20);
}



/**\brief
 * ���ƽ�����
 *
 * �麯�������丸��CWindow��draw()������
 */
void CProgressBar::OnDraw(void)
{
	if(pos>1.0f)pos=1.0f;
	if(pos<0.0f)pos=0.0f;

	glColor4f(BarColor.r,BarColor.g,BarColor.b,BarColor.a);
	glBegin(GL_QUADS);
		glVertex2i(m_sRect.x+border,m_sRect.y+m_sRect.height-border);
		glVertex2i(m_sRect.x+border,m_sRect.y+border);
		glVertex2i(m_sRect.x+border+(int)(pos*(m_sRect.width-2.0f*border)),m_sRect.y+border);
		glVertex2i(m_sRect.x+border+(int)(pos*(m_sRect.width-2.0f*border)),m_sRect.y+m_sRect.height-border);
	glEnd();
}


/**\brief
 * ��INI�ļ����봰������
 */
BOOL CProgressBar::LoadIni(char* filename,char* index)
{
	CIniFile Ini(filename);
	
	m_sRect.x=Ini.ReadInt(index,"x");
	m_sRect.y=Ini.ReadInt(index,"y");
	m_sRect.width=Ini.ReadInt(index,"width");
	m_sRect.height=Ini.ReadInt(index,"height");

	//����ɫ
	m_sColor.r	=PERSENT(Ini.ReadInt(index,"c1r"));
	m_sColor.g	=PERSENT(Ini.ReadInt(index,"c1g"));
	m_sColor.b	=PERSENT(Ini.ReadInt(index,"c1b"));
	m_sColor.a	=PERSENT(Ini.ReadInt(index,"c1a"));
	//������ɫ
	BarColor.r	=PERSENT(Ini.ReadInt(index,"c2r"));
	BarColor.g	=PERSENT(Ini.ReadInt(index,"c2g"));
	BarColor.b	=PERSENT(Ini.ReadInt(index,"c2b"));
	BarColor.a	=PERSENT(Ini.ReadInt(index,"c2a"));

	border=Ini.ReadInt(index,"border");
	pos=PERSENT(Ini.ReadInt(index,"pos"));

	return TRUE;
}

