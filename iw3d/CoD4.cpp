#include "stdinc.h"

// AFDD0 - offset to Com_Error
Com_Printf_t Com_Printf = (Com_Printf_t)0x4FCBC0;
Cmd_AddCommand_t Cmd_AddCommand = (Cmd_AddCommand_t)0x4F9950;
Cmd_AddServerCommand_t Cmd_AddServerCommand = (Cmd_AddServerCommand_t)0x4F9140;

Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand = (Cmd_ExecuteSingleCommand_t)0x55C280;

SV_SendServerCommand_t SV_SendServerCommand = (SV_SendServerCommand_t)0x531320;

Dvar_FindVar_t _Dvar_FindVar = (Dvar_FindVar_t)0x56B5D0;
dvar_t* Dvar_FindVar(char* name)
{
	__asm mov edi, name;
	return _Dvar_FindVar();
}


NET_StringToAdr_t NET_StringToAdr_CoD4 = (NET_StringToAdr_t)0x508F40;
NET_OOBPrint_t NET_OOBPrint = (NET_OOBPrint_t)0x571E30;


//OOBPrint: 0x508BF0



/*
ENTRIES

Net_GetPacket: 0x00577CE0
Sys_SendPacket: 0x00577F50
NET_OutOfBandPrint: 0x571DB0



*/



DWORD* cmd_arg_id = (DWORD*)0x1410B40;
DWORD* cmd_argc = (DWORD*)0x1410B84;
DWORD** cmd_argv = (DWORD**)0x1410BA4;

int Cmd_Argc(void) {
    return cmd_argc[*cmd_arg_id];
}
char* Cmd_Argv(int arg) {
    if ((unsigned)arg >= cmd_argc[*cmd_arg_id]) {
        return "";
    }
    return (char*)(cmd_argv[*cmd_arg_id][arg]);
}

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




