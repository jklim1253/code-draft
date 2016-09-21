#pragma once
#include "afxwin.h"

enum UI_BUTTON_STATE {
	UI_BST_NORMAL,
	UI_BST_HOVER,
	UI_BST_PRESSED,
	UI_BST_CLICKED,
	UI_BST_CHECKED
};

#define BS_ONOFFBUTTON 0x0000C000L

class CUIButton : public CButton {
public:
	CUIButton();
	~CUIButton();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();

public :
	void SetButtonState(int bs);
	int GetButtonState() const;

private :
	LOGFONT fontBasic;
	bool m_bMouseTracking;
	int m_buttonState;
public:
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
};

