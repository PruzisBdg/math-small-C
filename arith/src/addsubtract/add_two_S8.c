#include "common.h"
#include "arith.h"

/* The sum of 2 chars, limited to a char

   For when the arithmetic musn't wrap on overrange.
*/

PUBLIC S8 AddTwoS8(S8 a, S8 b)
{
   return ClipS16toS8( ((S16)a + (S16)b) );
}

 
