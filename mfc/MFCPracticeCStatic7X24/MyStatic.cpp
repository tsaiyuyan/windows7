// MouseAction.cpp : implementation file
//

#include "stdafx.h"
#include "MyStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyStatic
IMPLEMENT_DYNAMIC(CMyStatic,BASECLASS)

CMyStatic::CMyStatic()
{
	m_bResizing = FALSE;
	m_bTranparent = FALSE;
	m_bHover = FALSE;
	m_bTracking = FALSE;
	m_bAllowMove = TRUE;
	m_windowName = _T("");
	m_track = NULL;
	
	lbtn_down_flag = false;
	memset(data7x24,0,sizeof(data7x24));

}


CMyStatic::~CMyStatic()
{
	
}

BEGIN_MESSAGE_MAP(CMyStatic, BASECLASS)
	//{{AFX_MSG_MAP(CMyStatic)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOVE()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyStatic message handlers


LRESULT CMyStatic::OnMouseHover(WPARAM wparam, LPARAM lparam) 
{
	if (!m_bHover)
	{
		//ShowWindow(SW_HIDE);
		BASECLASS::Invalidate();
		//ShowWindow(SW_SHOW);
	}
	m_bHover=TRUE;
	/* This line corrects a problem with the tooltips not displaying when 
	the mouse passes over them, if the parent window has not been clicked yet.
	Normally this isn't an issue, but when developing multi-windowed apps, this 
	bug would appear. Setting the ActiveWindow to the parent is a solution to that.
	*/
	::SetActiveWindow(GetParent()->GetSafeHwnd());

	
	return 0;
}

LRESULT CMyStatic::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bTracking = FALSE;
	m_bHover=FALSE;
	RedrawWindow();

	lbtn_down_flag = false;
	Invalidate();
	return 0;
}

void CMyStatic::OnRButtonDown( UINT nFlags, CPoint point )
{
	if ((IsMoveable() == TRUE) && (m_bResizing == FALSE)) // Are we allowed to resize the window?
	{
		m_bResizing = TRUE;
		m_point = point;
		CRect rect;
		BOOL bSuccess = FALSE;
		GetClientRect(rect);//Tell the tracker where we are
		m_track = new CRectTracker(&rect, CRectTracker::dottedLine | 
								CRectTracker::resizeInside |
								CRectTracker::hatchedBorder);
		if (nFlags & MK_CONTROL) // If Ctrl + Right-Click then Resize object
		{
			GetWindowRect(rect);
			GetParent()->ScreenToClient(&rect);
			bSuccess = m_track->TrackRubberBand(GetParent(),rect.TopLeft());//Let user resize window
			m_track->m_rect.NormalizeRect();
		}
		else // If not Ctrl + Right-Click, then Move Object
		{
			bSuccess = m_track->Track(GetParent(), point);//Let user move window
		}
		if (bSuccess)
		{
			rect = LPRECT(m_track->m_rect);
			//ClientToScreen(&rect);
			//GetParent()->ScreenToClient(&rect);
			//SetWindowPos(&wndTopMost,rect.left,rect.top,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
			MoveWindow(rect.left,rect.top,rect.Width(),rect.Height(),TRUE);//Move Window to our new position
		}
		delete m_track;
		m_track = NULL;
		rect = NULL;
		m_bResizing = FALSE;
	}
	BASECLASS::OnRButtonDown(nFlags,point);
}

void CMyStatic::LButtonDo( CPoint point)
{
	CRect m_rect;
	GetClientRect(&m_rect);	
	int cx = m_rect.Width()/devide_w;
	int cy = m_rect.Height ()/devide_h;

	int x_count = 0;
	int y_count = 0;
		
	while(x_count * cx < point.x - cx)
	{		
		x_count++;
	}

	while(y_count * cy < point.y - cy)
	{
		y_count++;
	}


	if((old_x!=x_count || old_y!=y_count) && (y_count < devide_h && x_count < devide_w))
	{
		if(data7x24[y_count][x_count]) 
			data7x24[y_count][x_count] = false;
		else
			data7x24[y_count][x_count] = true;
	
		old_x = x_count;
		old_y = y_count;
		Invalidate();			
	}

}
void CMyStatic::OnLButtonDown( UINT nFlags, CPoint point )
{
	lbtn_down_flag = true;
	old_x = -1;
	old_y = -1;

	LButtonDo(point);
	BASECLASS::OnLButtonDown(nFlags,point);
}

void CMyStatic::OnLButtonUp( UINT nFlags, CPoint point )
{
	lbtn_down_flag = false;
	Invalidate();

	BASECLASS::OnLButtonDown(nFlags,point);
}
void CMyStatic::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme); //Tell Windows that we want to process all mouse Hover and Leave Messages
		m_point = point;
	}
	if(lbtn_down_flag)
	{
		LButtonDo(point);
		//TRACE(L"mousemove x = %d,y = %d ,x_count = %d ,y_count =%d\n",old_x,old_y,x_count,y_count);
	}
	BASECLASS::OnMouseMove(nFlags,point);
}


void CMyStatic::OnMove(int x, int y) 
{
	BASECLASS::OnMove(x, y);
	
	// This code is so that when a transparent control is moved
	// and the dialog or app window behind the transparent control
	// is showing a bitmap, this forces the parent to redraw
	// before we redraw so that the bitmap is shown properly
	// and also eliminates any window overlapping that may occur with
	// using a Transparent Window on top of a Bitmap...
	// If you are not using a transparent window, you shouldn't need this...
	
	ShowWindow(SW_HIDE);// Hide Window
	CRect rect;
	GetWindowRect(&rect);
	GetParent()->ScreenToClient(&rect);
	GetParent()->InvalidateRect(&rect);//Tell Parent to redraw the rect
	ShowWindow(SW_SHOW);//Now redraw us so that Control displays correctly
}


HBRUSH CMyStatic::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = NULL;
	
	if (m_bTranparent)
	{
		pDC->SetBkMode(TRANSPARENT);//Set transparent background
		LOGBRUSH brush;
		brush.lbColor = HOLLOW_BRUSH;
		brush.lbHatch = 0;
		brush.lbStyle = 0;
		hbr = CreateBrushIndirect(&brush);//Use a transparent brush for painting
	}
	else
		hbr = BASECLASS::OnCtlColor(pDC, pWnd, nCtlColor);//Else use default
	return hbr;
}


void CMyStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);
	int nWidth = rect.Width();
	int nHeight = rect.Height(); 
	
	//memdc 兩種使用方法

	//方法1、使用MSDN內建的CMemDC
	CMemDC dc2(dc, &rect);
	CDC& dcMem = dc2.GetDC();
	//CDC* pDC = &memDC.GetDC(); 

	//方法2、使用網路流傳內建的CMemDC 因為會跟MSDN衝突 所以改名為CCMemDC
	//CCMemDC dcMem(&dc,&rect);
	
	int cx = nWidth/devide_w;
	int cy = nHeight/devide_h;

	CPen pen(PS_SOLID,1,RGB(255,255,255));
	CPen *oldpen = dcMem.SelectObject(&pen);
	
	// First let the control do its default drawing.
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)dcMem.m_hDC, 0 );

	dcMem.FillSolidRect(0,0,nWidth-(nWidth%devide_w),nHeight-(nHeight%devide_h),RGB(0,255,0));
	int i,j;
	
	for( i = 0 ;i<devide_h;i++)
	{
		for( j = 0 ;j<devide_w;j++)
		{
			int x,y;
			x = 0+cx*j;
			y = 0+cy*i;
			if(data7x24[i][j])
				dcMem.FillSolidRect(x,y,cx,cy,RGB(255,0,0));
			
		}
	}

	//draw line
	for(i = 0 ;i < devide_h ;i++)
	{
		dcMem.MoveTo(0,i*cy);
		dcMem.LineTo(nWidth,i*cy);
	}

	for(i = 0 ;i< devide_w ;i++)
	{
		dcMem.MoveTo(i*cx,0);
		dcMem.LineTo(i*cx,nHeight);
	}

	dcMem.SelectObject(oldpen);

	CBrush StaticBrush;
	CPen StaticPen;
	StaticBrush.CreateStockObject(HOLLOW_BRUSH);
	StaticPen.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));

	const wchar_t str = ' ';
	CSize size = dcMem.GetTextExtent(&str,1);
	CRect m_textrect = rect;

	CFont m_font;
	if (!(HFONT)m_font)
	{
		// first time init: create font
		LOGFONT lf;
		GetFont()->GetObject(sizeof(lf), &lf);
		m_font.CreateFontIndirect(&lf);
	}
	dcMem.SelectObject(&m_font);

	{
		int y = (rect.bottom / size.cy);
		{
			dcMem.SetBkMode(TRANSPARENT);
			dcMem.SetTextColor(RGB(255, 255, 255));
			if (m_bHover)
				dcMem.SetTextColor(RGB(255, 0, 0));
			dcMem.SelectObject(&StaticBrush);
			dcMem.SelectObject(&StaticPen);
			{
				m_textrect.bottom = size.cy;
				m_textrect.top = m_textrect.bottom-size.cy;
				CString szStr;
				GetWindowText(szStr);
				dcMem.ExtTextOut(0, m_textrect.top,ETO_CLIPPED,&m_textrect,szStr,NULL);
			}
		}
	}

	// Do not call CMouseAction::OnPaint() for painting messages

}
