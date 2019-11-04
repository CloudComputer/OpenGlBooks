#if !defined(AFX_CANVASFRAME_H__F888694D_7141_11D5_BD53_0050BAE96245__INCLUDED_)
#define AFX_CANVASFRAME_H__F888694D_7141_11D5_BD53_0050BAE96245__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// canvasFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// canvasFrame frame

class canvasFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(canvasFrame)
public:
	canvasFrame();           // protected constructor used by dynamic creation
	void CreateDDPla(int width,int height,char* filename,int num);
	void ColorKey(int num);
	void CreateDSBuf(char* filename,int num);
	void InitDD();
	void InitDS();
	void InitDI();
	void Playing();
	void Over();
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(canvasFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~canvasFrame();

	// Generated message map functions
	//{{AFX_MSG(canvasFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CANVASFRAME_H__F888694D_7141_11D5_BD53_0050BAE96245__INCLUDED_)
