//========================================================
/**
*  @file      SkyBox.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  �����
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef _SKY_BOX_H_
#define _SKY_BOX_H_

#include "camera.h"
#include "texture.h"


/**\brief
 * ��պ���
 */
class CSkyBox  
{
public:
	CSkyBox();
	~CSkyBox();

	BOOL Init();			//!< ��յĳ�ʼ��

	void Render();			//!< ��Ⱦ���


private:
	CTexture texture;		//!< �������

	float yrot;				//!< Χ��Y�����ת�Ƕ�

	vector3d m_sCameraPos;	//!< �������λ��
};

#endif