// ==========================================================
// iw3d project
//
// File: PatchCoD4_GuidValidation.cpp
// Purpose: Validates player guids[0-9a-f]{32}, VERY useful when authentication server isn't being used.
//
// Initial author: ArmedGuy
// ==========================================================

#include "stdinc.h"

StompHook hGuidValidationHook;
#define GUID_VALIDATION 0x529375
DWORD pValidGuid = 0x529384;
DWORD pSkipBanCheck = 0x52937F;
__declspec(naked) void GuidValidationStub()
{
	_asm {
		push ebp;
		push esi;
		cmp dword ptr ss:[esi+4], MASTERSERVERIP;
		je masterserver;
		mov edx, 0;
validationloop:
		cmp byte ptr ss:[ebp+edx], 0x30;
		jl invalid;
		cmp byte ptr ss:[ebp+edx], 0x39;
		jle validchar;
		cmp byte ptr ss:[ebp+edx], 0x61;
		jl invalid;
		cmp byte ptr ss:[ebp+edx], 0x66;
		jg invalid;
validchar:
		add edx, 1;
		cmp edx, 0x20;
		je allvalid;
		jmp validationloop;
masterserver:
		push edi;
		mov eax, 0;
		jmp pSkipBanCheck;
invalid:
		push edi;
		mov eax, 1;
		jmp pSkipBanCheck;
allvalid:
		push edi;
		jmp pValidGuid;
	}
}
void PatchCoD4_GuidValidation()
{
	hGuidValidationHook.initialize(GUID_VALIDATION, GuidValidationStub);
	hGuidValidationHook.installHook();
}
/*

00529444   55               PUSH EBP                                 ; jump from ban check function, the hook for this code
00529445   56               PUSH ESI
00529446   36:817E 04 3F927>CMP DWORD PTR SS:[ESI+4],157C923F        ; is current challenger the masterserver?
0052944E   74 43            JE SHORT iw3mp.00529493                  ; if so, skip GUID auth and allow
00529450   BA 00000000      MOV EDX,0
00529455   36:803C2A 30     CMP BYTE PTR SS:[EDX+EBP],30             ; compare ASCII chars, must be between 30-39 and 61-66(0123456789abcdef)
0052945A   7C 21            JL SHORT iw3mp.0052947D
0052945C   36:803C2A 39     CMP BYTE PTR SS:[EDX+EBP],39
00529461   7F 02            JG SHORT iw3mp.00529465
00529463   EB 0E            JMP SHORT iw3mp.00529473
00529465   36:803C2A 61     CMP BYTE PTR SS:[EDX+EBP],61
0052946A   7C 11            JL SHORT iw3mp.0052947D
0052946C   36:803C2A 66     CMP BYTE PTR SS:[EDX+EBP],66
00529471   7F 0A            JG SHORT iw3mp.0052947D
00529473   83C2 01          ADD EDX,1                                ; i++;
00529476   83FA 20          CMP EDX,20                               ; if i == 32
00529479   74 0D            JE SHORT iw3mp.00529488                  ; valid client, continue checking bans
0052947B  ^EB D8            JMP SHORT iw3mp.00529455                 ; if we haven't looped through all 32 chars, jump back up
0052947D   57               PUSH EDI                                 ; char out of valid ranges, send a "perm banned" message back to client and drop connection
0052947E   B8 01000000      MOV EAX,1
00529483  ^E9 F7FEFFFF      JMP iw3mp.0052937F
00529488   8BD1             MOV EDX,ECX                              ; regular client with valid GUID
0052948A   57               PUSH EDI
0052948B  ^E9 F4FEFFFF      JMP iw3mp.00529384
00529490   57               PUSH EDI                                 ; master server, always returns 0 as it doesn't have any GUID
00529491   B8 00000000      MOV EAX,0
00529496  ^E9 E4FEFFFF      JMP iw3mp.0052937F
0052949B   90               NOP                                      ; not using any of the below stuff
0052949C   90               NOP
0052949D   90               NOP
0052949E   90               NOP
0052949F   90               NOP
005294A0   90               NOP
005294A1   90               NOP
005294A2   90               NOP
005294A3   90               NOP
005294A4   90               NOP
005294A5   90               NOP
*/
