#include "stdinc.h"


Com_Printf_t Com_Printf = (Com_Printf_t)0x4FCBC0;
Cmd_AddCommand_t Cmd_AddCommand = (Cmd_AddCommand_t)0x4F9950;
Cmd_AddServerCommand_t Cmd_AddServerCommand = (Cmd_AddServerCommand_t)0x4F9140;

Dvar_FindVar_t _Dvar_FindVar = (Dvar_FindVar_t)0x56B5D0;
dvar_t* Dvar_FindVar(char* name)
{
	__asm mov edi, name;
	return _Dvar_FindVar();
}


NET_StringToAdr_t NET_StringToAdr_CoD4 = (NET_StringToAdr_t)0x508F40;
NET_OOBPrint_t NET_OOBPrint = (NET_OOBPrint_t)0x508BF0;

//OOBPrint: 0x508BF0


bool NET_StringToAdr(const char* address, netadr_t* adr)
{
	__asm mov eax, address;
	__asm mov ecx, 0xFFFFFFFF;
	NET_StringToAdr_CoD4( adr);
}
typedef void (__cdecl* sendOOB_t)(int, int, int, int, int, int, const char*);
sendOOB_t OOBPrint = (sendOOB_t)0x4AEF00; //MW2 one, not CoD4

void OOBPrintT(int type, netadr_t netadr, const char* message)
{
        int* adr = (int*)&netadr;

        OOBPrint(type, *adr, *(adr + 1), *(adr + 2), 0xFFFFFFFF, *(adr + 4), message);
}

void NET_OutOfBandPrint(int type, netadr_t adr, const char* message, ...)
{
        va_list args;
        char buffer[65535];

        va_start(args, message);
        _vsnprintf(buffer, sizeof(buffer), message, args);
        va_end(args);

        OOBPrintT(type, adr, buffer);
}




