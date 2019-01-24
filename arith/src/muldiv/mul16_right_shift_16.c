#include "common.h"
#include "arith.h"

/* ----------------------------- MulS16ToS16 --------------------------------------- */

PUBLIC S16 MulS16_RS16(S16 a, S16 b)
{
   return MulS16(a, b) >> 16;
}

