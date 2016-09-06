
// MainAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MainApp.h"
#include "MainAppDlg.h"
#include "afxdialogex.h"
#include <sstream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _UNICODE
#define tostringstream wostringstream
#define tstring wstring
#else
#define tostringstream ostringstream
#define tstring string
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMainAppDlg dialog



CMainAppDlg::CMainAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAINAPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainAppDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMainAppDlg message handlers

BOOL CMainAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	res[0].open(_T("ResourceOnly.dll"));
	res[1].open(_T("ResDll.dll"));

	bmpTest[0].Attach(res[0].getBitmap(100));
	bmpTest[1].Attach(res[1].getBitmap(101));
	bmpTest[2].Attach(res[0].getBitmap(101));


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainAppDlg::OnPaint()
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
		{
			CPaintDC client(this);

			CDC dc;
			dc.CreateCompatibleDC(&client);

			CBitmap* bmpOld = dc.SelectObject(&bmpTest[0]);
			client.BitBlt(100, 0, 100, 100, &dc, 100, 0, SRCCOPY);
			dc.SelectObject(bmpOld);

			bmpOld = dc.SelectObject(&bmpTest[1]);
			client.BitBlt(0, 0, 100, 100, &dc, 0, 0, SRCCOPY);
			dc.SelectObject(bmpOld);

			bmpOld = dc.SelectObject(&bmpTest[2]);
			client.BitBlt(0, 0, 100, 100, &dc, 0, 0, SRCCOPY);
			dc.SelectObject(bmpOld);

			CRect rc;
			GetClientRect(&rc);
			client.DrawText(_T("HEllo"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}

	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

