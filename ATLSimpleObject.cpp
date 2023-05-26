// ATLSimpleObject.cpp: CATLSimpleObject 的实现

#include "pch.h"
#include "ATLSimpleObject.h"


// CATLSimpleObject

HRESULT CATLSimpleObject::IShellExtInit(PCIDLIST_ABSOLUTE pidlFolder, IDataObject* pdtobj, HKEY hkeyProgID)
{
    return ;
}

HRESULT CATLSimpleObject::QueryContextMenu(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
    return E_NOTIMPL;
}

HRESULT CATLSimpleObject::GetCommandString(UINT_PTR idCmd, UINT uType, UINT* pReserved, CHAR* pszName, UINT cchMax)
{
    return E_NOTIMPL;
}

HRESULT CATLSimpleObject::InvokeCommand(CMINVOKECOMMANDINFO* pici)
{
    return E_NOTIMPL;
}
