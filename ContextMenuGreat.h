// ContextMenuGreat.h: CContextMenuGreat 的声明

#pragma once
#include "resource.h"       // 主符号
#include <ShObjIdl_core.h>


#include "main_i.h"
#include <string>
#include <vector>



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;


// CContextMenuGreat

class ATL_NO_VTABLE CContextMenuGreat :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CContextMenuGreat, &CLSID_ContextMenuGreat>,
	public IDispatchImpl<IContextMenuGreat, &IID_IContextMenuGreat, &LIBID_mainLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IShellExtInit,
	public IContextMenu
{
private:
	enum MyCmd
    {
        CMD_ROOT,
		CMD_SHOW_ONE,
		CMD_SHOW_TWO,
		CMD_SHOW_THR,
		CMD_SHOW_FOUR,
		CMD_SHOW_FIFT,
        CMD_END
    };
    struct MenuInfo
    {
        std::string name;
        // other infos
    };
    // datas
    std::vector<std::wstring> m_filepaths;
public:
	CContextMenuGreat()
	{
		InternalAddRef();
		
	}
	~CContextMenuGreat() {
		InternalRelease();
		InternalRelease();
	}
DECLARE_REGISTRY_RESOURCEID(108)


BEGIN_COM_MAP(CContextMenuGreat)
	COM_INTERFACE_ENTRY(IContextMenuGreat)
	COM_INTERFACE_ENTRY(IContextMenu)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
		
	}

public:
	HRESULT Initialize(PCIDLIST_ABSOLUTE pidlFolder, IDataObject* pdtobj, HKEY hkeyProgID);
	HRESULT QueryContextMenu(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
	HRESULT GetCommandString(UINT_PTR idCmd, UINT     uType, UINT* pReserved, CHAR* pszName, UINT     cchMax);
	HRESULT InvokeCommand(CMINVOKECOMMANDINFO* pici);
	
};

OBJECT_ENTRY_AUTO(__uuidof(ContextMenuGreat), CContextMenuGreat)
