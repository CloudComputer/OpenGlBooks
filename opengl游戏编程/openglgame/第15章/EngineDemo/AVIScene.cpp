//========================================================
/**
*  @file      AVIScene.cpp
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

#include "stdafx.h"
#include "aviscene.h"
#include "inifile.h"

AVIScene::AVIScene(void):m_strAVIFile(NULL)
{
}

AVIScene::~AVIScene(void)
{
	m_cAVI.Stop();
	_DELETE(m_strAVIFile);
}


/**\brief
 * �����ĳ�ʼ��
 */
BOOL AVIScene::Init(void)
{
	if(!m_cAVI.Init(CInput::GetSysHWnd()))return FALSE;

	return TRUE;
}


/**\brief
 * ��INI�ļ���������
 */
BOOL AVIScene::LoadIni(char* _filename,char* _index)
{
	CIniFile Ini(_filename);
	m_strAVIFile=Ini.ReadText(_index,"AVIFile");

	return TRUE;
}


/**\brief
 * ���³�������
 */
void AVIScene::UpdateData(void)
{
}


/**\brief
 * ��������Ⱦ
 */
void AVIScene::Render(void)
{
	if(!m_strAVIFile)return;

	m_cAVI.Load(m_strAVIFile);
	m_cAVI.Play();
	if(SYS_KEYBOARD->KeyDown(DIK_ESCAPE)||SYS_MOUSE->ButtonDown(1))m_cAVI.Stop();

}
