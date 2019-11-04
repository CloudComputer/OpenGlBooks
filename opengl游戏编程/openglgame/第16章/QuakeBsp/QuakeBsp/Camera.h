//========================================================
/**
*  @file      Camera.h
*
*  ��Ŀ������ Quake���ڳ���ʵ��
*  �ļ�����:  �������  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-08-06	
*  �޸����ڣ� 2007-09-01
*
*/     
//========================================================
#ifndef _CAMERA_H
#define _CAMERA_H

/** ������� */
class CCamera {

public:

	CCamera();	

	///�����������Եķ���
	CVector3 Position() {	return m_vPosition;		}
	CVector3 View()		{	return m_vView;			}
	CVector3 UpVector() {	return m_vUpVector;		}
	CVector3 Strafe()	{	return m_vStrafe;		}

	/** ������������Եķ��� */
	void SetPosition(CVector3 vPosition)	{	m_vPosition = vPosition;	}
	void SetView(CVector3 vView)			{	m_vView = vView;			}
	void SetUpVector(CVector3 vUpVector)	{	m_vUpVector = vUpVector;	}
	
	/** ��������� */
	void PositionCamera(float positionX, float positionY, float positionZ,
			 		    float viewX,     float viewY,     float viewZ,
						float upVectorX, float upVectorY, float upVectorZ);

	/** ��ת����� */
	void RotateView(float angle, float X, float Y, float Z);

	/** ���������ת����� */
	void SetViewByMouse(); 

	void RotateAroundPoint(CVector3 vCenter, float X, float Y, float Z);

	/** �����ƶ������ */
	void StrafeCamera(float speed);

	/** ǰ���ƶ������ */
	void MoveCamera(float speed);

	/** �����̶��� */
	void CheckForMovement();

	/** ��������� */
	void Update();

	/** �����ӿ� */
	void Look();

private:

	/** �����λ�� */
	CVector3 m_vPosition;					

	/** ������ӵ� */
	CVector3 m_vView;						

	/** �������� */
	CVector3 m_vUpVector;		
	
	/** ƽ���� */
	CVector3 m_vStrafe;	
};

#endif
