//========================================================
/**
*  @file      MapView.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  С��ͼ
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef __MAP_VIEW_H__
#define __MAP_VIEW_H__

#include "window.h"
#include "texture.h"
#include "MonstersMgr.h"
#include "role.h"

/**\brief
 * С��ͼ��
 */
class MapView : public CWindow
{
public:
	MapView(void);
	~MapView(void);

	/**\brief
	 * ��INI�ļ�����С��ͼ����
	 */
	BOOL LoadIni(char* _filename,char* _index);





private:
	/**\brief
	 * С��ͼ�Ļ���
	 */
	void OnDraw(void);
};


#endif