#include "stdinc.h"

#define VA_BUFFER_COUNT         4
#define VA_BUFFER_SIZE          32768

static char g_vaBuffer[VA_BUFFER_COUNT][VA_BUFFER_SIZE];
static int g_vaNextBufferIndex = 0;

const char *va( const char *fmt, ... )
{
        va_list ap;
        char *dest = &g_vaBuffer[g_vaNextBufferIndex][0];
        g_vaNextBufferIndex = (g_vaNextBufferIndex + 1) % VA_BUFFER_COUNT;
        va_start(ap, fmt);
        int res = _vsnprintf( dest, VA_BUFFER_SIZE, fmt, ap );
        dest[VA_BUFFER_SIZE - 1] = '\0';
        va_end(ap);

        if (res < 0 || res >= VA_BUFFER_SIZE)
        {
                //Attempted to overrun string in call to va(), cba to Com_Error it
				Com_Printf(0, "Error: Attempted to overrun string in call to va()\n"); //Not bothered to use Com_Error
        }
        return dest;
}