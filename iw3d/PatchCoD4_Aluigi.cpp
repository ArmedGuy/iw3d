// ==========================================================
// iw3d project
//
// File: PatchCoD4_Aluigi.cpp
// Purpose: Apply security patches found by Luigi "Aluigi" Auriemma in runtime
//
// Initial author: ArmedGuy
// ==========================================================

#include "stdinc.h"

StompHook patchVa;
#define VA_HOOK 0x571E30

void PatchCoD4_Aluigi()
{
	// Our va is bettar!
	patchVa.initialize(VA_HOOK, va);
	patchVa.installHook();
}