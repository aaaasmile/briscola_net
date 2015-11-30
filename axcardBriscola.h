//axcardBriscola.h

// file adapted from autogenerated. Reason i don't want fix clsid for create control.

#if !defined(AFX_AXJPGCARD_H__BA1E80B9_6EA0_406E_8B56_23DF85ABF25A__INCLUDED_)
#define AFX_AXJPGCARD_H__BA1E80B9_6EA0_406E_8B56_23DF85ABF25A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//! class axcardBriscola
/**
Class the used to create all cards control
*/
class axcardBriscola : public CWnd
{
protected:
	DECLARE_DYNCREATE(axcardBriscola)

public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x25763cce, 0x4c53, 0x11d5, { 0xa3, 0x1d, 0x0, 0xa0, 0xcc, 0x77, 0xe7, 0x9c } };
		return clsid;
	}
    //! create a control card
	BOOL Create( REFCLSID clsid,LPCTSTR lpszWindowName, DWORD dwStyle,
		         const RECT& rect,CWnd* pParentWnd, UINT nID);
	

    
// Attributes
public:

// Operations
public:
	void SetBackColor(unsigned long newValue);
	unsigned long GetBackColor();
	long GetCardIndex();
	void SetCardIndex(long nNewValue);
	tagCARDSHOWSTATUS* GetCardStatus();
	void               SetCardStatus(tagCARDSHOWSTATUS* newValue);
	long GetNumCardOnDeck();
	long GetSizeImageX();
	long GetSizeImageY();
	CString GetDeckName();
	void SetNumCardOnDeck(int num);

private:
    //! interface to cards methods
    IAxJpgCard*   m_pIAxCards;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AXJPGCARD_H__BA1E80B9_6EA0_406E_8B56_23DF85ABF25A__INCLUDED_)