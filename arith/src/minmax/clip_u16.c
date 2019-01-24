#include "common.h"
#include "arith.h"

PUBLIC U16 ClipU16(U16 n, U16 min, U16 max)
{
   if( n < min )
      return min;
   else if( n > max )
      return max;
   else
      return n;

}

 
