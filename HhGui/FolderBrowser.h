#ifndef HH_FOLDER_BROWSER
#define HH_FOLDER_BROWSER

/*
 * Copyright (c) 2003, Jon Marinello
 *
 */

#include "stdafx.h"

#include <string>

class HH_FolderBrowser
{
public:
    HH_FolderBrowser();

    ~HH_FolderBrowser();

    int DoModal( HWND ownerWindowHandle, const std::string& title );

    std::string GetFolderPath() const { return _folderPath; }

protected:
    LPMALLOC    _pMalloc;
    char _folderPath[ _MAX_PATH ];

private:
    // not allowed
    HH_FolderBrowser( const HH_FolderBrowser& );
    HH_FolderBrowser& operator=( const HH_FolderBrowser& );
};

#endif
