/*
 * Copyright (c) 2003, Jon Marinello
 *
 */

#include "stdafx.h"

#include <HhGui/FolderBrowser.h>
#include <HhGui/Exceptions.h>

HH_FolderBrowser::HH_FolderBrowser()
    : _pMalloc( NULL )
{
    ::ZeroMemory( _folderPath, sizeof _folderPath );

    if ( ::SHGetMalloc( &_pMalloc ) == E_FAIL )
    {
        throw HH_ShellCallFailed( "::SHGetMalloc()" );
    }
}



HH_FolderBrowser::~HH_FolderBrowser()
{
    if ( _pMalloc != NULL )
    {
        _pMalloc->Release();
        _pMalloc = NULL;
    }
}



int HH_FolderBrowser::DoModal( HWND ownerWindowHandle, const std::string& title )
{
    BROWSEINFO browseInfo;
    ::ZeroMemory( &browseInfo, sizeof BROWSEINFO );

    browseInfo.hwndOwner = ownerWindowHandle;

    browseInfo.lpszTitle = title.c_str();

    LPITEMIDLIST pidlSelected = ::SHBrowseForFolder( &browseInfo );
    if ( pidlSelected != NULL )
    {
        if ( !::SHGetPathFromIDList( pidlSelected, _folderPath ) )
        {
            throw HH_ShellCallFailed( "::SHGetPathFromIDList()" );
        }

        _pMalloc->Free( pidlSelected );

        return IDOK;
    }
    return IDCANCEL;
}
