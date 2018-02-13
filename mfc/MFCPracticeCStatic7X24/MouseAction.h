#if !defined(AFX_MOUSEACTION_H__E436F421_FABC_11D5_85B7_0060979DBC4B__INCLUDED_)
#define AFX_MOUSEACTION_H__E436F421_FABC_11D5_85B7_0060979DBC4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MouseAction.h : header file
//
// Code for Mouse Leave and Mouse Hover
// Hover code orginally based on CHoverButton by Niek Albers

/* Here you need to set up defines for baseclass so that when it is included
 in the proper header file, the correct class is used. This is only a problem 
 if you are using this as the base for multiple classes in the project.
 If you wanted both a button and an Edit control to be moveable at runtime then
 you would declared:
 #if defined(MYBUTTONCLASS)
 #define BASECLASS CButton
 #elif defined(MYEDITCLASS)
 #define BASECLASS CEdit
 #else
 #define BASECLASS CWnd
 #endif

  Then in your Button header file you would declare:
  #define MYBUTTONCLASS
  #include "mouseaction.h"

  and in the edit class:
  #define MYEDITCLASS
  #include "mouseaction.h"

  When the code compiles and is run, each class will be derived from the proper window and allow the moving
*/
#if defined(RPDBTN)
#define BASECLASS CButton
#elif defined(RPDSLID)
#define BASECLASS CSliderCtrl
#elif defined(RPDTEXT)
#define BASECLASS CStatic
#else
#define BASECLASS CWnd
#endif
/////////////////////////////////////////////////////////////////////////////
// CMouseAction window

class CMouseAction : public BASECLASS
{
// Construction
public:
	CMouseAction();
	DECLARE_SERIAL(CMouseAction)
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseAction)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMouseAction();
	BOOL IsTransparent() { return m_bTranparent; }
	void SetTransparent(BOOL bTransparent=TRUE) { m_bTranparent = bTransparent;	}
	BOOL IsHovering() { return m_bHover; }
	BOOL IsMoveable() { return m_bAllowMove; }
	void SetMoveable(BOOL moveAble = TRUE) { m_bAllowMove = moveAble; }
	void SetToolTipText(CString spText, BOOL bActivate = TRUE);
	void SetToolTipText(UINT nId, BOOL bActivate = TRUE);
	void DeleteToolTip();
	CString GetWindowName() { return  m_windowName;	}//These are strictly to allow easy identification during Serialization
	void SetWindowName(CString szName) { m_windowName = szName;	}

	// Generated message map functions
protected:
	BOOL m_bResizing;
	BOOL m_bTracking;
	BOOL m_bHover;
	BOOL m_bAllowMove;
	BOOL m_bTranparent;
	CPoint m_point;
	CRectTracker *m_track;
	CString m_windowName;
	void ActivateTooltip(BOOL bActivate = TRUE);
	CString m_tooltext;
	CToolTipCtrl* m_ToolTip;
	void InitToolTip();
	TCHAR *LongToStr(TCHAR *ch,long value)
	{
		_stprintf(ch,_T("%i"),value);
		return ch;
	}
	//{{AFX_MSG(CMouseAction)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam);
	afx_msg void OnRButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnMove(int x, int y);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSEACTION_H__E436F421_FABC_11D5_85B7_0060979DBC4B__INCLUDED_)
