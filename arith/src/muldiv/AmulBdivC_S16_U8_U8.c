#include "common.h"
#include "arith.h"

PUBLIC S16 AmulBdivC_S16U8(S16 a, U8 b, U8 c)
{
   return ClipLongToInt( (a * (S32)b) / c );
} 
