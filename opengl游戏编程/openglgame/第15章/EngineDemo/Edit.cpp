//========================================================
/**
*  @file      Edit.cpp
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  �༭����
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
#include "edit.h"
#include "timer.h"

Edit::Edit(void)
	:m_bFocus(FALSE),m_iCaret(0),m_bReturn(FALSE),m_sNamePos(SPoint2(5,130)),m_bPassword(FALSE),
	m_fDeltaTime(0.f),m_sFontColor(SColor(1.f,1.f,1.f,1.f)),m_sCaretColor(SColor(1.f,1.f,1.f,1.f))
{
	ZeroMemory(m_szText,256);
	m_sColor=SColor(0.f,0.f,0.f,1.f);
	m_sRect=SRect(10,20,400,24);
}


/**\brief
 * ���ƿؼ�
 */
void Edit::OnDraw(void)
{
	//! ����edit�Ŀ�Ⱥ͸߶�
	m_sRect.height=16;
	if((m_sRect.width)%16!=2)m_sRect.width-=m_sRect.width%16-16-2;


	//! ȷ���Ƿ񻹿�������
	if( IsActive()&&CInput::GetSysInput()->GetMouse()->ButtonDown(0)&&m_bFocus==FALSE)
	{
		m_bFocus=TRUE; CIme::GetSysIme()->Enable();
	}
	if(!IsActive()&&CInput::GetSysInput()->GetMouse()->ButtonDown(0))
	{
		m_bFocus=FALSE;//CIme::GetSysIme()->Disable();
	}

	SYS_FONT->SetColor(SColor(1.f,0.f,0.f,1.f)/*m_sFontColor*/);
	SYS_FONT->Format(CIme::GetSysIme()->GetImeName());
	SYS_FONT->PrintAt(m_sNamePos.x,m_sNamePos.y);
	SYS_FONT->Format(CIme::GetSysIme()->GetImeInputCompStr());
	SYS_FONT->PrintAt(m_sNamePos.x,m_sNamePos.y-18);

	//! ��ʾ����
	if(m_bFocus)
	{
		m_iCaret=CIme::GetSysIme()->GetWordCaret();
		if(m_iCaret<=(m_sRect.width/16-1))
		{
			CIme::GetSysIme()->SetReceiveChar(true);
			strcpy(m_szText,CIme::GetSysIme()->GetImeInputResultStr());
		}
		else
		{
			m_iCaret=m_sRect.width/16-1;
			CIme::GetSysIme()->SetReceiveChar(false);
		}

		m_fDeltaTime-=CTimer::GetSysTimer()->m_fTime;
		if(m_fDeltaTime<=0.0f)m_fDeltaTime=1.0f;
		if(m_fDeltaTime<0.5f)
		{
			glColor3f(m_sCaretColor.r,m_sCaretColor.g,m_sCaretColor.b);
			glBegin(GL_LINES);
				glVertex2i(m_sRect.x+1+(m_iCaret+1)*16,m_sRect.y);
				glVertex2i(m_sRect.x+1+(m_iCaret+1)*16,m_sRect.y+m_sRect.height);
			glEnd();
		}

		if(CIme::GetSysIme()->GetReturnState())
		{
			m_bReturn=TRUE;
			CIme::GetSysIme()->Disable();
			CIme::GetSysIme()->Enable();
		}

	}else m_bReturn=FALSE;

	SYS_FONT->SetColor(m_sFontColor);
	if(!m_bPassword)//ƽ������״̬
	{
		SYS_FONT->Format(m_szText);
		SYS_FONT->PrintAt(m_sRect.x,m_sRect.y);
	}
	else	//��������״̬ʱ��ʾ"*"
	{
		char str[256];
		size_t  i=strlen(m_szText);
		memset(str,'*',i);
		str[i]='\0';
		SYS_FONT->Format(str);
		SYS_FONT->PrintAt(m_sRect.x,m_sRect.y);
	}
}
