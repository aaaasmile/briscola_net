//JpgLoader.cpp

#include "stdafx.h"
#include "JpgLoader.h"

////////////////////////////////////////
//          LoadImageFromResource
/*! Load a jpg resource with load picture and store it in LPPICTURE pointer
// \param   int iIdResource : 
// \param LPPICTURE* pgpPicture : 
// \param HINSTANCE hInstance: 
*/
HRESULT cJpgLoader::LoadImageFromResource(  int iIdResource, 
                                            LPPICTURE* pgpPicture,
                                            HINSTANCE hInstance
                                           )
{
    HRSRC hRes = FindResource(hInstance, MAKEINTRESOURCE(iIdResource), "jpg");
    if (hRes==NULL) 
    {
      ATLTRACE("Couldn't find jpg resource %d!\n", iIdResource);
      return E_FAIL;
    }

    DWORD dwFileSize = SizeofResource(hInstance, hRes);

    HGLOBAL hResurce = LoadResource(hInstance, hRes);
    ATLASSERT(hResurce);

    LPVOID pvData = NULL;

    // alloc memory based on file size
    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);

    if (hGlobal == NULL)
    {
        return E_OUTOFMEMORY;
    }

    pvData = GlobalLock(hGlobal);

    if (pvData == NULL)
    {
        GlobalUnlock(hGlobal);
        return E_FAIL;
    }

    memcpy(pvData, hResurce ,dwFileSize);
   
    GlobalUnlock(hGlobal);
    
    
    LPSTREAM pstm = NULL;

    // create IStream* from global memory
    HRESULT hr = CreateStreamOnHGlobal(hGlobal,
                                       TRUE,
                                       &pstm);

    if (FAILED(hr))
    {
        if (pstm != NULL)
            pstm->Release();
            
        return hr;
    }
    else if (pstm == NULL)
    {
        return E_FAIL;
    }

	// Create IPicture from image file
	if (*pgpPicture)
		(*pgpPicture)->Release();

    hr = ::OleLoadPicture(pstm,
                          dwFileSize,
                          FALSE,
                          IID_IPicture,
                          (LPVOID *)&(*pgpPicture));

    if (FAILED(hr))
    {
    	pstm->Release();
        return hr;
    }
    else if (*pgpPicture == NULL)
    {
    	pstm->Release();
        return E_FAIL;
    }

    pstm->Release();

    return S_OK;
}


////////////////////////////////////////
//          LoadPictureFile
/*! Load picture from file
// \param LPCTSTR    szFile : 
// \param LPPICTURE* pgpPicture : 
*/
BOOL cJpgLoader::LoadPictureFile(LPCTSTR    szFile, LPPICTURE* pgpPicture)
{
    // open file
    HANDLE hFile = CreateFile(szFile,
                              GENERIC_READ,
                              0,
                              NULL,
                              OPEN_EXISTING,
                              0,
                              NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }

    // get file size
    DWORD dwFileSize = GetFileSize(hFile, NULL);

    if (dwFileSize == (DWORD)-1)
    {
        CloseHandle(hFile);
        return FALSE;
    }

    LPVOID pvData = NULL;

    // alloc memory based on file size
    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);

    if (hGlobal == NULL)
    {
        CloseHandle(hFile);
        return FALSE;
    }

    pvData = GlobalLock(hGlobal);

    if (pvData == NULL)
    {
        GlobalUnlock(hGlobal);
        CloseHandle(hFile);
        return FALSE;
    }

    DWORD dwBytesRead = 0;

    // read file and store in global memory
    BOOL bRead = ReadFile(hFile,
                          pvData,
                          dwFileSize,
                          &dwBytesRead,
                          NULL);

    GlobalUnlock(hGlobal);
    CloseHandle(hFile);

    if (!bRead)
    {
        return FALSE;
    }

    LPSTREAM pstm = NULL;

    // create IStream* from global memory
    HRESULT hr = CreateStreamOnHGlobal(hGlobal,
                                       TRUE,
                                       &pstm);

    if (!(SUCCEEDED(hr)))
    {

        if (pstm != NULL)
            pstm->Release();
            
        return FALSE;
    }

    else if (pstm == NULL)
    {
        return FALSE;
    }

	// Create IPicture from image file
	if (*pgpPicture)
		(*pgpPicture)->Release();

    hr = ::OleLoadPicture(pstm,
                          dwFileSize,
                          FALSE,
                          IID_IPicture,
                          (LPVOID *)&(*pgpPicture));

    if (!(SUCCEEDED(hr)))
    {
    	pstm->Release();
        return FALSE;
    }
    else if (*pgpPicture == NULL)
    {
    	pstm->Release();
        return FALSE;
    }

    pstm->Release();

    return TRUE;  //Made it ...!
}
