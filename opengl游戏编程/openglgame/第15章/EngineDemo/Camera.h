//========================================================
/**
*  @file      Camera.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  �������
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================


#ifndef _CAMERA_H__
#define _CAMERA_H__

#include "input.h"


/**\brief
 * �������
 */
class CCamera
{
public:
	CCamera(void);
	~CCamera(void){}


	/**\brief
	 * �����ת�Ƕ�
	 */
	float GetDir(void){return direction;}


	/**\brief
	 * ������
	 */
	float GetPitch(void){return pitch;}


	/**\brief
	 * ����������Ӣ�۵ľ���
	 */
	float GetViewDistance(void){return dist_to_role;}
	
	
	/**\brief
	 * ����������λ��
	 */
	void GetCameraPos(vector3d *pVector){*pVector=position;}


	/**\brief
	 * ����������Ӣ�۵ľ���
	 */
	float GetDestToRole(){return dist_to_role;}


	/**\brief
	 * ���ñ�þ���
	 */
	void FrameMove(void);


	/**\brief
	 * ��������Ĳ����������ŵ���ѭ����
	 */
	void Update(void);
	
	
	/**\brief
	 * ��õ�ǰ�������ָ��
	 */
	static CCamera* GetCameraPointer(void){return m_pCamera;}



private:
	//! �����õ��������ָ��
	static CCamera *m_pCamera;

	//! ��Ӣ�۵ľ���
	float dist_to_role;

	//! �������λ��
	vector3d position;

	//! Ӣ�۵�λ��
	vector3d role_pos;

	//! ��ת�Ƕ�
	float direction;
	
	//! ��б
	float pitch;

};



#endif