// dllmain.h: 模块类的声明。

class CmainModule : public ATL::CAtlDllModuleT< CmainModule >
{
public :
	DECLARE_LIBID(LIBID_mainLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MAIN, "{f17db82d-29b8-4245-9ea9-6182eea7bd33}")
};

extern class CmainModule _AtlModule;
