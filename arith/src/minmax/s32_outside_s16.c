#include "arith.h"

PUBLIC BIT S32outsideS16(S32 l)
{
   if( l < -32768L )
      return 1;
   else if( l > 32767L )
      return 1;
   else
      return 0;
}

  
