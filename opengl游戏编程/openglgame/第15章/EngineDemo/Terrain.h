//========================================================
/**
*  @file      Terrain.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  ������
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================



#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "texture.h"
#include "camera.h"


/**\brief
 * ������
 */
class CTerrain
{
public:
	CTerrain();
	~CTerrain(){delete [] heightMap; }
	
	BOOL Init(int _width,char* TexFile);
	BOOL Load(char* filename);

	static CTerrain* GetSysTerrain(){return m_pTerrain;}
	
	/**\brief
	 * ȡ�õ��εĿ�
	 */
	int GetWidth(){return m_nWidth;}

	int GetCellWidth(){return m_nCellWidth;}

	void Render(void);

	float GetHeight(float x, float z);

private:
	//! ���δ�СΪm_iWidth*m_iWidth�������2^n
	unsigned int m_nWidth;

	//! ��̬�߳�ӳ��
	short*        heightMap;      

	//! ÿ�����ӵĿ��
	unsigned int m_nCellWidth;

	// �����ϵĶ�������
	CTexture terrainTex;

	// �����ɫ
	float fogColor[4];

	float scanDepth;
	
	static CTerrain* m_pTerrain;
};


#endif