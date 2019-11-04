//========================================================
/**
*  @file      ProgressBar.h
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

#ifndef _PROGRESS_BAR_H_
#define _PROGRESS_BAR_H_

#include "StdAfx.h"
#include "Window.h"


/**\brief
 * ��������
 */
class CProgressBar : public CWindow
{
public:
	CProgressBar();
	~CProgressBar(){}


	/**\brief
	 * ��INI�ļ����봰������
	 */
	virtual BOOL LoadIni(char* filename,char* index);


	/**\brief
	 * ���ý������Ľ���
	 */
	void	SetPos(float p){pos=p;}


	/**\brief
	 * ���ý������߿�Ŀ��
	 */
	void	SetBorderWidth(int b){border=b;}


	/**\brief
	 * ���ý���������ɫ
	 */
	void	SetBarColor(SColor c){BarColor=c;}
	

	/**\brief
	 * ��ý������Ľ���
	 */
	float	GetPos(){return pos;}
	
	
	/**\brief
	 * ȡ�ñ߿�Ŀ��
	 */
	int		GetBorderWidth(){return border;}
	
	
	/**\brief
	 * ȡ�ý���������ɫ
	 */
	SColor	GetBarColor(){return BarColor;}



private:
	//! ������¼�����ý������Ľ���
	float	pos;
	
	//�߿���
	int		border;
	
	//������ɫ
	SColor	BarColor;
	
	
	/**\brief
	 * ���ƽ�����
	 *
	 * �麯�������丸��CWindow��draw()������
	 */
	virtual void OnDraw(void);
};


#endif