

typedef struct cmd_function_s 
{
	char unknown_padding[24];
} cmd_function_t;


// DVAR Flags
//Retrieved from original q3a source code
#define DVAR_FLAG_NORMAL         0   // just a normal dvar
#define	DVAR_FLAG_ARCHIVE		1	// set to cause it to be saved to vars.rc
								// used for system variables, not for player
								// specific configurations
#define	DVAR_FLAG_USERINFO		2	// sent to server on connect or change
#define	DVAR_FLAG_SERVERINFO		4	// sent in response to front end requests
#define	DVAR_FLAG_SYSTEMINFO		8	// these cvars will be duplicated on all clients
#define	DVAR_FLAG_WRITEPROT			16	// don't allow change from console at all,
								// but can be set from the command line
#define	DVAR_FLAG_LATCH			32	// will only change when C code next does
								// a Cvar_Get(), so it can't be changed
								// without proper initialization.  modified
								// will be set, even though the value hasn't
								// changed yet
#define	DVAR_FLAG_READONLY		64	// display only, cannot be set by user at all
#define	DVAR_FLAG_USER_CREATED	128	// created by a set command
#define	DVAR_FLAG_TEMP			256	// can be set even when cheats are disabled, but is not archived
#define DVAR_FLAG_CHEAT			512	// can not be changed if cheats are disabled
#define DVAR_FLAG_NORESTART		1024	// do not clear when a cvar_restart is issued

// Borrowed "aRev" style from http://fourdeltaone.net
// Original author: NTAuthority, all creds go to him
typedef enum
{
        DVAR_TYPE_BOOL          = 0,
        DVAR_TYPE_FLOAT         = 1,
        DVAR_TYPE_FLOAT_2       = 2,
        DVAR_TYPE_FLOAT_3       = 3,
        DVAR_TYPE_FLOAT_4       = 4,
        DVAR_TYPE_INT           = 5,
        DVAR_TYPE_ENUM          = 6,
        DVAR_TYPE_STRING        = 7,
        DVAR_TYPE_COLOR         = 8,
} dvar_type;
union dvar_value_t {
                char*   string;
                int             integer;
                float   value;
                bool    boolean;
                float   vec2[2];
                float   vec3[3];
                float   vec4[4];
                BYTE    color[4];
};
union dvar_maxmin_t {
        int i;
        float f;
};
typedef struct dvar_s
{
        const char*             name;
        const char*             description;
        short                   flags;
        char                    type;
        char                    modified; //1 if modified
        dvar_value_t    current;
        dvar_value_t    latched;
        dvar_value_t    default;
        dvar_maxmin_t min; 
        dvar_maxmin_t max;
} dvar_t;


typedef enum { 
	NA_BOT,
	NA_BAD,
	NA_LOOPBACK,
	NA_BROADCAST,
	NA_IP
} netadrtype_t;

typedef enum {
	NS_CLIENT,
	NS_SERVER
} netsrc_t;

typedef struct {
	netadrtype_t type;
	BYTE ip[4];
	unsigned short port;
	BYTE ipx[10];
} netadr_t;

typedef struct masterserver_s
{
	dvar_t* address;
	netadr_t resolvedAddress;
} masterserver_t;


//player list 0x1CBFC8C , 0x0A563C between each player

//connectInfoString[1024] at 0x1CC02DC
typedef struct player_s {
	int state;
	char pad[1616];
	char connectInfoString[1024];
} player_t;

//#define _EDIPROB_   // issue with Dvar_FindVar

//CoD4 functions
typedef void (__cdecl *Com_Printf_t)(int, const char*, ...);
extern Com_Printf_t Com_Printf;

typedef void (__cdecl * xcommand_t)(void);
typedef void (__cdecl * Cmd_AddCommand_t)(const char* cmd, xcommand_t callback, cmd_function_t* data, char);
extern Cmd_AddCommand_t Cmd_AddCommand;

typedef void (__cdecl * Cmd_AddServerCommand_t)(const char* cmd, xcommand_t callback, cmd_function_t* data);
extern Cmd_AddServerCommand_t Cmd_AddServerCommand;

typedef dvar_t* (__cdecl * Dvar_FindVar_t)(void);
extern Dvar_FindVar_t _Dvar_FindVar;
dvar_t* Dvar_FindVar(char* name);


typedef void (__cdecl * SV_SendServerCommand_t)(void*, const char*, ...);
extern SV_SendServerCommand_t SV_SendServerCommand;

typedef void(__cdecl * Cmd_ExecuteSingleCommand_t)(int, const char*, ...);
extern Cmd_ExecuteSingleCommand_t Cmd_ExecuteSingleCommand;


typedef bool (__cdecl * NET_StringToAdr_t)(netadr_t*);
bool NET_StringToAdr(const char* address, netadr_t* adr);
extern NET_StringToAdr_t NET_StringToAdr_CoD4;

typedef int (__cdecl * NET_OOBPrint_t)(int type, netadr_t adr, const char* message);
extern NET_OOBPrint_t NET_OOBPrint;