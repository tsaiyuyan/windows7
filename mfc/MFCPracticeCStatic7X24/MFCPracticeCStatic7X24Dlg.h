
// MFCPracticeCStatic7X24Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "MyStatic.h"

// CMFCPracticeCStatic7X24Dlg dialog
class CMFCPracticeCStatic7X24Dlg : public CDialogEx
{
// Construction
public:
	CMFCPracticeCStatic7X24Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCPRACTICECSTATIC7X24_DIALOG };

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
public:
	CMyStatic m_Static7X24;
	afx_msg void OnStnClickedStatic7x24();
};
