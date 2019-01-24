#include "common.h"
#include "arith.h"

PUBLIC BIT InsideLimitsU8(U8 n, U8 min, U8 max)
{
   if( n <= min )
      return 0;
   else if( n >= max )
      return 0;
   else
      return 1;
}

   
