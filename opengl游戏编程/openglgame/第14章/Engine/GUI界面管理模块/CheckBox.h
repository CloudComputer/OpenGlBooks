//========================================================
/**
*  @file      CheckBox.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��ѡ����
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================


#ifndef _CHECK_BOX_H_
#define _CHECK_BOX_H_

#include "StdAfx.h"
#include "Button.h"


/**\brief
 * ��ѡ����
 */
class CCheckBox : public CButton  
{
public:
	CCheckBox(){bChecked=FALSE;}
	~CCheckBox(){}


	/**\brief
	 * ��INI�ļ�����
	 */
	virtual BOOL LoadIni(char* filename,char* index);


	/**\brief
	 * �Ƿ�ѡ��
	 */
	BOOL	GetState(){return bChecked;}


	/**\brief
	 * ���ø�ѡ���״̬
	 */
	void	SetState(BOOL _bChecked){bChecked=_bChecked;}

private:
	//! �Ƿ�ѡ
	BOOL bChecked;


	/**\brief
	 *  ����
	 */
	virtual void OnDraw(void);

};

#endif