#include "stdafx.h"
#include "UIButton.h"
#include <fstream>


CUIButton::CUIButton()
	: m_buttonState(UI_BST_NORMAL)
	, m_bMouseTracking(false)
{
}


CUIButton::~CUIButton()
{
}
BEGIN_MESSAGE_MAP(CUIButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_CREATE()
	ON_WM_PAINT()
//	ON_WM_DRAWITEM()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


void CUIButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bMouseTracking) {
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		tme.hwndTrack = this->GetSafeHwnd();
		tme.dwHoverTime = 1;
		::TrackMouseEvent(&tme);

		m_bMouseTracking = true;
	}

	CButton::OnMouseMove(nFlags, point);
}


void CUIButton::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default
	m_buttonState = UI_BST_NORMAL;
	if (GetCheck() == BST_CHECKED) {
		m_buttonState = UI_BST_CHECKED;
	}
	m_bMouseTracking = false;
	Invalidate();

	CButton::OnMouseLeave();
}


void CUIButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_buttonState = UI_BST_HOVER;
	m_bMouseTracking = false;
	Invalidate();

	CButton::OnMouseHover(nFlags, point);
}


int CUIButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.hwndTrack = this->GetSafeHwnd();
	tme.dwHoverTime = 1;
	::TrackMouseEvent(&tme);

	m_bMouseTracking = true;

	// load config file.
	std::fstream config;
	config.open(_T("font.config"), std::ios_base::in | std::ios_base::binary);
	if (!config.good()) {
		CFontDialog dlg;
		if (dlg.DoModal() == IDOK) {
			dlg.GetCurrentFont(&fontBasic);
		}
		else {
			this->GetFont()->GetLogFont(&fontBasic);
		}
	}
	else {
		config.read((char*)&fontBasic, sizeof(LOGFONT));
	}

	CFont font;
	font.CreateFontIndirect(&fontBasic);
	this->SetFont(&font);

	config.close();


	return 0;
}


void CUIButton::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CButton::OnPaint() for painting messages
	CString strButtonState, strText;
	LPTSTR szButtonState[] = {
		_T("NORMAL"),
		_T("HOVER"),
		_T("PRESSED"),
		_T("CLICKED"),
		_T("CHECKED"),
	};
	COLORREF clrButtonState[] = {
		RGB(255,255,255),
		RGB(200,200,200),
		RGB(210,100,50),
		RGB(10,200,150),
		RGB(100,100,150),
	};
	CRect rc;
	GetClientRect(&rc);

	CBrush whiteBrush(clrButtonState[m_buttonState]);
	dc.FillRect(&rc, &whiteBrush);

	CBrush blackBrush(RGB(200,200,200));
	dc.FrameRect(&rc, &blackBrush);

	GetWindowText(strText);
	strButtonState.Format(_T("%s (%s)"), strText, szButtonState[m_buttonState]);
	int nOldMode = dc.SetBkMode(TRANSPARENT);
	dc.DrawText(strButtonState, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	dc.SetBkMode(nOldMode);

}

void CUIButton::SetButtonState(int bs)
{
	m_buttonState = bs;
}

int CUIButton::GetButtonState() const
{
	return m_buttonState;
}

//void CUIButton::EnableOnOff(bool bEnable)
//{
//	m_bEnableOnOff = bEnable;
//}

//void CUIButton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
//{
//	// TODO: Add your message handler code here and/or call default
//	HDC hdc = lpDrawItemStruct->hDC;
//	CDC dc;
//	dc.Attach(hdc);
//
//	CString strButtonState, strText;
//	LPTSTR szButtonState[] = {
//		_T("NORMAL"),
//		_T("HOVER"),
//		_T("PRESSED"),
//		_T("CLICKED"),
//	};
//	CRect rc;
//	GetClientRect(&rc);
//	GetWindowText(strText);
//	strButtonState.Format(_T("%s (%s)"), strText, szButtonState[m_buttonState]);
//	dc.DrawText(strButtonState, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
//
//	dc.Detach();
//
//	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
//}


void CUIButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_buttonState = UI_BST_PRESSED;
	m_bMouseTracking = false;
	Invalidate();

	CButton::OnLButtonDown(nFlags, point);
}


void CUIButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_buttonState = UI_BST_CLICKED;

	m_bMouseTracking = false;
	Invalidate();

	CButton::OnLButtonUp(nFlags, point);
}


BOOL CUIButton::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: Add your specialized code here and/or call the base class

	return CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID);
}
