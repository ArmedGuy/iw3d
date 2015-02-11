// ==========================================================
// iw3d project
//
// File: PatchCoD4_Commands.cpp
// Purpose: Experimenting with hooking existing commands
//          and provide custom functionality
//
// Initial author: ArmedGuy
// ==========================================================

#include "stdinc.h"

CallHook hKickHook;
CallHook hRemoteKickHook;

void KickCommandHook(char d1, char d2)
{
	Com_Printf(0, "Usage: kick <player> [reason]\n");
}

void PatchCoD4_Commands()
{
	hKickHook.initialize(0x52802E, KickCommandHook);
	hKickHook.installHook();

	hRemoteKickHook.initialize(0x52817B, KickCommandHook);
	hRemoteKickHook.installHook();
}
