#if !defined(AFX_CONVEDIT_H__8222A5D1_443B_40F4_B959_4A52D5D63143__INCLUDED_)
#define AFX_CONVEDIT_H__8222A5D1_443B_40F4_B959_4A52D5D63143__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConvEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConvEdit window

class CConvEdit : public CEdit
{
// Construction
public:
	CConvEdit();

// Attributes
public:

// Operations
public:
	CBrush Brush;
	CFont Font;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConvEdit)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConvEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CConvEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVEDIT_H__8222A5D1_443B_40F4_B959_4A52D5D63143__INCLUDED_)
