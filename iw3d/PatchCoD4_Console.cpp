// ==========================================================
// iw3d project
//
// File: PatchCoD4_Console.cpp
// Purpose: Create a console-based server instead of that hideous GUI that lags.
//
// Initial author: ArmedGuy
// ==========================================================


#include "stdinc.h"

StompHook hCreateWindow;
StompHook hDestroyWindow;
StompHook hSysPrint;

#define SYS_CREATEWINDOW_HOOK 0x57A430
#define SYS_DESTROYWINDOW_HOOK 0x576B9E
DWORD pPostDestroyWindow =  0x576BC5; // Remember to set EBX to 0

#define SYS_PRINT_HOOK 0x57A7B0 // was: 0x576C20

// main call to that func: 004FCB8C
// where (i guess) handle == null that stops current prints: 0x4FCB73
// amount of bytes to nop: 2 4 1 2
/*
0057A430 = Console creation func
004FD4E0 = Server Quit part
*/

void Sys_CreateConsole()
{
	FreeConsole();
	AllocConsole();
	SetConsoleTitleA("IW3 Console - Uber Alpha test version 0.1");
	freopen("CON", "w", stdout); // Reset stdout to console output
	Com_Printf(0, "Running in console mode!\n");
}

__declspec(naked) void Sys_DestroyConsole()
{
	FreeConsole();
	__asm {
		mov ebx, 0;
		jmp pPostDestroyWindow;
	}
}

void Sys_Print()
{
	char* msg;
	__asm mov ecx, msg;
	if(msg != NULL)
		printf(msg);
}

void PatchCoD4_Console()
{
	memset((void*)0x4FCB73, 0x90, 9); // disable null check

	hCreateWindow.initialize(SYS_CREATEWINDOW_HOOK, Sys_CreateConsole);
	hCreateWindow.installHook();

	hDestroyWindow.initialize(SYS_DESTROYWINDOW_HOOK, Sys_DestroyConsole);
	hDestroyWindow.installHook();

	hSysPrint.initialize(SYS_PRINT_HOOK, Sys_Print);
	hSysPrint.installHook();
}