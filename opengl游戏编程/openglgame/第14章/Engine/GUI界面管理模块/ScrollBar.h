//========================================================
/**
*  @file      ScrollBar.h
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

#ifndef _SCROLL_BAR_H_
#define _SCROLL_BAR_H_

#include "StdAfx.h"
#include "button.h"
#include "IniFile.h"


/**\brief
 * ��������
 */
class CScrollBar  
{
public:
	CScrollBar();
	~CScrollBar();


	//! TRUE:ˮƽ��FALSE:��ֱ
	BOOL	style;
	
	//λ�ã����½�����
	int		x,y;
	
	//���������
	int		width;
	
	//�������ĳ���
	int		MaxLength;
	
	//����ĳ���
	int		CellLength;


	/**\brief
	 * ���û���λ��
	 */
	void	SetPos(float p){pos=p;}
	
	
	/**\brief
	 * ��û���λ�ã�posֵ��
	 */
	float	GetPos(){return pos;}
	
	
	/**\brief
	 * ��INI�ļ�����
	 */
	BOOL	LoadIni(char* filename,char* index);
	
	
	/**\brief
	 * ���ƹ�����
	 */
	void	draw(void);
	
	
	/**\brief
	 * �������Ƿ��ڻ״̬��������Ƿ�������
	 */
	BOOL	IsActive(void);


private:
	//! �����λ�ã��ðٷ�����ʾ
	float	pos;

	//! ����ÿ���ƶ�����С����
	float	MinPos;

	//! ���ϣ�ǰ����ť
	CButton*	btn1;

	//! ���£��󣩰�ť
	CButton*	btn2;

	//! ����
	CButton*	CenBtn;

};


#endif