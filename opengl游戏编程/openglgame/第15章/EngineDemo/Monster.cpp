//========================================================
/**
*  @file      Monster.cpp
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ��Ϸ�еĹ���
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
#include "Monster.h"
#include "mmsystem.h"
#include "timer.h"
#include "inifile.h"

CMonster::CMonster()
{
	property = new SActiveObjPro;
	SActiveObjPro info;
	info.speed = 0.4f;
	info.vPosition.x = 80.0f;
	info.vPosition.y = 0.0f;
	info.vPosition.z = 250.0f;
	info.start_pos.x = 80.0f;
	info.start_pos.y = 250.0f;
	info.curr_pos = info.start_pos;
	info.t_add = 0.1f;
	info.object_state = STAND;
	info.curr_frame = STAND_START;
	info.next_frame = info.curr_frame + 1;
	info.yrot = 0.0f;
	info.t = 0.0f;
	info.m_sColor=SColor(1.f,1.f,1.f,1.f);
	info.life = 100;
	info.curr_life = 100;
	info.dist_min = 1000.0f;
	info.dist_max = 4000.0f;
	SetMonsterInfo(info);


	time_elapse = timeGetTime();
}


BOOL CMonster::Init(char *modelname,char *texturename,float scale,float h)
{
	if(!CActiveObj::Init(modelname,texturename,scale,h))return FALSE;

	if(!fireball.Init("data/star.bmp",4.0f))return FALSE;

    fireball.SetColor(0.0f , 1.0f , 1.0f);
	fireball.SetSpeed(property->speed*3 );

	return TRUE;
}


/**\brief
 * ��INI�ļ���ʼ��һ������
 */
BOOL CMonster::LoadIni(char* filename,char* index)
{
	CIniFile Ini(filename);

	SActiveObjPro info;
	info.speed		= PERSENT(Ini.ReadInt(index,"speed"));
	m_sPos.x= (float)Ini.ReadInt(index,"x");
	m_sPos.y= 0.0f;
	m_sPos.z= (float)Ini.ReadInt(index,"y");

	info.start_pos.x= m_sPos.x;
	info.start_pos.y= m_sPos.z;
	info.curr_pos	= info.start_pos;
	info.yrot		= (float)Ini.ReadInt(index,"direction");
	info.m_sColor	=SColor(1.f,1.f,1.f,1.f);
	info.life		= Ini.ReadInt(index,"life");
	info.curr_life	= info.life;
	info.shadow		= Ini.ReadInt(index,"Shadow");
	info.dist_min	= (float)Ini.ReadInt(index,"dist_min");
	info.dist_max	= (float)Ini.ReadInt(index,"dist_max");
	this->SetMonsterInfo(info);

	if(!this->Init(
			Ini.ReadText(index,"ModelFile"),Ini.ReadText(index,"TexFile"),
			PERSENT(Ini.ReadInt(index,"scale")),PERSENT(Ini.ReadInt(index,"h"))
		))return FALSE;

	return TRUE;
}


void CMonster::EndRender()
{
	vector3d v;
	vector2d orient1;
	float theta1 , theta2;
	if(property->object_state != DEATH)
	{
		///////////����ʱ���������ֵ����һ��������////////////
		static float dtime=0.f;
		dtime-=CTimer::GetSysTimer()->m_fTime;
		if(dtime<=0.f)
		{
			property->curr_life+=2;
			if(property->curr_life>=property->life)property->curr_life=property->life;
			dtime=1.5f;
		}

		ObjectInfo.GetRolePointer()->GetObjectPos(&v);
		v.y += 6.0f;
		float d = property->vPosition.dist_sqr(v);
		//�ù��������ɫ
		vector2d v2;
		v2.x = v.x;
		v2.y = v.z;

		//�������ֵ����0.5��������
		if(GetLife()>=0.5f)orient1 = v2 - property->curr_pos;
		else orient1=property->curr_pos-v2;

		orient1.normalize();
		theta1 = property->orient.getradian();
		theta2 = orient1.getradian();
		property->yrot += theta1 - theta2;
		if(property->yrot >=360.0f)property->yrot -= 360.0f;
		if(property->yrot <0.0f)property->yrot += 360.0f;
		property->orient = orient1;

		//����ɫ�ľ������dist_min����С��dist_maxʱ,����׷�Ͻ�ɫ
		if((d>property->dist_min&&d<property->dist_max)||(GetLife()<0.5f&&d<property->dist_max))
		{
			if(!fireball.isRun())
			{
				property->bArrive = FALSE;
				if(property->object_state != RUN)SetObjectState(RUN);
				property->start_pos = property->curr_pos;
				property->end_pos = property->start_pos + property->orient * (d-property->dist_min);
			}
		}
		else property->bArrive = TRUE;

		//����ɫ�ľ���С��dist_minʱ����
		if(d <= property->dist_min)
		{
			if(!fireball.isRun()&&property->bArrive&&ObjectInfo.GetRolePointer()->object_state != DEATH)
			{
				if(timeGetTime() - time_elapse > 1500)
				{
					time_elapse = timeGetTime();
					fireball.Set(property->vPosition,v);
				}
			}
		}

		if(fireball.isRun())fireball.Change(v);
		if(fireball.canReduceLife())
		{
			ObjectInfo.GetRolePointer()->ReduceLife(10);
			sound.LoadSoundFX("sound\\dead02.wav");
			sound.Play();
		}
	}
	CActiveObj::EndRender();
}


void CMonster::SetMonsterInfo(SActiveObjPro& info)
{
	memcpy(property,&info,sizeof(SActiveObjPro));
	ObjectInfo.PushMonster(property);
}


void CMonster::Render_Pick()
{
	property->t_add =CTimer::GetSysTimer()->m_fTime*12.f;

	glPushMatrix();
	glTranslatef(property->vPosition.x,property->vPosition.y,property->vPosition.z);
	glRotatef(property->yrot,0.0f,1.0f,0.0f);
	md2.RenderFrame(property->curr_frame,property->next_frame,property->t);
	glPopMatrix();
}


void CMonster::SetSpeed(float s)
{
	property->speed =s;
	fireball.SetSpeed(property->speed*4);
}
