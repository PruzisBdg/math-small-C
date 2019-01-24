#include "common.h"
#include "arith.h"

PUBLIC U8 U8byPcent(U8 n, U8 pcent)
{
   return AmulBdivC_U8(n, pcent, 100);
}

 
