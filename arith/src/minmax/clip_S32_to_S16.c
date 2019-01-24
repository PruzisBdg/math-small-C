#include "common.h"
#include "arith.h"

PUBLIC S16 ClipS32_S16Limits(S32 n, S16 min, S16 max)
{
   if( n < min )
      return min;
   else if( n > max )
      return max;
   else
      return n;
}


