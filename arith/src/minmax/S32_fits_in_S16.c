#include "arith.h"

PUBLIC BIT S32FitsInS16(S32 l)
{
   return (l < -32768L) ? 0 : (l > 32767L ? 0 : 1);
}

  
