#include "common.h"
#include "arith.h"

PUBLIC S8 ClipS16toS8(S16 n)
{
   return (S8)ClipInt(n, MIN_S8, MAX_S8);
}

  
