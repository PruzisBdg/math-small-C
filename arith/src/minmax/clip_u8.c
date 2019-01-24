#include "common.h"
#include "arith.h"

PUBLIC U8 ClipU8(U8 n, U8 min, U8 max)
{
   if( n < min )
      return min;
   else if( n > max )
      return max;
   else
      return n;
}

 
