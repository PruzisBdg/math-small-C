#include "arith.h"

PUBLIC BIT WithinPcentS16(S16 a, S16 b, U8 maxPcentApart)
{
   return PcentDiffS16(a, b) < maxPcentApart;
}


  
