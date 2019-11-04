//========================================================
/**
*  @file      GLFont.h
*
*  ��Ŀ������ OpenGL����
*  �ļ�����:  λͼ������  
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2006-09-13	
*  �޸����ڣ� 2006-11-21
*
*/     
//========================================================
#ifndef	__GLFONT_H__
#define	__GLFONT_H__


/** ����λͼ������ */
class GLFont															
{
public:
    
	/** ���캯������������ */
	GLFont();
	~GLFont();
    
	/** ��Ա���� */
	bool InitFont(HDC hDC, char *fontName,int Size );  /**< ��ʼ������ */
	void PrintText(char *string, float x, float y);    /**< ��λ��(x,y)�������ַ���string */
	void KillGLFont();                                 /**< ɾ������ */

protected:
	unsigned int listBase;                             /**< �����������ʾ�б�Ŀ�ʼλ�� */
	
};

#endif	// __GLFONT_H__