// appProc.h: interface for the appProc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPPROC_H__FE858DC1_2FD3_11D8_B47F_0002441FF68C__INCLUDED_)
#define AFX_APPPROC_H__FE858DC1_2FD3_11D8_B47F_0002441FF68C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class appProc  
{
public:
	virtual void Render();
	virtual void Run();

};

/*///////////////////////////////////////////



  �M�_�D���e



/*///////////////////////////////////////////
void appTreasureRun();
class appTreasure : public appProc  
{
public:
	void DrawText();
	void GetProp();
	void DrawProp();
	void AddObj();
	void Move();
	void Render();
	void Run();
};
/*///////////////////////////////////////////

  �ǳƶ}�l

/*///////////////////////////////////////////
void appTreasureStartRun();
class appTreasureStart : public appProc  
{
public:
	void Render();
	void Run();
};

/*///////////////////////////////////////////

  �C������

/*///////////////////////////////////////////
void appTreasureGameoverRun();
class appTreasureGameover : public appProc  
{
public:
	void Render();
	void Run();
};
/*///////////////////////////////////////////

  �򩳪���ŧi

/*///////////////////////////////////////////
class gameObj
{
public ://�ƧǦ�C
	gameObj * m_Exit ;//��C�U�@��
	gameObj * m_Next ;//��C�W�@��
public :
	float m_x , m_y , m_top ;
public :
	virtual void SortDraw();
	void AddSort();
};
/*///////////////////////////////////////////

  ������ƫŧi

/*///////////////////////////////////////////
//#include "myd3d.h"
class gameRole : public gameObj
{
private :
	int m_GridTime , m_GridNextTime ;//����ɶ�
	int m_Index ;//�ثe������
	int m_News ;//��V
public :
	d3dCartoon *m_Cartoon ;//�ʵe��
	int m_Alpha ;//�����C��
public :
	void SetCartoon( d3dCartoon * cartoon , int NextTime , int News );
	void Draw();
	void SortDraw();
};

#endif // !defined(AFX_APPPROC_H__FE858DC1_2FD3_11D8_B47F_0002441FF68C__INCLUDED_)
