//========================================================
/**
*  @file      GUIMgr.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  GUI���������
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef __GUI_MGR_H__
#define __GUI_MGR_H__

#include "ListView.h"
#include "edit.h"
#include "dialog.h"
#include "animate.h"
#include "window.h"
#include "ListView.h"
#include "edit.h"
#include "mapview.h"
#include "progressbar.h"
#include "SceneMgr.h"


/**\brief
 * ���������
 */
class GUIMgr
{
public:
	GUIMgr(void);
	~GUIMgr(void);


	static GUIMgr* GetSysGUIMgr(){return m_pGUIMgr;}

	/**\brief
	 * ��INI�ļ�����������
	 */
	BOOL LoadCurIni(char* _filename,char* _index);


	/**\brief
	 * �������Ⱦ
	 */
	void Render(void);


	/**\brief
	 * ���뵭��
	 */
	void Fade(void);

	/**\brief
	 * ��ʼ���ֵ��뵭��Ч��
	 */
	void BeginFade(void){m_fFadeAlpha=1.f;}


private:
	static GUIMgr* m_pGUIMgr;

	CAnimate m_cCursor;
	CWindow bottom;

	ListView	m_cChatList;

	//! ���������
	Edit		m_cChatEdit;

	//! ���˵�
	Dialog		m_cMainMenu;

	//! С��ͼ
	MapView		m_cMapView;

	//! �Ƿ񵯳����Ի���
	BOOL		m_bMainMenu;

	//! �����С�˵�
	Dialog		m_cTopMenu;
	CAnimate	m_cTopAni;

	//! �������Ƶ��뵭���ı���
	float		m_fFadeAlpha;

	/////////////////////////////////////////
	//! Ӣ�۵�Ѫ��
	CProgressBar m_cRoleLife;

	//! �����Ѫ��
	CProgressBar m_cMonsterLife;

	//! Ӣ�����Դ���
	Dialog		m_cPropertyWnd;
	/**\brief
	 * Ӣ�۵�����
	 */
	void Property(void);

	//! Ӣ�۵���Ʒ������
	Dialog		m_cBagWnd;
	/**\brief
	 * Ӣ�۵���Ʒ��
	 */
	void Bag(void);

	///////////////////////////////////////////
	CTexture	m_cLifeTex;
	CTexture	m_cMagicTex;
	/**\brief
	 * �������ħ����Ļ���
	 */
	void Ball(CTexture tex,float x,float y,float pos);
};

#endif