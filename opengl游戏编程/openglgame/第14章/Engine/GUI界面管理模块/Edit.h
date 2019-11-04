//========================================================
/**
*  @file      Edit.h
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

#ifndef __EDIT_H__
#define __EDIT_H__

#include "stdafx.h"
#include "window.h"
#include "ime.h"
#include "font.h"


/**\brief
 * edit�༭����
 */
class Edit : public CWindow
{
public:
	Edit(void);
	~Edit(void){}


	/**\brief
	 * �Ƿ��������ַ�
	 */
	BOOL IsFocus(){return m_bFocus;}


	/**\brief
	 * ���ý���
	 */
	void SetFocus(BOOL _focus){m_bFocus=_focus;}


	/**\brief
	 * ȡ�ñ༭���е��ַ���
	 */
	char* GetText(){return m_szText;}


	/**\brief
	 * �Ƿ������˻س�
	 */
	BOOL GetReturnState(){return m_bReturn;}
	void SetReturnState(BOOL _b){m_bReturn=_b;}


	/**\brief
	 * ������ʾ���뷨���Ƶ�λ��
	 */
	void SetInputNamePos(SPoint2 _point){m_sNamePos=_point;}


	/**\brief
	 * ����������ɫ
	 */
	void SetFontColor(SColor _color){m_sFontColor=_color;}


	/**\brief
	 * ȡ��������ɫ
	 */
	SColor GetFontColor(){return m_sFontColor;}


	/**\brief
	 * ���ò������ɫ
	 */
	void SetCaretColor(SColor _color){m_sCaretColor=_color;}


	/**\brief
	 * ȡ�ò������ɫ
	 */
	SColor GetCaretColor(){return m_sCaretColor;}


	/**\brief
	 * �����Ƿ�Ϊ��������
	 */
	void SetPasswordState(BOOL _b){m_bPassword=_b;}


private:
	/**\brief
	 * ���ƿؼ�
	 */
	virtual void OnDraw(void);


	//! �Ƿ�������
	BOOL	m_bFocus;

	//! �Ƿ��˻س�
	BOOL	m_bReturn;

	//! �Ƿ�����������
	BOOL	m_bPassword;

	//! ������ַ���
	char	m_szText[256];

	//! ���뷨����ʾ��λ��
	SPoint2	m_sNamePos;

	//! ������λ��
	int		m_iCaret;

	//! ������ɫ
	SColor	m_sFontColor;

	//! �������ɫ
	SColor	m_sCaretColor;

	//! һ���м���������ڲ��������˸��
	float	m_fDeltaTime;
};


#endif