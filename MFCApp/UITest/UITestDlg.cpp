
// UITestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UITest.h"
#include "UITestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUITestDlg dialog



CUITestDlg::CUITestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_UITEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUITestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADD, m_ctrlAddButton);
	DDX_Control(pDX, IDC_MODIFY, m_ctrlModifyButton);
	DDX_Control(pDX, IDC_REMOVE, m_ctrlRemoveButton);
}

BEGIN_MESSAGE_MAP(CUITestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CUITestDlg message handlers

BOOL CUITestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	this->UpdateLayout();
	m_ctrlRemoveButton.SetButtonStyle(BS_CHECKBOX);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUITestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUITestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUITestDlg::UpdateLayout()
{
	int nMargin = 5;
	int nButtonWidth = 0;
	int nButtonHeight = 0;
	CRect rc, rcLocal;
	GetClientRect(&rc);
	nButtonWidth = (rc.Width() - 2 * nMargin - 2 * nMargin) / 3;
	nButtonHeight = rc.Height() - 2 * nMargin;

	m_ctrlAddButton.MoveWindow(nMargin, nMargin, nButtonWidth, nButtonHeight);
	m_ctrlAddButton.GetWindowRect(&rcLocal);
	ScreenToClient(&rcLocal);

	m_ctrlModifyButton.MoveWindow(rcLocal.right + nMargin, rcLocal.top, nButtonWidth, nButtonHeight);
	m_ctrlModifyButton.GetWindowRect(&rcLocal);
	ScreenToClient(&rcLocal);

	m_ctrlRemoveButton.MoveWindow(rcLocal.right + nMargin, rcLocal.top, nButtonWidth, nButtonHeight);
	m_ctrlRemoveButton.GetWindowRect(&rcLocal);
	ScreenToClient(&rcLocal);

}
