
// MainAppDlg.h : header file
//

#pragma once

#include "ExRes.h"

// CMainAppDlg dialog
class CMainAppDlg : public CDialog
{
// Construction
public:
	CMainAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private :
	CBitmap bmpTest[3];

	ExResource res[2];
};
