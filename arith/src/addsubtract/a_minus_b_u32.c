#include "common.h"
#include "arith.h"

/* The difference of 2 unsigned longs, limited to an unsigned long
   and clipped against arithmetic overrange.
*/

PUBLIC U32 AminusBU32(U32 a, U32 b)
{
   return (a > b) ? a - b : 0;
}

   
