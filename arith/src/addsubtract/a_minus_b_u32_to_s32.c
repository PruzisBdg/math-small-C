#include "common.h"
#include "arith.h"

/* The difference of 2 unsigned longs, limited to an unsigned long
   and clipped against arithmetic overrange.
*/

PUBLIC S32 AminusBU32toS32(U32 a, U32 b)
{
   return (a > b) ? ClipU32toS32(a - b) : -ClipU32toS32(b - a);
}


