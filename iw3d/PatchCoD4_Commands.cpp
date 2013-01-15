// ==========================================================
// iw3d project
//
// File: PatchCoD4_Commands.cpp
// Purpose: Experimenting with hooking existing commands and provide custom functionality
//
// Initial author: ArmedGuy
// ==========================================================

#include "stdinc.h"

CallHook hKickHook;
CallHook hRemoteKickHook;

void KickCommandHook(char, char);

DWORD pKickCommand = 0x52802E;
DWORD pRemoteKickCommand = 0x52817B;


void PatchCoD4_Commands()
{
	hKickHook.initialize(pKickCommand, KickCommandHook);
	hKickHook.installHook();

	hRemoteKickHook.initialize(pRemoteKickCommand, KickCommandHook);
	hRemoteKickHook.installHook();
}



void KickCommandHook(char d1, char d2)
{
	Com_Printf(0, "Usage: kick <player> [reason]\n");
}
