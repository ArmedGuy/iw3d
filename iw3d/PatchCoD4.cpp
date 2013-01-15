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