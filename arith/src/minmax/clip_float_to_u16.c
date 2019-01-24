#include "common.h"
#include "arith.h"

PUBLIC U16 ClipFloatToU16(float f)
{
   return
      f <= 0.0
         ? 0
         : (f > (float)MAX_U16
            ? MAX_U16
            : (U16)f);
}

// --------------------------------- eof ----------------------------------


  
