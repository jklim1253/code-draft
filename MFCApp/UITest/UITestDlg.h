
// UITestDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "UIButton.h"


// CUITestDlg dialog
class CUITestDlg : public CDialogEx
{
// Construction
public:
	CUITestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UITEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CUIButton m_ctrlAddButton;
	CUIButton m_ctrlModifyButton;
	CUIButton m_ctrlRemoveButton;
	void UpdateLayout();
};
