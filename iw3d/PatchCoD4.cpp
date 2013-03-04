// ==========================================================
// iw3d project
//
// File: PatchCoD4.cpp
// Purpose: Provide patches for CoD4 Dedicated Servers running on Windows
//
// Initial author: ArmedGuy
// ==========================================================
#include "stdinc.h"

void Sys_RunInit()
{
	PatchCoD4();
}
dvar_t* dedicated;

void PatchCoD4_Console();
void PatchCoD4_Commands();
void PatchCoD4_GuidValidation();
void PatchCoD4_Auth();
void PatchCoD4_Aluigi();
void PatchCoD4_Misc();

void PatchCoD4()
{
	PatchCoD4_Aluigi();
	PatchCoD4_Console();

	PatchCoD4_Commands();

	PatchCoD4_GuidValidation();
	PatchCoD4_Auth();

	PatchCoD4_Misc();
}

void PatchCoD4_Misc()
{

	// disable "dvar set" string in console log
	memset((void*)0x56B203, 0x90, 5);

	// remove "WARNING: unknown dvar" from console
	memset((void*)0x56D61A, 0x90, 5);

	// remove improper quit message
	char tmp1[] = {0xEB, 0x50};
	memcpy((void*)0x577415,  tmp1, 2);

	// remove computer changed message
	char tmp2[] = {0xEB, 0x2F};
	memcpy((void*)0x576775, tmp2, 2);

	// remove delta request messages(hopefully)
	//*(char*)0x534180 = 0xEB;
}