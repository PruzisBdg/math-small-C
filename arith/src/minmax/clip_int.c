#include "common.h"
#include "arith.h"

PUBLIC S16 ClipInt(S16 n, S16 min, S16 max)
{
   if( n < min )
      return min;
   else if( n > max )
      return max;
   else
      return n;
}

 
