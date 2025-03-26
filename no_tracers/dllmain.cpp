#define WIN32_LEAN_AND_MEAN

#include "windows.h"

#define UInt32 unsigned long


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	return TRUE;
}

void SafeWrite32(UInt32 addr, UInt32 data)
{
	UInt32 oldProtect;

	VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &oldProtect);
	*((UInt32*)addr) = data;
	VirtualProtect((void*)addr, 4, oldProtect, &oldProtect);
}

extern "C" __declspec(dllexport) void loaded_client()
{
	HMODULE client = GetModuleHandleA("client.dll");
	if (client != NULL)
	{
		UInt32 addr = (UInt32)client + 0x4099A;
		SafeWrite32(addr, 0xB0E9);
	}
}
