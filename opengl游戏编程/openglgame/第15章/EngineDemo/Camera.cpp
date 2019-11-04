//========================================================
/**
*  @file      Camera.cpp
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


#include "stdafx.h"
#include "Camera.h"
#include "mathlib.h"
#include "role.h"


//! ����ʹ�õ��������ָ��
CCamera* CCamera::m_pCamera = NULL;


CCamera::CCamera(void):direction(0.0f),pitch(21.f),
				dist_to_role(80.0f),role_pos(vector3d(2.0f,0.4f,-0.5f))
{
	m_pCamera = this;
}



/**\brief
 * ��������Ĳ����������ŵ���ѭ����
 */
void CCamera::Update(void)
{
	if(CInput::GetSysInput()->GetMouse()->GetWheelState()>0)
	{
		pitch += 1.0f;
		//if(pitch>90.0f)	pitch=90.0f;
	}
	if(CInput::GetSysInput()->GetMouse()->GetWheelState()<0)
	{
		pitch -= 1.0f;
		//if(pitch<0.f)pitch=0.f;
	}

	SPoint2 p=SYS_MOUSE->GetMousePos();
	if(p.x <=5)
	{
		if(CRole::GetRolePointer()->IsArrive())direction+=1.0f;
	}

	if(p.x >=SYS_WIDTH-5)
	{
		if (CRole::GetRolePointer()->IsArrive())direction-=1.0f;
	}
	if(p.y>SYS_HEIGHT-5)
	{
		dist_to_role += 0.5f ;
		//if(dist_to_role>120.0f)dist_to_role=120.0f;
	}
	if(p.y<5)
	{
		dist_to_role -= 0.5f;
		//if(dist_to_role<80.0f)dist_to_role=80.0f;
	}

	role_pos=CRole::GetRolePointer()->GetPos();
	position = role_pos ;
	position.z += dist_to_role;
	position.y = role_pos.y+15.0f;

	FrameMove();
}


/**\brief
 * ���ñ�þ���
 */
void CCamera::FrameMove(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f,0.0f,-dist_to_role);
	glRotatef(pitch,1.0f,0.0f,0.f);
	glRotatef(direction,0.0f,1.0f,0.0f);

    glTranslatef(0.0f,0.0f,dist_to_role);

	glTranslatef(-position.x,-position.y,-position.z);
}

