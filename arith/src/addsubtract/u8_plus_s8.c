#include "common.h"
#include "arith.h"

/* The sum of uchar and a char, limited to an uchar

   For when the arithmetic musn't wrap on overrange.
*/

PUBLIC U8 U8PlusS8(U8 a, S8 b) 
{ 
   return ClipS16toU8((S16)a + b); 
}

 
