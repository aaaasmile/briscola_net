/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Jörg König
// All rights reserved
//
// This file is part of the completely free tetris clone "CGTetris".
//
// This is free software.
// You may redistribute it by any means providing it is not sold for profit
// without the authors written consent.
//
// No warrantee of any kind, expressed or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc., and
// I'll try to keep a version up to date.  I can be reached as follows:
//    J.Koenig@adg.de                 (company site)
//    Joerg.Koenig@rhein-neckar.de    (private site)
/////////////////////////////////////////////////////////////////////////////


// BitmapDialog.h : main header file for the BITMAPDIALOG application
//

#if !defined(AFX_BITMAPDIALOG_H__55BE67E3_17E6_11D2_9AB8_0060B0CDC13E__INCLUDED_)
#define AFX_BITMAPDIALOG_H__55BE67E3_17E6_11D2_9AB8_0060B0CDC13E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpPalette 

class CDIBitmap
{
	friend class CBmpPalette;

	BITMAPINFO *	m_pInfo;
	BYTE *			m_pPixels;
	CBmpPalette *	m_pPal;
	BOOL			m_bIsPadded;

	public:		//constructors
		CDIBitmap();
		virtual ~CDIBitmap();

	private:
		CDIBitmap( const CDIBitmap& dbmp );

	public:		// attributes
		BITMAPINFO *	GetHeaderPtr() const;
		BYTE *			GetPixelPtr() const;
		RGBQUAD *		GetColorTablePtr() const;
		int				GetWidth() const;
		int				GetHeight() const;
		CBmpPalette *	GetPalette() { return m_pPal; }

	public:		// operations
		BOOL			CreatePalette();	// auto. made by "Load()" and "CreateFromBitmap()"
		void			ClearPalette();		// destroy the palette associated with this image
		BOOL			CreateFromBitmap( CDC *, CBitmap * );
		BOOL			LoadResource(LPCTSTR ID);
		BOOL			LoadResource(UINT ID) { return LoadResource(MAKEINTRESOURCE(ID)); }
		BOOL			LoadBitmap(UINT ID) { return LoadResource(ID); }
		BOOL			LoadBitmap(LPCTSTR ID) { return LoadResource(ID); }
		void			DestroyBitmap();
		BOOL			DeleteObject() { DestroyBitmap(); return TRUE; }
		
	public:		// overridables
			// draw the bitmap at the specified location
		virtual void	DrawDIB( CDC * pDC, int x=0, int y=0 );

			// draw the bitmap and stretch/compress it to the desired size
		virtual void	DrawDIB( CDC * pDC, int x, int y, int width, int height );

			// draw parts of the dib into a given area of the DC
		virtual int		DrawDIB( CDC * pDC, CRect & rectDC, CRect & rectDIB );

			// load a bitmap from disk
		virtual BOOL	Load( CFile * pFile );
		virtual BOOL	Load( const CString & );

			// save the bitmap to disk
		virtual BOOL	Save( CFile * pFile );
		virtual BOOL	Save( const CString & );

	protected:
		int				GetPalEntries() const;
		int				GetPalEntries( BITMAPINFOHEADER& infoHeader ) const;
		DWORD			GetBitsPerPixel() const;
		DWORD			LastByte( DWORD BitsPerPixel, DWORD PixelCount ) const;
		DWORD			GetBytesPerLine( DWORD BitsPerPixel, DWORD Width ) const;
		BOOL			PadBits();
		BOOL			UnPadBits();
		WORD			GetColorCount() const;
};

/////////////////////////////////////////////////////////////////////////////
// CBmpPalette 

class CBmpPalette : public CPalette
{
public:
    CBmpPalette( CDIBitmap* pBmp );
};


/////////////////////////////////////////////////////////////////////////////
// CBitmapDialog dialog

class CBitmapDialog : public CDialog
{
// Construction
public:
	CBitmapDialog(UINT uResourceID, CWnd* pParent = NULL);
	CBitmapDialog(LPCTSTR pszResourceID, CWnd* pParent = NULL);
	CBitmapDialog();

	enum {
		BITMAP_TILE = 0,		// tile the bitmap to fill the dialog
		BITMAP_STRETCH,			// stretch the bitmap so it fits to the dialog
		BITMAP_CENTER			// center the bitmap inside the dialog
	};


// Attributes
public:
	BOOL	SetBitmap(UINT uResource, int Type = CBitmapDialog::BITMAP_TILE);

// Dialog Data
protected:
	//{{AFX_DATA(CBitmapDialog)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
protected:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CDIBitmap	m_bmpBackground;
	int			m_nType;		// see enum above
	CBrush		m_HollowBrush;

	// Generated message map functions
	//{{AFX_MSG(CBitmapDialog)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void	CommonConstruct();
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPDIALOG_H__55BE67E3_17E6_11D2_9AB8_0060B0CDC13E__INCLUDED_)
