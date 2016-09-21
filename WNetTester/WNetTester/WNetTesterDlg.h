
// WNetTesterDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "WNetWrapper.h"


// CWNetTesterDlg dialog
class CWNetTesterDlg : public CDialogEx
{
// Construction
public:
	CWNetTesterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WNETTESTER_DIALOG };
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
public:
	CButton m_ctrlBrowserButton;
	CEdit m_ctrlValueEdit;
	CListCtrl m_ctrlInfoList;

private :
	WNetWrapper wnet;
public:
	afx_msg void OnBnClickedBrowser();
};
