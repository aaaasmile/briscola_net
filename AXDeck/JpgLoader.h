// JpgLoader.h

#ifndef _JPG_LOADER_H
#define _JPG_LOADER_H

class  cJpgLoader
{
public:
    cJpgLoader(){};
    HRESULT LoadImageFromResource(int iIdResource, LPPICTURE* pgpPicture, HINSTANCE hInstance);
    BOOL    LoadPictureFile(LPCTSTR    szFile, LPPICTURE* pgpPicture);
};

#endif
