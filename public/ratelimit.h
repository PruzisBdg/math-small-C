/*---------------------------------------------------------------------------
|
|                Rate counter with limit detector
|
|
|
|
|
|
|   
|      Rev 1.0   May 19 2009 12:56:28   spruzina
|   Initial revision.
|
|--------------------------------------------------------------------------*/

#ifndef RATELIMIT_H
#define RATELIMIT_H

#include "common.h"
#include "systime.h"

typedef struct
{
   U8             minCnt;        // minimum count to trigger rate limit
   U16            maxPerMinute;  // limiting rate in counts per minute
   U8             cnt;           // current count
   T_Timer        t1;            // times counter decrement
}  S_RateLimit;

PUBLIC void RateLimit_Make( S_RateLimit *r, U16 maxPerMinute, U8 minCnt );
PUBLIC void RateLimit_Reset( S_RateLimit *r );
PUBLIC U8 RateLimit_Tick( S_RateLimit *r );

#endif // RATELIMIT_H
 
