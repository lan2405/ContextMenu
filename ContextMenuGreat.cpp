// ContextMenuGreat.cpp: CContextMenuGreat 的实现

#include "pch.h"
#include "ContextMenuGreat.h"


// CContextMenuGreat

HRESULT CContextMenuGreat::Initialize(PCIDLIST_ABSOLUTE pidlFolder, IDataObject* pdtobj, HKEY hkeyProgID)
{
    
    FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
    STGMEDIUM stg = { TYMED_HGLOBAL };
    HDROP      hDrop;

    //空白处右键，pdtobj是空指针
    if (pdtobj == nullptr)
    {
        return E_INVALIDARG;
    }

    // 在数据对象内查找CF_HDROP类型数据。
    // 如果没有数据，返回一个错误（“无效参数”）给Explorer。
    if (FAILED(pdtobj->GetData(&fmt, &stg)))
    {
        return E_INVALIDARG;
    }

    // 取得指向实际数据的指针。
    hDrop = (HDROP)GlobalLock(stg.hGlobal);

    // 确保非NULL
    if (NULL == hDrop)
    {
        return E_INVALIDARG;
    }

    //选中文件个数
    UINT uNumFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);

    if (0 == uNumFiles)
    {
        GlobalUnlock(stg.hGlobal);
        ReleaseStgMedium(&stg);
        return E_INVALIDARG;
    }

    // 获取选中的文件
    for (UINT index = 0; index < uNumFiles; index++)
    {
        WCHAR szFile[MAX_PATH + 1];
        if (0 == DragQueryFile(hDrop, index, szFile, MAX_PATH))
            continue;

        m_filepaths.push_back(szFile);
    }

    GlobalUnlock(stg.hGlobal);
    ReleaseStgMedium(&stg);
	return S_OK;
}

HRESULT CContextMenuGreat::QueryContextMenu(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
	HMENU uhmenu = CreatePopupMenu();
	
	MENUITEMINFO hmenu_lpmi{ sizeof(MENUITEMINFO),MIIM_TYPE| MIIM_STATE | MIIM_SUBMENU,MFT_STRING,MFS_ENABLED };
	hmenu_lpmi.hSubMenu = uhmenu;
    hmenu_lpmi.dwTypeData = _T("主菜单");

    MENUITEMINFO uhmenu_lpmi0{ sizeof(MENUITEMINFO),MIIM_TYPE | MIIM_STATE | MIIM_ID ,MFT_STRING,MFS_ENABLED ,idCmdFirst + CMD_SHOW_ONE };
	MENUITEMINFO uhmenu_lpmi1{ sizeof(MENUITEMINFO),MIIM_TYPE | MIIM_STATE | MIIM_ID ,MFT_STRING,MFS_ENABLED, idCmdFirst + CMD_SHOW_TWO };
	MENUITEMINFO uhmenu_lpmi2{ sizeof(MENUITEMINFO),MIIM_TYPE | MIIM_STATE | MIIM_ID ,MFT_STRING,MFS_ENABLED, idCmdFirst + CMD_SHOW_THR };
	MENUITEMINFO uhmenu_lpmi3{ sizeof(MENUITEMINFO),MIIM_TYPE | MIIM_STATE | MIIM_ID ,MFT_STRING,MFS_ENABLED, idCmdFirst + CMD_SHOW_FOUR };


	uhmenu_lpmi0.dwTypeData = _T("子菜单0");
	uhmenu_lpmi1.dwTypeData = _T("子菜单1");
	uhmenu_lpmi2.dwTypeData = _T("子菜单2");
	uhmenu_lpmi3.dwTypeData = _T("子菜单3");
	//uhmenu_lpmi4.dwTypeData = _T("子菜单4");

	InsertMenuItem(uhmenu, 1,TRUE , (LPCMENUITEMINFO)&uhmenu_lpmi0);
	InsertMenuItem(uhmenu, 2, TRUE, (LPCMENUITEMINFO)&uhmenu_lpmi1);
	InsertMenuItem(uhmenu, 3, TRUE, (LPCMENUITEMINFO)&uhmenu_lpmi2);
	InsertMenuItem(uhmenu, 4, TRUE, (LPCMENUITEMINFO)&uhmenu_lpmi3);
	
	InsertMenu(hmenu, indexMenu, MF_BYCOMMAND| MF_POPUP| MF_STRING,(UINT_PTR)uhmenu, _T("主菜单"));
	return MAKE_HRESULT(SEVERITY_SUCCESS,0, CMD_SHOW_FOUR+1);
}

HRESULT CContextMenuGreat::GetCommandString(UINT_PTR idCmd, UINT uType, UINT* pReserved, CHAR* pszName, UINT cchMax)
{
	return E_NOTIMPL;
}

HRESULT CContextMenuGreat::InvokeCommand(CMINVOKECOMMANDINFO* pici)
{
    CMINVOKECOMMANDINFOEX* piciEx = nullptr;
    BOOL if_ex=false;
    if (pici->cbSize == sizeof(CMINVOKECOMMANDINFOEX) && pici->fMask == CMIC_MASK_UNICODE)
    {
        if_ex = true;
        piciEx = (CMINVOKECOMMANDINFOEX*)pici;
    }
    UINT cmd;
    if (if_ex) {
        if (0 == HIWORD(piciEx->lpVerbW))
            cmd = LOWORD(piciEx->lpVerbW);
        else return E_INVALIDARG;
    }
    else {
        if (0 == HIWORD(pici->lpVerb))
            cmd = LOWORD(pici->lpVerb);
        else return E_INVALIDARG;
    }
    switch (cmd)
    {
    case CMD_SHOW_ONE:
        system("cmd");
        break;
    case CMD_SHOW_TWO:
        system("powershell");
        break;
    case CMD_SHOW_THR:
       
        break;
    case CMD_SHOW_FOUR:
        
        break;
    default:
        break;
    }
	return S_OK;
}
