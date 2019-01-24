#include "common.h"
#include "arith.h"

/* The difference of 2 ints, limited to an int

   For when the arithmetic musn't wrap on overrange.
*/

PUBLIC S16 AminusBS16(S16 a, S16 b)
{
   return ClipLongToInt( ((S32)a - (S32)b) );
}

  
