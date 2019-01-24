/*-----------------------------------------------------------------------------------------
|
|  Keepout_S16
|
|  Clip 'n' to ON or OUTSIDE -lim < n < lim. n == 0 returns 'lim'; the high side.
|
------------------------------------------------------------------------------------------*/

#include "arith.h"
#include "common.h"

PUBLIC S16 Keepout_S16(S16 n, S16 min)
{
   return (n < 0) ? MinS16(n, -min) : MaxS16(n, min);
}

 
