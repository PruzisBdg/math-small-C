#include "common.h"
#include "arith.h"

PUBLIC U8 U8byTenths(U8 n, U8 tenths)
{
   return AmulBdivC_U8(n, tenths, 10);
}

 
