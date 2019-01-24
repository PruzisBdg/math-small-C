/*---------------------------------------------------------------------------
|
|                Rate counter with limit detector
|
|--------------------------------------------------------------------------*/

#include "common.h"
#include "math_common.h"
#include "systime.h"
#include "ratelimit.h"

/*-----------------------------------------------------------------------------
|
|  RateLimit_Reset()
|
------------------------------------------------------------------------------*/

PUBLIC void RateLimit_Reset( S_RateLimit *r )
{
   _ResetTimer(r->t1);
   r->cnt = 0;
}

/*-----------------------------------------------------------------------------
|
|  RateLimit_Make()
|
------------------------------------------------------------------------------*/

PUBLIC void RateLimit_Make( S_RateLimit *r, U16 maxPerMinute, U8 minCnt )
{
   r->maxPerMinute = maxPerMinute;
   r->minCnt = minCnt;
   RateLimit_Reset(r);
}


/*-----------------------------------------------------------------------------
|
|  RateLimit_Tick()
|
|  Add a tick to the rate counter 'r'. Return '1' if over the limit, else 0.
|
------------------------------------------------------------------------------*/

PUBLIC U8 RateLimit_Tick( S_RateLimit *r )
{
   U16   n;
   U8    maxCnt;

   if( ElapsedS(r->t1) > _TicksMin_S(1) )     // more than 1 minute since last tick?
   {
      _ResetTimer(r->t1);                    // then reset timer
      r->cnt = 1;                            // count this (1) tick
      return 0;                              // and limit not exceeded
   }
   else                                      // else less than 1 minute since last tick
   {
      r->cnt++;                              // add the tick

      // Get the limit count for the interval for which ticks have been summed.

      n = r->maxPerMinute * (U32)ElapsedS(r->t1) / _TicksMin_S(1);
      maxCnt = MIN(n, 0xFF);

      if( r->cnt >= r->minCnt &&             // minimum count exceeded?
          r->cnt >= maxCnt )                 // AND limit count on summing interval exceeded?
      {
         RateLimit_Reset(r);                 // then will start over
         return 1;                           // and return 'rate-exceeded'
      }
      else
      {
         return 0;                           // did not exceed rate limit
      }
   }
}

// -------------------------------- eof -------------------------------------



