//========================================================
/**
*  @file      Music.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  DirectMusic������
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "StdAfx.h"
#include <dmusicc.h>
#include <dmusici.h>


/**\brief
 * DMusic�����ֲ�����
 */
class CMusic
{
public:
	CMusic();
	~CMusic();

	static IDirectMusicSegment* LoadMIDISegment(IDirectMusicLoader* pLoader, WCHAR *wszMidiFileName );

	/**\brief
	 * ��ʼ��DMUSIC
	 */
	static BOOL InitMusic();

	/**\brief
	 * ����MIDI�����ļ�
	 */
	BOOL LoadMusic(WCHAR *);
	BOOL LoadMusic(char* filename){return LoadMusic(WChar(filename));}

	/**\brief
	 * ��ʼ����
	 */
	BOOL Play(int start=0);

	/**\brief
	 * ֹͣ����
	 */
	BOOL Stop();

	/**\brief
	 * ��ͣ����
	 */
	BOOL Pause();

	/**\brief
	 * ��ͣ��������������
	 */
	BOOL Resume();

	/**\brief
	 * �Ƿ����ڲ���
	 */
	BOOL IsPlay();

	/**\brief
	 * �õ���ǰ���ֶ����ָ��
	 */
	static CMusic* GetSysMusic(){return m_pMusic;}

private:
	//�Ƿ�������
	static bool bMusic;

	//�������Ƿ��Ѵ���
	static bool bExist;
	
	//�Ƿ񲥷�
	static bool bPlay;
	static IDirectMusicPerformance* g_pPerf;
	static IDirectMusicLoader* g_pLoader;
	IDirectMusicSegment* g_pMIDISeg;

	//��ͣ��
	MUSIC_TIME PauseTime;

	//�ļ�
	WCHAR MusicFile[MAX_PATH];

	//! ����ָ��
	static CMusic* m_pMusic;

	static IDirectMusicPerformance* CreatePerformance(void);
	static IDirectMusicLoader* CreateLoader(void);
};

#endif