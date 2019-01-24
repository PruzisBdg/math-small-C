#include "common.h"
#include "arith.h"

/* The sum of 2 uchars, limited to an uchar

   For when the arithmetic musn't wrap on overrange.
*/

PUBLIC U8 AddTwoU8(U8 a, U8 b)
{
   return ClipS16toU8( ((S16)a + (S16)b) );
}

 
