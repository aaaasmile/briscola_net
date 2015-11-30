// AxJpgCard.cpp : Implementation of CAxJpgCard

#include "stdafx.h"
#include "AX_jpg_Server.h"
#include "AxJpgCard.h"

#define HIMETRIC_INCH	2540

/////////////////////////////////////////////////////////////////////////////
// CAxJpgCard

extern LPPICTURE g_ImageHandle[CS_MAXINDEX];



// Standard colours
PALETTEENTRY CAxJpgCard::ms_StdColours[] = {
    { 0x00, 0x00, 0x00, 0 },    // First 2 will be palette for monochrome bitmaps
    { 0xFF, 0xFF, 0xFF, 0 },
    
    { 0x00, 0x00, 0xFF, 0 },    // First 16 will be palette for 16 colour bitmaps
    { 0x00, 0xFF, 0x00, 0 },
    { 0x00, 0xFF, 0xFF, 0 },
    { 0xFF, 0x00, 0x00, 0 },
    { 0xFF, 0x00, 0xFF, 0 },
    { 0xFF, 0xFF, 0x00, 0 },
    
    { 0x00, 0x00, 0x80, 0 },
    { 0x00, 0x80, 0x00, 0 },
    { 0x00, 0x80, 0x80, 0 },
    { 0x80, 0x00, 0x00, 0 },
    { 0x80, 0x00, 0x80, 0 },
    { 0x80, 0x80, 0x00, 0 },
    { 0x80, 0x80, 0x80, 0 },
    
    { 0xC0, 0xC0, 0xC0, 0 },
};

////////////////////////////////////////
//       CAxJpgCard
/*! Constructor
*/
CAxJpgCard::CAxJpgCard(): m_lCardIndex(0),
                          m_lNumMazzoItems(33)
{
    m_hCurrentImage = g_ImageHandle[m_lCardIndex];
    OLE_HANDLE hOleHandle;
    m_hCurrentImage->get_Handle(&hOleHandle);  
    m_hCurrentBitmap = (HBITMAP)hOleHandle;
    m_clrBckColor = 0;
    m_bCreatedRot = false;
    
    m_eCardStatus = CSW_ST_DRAWFIRST;
    m_eOldStatus = CSW_ST_DRAWFIRST;
}


STDMETHODIMP CAxJpgCard::InterfaceSupportsErrorInfo(REFIID riid)
{
    static const IID* arr[] = 
    {
        &IID_IAxJpgCard,
    };
    for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
    {
        if (InlineIsEqualGUID(*arr[i], riid))
            return S_OK;
    }
    return S_FALSE;
}


//////////////////////////////////////////////////////////////////
//   Get and put methods
/////////////////////////////////
STDMETHODIMP CAxJpgCard::get_CardIndex(long *pVal)
{
    if (pVal == NULL)
        return E_FAIL;
    
    *pVal = m_lCardIndex;
    
    return S_OK;
}


////////////////////////////////////////
//       put_CardIndex
/*! New Index for bitmap  card
// \param long newVal : 
*/
STDMETHODIMP CAxJpgCard::put_CardIndex(long newVal)
{
    if (newVal >= 0 && newVal < CS_MAXINDEX)
    {
        m_lCardIndex = newVal;
        m_hCurrentImage = g_ImageHandle[m_lCardIndex];
        OLE_HANDLE hOleHandle;
        m_hCurrentImage->get_Handle(&hOleHandle);  
        m_hCurrentBitmap = (HBITMAP)hOleHandle;
        _ASSERT(m_hCurrentImage != 0);
        FireViewChange();
        
    }
    
    return S_OK;
}


////////////////////////////////////////
//       get_CardStatus
/*! Return the control status
// \param LP_CARDSHOWSTATUS pVal : 
*/
STDMETHODIMP CAxJpgCard::get_CardStatus(LP_CARDSHOWSTATUS pVal)
{
    
    if (pVal != NULL)
    {
        *pVal = m_eCardStatus;
        return S_OK;
    }
    return E_INVALIDARG;
}


////////////////////////////////////////
//       put_CardStatus
/*! Add a new status
// \param LP_CARDSHOWSTATUS pVal : 
*/
STDMETHODIMP CAxJpgCard::put_CardStatus(LP_CARDSHOWSTATUS pVal)
{
    if (pVal != NULL)
    {
        m_eCardStatus = *pVal;
        m_bCreatedRot = false;
        if (m_eOldStatus == CSW_ST_INVISIBLE)
        {
                            // control was hidden, restore it
            DoVerbShow(&m_rc, m_hWnd);
            
        }
        FireViewChange();
    }
    return S_OK;
}


////////////////////////////////////////////////////////////////

HRESULT CAxJpgCard::Init()
{
    
    
    return S_OK;
}

////////////////////////////////////////
//       OnDraw
/*! Draw current selected card
// \param ATL_DRAWINFO& di : 
*/
HRESULT CAxJpgCard::OnDraw(ATL_DRAWINFO& di)
{
    
    RECT& rc = *(RECT*)di.prcBounds;
    
    HDC hdcComp = CreateCompatibleDC(di.hdcDraw);
    
    short iType;
    m_hCurrentImage->get_Type(&iType);
    ATLASSERT(iType == PICTYPE_BITMAP);
    
    //CreateDib(hdcComp);
    
    //SelectObject(hdcComp, (HBITMAP)m_hCurrentImage);
    SelectObject(hdcComp, m_hCurrentBitmap);
    
    
                            // draw a contour rectangle
    if (m_eCardStatus != CSW_ST_MAZZO)
        Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
    
    rc.left += e_OverLine;
    rc.right -= e_OverLine;
    rc.top += e_OverLine;
    rc.bottom -= e_OverLine;
    
    m_rc = rc;
    
    switch (m_eCardStatus)
    {
    case CSW_ST_DRAWFIRST:
        // first draw
        GetDIBColorTable(hdcComp, 0,  256, m_pColors );
        
        //DrawEmpty(rc, di.hdcDraw, hdcComp);
        //m_eCardStatus = CSW_ST_EMPTY;
        
        DrawNormal(rc, di.hdcDraw, hdcComp);
        m_eCardStatus = CSW_ST_DRAWNORMAL;
        //DrawAsMazzo(rc, di.hdcDraw, hdcComp);
        //m_eCardStatus = CSW_ST_MAZZO;

        //DrawRotated(rc, di.hdcDraw, hdcComp);
        //m_eCardStatus = CSW_ST_ROTATE90;
        
        //::OutputDebugString("Draw First\n");
        break;
    case CSW_ST_MAZZO:
        // deck draw (mazzo)
        DrawAsMazzo(rc, di.hdcDraw, hdcComp);
        //::OutputDebugString("Draw Mazzo\n");
        
    case CSW_ST_DRAWNORMAL:
        // usual draw
        DrawNormal(rc, di.hdcDraw, hdcComp);
        //::OutputDebugString("Draw Normal\n");
        break;
        
    case CSW_ST_ANIMATETOBLACK:
        // animate bitmap color to black
        AnimateToBlack(rc, di.hdcDraw, hdcComp);
        m_eCardStatus = CSW_ST_EMPTY;
        //::OutputDebugString("Animate to black\n");
        break;
        
    case CSW_ST_INVISIBLE:
        DrawInvisibile(rc, di.hdcDraw, hdcComp);
        m_eOldStatus = CSW_ST_INVISIBLE;
        //::OutputDebugString("Control invisible\n");
        break;
        
    case CSW_ST_ROTATE90:
        DrawRotated(rc, di.hdcDraw, hdcComp);
        //::OutputDebugString("Draw rotate 90\n");
        break;
        
    case CSW_ST_EMPTY:
        DrawEmpty(rc, di.hdcDraw, hdcComp);
        //::OutputDebugString("Draw Empty\n");
        break;
        
    case CSW_ST_RESTORE:
        DrawOriginalColors(rc, di.hdcDraw, hdcComp);
        m_eCardStatus = CSW_ST_DRAWNORMAL;
        //::OutputDebugString("Draw restore\n");
        break;

    case CSW_ST_SELECTED1:
        DrawSelected(rc, di.hdcDraw, hdcComp,1);
        m_eCardStatus = CSW_ST_SELECTED1;
        break;

    case CSW_ST_SELECTED2:
        DrawSelected(rc, di.hdcDraw, hdcComp,2);
        m_eCardStatus = CSW_ST_SELECTED2;
        break;

        
    default:
        _ASSERT(0);
        
        
    }
    
    
    
    DeleteDC(hdcComp);
    
    
    return S_OK;
}


////////////////////////////////////////
//       DrawInvisibile
/*! Hide the control
// \param RECT &rc : 
// \param HDC hdcDST : 
// \param HDC hdcSRC : 
*/
BOOL CAxJpgCard::DrawInvisibile(RECT &rc, HDC hdcDST, HDC hdcSRC)
{

    DoVerbHide(&rc, m_hWnd);
    
    return true;
}


////////////////////////////////////////
//       CreateDib
/*! Create a DIB from current bitmap
// \param HDC hdcSRC : 
*/
BOOL CAxJpgCard::CreateDib(HDC hdcSRC)
{
    BITMAP        bm;
    UINT          iColorDataType;   // color data type (palette or RGB values)
    ::GetObject( m_hCurrentBitmap, sizeof(bm), (LPVOID)&bm );
    
    HDC hdcComp = CreateCompatibleDC(hdcSRC);
    
    iColorDataType = DIB_RGB_COLORS;
    
    // create a DIB
    DIBINFO DIBinfo;
    BITMAPINFOHEADER& bih = DIBinfo.bmiHeader;
    bih.biSize          = sizeof(BITMAPINFOHEADER);
    bih.biWidth         = bm.bmWidth ; 
    bih.biHeight        = bm.bmHeight;
    bih.biPlanes        = 1;                // Must always be 1 according to docs
    bih.biBitCount      = bm.bmBitsPixel;
    bih.biCompression   = BI_RGB;
    bih.biSizeImage     = BytesPerLine(bm.bmHeight, bm.bmBitsPixel) * bm.bmWidth;
    bih.biXPelsPerMeter = 0;
    bih.biYPelsPerMeter = 0;
    bih.biClrUsed       = 0;
    bih.biClrImportant  = 0;
    
    if (!::GetDIBits(hdcComp, m_hCurrentBitmap, 0, bm.bmHeight, NULL, DIBinfo, iColorDataType))
    {
        ATLTRACE("Unable to GetDIBits\n");
    }
    
    BYTE* pvBitsSRC = (BYTE*)bm.bmBits;
    BYTE* pvBitsDST = NULL;
    
    
    
    // create dib for rotated image with bitmap set to all null
    HBITMAP hCurrentDib = ::CreateDIBSection(hdcComp , (const BITMAPINFO*) DIBinfo, DIB_RGB_COLORS, (VOID**)&pvBitsDST, NULL, 0);
    ATLASSERT( hCurrentDib != NULL);
    
    DWORD dwImageSize = DIBinfo.bmiHeader.biSizeImage;
    if (dwImageSize == 0)
    {
        int nBytesPerLine = BytesPerLine(DIBinfo.bmiHeader.biWidth, 
            DIBinfo.bmiHeader.biBitCount);
        dwImageSize = nBytesPerLine * DIBinfo.bmiHeader.biHeight;
    }
    
    
    CreateHalftonePalette(DIBinfo, 256);
    
    m_hCurrentBitmap = hCurrentDib;
    
    //memcpy(pvBitsDST, pvBitsSRC, dwImageSize);
    
    
    return TRUE;
}


////////////////////////////////////////
//       CreateHalftonePalette
/*! 
// \param PALETTEENTRY& palette : 
// \param int nNumColours : 
*/
BOOL CAxJpgCard::CreateHalftonePalette(DIBINFO &DIBinfo, int nNumColours)
{
    
    int nNumStandardColours = sizeof(ms_StdColours) / sizeof(ms_StdColours[0]);
    int nIndex = 0;
    int nNumEntries = nNumColours;
    if (nNumEntries <= 0 || nNumEntries > 256)
        nNumEntries = 256;
    
    PALETTEINFO PalInfo;                   
    PalInfo.palNumEntries = (WORD) nNumEntries;
    
    // The standard colours (16)
    for (int i = 0; i < nNumStandardColours; i++)
    {
        if (nIndex >= nNumEntries) break;
        memcpy( &(PalInfo.palPalEntry[nIndex]), &(ms_StdColours[i]), sizeof(PALETTEENTRY) );
        nIndex++;
    }
    
    // A colour cube (6 divisions = 216)
    for (int blue = 0; blue <= 5; blue++)
        for (int green = 0; green <= 5; green++)
            for (int red = 0; red <= 5; red++)
            {
                if (nIndex >= nNumEntries)
                    break;
                
                PalInfo.palPalEntry[nIndex].peRed   = (BYTE) ((red*255)/5);
                PalInfo.palPalEntry[nIndex].peGreen = (BYTE) ((green*255)/5);
                PalInfo.palPalEntry[nIndex].peBlue  = (BYTE) ((blue*255)/5);
                PalInfo.palPalEntry[nIndex].peFlags = 0;
                nIndex++;
            }
            
            // A grey scale (24 divisions)
            for (int grey = 0; grey <= 23; grey++)
            {
                if (nIndex >= nNumEntries) 
                    break;
                
                PalInfo.palPalEntry[nIndex].peRed   = (BYTE) (grey*255/23);
                PalInfo.palPalEntry[nIndex].peGreen = (BYTE) (grey*255/23);
                PalInfo.palPalEntry[nIndex].peBlue  = (BYTE) (grey*255/23);
                PalInfo.palPalEntry[nIndex].peFlags = 0;
                nIndex++;
            }
            
            for (int i = 0; i < nNumColours; i++)
            {
                // palette = (LPLOGPALETTE) PalInfo;
                DIBinfo.bmiColors[i].rgbBlue = PalInfo.palPalEntry[i].peBlue;  
                DIBinfo.bmiColors[i].rgbGreen = PalInfo.palPalEntry[i].peGreen; 
                DIBinfo.bmiColors[i].rgbRed = PalInfo.palPalEntry[i].peRed; 
            }
            
            return TRUE;
}

////////////////////////////////////////
//       DrawRotated
/*! Rotate the current Dib on 90. At the first time a new dib is created an rotation is performed
    Attention: this function is not valid for 256 colors because no palette is loaded.
    OleLoadPicture make a bitmap and map each color on sistem color. For sistem with 256 colors or
    minor a palette is needed
// \param RECT &rc : 
// \param HDC hdcDST : 
// \param HDC hdcSRC : 
*/
BOOL CAxJpgCard::DrawRotated(RECT &rc, HDC hdcDST, HDC hdcSRC)
{
    
    BITMAP        bm;
    UINT          iColorDataType;   // color data type (palette or RGB values)
    
    if (!m_bCreatedRot)
    {
        // create a new rotated dib
        
        // bitmap pointer
        ::GetObject( m_hCurrentBitmap, sizeof(bm), (LPVOID)&bm );
        
        // by LoadImage if create Dib is done, the pointer of the Bits is bm.Bits
        
        HDC hdcComp = CreateCompatibleDC(hdcSRC);
        
        iColorDataType = DIB_RGB_COLORS;
        
        // create rotated DIB
        DIBINFO DIBinfo;
        BITMAPINFOHEADER& bih = DIBinfo.bmiHeader;
        bih.biSize          = sizeof(BITMAPINFOHEADER);
        bih.biWidth         = bm.bmHeight; 
        bih.biHeight        = bm.bmWidth ;
        bih.biPlanes        = 1;                // Must always be 1 according to docs
        bih.biBitCount      = bm.bmBitsPixel;
        bih.biCompression   = BI_RGB;
        bih.biSizeImage     = BytesPerLine(bm.bmHeight, bm.bmBitsPixel) * bm.bmWidth;
        bih.biXPelsPerMeter = 0;
        bih.biYPelsPerMeter = 0;
        bih.biClrUsed       = 0;
        bih.biClrImportant  = 0;
        
        //CDIBSectionLite Myth;
        //Myth.SetBitmap(m_hCurrentImage,NULL);
        
        // calls GetDIBits with NULL bits pointer to fill in the BITMAPINFOHEADER data
        // This filled DIBinfo is used to create the rotated DIB. We need this call because
        // we have no color information
        if (!::GetDIBits(hdcComp, m_hCurrentBitmap, 0, bm.bmHeight, NULL, DIBinfo, iColorDataType))
        {
            ATLTRACE("Unable to GetDIBits\n");
        }
        
        // invert width and height, invert now otherwise GetDIBits fail
        
        // source bitmap is very easy to retrive and this is a DIB bitmap, not a DDB
        BYTE* pvBitsSRC = (BYTE*)bm.bmBits;
        BYTE* pvBitsDST = NULL;
        
        
        // create dib for rotated image with bitmap set to all null
        HBITMAP hRotated = ::CreateDIBSection(hdcComp , (const BITMAPINFO*) DIBinfo, DIB_RGB_COLORS, (VOID**)&pvBitsDST, NULL, 0);
        ATLASSERT( hRotated != NULL);
        
        // copy the buffer
        int iBytePerLineDST = BytesPerLine(bm.bmHeight, bm.bmBitsPixel);
        int iBytePerLineSRC = BytesPerLine(bm.bmWidth, bm.bmBitsPixel);
        int iIndexDST = 0;
        int iIndexSRC = 0;
        int iIndexSRCNext = 0;
        int iIndexDSTNext = 0;
        int iWidthDST = bm.bmHeight;
        int iHeightDST = bm.bmWidth;
        int iWidthSRC = bm.bmWidth ;
        int iheightSRC = bm.bmHeight ;
        int iBitFactor = bm.bmBitsPixel / 8;
        
        // rotation on 90° on clock direction
        for (int i = 0; i < iheightSRC; i ++ )
        {
            iIndexDST = i * iBitFactor + iBytePerLineDST * (iWidthSRC - 1);
            iIndexSRC = i * iBytePerLineSRC;
            for (int j = 0; j < iWidthSRC; j ++)
            {
                
                iIndexDSTNext = iIndexDST + 1; 
                
                iIndexSRCNext = iIndexSRC + 1;
                if (iBitFactor > 2)
                {
                            // true color
                    int iDST3 = iIndexDSTNext + 1;
                    int iSRC3 = iIndexSRCNext + 1;
                    pvBitsDST[iDST3] = pvBitsSRC[iSRC3];
                }
                
                ATLASSERT(iIndexDST >= 0);
                pvBitsDST[iIndexDST] = pvBitsSRC[iIndexSRC];
                pvBitsDST[iIndexDSTNext] = pvBitsSRC[iIndexSRCNext];

                iIndexDST -= iBytePerLineDST ;
                iIndexSRC += iBitFactor;
                
            }
        }
        
        
        // set the current image to rotated image
        m_hCurrentBitmap = hRotated;
        
        SelectObject(hdcComp, m_hCurrentBitmap);
        
        SetStretchBltMode(hdcDST, COLORONCOLOR);
        
        // blit the image
        StretchBlt(hdcDST, rc.left, rc.top, (rc.right - rc.left) , (rc.bottom - rc.top), 
            hdcComp, 0,0,  e_BmH,e_BmW, SRCCOPY );
        
        DeleteDC(hdcComp);
        
        m_bCreatedRot = true;
    }
    else
    {
        SetStretchBltMode(hdcDST, COLORONCOLOR);
        // image is already created, only stretch on display
        StretchBlt(hdcDST, rc.left, rc.top, (rc.right - rc.left) , (rc.bottom - rc.top), 
            hdcSRC, 0,0,  e_BmH, e_BmW, SRCCOPY );
    }
    
    
    return TRUE;
}


////////////////////////////////////////
//       BytesPerLine
/*! 
// \param int nWidth : 
// \param int nBitsPerPixel : 
*/
int CAxJpgCard::BytesPerLine(int nWidth, int nBitsPerPixel)
{
    int nBytesPerLine = nWidth * nBitsPerPixel;
    nBytesPerLine = ( (nBytesPerLine + 31) & (~31) ) / 8;
    
    return nBytesPerLine;
}


////////////////////////////////////////
//       DrawEmpty
/*! Draw an empty card, only contour
// \param RECT &rc : 
// \param HDC hdcDST : 
// \param HDC hdcSRC : 
*/
BOOL CAxJpgCard::DrawEmpty(RECT &rc, HDC hdcDST, HDC hdcSRC)
{
    if ( m_clrBckColor == 0)
        GetAmbientBackColor( m_clrBckColor ); 
    
    LOGBRUSH logBrush;
    logBrush.lbStyle = BS_HOLLOW;


    HBRUSH hBrushBck = CreateSolidBrush(m_clrBckColor);
    //HBRUSH hBrushBck = CreateBrushIndirect(&logBrush);
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdcDST, hBrushBck);
    
    // draw a empty rectangle
    FillRect(hdcDST, &rc, hBrushBck);
    
    SelectObject(hdcDST, hOldBrush);
    DeleteObject(hBrushBck);
    
    return TRUE;
}


////////////////////////////////////////
//       DrawNormal
/*! Draw the bitmap on the current status
// \param RECT &rc : 
// \param HDC hdcDST : 
// \param HDC hdcSRC : 
*/
BOOL CAxJpgCard::DrawNormal(RECT &rc, HDC hdcDST, HDC hdcSRC)
{
    SetStretchBltMode(hdcDST, COLORONCOLOR);
    
    HRESULT hrP = NULL;
    
    
    
    StretchBlt(hdcDST, rc.left, rc.top, (rc.right - rc.left) , (rc.bottom - rc.top), 
        hdcSRC, 0,0, e_BmW, e_BmH, SRCCOPY );
    
    
    return TRUE;
}


////////////////////////////////////////
//       DrawSelected
/*! Draw card with highlighted countor to indicate selection
// \param RECT &rc : 
// \param HDC hdcDST : 
// \param HDC hdcSRC : 
*/
BOOL CAxJpgCard::DrawSelected(RECT &rc, HDC hdcDST, HDC hdcSRC, int iTypeSel)
{
    SetStretchBltMode(hdcDST, COLORONCOLOR);
    
    HRESULT hrP = NULL;
    
    HPEN hPenSel;
    if (iTypeSel == 1)
    {
        hPenSel = ::CreatePen(PS_SOLID, 3, RGB(250, 2, 2));
    }
    else
    {
        hPenSel = ::CreatePen(PS_SOLID, 3, RGB(255, 255, 0));
    }
    HPEN hOldPen = (HPEN)::SelectObject(hdcDST, hPenSel);
    Rectangle(hdcDST, rc.left, rc.top, rc.right, rc.bottom);
    ::SelectObject(hdcDST, hOldPen);
    ::DeleteObject(hPenSel);
    
    rc.left += e_OverLine;
    rc.right -= e_OverLine;
    rc.top += e_OverLine;
    rc.bottom -= e_OverLine;
    
    
    StretchBlt(hdcDST, rc.left, rc.top, (rc.right - rc.left) , (rc.bottom - rc.top), 
        hdcSRC, 0,0, e_BmW, e_BmH, SRCCOPY );
    
    
    return TRUE;
}


////////////////////////////////////////
//          DrawAsMazzo
/*! draw the card control as mazzo
// \param RECT &rc : 
// \param HDC hdcDST : 
// \param HDC hdcSRC : 
*/
BOOL CAxJpgCard::DrawAsMazzo(RECT &rc, HDC hdcDST, HDC hdcSRC)
{
    SetStretchBltMode(hdcDST, COLORONCOLOR);
    
    HRESULT hrP = NULL;

    RECT rc1 = rc;

    rc1.left -= e_OverLine;
    rc1.right += e_OverLine;
    rc1.top -= e_OverLine;
    rc1.bottom += e_OverLine;

                            // draws background
    DrawEmpty(rc1, hdcDST, NULL);
    
    int iOffset = 10; 
   
                            // draws cards lines
    int iXold = rc.right;
    int iXnew = iXold - iOffset;
    int iYold = rc.top;
    int iYnew = rc.top + iOffset;
    int iLineHeight = (rc.bottom - rc.top)- iOffset; 
    int iLineStepV = iXold - iXnew;
    int iLineWidth = 2;
    int iNumLinVert = iLineStepV / iLineWidth;
    if ( iLineStepV <= 2)
        iNumLinVert = 0;

    if ( m_lNumMazzoItems <= 2)
    {
        iNumLinVert = 0;
    }
    else if ( m_lNumMazzoItems <= 4)
    {
        iNumLinVert = 2;
    }
    else if ( m_lNumMazzoItems <= 6)
    {
        iNumLinVert = 3;
    }
    else if ( m_lNumMazzoItems <= 8)
    {
        iNumLinVert = 4;
    }
    else 
    {
        iNumLinVert = 5;
    }


                            // tan(pi/4)
                            // neg because x grow, y small
    double dm = - 0.854; 
    double db = iYold - dm * iXold;

    HPEN pen_black = CreatePen(PS_SOLID, 0, RGB(0,0,0));
    HPEN pen_old = (HPEN)SelectObject(hdcDST, pen_black);   

                            //draw vertical lines
    for (int i = iNumLinVert - 1; i >= 0; i--)
    {
        int iX1 = iXold - iLineWidth * i;
        int iX2 = iX1;
        double dY1 = iX1 * dm + db;
        int iY1 = (int)dY1;
        int iY2 = iY1 + iLineHeight;

        MoveToEx(hdcDST, iX1, iY1, NULL);
        LineTo(hdcDST, iX2, iY2);
      
    }

                            // draw horizontal lines
    int iLineStepH = iYnew - iYold;
    //int iNumLinHor = iLineStepH / iLineWidth;
    int iNumLinHor = iNumLinVert;
    int iLineYwidth = (rc.right - rc.left) - iOffset; ;

    for (int i = iNumLinHor - 1; i >= 0; i--)
    {
        int iY1 = iYold + i * iLineWidth;
        int iY2 = iY1;
        
        double dX1 = (iY1 - db) / dm;
        int iX1 = (int)dX1;
        int iX2 = iX1 - iLineYwidth ;
        
        MoveToEx(hdcDST, iX1, iY1, NULL);
        LineTo(hdcDST, iX2, iY2);
      
    }

    SelectObject(hdcDST, pen_old); 
    DeleteObject(pen_black);

                            // draw deck bitmap
    rc.top  += iLineWidth * iNumLinHor ;
    rc.right  -= iLineWidth * iNumLinVert;

    Rectangle(hdcDST, rc.left, rc.top, rc.right, rc.bottom);

    rc.left += e_OverLine;
    rc.right -= e_OverLine;
    rc.top += e_OverLine;
    rc.bottom -= e_OverLine;
    
    StretchBlt(hdcDST, rc.left, rc.top, (rc.right - rc.left) , (rc.bottom - rc.top), 
        hdcSRC, 0,0, e_BmW, e_BmH, SRCCOPY );
    
    return TRUE;
}



////////////////////////////////////////
//       DrawRender
/*! use render funtion to show the picture
// \param RECT &rc : 
// \param HDC hdcDST : 
// \param HDC hdcSRC : 
*/
BOOL CAxJpgCard::DrawRender(RECT &rc, HDC hdcDST, HDC hdcSRC)
{
    //Get width and height of picture
    
    long hmWidth  = 0;
    long hmHeight = 0;
    
    HRESULT hrP;
    
    m_hCurrentImage->get_Width (&hmWidth);
    m_hCurrentImage->get_Height(&hmHeight);
    
    
    //Use to get height and width for display
    int nWidth = rc.right - rc.left ;
    int nHeight= rc.bottom - rc.top ;
    
    // render normal size (with no rotation)
    hrP = m_hCurrentImage->Render(hdcDST, rc.left, rc.bottom , nWidth,-nHeight,0,0, hmWidth, hmHeight, &rc);
    // render upside down
    //hrP = m_hCurrentImage->Render(hdcDST, rc.right  , rc.top , -nWidth, nHeight, 0, 0, hmWidth, hmHeight, &rc);
    
    
    
    if (SUCCEEDED(hrP))
        return TRUE;
    
    return FALSE;
    
}

////////////////////////////////////////
//       AnimateToBlack
/*! Change the color of the bitmap to blend to dark
*/
BOOL CAxJpgCard::AnimateToBlack(RECT &rc, HDC hdcDST, HDC hdcSRC)
{
    RGBQUAD pColors[256];
    
    for (int i = 0; i < 256; i++)
    {
        pColors[i].rgbBlue = m_pColors[i].rgbBlue;
        pColors[i].rgbGreen = m_pColors[i].rgbGreen;
        pColors[i].rgbRed = m_pColors[i].rgbRed;
    }
    
    
    BYTE byReduct = 5;
    for (int j = 0; j < 50; j++)
    {
        StretchBlt(hdcDST, rc.left, rc.top, (rc.right - rc.left) , (rc.bottom - rc.top), hdcSRC, 0,0, e_BmW, e_BmH, SRCCOPY );
        
        for (int i = 0; i < 256; i++)
        {
            (pColors[i].rgbBlue > byReduct) ? pColors[i].rgbBlue -= byReduct : 0;
            (pColors[i].rgbGreen > byReduct) ? pColors[i].rgbGreen -= byReduct : 0;
            (pColors[i].rgbRed > byReduct) ? pColors[i].rgbRed -= byReduct : 0;
            
        }
        int a = SetDIBColorTable(hdcSRC, 0, 256, pColors );
        
        Sleep(5);
    }
    
    /*
    char szMsg[1024];
    
      for (i = 0; i < 256; i++)
      {
      ::sprintf(szMsg, _T("pColors[%d].Blue = %d, Green = %d, Red = %d \n"), i, pColors[i].rgbBlue, pColors[i].rgbGreen, pColors[i].rgbRed );
      ::OutputDebugString(szMsg);
      }
    */
    
    return TRUE;
    
}


////////////////////////////////////////
//       DrawOriginalColors
/*! Restore original palette and draw bitmap
// \param RECT &rc : 
// \param HDC hdcDST : 
// \param HDC hdcSRC : 
*/
BOOL CAxJpgCard::DrawOriginalColors(RECT &rc, HDC hdcDST, HDC hdcSRC)
{
    RGBQUAD pColors[256];
    
    for (int i = 0; i < 256; i++)
    {
        pColors[i].rgbBlue = m_pColors[i].rgbBlue;
        pColors[i].rgbGreen = m_pColors[i].rgbGreen;
        pColors[i].rgbRed = m_pColors[i].rgbRed;
    }
    
    
    int a = SetDIBColorTable(hdcSRC, 0, 256, pColors );
    StretchBlt(hdcDST, rc.left, rc.top, (rc.right - rc.left) , (rc.bottom - rc.top), hdcSRC, 0,0, e_BmW, e_BmH, SRCCOPY );
    
    return TRUE;
    
}



////////////////////////////////////////
//        OnLButtonDown
/*! mouse taste is pressed, call client callback
// \param UINT uMsg : 
// \param WPARAM wParam : 
// \param LPARAM lParam : 
// \param BOOL& bHandled : 
*/
LRESULT CAxJpgCard::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    // dispatch source event
    CProxy_IAxJpgCardEvents<CAxJpgCard>::Fire_LMouseClick();
    // interface source event for C++ clients
    CProxy_IAxJpgCardEventsVtbl<CAxJpgCard>::Fire_LMouseClick(); 
    
    return 0;
}


////////////////////////////////////////
//       OnRButtonDown
/*! Right mouse taste is pressed, callback in the client
// \param UINT uMsg : 
// \param WPARAM wParam : 
// \param LPARAM lParam : 
// \param BOOL& bHandled : 
*/
LRESULT CAxJpgCard::OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    // dispatch source event
    CProxy_IAxJpgCardEvents<CAxJpgCard>::Fire_RMouseClick();
    // interface source event for C++ clients
    CProxy_IAxJpgCardEventsVtbl<CAxJpgCard>::Fire_RMouseClick(); 
    
    return 0;
}



////////////////////////////////////////
//      get_NumCardOnDeck
/*! provides the deck cards count
// \param long *pVal : 
*/
STDMETHODIMP CAxJpgCard::get_NumCardOnDeck(long *pVal)
{
    if (pVal != NULL)
	    *pVal = m_lNumMazzoItems;
    else
        return E_POINTER;

	return S_OK;
}


////////////////////////////////////////
//          put_NumCardOnDeck
/*! set the new cards value on deck
// \param long newVal : 
*/
STDMETHODIMP CAxJpgCard::put_NumCardOnDeck(long newVal)
{
    if (newVal >= 0 && newVal <= CS_MAXDECK)
    {
	    m_lNumMazzoItems = newVal;
        FireViewChange();
    }
    else
        return E_INVALIDARG;

	return S_OK;
}


////////////////////////////////////////
//       get_SizeImageX
/*! Provides image bitmap Width
// \param long *pVal : 
*/
STDMETHODIMP CAxJpgCard::get_SizeImageX(long *pVal)
{
	*pVal = e_BmW;
	return S_OK;
}

STDMETHODIMP CAxJpgCard::put_SizeImageX(long newVal)
{
	return S_OK;
}


////////////////////////////////////////
//       get_SizeImageY
/*! Provides image bitmap height
// \param long *pVal : 
*/
STDMETHODIMP CAxJpgCard::get_SizeImageY(long *pVal)
{
	*pVal = e_BmH;

	return S_OK;
}

STDMETHODIMP CAxJpgCard::put_SizeImageY(long newVal)
{
	return S_OK;
}


////////////////////////////////////////
//       get_DeckName
/*! Provides deck name
// \param BSTR *pVal : 
*/
STDMETHODIMP CAxJpgCard::get_DeckName(BSTR *pVal)
{
	if (pVal)
	{
		CComBSTR bstrName("Piacentine");
		*pVal = (BSTR)bstrName;
	}

	return S_OK;
}



