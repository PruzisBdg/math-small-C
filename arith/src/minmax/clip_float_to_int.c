#include "common.h"
#include "arith.h"

PUBLIC S16 ClipFloatToInt(float f)
{
   if( f < (float)MIN_INT )
      return MIN_INT;
   else if( f > (float)MAX_INT )
      return MAX_INT;
   else
      return (S16)f;
}


 
