#include "common.h"
#include "arith.h"

PUBLIC U16 ClipU32toU16(U32 n)
{
   return (n > MAX_U16) ? MAX_U16 : n;
}

  
