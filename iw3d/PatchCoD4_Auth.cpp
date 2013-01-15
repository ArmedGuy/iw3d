// ==========================================================
// iw3d project
//
// File: PatchCoD4_Auth.cpp
// Purpose: Overrides Sys_IsLocalAddress to skip authserver authentication for clients.
//
// Initial author: ArmedGuy
// ==========================================================
#include "stdinc.h"
StompHook hAuthHook;
#define AUTH_HOOK 0x529425

__declspec(naked) void AuthenticationStub()
{
	__asm
	{
		sub esp, 0x14;
		cmp dword ptr ss:[esp+0x1c], MASTERSERVERIP;
		je ismasterserver;
		add esp, 0x14;
		mov eax, 0;
		retn;
ismasterserver:
		add esp, 0x14;
		mov eax, 1;
		retn;
	}
}
void PatchCoD4_Auth()
{
	hAuthHook.initialize(AUTH_HOOK, AuthenticationStub);
	hAuthHook.installHook();
}