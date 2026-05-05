#include "common.h"
#include "arith.h"

PUBLIC U32 ClipFloatToU32(float f)
{
   return
      f <= 0.0
         ? 0
         : (f > (float)MAX_U32
            ? MAX_U32
            : (U32)f);
}

// --------------------------------- eof ----------------------------------


  
