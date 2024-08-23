#include <Arduino.h>
#include "debug_conditionals.h"

#ifdef DEBUG_ON

char* debugSnSeconds(const char* _Buffer,
                     size_t const _BufferCount,
                     const char* sMessage,
                     uint32_t seconds_run_time)
    {
    char buffer[NUMBER_BUFFER + 1];

    uint32_t tm_Hours = (seconds_run_time / 3600);
    uint32_t tm_Minutes = (seconds_run_time / 60) % 60;
    uint32_t tm_Seconds = seconds_run_time % 60;
    strncpy(_Buffer, sMessage, _BufferCount); // DEBUG_PRINT(sMessage);
    if (tm_Hours > 0)
        {
        snprintf(buffer, NUMBER_BUFFER, "%u:", tm_Hours);
        strncpy(_Buffer, buffer, _BufferCount); //  DEBUG_PRINT(buffer);
        }
    snprintf(buffer, NUMBER_BUFFER, "%02.2u:", tm_Minutes);
    strncat(_Buffer, buffer, _BufferCount); //DEBUG_PRINT(buffer);
    snprintf(buffer, NUMBER_BUFFER, "%02.2u", tm_Seconds);
    strncat(_Buffer, buffer, _BufferCount); //DEBUG_PRINT(buffer);
    if (tm_Hours > 0)
        {
        strncat(_Buffer, " hour(s)", _BufferCount); //DEBUG_PRINT(" hour(s) ");
        }
    else
        {
        if (tm_Minutes > 0)
            {
            strncat(_Buffer, " minutes(s)", _BufferCount); //DEBUG_PRINT(" minutes(s) ");
            }
        else
            {
            strncat(_Buffer, " seconds(s)", _BufferCount); //DEBUG_PRINT(" seconds(s) ");
            }
        }
    }

#endif
