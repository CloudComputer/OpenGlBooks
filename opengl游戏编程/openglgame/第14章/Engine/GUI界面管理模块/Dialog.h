//========================================================
/**
*  @file      Dialog.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  �Ի�����
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef _CGW_DIALOG_H__
#define _CGW_DIALOG_H__

#include "window.h"
#include "button.h"


/**\brief
 * �Ի�����
 */
class Dialog : public CWindow
{
public:
	Dialog(void);
	~Dialog(void);

	/**\brief
	 * ��ð�ť��Ŀ
	 */
	unsigned int GetButtonNum(){return m_nButtonNum;}


	/**\brief
	 * ��INI�ļ�����Ի���
	 */
	BOOL LoadIni(char* _filename,char* _index);


private:
	//! �˵��ϵİ�ť��Ŀ
	unsigned int m_nButtonNum;

	//! ��ťָ��
	CButton*	m_pButton;


	/**\brief
	 * �Ի�����Ⱦ
	 */
	void OnDraw();
};

#endif