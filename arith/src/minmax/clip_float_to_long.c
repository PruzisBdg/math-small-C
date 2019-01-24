#include "common.h"
#include "arith.h"

PUBLIC S32 ClipFloatToLong(float f)
{
   if( f < (float)MIN_LONG )
      return MIN_LONG;
   else if( f > (float)MAX_LONG )
      return MAX_LONG;
   else
      return (S32)f;
   
}

 
