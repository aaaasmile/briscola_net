// AxJpgCard.h : Declaration of the CAxJpgCard

#ifndef __AXJPGCARD_H_
#define __AXJPGCARD_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "AX_jpg_ServerCP.h"

enum
{
    e_BmW = 156,
    e_BmH = 300,
    e_OverLine = 2,
    CS_MAXINDEX = 42,
    CS_MAXDECK = 40,
};

struct DIBINFO : public BITMAPINFO
{
	RGBQUAD	 arColors[255];    // Color table info - adds an extra 255 entries to palette

	operator LPBITMAPINFO()          { return (LPBITMAPINFO) this; }
	operator LPBITMAPINFOHEADER()    { return &bmiHeader;          }
	RGBQUAD* ColorTable()            { return bmiColors;           }
};

struct PALETTEINFO : public LOGPALETTE
{
    PALETTEENTRY arPalEntries[255];               // Palette entries

    PALETTEINFO() { palVersion = (WORD) 0x300; }

    operator LPLOGPALETTE()   { return (LPLOGPALETTE) this;            }
    operator LPPALETTEENTRY() { return (LPPALETTEENTRY) (palPalEntry); }
};

/////////////////////////////////////////////////////////////////////////////
// CAxJpgCard
class ATL_NO_VTABLE CAxJpgCard : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CAxJpgCard, IAxJpgCard, &IID_IAxJpgCard, &LIBID_AX_JPG_SERVERLib>,
	public CComControl<CAxJpgCard>,
	public IPersistStreamInitImpl<CAxJpgCard>,
	public IOleControlImpl<CAxJpgCard>,
	public IOleObjectImpl<CAxJpgCard>,
	public IOleInPlaceActiveObjectImpl<CAxJpgCard>,
	public IViewObjectExImpl<CAxJpgCard>,
	public IOleInPlaceObjectWindowlessImpl<CAxJpgCard>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CAxJpgCard>,
	public IPersistStorageImpl<CAxJpgCard>,
	public ISpecifyPropertyPagesImpl<CAxJpgCard>,
	public IQuickActivateImpl<CAxJpgCard>,
	public IDataObjectImpl<CAxJpgCard>,
	public IProvideClassInfo2Impl<&CLSID_AxJpgCard, &DIID__IAxJpgCardEvents, &LIBID_AX_JPG_SERVERLib>,
	public IPropertyNotifySinkCP<CAxJpgCard>,
	public CComCoClass<CAxJpgCard, &CLSID_AxJpgCard>,
	public CProxy_IAxJpgCardEvents< CAxJpgCard >,
	public CProxy_IAxJpgCardEventsVtbl< CAxJpgCard >
{
public:
	CAxJpgCard();
	
DECLARE_REGISTRY_RESOURCEID(IDR_AXJPGCARD)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAxJpgCard)
	COM_INTERFACE_ENTRY(IAxJpgCard)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CAxJpgCard)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CAxJpgCard)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IAxJpgCardEvents)
	CONNECTION_POINT_ENTRY(IID__IAxJpgCardEventsVtbl)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CAxJpgCard)
	CHAIN_MSG_MAP(CComControl<CAxJpgCard>)
	DEFAULT_REFLECTION_HANDLER()
    MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
    MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

    STDMETHOD(get_CardStatus)(/*[out, retval]*/ LP_CARDSHOWSTATUS pVal);
	STDMETHOD(put_CardStatus)(/*[in]*/ LP_CARDSHOWSTATUS pVal);
	STDMETHOD(get_CardIndex)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_CardIndex)(/*[in]*/ long newVal);

	HRESULT OnDraw(ATL_DRAWINFO& di);
	
	OLE_COLOR   m_clrBorderColor;
	BOOL        m_bBorderVisible;

public:
	STDMETHOD(get_DeckName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_SizeImageY)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_SizeImageY)(/*[in]*/ long newVal);
	STDMETHOD(get_SizeImageX)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_SizeImageX)(/*[in]*/ long newVal);
	STDMETHOD(get_NumCardOnDeck)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_NumCardOnDeck)(/*[in]*/ long newVal);
    static PALETTEENTRY ms_StdColours[];

private:
    LRESULT     OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT     OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
    HRESULT Init();
    BOOL    DrawRotated(RECT &rc, HDC hdcDST, HDC hdcSRC);
    BOOL    AnimateToBlack(RECT &rc, HDC hdcDST, HDC hdcSRC);
    BOOL    DrawOriginalColors(RECT &rc, HDC hdcDST, HDC hdcSRC);
    BOOL    DrawEmpty(RECT &rc, HDC hdcDST, HDC hdcSRC);
    BOOL    DrawNormal(RECT &rc, HDC hdcDST, HDC hdcSRC);
    BOOL    DrawInvisibile(RECT &rc, HDC hdcDST, HDC hdcSRC);
    BOOL    DrawRender(RECT &rc, HDC hdcDST, HDC hdcSRC);
    BOOL    DrawAsMazzo(RECT &rc, HDC hdcDST, HDC hdcSRC);
    int     BytesPerLine(int nWidth, int nBitsPerPixel);
    BOOL    CreateDib(HDC hdcSRC);
    BOOL    CreateHalftonePalette(DIBINFO &DIBinfo, int nNumColours);
    BOOL    DrawSelected(RECT &rc, HDC hdcDST, HDC hdcSRC,int iTypeSel);
private:
    //!actual mazzo index card
    long                m_lCardIndex;
    //! handle toi the active picture
    LPPICTURE           m_hCurrentImage;
    //! bitmap size
    SIZE                m_lSizeBitmap; 
    //! back color
    OLE_COLOR           m_clrBckColor;
    //! colors of the card
    RGBQUAD             m_pColors[256];
    //! card control status
    CARDSHOWSTATUS      m_eCardStatus;
    //! old card status to handle transactionstatus
    CARDSHOWSTATUS      m_eOldStatus;
    //! flag to know of the current image already have a rotation
    bool                m_bCreatedRot;
    //! image rect
    RECT                m_rc;
    //! current bitmap
    HBITMAP             m_hCurrentBitmap;
    //! number of cards as mazzo
    long                m_lNumMazzoItems;
    
};

#endif //__AXJPGCARD_H_
