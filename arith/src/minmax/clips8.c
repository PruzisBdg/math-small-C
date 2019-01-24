#include "arith.h"

PUBLIC S8 ClipS8(S8 n, S8 min, S8 max)
{
   if( n < min )
      return min;
   else if( n > max )
      return max;
   else
      return n;

}

 
