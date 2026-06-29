#include "common.h"
#include "arith.h"
#include <float.h>

PUBLIC long ClipFloatToLong(float f)
{
   if(isnan(f))
      return 0;
   // Next 2 clauses use '<=' and ''>=' to capture MIN_S32 and MAX_S32 and avoid sign-reversal trying to (S32)cast.
   else if( f <= (float)MIN_LONG || f == FLT_MIN )
      return MIN_LONG;
   else if( f >= (float)MAX_LONG || f == FLT_MAX)
      return MAX_LONG;
   else
      return (long)f;
}


