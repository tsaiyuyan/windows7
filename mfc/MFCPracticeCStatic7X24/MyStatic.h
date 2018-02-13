#if !defined(AFX_MOUSEACTION_H__E436F421_FABC_11D5_85B7_0060979DBC4B__INCLUDED_)
#define AFX_MOUSEACTION_H__E436F421_FABC_11D5_85B7_0060979DBC4B__INCLUDED_

#pragma once

#include "CCMemDC.h"
#define BASECLASS CStatic

/////////////////////////////////////////////////////////////////////////////
// CMouseAction window

class CMyStatic : public CStatic
{
// Construction
public:
	CMyStatic();
	DECLARE_DYNAMIC(CMyStatic)
// Attributes
public:
	bool lbtn_down_flag;
	int old_x;
	int old_y;
	static const int devide_h = 7;
	static const int devide_w = 24;
	bool data7x24[devide_h][devide_w];
	void LButtonDo(CPoint point);
	
	
	




// Operations
public:

// Implementation
public:
	virtual ~CMyStatic();
	
	void SetTransparent(BOOL bTransparent=TRUE) { m_bTranparent = bTransparent;	}
	BOOL IsHovering() { return m_bHover; }
	BOOL IsMoveable() { return m_bAllowMove; }
	void SetMoveable(BOOL moveAble = TRUE) { m_bAllowMove = moveAble; }
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
	afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnMove(int x, int y);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	//}}AFX_MSG
	void OnDraw(CDC* pDC) ;
	DECLARE_MESSAGE_MAP()
};


#endif 
