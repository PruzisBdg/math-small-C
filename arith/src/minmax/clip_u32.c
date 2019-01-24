#include "common.h"
#include "arith.h"

PUBLIC U32 ClipU32(S32 n, U32 min, U32 max)
{
   if( n < min )
      return min;
   else if( n > max )
      return max;
   else
      return n;
}

  
