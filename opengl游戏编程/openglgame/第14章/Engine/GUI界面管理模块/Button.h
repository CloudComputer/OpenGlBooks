//========================================================
/**
*  @file      Button.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��ť��
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "StdAfx.h"
#include "Window.h"
#include "Font.h"
#include "IniFile.h"
#include "Sound.h"


//! ��ť������ʱҪ���ŵ������ļ�
#define DOWNL_SOUND_NAME "sound\\click.wav"


/**\brief
 * ��ť��
 */
class CButton : public CWindow
{
public:


public:
	CButton();
	virtual ~CButton(){}


	/**\brief
	 * ���ð�ť�ϵ���
	 */
	void	SetText(char* str){bHasText=TRUE;strcpy(m_chText,str);}


	/**\brief
	 * ȡ�ð�ť�ϵ���
	 */
	char*	GetText(){return m_chText;}


	/**\brief
	 * ���ð�ť�ϵ��ֵ���ʾ����
	 */
	void	SetTextStyle(int _style){m_iTextStyle=_style;}


	/**\brief
	 * ȡ�ð�ť�ϵ��ֵ���ʾ����
	 */
	int		GetTextStyle(){return m_iTextStyle;}


	/**\brief
	 * ���ð�ť�ڻʱ����ɫ
	 */
	void	SetActiveColor(SColor c){color2=c;}


	/**\brief
	 * ȡ�ð�ť�ʱ����ɫ
	 */
	SColor	GetActiveColor(){return color2;}


	/**\brief
	 * ���ð�ťƽ������ɫ
	 */
	void	SetNormalColor(SColor _color){color1=_color;}


	/**\brief
	 * ȡ�ð�ť�ʱ����ɫ
	 */
	SColor	GetNormalColor(){return color1;}


	/**\brief
	 * �����������ɫ
	 */
	void	SetTextColor(SColor _color){m_sTextColor=_color;}


	/**\brief
	 * ���ð�ť�Ƿ����
	 */
	void	SetEnable(BOOL _anable){bEnable=_anable;}


	/**\brief
	 * ȡ�ð�ť�Ƿ����
	 */
	BOOL	GetEnable(){return bEnable;}


	/**\brief
	 * ��INI�ļ�����İ�ť����
	 */
	virtual BOOL LoadIni(char* _filename,char* _index);



private:
	//! ��ť�ϵ���
	char	m_chText[256];
	
	//! ��ť���Ƿ�����
	BOOL	bHasText;

	//! ��ť�Ƿ����
	BOOL	bEnable;

	/**\brief
	 * ����ѭ��,�麯�������丸��CWindow��draw()������
	 */
	virtual void OnDraw(void);


protected:
	//! �����ͣ���ȡBTN_TEXT_LEFT,BTN_TEXT_CENTER,BTN_TEXT_RIGHT
	int		m_iTextStyle;

	//! ��ťƽʱ����ɫ
	SColor	color1;

	//! ��ť������ʱ����ɫ
	SColor	color2;

	//! ������ɫ
	SColor	m_sTextColor;
	
	//! ��갴��ʱ������
	static	CSound m_cSound;

};

#endif