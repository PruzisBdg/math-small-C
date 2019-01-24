#include "common.h"
#include "arith.h"

PUBLIC S16 AmulBdivC_S16(S16 a, S16 b, S16 c)
{
   return ClipLongToInt( (a * (S32)b) / c );
} 
