#include "common.h"
#include "arith.h"

PUBLIC S32 ClipFloatToS32_old(float f)
{
   if( f < (float)MIN_S32 )
      return MIN_S32;
   else if( f > (float)MAX_S32 )
      return MAX_S32;
   else
      return (S32)f;
}


