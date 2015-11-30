#if !defined(AFX_INSERTNAME_DLG_H__EF9C22A0_ED14_469D_A5E7_DDE67F2103EB__INCLUDED_)
#define AFX_INSERTNAME_DLG_H__EF9C22A0_ED14_469D_A5E7_DDE67F2103EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsertName_Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// InsertName_Dlg dialog

class InsertName_Dlg : public CDialog
{
// Construction
public:
	InsertName_Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(InsertName_Dlg)
	enum { IDD = IDD_PLAYERNAME };
	CString	m_strPlayerName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(InsertName_Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(InsertName_Dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSERTNAME_DLG_H__EF9C22A0_ED14_469D_A5E7_DDE67F2103EB__INCLUDED_)
