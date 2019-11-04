//=========================================================================
/**
*  @file      CollideDemo.h
*
*  ��Ŀ������ ��ײ�����ʾ
*  �ļ�����:  ����ʵ���� 
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-10-10
*
*  ����������������������¼����麯��
*																								
*	virtual bool Init();														
*		ִ�����еĳ�ʼ������������ɹ���������true							
*																			
*	virtual void Uninit();													
*		ִ�����е�ж�ع���										
*																			
*	virtual void Update(DWORD milliseconds);										
*		ִ�����еĸ��²���������Ĳ���Ϊ���β���������ʱ�䣬�Ժ���Ϊ��λ
*																			
*	virtual void Draw();															
*		ִ�����еĻ��Ʋ���
*/
//=========================================================================

#ifndef __DEMO_H__
#define __DEMO_H__

#include "stdafx.h"
#include "GLFrame.h"												/**< ���������Ŀ���� */
#include "Input.h"
#include "Font.h"
#include "Vector.h"
#include "BMPLoader.h"
#include "Tray.h"


/** ƽ��ṹ */
struct Plane
{
	Vector3 _Position;
	Vector3 _Normal;
};
                                         
/** Բ���ṹ */
struct Cylinder
{                          
	Vector3 _Position;
    Vector3 _Axis;
    double _Radius;
};
                                          
/** ��ը�ṹ */
struct Explosion
{
	Vector3 _Position;
	float   _Alpha;
	float   _Scale;
};



/** ��GL_Application������һ������ */
class CDemo : GLApplication								
{
public:
	bool	Init();								    /**< ��ʼ������ */
	void	Uninit();								/**< ж�ع��� */
	void	Update(DWORD milliseconds);				/**< ���²��� */
	void	Draw();									/**< ���Ʋ��� */

	void    CaculateFrameRate();                    /**< ����֡�� */
	void    PrintText();                            /**< ���������Ϣ */

	void    InitVars();                             /**< ��ʼ������ */
	bool    LoadTexture();                          /**< �������� */

	/** �����ƽ���Ƿ���ײ */
	int TestIntersionPlane(const Plane& plane,const Vector3& position,
		                   const Vector3& direction, double& lamda, 
						   Vector3& pNormal);
    
	/** ����Ƿ���Բ������ײ */
	int TestIntersionCylinder(const Cylinder& cylinder,const Vector3& position,
		                      const Vector3& direction, double& lamda, 
							  Vector3& pNormal,Vector3& newposition);
    
	/** �ҵ����������ڵ�ǰʱ��Ƭ����ײ�� */
	int FindBallCol(Vector3& point, double& TimePoint, double Time2, 
		            int& BallNr1, int& BallNr2);
  
	/** ��Ҫ�Ĵ������ */
	void    Process();      
	
private:
	friend class GLApplication;				   /**< ����Ϊ����һ����Ԫ�� */
	CDemo(const char * class_name);			   /**< ���캯�� */
   
	/** �û��Զ���ĳ������ */
	CInputSystem*  m_pInput;                   /**< ����ϵͳ */
    CBMPLoader     m_texture[4];               /**< �������� */
	GLUquadricObj  *cylinder_obj;              /**< ʹ�ö��μ�������ȾԲ�� */
	GLuint         dlist;                      /**< ������ʾ�б� */
	Plane          pl1,pl2,pl3,pl4,pl5;        /**< �����5��ƽ�� */
    Cylinder       cyl1,cyl2,cyl3;             /**< 3��Բ�� */
    Explosion      ExplosionArray[20];         /**< ���汬ըЧ�� */
 	GLFont         m_Font;                     /**< ������ */
  	float          m_Fps;                      /**< ֡�� */
	      
};


#endif	// __DEMO_H__