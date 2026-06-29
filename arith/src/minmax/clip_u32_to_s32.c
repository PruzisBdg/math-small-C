#include "common.h"
#include "arith.h"

PUBLIC S32 ClipU32toS32(U32 n)
{
   return n >= MAX_S32 ? MAX_S32 : n;
}


