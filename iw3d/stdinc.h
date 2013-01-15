#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <io.h>

#include "CoD4.h"
#include "utils.h"
#include "Hooking.h"




void Main_UnprotectModule(HMODULE hMod);

#define MASTERSERVERIP 0x157C923F
#pragma comment(linker, "/export:Direct3DCreate9=d3d9.Direct3DCreate9") //DLL Proxy

void Sys_RunInit();
void PatchCoD4();