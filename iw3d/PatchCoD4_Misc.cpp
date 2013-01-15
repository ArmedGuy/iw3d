// ==========================================================
// iw3d project
//
// File: PatchCoD4_Misc.cpp
// Purpose: Various fixes
//
// Initial author: ArmedGuy
// ==========================================================

#include "stdinc.h"



void PatchCoD4_Misc()
{

	// disable "dvar set" string in console log
	memset((void*)0x56B203, 0x90, 5);

	// remove "WARNING: unknown dvar" from console
	memset((void*)0x56D61A, 0x90, 5);
}