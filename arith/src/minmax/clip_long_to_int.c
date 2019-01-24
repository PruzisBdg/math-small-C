#include "arith.h"

PUBLIC S16 ClipLongToInt(S32 l)
{
   if( l < -32768L )
      return -32768;
   else if( l > 32767L )
      return 32767;
   else
      return l;
}

 
