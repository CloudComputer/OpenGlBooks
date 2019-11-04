//========================================================
/**
*  @file      ListView.h
*
*  ��Ŀ������ ������Ϸ����
*  �ļ�����:  �б����
*  ����ƽ̨�� Windows98/2000/NT/XP
*  
*  ���ߣ�     WWBOSS
*  �����ʼ�:  wwboss123@gmail.com
*  �������ڣ� 2007-07-26	
*  �޸����ڣ� 2007-07-26
*
*/ 
//========================================================

#ifndef _LIST_VIEW_H_
#define _LIST_VIEW_H_

#include "window.h"
#include "button.h"
#include "ScrollBar.h"
#include <vector>
using namespace std;

//! ÿ���б���ĸ߶�
#define ITEM_HEIGHT 20


/**\brief
 * ListView�б����
 */
class ListView : public CWindow
{
public:
	ListView(void);
	~ListView(void){}


	/**\brief
	 * ȡ�����ڵ�������
	 */
	unsigned int GetItemNum(){return m_vItems.size();}


	/**\brief
	 * ȡ�õ�ǰѡ��������
	 */
	unsigned int GetCurrItem(){return m_nCurrItem;}


	/**\brief
	 * ȡ���б����ϵ��ַ���
	 */
	char* GetItemText(unsigned int _nWhere);


	/**\brief
	 * ȡ�ñ߿���
	 */
	int GetBorderWidth(){return m_iBorderWidth;}


	/**\brief
	 * ���ñ߿���
	 */
	void SetBorderWidth(int _width){m_iBorderWidth=_width;}


	/**\brief
	 * ȡ���б������ɫ
	 */
	SColor GetItemColor(){return m_sItemColor;}


	/**\brief
	 * �����б�����ɫ
	 */
	void SetItemColor(SColor _color){m_sItemColor=_color;}


	/**\brief
	 * �����������ɫ����Insert֮ǰ���ô˺���
	 */
	void SetTextColor(SColor _color){m_sTextColor=_color;}


	/**\brief
	 * ����һ���б���
	 *
	 *\param	_iWhere	�����λ�ã�Ϊ-1ʱ�嵽��β
	 *\param	_str	�������ϵ�����
	 *\return	BOOL	�����Ƿ�ɹ�
	 */
	BOOL InsertItem(unsigned int _iWhere,char* _str);


	/**\brief 
	 * ɾ��һ���б��Ĭ�ϲ���-1ʱɾ����βԪ��
	 */
	BOOL DeleteItem(unsigned int _iWhere=-1);


	/**\brief
	 * ȡ�ù�������ָ��
	 */
	CScrollBar* GetScrollBar(){return &m_cScroll;}


private:
	//! �б�������
	vector<CButton> m_vItems;

	//! �ұߵĹ�����
	CScrollBar m_cScroll;

	//! �߿���
	int m_iBorderWidth;

	//! ��ǰѡ����
	unsigned int m_nCurrItem;

	//! ��ǰѡ�����ϵ��ַ���
	char* m_chCurrText;

	//! �б������ɫ
	SColor m_sItemColor;

	//! �������ɫ
	SColor m_sTextColor;

	/**\brief
	 * �����б�
	 */
	virtual void OnDraw(void);


	//--------------------------
	//����Ĳ���ֻ����ȾʱҪ�õ��м����

	//! ���ù���ʱ����ܷ��µ�����
	unsigned int m_nMaxItemNum;

	//! �б���Ŀ�
	int m_iItemWidth;

	//! �б����x
	int m_iItemX;

	//! ��һ���б����y
	int m_iFirstY;


};



#endif