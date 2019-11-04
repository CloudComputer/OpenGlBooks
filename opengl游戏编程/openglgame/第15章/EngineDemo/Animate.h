//========================================================
/**
*  @file      Animate.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  2Dƽ�涯����
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef _ANIMATE_H_
#define _ANIMATE_H_

#include "StdAfx.h"
#include "Texture.h"
#include "IniFile.h"


/**\brief
 * 2Dƽ�涯����
 */
class CAnimate  
{
public:
	//! ����֡��֮֡�����ʱ
	float	DeltaTime;

	//! ��ɫ
	SColor	color;

	//! ���ھ���
	SRect	rect;


	CAnimate();
	~CAnimate(){}


	/**\brief
	 * �Ƿ�͸������
	 */
	BOOL GetBlendState(){return bBlend;}


	/**\brief
	 * ��������
	 *
	 *\param	filename	�����ļ���
	 *\param	nFrameNum	��֡��
	 *\param	_bBlend		�Ƿ�͸������
	 *\return	BOOL		�Ƿ�ɹ���������
	 */
	BOOL LoadTexture(char* filename,int nFrameNum,BOOL _bBlend);


	/**\brief
	 * ͨ��INI�ļ���ʼ��
	 */
	virtual BOOL LoadIni(char* filename,char* index);
	

	/**\brief
	 * ��Ⱦ����
	 */
	void draw(void);


	/**\brief
	 * �ƶ�����
	 *
	 *\param	_dx	x��ƫ��
	 *\param	_dx	y��ƫ��
	 */
	void move(int _dx,int _dy){rect.x+=_dx;rect.y+=_dy;}



private:
	//! ������֡��
	unsigned int FrameNum;
	
	//! �Ƿ�͸������
	BOOL		bBlend;

	//! �������õ�����
	CTexture	texture;
	
	//! ���ڲ��ŵ�n֡����0��ʼ��
	unsigned int n;

	//! ��֡��ļ��ʱ��
	float		m_fDeltaTime;
};


#endif