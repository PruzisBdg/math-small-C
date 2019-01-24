#include "common.h"
#include "arith.h"

PUBLIC U8 ClipS16toU8(S16 n)
{
   return (U8)ClipInt(n, MIN_U8, MAX_U8);
}

 
