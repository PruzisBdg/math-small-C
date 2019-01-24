#include "common.h"
#include "arith.h"

PUBLIC S32 ClipLong(S32 n, S32 min, S32 max)
{
   if( n < min )
      return min;
   else if( n > max )
      return max;
   else
      return n;
}

 
