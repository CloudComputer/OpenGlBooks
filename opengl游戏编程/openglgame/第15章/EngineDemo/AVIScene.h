//========================================================
/**
*  @file      AVIScene.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��Ƶ���������ࡪ�������õ�Ƭͷ�����ͳ��䶯��
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef __AVI_SCENE_H__
#define __AVI_SCENE_H__

#include "iscene.h"
#include "aviplayer.h"
#include "input.h"

/**\brief
 * ��Ƶ����������
 */
class AVIScene : public IScene
{
public:
	AVIScene(void);
	~AVIScene(void);


	/**\brief
	 * �����ĳ�ʼ��
	 */
	BOOL Init(void);


	/**\brief
	 * ��INI�ļ���������
	 */
	BOOL LoadIni(char* _filename,char* _index);


	/**\brief
	 * ���³���������
	 */
	void UpdateData(void);


	/**\brief
	 * ��������Ⱦ
	 */
	void Render(void);


protected:
	//! AVI������
	AVIPlayer m_cAVI;

	//! Ҫ���ŵ�AVI�ļ���
	char* m_strAVIFile;
};


#endif