#if !defined(AFX_DLGCONTAYOURPOINTS_H__475DD3D5_F61F_4BE7_8FB2_D46D90BFA156__INCLUDED_)
#define AFX_DLGCONTAYOURPOINTS_H__475DD3D5_F61F_4BE7_8FB2_D46D90BFA156__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgContaYourPoints.h : header file
//

#include "cBriscolaGame.h"
#include "axcardBriscola.h"

/////////////////////////////////////////////////////////////////////////////
// DlgContaYourPoints dialog

class DlgContaYourPoints : public CDialog
{
// Construction
public:
	DlgContaYourPoints(CWnd* pParent = NULL);   // standard constructor

	//{{AFX_DATA(DlgContaYourPoints)
	enum { IDD = IDD_CONTAYOURPOINTS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

    //! button to previous card
    CButton  m_btUpCard;
    //! button to the next card
    CButton  m_btDownCard;
    //! button to the first card
    CButton  m_btDownFirst;
    //! button to the last card
    CButton  m_btUpEnd;
    //! control card to navigate points
	axcardBriscola  m_axCardPoints;
    //! tot points
    CStatic     m_lblNumOfPoints;
    //! tot cards taken
    CStatic     m_lblNuOfCards;


    //! set the mayzzo of taken cards
    void       SetMazzo(VCT_LONG& vc_Val){m_vct_MyCards = vc_Val;}
    //! set the total points taken
    void       SetTotPointsTaken(int iVal){m_iTotPoints = iVal;}


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgContaYourPoints)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgContaYourPoints)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtDownconta();
	afx_msg void OnBtUpconta();
	afx_msg void OnBtDowncontaF();
	afx_msg void OnBtUpconta0();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    void        showPos();

private:
    //! index of cards taken
    VCT_LONG      m_vct_MyCards;
    //! current position
    int           m_iMazzoPos;
    //! total number of cards
    int           m_iNumCards ;
    //! total points
    int           m_iTotPoints;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONTAYOURPOINTS_H__475DD3D5_F61F_4BE7_8FB2_D46D90BFA156__INCLUDED_)
