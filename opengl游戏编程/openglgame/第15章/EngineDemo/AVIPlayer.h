//========================================================
/**
*  @file      AVIPlayer.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  AVI������
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef __AVI_PLAYER__
#define __AVI_PLAYER__

#include "stdafx.h"
#include <vfw.h>
#pragma comment(lib,"vfw32.lib")


/**\brief
 * AVI������
 */
class AVIPlayer
{
public:
	AVIPlayer(void);
	~AVIPlayer(void);


	/**\brief
	 * ��ʼ��������
	 */
	BOOL Init(HWND _hWnd);
	
	
	/**\brief
	 * ����AVI�ļ�
	 */
	BOOL Load(char* _filename);

	
	/**\brief
	 * ����ӰƬ
	 */
	void Play();


	/**\brief
	 * ��ͣ����
	 */
	void Pause();


	/**\brief
	 * ֹͣ����
	 */
	void Stop();


private:
	//! �����ھ��
	HWND m_hWnd;

	//! MCI���ھ��
	HWND m_hmmWnd;

};


////////////////////////////////////////////////////
//--------------inline����ʵ��----------------------

/**\brief
 * ����AVI�ļ�
 */
inline BOOL AVIPlayer::Load(char* _filename)
{
	if(!m_hmmWnd)
	{
		m_hmmWnd=MCIWndCreate(m_hWnd,(HINSTANCE)GetModuleHandle(NULL),WS_CHILD|WS_VISIBLE|MCIWNDF_NOMENU|MCIWNDF_NOPLAYBAR,_filename);
		RECT r; GetClientRect(m_hWnd,&r);	
		SetWindowPos(m_hmmWnd,0,0,0,r.right-r.left,r.bottom-r.top,SWP_NOZORDER);
	}

	return TRUE;
}


/**\brief
 * ����ӰƬ
 */
inline void AVIPlayer::Play()
{
	if(m_hWnd)MCIWndPlay(m_hmmWnd);
}


/**\brief
 * ��ͣ����
 */
inline void AVIPlayer::Pause()
{
	if(m_hWnd)MCIWndPause(m_hmmWnd);
}


/**\brief
 * ֹͣ����
 */
inline void AVIPlayer::Stop()
{
	if(m_hmmWnd)
	{
		MCIWndDestroy(m_hmmWnd);
		m_hmmWnd=NULL;
	}
}



#endif