#include "common.h"
#include "arith.h"


PUBLIC S16 S16byPcent(S16 n, U8 pcent)
{
   return AmulBdivC_S16U8(n, pcent, 100);
}


