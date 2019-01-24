#include "common.h"
#include "arith.h"

PUBLIC BIT InsideLimitsS16(S16 n, S16 min, S16 max)
{
   if( n <= min )
      return 0;
   else if( n >= max )
      return 0;
   else
      return 1;
}

  
